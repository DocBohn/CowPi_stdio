#include <CowPi_stdio.h>

// Arduino.h is implicitly included in the Arduino IDE but not in PlatformIO
#include <Arduino.h>

void setup(void) {
    cowpi_stdio_setup(9600);

    float f = 3.14f;
    long long n = 42;

#ifndef ARDUINO_RASPBERRY_PI_PICO
    printf("The default `printf` won't convert floating point values such as %f.\n", f);
#endif ARDUINO_RASPBERRY_PI_PICO
#ifdef __AVR__
    printf("If you need to print floats, use the additional build arguments\n");
    printf("        -Wl,-u,vfprintf -lprintf_flt -lm        (see the `extras/` directory)\n\n");
#else
    printf("\n");
#endif //__AVR__

    printf("Trying to print 64-bit integers such as %lld (which is more bits than we need)\n", n);
#ifdef __AVR__
    printf("will abort the output for that `printf` statement.\n");
#else
    printf("won't result in a conversion.\n");
#endif //__AVR__
}

void loop(void) {
}
