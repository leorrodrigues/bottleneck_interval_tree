#ifndef _INTERVAL_TREE_
#define _INTERVAL_TREE_

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

namespace Interval_Tree {
typedef struct node_t {
	unsigned int size; // the total ammount of children the node has.
	int interval[2]; // The interval that the node has [_,-1] to define infinity
	int height; // The height of the subtree

	float capacity; // The total ammount of capacity the current node has available

	node_t *left;
	node_t *right;
} node_t;

class Interval_Tree {

private:
typedef struct {
	node_t *root;
	float capacity; // the capacity of the server
} interval_tree_t;

interval_tree_t *tree;

inline int getHeight(node_t* node){
	return node==NULL ? -1 : node->height;
}

inline int getSize(node_t* node){
	return node==NULL ? 0 : node->size+1;
}

inline int getMax(int a, int b){
	return a>b ? a : b;
}

inline int getBF(node_t* node){
	return getHeight(node->right)-getHeight(node->left);
}

inline void single_rotate_left(node_t* x){
	node_t *temp =  x->right;

	std::swap((*x),((*x->right)));

	temp->right = x->left;
	x->left = temp;

	x->left->height = getMax(getHeight(x->left->left),getHeight(x->left->right)) + 1;

	x->height = getMax(getHeight(x->left),getHeight(x->right)) + 1;

	x->left->size = getSize(x->left->left) + getSize(x->left->right);
	x->size = getSize(x->left) + getSize(x->right);
}

inline void single_rotate_right(node_t* x){
	node_t *temp =  x->left;

	std::swap((*x),((*x->left)));

	temp->left = x->right;
	x->right = temp;

	x->right->height = getMax(getHeight(x->right->left),getHeight(x->right->right)) + 1;
	x->height = getMax(getHeight(x->left),getHeight(x->right)) + 1;

	x->right->size = getSize(x->right->left) + getSize(x->right->right);
	x->size = getSize(x->left) + getSize(x->right);
}

void show_bf(node_t *node,unsigned int tab){
	int i=0;
	if(node==NULL) {
		for(i=0; i<tab; i++)
			printf("\t");
		printf("Node: NULL\n");
		return;
	}
	for(i=0; i<tab; i++)
		printf("\t");
	printf("Node in [%d,%d] # Elements: %u # Height %d # Capacity: %f\n", node->interval[0], node->interval[1], node->size, node->height, node->capacity);
	show_bf(node->left,tab+1);
	show_bf(node->right,tab+1);
}

void free_nodes(node_t *node){
	if(node == NULL) return;
	free_nodes(node->left);
	free_nodes(node->right);
	free(node);
	node=NULL;
}

public:
Interval_Tree(float capacity = 0){
	if((tree = (interval_tree_t*)malloc(sizeof(interval_tree_t)))==NULL) {
		printf("Error in malloc\n");
		exit(1);
	}
	tree->root=NULL;
	tree->capacity = capacity;
}

~Interval_Tree(){
	free_nodes(tree->root);
	free(tree);
	tree=NULL;
}

void show(){
	printf("The Bottleneck Interval Tree ");
	if(tree->root==NULL) {
		printf("don't has any elements.\n");
	}else{
		printf("has %u elements.\n", tree->root->size+1);
		show_bf(tree->root, 0);
	}
}

void insert(int interval_min, int interval_max, float capacity){
	node_t **path = NULL;
	int index=-1;
	int key = interval_min;
	bool hasOverlap = false;

	//allocate the paths size
	if(tree->root != NULL) {
		path = (node_t**)malloc(sizeof(node_t*)*(tree->root->height+2)); //allocate the total ammount needed to build the path
	}

	//iterate through the tree to get the nodes
	{
		node_t *aux = tree->root;

		while(aux != NULL && aux->interval[0] != interval_min) {//while not found an empty child and the current node dont has the same low interval of the new node
			++index;
			path[index] = aux;
			aux = interval_min > aux->interval[0] ? aux->right : aux->left;
		}
		//check if the low interval are equal.
		if(interval_min == aux->interval[0]) {
			//iterate through the nodes that has the same low interval to check the hight interval. If exists a node with the same [a,b] interval, just add the total ammount of
		}
	}

	node_t *new_node;
	if((new_node = (node_t*)malloc(sizeof(node_t)))==NULL) {
		printf("Error in alocate new node\n");
		exit(1);
	}

	new_node->left = NULL;
	new_node->right = NULL;
	new_node->size = 0;
	new_node->height=0;

	new_node->interval[0] = interval_min;
	new_node->interval[1] = interval_max;

	new_node->capacity = capacity;

	if(index==-1) {
		tree->root=new_node;
	}else{
		if(key > path[index]->interval[0])
			path[index]->right = new_node;
		else
			path[index]->left = new_node;

		++path[index]->size;
		path[++index]=new_node;
	}
	int bf;
	while(index>=0) {         // returning the path, updating the nodes' height and check if is needed to make some rotation.
		//updating the height
		path[index]->height = getMax(getHeight(path[index]->left),getHeight(path[index]->right)) + 1;

		path[index]->size = getSize(path[index]->left)+getSize(path[index]->right);

		//check the balancing factor
		bf = getBF(path[index]);

		if(bf > 1 && key > path[index]->right->interval[0]) {         // single left
			single_rotate_left(path[index]);
			bf = getBF(path[index]);
		}
		if(bf < -1 && key < path[index]->left->interval[0]) {         // single right
			single_rotate_right(path[index]);
			bf = getBF(path[index]);
		}
		if(bf > 1 && key < path[index]->right->interval[0]) {         // double left
			single_rotate_right(path[index]->right);
			single_rotate_left(path[index]);
			bf = getBF(path[index]);
		}
		if(bf < -1 && key > path[index]->left->interval[0]) {         // double right
			single_rotate_left(path[index]->left);
			single_rotate_right(path[index]);
			bf = getBF(path[index]);
		}
		--index;
	}
	if(path!=NULL)
		free(path);
	path=NULL;
}

void remove(int key, int s_key){        //key = min_interval, s_key = max_interval
	node_t **path = NULL;
	if(tree->root == NULL)         //empty tree
		return;
	else
		path = (node_t**)malloc(sizeof(node_t*)*(tree->root->height+2));         //allocate the total ammount needed to build the path, it's a ternary pointer to store all the original pointers of Interval_Tree

	int index=-1;

	{
		node_t *aux = tree->root;
		while(aux != NULL) {        //while not found a empty child
			++index;
			path[index] = aux;         // update the path
			if(aux->interval[0] == key) {         // equal keys aren't allowed
				break;         // find the node
			}
			aux = key > aux->interval[0] ? aux->right : aux->left;
		}
		// printf("Key found! Cheking for Skey\n");
		while(aux != NULL && aux->interval[1] != s_key) {
			aux = s_key > aux->interval[1] ? aux->right : aux->left;
		}
		// printf("Both keys found\n");
		if(aux==NULL) {         // didn't find any child that hold the key for deletion
			free(path);         // Free the parh variable
			path=NULL;
			printf("Don't existis any node that holds the specific interval [%d;%d]\n", key, s_key);
			return;
		}
	}

	int index_sub = index;

	node_t *temp = (node_t*) malloc(sizeof(node_t));
	if (path[index_sub]->size>1) {         // the node two children
		temp = path[index_sub]->left;
		path[++index_sub] = path[index_sub]->left;
		while(temp->right != NULL) {         // get the node with the largest key in the left subtree of the selected node
			path[++index_sub] = path[index_sub]->right;
			temp = temp->right;
		}

		if(index>0) {
			if(path[index]->right != temp) {
				temp->right = path[index]->right;
			}
			if(path[index]->left != temp) {
				temp->left = path[index]->left;
			}
			if(path[index-1]->left->interval[0]>temp->interval[0])
				path[index-1]->left = temp;
			else
				path[index-1]->right = temp;
			if(path[index_sub-1]->left==path[index_sub]) {
				path[index_sub-1]->left = NULL;
			} else{
				path[index_sub-1]->right = NULL;
			}
			free(path[index]);
			path[index] = temp;
			path[index_sub] = NULL;
		}else{
			if(temp != path[index]->right)
				temp->right = path[index]->right;
			if(temp != path[index]->left)
				temp->left = path[index]->left;
			if(path[index_sub-1]->left == path[index_sub])
				path[index_sub-1]->left = NULL;
			else
				path[index_sub-1]->right = NULL;
			free(tree->root);
			path[index] = temp;
			tree->root = temp;
		}
	} else {         // the node has at maximum one child
		if(path[index_sub]->left==NULL && path[index_sub]->right==NULL) {         //no child
			if(index_sub>0) {
				if(path[index_sub-1]->left == path[index_sub]) {
					free(path[index_sub-1]->left);
					path[index_sub-1]->left = NULL;
				} else if(path[index_sub-1]->right == path[index_sub]) {
					free(path[index_sub-1]->right);
					path[index_sub-1]->right = NULL;
				}
				path[index_sub] = NULL;
			}else{
				free(tree->root);
				tree->root=NULL;
				path[index] = NULL;
			}
		} else{         //one child
			if(index_sub>0) {
				if(path[index_sub]->left != NULL) {
					temp = path[index_sub]->left;
				} else {
					temp = path[index_sub]->right;
				}
				if(path[index_sub-1]->left == path[index_sub]) {
					free(path[index_sub-1]->left);
					path[index_sub-1]->left = temp;
				}else{
					free(path[index_sub-1]->right);
					path[index_sub-1]->right = temp;
				}
				path[index_sub] = temp;
			}else{
				if(path[index]->left != NULL)
					temp = path[index]->left;
				else
					temp = path[index]->right;
				free(tree->root);
				tree->root = temp;
				path[index] = temp;
			}
		}
	}
	index = index_sub;         // remove the last element index
	int bf;
	while(index>=0) {         // returning the path, updating the nodes' height and check if is needed to make some rotation.
		//updating the height
		if(path[index]==NULL) {
			--index;
			continue;
		}
		path[index]->height = getMax(getHeight(path[index]->left),getHeight(path[index]->right)) + 1;
		path[index]->size = getSize(path[index]->left)+getSize(path[index]->right);
		//check the balancing factor
		bf = getBF(path[index]);

		// printf("BF %d\n",bf);
		if(bf > 1 && getBF(path[index]->right) >= 0) {         // single left
			single_rotate_left(path[index]);
			bf = getBF(path[index]);
		}
		if(bf < -1 && getBF(path[index]->left) < 0) {         // single right
			// printf("SINGLE RIGHT\n");
			single_rotate_right(path[index]);
			bf = getBF(path[index]);
		}
		if(bf > 1 && getBF(path[index]->right) < 0) {         // double left
			// printf("DOUBLE LEFT\n");
			single_rotate_right(path[index]->right);
			single_rotate_left(path[index]);
			bf = getBF(path[index]);
		}
		if(bf < -1 && getBF(path[index]->left) >= 0) {         // double right
			// printf("DOUBLE RIGHT\n");
			single_rotate_left(path[index]->left);
			single_rotate_right(path[index]);
			bf = getBF(path[index]);
		}
		index--;
	}
	if(path!=NULL)
		free(path);
	path=NULL;
}

//TODO
float getMinCapacityInterval(int p_key, int s_key){         // retorna um vetor com todos os nós que possuem o intervalo
	node_t** queue = (node_t**)malloc(sizeof(node_t*)*(tree->root->size+1));         //malloc the tree's size (worst case).
	float min_cap = tree->capacity;         //the maximum capacity is the tree capacity
	int index=-1,aux=0, size = tree->root->size+1;

	queue[0] = tree->root;

	while(queue[++index] != NULL && index < size) {
		if(queue[index]==NULL) printf("NAO FAZ SENTIDO\n");
		if( p_key<=queue[index]->interval[1] && queue[index]->interval[0]<=s_key && queue[index]->capacity<min_cap) {
			min_cap = queue[index]->capacity;         //get the min capacity of the overlaped node
		}
		if(queue[index]->left!=NULL && p_key <= queue[index]->left->interval[1] && queue[index]->left->interval[0] <= s_key) {
			queue[++aux] = queue[index]->left;
		}
		if(queue[index]->right!=NULL && p_key <= queue[index]->right->interval[1] && queue[index]->right->interval[0] <= s_key) {
			queue[++aux] = queue[index]->right;
		}
	}
	return min_cap;
}

};
}
#endif
