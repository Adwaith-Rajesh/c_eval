#ifndef _EVAL_H
#define _EVAL_H

#include <stdarg.h>

#include "eval_utils.h"
#include "linked_list.h"

#define STRING_P(X) (String *)(X)
#define VOID_P(X) (void *)(X)

typedef LinkedStack Stack;

void *_infix_to_postfix(Node *, va_list);
LinkedList *infix_to_postfix_list(String *);

#endif
