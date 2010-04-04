//
// "$Id$"
//
// Pixmap drawing code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/** \fn Fl_Pixmap::Fl_Pixmap(const char **data)
  The constructors create a new pixmap from the specified XPM data.*/

/** \fn Fl_Pixmap::Fl_Pixmap(const unsigned char * const *data)
  The constructors create a new pixmap from the specified XPM data.*/

/** \fn Fl_Pixmap::Fl_Pixmap(const unsigned char **data)
  The constructors create a new pixmap from the specified XPM data.*/

// Draws X pixmap data, keeping it stashed in a server pixmap so it
// redraws fast.

// See fl_draw_pixmap.cxx for code used to get the actual data into pixmap.
// Implemented without using the xpm library (which I can't use because
// it interferes with the color cube used by fl_draw_image).

#include <fltk3/run.h>
#include <fltk3/draw.h>
#include <fltk3/x.H>
#include <fltk3/Widget.h>
#include <fltk3/MenuItem.h>
#include <fltk3/Fl_Pixmap.H>

#include <stdio.h>
#include "flstring.h"
#include <ctype.h>

#ifdef WIN32
extern void fl_release_dc(HWND, HDC);      // located in Fl_win32.cxx
#endif

#ifdef __APPLE_QUARTZ__
extern Fl_Offscreen fl_create_offscreen_with_alpha(int w, int h);
#endif

extern uchar **fl_mask_bitmap; // used by fl_draw_pixmap.cxx to store mask
void fl_restore_clip(); // in fl_rect.cxx

void Fl_Pixmap::measure() {
  int W, H;

  // ignore empty or bad pixmap data:
  if (w()<0 && data()) {
    fl_measure_pixmap(data(), W, H);
    w(W); h(H);
  }
}

void Fl_Pixmap::draw(int XP, int YP, int WP, int HP, int cx, int cy) {
  if(fl_device->type() == fltk3::Device::postscript_device) {
    fl_device->draw(this, XP, YP, WP, HP, cx, cy);
    return;
    }
  // ignore empty or bad pixmap data:
  if (!data()) {
    draw_empty(XP, YP);
    return;
  }
  if (w()<0) measure();
  if (WP==-1) {
    WP = w();
    HP = h();
  }
  if (!w()) {
    draw_empty(XP, YP);
    return;
  }
  // account for current clip region (faster on Irix):
  int X,Y,W,H; fl_clip_box(XP,YP,WP,HP,X,Y,W,H);
  cx += X-XP; cy += Y-YP;
  // clip the box down to the size of image, quit if empty:
  if (cx < 0) {W += cx; X -= cx; cx = 0;}
  if (cx+W > w()) W = w()-cx;
  if (W <= 0) return;
  if (cy < 0) {H += cy; Y -= cy; cy = 0;}
  if (cy+H > h()) H = h()-cy;
  if (H <= 0) return;
  if (!id_) {
#ifdef __APPLE_QUARTZ__
    id_ = fl_create_offscreen_with_alpha(w(), h());
    fl_begin_offscreen((Fl_Offscreen)id_);
    fl_draw_pixmap(data(), 0, 0, fltk3::GREEN);
    fl_end_offscreen();
#else
    id_ = fl_create_offscreen(w(), h());
    fl_begin_offscreen((Fl_Offscreen)id_);
    uchar *bitmap = 0;
    fl_mask_bitmap = &bitmap;
    fl_draw_pixmap(data(), 0, 0, fltk3::BLACK);
    fl_mask_bitmap = 0;
    if (bitmap) {
      mask_ = fl_create_bitmask(w(), h(), bitmap);
      delete[] bitmap;
    }
    fl_end_offscreen();
#endif
  }

#if defined(USE_X11)
  if (mask_) {
    // I can't figure out how to combine a mask with existing region,
    // so cut the image down to a clipped rectangle:
    int nx, ny; fl_clip_box(X,Y,W,H,nx,ny,W,H);
    cx += nx-X; X = nx;
    cy += ny-Y; Y = ny;
    // make X use the bitmap as a mask:
    XSetClipMask(fl_display, fl_gc, mask_);
    int ox = X-cx; if (ox < 0) ox += w();
    int oy = Y-cy; if (oy < 0) oy += h();
    XSetClipOrigin(fl_display, fl_gc, X-cx, Y-cy);
  }
  fl_copy_offscreen(X, Y, W, H, id_, cx, cy);
  if (mask_) {
    // put the old clip region back
    XSetClipOrigin(fl_display, fl_gc, 0, 0);
    fl_restore_clip();
  }
#elif defined(WIN32)
  if (fl_device->type() == fltk3::Device::gdi_printer) {
    typedef BOOL (WINAPI* fl_transp_func)  (HDC,int,int,int,int,HDC,int,int,int,int,UINT);
    static HMODULE hMod = NULL;
    static fl_transp_func fl_TransparentBlt = NULL;
    if (!hMod) {
      hMod = LoadLibrary("MSIMG32.DLL");
      if(hMod) fl_TransparentBlt = (fl_transp_func)GetProcAddress(hMod, "TransparentBlt");
      }
    if (hMod) {
#     define UNLIKELY_RGB_COLOR 2,3,4 // a nearly black color unlikely to occur in pixmaps
#     define WIN_COLOR RGB(2,3,4)
      Fl_Offscreen tmp_id = fl_create_offscreen(w(), h());
      fl_begin_offscreen(tmp_id);
      uchar *bitmap = 0;
      fl_mask_bitmap = &bitmap;
      // draw pixmap to offscreen using the unlikely color for background
      fl_draw_pixmap(data(), 0, 0, fl_rgb_color(UNLIKELY_RGB_COLOR) ); 
      fl_end_offscreen();
      HDC new_gc = CreateCompatibleDC(fl_gc);
      int save = SaveDC(new_gc);
      SelectObject(new_gc, (void*)tmp_id);
      // print all of offscreen but its parts using unlikely color
      fl_TransparentBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, w(), h(), WIN_COLOR );
      RestoreDC(new_gc,save);
      // This is an approximate algorithm that fails to print pixmap pixels that would use the unlikely color.
      // It can be transformed into an exact algorithm by adding the following commented out statements
      // that print pixmap one more time hiding another color (any color would fit)
      /*
#     define UNLIKELY_RGB_COLOR2 4,3,2
#     define WIN_COLOR2 RGB(4,3,2)
      {
	fl_begin_offscreen(tmp_id);
	fl_draw_pixmap(data(), 0, 0, fl_rgb_color(UNLIKELY_RGB_COLOR2) );
	fl_end_offscreen();
      }
      save = SaveDC(new_gc);
      SelectObject(new_gc, (void*)tmp_id);
      fl_TransparentBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, w(), h(), WIN_COLOR2 );
      RestoreDC(new_gc,save);
      */
      DeleteDC(new_gc);
      fl_delete_offscreen(tmp_id);
    }
    else {
      fl_copy_offscreen(X, Y, W, H, (Fl_Offscreen)id_, cx, cy);
    }
  }
  else if (mask_) {
    HDC new_gc = CreateCompatibleDC(fl_gc);
    int save = SaveDC(new_gc);
    SelectObject(new_gc, (void*)mask_);
    BitBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, SRCAND);
    SelectObject(new_gc, (void*)id_);
    BitBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, SRCPAINT);
    RestoreDC(new_gc,save);
    DeleteDC(new_gc);
  } else {
    fl_copy_offscreen(X, Y, W, H, (Fl_Offscreen)id_, cx, cy);
  }
#elif defined(__APPLE_QUARTZ__)
  fl_copy_offscreen(X, Y, W, H, (Fl_Offscreen)id_, cx, cy);
#else
# error unsupported platform
#endif
}

/**
  The destructor free all memory and server resources that are used by
  the pixmap.
*/
Fl_Pixmap::~Fl_Pixmap() {
  uncache();
  delete_data();
}

void Fl_Pixmap::uncache() {
  if (id_) {
    fl_delete_offscreen((Fl_Offscreen)id_);
    id_ = 0;
  }

  if (mask_) {
    fl_delete_bitmask((Fl_Bitmask)mask_);
    mask_ = 0;
  }
}

void Fl_Pixmap::label(fltk3::Widget* widget) {
  widget->image(this);
}

void Fl_Pixmap::label(fltk3::MenuItem* m) {
  fltk3::set_labeltype(fltk3::IMAGE_LABEL, labeltype, fltk3::Image::measure);
  m->label(fltk3::IMAGE_LABEL, (const char*)this);
}

void Fl_Pixmap::copy_data() {
  if (alloc_data) return;

  char		**new_data,	// New data array
		**new_row;	// Current row in image
  int		i,		// Looping var
		ncolors,	// Number of colors in image
		chars_per_pixel,// Characters per color
		chars_per_line;	// Characters per line 

  // Figure out how many colors there are, and how big they are...
  sscanf(data()[0],"%*d%*d%d%d", &ncolors, &chars_per_pixel);
  chars_per_line = chars_per_pixel * w() + 1;

  // Allocate memory for the new array...
  if (ncolors < 0) new_data = new char *[h() + 2];
  else new_data = new char *[h() + ncolors + 1];

  new_data[0] = new char[strlen(data()[0]) + 1];
  strcpy(new_data[0], data()[0]);

  // Copy colors...
  if (ncolors < 0) {
    // Copy FLTK colormap values...
    ncolors = -ncolors;
    new_row = new_data + 1;
    *new_row = new char[ncolors * 4];
    memcpy(*new_row, data()[1], ncolors * 4);
    ncolors = 1;
    new_row ++;
  } else {
    // Copy standard XPM colormap values...
    for (i = 0, new_row = new_data + 1; i < ncolors; i ++, new_row ++) {
      *new_row = new char[strlen(data()[i + 1]) + 1];
      strcpy(*new_row, data()[i + 1]);
    }
  }

  // Copy image data...
  for (i = 0; i < h(); i ++, new_row ++) {
    *new_row = new char[chars_per_line];
    memcpy(*new_row, data()[i + ncolors + 1], chars_per_line);
  }

  // Update pointers...
  data((const char **)new_data, h() + ncolors + 1);
  alloc_data = 1;  
}

fltk3::Image *Fl_Pixmap::copy(int W, int H) {
  Fl_Pixmap	*new_image;	// New pixmap

  // Optimize the simple copy where the width and height are the same...
  if (W == w() && H == h()) {
    // Make an exact copy of the image and return it...
    new_image = new Fl_Pixmap(data());
    new_image->copy_data();
    return new_image;
  }
  if (W <= 0 || H <= 0) return 0;

  // OK, need to resize the image data; allocate memory and 
  char		**new_data,	// New array for image data
		**new_row,	// Pointer to row in image data
		*new_ptr,	// Pointer into new array
		new_info[255];	// New information line
  const char	*old_ptr;	// Pointer into old array
  int		i,		// Looping var
		c,		// Channel number
		sy,		// Source coordinate
		dx, dy,		// Destination coordinates
		xerr, yerr,	// X & Y errors
		xmod, ymod,	// X & Y moduli
		xstep, ystep;	// X & Y step increments
  int		ncolors,	// Number of colors in image
		chars_per_pixel,// Characters per color
		chars_per_line;	// Characters per line 

  // Figure out how many colors there are, and how big they are...
  sscanf(data()[0],"%*d%*d%d%d", &ncolors, &chars_per_pixel);
  chars_per_line = chars_per_pixel * W + 1;

  sprintf(new_info, "%d %d %d %d", W, H, ncolors, chars_per_pixel);

  // Figure out Bresenheim step/modulus values...
  xmod   = w() % W;
  xstep  = (w() / W) * chars_per_pixel;
  ymod   = h() % H;
  ystep  = h() / H;

  // Allocate memory for the new array...
  if (ncolors < 0) new_data = new char *[H + 2];
  else new_data = new char *[H + ncolors + 1];
  new_data[0] = new char[strlen(new_info) + 1];
  strcpy(new_data[0], new_info);

  // Copy colors...
  if (ncolors < 0) {
    // Copy FLTK colormap values...
    ncolors = -ncolors;
    new_row = new_data + 1;
    *new_row = new char[ncolors * 4];
    memcpy(*new_row, data()[1], ncolors * 4);
    ncolors = 1;
    new_row ++;
  } else {
    // Copy standard XPM colormap values...
    for (i = 0, new_row = new_data + 1; i < ncolors; i ++, new_row ++) {
      *new_row = new char[strlen(data()[i + 1]) + 1];
      strcpy(*new_row, data()[i + 1]);
    }
  }

  // Scale the image using a nearest-neighbor algorithm...
  for (dy = H, sy = 0, yerr = H; dy > 0; dy --, new_row ++) {
    *new_row = new char[chars_per_line];
    new_ptr  = *new_row;

    for (dx = W, xerr = W, old_ptr = data()[sy + ncolors + 1];
	 dx > 0;
	 dx --) {
      for (c = 0; c < chars_per_pixel; c ++) *new_ptr++ = old_ptr[c];

      old_ptr += xstep;
      xerr    -= xmod;

      if (xerr <= 0) {
	xerr    += W;
	old_ptr += chars_per_pixel;
      }
    }

    *new_ptr = '\0';
    sy       += ystep;
    yerr     -= ymod;
    if (yerr <= 0) {
      yerr += H;
      sy ++;
    }
  }

  new_image = new Fl_Pixmap((char*const*)new_data);
  new_image->alloc_data = 1;

  return new_image;
}

void Fl_Pixmap::color_average(fltk3::Color c, float i) {
  // Delete any existing pixmap/mask objects...
  uncache();

  // Allocate memory as needed...
  copy_data();

  // Get the color to blend with...
  uchar		r, g, b;
  unsigned	ia, ir, ig, ib;

  fltk3::get_color(c, r, g, b);
  if (i < 0.0f) i = 0.0f;
  else if (i > 1.0f) i = 1.0f;

  ia = (unsigned)(256 * i);
  ir = r * (256 - ia);
  ig = g * (256 - ia);
  ib = b * (256 - ia);

  // Update the colormap to do the blend...
  char		line[255];	// New colormap line
  int		color,		// Looping var
		ncolors,	// Number of colors in image
		chars_per_pixel;// Characters per color


  sscanf(data()[0],"%*d%*d%d%d", &ncolors, &chars_per_pixel);

  if (ncolors < 0) {
    // Update FLTK colormap...
    ncolors = -ncolors;
    uchar *cmap = (uchar *)(data()[1]);
    for (color = 0; color < ncolors; color ++, cmap += 4) {
      cmap[1] = (ia * cmap[1] + ir) >> 8;
      cmap[2] = (ia * cmap[2] + ig) >> 8;
      cmap[3] = (ia * cmap[3] + ib) >> 8;
    }
  } else {
    // Update standard XPM colormap...
    for (color = 0; color < ncolors; color ++) {
      // look for "c word", or last word if none:
      const char *p = data()[color + 1] + chars_per_pixel + 1;
      const char *previous_word = p;
      for (;;) {
	while (*p && isspace(*p)) p++;
	char what = *p++;
	while (*p && !isspace(*p)) p++;
	while (*p && isspace(*p)) p++;
	if (!*p) {p = previous_word; break;}
	if (what == 'c') break;
	previous_word = p;
	while (*p && !isspace(*p)) p++;
      }

      if (fl_parse_color(p, r, g, b)) {
        r = (ia * r + ir) >> 8;
        g = (ia * g + ig) >> 8;
        b = (ia * b + ib) >> 8;

        if (chars_per_pixel > 1) sprintf(line, "%c%c c #%02X%02X%02X",
	                                 data()[color + 1][0],
	                                 data()[color + 1][1], r, g, b);
        else sprintf(line, "%c c #%02X%02X%02X", data()[color + 1][0], r, g, b);

        delete[] (char *)data()[color + 1];
	((char **)data())[color + 1] = new char[strlen(line) + 1];
	strcpy((char *)data()[color + 1], line);
      }
    }
  }
}

void Fl_Pixmap::delete_data() {
  if (alloc_data) {
    for (int i = 0; i < count(); i ++) delete[] (char *)data()[i];
    delete[] (char **)data();
  }
}

void Fl_Pixmap::set_data(const char * const * p) {
  int	height,		// Number of lines in image
	ncolors;	// Number of colors in image

  if (p) {
    sscanf(p[0],"%*d%d%d", &height, &ncolors);
    if (ncolors < 0) data(p, height + 2);
    else data(p, height + ncolors + 1);
  }
}


void Fl_Pixmap::desaturate() {
  // Delete any existing pixmap/mask objects...
  uncache();

  // Allocate memory as needed...
  copy_data();

  // Update the colormap to grayscale...
  char		line[255];	// New colormap line
  int		i,		// Looping var
		ncolors,	// Number of colors in image
		chars_per_pixel;// Characters per color
  uchar		r, g, b;

  sscanf(data()[0],"%*d%*d%d%d", &ncolors, &chars_per_pixel);

  if (ncolors < 0) {
    // Update FLTK colormap...
    ncolors = -ncolors;
    uchar *cmap = (uchar *)(data()[1]);
    for (i = 0; i < ncolors; i ++, cmap += 4) {
      g = (uchar)((cmap[1] * 31 + cmap[2] * 61 + cmap[3] * 8) / 100);
      cmap[1] = cmap[2] = cmap[3] = g;
    }
  } else {
    // Update standard XPM colormap...
    for (i = 0; i < ncolors; i ++) {
      // look for "c word", or last word if none:
      const char *p = data()[i + 1] + chars_per_pixel + 1;
      const char *previous_word = p;
      for (;;) {
	while (*p && isspace(*p)) p++;
	char what = *p++;
	while (*p && !isspace(*p)) p++;
	while (*p && isspace(*p)) p++;
	if (!*p) {p = previous_word; break;}
	if (what == 'c') break;
	previous_word = p;
	while (*p && !isspace(*p)) p++;
      }

      if (fl_parse_color(p, r, g, b)) {
        g = (uchar)((r * 31 + g * 61 + b * 8) / 100);

        if (chars_per_pixel > 1) sprintf(line, "%c%c c #%02X%02X%02X", data()[i + 1][0],
	                                 data()[i + 1][1], g, g, g);
        else sprintf(line, "%c c #%02X%02X%02X", data()[i + 1][0], g, g, g);

        delete[] (char *)data()[i + 1];
	((char **)data())[i + 1] = new char[strlen(line) + 1];
	strcpy((char *)data()[i + 1], line);
      }
    }
  }
}

//
// End of "$Id$".
//
