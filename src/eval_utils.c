#include "eval_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

TreeNode *_create_float_tree_node(double val) {
    TreeNode *new_tree_node = malloc(sizeof(TreeNode));
    TreeNodeData *new_tree_node_data = malloc(sizeof(TreeNodeData));

    new_tree_node_data->float_val = val;
    new_tree_node_data->type = FLOAT;
    new_tree_node_data->string_val = NULL;
    new_tree_node_data->char_p_val = NULL;

    new_tree_node->data = new_tree_node_data;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    return new_tree_node;
}

TreeNode *_create_char_p_tree_node(char *val) {
    TreeNode *new_tree_node = malloc(sizeof(TreeNode));
    TreeNodeData *new_tree_node_data = malloc(sizeof(TreeNodeData));

    new_tree_node_data->char_p_val = val;
    new_tree_node_data->type = CHAR_P;
    new_tree_node_data->float_val = 0.0;
    new_tree_node_data->string_val = NULL;

    new_tree_node->data = new_tree_node_data;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    return new_tree_node;
}

TreeNode *_create_string_tree_node(String *str) {
    TreeNode *new_tree_node = malloc(sizeof(TreeNode));
    TreeNodeData *new_tree_node_data = malloc(sizeof(TreeNodeData));

    new_tree_node_data->string_val = str;
    new_tree_node_data->type = STRING;
    new_tree_node_data->float_val = 0.0;
    new_tree_node_data->char_p_val = NULL;

    new_tree_node->data = new_tree_node_data;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    return new_tree_node;
}

void display_tree_node(TreeNode *node) {
    if (node->data->type == FLOAT) {
        printf("%lf", node->data->float_val);
    } else if (node->data->type == STRING) {
        string_print(node->data->string_val);
    } else if (node->data->type == CHAR_P) {
        printf("%s", node->data->char_p_val);
    } else {
        fprintf(stderr, "got unknown type\n");
        exit(1);
    }
}

void free_tree_node(TreeNode *node) {
    if (node == NULL) return;
    free_tree_node(node->left);
    free_tree_node(node->right);

    if (node->data != NULL)
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
        free(string->_str);
    }
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

String *string_create_from_char_p(char *str, size_t size) {
    String *new_string = string_create(size + 1);
    size_t i = 0;
    while (str[i] != '\0') {
        string_append_char(new_string, str[i++]);
    }
    return new_string;
}

LinkedList *string_split_on_char_p(String *string, const char *ch) {
    LinkedList *strings = ll_init();
    char *token = strtok(string->_str, ch);
    while (token != NULL) {
        ll_append(strings, create_node(string_create_from_char_p(token, strlen(token))));
        token = strtok(NULL, ch);
    }
    return strings;
}

int string_n_cmp_char_p(String *string, const char *ch, size_t n) {
    return strncmp(string->_str, ch, n);
}
