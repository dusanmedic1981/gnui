// "$Id$"
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
//    http://www.gnui.org/str.php

/** \file

Declarations of FLTK symbols and interfaces that only exist if FLTK is
compiled on Windows. It is recommended you avoid using this header
file, and that you segregate code requiring it to it's own source
file.

FLTK is currently using the Carbon interface, and this includes
the <Carbon/Carbon.h> header file. A macro is used to rename the
Carbon "Style" as "XStyle" to avoid conflicts with FLTK. (all
drawing is using Quartz, however!)

Many of the functions have the same name and purpose as ones defined
in x11.h, just with different return types. Due to how Doxygen works,
the X version of these is described here.
*/

#ifndef gnui_osx_h
#define gnui_osx_h

# ifndef DOXYGEN
// Standard MacOS Carbon API includes...
#  define Style XStyle
#  include <Carbon/Carbon.h>
#  undef Style

// Now make some fixes to the headers...
#  undef check			// Dunno where this comes from...
# endif

# include "draw.h"

////////////////////////////////////////////////////////////////

namespace gnui {

/// \name gnui/osx.h
//@{

////////////////////////////////////////////////////////////////
// constant information about the display:

//extern GNUI_API void    *qdisplay;
extern GNUI_API void	open_display();
extern GNUI_API void	close_display();
extern GNUI_API WindowPtr  quartz_window;
extern GNUI_API CGContextRef quartz_gc;
extern GNUI_API Handle    system_menu;
extern GNUI_API class     SystemMenuBar *system_menu_bar;

////////////////////////////////////////////////////////////////
// event handling:

// we want some way to access last message from system

// Register a function to call when user opens a file in finder:
extern void open_callback(void (*cb)(const char* name));

////////////////////////////////////////////////////////////////
// drawing functions:

extern GNUI_API void	clip_region(RgnHandle);
extern GNUI_API RgnHandle	clip_region();
extern GNUI_API void	draw_into(CGContextRef xid, int w, int h);
extern GNUI_API void	stop_drawing(CGImageRef xid);
# define HFONT const char* // points at name of font!
extern GNUI_API HFONT	xfont();

extern GNUI_API void clear_quartz_clipping();
extern GNUI_API void begin_quartz_image(CGRect&, const Rectangle&);
extern GNUI_API void end_quartz_image();

////////////////////////////////////////////////////////////////
# ifdef gnui_Window_h // only include this if <gnui/Window.h> was included

// When gnui tells X about a window, one of these objects is created.
// Warning: this object is highly subject to change!  It's definition
// is only here so that gnui::xid(Window) can be declared inline:

class GNUI_API CreatedWindow {
public:
  WindowPtr xid; // used by main windows
  Window* window;
  RgnHandle region; // damage region
  void expose(const Rectangle&);
  CreatedWindow* next;
  RgnHandle subRegion; // region which clips out children
  CreatedWindow *children, *brother;
  bool wait_for_expose;
  bool need_new_subRegion;
  bool overlay;
  static CreatedWindow* first;
  static CreatedWindow* find(const Window* window) {return window->i;}
  static int borders(const Window* w, int& dx, int& dy, int& dw, int& dh);
  // Quartz additions:
  CGContextRef gc;
};

extern GNUI_API void fill_quartz_context();
extern GNUI_API void release_quartz_context(CreatedWindow *x=0);

// convert xid <-> Window:
//inline WindowPtr xid(const Window*w) {return CreatedWindow::find(w)->xid;}
WindowPtr xid(const Window*);
Window* find(WindowPtr xid);

extern CursPtr default_cursor;
extern CursPtr current_cursor;
extern const Widget* cursor_for;

# endif //GNUI_Window_H

//@}

}

# if USE_CAIRO
#  include <gnui/gnui_cairo.h>
#  include <cairo-quartz.h>
# else
   typedef struct _cairo cairo_t;
# endif

#endif

// End of "$Id$".
