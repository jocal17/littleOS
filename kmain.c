#include "framebuffer.h"
#include "serial.h"

int main() {

    serial_init(COM1);
    fb_write("Input works.", 12);
    char *log = "Loggging works!";
    while(*log) {
        serial_write(COM1, *log++);
    }
    return 0;
}
