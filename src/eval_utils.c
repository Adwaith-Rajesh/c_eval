#include "eval_utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

TreeNode *_create_float_tree_node(double val) {
    TreeNode *new_tree_node = malloc(sizeof(TreeNode));
    TreeNodeData *new_tree_node_data = malloc(sizeof(TreeNodeData));

    new_tree_node_data->float_val = val;
    new_tree_node_data->type = FLOAT;
    new_tree_node_data->string_val = NULL;

    new_tree_node->data = new_tree_node_data;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    return new_tree_node;
}

TreeNode *_create_string_tree_node(char *val) {
    TreeNode *new_tree_node = malloc(sizeof(TreeNode));
    TreeNodeData *new_tree_node_data = malloc(sizeof(TreeNodeData));

    new_tree_node_data->string_val = val;
    new_tree_node_data->type = STRING;
    new_tree_node_data->float_val = 0.0;

    new_tree_node->data = new_tree_node_data;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    return new_tree_node;
}

void display_tree_node(TreeNode *node) {
    if (node->data->type == FLOAT) {
        printf("%lf\n", node->data->float_val);
    } else if (node->data->type == STRING) {
        printf("%s\n", node->data->string_val);
    } else {
        fprintf(stderr, "got unknown type\n");
        exit(1);
    }
}

void free_tree_node(TreeNode *node) {
    if (node == NULL) return;
    if (node->data == NULL) return;
    free(node->data);
    free(node);
}

LinkedStack *ls_init() {
    LinkedList *new_ll = ll_init();
    LinkedStack *new_ls = malloc(sizeof(LinkedStack));
    new_ls->list = new_ll;
    new_ls->top = NULL;
    return new_ls;
}

void ls_push(LinkedStack *stack, void *data) {
    Node *new_node = create_node(data);
    stack->top = new_node;
    ll_append_left(stack->list, new_node);
}

void *ls_pop(LinkedStack *stack) {
    Node *node = ll_pop_left(stack->list);
    stack->top = stack->list->head;

    if (node == NULL) return NULL;
    void *v_p = node->data;
    free_node(node);
    return v_p;
}

void *ls_peek(LinkedStack *stack) {
    if (stack->top == NULL) return NULL;
    return stack->top->data;
}

int ls_is_empty(LinkedStack *stack) {
    return ll_is_empty(stack->list);
}

void ls_print(LinkedStack *stack, StackItemPrinterFn *fn) {
    // could not find an easy way to do it.
    // w/o iterating the list myself
    Node *temp = stack->list->head;
    while (temp != NULL) {
        fn(temp->data);
        temp = temp->next;
    }
}

void ls_free(LinkedStack *stack) {
    ll_free(stack->list);
    free(stack);
}

String *string_create(size_t size) {
    if (size < 1) return NULL;

    String *new_string = malloc(sizeof(String));
    new_string->_str = malloc(sizeof(char) * size);
    new_string->_str[0] = '\0';
    new_string->curr_p = 0;
    new_string->cap = size;
    return new_string;
}

void string_destroy(String *string) {
    if (string == NULL) return;
    if (string->_str != NULL) {
        printf("in if\n");
        free(string->_str);
    }
    printf("outside\n");
    free(string);
}

void string_append_char(String *string, char ch) {
    if (string->curr_p < string->cap - 1) {
        string->_str[string->curr_p] = ch;
        string->_str[++string->curr_p] = '\0';
        return;
    }
}

void string_print(String *string) {
    if (string == NULL) return;
    printf("%s", string->_str);
}
