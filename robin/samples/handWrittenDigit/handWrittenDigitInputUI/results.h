#ifndef RESULTS_H
#define RESULTS_H

#include <gtkmm.h>

#include <string>
#include <iostream>

using namespace std;

class Results : public Gtk::Grid {
public:
	Results();

	virtual ~Results();
	
protected:
	void initialize();
	void print_results();
	void clear_results();
	bool get_results();
	Gtk::Entry percentage[10];

}; //RESULTS

#endif /* RESULTS_GUI_H */
