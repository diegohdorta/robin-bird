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
	RobinBird nn(modelName);
	HandwrittenDigit foo(std::move(nn));

	std::vector<double> image = readImage("cropped.png");
	resultsVector = foo.runInferenceSingleImageToVector(image);
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
}
