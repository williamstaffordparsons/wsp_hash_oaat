#ifndef WSP_HASH_OAAT_H
#define WSP_HASH_OAAT_H

#include <stdint.h>

struct wsp_hash_oaat_s {
  uint32_t _state;
  uint32_t state;
};

uint32_t wsp_hash_oaat(unsigned long input_count, const uint8_t *input);

void wsp_hash_oaat_initialize(struct wsp_hash_oaat_s *s);

void wsp_hash_oaat_transform(unsigned long i, unsigned long input_count,
                           const uint8_t *input,
                           struct wsp_hash_oaat_s *s);

void wsp_hash_oaat_finalize(struct wsp_hash_oaat_s *s);

#endif
