//
// "$Id$"
//
// GLUT emulation header file for the Fast Light Tool Kit (FLTK).
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
//     http://www.gnui.org/str.php
//

// Emulation of GLUT using gnui.

// GLUT is Copyright (c) Mark J. Kilgard, 1994, 1995, 1996:
// "This program is freely distributable without licensing fees  and is
// provided without guarantee or warrantee expressed or  implied. This
// program is -not- in the public domain."

// Although I have copied the GLUT API, none of my code is based on
// any GLUT implementation details and is therefore covered by the LGPL.

// FLTK does not include the GLUT drawing functions (such as
// glutWireTeapot()) or the stroke fonts but the declarations for the
// drawing functions are included here because otherwise there is no
// way to get them along with this.  To use them you will have to
// link in the original GLUT library, put -lglut *after* -lgnui.

// Commented out lines indicate parts of GLUT that are not emulated.

#ifndef __glut_h__
#  define __glut_h__

#  include "gl.h"

////////////////////////////////////////////////////////////////
// GLUT is emulated using this window class and these static variables
// (plus several more static variables hidden in glut.C):

#  include <gnui/run.h>
#  include <gnui/events.h>
#  include <gnui/GlWindow.h>
#  include <gnui/Cursor.h>
#  include <gnui/visual.h>

namespace gnui {
	
	class GNUI_GLUT_API GlutWindow : public gnui::GlWindow {
	  void _init();
	  int mouse_down;
	protected:
	  void draw();
	  void draw_overlay();
	  int handle(int);
	public: // so the inline functions work
	  int number;
	  int menu[3];
	  void make_current();
	  void (*display)();
	  void (*overlaydisplay)();
	  void (*reshape)(int w, int h);
	  void (*keyboard)(uchar, int x, int y);
	  void (*mouse)(int b, int state, int x, int y);
	  void (*motion)(int x, int y);
	  void (*passivemotion)(int x, int y);
	  void (*entry)(int);
	  void (*visibility)(int);
	  void (*special)(int, int x, int y);
	  GlutWindow(int w, int h, const char *);
	  GlutWindow(int x, int y, int w, int h, const char *);
	  ~GlutWindow();
	};
}

extern GNUI_GLUT_API gnui::GlutWindow *glut_window;	// the current window
extern GNUI_GLUT_API int glut_menu;			// the current menu

// function pointers that are not per-window:
extern GNUI_GLUT_API void (*glut_idle_function)();
extern GNUI_GLUT_API void (*glut_menustate_function)(int);
extern GNUI_GLUT_API void (*glut_menustatus_function)(int,int,int);

////////////////////////////////////////////////////////////////

//#  define GLUT_API_VERSION This does not match any version of GLUT exactly...

GNUI_GLUT_API void glutInit(int *argcp, char **argv); // creates first window

GNUI_GLUT_API void glutInitDisplayMode(unsigned int mode);
enum {
  GLUT_RGB	= gnui::RGB_COLOR,
  GLUT_RGBA	= gnui::RGB_COLOR,
  GLUT_INDEX	= gnui::INDEXED_COLOR,
  GLUT_SINGLE	= gnui::SINGLE_BUFFER,
  GLUT_DOUBLE	= gnui::DOUBLE_BUFFER,
  GLUT_ACCUM	= gnui::ACCUM_BUFFER,
  GLUT_ALPHA	= gnui::ALPHA_BUFFER,
  GLUT_DEPTH	= gnui::DEPTH_BUFFER,
  GLUT_STENCIL	= gnui::STENCIL_BUFFER,
  GLUT_MULTISAMPLE = gnui::MULTISAMPLE,
  GLUT_STEREO	= gnui::STEREO
//GLUT_LUMINANCE = 512
};

GNUI_GLUT_API void glutInitWindowPosition(int x, int y);

GNUI_GLUT_API void glutInitWindowSize(int w, int h);

GNUI_GLUT_API void glutMainLoop();

GNUI_GLUT_API int glutCreateWindow(const char *title);

GNUI_GLUT_API int glutCreateSubWindow(int win, int x, int y, int width, int height);

GNUI_GLUT_API void glutDestroyWindow(int win);

inline void glutPostRedisplay() {glut_window->redraw();}

GNUI_GLUT_API void glutPostWindowRedisplay(int win);

GNUI_GLUT_API void glutSwapBuffers();

inline int glutGetWindow() {return glut_window->number;}

GNUI_GLUT_API void glutSetWindow(int win);

inline void glutSetWindowTitle(const char *t) {glut_window->label(t);}

inline void glutSetIconTitle(const char *t) {glut_window->iconlabel(t);}

inline void glutPositionWindow(int x, int y) {glut_window->position(x,y);}

inline void glutReshapeWindow(int w, int h) {glut_window->resize(w,h);}

inline void glutPopWindow() {glut_window->show();}

//inline void glutPushWindow();

inline void glutIconifyWindow() {glut_window->iconize();}

inline void glutShowWindow() {glut_window->show();}

inline void glutHideWindow() {glut_window->hide();}

inline void glutFullScreen() {glut_window->fullscreen();}

inline void glutSetCursor(gnui::Cursor* cursor) {glut_window->cursor(cursor);}
// notice that the numeric values are different than glut:

//#define GLUT_CURSOR_RIGHT_ARROW
//#define GLUT_CURSOR_LEFT_ARROW
#define GLUT_CURSOR_INFO	gnui::CURSOR_HAND
//#define GLUT_CURSOR_DESTROY
#define GLUT_CURSOR_HELP	gnui::CURSOR_HELP
//#define GLUT_CURSOR_CYCLE
//#define GLUT_CURSOR_SPRAY
#define GLUT_CURSOR_WAIT	gnui::CURSOR_WAIT
#define GLUT_CURSOR_TEXT	gnui::CURSOR_INSERT
#define GLUT_CURSOR_CROSSHAIR	gnui::CURSOR_CROSS
#define GLUT_CURSOR_UP_DOWN	gnui::CURSOR_NS
#define GLUT_CURSOR_TOP_SIDE	gnui::CURSOR_NS
#define GLUT_CURSOR_BOTTOM_SIDE	gnui::CURSOR_NS
#define GLUT_CURSOR_LEFT_RIGHT	gnui::CURSOR_WE
#define GLUT_CURSOR_LEFT_SIDE	gnui::CURSOR_WE
#define GLUT_CURSOR_RIGHT_SIDE	gnui::CURSOR_WE
#define GLUT_CURSOR_TOP_LEFT_CORNER	gnui::CURSOR_NWSE
#define GLUT_CURSOR_TOP_RIGHT_CORNER	gnui::CURSOR_NESW
#define GLUT_CURSOR_BOTTOM_RIGHT_CORNER	gnui::CURSOR_NWSE
#define GLUT_CURSOR_BOTTOM_LEFT_CORNER	gnui::CURSOR_NESW
#define GLUT_CURSOR_INHERIT		gnui::CURSOR_DEFAULT
#define GLUT_CURSOR_NONE		gnui::CURSOR_NONE
#define GLUT_CURSOR_FULL_CROSSHAIR	gnui::CURSOR_CROSS
//inline void glutWarpPointer(int x, int y);

inline void glutEstablishOverlay() {glut_window->make_overlay_current();}

inline void glutRemoveOverlay() {glut_window->hide_overlay();}

inline void glutUseLayer(GLenum layer) {
  layer ? glut_window->make_overlay_current() : glut_window->make_current();}
enum {GLUT_NORMAL, GLUT_OVERLAY};

inline void glutPostOverlayRedisplay() {glut_window->redraw_overlay();}

inline void glutShowOverlay() {glut_window->redraw_overlay();}

inline void glutHideOverlay() {glut_window->hide_overlay();}

GNUI_GLUT_API int glutCreateMenu(void (*)(int));

GNUI_GLUT_API void glutDestroyMenu(int menu);

inline int glutGetMenu() {return glut_menu;}

inline void glutSetMenu(int m) {glut_menu = m;}

GNUI_GLUT_API void glutAddMenuEntry(const char *label, int value);

GNUI_GLUT_API void glutAddSubMenu(const char *label, int submenu);

GNUI_GLUT_API void glutChangeToMenuEntry(int item, const char *label, int value);

GNUI_GLUT_API void glutChangeToSubMenu(int item, const char *label, int submenu);

GNUI_GLUT_API void glutRemoveMenuItem(int item);

inline void glutAttachMenu(int b) {glut_window->menu[b] = glut_menu;}

inline void glutDetachMenu(int b) {glut_window->menu[b] = 0;}

inline void glutDisplayFunc(void (*f)()) {glut_window->display = f;}

inline void glutReshapeFunc(void (*f)(int w, int h)) {glut_window->reshape=f;}

inline void glutKeyboardFunc(void (*f)(uchar key, int x, int y)) {
  glut_window->keyboard = f;}

inline void glutMouseFunc(void (*f)(int b, int state, int x, int y)) {
  glut_window->mouse = f;}
enum {
  GLUT_LEFT_BUTTON	= 0,
  GLUT_MIDDLE_BUTTON	= 1,
  GLUT_RIGHT_BUTTON	= 2,
  GLUT_DOWN		= 0,
  GLUT_UP		= 1
};

inline void glutMotionFunc(void (*f)(int x, int y)) {glut_window->motion= f;}

inline void glutPassiveMotionFunc(void (*f)(int x, int y)) {
  glut_window->passivemotion= f;}

inline void glutEntryFunc(void (*f)(int s)) {glut_window->entry = f;}
enum {GLUT_LEFT, GLUT_ENTERED};

inline void glutVisibilityFunc(void (*f)(int s)) {glut_window->visibility=f;}
enum {GLUT_NOT_VISIBLE, GLUT_VISIBLE};

GNUI_GLUT_API void glutIdleFunc(void (*f)());

// Warning: this cast may not work on all machines:
inline void glutTimerFunc(unsigned int msec, void (*f)(int), int value) {
  gnui::add_timeout(msec*.001f, (gnui::TimeoutHandler)f, (void *)value);
}

inline void glutMenuStateFunc(void (*f)(int state)) {
  glut_menustate_function = f;}

inline void glutMenuStatusFunc(void (*f)(int status, int x, int y)) {
  glut_menustatus_function = f;}
enum {GLUT_MENU_NOT_IN_USE, GLUT_MENU_IN_USE};

inline void glutSpecialFunc(void (*f)(int key, int x, int y)) {
  glut_window->special = f;}
enum {
  GLUT_KEY_F1		= 1,
  GLUT_KEY_F2		= 2,
  GLUT_KEY_F3		= 3,
  GLUT_KEY_F4		= 4,
  GLUT_KEY_F5		= 5,
  GLUT_KEY_F6		= 6,
  GLUT_KEY_F7		= 7,
  GLUT_KEY_F8		= 8,
  GLUT_KEY_F9		= 9,
  GLUT_KEY_F10		= 10,
  GLUT_KEY_F11		= 11,
  GLUT_KEY_F12		= 12,
// WARNING: Different values than Glut uses:
  GLUT_KEY_LEFT		= gnui::LeftKey,
  GLUT_KEY_UP		= gnui::UpKey,
  GLUT_KEY_RIGHT	= gnui::RightKey,
  GLUT_KEY_DOWN		= gnui::DownKey,
  GLUT_KEY_PAGE_UP	= gnui::PageUpKey,
  GLUT_KEY_PAGE_DOWN	= gnui::PageDownKey,
  GLUT_KEY_HOME		= gnui::HomeKey,
  GLUT_KEY_END		= gnui::EndKey,
  GLUT_KEY_INSERT	= gnui::InsertKey
};
//inline void glutSpaceballMotionFunc(void (*)(int x, int y, int z));

//inline void glutSpaceballRotateFunc(void (*)(int x, int y, int z));

//inline void glutSpaceballButtonFunc(void (*)(int button, int state));

//inline void glutButtonBoxFunc(void (*)(int button, int state));

//inline void glutDialsFunc(void (*)(int dial, int value));

//inline void glutTabletMotionFunc(void (*)(int x, int y));

//inline void glutTabletButtonFunc(void (*)(int button, int state, int x, int y));

inline void glutOverlayDisplayFunc(void (*f)()) {
  glut_window->overlaydisplay = f;}

//inline void glutWindowStatusFunc(void (*)(int state));
//enum {GLUT_HIDDEN, GLUT_FULLY_RETAINED, GLUT_PARTIALLY_RETAINED,
//	GLUT_FULLY_COVERED};

//inline void glutSetColor(int, GLfloat red, GLfloat green, GLfloat blue);

//inline GLfloat glutGetColor(int ndx, int component);
//#define GLUT_RED			0
//#define GLUT_GREEN			1
//#define GLUT_BLUE			2

//inline void glutCopyColormap(int win);

// Warning: values are changed from GLUT!
// Also relies on the GL_ symbols having values greater than 100
int glutGet(GLenum type);
enum {
  GLUT_RETURN_ZERO = 0,
  GLUT_WINDOW_X,
  GLUT_WINDOW_Y,
  GLUT_WINDOW_WIDTH,
  GLUT_WINDOW_HEIGHT,
  GLUT_WINDOW_PARENT,
//GLUT_WINDOW_NUM_CHILDREN,
//GLUT_WINDOW_CURSOR,
  GLUT_SCREEN_WIDTH,
  GLUT_SCREEN_HEIGHT,
//GLUT_SCREEN_WIDTH_MM,
//GLUT_SCREEN_HEIGHT_MM,
  GLUT_MENU_NUM_ITEMS,
  GLUT_DISPLAY_MODE_POSSIBLE,
  GLUT_INIT_WINDOW_X,
  GLUT_INIT_WINDOW_Y,
  GLUT_INIT_WINDOW_WIDTH,
  GLUT_INIT_WINDOW_HEIGHT,
  GLUT_INIT_DISPLAY_MODE,
//GLUT_ELAPSED_TIME,
  GLUT_WINDOW_BUFFER_SIZE
};

#  define GLUT_WINDOW_STENCIL_SIZE	GL_STENCIL_BITS
#  define GLUT_WINDOW_DEPTH_SIZE	GL_DEPTH_BITS
#  define GLUT_WINDOW_RED_SIZE		GL_RED_BITS
#  define GLUT_WINDOW_GREEN_SIZE	GL_GREEN_BITS
#  define GLUT_WINDOW_BLUE_SIZE		GL_BLUE_BITS
#  define GLUT_WINDOW_ALPHA_SIZE	GL_ALPHA_BITS
#  define GLUT_WINDOW_ACCUM_RED_SIZE	GL_ACCUM_RED_BITS
#  define GLUT_WINDOW_ACCUM_GREEN_SIZE	GL_ACCUM_GREEN_BITS
#  define GLUT_WINDOW_ACCUM_BLUE_SIZE	GL_ACCUM_BLUE_BITS
#  define GLUT_WINDOW_ACCUM_ALPHA_SIZE	GL_ACCUM_ALPHA_BITS
#  define GLUT_WINDOW_DOUBLEBUFFER	GL_DOUBLEBUFFER
#  define GLUT_WINDOW_RGBA		GL_RGBA
#  define GLUT_WINDOW_COLORMAP_SIZE	GL_INDEX_BITS
#  ifdef GL_SAMPLES_SGIS
#    define GLUT_WINDOW_NUM_SAMPLES	GL_SAMPLES_SGIS
#  else
#    define GLUT_WINDOW_NUM_SAMPLES	GLUT_RETURN_ZERO
#  endif
#  define GLUT_WINDOW_STEREO		GL_STEREO

//int glutDeviceGet(GLenum type);
//#define GLUT_HAS_KEYBOARD		600
//#define GLUT_HAS_MOUSE		601
//#define GLUT_HAS_SPACEBALL		602
//#define GLUT_HAS_DIAL_AND_BUTTON_BOX	603
//#define GLUT_HAS_TABLET		604
//#define GLUT_NUM_MOUSE_BUTTONS	605
//#define GLUT_NUM_SPACEBALL_BUTTONS	606
//#define GLUT_NUM_BUTTON_BOX_BUTTONS	607
//#define GLUT_NUM_DIALS		608
//#define GLUT_NUM_TABLET_BUTTONS	609

// WARNING: these values are different than Glut uses:
enum {
  GLUT_ACTIVE_SHIFT	= gnui::SHIFT,
  GLUT_ACTIVE_CTRL	= gnui::CTRL,
  GLUT_ACTIVE_ALT	= gnui::ALT
};
inline int glutGetModifiers() {return gnui::event_state() & (GLUT_ACTIVE_SHIFT | GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT);}

int glutLayerGet(GLenum);
#  define GLUT_OVERLAY_POSSIBLE		800
//#define GLUT_LAYER_IN_USE		801
//#define GLUT_HAS_OVERLAY		802
#  define GLUT_TRANSPARENT_INDEX		803
#  define GLUT_NORMAL_DAMAGED		804
#  define GLUT_OVERLAY_DAMAGED		805

//inline int glutVideoResizeGet(GLenum param);
//#define GLUT_VIDEO_RESIZE_POSSIBLE	900
//#define GLUT_VIDEO_RESIZE_IN_USE	901
//#define GLUT_VIDEO_RESIZE_X_DELTA	902
//#define GLUT_VIDEO_RESIZE_Y_DELTA	903
//#define GLUT_VIDEO_RESIZE_WIDTH_DELTA	904
//#define GLUT_VIDEO_RESIZE_HEIGHT_DELTA 905
//#define GLUT_VIDEO_RESIZE_X		906
//#define GLUT_VIDEO_RESIZE_Y		907
//#define GLUT_VIDEO_RESIZE_WIDTH	908
//#define GLUT_VIDEO_RESIZE_HEIGHT	909

//inline void glutSetupVideoResizing();

//inline void glutStopVideoResizing();

//inline void glutVideoResize(int x, int y, int width, int height);

//inline void glutVideoPan(int x, int y, int width, int height);

////////////////////////////////////////////////////////////////
// Emulated GLUT drawing functions:

// Font argument must be a void* for compatability, so...
extern GNUI_GLUT_API struct Glut_Bitmap_Font {gnui::Font* font; int size;}
  glutBitmap9By15, glutBitmap8By13, glutBitmapTimesRoman10,
  glutBitmapTimesRoman24, glutBitmapHelvetica10, glutBitmapHelvetica12,
  glutBitmapHelvetica18;
#  define GLUT_BITMAP_9_BY_15             (&glutBitmap9By15)
#  define GLUT_BITMAP_8_BY_13             (&glutBitmap8By13)
#  define GLUT_BITMAP_TIMES_ROMAN_10      (&glutBitmapTimesRoman10)
#  define GLUT_BITMAP_TIMES_ROMAN_24      (&glutBitmapTimesRoman24)
#  define GLUT_BITMAP_HELVETICA_10        (&glutBitmapHelvetica10)
#  define GLUT_BITMAP_HELVETICA_12        (&glutBitmapHelvetica12)
#  define GLUT_BITMAP_HELVETICA_18        (&glutBitmapHelvetica18)

GNUI_GLUT_API void glutBitmapCharacter(void *font, int character);
GNUI_GLUT_API int glutBitmapWidth(void *font, int character);
GNUI_GLUT_API int glutBitmapLength(void *font, const unsigned char* string);

////////////////////////////////////////////////////////////////
// GLUT drawing functions.  These are NOT emulated but you can
// link in the glut library to get them.  This assumes the object
// files in GLUT remain as they currently are so that there are
// not symbol conflicts with the above.

extern "C" {

extern int APIENTRY glutExtensionSupported(char *name);

/* Stroke font constants (use these in GLUT program). */
#  ifdef WIN32
#    define GLUT_STROKE_ROMAN		((void*)0)
#    define GLUT_STROKE_MONO_ROMAN	((void*)1)
#  else
extern void *glutStrokeRoman;
#    define GLUT_STROKE_ROMAN		(&glutStrokeRoman)
extern void *glutStrokeMonoRoman;
#    define GLUT_STROKE_MONO_ROMAN	(&glutStrokeMonoRoman)
#  endif

/* GLUT font sub-API */
extern void APIENTRY glutStrokeCharacter(void *font, int character);
extern int APIENTRY glutStrokeWidth(void *font, int character);

/* GLUT pre-built models sub-API */
extern void APIENTRY glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
extern void APIENTRY glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
extern void APIENTRY glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
extern void APIENTRY glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
extern void APIENTRY glutWireCube(GLdouble size);
extern void APIENTRY glutSolidCube(GLdouble size);
extern void APIENTRY glutWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
extern void APIENTRY glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
extern void APIENTRY glutWireDodecahedron();
extern void APIENTRY glutSolidDodecahedron();
extern void APIENTRY glutWireTeapot(GLdouble size);
extern void APIENTRY glutSolidTeapot(GLdouble size);
extern void APIENTRY glutWireOctahedron();
extern void APIENTRY glutSolidOctahedron();
extern void APIENTRY glutWireTetrahedron();
extern void APIENTRY glutSolidTetrahedron();
extern void APIENTRY glutWireIcosahedron();
extern void APIENTRY glutSolidIcosahedron();

}

#endif                  /* !__glut_h__ */

//
// End of "$Id$".
//
