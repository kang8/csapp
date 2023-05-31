#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;

  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }

  printf("\n");
}

void show_int(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }

void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }

void show_pointer(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

void test_show_bytes(int val) {
  int ival = val;
  float fval = (float)val;
  int *pval = &val;

  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}

/**
 * little endian output:
 *  39 30 00 00
 *  00 e4 40 46
 *  5c 3e fc 84 fc 7f 00 00 (randomly)
 *
 * big endian output:
 *  00 00 30 39
 *  46 40 e4 00
 *  1c 0c d0 1a ff 7f 00 00 (randomly)
 */
int main() {
  int val = 12345;
  test_show_bytes(val);
  return 0;
}
