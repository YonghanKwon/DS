#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define MAX_TREE_SIZE 100
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct node *treePointer;
typedef struct node {
	char name;
	treePointer father;
	treePointer mother;
}node;

node f_tree[MAX_TREE_SIZE];

treePointer get_tree(int n) {
	treePointer *tree;
	tree = &(f_tree[n]);
	(&f_tree[n])->father = NULL;
	(&f_tree[n])->mother = NULL;
	return tree;
}

treePointer queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

void addq(treePointer tree) {
	if ((rear + 1) % MAX_QUEUE_SIZE == front) {
		queue_full();
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = tree;
}

int queue_full() {
	printf("queue is full, cannot add element");
	exit(EXIT_FAILURE);
}

treePointer deleteq() {
	treePointer x;

	if (front == rear) {
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	x = queue[front];
	return x;
}

treePointer levelordersearch(treePointer ptr, char c) {
	treePointer free;
	if (!ptr)
		return NULL;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		free = ptr;
		if (ptr != NULL) {
			if (ptr->name == c) {
				for (; free != NULL;) {
					free = deleteq();
				}
				return ptr;
			}
			if (ptr->father != NULL)
				addq(ptr->father);
			if (ptr->mother != NULL)
				addq(ptr->mother);
		}
		else break;
	}
	return NULL;
}

void levelorderprint(treePointer ptr) {
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr != NULL) {
			printf("%c", ptr->name);
			if (ptr->father != NULL) {
				addq(ptr->father);
			}
			if (ptr->mother != NULL) {
				addq(ptr->mother);
			}
		}
		else break;
	}
}


int main()
{
	char tree[4];
	int n = 0;
	treePointer A, familytree;


	do {
		printf(">>");
		gets(tree);
		{
			if (tree[0] != '$' || tree[1] != '$' || tree[2] != '$') {
				if (n == 0)
				{
					A = get_tree(n);
					A->name = tree[0];
					if (tree[1] == 'F') {
						n++;
						A->father = get_tree(n);
						A->father->name = tree[2];
					}
					else if (tree[1] == 'M') {
						A->mother = get_tree(n);
						A->mother->name = tree[2];
					}
					levelorderprint(A);
					printf("\n");
					n++;
				}
				else if (n > 0) {
					familytree = levelordersearch(A, tree[0]);
					if (familytree != NULL) {
						if (tree[1] == 'F') {
							familytree->father = get_tree(n);
							familytree->father->name = tree[2];
						}
						else if (tree[1] == 'M') {
							familytree->mother = get_tree(n);
							familytree->mother->name = tree[2];
						}
						levelorderprint(A);
						printf("\n");
						n++;
					}

					else {
						familytree = A;
						A = get_tree(n);
						A->name = tree[0];

						if (tree[1] == 'F') {
							A->father = levelordersearch(familytree, tree[2]);

						}
						else if (tree[1] == 'M') {
							A->mother = levelordersearch(familytree, tree[2]);
						}
						levelorderprint(A);
						printf("\n");
						n++;
					}
				}
			}
		}
	} while (tree[0] != '$' || tree[1] != '$' || tree[2] != '$');

	return 0;
}