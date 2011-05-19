//
// "$Id$"
//
// FLUID print panel for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// generated by Fast Light User Interface Designer (fluid) version 1.0300

#ifndef print_panel_h
#define print_panel_h
#include <fltk3/run.h>
#include <fltk3/DoubleWindow.h>
extern fltk3::DoubleWindow *print_panel;
#include <fltk3/Group.h>
extern fltk3::Group *print_panel_controls;
#include <fltk3/Choice.h>
extern fltk3::Choice *print_choice;
#include <fltk3/Button.h>
extern fltk3::Button *print_properties;
#include <fltk3/Box.h>
extern fltk3::Box *print_status;
#include <fltk3/RoundButton.h>
extern fltk3::RoundButton *print_all;
extern fltk3::RoundButton *print_pages;
extern fltk3::RoundButton *print_selection;
#include <fltk3/IntInput.h>
extern Fl_Int_Input *print_from;
extern Fl_Int_Input *print_to;
#include <fltk3/Spinner.h>
extern Fl_Spinner *print_copies;
#include <fltk3/CheckButton.h>
extern fltk3::CheckButton *print_collate_button;
extern fltk3::Group *print_collate_group[2];
#include <fltk3/ReturnButton.h>
extern void print_cb(fltk3::ReturnButton*, void*);
#include <fltk3/Progress.h>
extern Fl_Progress *print_progress;
extern fltk3::DoubleWindow *print_properties_panel;
extern fltk3::Choice *print_page_size;
extern fltk3::Button *print_output_mode[4];
fltk3::DoubleWindow* make_print_panel();
extern fltk3::MenuItem menu_print_page_size[];
extern void print_cb(fltk3::ReturnButton *, void *); 
void print_load();
void print_update_status();
#endif

//
// End of "$Id$".
//
