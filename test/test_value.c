#include "../src/value.h"
#include <assert.h>
#include <stdio.h>

void test_create_number_value() {

  printf("start test create number value");
  double val = 33;
  struct Value number_value = {0};

  number_value = NUMBER(33);

  assert(IS_NUMBER(number_value));
  assert(AS_NUMBER(number_value) == val);

  printf("test_create_number_value -- PASSED");
}

int main() { test_create_number_value(); }
