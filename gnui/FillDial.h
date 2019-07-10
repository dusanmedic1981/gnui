//
// "$Id$"
//
// Copyright 2002 by Bill Spitzak and others.
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

#ifndef gnui_FillDial_h
#define gnui_FillDial_h

#include "Dial.h"

namespace gnui {

/*! Dial but the constructor sets type() to FILL, so it draws a pie slice. */
class GNUI_API FillDial : public Dial {
public:
    FillDial(int x,int y,int w,int h, const char *l = 0)
      : Dial(x,y,w,h,l) {type(FILL);}
};

}

#endif

//
// End of "$Id$".
//
