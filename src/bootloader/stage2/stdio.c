#include "x86.h"
#include "stdio.h"

void cls(void) {
  x86_Video_ClearScreen();
}

void putc(char c) {
  x86_Video_WriteCharTeletype(c, 0);
}

void puts(const char *s) {
  while (*s) {
    putc(*s++);
  }
}

#define PRINTF_STATE_NORMAL           0
#define PRINTF_STATE_LENGTH           1
#define PRINTF_STATE_LENGTH_SHORT     2
#define PRINTF_STATE_LENGTH_LONG      3
#define PRINTF_STATE_SPEC             4

#define PRINTF_LENGTH_DEFAULT         0
#define PRINTF_LENGTH_SHORT_SHORT     1
#define PRINTF_LENGTH_SHORT           2
#define PRINTF_LENGTH_LONG            3
#define PRINTF_LENGTH_LONG_LONG       4

void _cdecl printf(const char *fmt, ...) {
  int* argp = (int*)&fmt + 1;

  int state   = PRINTF_STATE_NORMAL;
  int length  = PRINTF_LENGTH_DEFAULT;
  int radix   = 10;
  bool sign   = false;

  while (*fmt) {
    switch (state) {
      case PRINTF_STATE_NORMAL:
        switch (*fmt) {
          case '%': state = PRINTF_STATE_LENGTH;
                    break;
          default:  putc(*fmt);
                    break;
        }
        break;
      case PRINTF_STATE_LENGTH:
        switch (*fmt) {
          case 'h': length = PRINTF_LENGTH_SHORT;
                    state = PRINTF_STATE_LENGTH_SHORT;
                    break;
          case 'l': length = PRINTF_LENGTH_LONG;
                    state = PRINTF_STATE_LENGTH_LONG;
                    break;
          default:  goto PRINTF_STATE_SPEC_;
        }
        break;
      case PRINTF_STATE_LENGTH_SHORT:
        if (*fmt == 'h') {
          length = PRINTF_LENGTH_SHORT_SHORT;
          state = PRINTF_STATE_SPEC;
        } else {
          goto PRINTF_STATE_SPEC_;
        }
        break;
      case PRINTF_STATE_LENGTH_LONG:
        if (*fmt == 'l') {
          length = PRINTF_LENGTH_LONG_LONG;
          state = PRINTF_STATE_SPEC;
        } else {
          goto PRINTF_STATE_SPEC_;
        }
        break;
      case PRINTF_STATE_SPEC:
      PRINTF_STATE_SPEC_:
        switch (*fmt) {
          case 'c': putc(*argp++);
                    break;
          case 's': puts(*(char**)argp++);
                    break;
          case 'd':
          case 'i': radix = 10; sign = true;
                    argp = printf_number(argp, length, radix, sign);
                    break;
          case 'u': radix = 10; sign = false;
                    argp = printf_number(argp, length, radix, sign);
                    break;
          case 'X':
          case 'x':
          case 'p': radix = 16; sign = false;
                    argp = printf_number(argp, length, radix, sign);
                    break;
          case 'o': radix = 8; sign = false;
                    argp = printf_number(argp, length, radix, sign);
                    break;
          case '%': putc('%');
                    break;
          default:  break;
        }
        state = PRINTF_STATE_NORMAL;
        length = PRINTF_LENGTH_DEFAULT;
        radix = 10;
        sign = false;
        break;
    }
    fmt++;
  }
}

const char g_HexChars[] = "0123456789ABCDEF";

int* printf_number(int* argp, int length, int radix, bool sign) {
  char buffer[32];
  unsigned long long number;
  int number_sign = 1;
  int pos = 0;

  switch (length) {
    case PRINTF_LENGTH_SHORT_SHORT:
    case PRINTF_LENGTH_SHORT:
    case PRINTF_LENGTH_DEFAULT:
      if (sign) {
        int n = *argp;
        if (n < 0) {
          number_sign = -1;
          n = -n;
        }
        number = (unsigned long long)n;
      } else {
        number = *(unsigned int*)argp;
      }
      argp++;
      break;
    case PRINTF_LENGTH_LONG:
      if (sign) {
        long int n = *(long int*)argp;
        if (n < 0) {
          number_sign = -1;
          n = -n;
        }
        number = (unsigned long long)n;
      } else {
        number = *(unsigned long int*)argp;
      }
      argp += 2;
      break;
    case PRINTF_LENGTH_LONG_LONG:
      if (sign) {
        long long int n = *(long long int*)argp;
        if (n < 0) {
          number_sign = -1;
          n = -n;
        }
        number = (unsigned long long)n;
      } else {
        number = *(unsigned long long*)argp;
      }
      argp += 4;
      break;
  }

  do {
    uint32_t rem;
    x86_div64_32(number, radix, &number, &rem);
    buffer[pos++] = g_HexChars[rem];
  } while (number > 0);

  if (sign && number_sign < 0) {
    buffer[pos++] = '-';
  }

  while (--pos >= 0) {
    putc(buffer[pos]);
  }

  return argp;
}

char getc(void) {
  return x86_Video_ReadCharTeletype(0);
}

char* gets(char* s, int n) {
  char* p = s;
  while (--n > 0) {
    char c = getc();
    if (c == '\r') {
      break;
    }
    *p++ = c;
  }
  *p = '\0';
  return s;
}

char* fgets(char* s, int size) {
  char* p = s;
  while (--size > 0) {
    char c = getc();
    if (c == '\r') {
      break;
    }
    *p++ = c;
  }
  *p = '\0';
  return s;
}