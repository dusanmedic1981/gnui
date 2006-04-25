// "$Id$"
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

#include <config.h>
#include <fltk/rgbImage.h>
#include <fltk/events.h>
#include <fltk/draw.h>

using namespace fltk;

/*! \class fltk::rgbImage

  Draws an uncompressed array of pixel data.
  This can draw any style of pixel data that fltk::drawimage()
  can draw (ie monochrome, rgb, or rgba in various arrangements).

  You can create one of these directly from an image file, see
  SharedImage for details.

  When you draw() this image, the data is copied to a system-specific
  intermediate buffer. If you then change the data and want the
  displayed image to update, you should call redraw() so that it
  knows to update the system-specific buffer.

  Notice that this only saves time if draw() is called much more often
  than redraw(). If you are changing the image continuously (ie video
  playback) this is just a waste of the memory for the system-specific
  buffer and of the time needed to create and copy it, you should
  instead call drawimage(pixels(),pixeltype()) directly.

  Future systems may be smart enough to draw the data directly without
  an intermediate object. So don't rely on the visible image not
  changing until redraw() is called.
*/

/*! Implementation of Image::update() */
void rgbImage::update()
{
  GSave gsave;
  make_current();
  drawimage(pixels(), pixeltype(), fltk::Rectangle(w(),h()), linedelta_);
}

#if 0 //WRITE_JPEG

// This function should be somewhere else!
// For temporary purposes it is conditiallly compiled here for use in
// Digital Domain's programs, but not in the public fltk version:

extern "C" {
#  include <stdio.h>
#  include <jpeglib.h>
}

bool rgbImage::write_jpeg(const char *filename, int quality, int dpi)
{
  int wdt, hgt;
  measure( wdt, hgt );
  if (!w() || !h() || !data ) return false;
  if ( depth!=3 ) return false; // for now, we only write RGB images

  JSAMPLE *image_buffer = (unsigned char*)data;
  int image_height = hgt;
  int image_width = wdt;
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * outfile;
  JSAMPROW row_pointer[1];
  int row_stride;

  /* Step 1: allocate and initialize JPEG compression object */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return 0;
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* Step 3: set parameters for compression */
  cinfo.image_width = image_width;
  cinfo.image_height = image_height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);
  cinfo.density_unit = 1;
  cinfo.X_density = cinfo.Y_density = dpi;

  /* Step 4: Start compressor */
  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */
  row_stride = image_width * 3;
  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  fclose(outfile);

  /* Step 7: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);

  return true;
}

#endif // WRITE_JPEG

//
// End of "$Id$".
//
