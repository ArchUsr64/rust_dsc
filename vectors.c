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
  if (vector->len < vector->capacity && vector->ptr != NULL) {
    vector->ptr[vector->len] = value;
    vector->len++;
    return;
  }
  else {
    int* old = vector->ptr;
    vector->capacity *= 2;
    vector->ptr = (int*)malloc(vector->capacity * sizeof(int));
    for (int i = 0; i < vector->len; i++) {
      vector->ptr[i] = old[i];
    }
    free(old);
    vector->ptr[vector->len+1] = value;
    vector->len++;
  }
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

/// Todo
void insert(int index, int value);

void drop(Vec* vector) {
  free(vector->ptr);
}

int main() {
  Vec x = new();
  push(&x, 5);
  push(&x, 3);
  push(&x, 9);
  push(&x, 2);
  push(&x, 0);
  printf("%d\n", unwrap(pop(&x)));
  printf("%d\n", unwrap(pop(&x)));
  printf("%d\n", unwrap(pop(&x)));
  printf("%d\n", unwrap(pop(&x)));
  printf("%d\n", unwrap(pop(&x)));
  printf("%d\n", unwrap(pop(&x)));
}
