# WSP-Hash-32
© 2024 William Stafford Parsons

## About
WSP-Hash-32 is a 32-bit hashing algorithm as a practical alternative to CityHash32 v1.1, 32-bit MurmurHash3, SipHash32 and XXHash32.

Read more [here](https://williamstaffordparsons.github.io/wsp-hash-32/).

## Example
``` c
#include <stdio.h>
#include "wsp_hash_32.h"

int main(void) {
  struct wsp_hash_32_s s;
  uint8_t input[8] = {'m', 'e', 's', 's', 'a', 'g', 'e', 0};
  unsigned char i = 0;

  while (i != 10) {
    i++;
    printf("All-at-once result %u is 0x%08x.\n", i,
           wsp_hash_32(8, (const uint8_t *) input));
    input[7]++;
  }

  input[7] = 0;
  i = 0;

  while (i != 10) {
    i++;
    wsp_hash_32_initialize(&s);
    wsp_hash_32_transform(0, 8, (const uint8_t *) input, &s);
    wsp_hash_32_finalize(&s);
    input[7]++;
    printf("Segmented result %u is 0x%08x.\n", i, s.state);
  }

  return 0;
}
```
