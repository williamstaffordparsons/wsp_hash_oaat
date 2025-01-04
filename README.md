# WSP-Hash-OAAT
© 2024 William Stafford Parsons

## About
WSP-Hash-OAAT is a tiny 32-bit OAAT hashing algorithm as a substantial improvement to 32-bit FNV-1a, Jenkin's OAAT, MicroOAAT and MurmurOAAT.

Read more [here](https://williamstaffordparsons.github.io/wsp-hash-oaat/).

## Example
``` c
#include <stdio.h>
#include "wsp_hash_oaat.h"

int main(void) {
  struct wsp_hash_oaat_s s;
  uint8_t input[8] = {'m', 'e', 's', 's', 'a', 'g', 'e', 0};
  unsigned char i = 0;

  while (i != 10) {
    i++;
    printf("All-at-once result %u is 0x%08x.\n", i, wsp_hash_oaat(8, input));
    input[7]++;
  }

  input[7] = 0;
  i = 0;

  while (i != 10) {
    i++;
    wsp_hash_oaat_initialize(&s);
    wsp_hash_oaat_transform(0, 8, input, &s);
    wsp_hash_oaat_finalize(&s);
    input[7]++;
    printf("Segmented result %u is 0x%08x.\n", i, s.mix);
  }

  return 0;
}
```
