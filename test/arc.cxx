//
// "$Id$"
//
// Arc drawing test program for the Fast Light Tool Kit (FLTK).
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

#include <fltk3/run.h>
#include <fltk3/DoubleWindow.h>
#include <fltk3/HorValueSlider.h>
#include <fltk3/draw.h>

using namespace fltk3;

double val[6] = {140, 140, 50, 0, 360, 0};
const char* name[6] = {"X", "Y", "R", "start", "end", "rotate"};

class Drawing : public Widget {
  void draw() {
    push_clip(x(),y(),w(),h());
    fltk3::color(DARK3);
    rectf(x(),y(),w(),h());
    push_matrix();
    if (val[5]) {
      translate(x()+w()/2.0, y()+h()/2.0);
      rotate(val[5]);
      translate(-(x()+w()/2.0), -(y()+h()/2.0));
    }
    fltk3::color(WHITE);
    translate(x(),y());
    begin_complex_polygon();
    arc(val[0],val[1],val[2],val[3],val[4]);
    gap();
    arc(140,140,20,0,-360);
    end_complex_polygon();
    fltk3::color(RED);
    begin_line();
    arc(val[0],val[1],val[2],val[3],val[4]);
    end_line();
    pop_matrix();
    pop_clip();
  }
public:
  Drawing(int X,int Y,int W,int H) : Widget(X,Y,W,H) {}
};

Drawing *d;

void slider_cb(Widget* o, void* v) {
  fltk3::Slider* s = (fltk3::Slider*)o;
  val[fl_intptr_t(v)] = s->value();
  d->redraw();
}

int main(int argc, char** argv) {
  DoubleWindow window(300,500);
  Drawing drawing(10,10,280,280);
  d = &drawing;

  int y = 300;
  for (int n = 0; n<6; n++) {
    fltk3::Slider* s = new fltk3::HorValueSlider(50,y,240,25,name[n]); y += 25;
    if (n<3) {s->minimum(0); s->maximum(300);}
    else if (n==5) {s->minimum(0); s->maximum(360);}
    else {s->minimum(-360); s->maximum(360);}
    s->step(1);
    s->value(val[n]);
    s->align(ALIGN_LEFT);
    s->callback(slider_cb, (void*)n);
  }

  window.end();
  window.show(argc,argv);
  return run();
}


//
// End of "$Id$".
//

