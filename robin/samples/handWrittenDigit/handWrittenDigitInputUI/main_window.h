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
#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm.h>

#include "handWrittenDigitInputUI.h"
#include "results.h"

class MainWindow : public Gtk::Window {
public:
	MainWindow();
	virtual ~MainWindow();

private:

	Gtk::Grid mainGrid;
	Gtk::Box drawAreaBox, resultBox, digitBox;
	Gtk::Label drawAreaLabel, resultLabel, digitLabel;
	Gtk::Frame drawAreaFrame, drawDigitFrame, resultFrame;
	HandWrittenDigitInputUI mainDrawArea;
	Results resultsGrid;
	Gtk::Button clearButton;
};

#endif /* GTKMM_MAINWINDOW_H */
