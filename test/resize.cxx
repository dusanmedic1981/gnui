// generated by Fast Light User Interface Designer (fluid) version 2.1000

#include "resize.h"
#include <fltk/events.h>

void warp(int dx, int dy) {
  gnui::warp_mouse(gnui::event_x_root()+dx, gnui::event_y_root()+dy);
}

static void cb_8(gnui::Button* o, void*) {
  gnui::Window* w = o->window();
  w->position(w->x(),w->y()-50);
  warp(0,-50);
}

static void cb_(gnui::Button* o, void*) {
  gnui::Window* w = o->window();
  w->position(w->x()-50,w->y());
  warp(-50,0);
}

static void cb_1(gnui::Button* o, void*) {
  gnui::Window* w = o->window();
  w->position(w->x()+50,w->y());
  warp(+50,0);
}

static void cb_2(gnui::Button* o, void*) {
  gnui::Window* w = o->window();
  w->position(w->x(),w->y()+50);
  warp(0,+50);
}

static void cb_grow(gnui::Button* o, void*) {
  gnui::Window* w = o->window();
  int mx = gnui::event_x_root()-w->x();
  int my = gnui::event_y_root()-w->y();
  warp(mx*20/w->w(), my*20/w->h());
  w->resize(w->w()+20, w->h()+20);
}

static void cb_shrink(gnui::Button* o, void*) {
  gnui::Window* w = o->window();
  int mx = gnui::event_x_root()-w->x();
  int my = gnui::event_y_root()-w->y();
  warp(-mx*20/w->w(), -my*20/w->h());
  w->resize(w->w()-20, w->h()-20);
}

#include <fltk/run.h>

int main (int argc, char **argv) {

  gnui::Window* w;
   {gnui::Window* o = new gnui::Window(320, 240);
    w = o;
    o->shortcut(0xff1b);
    o->begin();
     {gnui::Button* o = new gnui::Button(60, 0, 39, 40, "@8->");
      o->set_vertical();
      o->callback((gnui::Callback*)cb_8);
    }
     {gnui::InvisibleBox* o = new gnui::InvisibleBox(148, 10, 157, 218, "This is a test of program-generated resize() of a window.  The window should \
move or resize once when each button is clicked.  The program and window manag\
er should not go into fits echoing resizes back and forth!");
      o->set_vertical();
      o->box(gnui::BORDER_BOX);
      o->align(gnui::ALIGN_LEFT|gnui::ALIGN_CENTER|gnui::ALIGN_INSIDE|gnui::ALIGN_WRAP);
      gnui::Group::current()->resizable(o);
    }
     {gnui::Button* o = new gnui::Button(20, 40, 40, 40, "@<-");
      o->set_vertical();
      o->callback((gnui::Callback*)cb_);
    }
     {gnui::Button* o = new gnui::Button(99, 40, 39, 40, "@->");
      o->set_vertical();
      o->callback((gnui::Callback*)cb_1);
    }
     {gnui::Button* o = new gnui::Button(60, 80, 39, 39, "@2->");
      o->set_vertical();
      o->callback((gnui::Callback*)cb_2);
    }
     {gnui::Button* o = new gnui::Button(30, 129, 108, 40, "grow");
      o->labelfont(gnui::HELVETICA_BOLD);
      o->labelsize(18);
      o->callback((gnui::Callback*)cb_grow);
    }
     {gnui::Button* o = new gnui::Button(30, 188, 108, 40, "shrink");
      o->labelfont(gnui::HELVETICA_BOLD);
      o->labelsize(18);
      o->callback((gnui::Callback*)cb_shrink);
    }
    o->end();
  }
  w->show(argc, argv);
  return  gnui::run();
}
