// generated by Fast Light User Interface Designer (fluid) version 2.0100

#include "radio.h"
using namespace gnui;

gnui::LightButton* ttlb;

static void cb_ttlb(gnui::LightButton*, void*) {
  Tooltip::enable(ttlb->value() ? true : false);
}

#include <fltk/run.h>

int main (int argc, char **argv) {

  gnui::Window* w;
   {gnui::Window* o = new gnui::Window(380, 274, "Radio buttons and Tooltips");
    w = o;
    o->tooltip("This is a window");
    o->begin();
     {gnui::Button* o = new gnui::Button(20, 10, 160, 25, "Button");
      o->tooltip("This is a button");
    }
     {gnui::ReturnButton* o = new gnui::ReturnButton(20, 40, 160, 25, "ReturnButton");
      o->shortcut(0xff0d);
      o->tooltip("This is a return button");
    }
     {gnui::LightButton* o = new gnui::LightButton(20, 70, 160, 25, "LightButton");
      o->tooltip("This is a light button!  This particular light button has a very long tooltip\
.  This tooltip should demonstrate that very long tooltips are wrapped across \
multiple lines.");
    }
     {gnui::CheckButton* o = new gnui::CheckButton(20, 100, 160, 25, "CheckButton");
      o->tooltip("This is a check button");
    }
     {gnui::RadioButton* o = new gnui::RadioButton(20, 125, 160, 25, "RoundButton");
      o->tooltip("This is a round button");
    }
     {gnui::Group* o = new gnui::Group(190, 10, 70, 200);
      o->set_vertical();
      o->tooltip("This is a group");
      o->begin();
       {gnui::CheckButton* o = new gnui::CheckButton(0, 0, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 25, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 50, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 75, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 100, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 125, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 150, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
       {gnui::CheckButton* o = new gnui::CheckButton(0, 175, 70, 25, "radio");
        o->type(gnui::CheckButton::RADIO);
        o->tooltip("This is a check button");
      }
      o->end();
    }
     {gnui::Group* o = new gnui::Group(270, 10, 90, 115);
      o->set_vertical();
      o->box(gnui::THIN_UP_BOX);
      o->tooltip("This is a group");
      o->begin();
       {gnui::Button* o = new gnui::Button(15, 10, 20, 20, "radio");
        o->type(gnui::Button::RADIO);
        o->align(gnui::ALIGN_RIGHT);
        o->tooltip("This the first button of the group");
      }
       {gnui::Button* o = new gnui::Button(15, 35, 20, 20, "radio");
        o->type(gnui::Button::RADIO);
        o->align(gnui::ALIGN_RIGHT);
        o->tooltip("This the second button of the group");
      }
       {gnui::Button* o = new gnui::Button(15, 60, 20, 20, "radio");
        o->type(gnui::Button::RADIO);
        o->align(gnui::ALIGN_RIGHT);
        o->tooltip("This the third button of the group");
      }
       {gnui::Button* o = new gnui::Button(15, 85, 20, 20, "radio");
        o->type(gnui::Button::RADIO);
        o->align(gnui::ALIGN_RIGHT);
        o->tooltip("This the fourth button of the group");
      }
      o->end();
    }
     {gnui::LightButton* o = ttlb = new gnui::LightButton(120, 230, 130, 30, "Show Tooltips");
      o->set_flag(gnui::STATE);
      o->callback((gnui::Callback*)cb_ttlb);
      o->tooltip("This button enables or disables tooltips");
    }
    o->end();
    o->resizable(o);
  }
  w->show(argc, argv);
  return  gnui::run();
}
