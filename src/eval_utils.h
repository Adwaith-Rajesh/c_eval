#ifndef _EVAL_UTILS_H
#define _EVAL_UTILS_H

#include "linked_list.h"

// clang-format off
#define create_tree_node(data) ({               \
    _Generic(data,                              \
        double: _create_float_tree_node,        \
        char*: _create_char_p_tree_node,        \
        String*: _create_string_tree_node       \
    )(data);                                    \
})

// clang format on

typedef enum {
    FLOAT,
    CHAR_P,
    STRING
} TreeNodeDataType;

typedef struct TreeNodeData {
    // the node can store a char * or float
    // this struct just makes it easier to do thing
    char *char_p_val;
    double float_val;
    struct String *string_val;
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

typedef struct String{
    char *_str;
    size_t curr_p;  // index where the next char will be inserted
    size_t cap;
} String;

TreeNode *_create_float_tree_node(double);
TreeNode *_create_char_p_tree_node(char *);
TreeNode *_create_string_tree_node(String *);

void display_tree_node(TreeNode *);
void free_tree_node(TreeNode *);

LinkedStack *ls_init();
void ls_push(LinkedStack *, void *);
void *ls_pop(LinkedStack *);
void *ls_peek(LinkedStack *);
int ls_is_empty(LinkedStack *);
void ls_print(LinkedStack *, StackItemPrinterFn *);
void ls_free(LinkedStack *);

String *string_create(size_t);
String *string_create_from_char_p(char *, size_t);
void string_destroy(String *);
void string_append_char(String *, char);
void string_print(String *);
LinkedList *string_split_on_char_p(String *, const char *);
int string_n_cmp_char_p(String *, const char *, size_t);

#endif
