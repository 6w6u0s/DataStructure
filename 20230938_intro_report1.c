#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int score[10]; // 학생 10명의 성적을 저장하는 배열
    int sum = 0; // 성적을 저장하는 변수
    double avg; // 평균 값 변수

    srand(time(NULL)); // 난수 생성 시드설정

    for (int i = 0; i < 10; i++) {  // 반복문 사용하여 학생 점수 합계 계산
        score[i] = rand() % 101; // 0~100사이의 난수 생성
        sum += score[i];
    }

    avg = sum / 10.0; // 평균 계산

    printf("평균점수 : %.2f\n", avg);

    return 0;
}