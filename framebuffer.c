/*
 * This file contains the code for printing to screen. FRAMEBUFFER contains the
 * address for the framebuffer: memory mapped I/O which is 32KB. Each 'page' is made up of
 * 80 (width) * 25(height) 16 bit cells. Each cell determines the character as well as the
 * background and foreground colors. The framebuffer also has two I/O ports for handling
 * the cursor position.
 */

#include "framebuffer.h"
#include "io.h"

static unsigned int cursor_pos = 0;
static unsigned int x_pos = 0;
static unsigned int y_pos = 0;

void fb_write_cell(unsigned int i, char c, unsigned char bg, unsigned char fg)
{
        volatile char* fb = (volatile char*)FRAMEBUFFER;
        fb[i * 2] = c;
        fb[i * 2 + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/*
 * This is the function for writing to the I/0 ports.
 * We can only write 8 of the 16 bits at a time so we
 * need to tell the command port which byte to expect.
 */
void fb_move_cursor(unsigned short pos)
{
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_advance_row()
{
        if (x_pos == 84)
                fb_advance_col();
        else
                x_pos++;

        cursor_pos = x_pos + (y_pos * 84);
        fb_move_cursor(cursor_pos);
}

void fb_advance_col()
{
        y_pos++;
        x_pos = 0;
        cursor_pos = x_pos + (y_pos * 84);
        fb_move_cursor(cursor_pos);
}

void fb_write(const char *buf, unsigned long len)
{
        char c;
        for (unsigned int i = 0; i < len; i++) {
                c = buf[i];
                fb_write_cell(i, c, BLACK, WHITE);
                fb_advance_row();
        }
}
