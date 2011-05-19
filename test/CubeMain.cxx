//
// "$Id$"
//
// CubeView class .
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

#include <config.h>
#include <fltk3/run.h>
#include "CubeViewUI.h"

int
main(int argc, char **argv) {

    CubeViewUI *cvui=new CubeViewUI;
    
//Initial global objects.
    
    Fl::visual(FL_DOUBLE|FL_INDEX);

    cvui->show(argc, argv);
    
    return fltk3::run();
}


//
// End of "$Id$".
//
