#ifndef IMG_H_
#define IMG_H_

#include <stdlib.h>
#include <assert.h>

#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

typedef struct {
  int width;
  int height;
  int channels;
  unsigned char* data;
} image;

image create_image(int width, int height, int channels, unsigned char* data);
image load_image(const char* path);
void save_image(const char* path, image img);
void save_gray_image(const char* path, image img);
image resize_image(image img, int target_width, int target_height);
image to_gray_img(image img);
void free_image(image img);

#endif // IMG_H_
