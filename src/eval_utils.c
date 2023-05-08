#include "eval_utils.h"

#include <stdio.h>
#include <stdlib.h>

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
