

#include<stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <limits.h>



int Boom[30][16],B_view[30][16];
int Boomlv[3][3] = { {9,9,10},{16,16,40}, {16,30,99} };
int Blv;
int Bx, By; //지뢰 카운트 하는 위치 나타내는 변수
int Cx, Cy; //클릭한 위치 나타내는 변수
int glife; //게임 생명


void initialize();
void display();



void score(char);
void Randboom(); // 지뢰를 랜덤으로 위치를 지정하는 함수
void CountBoom();
void Boomgame();
void ClickBoom();
void CheckB();

// 게임 초기화 설정
void initialize() {
    glife = 1;
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            Boom[i][j] = 0;
            B_view[i][j] = -2;
        }
    }

    Randboom(Boomlv[Blv][2]);

}

// 화면에 배열 출력
void display() {
    system("cls");
    /*
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            printf("%3c", Boom[i][j]+48);
        }
        printf("\n");
    }
    */
    printf("  ");
    for (int j = 0; j < By; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < Bx; i++) {
        printf("%2d", i + 1);
        for (int j = 0; j < By; j++) {
            printf("%3c", B_view[i][j] + 48);
        }
        printf("\n");
    }

}




void Randboom(int bmax) {
    int ranx, rany, bcount;
     do{
        
        ranx = rand() % (Bx);
        rany = rand() % (By);
        if (Boom[ranx][rany] == 0) {
            Boom[ranx][rany] = -1;
        }

        bcount = 0;
        for (int i = 0; i < Bx; i++) {
            for (int j = 0; j < By; j++) {
                if (Boom[i][j] == -1) {
                    bcount += 1;
                }
            }
        }
    }while (bcount < bmax);

    CountBoom();
}

void CountBoom() {
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            if (Boom[i][j] == 0) {//해당 칸이 폭탄이 아닌 경우
                for (int Fx = -1; Fx <= 1; Fx++){
                    if (Fx + i < 0)continue;
                    for (int Fy = -1; Fy <= 1; Fy++) {
                        if (Fy + j < 0)continue;
                        if (Boom[i+Fx][j+Fy] == -1) {
                            Boom[i][j] += 1;
                        }
                    }
                }
            }
        }
    }
}



void Boomgame() {
    Blv = -1;
    do {
        printf("난이도를 선택하세요. 1~3단계\n난이도는 숫자로 입력해주세요.\n예시) 1\n 난이도 : ");
        scanf_s("%d", &Blv);

    } while (Blv < 1 || Blv > 3);
    Blv -= 1;

    Bx = Boomlv[Blv][0];
    By = Boomlv[Blv][1];
    initialize();
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            printf("%3c", Boom[i][j] + 48);
        }
        printf("\n");
    }
    display();
    
    printf("게임을 시작합니다.\n");
    
    while (glife > 0)//게임플레이
    {
        display();
        ClickBoom(Cx,Cy);
        CheckBoom();
    }

    system("cls");
    printf("  ");
    for (int j = 0; j < By; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");
    for (int i = 0; i < Bx; i++) {
        printf("%2d", i + 1);
        for (int j = 0; j < By; j++) {
            printf("%3c", Boom[i][j] + 48);
        }
        printf("\n");
    }

    if (glife == 0) {
        printf("지뢰를 선택하셨습니다. 생명이 하나 소멸됩니다.");
    }
    else {
        printf("게임 클리어! 축하드립니다.");
    }
}

void ClickBoom(int Cx, int Cy) {
    printf("행과 열을 입력해주세요.\n예시)10 8\n입력가능 행 : 1 ~ %d, 입력가능 열: 1 ~ %d\n행 열:", Bx, By);
    scanf_s("%d %d", &Cx, &Cy);
    while (Cx > Bx|| Cx < 1 || Cx > By|| Cy < 1)
    {
        printf("행과 열을 다시 입력해주세요.\n예시)10 8\n입력가능 행 : 1 ~ %d, 입력가능 열: 1 ~ %d\n행 열:", Bx, By);
        scanf_s("%d %d", &Cx, &Cy);
    }
    Cx -= 1;
    Cy -= 1;
    if (Boom[Cx][Cy] == -1) {
        glife -= 1;
    } else if (Boom[Cx][Cy] == 0) {
        B_view[Cx][Cy] = Boom[Cx][Cy];
        for (int Fx = -1; Fx <= 1; Fx++) {
            if (Fx + Cx < 0)continue;
            for (int Fy = -1; Fy <= 1; Fy++) {
                if (Fy + Cy < 0)continue;
                B_view[Fx + Cx][Fy + Cy] = Boom[Fx + Cx][Fy + Cy];
            }
        }
    }else{
        B_view[Cx][Cy] = Boom[Cx][Cy];
    }
    
    return 0;
}

int CheckBoom() {
    int Bcount = 0;
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            if (B_view[Cx][Cy] != Boom[Cx][Cy]) {
                Bcount += 1;
            }
        }
    }
    if (Bcount == Boomlv[Blv][2])
    {
        glife = -1;
    }
}

int main(void)
{
    Boomgame();

    return 0;
}
