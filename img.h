#ifndef IMG_H_
#define IMG_H_
#include <stdlib.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

typedef struct {
  int width;
  int height;
  int channels;
  unsigned char* data;
} image;

image create_image(int width, int height, int channels, unsigned char* data) {
  return (image) {
    .width = width, 
    .height = height,
    .channels = channels,
    .data = data 
  };
}

image load_image(const char* path) {
  int width, height, channels;
  unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
 
  // Could not find data
  assert(data);

  return create_image(width, height, channels, data);;
}

image save_image(const char* path, image img) {
  stbi_write_png(path, img.width, img.height, img.channels, img.data, img.width * img.channels);
}

image save_gray_image(const char* path, image img) {
  // check if image is gray
  assert(img.channels == 1);
  unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char) * img.width * img.height * 3);

  for (int y = 0; y < img.height; y++) {
    for(int x = 0; x < img.width; x++) {
      new_data[(y * img.width + x) * 3 + 0] = img.data[y * img.width + x];
      new_data[(y * img.width + x) * 3 + 1] = img.data[y * img.width + x];
      new_data[(y * img.width + x) * 3 + 2] = img.data[y * img.width + x];
    }
  }

  stbi_write_png(path, img.width, img.height, 3, new_data, img.width * 3);
  free(new_data);
}

image resize_image(image img, int target_width, int target_height) {
  unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char) * target_width * target_height * img.channels);
  stbir_resize_uint8(img.data, img.width, img.height, 0,
                     new_data, target_width, target_height, 0, img.channels);
  return create_image(target_width, target_height, img.channels, new_data);
}

// converts an image to gray scale
image to_gray_img(image img) {
  unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char) * img.width * img.height);

  for (int y = 0; y < img.height; y++) {
    for (int x = 0; x < img.width; x++) {
      int sum = 0;
      for (int c = 0; c < img.channels; c++) {
        sum += img.data[y * img.width * img.channels + x * img.channels + c];
      }
      new_data[y * img.width + x] = (unsigned char)(sum / img.channels);
    }
  }

  return create_image(img.width, img.height, 1, new_data);
}

void free_image(image img) {
  stbi_image_free(img.data);
}

#endif // IMG_H_
