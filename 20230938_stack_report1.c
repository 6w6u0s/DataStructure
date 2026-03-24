int main() {
    Stack s;
    initStack(&s);
    char str[MAX];

    printf("문자열을 입력하세요: ");
    fgets(str, MAX, stdin); 
    //fgets(문자열, 크기, 입력스트림)
    //fgets(배열명, 배열크기, 키보드로입력)
    //scanf는 공백 전까지만 읽는다.
    str[strcspn(str, "\n")] = '\0'; 
    //str에서 \n을 찾아 \0으로 바꾼다
    //strcspn = C String Complement Span의 줄임말
    // strcspn은 str에 문자열에서 \n이 나오는 위치를 반환하고
    // str배열에 그 위치에 있는값을 \0으로 바꿔서 \n을 없앤다.

    // 문자열을 스택에 push
    for (int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }

    // 역순 출력 pop
    printf("거꾸로 출력된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }
    printf("\n");

    return 0;
}