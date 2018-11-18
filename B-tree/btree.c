/*
    B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
    DC - UFSCar - São Carlos - 2015
 */
#include "btree.h"
#include "btree_util.h"

BTree* btree_new(int order) {
	BTree* bt = malloc(sizeof(BTree));
	assert(bt != NULL);

	#ifdef DEBUG
	printf("allocated new b-tree of order %d\n", order);
	#endif

	// Após alocar, temos que inicializar a B-Tree
	bt->order = order;
	bt->root = _node_new(order, TRUE);

	return bt;
}

void btree_init(BTree *bt, int order) {
	assert(bt != NULL);

	bt->order = order;
	bt->root = _node_new(order, TRUE);
}

node_position btree_insert(BTree* bt, int key, void *value) {
	assert(bt != NULL);

	#ifdef DEBUG
	printf("inserting key %d\n", key);
	#endif

	node_t *root = bt->root;

	// Esse pair será enviado durante as chamadas recursivas de inserção,
	// e é o que realmente será inserido na B-Tree
	pair_t *pair = _pair_new(key, value);

	if (root->n_keys == 2*bt->order -1) {
		// Caso a raiz da B-Tree já esteja cheia,
		// devemos executar o procedimento de split
		// e deixá-la com apenas uma chave.
		// Esse é o único caso em que a altura da B-Tree aumenta

/*		#ifdef DEBUG
		printf("root full - spliting up\n");
		#endif

		node_t *new_root = _node_new(bt->order, FALSE);
		new_root->children[0] = root;

		_btree_split(new_root, 0, bt->order);
		bt->root = new_root;

		// Podemos prosseguir com a inserção
		return _btree_insert_nonfull(new_root, pair, bt->order);
*/	}
	else {
		// A raiz respeita a restrição de não estar cheia
		#ifdef DEBUG
		printf("root not full - calling _btree_insert_nonfull()\n");
		#endif

		return _btree_insert_nonfull(bt->root, pair, bt->order);
	}
}

void _btree_split(node_t *node, int pos, int order) {
	// Para mais informações, consulte a documentação,
	// em especial o pseudo-código B-Tree-Split-Child

	node_t *y = node->children[pos];
	assert(y != NULL);

	node_t *z = _node_new(order, y->is_leaf);
	z->n_keys = order-1;

	#ifdef DEBUG
	printf("moving keys from root to right: ");
	#endif
	_node_deslocate_keys_up(z, y, 0, order-1, 0, order);

	if (!y->is_leaf) {
		#ifdef DEBUG
		printf("moving children from root to right: ");
		#endif
		_node_deslocate_children_up(z, y, 0, order, 0, order);
	}
	y->n_keys = order-1;

	#ifdef DEBUG
	printf("deslocating new-root childrens pos: ");
	#endif
	_node_deslocate_children_down(node, node, node->n_keys, pos, 1, 0);

	node->children[pos+1] = z;

	#ifdef DEBUG
	printf("moving %d keys: ", node->n_keys);
	#endif
	_node_deslocate_keys_down(node, node, node->n_keys-1, pos-1, 1, 0);

	#ifdef DEBUG
	printf("inserting key %d at %d of new-root\n", y->keys[order-1]->key, pos);
	#endif
	node->keys[pos] = y->keys[order-1];

	node->n_keys++;
}
node_position _btree_insert_nonfull(node_t * node, pair_t *pair, int order) {
	// Para mais informações, consulte a documentação,
	// em especial o pseudo-código B-Tree-Insert-Nonfull

	#ifdef DEBUG
	printf("at _btree_insert_nonfull() with key %d\n", pair->key);
	#endif

	int pos = node->n_keys - 1;
	if (node->is_leaf) {
		#ifdef DEBUG
		printf("at leaf node\n");
		#endif

		while (pos >= 0 && pair->key < node->keys[pos]->key) {
			node->keys[pos+1] = node->keys[pos];
			pos--;
		}

		if (pos >= 0 && pair->key == node->keys[pos]->key) {
			#ifdef DEBUG
			printf("duplicated key. ignoring insertion.");
			#endif

			pos++;
			while (pos != node->n_keys) {
				node->keys[pos] = node->keys[pos+1];
				pos++;
			}

			return _node_position_new(NULL, -1);
		}
		else {
			pos++;

			#ifdef DEBUG
			printf("inserted key %d at position %d\n", pair->key, pos);
			#endif

			node->keys[pos] = pair;
			node->n_keys++;
			return _node_position_new(node, pos);
		}
	}
	else {
		while (pos >= 0 && pair->key < node->keys[pos]->key) {
			pos--;
		}
		if (pos >= 0 && pair->key == node->keys[pos]->key) {
			#ifdef DEBUG
			printf("duplicated key. ignoring insertion.");
			#endif

			return _node_position_new(NULL, -1);
		}
		else {
			pos++;

			if (node->children[pos]->n_keys == 2*order-1) {
				_btree_split(node, pos, order);
				if (pair->key > node->keys[pos]->key) {
					pos++;
				}
			}

			return _btree_insert_nonfull(node->children[pos], pair, order);
		}
	}
}
