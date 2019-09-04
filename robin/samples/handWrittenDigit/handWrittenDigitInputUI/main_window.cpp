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
#include "main_window.h"

MainWindow::MainWindow() : clearButton("Clear") {
	set_title("AI/ML Digit Gui - v0.1");
	set_border_width(10);
	
	drawAreaLabel.set_text("Draw digit");
	drawAreaLabel.set_halign(Gtk::ALIGN_START);
	drawAreaBox.pack_start(drawAreaLabel);
	mainGrid.attach(drawAreaBox, 1, 0, 1, 1);

	resultLabel.set_text("Results");
	resultLabel.set_halign(Gtk::ALIGN_START);
	resultBox.pack_start(resultLabel);
	mainGrid.attach(resultBox, 3, 0, 1, 1);

	digitLabel.set_text("0\n\n1\n\n2\n\n3\n\n4\n\n5\n\n6\n\n7\n\n8\n\n9");
	digitLabel.set_halign(Gtk::ALIGN_END);
	digitBox.set_border_width(10);
	digitBox.set_spacing(30);
	digitBox.pack_start(digitLabel);
	mainGrid.attach(digitBox, 2, 1, 1, 1);
	
	drawAreaFrame.set_size_request(340, 340);
	drawAreaFrame.add(mainDrawArea);
	mainGrid.attach(drawAreaFrame, 1, 1, 1, 1);

	resultFrame.set_size_request(160, 340);
	resultFrame.add(resultsGrid);
	mainGrid.attach(resultFrame, 3, 1, 1, 1);

	clearButton.set_halign(Gtk::ALIGN_END);
	clearButton.set_valign(Gtk::ALIGN_CENTER);
	mainGrid.attach(clearButton, 1, 2, 1, 1);

	clearButton.signal_clicked().connect(sigc::mem_fun(mainDrawArea,
			&HandWrittenDigitInputUI::on_clear_button));

	add(mainGrid);

	show_all_children();
}

MainWindow::~MainWindow()
{
}
