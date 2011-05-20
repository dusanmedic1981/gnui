//
// "$Id$"
//
// fltk3::HelpDialog dialog for the Fast Light Tool Kit (FLTK).
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

// fltk3::HelpDialog (autogenerated class) doxygen documentation placeholder

/** \class fltk3::HelpDialog
  The fltk3::HelpDialog widget displays a standard help dialog window
  using the fltk3::HelpView widget.
  
  <P ALIGN=CENTER> \image html fltk3::HelpDialog.png </P> 
  \image latex  fltk3::HelpDialog.png "fltk3::HelpDialog" width=8cm
*/

/** \fn fltk3::HelpDialog::fltk3::HelpDialog()
  The constructor creates the dialog pictured above.*/

/** \fn fltk3::HelpDialog::~Fl_Help_Dialog()
  The destructor destroys the widget and frees all memory that has been
  allocated for the current file.
*/

/** \fn void fltk3::HelpDialog::hide()
  Hides the fltk3::HelpDialog window.*/

/** \fn void fltk3::HelpDialog::load(const char *f)
  Loads the specified HTML file into the fltk3::HelpView widget.
  The filename can also contain a target name ("filename.html#target").
*/

/** \fn void fltk3::HelpDialog::position(int x, int y)
  Set the screen position of the dialog.*/

/** \fn void fltk3::HelpDialog::resize(int xx, int yy, int ww, int hh)
  Change the position and size of the dialog.*/

/** \fn void fltk3::HelpDialog::show()
  Shows the fltk3::HelpDialog window.*/

/** \fn void fltk3::HelpDialog::textsize(fltk3::Fontsize s)
  Sets or gets the default text size for the help view.*/

/** \fn uchar fltk3::HelpDialog::textsize()
  Sets or gets the default text size for the help view.*/

/** \fn void fltk3::HelpDialog::topline(const char *n)
  Sets the top line in the fltk3::HelpView widget to the named or
  numbered line.
*/

/** \fn void fltk3::HelpDialog::topline(int n)
  Sets the top line in the fltk3::HelpView widget to the named or
  numbered line.
*/

/** \fn void fltk3::HelpDialog::value(const char *v)
  The first form sets the current buffer to the string provided and
  reformats the text. It also clears the history of the "back" and
  "forward" buttons. The second form returns the current buffer contents.
*/

/** \fn const char *fltk3::HelpDialog::value() const
  The first form sets the current buffer to the string provided and
  reformats the text. It also clears the history of the "back" and
  "forward" buttons. The second form returns the current buffer contents.
*/

/** \fn int fltk3::HelpDialog::visible()
  Returns 1 if the fltk3::HelpDialog window is visible.*/

/** \fn int fltk3::HelpDialog::x()
  Returns the position and size of the help dialog.*/

/** \fn int fltk3::HelpDialog::y()
  Returns the position and size of the help dialog.*/

/** \fn int fltk3::HelpDialog::w()
  Returns the position and size of the help dialog.*/

/** \fn int fltk3::HelpDialog::h()
  Returns the position and size of the help dialog.*/

/** \fn void fltk3::HelpDialog::show()
  Shows the main Help Dialog Window
  Delegates call to encapsulated window_ void fltk3::Window::show() method */

/** \fn void fltk3::HelpDialog::show(int argc, char **argv)
  Shows the main Help Dialog Window
  Delegates call to encapsulated window_ void fltk3::Window::show(int argc, char **argv) instance method */

/** \fn void fltk3::HelpDialog::textsize(fltk3::Fontsize s)
  Sets the internal fltk3::HelpView instance text size.
  Delegates call to encapsulated view_ void fltk3::HelpView::textsize(fltk3::Fontsize s) instance method */

//
// End of "$Id$".
//
