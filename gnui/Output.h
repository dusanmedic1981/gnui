//
// "$Id$"
//
// One-line text output, the user can select text and copy it
// to other applications.
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
//

#ifndef gnui_Output_h
#define gnui_Output_h

#include "Input.h"

namespace gnui {

class GNUI_API Output : public Input {
  virtual bool replace(int, int, const char*, int); // does nothing
public:
  Output(int x, int y, int w, int h, const char *l = 0);
  int handle(int);
  // this style is so Motif can have different color for output vs input:
  static NamedStyle* default_style;
};

}

#endif 

//
// End of "$Id$".
//
