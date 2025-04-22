#ifndef value_h
#define value_h

enum value_type { VAL_NUMBER, VAL_BOOLEAN };

struct value {
  value_type type;
  union {
    double number;
    bool boolean;
  } as;
};

#define IS_NUMBER (value)((value).type == VAL_NUMBER)
#define AS_NUMBER (value)((value).as.number = value)
#define NUMBER (value)((Value){VAL_NUMBER, {.number}})

#endif // !VALUE
