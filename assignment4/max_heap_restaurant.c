#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_SIZE 10	//heap size+1
#define MAX_QUEUE_SIZE 10	//queue size+1
#define HEAP_FULL(n) (n==MAX_HEAP_SIZE-1)
#define HEAP_EMPTY(n) (!n)

typedef struct element {
	int wait_num;
	int peo_num;
}element;

element heap[MAX_HEAP_SIZE];
element queue[MAX_QUEUE_SIZE];

int front = 0;
int rear = 0;

void heap_push(element item, int *n){
	int i;
	if (HEAP_FULL(*n)) {

	}
	i = ++(*n);
	while ((i != 1) && (item.wait_num > heap[i / 2].wait_num)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element heap_pop(int *n)
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n))
	{
		item.peo_num = 5;
		item.wait_num = 0;
		return item;
	}

	item = heap[1];
	//adjust
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].wait_num < heap[child + 1].wait_num))
			child++;
		if (temp.wait_num >= heap[child].wait_num)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void addq(element item){
	if ((rear + 1) % MAX_QUEUE_SIZE == front) {
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = item;
}
element deleteq() {
	element x;

	if (front == rear) {
		x.peo_num = 0;
		x.wait_num = 0;
		return x;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	x = queue[front];
	return x;
}


int main() {

	int select_func,people_num,seat_size;
	int seat_size_success;
	int seat_assign_success=1;
	int waitingNum = 9;
	int heapsize = 0;
	int desk_wait_num = 0;
	element customer;

	printf("Start of Program\n");
	printf("기능:\n");
	printf("0.종료 1.대기접수 2.식탁배정\n");
	printf("식탁 대기수: %d\n",desk_wait_num);
	printf("-------------\n");
	while ((waitingNum!=0)||(desk_wait_num!=0)) {
		printf("기능 선택?:");
		scanf_s("%d", &select_func);
		if (select_func == 0)
		{
			printf("End of Program\n");
			return 0;
		}
		else if (select_func == 1)
		{
			printf("대기번호:%d\n", waitingNum);
			printf("인원수?:");
			scanf_s("%d", &people_num);
			customer.wait_num = waitingNum;
			customer.peo_num = people_num;
			heap_push(customer, &heapsize);
			waitingNum--;
			desk_wait_num++;
			printf("식탁 대기수: %d\n", desk_wait_num);
			printf("-------------\n");

		}
		else if (select_func == 2)
		{
			seat_assign_success = 1;
			printf("식탁 크기?");
			scanf_s("%d", &seat_size);
			do {
				customer = heap_pop(&heapsize);
				if (customer.peo_num > seat_size) {
					addq(customer);
					seat_size_success = 1;
					if (customer.peo_num == 5)
					{
						seat_assign_success = 0;
					}
				}
				else {
					seat_size_success = 0;
					desk_wait_num--;
				}
			} while (seat_size_success&&seat_assign_success);

			if (seat_size_success == 0)
			{
				printf("배정:: 대기번호: %d 인원수: %d\n", customer.wait_num, customer.peo_num);
			}
			else {
				printf("배정불가::\n");
			}

			while (1) {
				customer = deleteq();
				if ((customer.peo_num==0)||(customer.peo_num==5))
					break;
				heap_push(customer, &heapsize);
			}
			

			printf("식탁 대기수: %d\n", desk_wait_num);
			printf("-------------\n");
		}
	}


	return 0;
}