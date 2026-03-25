#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

//스택 초기화
void initStack(Stack *s) {
    s->top = -1;
}

//스택이 비었는지 확인
int isEmpty(Stack *s) {
    return s->top == -1;
}

//스택이 가득찼는지 확인
int isFull(Stack *s) {
    return s->top == MAX -1;
}

//스택에 요소를 추가 push
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack OverFlow Cannot Push %d\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

//스택에서 요소를 제거 pop
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow Cannot pop\n");
        return -1;
    }
    return s->data[(s->top)--];
}

//스택의 최상단 요소를 확인 peek
int peek(Stack *s) {
    if(isEmpty(s)) {
        printf("Stack is Empty Cannot peek\n");
        return -1;
    }
    return s->data[s->top];
}

//스택 내용 출력
void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is Empty\n");
        return;
    }
    printf("Stack Content : ");
    for(int i=0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initStack(&s);
    char str[MAX];
    int valid = 1;//괄호 유효 체크하는 변수 
                  // 1은 유효 0은유효안함
    
    printf("문자열을 입력하세요 : ");
    fgets(str, MAX, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    for(int i=0; str[i] != '\0'; i++) {
        char ch = str[i];
        
        //여는괄호 스택에 삽입
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        
        //닫는괄호
        else if (ch ==')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) {
                valid = 0;
                break;
            }
            //닫는 괄호가 나오면스택에서 마지막여는 괄호를 꺼냄
            char cheak = pop(&s);
            
            //꺼낸 여는 괄호와 현재닫는괄호가 맞는지 확인
            if ((ch == ')' && cheak != '(') ||
                (ch == '}' && cheak != '{') ||
                (ch == ']' && cheak != '[')) {
                    valid = 0;
                    break;
                }
        }
    } 
    if (valid && s.top == -1)
        printf("유효한괄호\n");
    else
        printf("유효하지않은 괄호\n");
        
        return 0;
}










