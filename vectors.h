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

void insert(Vec* vector, int index, int element) {
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
