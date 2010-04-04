//
// "$Id: Image.H 7273 2010-03-15 23:47:47Z AlbrechtS $"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   Image, fltk3::RGBImage classes . */

#ifndef Fltk3_Image_H
#  define Fltk3_Image_H

#  include "Enumerations.H"

namespace fltk3 {
  class Widget;
  struct MenuItem;
  struct Label;

/**
  Image is the base class used for caching and
  drawing all kinds of images in FLTK. This class keeps track of
  common image data such as the pixels, colormap, width, height,
  and depth. Virtual methods are used to provide type-specific
  image handling.</P>
  
  <P>Since the Image class does not support image
  drawing by itself, calling the draw() method results in
  a box with an X in it being drawn instead.
*/
class FL_EXPORT Image {
  int w_, h_, d_, ld_, count_;
  const char * const *data_;

  // Forbid use of copy contructor and assign operator
  Image & operator=(const Image &);
  Image(const Image &);

  protected:

  /**
    The first form of the w() method returns the current
    image width in pixels.</P>
    
    <P>The second form is a protected method that sets the current
    image width.
  */
  void w(int W) {w_ = W;}
  /**
    The first form of the h() method returns the current
    image height in pixels.</P>
    
    <P>The second form is a protected method that sets the current
    image height.
  */
  void h(int H) {h_ = H;}
  /**
    The first form of the d() method returns the current
    image depth. The return value will be 0 for bitmaps, 1 for
    pixmaps, and 1 to 4 for color images.</P>
    
    <P>The second form is a protected method that sets the current
    image depth.
  */
  void d(int D) {d_ = D;}
  /**    See int ld()  */
  void ld(int LD) {ld_ = LD;}
  /**    See const char * const *data()  */
  void data(const char * const *p, int c) {data_ = p; count_ = c;}
  void draw_empty(int X, int Y);

  static void labeltype(const fltk3::Label *lo, int lx, int ly, int lw, int lh, fltk3::Align la);
  static void measure(const fltk3::Label *lo, int &lw, int &lh);

  public:

  /** See void Image::w(int) */
  int w() const {return w_;}
  /** See void Image::h(int) */
  int h() const {return h_;}
  /**
    The first form of the d() method returns the current
    image depth. The return value will be 0 for bitmaps, 1 for
    pixmaps, and 1 to 4 for color images.</P>
    
    <P>The second form is a protected method that sets the current
    image depth.
  */
  int d() const {return d_;}
  /**
    The first form of the ld() method returns the current
    line data size in bytes. Line data is extra data that is included
    after each line of color image data and is normally not present.</P>
    
    <P>The second form is a protected method that sets the current
    line data size in bytes.
  */
  int ld() const {return ld_;}
  /**
    The count() method returns the number of data values
    associated with the image. The value will be 0 for images with
    no associated data, 1 for bitmap and color images, and greater
    than 2 for pixmap images.
  */
  int count() const {return count_;}
  /**
    The first form of the data() method returns a
    pointer to the current image data array. Use the
    count() method to find the size of the data array.</P>
    
    <P>The second form is a protected method that sets the current
    array pointer and count of pointers in the array.
  */
  const char * const *data() const {return data_;}
  
  /**
    The constructor creates an empty image with the specified
    width, height, and depth. The width and height are in pixels.
    The depth is 0 for bitmaps, 1 for pixmap (colormap) images, and
    1 to 4 for color images.
  */
  Image(int W, int H, int D) {w_ = W; h_ = H; d_ = D; ld_ = 0; count_ = 0; data_ = 0;}
  virtual ~Image();
  virtual Image *copy(int W, int H);
  /**
    The copy() method creates a copy of the specified
    image. If the width and height are provided, the image is
    resized to the specified size. The image should be deleted (or in
    the case of Fl_Shared_Image, released) when you are done
    with it.
  */
  Image *copy() { return copy(w(), h()); }
  virtual void color_average(fltk3::Color c, float i);
  /**
    The inactive() method calls
    color_average(fltk3::BACKGROUND_COLOR, 0.33f) to produce 
    an image that appears grayed out. <I>This method does not 
    alter the original image data.</I>
  */
  void inactive() { color_average(fltk3::GRAY, .33f); }
  virtual void desaturate();
  virtual void label(fltk3::Widget*w);
  virtual void label(fltk3::MenuItem*m);
  /**
    The draw() methods draw the image. This form specifies
    a bounding box for the image, with the origin
    (upper-lefthand corner) of the image offset by the cx
    and cy arguments.
  */
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0); // platform dependent
  /**
    The draw() methods draw the image. This form
    specifies the upper-lefthand corner of the image
  */
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);} // platform dependent
  virtual void uncache();
};

/**
  The fltk3::RGBImage class supports caching and drawing
  of full-color images with 1 to 4 channels of color information.
  Images with an even number of channels are assumed to contain
  alpha information, which is used to blend the image with the
  contents of the screen.</P>
  
  <P>fltk3::RGBImage is defined in
  &lt;fltk3/Image.H&gt;, however for compatibility reasons
  &lt;fltk3/fltk3::RGBImage.H&gt; should be included.
*/
class FL_EXPORT RGBImage : public Image {
  public:

  const uchar *array;
  int alloc_array; // Non-zero if array was allocated

  private:

#if defined(__APPLE__) || defined(WIN32)
  void *id_; // for internal use
  void *mask_; // for internal use (mask bitmap)
#else
  unsigned id_; // for internal use
  unsigned mask_; // for internal use (mask bitmap)
#endif // __APPLE__ || WIN32

  public:

/**  The constructor creates a new image from the specified data. */
  RGBImage(const uchar *bits, int W, int H, int D=3, int LD=0) :
    Image(W,H,D), array(bits), alloc_array(0), id_(0), mask_(0) {data((const char **)&array, 1); ld(LD);}
  virtual ~RGBImage();
  virtual Image *copy(int W, int H);
  Image *copy() { return copy(w(), h()); }
  virtual void color_average(fltk3::Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(fltk3::Widget*w);
  virtual void label(fltk3::MenuItem*m);
  virtual void uncache();
};

} // namespace fltk3

#endif // !Image_H

//
// End of "$Id: Image.H 7273 2010-03-15 23:47:47Z AlbrechtS $".
//
