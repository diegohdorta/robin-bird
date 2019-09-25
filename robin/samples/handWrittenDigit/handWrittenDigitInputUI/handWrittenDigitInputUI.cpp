/* Copyright (c) 2019 NXP Semiconductors
 *
 * SPDX-License-Identifier: GPL3
 * Marco Franchi <marco.franchi@nxp.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or 2 any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "handWrittenDigitInputUI.h"

HandWrittenDigitInputUI::HandWrittenDigitInputUI() {
	configure_surface();
	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK);
}

bool HandWrittenDigitInputUI::configure_surface () {
	surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 340, 340);
	cr = Cairo::Context::create(surface);

	clear_surface();

	return true;
}

void HandWrittenDigitInputUI::clear_surface() {
	cr->save();
	cr->set_source_rgb (1, 1, 1);
	cr->paint();
	cr->restore();
}

void HandWrittenDigitInputUI::draw_brush(double x, double y) {
	cr->rectangle(x-1, y, 24, 24);
	cr->rectangle(x+1, y, 24, 24);
	cr->rectangle(x, y-1, 24, 24);
	cr->rectangle(x, y+1, 24, 24);
	cr->rectangle(x, y, 24, 24);
	cr->fill();
	queue_draw();
	result_image();
}

void HandWrittenDigitInputUI::on_clear_button() {
	clear_surface();
	queue_draw();
	surface->write_to_png("temp.png");
	Mat resultImage = cv::imread("temp.png", CV_LOAD_IMAGE_GRAYSCALE);
	imwrite("cropped.png", resultImage);
	resultsLink.clear_results();
}

bool HandWrittenDigitInputUI::on_button_press_event(GdkEventButton *event) {
	if (event->button == GDK_BUTTON_PRIMARY)
		draw_brush(event->x, event->y);
	return true;
}

bool HandWrittenDigitInputUI::on_motion_notify_event(GdkEventMotion *event) {
	if (event->state & Gdk::BUTTON1_MASK)
		draw_brush(event->x, event->y);
	return true;
}

bool HandWrittenDigitInputUI::on_draw(Cairo::RefPtr<Cairo::Context> const & cr) {
	cr->set_source (surface, 0, 0);
	cr->paint();

	return false;
}

bool compareAreas(vector<Point> c1, vector<Point> c2) {
	return (fabs(contourArea(Mat(c1))) < fabs(contourArea(Mat(c2))));
}

void HandWrittenDigitInputUI::result_image() {
	//TODO: try to convert the surface direct to a Mat Frame
	surface->write_to_png("temp.png");

	Mat resultImage = cv::imread("temp.png", CV_LOAD_IMAGE_GRAYSCALE);
	vector<vector<Point>> contours;
	vector<Point> result;
	vector<vector<Point>> contours_t;
	Rect roi;

	threshold(resultImage, resultImage, 60, 255, CV_THRESH_BINARY_INV);
	findContours(resultImage, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	sort(contours.begin(), contours.end(), compareAreas);
	approxPolyDP(contours[contours.size()-1], result, 0.02*arcLength(contours[contours.size()-1], true), true);
	contours_t.push_back(result);
	roi = boundingRect(Mat(contours_t[0]));

	Mat cropImage = resultImage(roi);
	threshold(cropImage, cropImage, 0, 255, CV_THRESH_BINARY_INV);
	resize(cropImage, cropImage, Size(32, 32), 0, 0, INTER_AREA);
	imwrite("cropped.png", cropImage);
	resultsLink.get_results();
}
