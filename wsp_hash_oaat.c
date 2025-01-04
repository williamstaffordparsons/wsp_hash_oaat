#include "wsp_hash_oaat.h"

uint32_t wsp_hash_oaat(const unsigned long input_count, const uint8_t *input) {
  uint32_t mix = 1111111111;
  uint32_t mix_offset = 1;
  unsigned long i = 0;

  while (i != input_count) {
    mix ^= input[i];
    mix += mix << 3;
    mix_offset += mix;
    mix_offset = (mix_offset << 27) | (mix_offset >> 5);
    i++;
  }

  mix ^= mix_offset;
  mix = (mix ^ mix_offset) + ((mix << 10) | (mix >> 22));
  return mix + ((mix_offset << 27) | (mix_offset >> 5));
}

void wsp_hash_oaat_initialize(struct wsp_hash_oaat_s *s) {
  s->mix = 1111111111;
  s->mix_offset = 1;
}

void wsp_hash_oaat_transform(unsigned long i, const unsigned long input_count,
                             const uint8_t *input, struct wsp_hash_oaat_s *s) {
  while (i != input_count) {
    s->mix ^= input[i];
    s->mix += s->mix << 3;
    s->mix_offset += s->mix;
    s->mix_offset = (s->mix_offset << 27) | (s->mix_offset >> 5);
    i++;
  }
}

void wsp_hash_oaat_finalize(struct wsp_hash_oaat_s *s) {
  s->mix ^= s->mix_offset;
  s->mix = (s->mix ^ s->mix_offset) + ((s->mix << 10) | (s->mix >> 22));
  s->mix += (s->mix_offset << 27) | (s->mix_offset >> 5);
}
