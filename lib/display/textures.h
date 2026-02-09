#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>

typedef enum {
  BRUSH,
  BRUSH_ICON,
  ERASER_ICON,
} Texture;

extern const uint8_t std_font[];
extern const uint8_t textures[][8];

#endif // TEXTURES_H
