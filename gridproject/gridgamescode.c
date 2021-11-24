

#include<stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

//게임 공통 변수
int glife; //게임 생명


//지뢰찾기 게임 개체 전역변수 선언
int Boom[30][16], B_view[30][16]; //Boom은 지뢰와 주변 지뢰수를 저장한 필드, B_view는 플레이어가 보는 필드
int Boomlv[3][3] = { {9,9,10},{16,16,40}, {16,30,99} };
int Blv; // 지뢰찾기 난이도
int Bx, By; //지뢰 카운트 하는 위치 나타내는 변수
int Cx, Cy; //클릭한 위치 나타내는 변수



void B_initialize();
void B_display();
void Randboom(); 
void CountBoom();
void Boomgame();
void ClickBoom();
void CheckBoom();

// 게임 초기화 설정
void B_initialize() {
    glife = 1;
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            Boom[i][j] = 0;
            B_view[i][j] = -2;
        }
    }

    Randboom(Boomlv[Blv][2]);

}

// 화면에 지뢰찾기 배열 출력
void B_display() {
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

//지뢰찾기 필드에 랜덤으로 정해진 개수(bmax)의 지뢰 지정
void Randboom(int bmax) {
    int ranx, rany, bcount;
    bcount = 0;
    while (bcount < bmax) {

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
    }

    CountBoom();
}

//지뢰찾기 필드의 지뢰 개수 세는 함수
void CountBoom() {
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            if (Boom[i][j] == 0) {//해당 칸이 폭탄이 아닌 경우
                for (int Fx = -1; Fx <= 1; Fx++) {
                    if (Fx + i < 0)continue;
                    for (int Fy = -1; Fy <= 1; Fy++) {
                        if (Fy + j < 0)continue;
                        if (Boom[i + Fx][j + Fy] == -1) {
                            Boom[i][j] += 1;
                        }
                    }
                }
            }
        }
    }
}

//지뢰찾기 필드를 선택했을때 함수
void ClickBoom() {
    printf("행과 열을 입력해주세요.\n예시)10 8\n입력가능 행 : 1 ~ %d, 입력가능 열: 1 ~ %d\n행 열:", Bx, By);
    scanf_s("%d %d", &Cx, &Cy);
    while (Cx > Bx || Cx < 1 || Cy > By || Cy < 1 )
    {
        B_display();
        printf("행과 열을 다시 입력해주세요.\n예시)10 8\n입력가능 행 : 1 ~ %d, 입력가능 열: 1 ~ %d\n행 열:", Bx, By);
        scanf_s("%d %d", &Cx, &Cy);
    }
    Cx -= 1;
    Cy -= 1;
    if (Boom[Cx][Cy] == -1) {
        glife -= 1;
    }
    else if (Boom[Cx][Cy] == 0) {
        B_view[Cx][Cy] = Boom[Cx][Cy];
        for (int Fx = -1; Fx <= 1; Fx++) {
            if (Fx + Cx < 0)continue;
            for (int Fy = -1; Fy <= 1; Fy++) {
                if (Fy + Cy < 0)continue;
                B_view[Fx + Cx][Fy + Cy] = Boom[Fx + Cx][Fy + Cy];
            }
        }
    }
    else {
        B_view[Cx][Cy] = Boom[Cx][Cy];
    }

    return 0;
}

//선택한 필드가 지뢰인지 확인하는 함수
void CheckBoom() {
    int Bcount = 0;
    for (int i = 0; i < Bx; i++) {
        for (int j = 0; j < By; j++) {
            if (B_view[i][j] != Boom[i][j]) {
                Bcount += 1;
            }
        }
    }
    if (Bcount == Boomlv[Blv][2])
    {
        glife = -1;
    }
}

//게임 실행 함수
void Boomgame() {
    Blv = -1;
    do {
        printf("난이도를 선택하세요. 1~3단계\n");
        printf("1단계 : 9 * 9 필드, 지뢰 10개\n2단계 : 16 * 16 필드, 지뢰 40개\n3단계 : 16 * 30 필드, 지뢰 99개\n");
        printf("난이도는 숫자로 입력해주세요.\n");
        printf("예시) 1\n");
        printf("난이도 : ");
        scanf_s("%d", &Blv);

    } while (Blv < 1 || Blv > 3);
    Blv -= 1;

    Bx = Boomlv[Blv][0];
    By = Boomlv[Blv][1];
    B_initialize();

    printf("게임을 시작합니다.\n");
    Sleep(1000);
    while (glife > 0)//게임플레이
    {
        B_display();
        ClickBoom(Cx, Cy);
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

//정렬게임 관련 개체 전역변수 선언
int Sort_Field[14][4];
int Sort_Field_count[14];
int Sort_End[14];
int Sort_Level[3] = { 8,11,14 };
int Slv,S_Check;

void S_initialize();
void S_Rand();
void S_Display();
void S_printball(int* Snum);
void S_Change();
void Sortgame();

void S_initialize() {
    glife = 1;
    for (int i = 0; i < Slv; i++)
    {
        Sort_Field_count[i] = -1;
        for (int j = 0; j < 4; j++) {
            Sort_Field[i][j] = 0;
        }
    }

    S_Rand();

}

void S_Rand() {
    for (int i = 1; i <= Sort_Level[Slv]-2; i++) {
        int S_count = 0;
        while (S_count < 4) {
            int ran = rand() % (Sort_Level[Slv] - 2);
            int rani = rand() % (4);
            if (Sort_Field[ran][rani] == 0)
            {
                Sort_Field[ran][rani] = i;
                S_count += 1;
                Sort_Field_count[ran] += 1;
            }
        }
    }

}

void S_printball(int* Snum) {
    if (*Snum == 0) {
        printf("○");
    }
    else if (*Snum == 1) {
        printf("ⓐ");
    }
    else if (*Snum == 2) {
        printf("ⓑ");
    }
    else if (*Snum == 3) {
        printf("ⓒ");
    }
    else if (*Snum == 4) {
        printf("ⓓ");
    }
    else if (*Snum == 5) {
        printf("ⓔ");
    }
    else if (*Snum == 6) {
        printf("ⓕ");
    }
    else if (*Snum == 7) {
        printf("ⓖ");
    }
    else if (*Snum == 8) {
        printf("ⓗ");
    }
    else if (*Snum == 9) {
        printf("ⓚ");
    }
    else if (*Snum == 10) {
        printf("ⓛ");
    }
    else if (*Snum == 11) {
        printf("ⓜ");
    }
    else if (*Snum == 12) {
        printf("ⓝ");
    }
}

void S_Display() {
    for (int i = 0; i < Sort_Level[Slv]; i++)
    {
        printf("%2d |", i + 1);
        for (int j = 0; j < 4; j++) {
            S_printball(&Sort_Field[i][j]);
            printf("|");
        }
        printf("\n");
    }
}

void S_Change() {

}

void Sortgame() {
    Slv = -1;
    do {
        printf("난이도를 선택하세요. 1~3단계\n");
        printf("1단계 : 8개의 비커 6가지의 알파벳 \n2단계 : 11개의 비커 9가지의 알파벳\n3단계 : 14개의 비커 12가지의 알파벳\n");
        printf("난이도는 숫자로 입력해주세요.\n");
        printf("예시) 1\n");
        printf("난이도 : ");
        scanf_s("%d", &Slv);

    } while (Slv < 1 || Slv > 3);
    Slv -= 1;
    S_initialize();
    system("cls");

    while (glife > 0)//게임플레이
    {
        S_Display();
        
    }
    



}


 //메인메뉴
int main(void)
{
    srand(time(NULL)); // 시드값 초기화(랜덤함수를 위한 기초작업)
    printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
    printf("□□□■■■■■■□□■□□□□□□□□□□□■□■□□□■■□□■□□■■■■■■□□□\n");
    printf("□□□■□□□□■□□■■■■■■□□■■■□■□■□□■□□■□■□□□□■■□□□□□\n");
    printf("□□□■□□□□■□□□□□□□□□□□□■□■□■□□□■■□□■□□□■□□■□□□□\n");
    printf("□□□■□□□□■□□■■■■■■□□□□■■■□■□□□□□□□□□□□■□□■□□□□\n");
    printf("□□□■■■■■■□□□□■□□□□□□□■□■□■□□■■■■■■□□■□□□□■□□□\n");
    printf("□□□□□■□□□□□■□□□□□□□□□■□■□■□□■□□□□■□□□□□□□□□□□\n");
    printf("□□□■■■■■■□□■■■■■■□□□□□□■□■□□■■■■■■□□■■■■■■□□□\n");
    printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
    printf("모눈게임즈\n");
    printf("하고 싶은 게임을 선택하세요.\n");
    printf("1.지뢰찾기\n");
    printf("2.정렬게임\n");
    printf("(숫자만 작성해주세요 예시. 1)\n");
    int G_menu = 0;
    scanf_s("%d", &G_menu);
    while (G_menu != 1 && G_menu != 2 ) {
        scanf_s("%d", &G_menu);
        printf("숫자 1또는 2만 입력해주세요.");
    }
   
    if (G_menu == 1) {
        printf("지뢰찾기를 선택하셨습니다.");
        Sleep(1000);
        system("cls");
        
        Boomgame();
    }
    else if (G_menu == 2) {
        printf("정렬게임을 선택하셨습니다.");
        Sleep(1000);
        system("cls");
        
        Sortgame();
    } 

    return 0;
}
