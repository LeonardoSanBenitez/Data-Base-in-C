
# About B trees
* keys are kept in sequential ordering
* the tree holds a hierarchical indexing
* ensures balance

### aplications

*  indexing (A significant improvement in databases can be made with index)
*  Most of the tree operations (search, insert, delete, max, min, ..etc ) require O(h) (where h is the height of the tree).
*  The hight of the B-tree is lower than from red-black ad other. The height of B-Trees is kept low by putting maximum possible keys in a B-Tree node.
*  Traversing a range of values is fast (unlike a hash map)
*  Used when $accessTime >> processTime$ 
*  practical B-trees have large number of child nodes


### relation with the hardware
* é mais rápido acessar dados (da memória secundária) quando eles estão proximos (have good locality) 
* B-trees solve this problem by grouping what would be many nodes together into a single giant node. That improve the locality and avoid the malloc overhead. That take advantage of the block structure of memory devices
* Generally, a B-Tree node size is kept equal to the disk block size

# How it works

* The keys are in increasing order. Subtrees are between two keys are between the range of those two

* O numero de filhos de um nó pode ter possui um range (lower and upper bounds)

* Keys: separation values. The subtrees (childs ) of that node will be "inserted" beetween those values, obedecendo a sequência da valores

* Se voce vai inserir e utrapassa o range, divida o nó em dois. If you will delete and the node will stay with less than the minimu range, join two nodes.

* $numberOfChilds = numberOfKeys + 1$

* k = number of keys of the node 

* **minimum degree (t)**

  * minimum number of childs 
  * must have at least t -1 keys
  * Internal nodes have at  least t childs 
  * max number of keys: 2t-1
  * max number of childs (also called *max degree*): 2t

* **order (m)**

  * other way of characterize a B-tree (rather than minimum degree)
  * Max number of keys 
  * $m=2t-1$
  * min number of keys: m/2

* **height**

  * B-trees are always completely balanced, with each leaf the same distance from the root. 

  * every n-node B-tree has height O(lg n)

    ![1542572439418](1542572439418.png)

### Insertion

### Deletition
it's complicated to delete a key from an internal node; the solution is to delete a key from a nearby leaf instead



# How SQLite works

* Page
	* definem a organização de memória da página
	* Em um banco de dados real, as páginas são otimizadas para terem o mesmo tamanho do bloco de memória do disco. Para isso, cada página armazena mais de uma linha.
	* Para mapear a memória (lembre-se que cada banco de dados terá colunas difernetes, que só sabemos em tempo de execução), cada página possui um header com os offsets (em bytes) de cada variável. Isso adiciona um pequeno overheah espacial, mas permite o mapeamento da memória	
	* Todas as páginas de um banco de dados possuem o mesmo tamanho (o tamanho
		 default do SQLite são 4096 bytes).
* Bytecode
	* 







==VEJA GRAFANA + INFLUX==

# Useful links

### B-trees itself

https://www.cs.usfca.edu/~galles/visualization/BTree.html 
http://forums.codeguru.com/showthread.php?453150-B-Tree-C-Implementation

### Databases 

https://cstack.github.io/db_tutorial/
https://www.sqlite.org/arch.html

​	https://github.com/mysql/mysql-server/tree/8.0/storage