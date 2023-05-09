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

void traverse_tree(TreeNode *node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) {
        printf((i == level - 1) ? "|-" : " ");
    }

    if (node->data->type == STRING) {
        string_print(node->data->string_val);
    } else if (node->data->type == FLOAT) {
        printf("%lf", node->data->float_val);
    }
    printf("\n");
    traverse_tree(node->left, level + 1);
    traverse_tree(node->right, level + 1);
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

    TreeNode *tree_node = postfix_list_to_expression_tree(p_list);
    traverse_tree(tree_node, 0);

    string_destroy(exp);

    ll_print(p_list, _test_node_printer);

    ll_map(p_list, _test_free_postfix_list);

    ll_free(p_list);
    free_tree_node(tree_node);

    return 0;
}
