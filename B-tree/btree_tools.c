/*
	B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
	DC - UFSCar - São Carlos - 2015
 */
#include "btree_tools.h"


void _btree_dfs_node(node_t *node, int level) {
	assert(node != NULL);

	int i;
	if (!node->is_leaf) {
		for (i = 0; i < node->n_keys+1; ++i) {
			_btree_dfs_node(node->children[i], level+1);
		}
	}

	printf("\tAlgum nó no nível %d possui %d chave(s): ", level, node->n_keys);
	for (i = 0; i < node->n_keys; ++i) {
		if (i != 0) printf(" ");
		printf("%d", node->keys[i]->key);
	}
	printf("\n");
}

void btree_dfs(BTree *bt) {
	assert(bt != NULL);
	_btree_dfs_node(bt->root, 0);
}

