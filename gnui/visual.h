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

#ifndef gnui_visual_h
#define gnui_visual_h

#include "GNUI_API.h"

namespace gnui {

/// \name gnui/visual.h
//@{

enum {
  RGB_COLOR	= 0,
  INDEXED_COLOR	= 1,
  SINGLE_BUFFER	= 0,
  DOUBLE_BUFFER	= 2,
  ACCUM_BUFFER	= 4,
  ALPHA_BUFFER	= 8,
  DEPTH_BUFFER	= 16,
  STENCIL_BUFFER= 32,
  RGB24_COLOR	= 64,
  MULTISAMPLE	= 128,
  STEREO	= 256
};

extern GNUI_API bool visual(int);

extern GNUI_GL_API bool glVisual(int);

extern GNUI_API void own_colormap();

//@}

}

#endif
