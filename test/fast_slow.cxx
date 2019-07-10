// generated by Fast Light User Interface Designer (fluid) version 2.0001

#include "fast_slow.h"

GNUI_Slider* control;

static void cb_control(GNUI_Slider* o, void*) {
  fast->value(o->value());
  if (!Fl::pushed()) slow->value(o->value());
}

GNUI_Slider* fast;

GNUI_Slider* slow;

int main (int argc, char **argv) {

  GNUI_Window* w;
   {GNUI_Window* o = new GNUI_Window(318, 443);
    w = o;
     {GNUI_Slider* o = control = new GNUI_Slider(90, 200, 30, 200, "move\nthis");
      o->callback((GNUI_Callback*)cb_control);
      o->when(GNUI_WHEN_CHANGED|GNUI_WHEN_RELEASE|GNUI_WHEN_NOT_CHANGED);
    }
     {GNUI_Slider* o = fast = new GNUI_Slider(140, 200, 30, 200, "fast\nredraw");
      o->set_output();
    }
     {GNUI_Slider* o = slow = new GNUI_Slider(190, 200, 30, 200, "slow\nredraw");
      o->set_output();
    }
     {GNUI_Box* o = new GNUI_Box(10, 10, 300, 180, "The left slider has\nchanged(GNUI_WHEN_CHANGED | GNUI_WHEN_RELEASE | GNUI_WHEN_NOT_\
CHANGED) so it produces a callback on both drag and release mouse events.\n\nT\
he middle slider (representing a widget with low overhead) is changed on every\
 mouse movement.\n\nThe right slider (representing a widget with high overhead\
) is only updated when the mouse is released, by checking if Fl::pushed() is z\
ero.");
      o->box(GNUI_DOWN_BOX);
      o->color((GNUI_Color)53);
      o->selection_color((GNUI_Color)47);
      o->align(132|GNUI_ALIGN_INSIDE);
    }
    o->end();
    o->resizable(o);
  }
  w->show(argc, argv);
  return  Fl::run();
}
