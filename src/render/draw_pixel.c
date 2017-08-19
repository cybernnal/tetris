#include "tetris.h"

void draw_pixel(int x, int y, Uint32 color, t_window *w)
{
    if ((y > WIN_Y || x > WIN_X || x < 0 || y < 0)) {
        printf("x: %d, y: %d\n", x, y);
        return ;
    }
    w->img_ptr[WIN_X * y + x] = color;
}