// where everything related to evaluation actually happens
#include "eval.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "eval_utils.h"
#include "linked_list.h"

// infix to postfix conversion and related functions

// https://stackoverflow.com/a/45555413/14617085
static int test_float(String *string) {
    int len;
    float dummy = 0.0;
    if (sscanf(string->_str, "%f %n", &dummy, &len) == 1 && len == (int)strlen(string->_str))
        return 1;
    else
        return 0;
}

static int prec(String *str) {
    if (string_n_cmp_char_p(str, "^", 1) == 0) return 3;
    if ((string_n_cmp_char_p(str, "*", 1) == 0) ||
        (string_n_cmp_char_p(str, "/", 1) == 0)) return 2;
    if ((string_n_cmp_char_p(str, "+", 1) == 0) ||
        (string_n_cmp_char_p(str, "-", 1) == 0)) return 1;
    return -1;
}

void *_test_free_stirng_from_tokens(Node *node, va_list args) {
    string_destroy(STRING_P(node->data));
    return NULL;
}

void _test_p_list_printer(Node *node) {
    string_print(STRING_P(node->data));
}

void *_infix_to_postfix(Node *node, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);

    LinkedList *p_list = va_arg(args_copy, LinkedList *);
    Stack *stack = va_arg(args_copy, Stack *);

    String *str = STRING_P(node->data);

    if (test_float(str)) {
        ll_append(p_list, create_node(str));
    } else if (string_n_cmp_char_p(str, "(", 1) == 0) {
        ls_push(stack, str);
    } else if (string_n_cmp_char_p(str, ")", 1) == 0) {
        while (!ls_is_empty(stack) && (string_n_cmp_char_p(STRING_P(ls_peek(stack)), "(", 1) != 0)) {
            ll_append(p_list, create_node(ls_pop(stack)));
        }
        ls_pop(stack);  // get rid of (
    } else {            // we have an operator
        if (!ls_is_empty(stack) && prec(str) == 3 && prec(STRING_P(ls_peek(stack))) == 3) {
            ls_push(stack, str);
            return node->data;
        }
        while (!ls_is_empty(stack) && (prec(str) <= prec(STRING_P(ls_peek(stack))))) {
            ll_append(p_list, create_node(ls_pop(stack)));
        }
        ls_push(stack, str);
    }

    return node->data;
}

LinkedList *infix_to_postfix_list(String *exp) {
    LinkedList *post_fix_list = ll_init();
    Stack *stack = ls_init();

    LinkedList *tokens = string_split_on_char_p(exp, " ");
    ll_map(tokens, _infix_to_postfix, post_fix_list, stack);

    while (!ls_is_empty(stack)) {
        ll_append(post_fix_list, create_node(ls_pop(stack)));
    }

    ls_free(stack);
    ll_free(tokens);
    return post_fix_list;
}

// end infix to postfix
