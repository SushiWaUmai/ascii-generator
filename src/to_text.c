#include "./to_text.h"

const char *table = ",.\"~!+:vcIow0XP$#RB@";
const int table_length = 20;

int get_index_from_pixel(unsigned char pixel) {
  int chunk = 256 / table_length;

  for (int i = 0; i < table_length; i++) {
    if (pixel < i * chunk) {
      return i;
    }
  }

  return 0;
}

char *img_to_text(image img) {
  // The Image must be in gray scale
  assert(img.channels == 1);

  char *text = (char *)malloc(sizeof(char) * img.width * img.height);

  for (int y = 0; y < img.height; y++) {
    for (int x = 0; x < img.width; x++) {
      unsigned char data = img.data[y * img.width + x];
      int index = get_index_from_pixel(data);
      text[y * img.width + x] = table[index];
    }
  }

  return text;
}
