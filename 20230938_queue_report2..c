#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  // 최대 작업 대기열 크기

// 프린터 작업 구조체
typedef struct {
    char documentName[50];  // 문서 이름
    int numPages;  // 문서 페이지 수
} PrintJob;

typedef struct {
    PrintJob joblist[SIZE];  // 작업 대기열 배열
    int front;  // 첫 번째 작업 인덱스
    int rear;   // 마지막 작업 인덱스
} PrintQueue;

// 초기화 함수
void initQueue(PrintQueue *q) {
    q->front = 0;
    q->rear = 0;
}

// 큐가 비어 있는지 확인
bool isEmpty(PrintQueue *q) {
    return q->front == q->rear;
}

// 큐가 가득 찼는지 확인
bool isFull(PrintQueue *q) {
    return (q->rear + 1) % SIZE == q->front;
}

// 작업 추가 함수
bool enqueue(PrintQueue *q, char *documentName, int numPages) {
    if (numPages > 50) {
        printf("ERROR! 페이지 수가 50장을 초과합니다.\n");
        return false;
    }
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    strcpy(q->joblist[q->rear].documentName, documentName);
    q->joblist[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}

// 작업 제거 함수
PrintJob dequeue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        PrintJob emptyJob = {"", 0};
        return emptyJob;
    }
    PrintJob job = q->joblist[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

// 대기열 상태 출력 함수
void printQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }
    printf("현재 대기 중인 작업:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n", q->joblist[i].documentName, q->joblist[i].numPages);
        i = (i + 1) % SIZE;
    }
}

void cancelJob(PrintQueue *q, char *documentName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있어 취소할 작업이 없습니다.\n");
        return;
    }

    int i = q->front;
    int targeti = -1;

    // 1. strcmp를 이용하여 해당문서 찾기
    while (i != q->rear) {
        if (strcmp(q->joblist[i].documentName, documentName) == 0) {
            targeti = i;
            break;
        }
        i = (i + 1) % SIZE;
    }

    if (targeti == -1) {
        printf("해당 문서 '%s'가 대기열에 없습니다.\n", documentName);
        return;
    }

    // 2. 데이터 당기기 (삭제된 위치부터 rear 전까지)
    for(int i = targeti; i != q->rear; i=(i+1)%SIZE){
        q->joblist[i] = q->joblist[(i+1)%SIZE];
    }

    // 3. rear 위치 조정
    q->rear = (q->rear - 1 + SIZE) % SIZE; 
    //+SIZE를 안해주면rear값에 -1 을 할때 rear의 방이 마이너스가 나올수있음.
    //그래서 %가 나머지만 구하기때문에 rear -1 에 +SIZE를 해주고 %를써서
    //사이즈로 나눈값의 나머지로 가기때문에 음수의 값이 나오는것을 걱정하지않아도됨.
    /////
    //rear위치 조정을 하는 이유 는 삭제한 방의 다음데이터를 삭제한방으로 끌어왔기때문에
    //똑같은 값이 두개가 됨
    // A B C 에서 B를 삭제하면 A C C 가 됨.
    //그래서 rear의 위치를 하나 앞으로 땡겨서 A C 로 만들어주는거임.
    
    printf("작업 '%s'가 취소되어 대기열에서 제거되었습니다.\n", documentName);
}

void clearQueue(PrintQueue *q) {
    initQueue(q);
    printf("대기열 초기화 완료.\n");
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 대기열 출력\n4. 인쇄취소\n5. 대기열 전체 비우기\n6. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("문서 이름: ");
                scanf("%s", documentName);
                printf("페이지 수: ");
                scanf("%d", &numPages);
                enqueue(&q, documentName, numPages);
                break;
            case 2: 
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPages);
                }
                break;
            case 3:
                printQueue(&q);
                break;
            case 4:
                printf("취소할 문서 이름: ");
                scanf("%s", documentName);
                cancelJob(&q, documentName);
                break;
            case 5:
                clearQueue(&q);
                break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
                break;
        }
    }
}