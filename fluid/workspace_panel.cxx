//
// "$Id$"
//
// Workspace Panels for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2011 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

// generated by Fast Light User Interface Designer (fluid) version 3.0000

#include "workspace_panel.h"

void Fl_Environment_Choice::cb_pMenuAll_i(fltk3::Menu_*, void* v) {
  // this is what we want to set or clear, pEnv is what we currently have
unsigned int e = (int)(long)v;
// find a good logic for settting, clearing, and partial values
if ( (pEnv&e)==e ) {
  // if all bits in the menu are set, toggle the bits off
  pEnv = pEnv ^ e;
} else {
  // some bits don't match, so switch all bits on
  pEnv = pEnv | e;
}

update_all();

if (callback())
  do_callback();
}
void Fl_Environment_Choice::cb_pMenuAll(fltk3::Menu_* o, void* v) {
  ((Fl_Environment_Choice*)(o->parent()))->cb_pMenuAll_i(o,v);
}

fltk3::MenuItem Fl_Environment_Choice::menu_pEnvMenu[] = {
 {"All Environments", 0,  (fltk3::Callback*)Fl_Environment_Choice::cb_pMenuAll, (void*)(FL_ENV_ALL), 128, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Command Line", 0,  0, 0, 64, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"All", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_ALL_SHELL), 128, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Makefile (make, gmake)", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_MAKE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"CMake File (cmake)", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_CMAKE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"MS Windows", 0,  0, 0, 64, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"All", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_ALL_VC), 128, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"VisualC 6", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_VC6), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"VisualC 2008", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_VC2008), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"VisualC 2010", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_VC2010), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Apple OS X", 0,  0, 0, 64, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Xcode 3 && 4", 0,  (fltk3::Callback*)cb_pMenuAll, (void*)(FL_ENV_XC4), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};
fltk3::MenuItem* Fl_Environment_Choice::pMenuAll = Fl_Environment_Choice::menu_pEnvMenu + 0;
Fl_Environment_Choice::Fl_Environment_Choice(int X, int Y, int W, int H, const char *L)
  : fltk3::Group(0, 0, W, H, L) {
this->box(fltk3::FLAT_BOX);
this->color(fltk3::BACKGROUND_COLOR);
this->selection_color(fltk3::BACKGROUND_COLOR);
this->labeltype(fltk3::NO_LABEL);
this->labelfont(0);
this->labelsize(14);
this->labelcolor(fltk3::FOREGROUND_COLOR);
this->align(fltk3::Align(fltk3::ALIGN_TOP));
this->when(fltk3::WHEN_RELEASE);
{ pEnvMenu = new fltk3::MenuButton(0, 0, 200, 26, "- unknown -");
  pEnvMenu->labelsize(9);
  pEnvMenu->align(fltk3::Align(192));
  pEnvMenu->menu(menu_pEnvMenu);
} // fltk3::MenuButton* pEnvMenu
pEnvMenu->copy(menu_pEnvMenu);
fltk3::MenuItem *mi = (fltk3::MenuItem*)pEnvMenu->menu();
int level = 0;
while (mi->label()) {
  unsigned int me = (int)(long)mi->user_data();
  if (me) {
    fltk3::MultiLabel *ml = new fltk3::MultiLabel;
    ml->labela = (char*)&menu_none_pixmap;
    ml->labelb = mi->text;
    ml->typea = fltk3::IMAGE_LABEL;
    ml->typeb = fltk3::NORMAL_LABEL;
    ml->label( mi );  
  }
  if (mi->flags&fltk3::SUBMENU) level++;
  mi++;
  while (level && !mi->label()) {
    level--; 
    mi++;
  }
}
position(X, Y);
end();
}

void Fl_Environment_Choice::update_all() {
  // now update all menus
  unsigned int e = pEnv;
  fltk3::MenuItem *mi = (fltk3::MenuItem*)pEnvMenu->menu();
  int level = 0;
  while (mi->label()) {
    unsigned int me = (int)(long)mi->user_data();
    if (me) {
      fltk3::MultiLabel *ml = (fltk3::MultiLabel*)mi->label();
      if ( (me&e)==0 ) {
        ml->labela = (char*)&menu_none_pixmap;
      } else if ( (me&e)==me ) {
        ml->labela = (char*)&menu_all_pixmap;
      } else {
        ml->labela = (char*)&menu_multi_pixmap;
      }
    }
    if (mi->flags&fltk3::SUBMENU) level++;
    mi++;
    while (level && !mi->label()) {
      level--; 
      mi++;
    }
  }
  
  // update the text
  if (pEnv==FL_ENV_ALL) {
    pEnvMenu->label("- all -");
  } else if (pEnv==FL_ENV_NONE) {
    pEnvMenu->label("- none -");
  } else {
    char buf[1024]; buf[0] = 0;
    if (pEnv&FL_ENV_MAKE) strcat(buf, "make, ");
    if (pEnv&FL_ENV_CMAKE) strcat(buf, "cmake, ");
    if (pEnv&FL_ENV_VC6) strcat(buf, "VC6, ");
    if (pEnv&FL_ENV_VC2008) strcat(buf, "VC2008, ");
    if (pEnv&FL_ENV_VC2010) strcat(buf, "VC2010, ");
    if (pEnv&FL_ENV_XC4) strcat(buf, "Xcode3 && 4, ");
    int n = strlen(buf);
    if (n>2) buf[n-2] = 0;
    pEnvMenu->copy_label(buf);
  }
}

/**
   Set the environment flags
*/
void Fl_Environment_Choice::value(unsigned int v) {
  pEnv = v;
  update_all();
}

/**
   Get the environment flags
*/
unsigned int Fl_Environment_Choice::value() {
  return pEnv;
}
extern Fl_Panel *the_file_panel;

void file_panel_set_cb(fltk3::Widget*, void *v) {
  if (v == Fl_Panel::LOAD) {
    } else {
      fltk3::Widget*const* a = the_file_panel->array();
      for (int i=the_file_panel->children(); i--;) {
        fltk3::Widget* o = *a++;
        if (o->changed()) {
          o->do_callback();
          //if (haderror) return;
          o->clear_changed();
        }
      }
    }
}

fltk3::ScrollGroup *pScrollGroup=(fltk3::ScrollGroup *)0;

static void cb_(fltk3::PackedGroup* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  int i, n = o->children();
  for (i=0; i<n; i++) {
    o->child(i)->hide();
  }
  wSpacer->show();
  Fl_Panel::propagate_load(o, v);
  o->layout();
  // TODO: if the window grows taller than the screen height,
  // we can use the pScrollGroup to keep the entire panell accesible.
  o->window()->size(o->window()->w(), o->y()+o->h()+15+25+10);
  pScrollGroup->resize(o->x(), o->y(), o->w(), o->h());
  pCloseGroup->resize(o->x(), o->y()+o->h()+15, o->w(), pCloseGroup->h());
  o->window()->init_sizes();
  
  static char buf[1024];
  if (Fl_Panel::numselected != 1)
    sprintf(buf, "Workspace Properties (%d items)", Fl_Panel::numselected);
  else
    sprintf(buf, "%s Properties", Fl_Panel::current->name());
  the_file_panel->label(buf);
};
}

static void cb_1(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && !t->is_file()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_Name(fltk3::Input* o, void* v) {
  if (v == Fl_Panel::LOAD) {
    if (Fl_Panel::numselected != 1 || Fl_Panel::current==0) {
      o->static_value("<Multiple Values>");
      o->deactivate();
    } else {
      o->static_value(Fl_Panel::current->name());
      o->activate();
    }
  } else {
    if (Fl_Panel::numselected == 1) {
      Fl_Panel::current->name(o->value());
      if (o->changed()) set_modflag(1);
    }
  };
}

static void cb_2(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && t->is_target()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_Destination(fltk3::Input* o, void* v) {
  if (v == Fl_Panel::LOAD) {
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_target()) {
        o->value(((Fl_Target_Type*)t)->target_path());
      }
    }
  } else {
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_target()) {
        ((Fl_Target_Type*)t)->target_path(o->value());
      }
    }
    set_modflag(1);
  };
}

static void cb_3(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && t->is_file()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_File(fltk3::Input* o, void* v) {
  if (v == Fl_Panel::LOAD) {
    if (Fl_Panel::numselected != 1 || Fl_Panel::current_file()==0L) {
      o->static_value("<Multiple Values>");
      o->deactivate();
    } else {
      o->static_value(Fl_Panel::current_file()->filename());
      o->activate();
    }
  } else {
    if (Fl_Panel::numselected == 1) {
      Fl_Panel::current_file()->filename(o->value());
      if (o->changed()) set_modflag(1);
    }
  };
}

static void cb_4(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && t->is_file()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_Unknown(fltk3::MenuButton* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  } else {
    int mod = 0;
    const fltk3::MenuItem *mi = o->mvalue();
    int e = mi->argument();
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_file()) {
        if (((Fl_File_Type*)t)->filetype() != e) {
          if (e==FL_FILE_EXPLICIT)
            ((Fl_File_Type*)t)->set_default_type();
          else
            ((Fl_File_Type*)t)->filetype(e|FL_FILE_EXPLICIT);
          mod = 1;
        }
      }
    }
    if (mod) set_modflag(1);
  }
  
  char buf[64];
  Fl_File_Type *ff = Fl_Panel::current_file();
  if (ff) {
    unsigned int ft = ff->filetype();
    if (ft&FL_FILE_EXPLICIT) {
      strcpy(buf, "explicit - ");
    } else {
      strcpy(buf, "default - ");
    }
    ft = ft & 0x7fff;
    for (const fltk3::MenuItem *mi = o->menu(); ; mi++) {
      if (!mi->label()) {
        strcat(buf, "<unknown>");
        break;
      }
      if (mi->argument()==ft) {
        strcat(buf, mi->label());
        break;
      }
    }
    o->copy_label(buf);
  };
}

fltk3::MenuItem menu_Unknown[] = {
 {"Default", 0,  0, (void*)(FL_FILE_EXPLICIT), 128, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"C Source Code", 0,  0, (void*)(FL_FILE_C_SOURCE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"C Header", 0,  0, (void*)(FL_FILE_C_HEADER), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"C++ Source Code", 0,  0, (void*)(FL_FILE_CPP_SOURCE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"C++ Header", 0,  0, (void*)(FL_FILE_CPP_HEADER), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"ObjectiveC Source", 0,  0, (void*)(FL_FILE_OBJC_SOURCE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"ObjectiveC Header", 0,  0, (void*)(FL_FILE_OBJC_HEADER), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Text", 0,  0, (void*)(FL_FILE_TEXT), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Shell Script", 0,  0, (void*)(FL_FILE_TEXT_SCRIPT), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"OS X Framework", 0,  0, (void*)(FL_FILE_FRAMEWORK), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Library", 0,  0, (void*)(FL_FILE_LIBRARY), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Fluid UI Design", 0,  0, (void*)(FL_FILE_FLUID_UI), 128, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Unknown", 0,  0, (void*)(FL_FILE_UNKNOWN), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0}
};

static void cb_5(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && t->is_file()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_Relative(fltk3::MenuButton* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  /*...*/
  } else {
    int mod = 0;
    const fltk3::MenuItem *mi = o->mvalue();
    int e = mi->argument();
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_file()) {
        if (((Fl_File_Type*)t)->location() != e) {
          ((Fl_File_Type*)t)->location(e);
          mod = 1;
        }
      }
    }
    if (mod) set_modflag(1);
  }

  // FIXME: we should show <multiple values> if required
  Fl_File_Type *ff = Fl_Panel::current_file();
  if (ff) {
    unsigned int fl =ff->location();
    for (const fltk3::MenuItem *mi = o->menu(); ; mi++) {
      if (!mi->label()) break;
      if (mi->argument()==fl) {
        o->label(mi->label());
        break;
      }
    }
  };
}

fltk3::MenuItem menu_Relative[] = {
 {"Relative to Workspace", 0,  0, (void*)(FL_LOCATION_WORKSPACE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Absolute Path", 0,  0, (void*)(FL_LOCATION_ABSOLUTE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Relative to IDE", 0,  0, (void*)(FL_LOCATION_IDE), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {"Relative to SDK", 0,  0, (void*)(FL_LOCATION_SDK), 0, fltk3::NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0}
};

static void cb_6(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && t->is_tool() && !t->is_folder() && !t->is_category()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_Build(Fl_Environment_Choice* o, void* v) {
  if (v == Fl_Panel::LOAD) {
    o->value(Fl_Panel::current_tool()->build_env());
  } else {
    int mod = 0;
    unsigned int e = o->value();
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_tool()) {
        if (((Fl_Tool_Type*)t)->build_env() != e) {
          ((Fl_Tool_Type*)t)->build_env(e);
          mod = 1;
        }
      }
    }
    if (mod) set_modflag(1);
  };
}

static void cb_7(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && (t->is_file() || t->is_folder() || t->is_category())) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_List(Fl_Environment_Choice* o, void* v) {
  if (v == Fl_Panel::LOAD) {
    o->value(Fl_Panel::current_tool()->list_env());
  } else {
    int mod = 0;
    unsigned int e = o->value();
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_tool()) {
        if (((Fl_Tool_Type*)t)->list_env() != e) {
          ((Fl_Tool_Type*)t)->list_env(e);
          mod = 1;
        }
      }
    }
    if (mod) set_modflag(1);
  };
}

fltk3::Group *wSpacer=(fltk3::Group *)0;

static void cb_8(fltk3::Group* o, void* v) {
  if (v == Fl_Panel::LOAD) {
  for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
    if (t->selected && t->is_target()) {
      o->show();
      break;
    }
  }
  if (o->visible())
    Fl_Panel::propagate_load(o, v);
};
}

static void cb_Makefile(fltk3::Input* o, void* v) {
  if (v == Fl_Panel::LOAD) {
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_target()) {
        o->value(((Fl_Target_Type*)t)->makefile_path());
      }
    }
  } else {
    for (Fl_Type *t = Fl_Type::first; t; t = t->next) {
      if (t->selected && t->is_target()) {
        ((Fl_Target_Type*)t)->makefile_path(o->value());
      }
    }
    set_modflag(1);
  };
}

fltk3::Group *pCloseGroup=(fltk3::Group *)0;

static void cb_Close(fltk3::Button*, void* v) {
  if (v == Fl_Panel::LOAD) {
  } else {
    file_panel_set_cb(0, 0);
    the_file_panel->hide();
  };
}

Fl_Panel* make_file_panel() {
  Fl_Panel* w;
  { Fl_Panel* o = new Fl_Panel(0, 0, 420, 454, "File Properties");
    w = o;
    o->box(fltk3::FLAT_BOX);
    o->color(fltk3::BACKGROUND_COLOR);
    o->selection_color(fltk3::BACKGROUND_COLOR);
    o->labeltype(fltk3::NO_LABEL);
    o->labelfont(0);
    o->labelsize(11);
    o->labelcolor(fltk3::FOREGROUND_COLOR);
    o->align(fltk3::Align(fltk3::ALIGN_CLIP|fltk3::ALIGN_INSIDE));
    o->when(fltk3::WHEN_RELEASE);
    o->hotspot(o);
    { pScrollGroup = new fltk3::ScrollGroup(7, 10, 405, 400);
      pScrollGroup->box(fltk3::FLAT_BOX);
      pScrollGroup->color(fltk3::LIGHT1);
      pScrollGroup->callback((fltk3::Callback*)Fl_Panel::propagate_load);
      { fltk3::PackedGroup* o = new fltk3::PackedGroup(7, 10, 405, 400);
        o->callback((fltk3::Callback*)cb_);
        { fltk3::Group* o = new fltk3::Group(10, 10, 400, 30);
          o->labelsize(12);
          o->callback((fltk3::Callback*)cb_1);
          o->align(fltk3::Align(fltk3::ALIGN_LEFT));
          { fltk3::Input* o = new fltk3::Input(110, 15, 290, 20, "Name ");
            o->tooltip("name and path of the file");
            o->labelsize(12);
            o->textsize(12);
            o->callback((fltk3::Callback*)cb_Name);
            o->when(fltk3::WHEN_CHANGED);
            fltk3::Group::current()->resizable(o);
          } // fltk3::Input* o
          o->end();
        } // fltk3::Group* o
        { fltk3::Group* o = new fltk3::Group(12, 40, 400, 30);
          o->labelsize(12);
          o->callback((fltk3::Callback*)cb_2);
          o->align(fltk3::Align(fltk3::ALIGN_LEFT));
          { fltk3::Input* o = new fltk3::Input(112, 45, 290, 20, "Destination Path ");
            o->tooltip("name and path of the file");
            o->labelsize(12);
            o->textsize(12);
            o->callback((fltk3::Callback*)cb_Destination);
            o->when(fltk3::WHEN_CHANGED);
            fltk3::Group::current()->resizable(o);
          } // fltk3::Input* o
          o->end();
        } // fltk3::Group* o
        { fltk3::Group* o = new fltk3::Group(9, 99, 400, 30);
          o->labelsize(12);
          o->callback((fltk3::Callback*)cb_3);
          o->align(fltk3::Align(fltk3::ALIGN_LEFT));
          { fltk3::Input* o = new fltk3::Input(109, 104, 290, 20, "File Name ");
            o->tooltip("name and path of the file");
            o->labelsize(12);
            o->textsize(12);
            o->callback((fltk3::Callback*)cb_File);
            o->when(fltk3::WHEN_CHANGED);
            fltk3::Group::current()->resizable(o);
          } // fltk3::Input* o
          o->end();
        } // fltk3::Group* o
        { fltk3::Group* o = new fltk3::Group(8, 129, 400, 30);
          o->callback((fltk3::Callback*)cb_4);
          { fltk3::Group* o = new fltk3::Group(108, 134, 200, 20, "File Type ");
            o->labelsize(12);
            o->callback((fltk3::Callback*)Fl_Panel::propagate_load);
            o->align(fltk3::Align(fltk3::ALIGN_LEFT));
            { fltk3::MenuButton* o = new fltk3::MenuButton(108, 134, 200, 20, "Unknown");
              o->labelsize(12);
              o->callback((fltk3::Callback*)cb_Unknown);
              o->menu(menu_Unknown);
            } // fltk3::MenuButton* o
            o->end();
          } // fltk3::Group* o
          o->end();
        } // fltk3::Group* o
        { fltk3::Group* o = new fltk3::Group(8, 159, 400, 30);
          o->labelsize(12);
          o->callback((fltk3::Callback*)cb_5);
          o->align(fltk3::Align(fltk3::ALIGN_LEFT));
          { fltk3::Group* o = new fltk3::Group(108, 164, 200, 20, "Location ");
            o->labelsize(12);
            o->callback((fltk3::Callback*)Fl_Panel::propagate_load);
            o->align(fltk3::Align(fltk3::ALIGN_LEFT));
            { fltk3::MenuButton* o = new fltk3::MenuButton(108, 164, 200, 20, "Relative to Workspace");
              o->labelsize(12);
              o->callback((fltk3::Callback*)cb_Relative);
              o->menu(menu_Relative);
            } // fltk3::MenuButton* o
            o->end();
          } // fltk3::Group* o
          o->end();
        } // fltk3::Group* o
        { fltk3::Group* o = new fltk3::Group(8, 189, 400, 30);
          o->callback((fltk3::Callback*)cb_6);
          { Fl_Environment_Choice* o = new Fl_Environment_Choice(108, 192, 200, 26, "Build in ");
            o->box(fltk3::FLAT_BOX);
            o->color(fltk3::BACKGROUND_COLOR);
            o->selection_color(fltk3::SELECTION_COLOR);
            o->labeltype(fltk3::NORMAL_LABEL);
            o->labelfont(0);
            o->labelsize(12);
            o->labelcolor(fltk3::FOREGROUND_COLOR);
            o->callback((fltk3::Callback*)cb_Build);
            o->align(fltk3::Align(fltk3::ALIGN_LEFT));
            o->when(fltk3::WHEN_RELEASE_ALWAYS);
          } // Fl_Environment_Choice* o
          o->end();
        } // fltk3::Group* o
        { fltk3::Group* o = new fltk3::Group(8, 219, 400, 30);
          o->callback((fltk3::Callback*)cb_7);
          { Fl_Environment_Choice* o = new Fl_Environment_Choice(108, 224, 200, 25, "List in ");
            o->box(fltk3::FLAT_BOX);
            o->color(fltk3::BACKGROUND_COLOR);
            o->selection_color(fltk3::SELECTION_COLOR);
            o->labeltype(fltk3::NORMAL_LABEL);
            o->labelfont(0);
            o->labelsize(12);
            o->labelcolor(fltk3::FOREGROUND_COLOR);
            o->callback((fltk3::Callback*)cb_List);
            o->align(fltk3::Align(fltk3::ALIGN_LEFT));
            o->when(fltk3::WHEN_RELEASE_ALWAYS);
          } // Fl_Environment_Choice* o
          o->end();
        } // fltk3::Group* o
        { wSpacer = new fltk3::Group(10, 400, 400, 10);
          wSpacer->end();
        } // fltk3::Group* wSpacer
        { fltk3::Group* o = new fltk3::Group(7, 70, 400, 30);
          o->labelsize(12);
          o->callback((fltk3::Callback*)cb_8);
          o->align(fltk3::Align(fltk3::ALIGN_LEFT));
          { fltk3::Input* o = new fltk3::Input(107, 75, 290, 20, "Makefile Path ");
            o->labelsize(12);
            o->textsize(12);
            o->callback((fltk3::Callback*)cb_Makefile);
            o->when(fltk3::WHEN_CHANGED);
            fltk3::Group::current()->resizable(o);
          } // fltk3::Input* o
          o->end();
        } // fltk3::Group* o
        o->end();
        fltk3::Group::current()->resizable(o);
      } // fltk3::PackedGroup* o
      pScrollGroup->end();
      fltk3::Group::current()->resizable(pScrollGroup);
    } // fltk3::ScrollGroup* pScrollGroup
    { pCloseGroup = new fltk3::Group(10, 420, 400, 25);
      pCloseGroup->labelsize(11);
      pCloseGroup->callback((fltk3::Callback*)Fl_Panel::propagate_load);
      { fltk3::Box* o = new fltk3::Box(10, 420, 290, 25);
        o->labelsize(11);
        fltk3::Group::current()->resizable(o);
      } // fltk3::Box* o
      { fltk3::Button* o = new fltk3::Button(300, 420, 110, 25, "Close");
        o->callback((fltk3::Callback*)cb_Close);
      } // fltk3::Button* o
      pCloseGroup->end();
    } // fltk3::Group* pCloseGroup
    o->set_non_modal();
    o->end();
  } // Fl_Panel* o
  return w;
}

//
// End of "$Id$".
//