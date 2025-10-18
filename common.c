#include "common.h"

void putchar(char ch);

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--) {
        *p++ = c;
    }
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t *) dst;
    const uint8_t *s = (const uint8_t *) src;
    while (n--) 
        *d++ = *s++;
    return dst;
}

char *strcpy(char *dst, const char *src) {
    char *d = dst;
    while (*src) 
        *d++ = *src++;
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            break;
        }
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; // skip current '%'
            switch (*fmt) {
                case '\0': // '%' at the end of the format string
                    putchar('%');
                    goto end;
                case '%': // print '%'
                    putchar('%');
                    break;
                case 's': { // print string
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': { // print integer in decimal 
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;
                    if (value < 0) {
                        putchar('-'); // 印出負號
                        magnitude = -magnitude; // Get 2's complement of value
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9) // 求 value 是十的幾次方，由 divisor 表示
                        divisor *= 10;

                    while (divisor > 0) { // 印出 value
                        putchar('0' + magnitude / divisor); // 印出 value 最左邊的數字
                        magnitude %= divisor;
                        divisor /= 10;
                    }

                    break;
                }
                case 'x': { // print integer in hexadecimal 
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                }
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }
end:
    va_end(vargs);
}

