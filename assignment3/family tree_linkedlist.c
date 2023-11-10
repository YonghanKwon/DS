#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct node *treePointer;
typedef struct node {
	char name;
	treePointer father;
	treePointer mother;
}node;

treePointer get_tree() {
	treePointer *tree;
	tree = (treePointer*)malloc(sizeof(node));
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

void free_all(treePointer ptr) {
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			if (ptr->father != NULL) {
				addq(ptr->father);
			}
			if (ptr->mother != NULL) {
				addq(ptr->mother);
			}
			free(ptr);
		}
		else break;
	}
}

int main()
{
	char tree[4];
	int n = 0;
	treePointer A, familytree;

	A = NULL;

	do {
		printf(">>");
		gets(tree);
		{
			if (tree[0] != '$' || tree[1] != '$' || tree[2] != '$') {
				if (n == 0)
				{
					A = get_tree();
					A->name = tree[0];
					A->father = NULL;
					A->mother = NULL;
					if (tree[1] == 'F') {
						A->father = get_tree();
						A->father->father = NULL;
						A->father->mother = NULL;
						A->father->name = tree[2];
					}
					else if (tree[1] == 'M') {
						A->mother = get_tree();
						A->mother->father = NULL;
						A->mother->mother = NULL;
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
							familytree->father = get_tree();
							familytree->father->father = NULL;
							familytree->father->mother = NULL;
							familytree->father->name = tree[2];
						}
						else if (tree[1] == 'M') {
							familytree->mother = get_tree();
							familytree->mother->father = NULL;
							familytree->mother->mother = NULL;
							familytree->mother->name = tree[2];
						}
						levelorderprint(A);
						printf("\n");
						n++;
					}

					else {
						familytree = A;
						A = get_tree();
						A->name = tree[0];
						A->father = NULL;
						A->mother = NULL;

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

	if(A)
	free_all(A);

	return 0;
}