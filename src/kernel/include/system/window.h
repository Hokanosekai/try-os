#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <drivers/vesa.h>

typedef struct {
  vbe_info_t* info;
  vbe_mode_info_t* mode_info;
} window_t;

bool window_init(window_t* window,
                 const int width,
                 const int height,
                 const int bpp);

void window_clear(window_t* window, const uint32_t color);

void window_draw_pixel(window_t* window,
                       const int x,
                       const int y,
                       const uint32_t color);

void window_draw_line(window_t* window,
                      const int x1,
                      const int y1,
                      const int x2,
                      const int y2,
                      const uint32_t color);

void window_draw_rect(window_t* window,
                      const int x,
                      const int y,
                      const int width,
                      const int height,
                      const uint32_t color);

void window_draw_rect_fill(window_t* window,
                           const int x,
                           const int y,
                           const int width,
                           const int height,
                           const uint32_t color);

void window_draw_circle(window_t* window,
                        const int x,
                        const int y,
                        const int radius,
                        const uint32_t color);

void window_draw_circle_fill(window_t* window,
                             const int x,
                             const int y,
                             const int radius,
                             const uint32_t color);

void window_draw_triangle(window_t* window,
                          const int x1,
                          const int y1,
                          const int x2,
                          const int y2,
                          const int x3,
                          const int y3,
                          const uint32_t color);

void window_draw_triangle_fill(window_t* window,
                               const int x1,
                               const int y1,
                               const int x2,
                               const int y2,
                               const int x3,
                               const int y3,
                               const uint32_t color);

void window_draw_char(window_t* window,
                      const int x,
                      const int y,
                      const char c,
                      const uint32_t color);

void window_draw_string(window_t* window,
                        const int x,
                        const int y,
                        const char* str,
                        const uint32_t color);

#endif
