#ifndef WSP_HASH_32_H
#define WSP_HASH_32_H

#include <stdint.h>
#include <string.h>

struct wsp_hash_32_s {
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
  uint32_t f;
  uint32_t g;
  uint32_t h;
  uint32_t _state;
  uint32_t state;
  unsigned long _input_count;
};

uint32_t wsp_hash_32(unsigned long input_count, const uint8_t *input);

void wsp_hash_32_initialize(struct wsp_hash_32_s *s);

void wsp_hash_32_transform(unsigned long i, unsigned long input_count,
                           const uint8_t *input,
                           struct wsp_hash_32_s *s);

void wsp_hash_32_finalize(struct wsp_hash_32_s *s);

#endif
