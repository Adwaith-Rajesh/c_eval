#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"
#include "eval_utils.h"
#include "linked_list.h"

void _test_node_printer(Node *node) {
    string_print(STRING_P(node->data));
    printf(" ");
}

void *_test_free_postfix_list(Node *node, va_list args) {
    (void)args;
    string_destroy(STRING_P(node->data));
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: c_eval <expression>\n");
        exit(1);
    }

    String *exp = string_create_from_char_p(argv[1], strlen(argv[1]) + 1);
    LinkedList *p_list = infix_to_postfix_list(exp);
    ll_print(p_list, _test_node_printer);

    printf("\n");

    string_destroy(exp);
    ll_map(p_list, _test_free_postfix_list);
    ll_free(p_list);

    return 0;
}
