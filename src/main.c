#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "img.h"
#include "to_text.h"
#include <stdlib.h>

void show(char *buffer, int width, int height) {
  for (int i = 0; i < height; i++) {
    fwrite(buffer + i * width, sizeof(char), width, stdout);
    fputs("\n", stdout);
  }
}

int main(void) {
  const char *file_name = "cool_img.jpg";
  printf("Loading file %s...\n", file_name);
  image img = load_image(file_name);
  image gray = to_gray_img(img);
  image resized = resize_image(gray, 64, 32);
  char *ascii = img_to_text(resized);

  // save_gray_image("GrayScale.png", gray);
  // save_gray_image("GrayScaleResized.png", resized);
  show(ascii, resized.width, resized.height);

  free_image(img);
  free_image(gray);
  free_image(resized);
  free(ascii);

  return 0;
}
