#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPCITY 4
#define NONE '\0'
#define EMPTY_VECTOR 'E'
#define INVALID_INDEX 'I'

void panic(char error_code) {
  printf("Error occured: %c\n", error_code);
}

typedef struct {
  int value;
  char errror_code;
} ErrorableInt;

int unwrap(ErrorableInt potentially_error) {
  if (potentially_error.errror_code == NONE)
    return potentially_error.value;
  printf("ERROR occured: %c\n", potentially_error.errror_code);
  exit(EXIT_FAILURE);
}

typedef struct {
  int *ptr;
  unsigned len;
  unsigned capacity;
} Vec;

void debug_print(Vec* vector) {
  printf("Capacity: %d, Length: %d, Values: [", vector->capacity, vector->len);
  for (int i = 0; i < vector->len; i++)
    printf("%d, ", vector->ptr[i]);
  printf("]\n");
}

void reserve(Vec* vector, int additional) {
  if (vector->capacity >= additional + vector->len) {
    return;
  }
  int* old = vector->ptr;
  vector->capacity *= 2;
  vector->ptr = malloc(sizeof(int) * vector->capacity);
  for (int i = 0; i < vector->len; i++)
    vector->ptr[i] = old[i];
  free(old);
}

Vec new() {
  Vec result = {(int*)malloc(sizeof(int) * INITIAL_CAPCITY), 0, INITIAL_CAPCITY};
  return result;
}

Vec with_capacity(int capacity) {
  Vec result = {(int*)malloc(sizeof(int) * capacity), 0, capacity};
  return result;
}

int* leak(Vec* vector) {
  return vector->ptr;
}

int is_empty(Vec* vector) {
  return vector->len == 0;
}

Vec clone(Vec* target) {
  Vec result = with_capacity(target->capacity);
  result.len = target->len;
  for (int i = 0; i < 0; i++)
    result.ptr[i] = target->ptr[i];
  return result;
}

unsigned len(Vec* vector) {
  return vector->len;
}

unsigned capacity(Vec* vector) {
  return vector->capacity;
}

void push(Vec* vector, int value) {
    reserve(vector, 1);
    vector->ptr[vector->len++] = value;
}

ErrorableInt pop(Vec* vector) {
  ErrorableInt errorable;
  if (vector->len > 0) {
    errorable.value = vector->ptr[vector->len - 1];
    errorable.errror_code = NONE;
    vector->len--;
  }
  else {
    errorable.errror_code = EMPTY_VECTOR;
  }
  return errorable;
}

void truncate(Vec* vector, int len) {
  if (len >= vector->len) {
    return;
  }
  vector->len = len;
}

void set_len(Vec* vector, int len) {
  vector->len = len;
}

void swap(Vec* vector, int a, int b) {
  int temp = vector->ptr[a];
  vector->ptr[a] = vector->ptr[b];
  vector->ptr[b] = temp;
}

int swap_remove(Vec* vector, int index) {
  int result = vector->ptr[index];
  vector->len--;
  swap(vector, vector->len, index);
  return result;
}

int is_sorted(Vec* vector) {
  for (int i = 1; i < vector->len; i++) {
    if (vector->ptr[i-1] > vector->ptr[i])
      return 0;
  }
  return 1;
}

int binary_serach(Vec* vector, int key) {
  int test_point = vector->len/2;
  int move_distance = test_point/2;
  move_distance = move_distance > 0 ? move_distance : 1;
  while (test_point >= 0 && test_point < vector->len) {
    int value = vector->ptr[test_point];
    if (value > key) {
      test_point -= move_distance;
    } else if (value < key) {
      test_point += move_distance;
    } else {
      return test_point;
    }
    move_distance /= 2;
    move_distance = move_distance > 0 ? move_distance : 1;
  }
  return -1;
}

void clear(Vec* vector) {
  vector->len = 0;
}

void append(Vec* vector, Vec* other) {
  for (int i = 0; i < other->len; i++)
    push(vector, other->ptr[i]);
}

int contains(Vec* vector, int value) {
  for (int i = 0; i < vector->len; i++)
    if (vector->ptr[i] == value)
      return i;
  return -1;
}

void reverse(Vec* vector) {
  for (int i = 0; i < vector->len / 2; i++)
    swap(vector, i, vector->len - 1 - i);
}

//TODO: remove, retain, split_off, sort

void insert(Vec* vector, int index, int element) {
  if (index > vector->len) {
    return;
  }
  reserve(vector, 1);
  int replaced = vector->ptr[index];
  vector->ptr[index] = element;
  for (int i = vector->len; i > index; i--) {
    printf("i: %d\n", i);
    vector->ptr[i] = vector->ptr[i-1];
  }
  vector->len++;
  vector->ptr[index+1] = replaced;
}

void drop(Vec* vector) {
  free(vector->ptr);
}
