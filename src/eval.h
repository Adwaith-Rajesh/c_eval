#ifndef _EVAL_H
#define _EVAL_H

#include <stdarg.h>

#include "eval_utils.h"
#include "linked_list.h"

#define STRING_P(X) (String *)(X)
#define VOID_P(X) (void *)(X)

typedef LinkedStack Stack;

LinkedList *infix_to_postfix_list(String *);
TreeNode *postfix_list_to_expression_tree(LinkedList *);

#endif
