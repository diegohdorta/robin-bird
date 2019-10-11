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
#include "results.h"

Results::Results() {
	set_row_homogeneous(true);
	initialize();
	show_all_children();
}

Results::~Results()
{
}

void Results::initialize() {
	for(int i = 0; i < 10; i++) {
		percentage[i].set_editable(false);
		percentage[i].set_can_focus(false);
		percentage[i].set_max_length(4);
		percentage[i].set_text("0%");
		percentage[i].set_alignment(Gtk::ALIGN_CENTER);
		percentage[i].set_valign(Gtk::ALIGN_CENTER);
		percentage[i].set_progress_fraction(-1);
		attach(percentage[i], 0, i, 1, 1);
	}
}

void Results::get_results(){
	gettimeofday(&start, NULL);
	RobinBird nn(modelName);
	HandwrittenDigit foo(std::move(nn));

	std::vector<double> image = readImage("cropped.png");
	resultsVector = foo.runInferenceSingleImageToVector(image);
	gettimeofday(&end, NULL);

	double inf = 1/((end.tv_usec - start.tv_usec)* 1e-6);
	ostringstream strToPrint;
	strToPrint << fixed << setprecision(2) << inf;
	inferenceResultsLabel.set_text(strToPrint.str());

	print_results();
}

void Results::print_results () {
	for(int i = 0; i < 10; i++) {
		percentage[i].set_text(to_string(resultsVector(0, i)));
		percentage[i].set_progress_fraction(resultsVector(0, i));
	}
}

void Results::clear_results() {
	for(int i = 0; i < 10; i++) {
		percentage[i].set_text("0%");
		percentage[i].set_progress_fraction(-1);
	}
	inferenceResultsLabel.set_text("");
}
