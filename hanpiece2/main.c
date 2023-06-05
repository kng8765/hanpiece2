/*
    *프로그래밍 실습 한피스2 과제_20190662 김나경
    (2) 항해 O
    (3) 스탯 추가 O
    (4) 보물상자 발견 이벤트 O
    (5) 아이템 발견 이벤트 O
    (6) 전투 이벤트 O
    (7) 전투 결과 정산 O
    (8) 게임 종료 O
    (9) 기타 : 게임 시작 전 BGM 재생(효과음)
             : 아이템(악마열매_방어) 추가
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>

#define LUF_ATTACK 1 // 공격
#define LUF_HOLD 2 // 기모으기

#define CRO_ATTACK 1 // 공격
#define CRO_HOLD 2 // 모래
#define CRO_NONE 3 // 여유

int gold = 1000;
int atk = 0;
int get_gold;
int apple = 0;

typedef struct Player {
    int hp;
    int atk;
    int state;
}Player;

Player luffy, crocodile;

int RandomNumber(int, int);
void intro();
void init();
void print_player_status();
int luffy_action();
void luffy_attack(int);
int crocodile_action();
void crocodile_attack(int);
int check_hp();
void battle();
int regame();

int RandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void intro() {
    //printf("==========한피스 part 2 시작==========\n");
    printf("해적왕이 될 사나이 루피는 \n고잉 메리호를 타고 모험을 떠난다.\n");
    printf("이곳은 험난한 바다 위,\n풍요로운 보물들이 뒤섞인 세계에서\n루피는 과연 해적왕이 될 수있을까 ??!!!.....\n");
    printf("\nPress <Enter> to continue..... \n");
    getchar();
}

void init_stat() {
    gold = 1000;
    atk = 0;
    apple = 0;
}

void init() {
    luffy.hp = RandomNumber(20, 40);
    luffy.atk = RandomNumber(5, 15);
    crocodile.hp = RandomNumber(30, 50);
    crocodile.atk = RandomNumber(10, 20);
    luffy.state = 0;
    crocodile.state = 0;
}

void print_player_status() {
    printf("\n==============================\n");
    printf("Luffy      HP: %d, 공격력: %d", luffy.hp < 0 ? 0 : luffy.hp, luffy.atk, (int)pow(2, luffy.state));
    if (atk > 0) {
        printf(" + %d = %d", atk, luffy.atk + atk);
    }
    printf(", 악마열매 갯수 : %d개", apple);
    if (luffy.state > 0)
        printf(" (기 x %d배 증가) = %d", (int)pow(2, luffy.state), (luffy.atk + atk) * (int)pow(2, luffy.state));
    printf("\nCrocodile  HP: %d, 공격력: %d", crocodile.hp < 0 ? 0 : crocodile.hp, crocodile.atk);
    if (crocodile.state > 0)
        printf(" (모래 상태)");
    printf("\n");
}

int luffy_action() {
    int action;
    printf("==========루피 차례===========\n");
    while (1) {
        printf("1. 공격 !\n2. 기 모으기\n==============================\n");
        printf("\n루피가 할 행동을 선택하세요(1 or 2) >>>> ");
        if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // 입력값 예외 처리
            printf("\n");
            getchar();
            printf("잘못된 입력입니다. 다시 입력하세요.\n=========================\n");
            continue;
        }
        break;
    }
    return action;
}

void luffy_attack(int action) {
    int damage;
    switch (action) {
    case LUF_ATTACK:
        damage = luffy.atk;
        if (atk > 0) {
            damage = luffy.atk + atk;
        }
        printf("\n루피의 공격 : '고무고무 총!' x %d\n", (int)pow(2, luffy.state));
        printf("루피 atk : %d\n\n", luffy.atk + atk);
        damage = damage * (int)pow(2, luffy.state);
        if (crocodile.state > 0) { // 방어력 반감 시킬것인지
            damage = damage / 2;
            printf("크로커다일의 방어로 데미지가 반감됩니다. (데미지 %d)\n", damage);
        }
        printf("크로커다일 %d - %d = %d\n", crocodile.hp, damage, crocodile.hp - damage);
        crocodile.hp -= damage;
        luffy.state = 0;
        break;
    case LUF_HOLD:
        printf("\n루피가 기를 모으고 있습니다...\n");
        luffy.state += 1;
        printf("루피 atk : %d\n\n", (luffy.atk + atk) * (int)pow(2, luffy.state));
        break;
    }
    print_player_status();
}

int crocodile_action() {
    int action = RandomNumber(1, 3);
    crocodile.state = 0;

    if (action == CRO_HOLD) {
        printf("=======크로커다일 차례========\n");
        printf("\n크로커다일이 몸을 모래로 바꿉니다.\n\n");
        crocodile.state = 1;
    }
    else if (action == CRO_NONE) {
        printf("=======크로커다일 차례========\n");
        printf("\n크로커다일이 여유를 부립니다:'니가 칠무해가 뭔지 알어?!\n\n");
    }
    return action;
}

void crocodile_attack(int action) {
    if (action == CRO_ATTACK) {
        printf("=======크로커다일 차례========\n");
        printf("\n크로커다일의 공격 : '사막의 폭풍!'\n");
        if (luffy.state > 0) {
            printf("크로커다일의 공격으로 루피의 모든 기가 사라집니다\n");
            printf("루피 atk : %d\n\n", luffy.atk + atk);
        }
        int damage;
        damage = crocodile.atk;
        if (apple > 0) {
            printf("루피가 악마 열매를 먹어 크로커다일의 공격을 방어하였습니다.\n");
            damage = 0;
            printf("루피 %d - %d = %d\n", luffy.hp, damage, luffy.hp - damage);
            luffy.hp -= damage;
            luffy.state = 0;
            apple--;
        }
        else {
            printf("루피 %d - %d = %d\n", luffy.hp, damage, luffy.hp - damage);
            luffy.hp -= damage;
            luffy.state = 0;
        }
    }
    print_player_status();
}

int check_gold() {
    if (gold <= 0) {
        printf("가진 돈을 모두 잃은 루피는 해적을 은퇴하게 된다...\n");
        return 1;
    }
    else if (gold >= 2000) {
        printf("루피는 %d골드를 모아 해적왕이 되었다고 한다...\n", gold);
        return 1;
    }
    return 0;
}

int check_hp() {
    if (luffy.hp <= 0) {
        printf("=============================\n");
        printf("칠무해의 벽은 너무 높았다ㅠ^ㅠ(루피의 패배) \n\n");
        printf("승자는 크로커다일!\n");
        printf("크로커다일에게 가진 돈을 모두 빼앗겼다!\n");
        gold = 0;

        return 0;
    }
    else if (crocodile.hp <= 0) {
        printf("=============================\n");
        printf("루피가 크로커다일을 쓰러뜨렸다!!(루피의 승리)\n\n");
        printf("승자는 루피!\n");
        get_gold = RandomNumber(500, 1000);
        gold += get_gold;
        printf("크로커다일에게 %d골드를 갈취했다!!\n", get_gold);
        return 0;
    }
    else if (luffy.hp <= 0 && crocodile.hp <= 0) {
        printf("무승부입니다.");
    }
    return 1;
}

void battle() {
    print_player_status();
    do {
        int luffy_act = luffy_action();
        luffy_attack(luffy_act);
        if (!check_hp()) {
            break;
        }
        int cro_act = crocodile_action();
        crocodile_attack(cro_act);
    } while (check_hp());
}

void event() {
    int evt = RandomNumber(1, 4);
    if (evt == 1) { //보물상자
        printf("\n*********************\n보물상자를 발견했다 !\n");
        get_gold = RandomNumber(0, 500);
        printf("보물상자에서 %d골드를 발견했다\n", get_gold);
        gold += get_gold;
        Sleep(3000);
    }
    else if (evt == 2) { //아이템
        printf("\n*********************\n아이템을 발견했다!\n");
        atk = RandomNumber(5, 10);
        printf("루피의 추가 공격력이 %d이(가) 되었다.", atk);
        Sleep(3000);
    }
    else if (evt == 3) { //배틀
        printf("\n*********************\n아니! 저 녀석은 칠무해 크로커다일 !\n");
        init();
        battle();
        Sleep(3000);
    }
    else if (evt == 4) { //아이템 2
        printf("\n*********************\n아이템을 발견했다!\n");
        apple = RandomNumber(1, 3);
        printf("루피가 악마의 열매 %d개를 흭득했다.", apple);
        Sleep(3000);
    }
}

void scrollText() {
    char text[] = "          M         ?";
    int textLength = sizeof(text) - 1;
    int currentPosition = textLength - 1;
    while (!check_gold()) {
        system("cls");
        printf("소지금 : %d골드\n공격력 : %d\n악마열매 : %d (회 방어 가능)\n", gold, atk, apple);

        printf("*********************\n");
        for (int i = 0; i < textLength - 1; i++) {
            if (i == currentPosition && currentPosition == 10) { // 이벤트!
                printf("!");
                event();
                break;
            }
            printf("%c", (i == currentPosition) ? '?' : text[i]);
        }
        printf("\n*********************\n");
        Sleep(200);
        currentPosition--;
        if (currentPosition < 0) {
            currentPosition = textLength - 2;
        }
    }
}

void play_bgm(int bgm[][3], int bgm_length) { //추가요소 : bgm 재생
    printf("==========한피스 part 2 시작===========\n");
    double pitch;
    double scale;
    for (int i = 0; i < bgm_length; i++) {
        pitch = bgm[i][1];
        if (pitch == 0)
            pitch = 0.5;
        switch (bgm[i][0]) {
        case 0:
            Sleep(bgm[i][2]);
            break;
        case 1:
            scale = 215 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        case 2:
            scale = 245 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        case 3:
            scale = 130 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        case 4:
            scale = 145 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        case 5:
            scale = 165 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        case 6:
            scale = 170 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        case 7:
            scale = 190 * pitch;
            Beep((int)scale, bgm[i][2]);
            break;
        }
    }
}

int regame() {
    int restart;
    printf("\n재시작하시겠습니까? (1: 재시작 / 0: 종료) >>> ");
    scanf("%d", &restart);

    if (restart == 1) { // 다시 시작
        printf("게임을 다시 시작합니다.\n");
        system("cls");
        return 1;
    }
    else { // 종료
        printf("게임을 종료합니다.\n");
        return 0;
    }
}

// 계이름, pitch, 진행시간(ms)
// -----------------------
// 도 레 미 파 솔 라 시   쉼표
// 3  4  5  6  7  1  2    0
// -----------------------
// 온   / 2분 / 4분 / 8분 / 16분 음표(밀리초 샘플)
// 1600 / 800 / 400 / 200 / 100
// 
// 악보 (우리의꿈, 직접 샘플로 해봄, 두번째 줄 마디까지)
// https://blog.naver.com/PostView.naver?blogId=hahaha6707&logNo=222493270244
int sheet[][3] = {
    {3, 1, 600 + 200},
    {3, 1, 200},
    {4, 1, 200},
    {5, 1, 200 + 400},
    {3, 1, 200},
    {3, 1, 200 + 200},
    {3, 2, 200 + 200},
    {2, 1, 200 + 1200},

    {0, 1, 400 + 400},
    {2, 1, 400},
    {3, 2, 200},
    {1, 1, 200 + 800},
    {1, 1, 200},
    {6, 1, 200 + 200},
    {4, 1, 200 + 400},
    {2, 0, 200},
    {2, 0, 200 + 200},
    {1, 1, 200 + 200},
    {7, 1, 200 + 800},
};

int main() {
    srand(time(NULL));
    play_bgm(sheet, sizeof(sheet) / sizeof(int) / 2);
    do {
        intro();
        init();
        init_stat();
        scrollText();
    } while (regame());
    return 0;
}