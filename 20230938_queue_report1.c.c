#include <stdio.h>  
#include<stdlib.h>
#include <stdbool.h>
#define SIZE 30

typedef struct {
    int data[SIZE];
    int front;
    int rear;
}LinearQueue;

void initQueue(LinearQueue *q) { // 큐 초기화
    q->front = 0;
    q->rear = -1; //rear를 -1로설정하여 첫삽입시 0이 되도록함
}

bool isEmpty(LinearQueue* q){
    return q->rear < q->front; //rear 가 fornt보다 작으면 비어있음
}

bool isFull(LinearQueue* q) {
    return q->rear == SIZE -1; //rear가 배열끝에 도달하면 가득 참
}

bool enqueue(LinearQueue* q, int value) {
    if(isFull(q)) {
        printf(">>> Queue is Full. >>>\n");
        return 0;
    }
    q->rear++;
    q->data[q->rear] = value; // rear위치에 데이터 추가
    return true;
}

int dequeue(LinearQueue *q) {
    if(isEmpty(q)) {
        printf(">>> Queue is Empty. >>>\n");
        return -1; // if Queue is empty, return -1
    }
    int value = q->data[q->front];
    q->front++;

    if(isEmpty(q)){
        printf("\n---------------------------------------\n");
        printf(">>> Queue is Empty. Reset Queue. >>>\n");
        printf("\n---------------------------------------\n");
        initQueue(q);
    }
    return value;
}

void printQueue(LinearQueue *q){
    if(isEmpty(q)) {
        printf(">>> Now, This queue is Empty. >>>\n");
        return;
    }
    printf("\n---------------------------------------\n");
    printf(">>> Current State of Queue. (fornt : %d, rear : %d) >>>\n", q->front, q-> rear);
    for (int i = q->front; i<= q->rear; i++) {
        printf("[%3d] ", q->data[i]);
    }
    printf("\n---------------------------------------\n");
}

int main()
{   
    LinearQueue q;
    initQueue(&q);
    int meun = 0;
    int number =0;
    
    while(1) {
        printf("\n-----Queue Management Program>-----\n");
        printf("1. Enqueue.\n");
        printf("2. Dequeue.\n");
        printf("3. Print Queue.\n");
        printf("4. Exit.\n");
        printf("Select the meun(int) : ");
        scanf("%d", &meun);
    
        switch(meun) {
            case 1:
                printf(">>> Enter the Number : ");
                scanf("%d", &number);
                enqueue(&q, number);
                break;
            case 2:
                number = dequeue(&q);
                if(number != -1) {
                    printf(">>> Dequeue : %d >>>\n", number);
                }
                break;
            case 3:
                printQueue(&q);
                break;
            case 4:
                printf(">>> Exit Program >>>\n");
                exit(0);
            default:
                printf(">>> Wrong input. Select again. >>>\n");
        }
    }

    return 0;
}
