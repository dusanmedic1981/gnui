//
// "$Id$"
//
// Popup list of items that the user can choose one of. Based on Motif
// but modern equivalent is the OS/X popup choices.
//
// This is not a "combo box". You should try this, but if you insist
// on that use the InputBrowser widget.
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

#ifndef gnui_Choice_h
#define gnui_Choice_h

#include "Menu.h"

namespace gnui {

class GNUI_API Choice : public Menu {
public:
  int handle(int);
  int handle(int, const Rectangle&);
  Choice(int,int,int,int,const char * = 0);
  static NamedStyle* default_style;
  void draw();
};

}

#endif

//
// End of "$Id$".
//
