#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

// separate inline function to prevent evaluating argument expression (and
// associated side effects) for `value` more than once. (e.g., IS_STRING(POP()))
#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

typedef enum {
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
  struct Obj *next;
};

struct ObjString {
  Obj obj;
  int length;
  char *chars;
  uint32_t hash;
};

ObjString *takeString(char *chars, int length);
ObjString *copyString(const char *chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif

/*  Design note:
   The above layour of the `ObjString`, namely `Obj` as the first field of the
   structure, allows safe convertion of the `ObjString *pointer` to the `Obj
   *pointer` and back.

   Checking `ObjType` value allows a safe "downcast" of the `Obj *pointer` to
   the `ObjString *pointer`.
*/