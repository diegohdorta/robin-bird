/* Copyright (c) 2019 NXP Semiconductors
 *
 * SPDX-License-Identifier: GPL3
 * Marco Franchi <marco.franchi@nxp.com>
 */
#ifndef GTKMM_HANDWRITTEN_DIGIT_INPUT_UI_H
#define GTKMM_HANDWRITTEN_DIGIT_INPUT_UI_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/cairomm.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "results.h"

using namespace std;
using namespace cv;

class HandWrittenDigitInputUI : public Gtk::DrawingArea {
public:
	HandWrittenDigitInputUI();

	Results resultsLink;
	virtual ~HandWrittenDigitInputUI() { };
	void on_clear_button();
	bool configure_surface ();
	Cairo::RefPtr<Cairo::ImageSurface> surface;
	Cairo::RefPtr<Cairo::Context> cr;

protected:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	void draw_brush(double x, double y);
	bool on_button_press_event(GdkEventButton *event);
	bool on_motion_notify_event(GdkEventMotion *event) override;
	void clear_surface();
	void result_image();

}; //HandWrittenDigitInputUI

#endif /* GTKMM_HANDWRITTEN_DIGIT_INPUT_UI_H */
