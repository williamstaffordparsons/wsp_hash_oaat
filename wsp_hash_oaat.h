#ifndef WSP_HASH_OAAT_H
#define WSP_HASH_OAAT_H

#include <stdint.h>

struct wsp_hash_oaat_s {
  uint32_t mix;
  uint32_t mix_offset;
};

uint32_t wsp_hash_oaat(const unsigned long input_count, const uint8_t *input);

void wsp_hash_oaat_initialize(struct wsp_hash_oaat_s *s);

void wsp_hash_oaat_transform(unsigned long i, const unsigned long input_count,
                             const uint8_t *input, struct wsp_hash_oaat_s *s);

void wsp_hash_oaat_finalize(struct wsp_hash_oaat_s *s);

#endif
