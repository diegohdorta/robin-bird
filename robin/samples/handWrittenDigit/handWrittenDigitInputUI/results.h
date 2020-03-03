/* Copyright 2019-2020 Diego Dorta, Marco Franchi
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef RESULTS_H
#define RESULTS_H

#include <gtkmm.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sys/time.h>

#include "math.h"
#include <robin-image.h>
#include <robin-nn.h>
#include <hwd.h>

using namespace std;

class Results : public Gtk::Grid {

struct timeval start, end;

public:
	Results();
	virtual ~Results();
	void clear_results();
	void get_results();
	const char *modelName;
	Gtk::Box inferenceResultsBox;
	Gtk::Label inferenceResultsLabel;
	
protected:
	void initialize();
	void print_results();
	Gtk::Entry percentage[10];
	Matrix<double> resultsVector;

}; //RESULTS

#endif /* RESULTS_GUI_H */
