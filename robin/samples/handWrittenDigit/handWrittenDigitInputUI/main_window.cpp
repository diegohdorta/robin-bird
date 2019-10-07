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
#include "main_window.h"

MainWindow::MainWindow(int argc, char *argv[]) : clearButton("Clear") {
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
	resultFrame.add(mainDrawArea.resultsLink);
	mainGrid.attach(resultFrame, 3, 1, 1, 1);

	clearButton.set_halign(Gtk::ALIGN_END);
	clearButton.set_valign(Gtk::ALIGN_CENTER);
	mainGrid.attach(clearButton, 1, 2, 1, 1);

	clearButton.signal_clicked().connect(sigc::mem_fun(mainDrawArea,
			&HandWrittenDigitInputUI::on_clear_button));

	mainDrawArea.resultsLink.modelName = argv[1];

	add(mainGrid);

	show_all_children();
}

MainWindow::~MainWindow()
{
}
