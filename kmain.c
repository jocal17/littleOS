#include "framebuffer.h"
#include "gdt.h"
#include "serial.h"
#include "strings.h"

int main()
{

        gdt_init();
        serial_init(COM1);
        //fb_write("Input works!", 12);
        print("Printing works!", 'f');
        print("Logging works!", 's');
        //char *log = "Logging works!";
        //while (*log) {
        //    serial_write(COM1, *log++);
        //}

        return 0;
}
