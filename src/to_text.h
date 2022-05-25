#ifndef TO_TEXT_H_
#define TO_TEXT_H_

#include "img.h"
#include <assert.h>

int get_index_from_pixel(unsigned char pixel);
char *img_to_text(image img);

#endif // TO_TEXT_H_
