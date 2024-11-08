#include "wsp_hash_oaat.h"

uint32_t wsp_hash_oaat(unsigned long input_count, const uint8_t *input) {
  uint32_t _state = 1;
  uint32_t state = 1111111111;
  unsigned long i = 0;

  while (i != input_count) {
    state ^= input[i];
    state += state << 3;
    _state += state;
    _state = (_state << 27) | (_state >> 5);
    i++;
  }

  state ^= _state;
  state = (_state ^ state) + ((state << 10) | (state >> 22));
  return ((_state << 27) | (_state >> 5)) + state;
}

void wsp_hash_oaat_initialize(struct wsp_hash_oaat_s *s) {
  s->_state = 1;
  s->state = 1111111111;
}

void wsp_hash_oaat_transform(unsigned long i, unsigned long input_count,
                             const uint8_t *input, struct wsp_hash_oaat_s *s) {
  while (i != input_count) {
    s->state ^= input[i];
    s->state += s->state << 3;
    s->_state += s->state;
    s->_state = (s->_state << 27) | (s->_state >> 5);
    i++;
  }
}

void wsp_hash_oaat_finalize(struct wsp_hash_oaat_s *s) {
  s->state ^= s->_state;
  s->state = (s->_state ^ s->state) + ((s->state << 10) | (s->state >> 22));
  s->state += (s->_state << 27) | (s->_state >> 5);
}
