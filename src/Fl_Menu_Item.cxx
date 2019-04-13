//
// "$Id$"
//
// The obsolete MenuItem structure.  This code should not be used
// in new gnui programs.
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

#ifndef DOXYGEN
#include <FL/Fl_Menu_Item.H>
#include <gnui/Menu.h>
#include <gnui/Item.h>
#include <gnui/ItemGroup.h>
#include <gnui/Divider.h>

using namespace gnui;

int Fl_Menu_Item::size() const {
  const Fl_Menu_Item* m = this;
  int nest = 0;
  for (;;) {
    if (!m->text) {
      if (!nest) return (m-this+1);
      nest--;
    } else if (m->flags & FL_SUBMENU) {
      nest++;
    }
    m++;
  }
}

const Fl_Menu_Item* Fl_Menu_Item::next(int n) const {
  if (n < 0) return 0; // this is so selected==-1 returns NULL
  const Fl_Menu_Item* m = this;
  int nest = 0;
  while (n>0) {
    if (!m->text) {
      if (!nest) return m;
      nest--;
    } else if (m->flags & FL_SUBMENU) {
      nest++;
    }
    m++;
    if (!nest && !(m->flags & FL_MENU_INVISIBLE)) n--;
  }
  return m;
}

// Recursive function to create Items and add them to a group:

static const Fl_Menu_Item* add(Group* g, const Fl_Menu_Item* m,void* data) {
  Group* saved = Group::current();
  g->begin();
  while (m && m->text) {
    Widget* o;
    const Fl_Menu_Item* next = m+1;
    if (m->flags & (FL_SUBMENU | FL_SUBMENU_POINTER)) {
      ItemGroup* g = new ItemGroup(m->text); o = g;
      if (m->flags & FL_SUBMENU_POINTER) {
	add(g, (Fl_Menu_Item*)(m->user_data_), data);
      } else {
	next = add(g, next, data) + 1;
      }
    } else {
      o = new Item(m->text);
      o->shortcut(m->shortcut_);
      if (m->callback_) o->callback(m->callback_);
      o->user_data(data ? data : m->user_data_);
      if (m->flags & FL_MENU_RADIO) o->type(Item::RADIO);
      else if (m->flags & FL_MENU_TOGGLE) o->type(Item::TOGGLE);
    }
    if (m->labeltype_) o->labeltype(m->labeltype_);
    if (m->labelfont_) o->labelfont(m->labelfont_);
    if (m->labelsize_) o->labelsize((float)m->labelsize_);
    if (m->labelcolor_) o->labelcolor(m->labelcolor_);
    // Shift the old flags values over to where they are in gnui,
    // but also allow new gnui flag values (this was done so RAW_LABEL
    // could be put in there for flwm)
    o->set_flag(((m->flags<<8)&(INACTIVE|STATE|INVISIBLE))|(m->flags&~0x1ff));
    if (m->flags & FL_MENU_DIVIDER) new Divider();
    m = next;
  }
  Group::current(saved);
  return m;
}

void Fl_Menu_Item::add_to(Menu* menu, void* data) const {
  ::add(menu, this, data);
}

/* Emulate old popup and test-shortcut methods on Fl_Menu_Item arrays: */
#include <gnui/PopupMenu.h>
#include <gnui/events.h>

const Fl_Menu_Item*
Fl_Menu_Item::pulldown(int X, int Y, int W, int H,
		       const Fl_Menu_Item* picked,
		       const char* title) const
{
  Group::current(0);
  PopupMenu menu(0,0,0,0);
  add_to(&menu);
  //menu.user_data(data);
  if (picked) menu.value(picked-this);
  if (menu.Menu::popup(Rectangle(X, Y, W, H), title))
    return this + menu.value();
  return 0;
}

// Searches the array for a shortcut that matches the current event
// and returns it:
const Fl_Menu_Item*
Fl_Menu_Item::test_shortcut() const
{
  Group::current(0);
  Menu menu(0,0,0,0);
  add_to(&menu);
  //menu.user_data(data);
  if (menu.handle_shortcut()) return this + menu.value();
  return 0;
}

#endif // !DOXYGEN
