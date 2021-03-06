/* ScummC
 * Copyright (C) 2004-2006  Alban Bedel
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

/**
 * @file scc_img.h
 * @ingroup utils
 * @brief Read/write image files
 *
 * A little lib to open image files. We are only intersted in
 * paletted format atm. Currently only uncompressed bmp is supported.
 *
 */

typedef struct scc_img {
  unsigned int w,h;
  unsigned int ncol,trans;
  unsigned int bpp;
  uint8_t* pal;    // NOTE: colors stored as BGR
  uint8_t* data;   // NOTE: either indexed(8bit), or stored as RGB
} scc_img_t;

/// Create a new empty image of the given size
scc_img_t* scc_img_new(int w,int h,int ncol,int bpp);

/// Destroy an image
void scc_img_free(scc_img_t* img);

/// Save an image as BMP using the given fd
int scc_img_write_bmp(scc_img_t* img,scc_fd_t* fd);

/// Save an image as BMP at the given path
int scc_img_save_bmp(scc_img_t* img,char* path);

/// Open an image. Only BMP is supported atm.
scc_img_t* scc_img_open(char* path);

/// Swap R and B channels
void scc_img_swapchannels(scc_img_t* img);

/// Remove palette from an image
void scc_img_unpal(scc_img_t* img);

/// Swap two color indexes
void scc_img_swapcol(scc_img_t* img, uint8_t src, uint8_t dest);

/// Copies alpha or transparency mask to dest
void scc_img_copymask(scc_img_t* img, scc_img_t* dest);

/// converts <32bpp to 32bpp with a mask
void scc_img_mask(scc_img_t* img);

/// Find pixel in image
int scc_img_findpixel(scc_img_t* img, int color, int* x, int* y);

/// Find color in palette
int scc_img_findpal(scc_img_t* img, int color);

/// Find palette indexes in room image
void scc_img_findpal_indexes(scc_img_t* costume_img, scc_img_t* room_img, uint8_t* indexes);

/// Reduce colors in image
int scc_img_quantize(scc_img_t* img, int colors);

/// Reduce colors across a set of images
int scc_images_quantize(scc_img_t** img, int num, int colors, int dump);

