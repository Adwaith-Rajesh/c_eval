#ifndef _EVAL_UTILS_H
#define _EVAL_UTILS_H

#include "linked_list.h"

// clang-format off
#define create_tree_node(data) ({               \
    _Generic(data,                              \
        double: _create_float_tree_node,        \
        char*: _create_string_tree_node         \
    )(data);                                    \
})

// clang format on

typedef enum {
    FLOAT,
    STRING
} TreeNodeDataType;

typedef struct TreeNodeData {
    // the node can store a char * or float
    // this struct just makes it easier to do thing
    char *string_val;
    double float_val;
    TreeNodeDataType type;

} TreeNodeData;

typedef struct TreeNode {
    TreeNodeData *data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    LinkedList *list;
    Node *top;
} LinkedStack;

typedef void StackItemPrinterFn (void *);

TreeNode *_create_float_tree_node(double);
TreeNode *_create_string_tree_node(char *);

void display_tree_node(TreeNode *);
void free_tree_node(TreeNode *);

LinkedStack *ls_init();
void ls_push(LinkedStack *, void *);
void *ls_pop(LinkedStack *);
void *ls_peek(LinkedStack *);
int ls_is_empty(LinkedStack *);
void ls_print(LinkedStack *, StackItemPrinterFn *);
void ls_free(LinkedStack *);

#endif
