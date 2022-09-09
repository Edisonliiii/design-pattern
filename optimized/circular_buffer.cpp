#include <cstdio.h>
#include <cstdlib.h>

#include <iostream>
/**
 * @brief circular buffer
 * -- user case
 * a. fixed length queue, will save the 'moving front' consumption
 * -- 4 ptrs
 * a. read ptr: at the beginning of the data
 * b. write ptr: at the end of the data
 * c. starting addr in memo
 * d. end addr in memo, or use buffer length
 *
 * -- three methods
 * 1. use one idle entry: pos_read - pos_wrt = 1, is full
 * 2. ref counting
 * 3. mirror
 */

class ElementType {};

typedef struct {
  int size;
  int start;
  int end;
  ElementType* elems;
} CircularBuffer;  // one more idle block implementation

void cb_init(CircularBuffer* cb, int size) {
  cb->size = size;
  cb->start = 0;
  cb->end = 0;
  cb->elems = (ElementType*)calloc(cb->size, sizeof(ElementType));
}

void cb_print(CircularBuffer* cb) {
  printf("size = 0x%x, start = %d, end = %d\n", cb->size, cb->start, cb->end);
}

int cb_is_full(CircularBuffer* cb) {
  return cb->end == (cb->start ^ cb->size);
  // flip MSB
}

int cb_is_empty(CircularBuffer* cb) { return cb->end == cb->start; }

int cb_inc(CircularBuffer* cb, int p) { return (p + 1) & (2 * cb->size - 1); }

void cb_read(CircularBuffer* cb, ElementType* elem) {
  *elem = cb->elems[cb->start &
                    (cb->size - 1)];  // wrap around to the start of the array
  cb->start = cb_inc(cb, cb->start);
}

void cb_write(CircularBuffer* cb, ElementType* elem) {
  cb->elems[cb->end & (cb->size - 1)] = *elem;
  if (cb_is_full(cb))
    cb->start = cb_inc(cb, cb->start);  // full, overwrite and move
  cb->end = cb_inc(cb, cb->end);
}