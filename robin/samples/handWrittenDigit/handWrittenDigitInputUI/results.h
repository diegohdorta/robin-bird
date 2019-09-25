#ifndef RESULTS_H
#define RESULTS_H

#include <gtkmm.h>

#include <string>
#include <iostream>

#include "math.h"
#include <robin-image.h>
#include <robin-nn.h>
#include <hwd.h>

using namespace std;

class Results : public Gtk::Grid {
public:
	Results();
	virtual ~Results();
	void clear_results();
	void get_results();
	
protected:
	void initialize();
	void print_results();
	Gtk::Entry percentage[10];
	Matrix<double> resultsVector;

}; //RESULTS

#endif /* RESULTS_GUI_H */
