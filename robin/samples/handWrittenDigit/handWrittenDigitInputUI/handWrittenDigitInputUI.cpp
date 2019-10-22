/* Copyright 2019 NXP Semiconductors
 *   
 * SPDX-License-Identifier: MIT
 * Marco Franchi <marco.franchi@nxp.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
	xx = x;
	yy = y;
	cr->rectangle(xx-12, yy-12, 24, 24);
	cr->fill();
	queue_draw();
	result_image();
}

void HandWrittenDigitInputUI::connect_draw_brush(double x2, double y2) {
	cr->set_line_width(24);
	cr->move_to(xx, yy);
	cr->line_to(x2, y2);
	cr->stroke();
	cr->rectangle(x2-9, y2-9, 18, 18);
	cr->fill();
	queue_draw();
	result_image();
	xx = x2;
	yy = y2;
}

void HandWrittenDigitInputUI::on_clear_button() {
	clear_surface();
	queue_draw();
	surface->write_to_png("temp.png");
	Mat resultImage = cv::imread("temp.png", IMREAD_GRAYSCALE);
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
		connect_draw_brush(event->x, event->y);
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

	Mat resultImage = cv::imread("temp.png", IMREAD_GRAYSCALE);
	vector<vector<Point>> contours;
	vector<Point> result;
	vector<vector<Point>> contours_t;
	Rect roi;

	threshold(resultImage, resultImage, 60, 255, THRESH_BINARY_INV);
	findContours(resultImage, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	sort(contours.begin(), contours.end(), compareAreas);
	approxPolyDP(contours[contours.size()-1], result, 0.02*arcLength(contours[contours.size()-1], true), true);
	contours_t.push_back(result);
	roi = boundingRect(Mat(contours_t[0]));

	Mat cropImage = resultImage(roi);
	threshold(cropImage, cropImage, 0, 255, THRESH_BINARY_INV);
	resize(cropImage, cropImage, Size(32, 32), 0, 0, INTER_AREA);
	imwrite("cropped.png", cropImage);
	resultsLink.get_results();
}
