#include "wsp_hash_32.h"

uint32_t _wsp_hash_read_32(const uint8_t *input, unsigned long i) {
  uint32_t _input;

  memcpy(&_input, &input[i], sizeof(_input));
  return _input;
}

uint32_t wsp_hash_32(unsigned long input_count, const uint8_t *input) {
  uint32_t a = 1;
  uint32_t b = 11;
  uint32_t c = 111;
  uint32_t d = 1111;
  uint32_t e = 11111;
  uint32_t f = 111111;
  uint32_t g = 1111111;
  uint32_t h = 11111111;
  unsigned long i = 0;
  uint32_t _state = 111111111;
  uint32_t state = 1111111111;
  unsigned long _input_count = 0;

  if (input_count >= 32) {
    i = 31;

    while (i < input_count) {
      _state = state;
      state += a + b + c + d + e + f + g + h;
      a += _wsp_hash_read_32(input, i - 3) + ((a << 8) | (a >> 24)) + _state + 1;
      b += _wsp_hash_read_32(input, i - 7) + ((b << 9) | (b >> 23)) + _state + 11;
      c += _wsp_hash_read_32(input, i - 11) + ((c << 10) | (c >> 22)) + _state + 111;
      d += _wsp_hash_read_32(input, i - 15) + ((d << 11) | (d >> 21)) + _state + 1111;
      e += _wsp_hash_read_32(input, i - 19) + ((e << 12) | (e >> 20)) + _state + 11111;
      f += _wsp_hash_read_32(input, i - 23) + ((f << 13) | (f >> 19)) + _state + 111111;
      g += _wsp_hash_read_32(input, i - 27) + ((g << 14) | (g >> 18)) + _state + 1111111;
      h += _wsp_hash_read_32(input, i - 31) + ((h << 15) | (h >> 17)) + _state + 11111111;
      i += 32;
    }

    if (i >= input_count) {
      i -= 32;
    }

    _state += a + b + c + d + e + f + g + h;
    i++;
  }

  if ((input_count - i) >= 16) {
    i += 16;
    _state += state;
    state += a + b + c + d + e;
    a += _wsp_hash_read_32(input, i - 16) + ((a << 8) | (a >> 24)) + _state + 1;
    b += _wsp_hash_read_32(input, i - 12) + ((b << 9) | (b >> 23)) + _state + 11;
    c += _wsp_hash_read_32(input, i - 8) + ((c << 10) | (c >> 22)) + _state + 111;
    d += _wsp_hash_read_32(input, i - 4) + ((d << 11) | (d >> 21)) + _state + 1111;
  }

  if ((input_count - i) >= 8) {
    i += 8;
    _state += state;
    state += a + b + c;
    a += _wsp_hash_read_32(input, i - 8) + ((a << 8) | (a >> 24)) + _state + 1;
    b += _wsp_hash_read_32(input, i - 4) + ((b << 9) | (b >> 23)) + _state + 11;
  }

  _input_count += input_count;

  if (i != input_count) {
    state += ((a << 8) | (a >> 24)) + _state;
    input_count -= i;

    if (input_count >= 4) {
      a += _wsp_hash_read_32(input, i) + state + 1111111111;

      if (input_count != 4) {
        _state += a + b;
        state += ((b << 10) | (b >> 22)) + _state;

        if (input_count == 7) {
          b += (input[i + 4] | (input[i + 5] << 8) | (input[i + 6] << 16))
            + state + 1111111;
        } else {
          if (input_count == 6) {
            b += (input[i + 4] | (input[i + 5] << 8)) + state + 111111;
          } else {
            b += input[i + 4] + state + 11111;
          }
        }
      }
    } else {
      if (input_count == 3) {
        a += (input[i] | (input[i + 1] << 8) | (input[i + 2] << 16)) + state
          + 111;
      } else {
        if (input_count == 2) {
          a += (input[i] | (input[i + 1] << 8)) + state + 11;
        } else {
          a += input[i] + state + 1;
        }
      }
    }
  }

  a += _state;
  state += (a << 8) | (a >> 24);
  b += state ^ _state;
  state += (b << 9) | (b >> 23);

  if (_input_count >= 16) {
    c += _state + state;
    state += (c << 10) | (c >> 22);
    d += state;
    state += (d << 11) | (d >> 21);

    if (_input_count >= 32) {
      e += state;
      state += (e << 12) | (e >> 20);
      f += state;
      state += (f << 13) | (f >> 19);
      g += state;
      state += (g << 14) | (g >> 18);
      h += a + state;
      state += ((h << 15) | (h >> 17)) + _state;
    }
  }

  _state += state + _input_count;
  state += ((a << 13) | (a >> 19)) ^ h;
  b += state;
  state += a ^ ((b << 14) | (b >> 18));
  c += _state ^ state;
  state += b ^ ((c << 15) | (c >> 17));
  d += _state + state;
  state += c ^ ((d << 17) | (d >> 15));
  _state += state;
  e += _state ^ state;
  state += d ^ ((e << 18) | (e >> 14));
  f += _state + state;
  state += e ^ ((f << 19) | (f >> 13));
  g += state;
  state += f ^ ((g << 20) | (g >> 12));
  h += state;
  return (g ^ ((h << 21) | (h >> 11))) + state + _state;
}

void wsp_hash_32_initialize(struct wsp_hash_32_s *s) {
  s->a = 1;
  s->b = 11;
  s->c = 111;
  s->d = 1111;
  s->e = 11111;
  s->f = 111111;
  s->g = 1111111;
  s->h = 11111111;
  s->_state = 111111111;
  s->state = 1111111111;
  s->_input_count = 0;
}

void wsp_hash_32_transform(unsigned long i, unsigned long input_count,
                           const uint8_t *input,
                           struct wsp_hash_32_s *s) {
  if (input_count >= 32) {
    i = 31;

    while (i < input_count) {
      s->_state = s->state;
      s->state += s->a + s->b + s->c + s->d + s->e + s->f + s->g + s->h;
      s->a += _wsp_hash_read_32(input, i - 3) + ((s->a << 8) | (s->a >> 24))
        + s->_state + 1;
      s->b += _wsp_hash_read_32(input, i - 7) + ((s->b << 9) | (s->b >> 23))
        + s->_state + 11;
      s->c += _wsp_hash_read_32(input, i - 11) + ((s->c << 10) | (s->c >> 22))
        + s->_state + 111;
      s->d += _wsp_hash_read_32(input, i - 15) + ((s->d << 11) | (s->d >> 21))
        + s->_state + 1111;
      s->e += _wsp_hash_read_32(input, i - 19) + ((s->e << 12) | (s->e >> 20))
        + s->_state + 11111;
      s->f += _wsp_hash_read_32(input, i - 23) + ((s->f << 13) | (s->f >> 19))
        + s->_state + 111111;
      s->g += _wsp_hash_read_32(input, i - 27) + ((s->g << 14) | (s->g >> 18))
        + s->_state + 1111111;
      s->h += _wsp_hash_read_32(input, i - 31) + ((s->h << 15) | (s->h >> 17))
        + s->_state + 11111111;
      i += 32;
    }

    if (i >= input_count) {
      i -= 32;
    }

    s->_state += s->a + s->b + s->c + s->d + s->e + s->f + s->g + s->h;
    i++;
  }

  if ((input_count - i) >= 16) {
    i += 16;
    s->_state += s->state;
    s->state += s->a + s->b + s->c + s->d + s->e;
    s->a += _wsp_hash_read_32(input, i - 16) + ((s->a << 8) | (s->a >> 24))
      + s->_state + 1;
    s->b += _wsp_hash_read_32(input, i - 12) + ((s->b << 9) | (s->b >> 23))
      + s->_state + 11;
    s->c += _wsp_hash_read_32(input, i - 8) + ((s->c << 10) | (s->c >> 22))
      + s->_state + 111;
    s->d += _wsp_hash_read_32(input, i - 4) + ((s->d << 11) | (s->d >> 21))
      + s->_state + 1111;
  }

  if ((input_count - i) >= 8) {
    i += 8;
    s->_state += s->state;
    s->state += s->a + s->b + s->c;
    s->a += _wsp_hash_read_32(input, i - 8) + ((s->a << 8) | (s->a >> 24))
      + s->_state + 1;
    s->b += _wsp_hash_read_32(input, i - 4) + ((s->b << 9) | (s->b >> 23))
      + s->_state + 11;
  }

  s->_input_count += input_count;

  if (i != input_count) {
    s->state += ((s->a << 8) | (s->a >> 24)) + s->_state;
    input_count -= i;

    if (input_count >= 4) {
      s->a += _wsp_hash_read_32(input, i) + s->state + 1111111111;

      if (input_count != 4) {
        s->_state += s->a + s->b;
        s->state += ((s->b << 10) | (s->b >> 22)) + s->_state;

        if (input_count == 7) {
          s->b += (input[i + 4] | (input[i + 5] << 8) | (input[i + 6] << 16))
            + s->state + 1111111;
        } else {
          if (input_count == 6) {
            s->b += (input[i + 4] | (input[i + 5] << 8)) + s->state + 111111;
          } else {
            s->b += input[i + 4] + s->state + 11111;
          }
        }
      }
    } else {
      if (input_count == 3) {
        s->a += (input[i] | (input[i + 1] << 8) | (input[i + 2] << 16))
          + s->state + 111;
      } else {
        if (input_count == 2) {
          s->a += (input[i] | (input[i + 1] << 8)) + s->state + 11;
        } else {
          s->a += input[i] + s->state + 1;
        }
      }
    }
  }
}

void wsp_hash_32_finalize(struct wsp_hash_32_s *s) {
  s->a += s->_state;
  s->state += (s->a << 8) | (s->a >> 24);
  s->b += s->_state ^ s->state;
  s->state += (s->b << 9) | (s->b >> 23);

  if (s->_input_count >= 16) {
    s->c += s->_state + s->state;
    s->state += (s->c << 10) | (s->c >> 22);
    s->d += s->state;
    s->state += (s->d << 11) | (s->d >> 21);

    if (s->_input_count >= 32) {
      s->e += s->state;
      s->state += (s->e << 12) | (s->e >> 20);
      s->f += s->state;
      s->state += (s->f << 13) | (s->f >> 19);
      s->g += s->state;
      s->state += (s->g << 14) | (s->g >> 18);
      s->h += s->a + s->state;
      s->state += ((s->h << 15) | (s->h >> 17)) + s->_state;
    }
  }

  s->_state += s->state + s->_input_count;
  s->state += ((s->a << 13) | (s->a >> 19)) ^ s->h;
  s->b += s->state;
  s->state += s->a ^ ((s->b << 14) | (s->b >> 18));
  s->c += s->_state ^ s->state;
  s->state += s->b ^ ((s->c << 15) | (s->c >> 17));
  s->d += s->_state + s->state;
  s->state += s->c ^ ((s->d << 17) | (s->d >> 15));
  s->_state += s->state;
  s->e += s->_state ^ s->state;
  s->state += s->d ^ ((s->e << 18) | (s->e >> 14));
  s->f += s->_state + s->state;
  s->state += s->e ^ ((s->f << 19) | (s->f >> 13));
  s->g += s->state;
  s->state += s->f ^ ((s->g << 20) | (s->g >> 12));
  s->h += s->state;
  s->state += (s->g ^ ((s->h << 21) | (s->h >> 11))) + s->_state;
}
