#ifndef value_h
#define value_h
#include <stdbool.h>

enum value_type { VAL_NUMBER, VAL_BOOLEAN };

struct Value {
  enum value_type type;
  union {
    double number;
    bool boolean;
  } as;
};

#define IS_NUMBER(val) ((val).type == VAL_NUMBER)
#define AS_NUMBER(val) ((val).as.number)
#define NUMBER(val) ((struct Value){VAL_NUMBER, {.number = val}})

#endif // !VALUE
