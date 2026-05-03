#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체 정의
typedef struct Node {
    char name[20];      //이름
    char phone[20];     // 전화번호
    struct Node* next;  // 다음 노드의 주소
} Node;

// 출력함수
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }
    printf("NULL\n");
}

// 특정 이름으로 전화번호 검색
void searchContact(Node* head, char* targetName) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->name, targetName) == 0) {
            printf("%s의 전화번호는 %s입니다.\n", targetName, current->phone);
            return;
        }
        current = current->next;
    }
    printf("%s님을 찾을 수 없습니다.\n", targetName);
}

// 동적할당 해제
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

// 첫 번째 노드 삽입 함수
Node* insertLast(Node* head, char* name, char* phone) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;

    // 리스트가 비어 있는 경우
    if (head == NULL) {
        return newNode; // 새 노드가 리스트의 시작점이 됨
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return head;
}

// 특정 이름의 연락처 삭제
Node* deleteContact(Node* head, char* targetName) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return NULL;
    }

    if (strcmp(head->name, targetName) == 0) { // 헤드 노드가 대상 값인 경우
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != NULL && strcmp(current->next->name, targetName) != 0) {
        current = current->next;
    }

    if (current->next == NULL) { // 대상 값을 찾지 못한 경우
        printf("이름 %s를 가진 연락처를 찾을 수 없습니다.\n", targetName);
        return head;
    }

    Node* temp = current->next;  // 삭제할 노드
    current->next = current->next->next; // 링크 재조정
    free(temp);                   // 삭제할 노드 메모리 해제

    return head;
}

int main() {
    Node* head = NULL; // 초기화된 리스트

    // 1. 새로운 연락처 추가
    head = insertLast(head, "가나다", "010-1111-1111");
    head = insertLast(head, "라마바", "010-2222-2222");
    head = insertLast(head, "사아차", "010-3333-3333");

    // 4. 현재 전화번호부 출력
    printf("--- 현재 전화번호부 ---\n");
    printList(head);
    printf("----------------------\n");

    // 2. 특정 이름의 연락처 검색
    searchContact(head, "가나다");

    // 3. 특정 이름의 연락처 삭제
    head = deleteContact(head, "라마바");

    // 삭제 후 결과 출력
    printf("\n--- 삭제 후 전화번호부 ---\n");
    printList(head);
    printf("------------------------\n");

    // 모든 리스트 메모리 해제
    freeList(head);

    return 0;
}