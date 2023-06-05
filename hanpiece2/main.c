/*
    *���α׷��� �ǽ� ���ǽ�2 ����_20190662 �質��
    (2) ���� O
    (3) ���� �߰� O
    (4) �������� �߰� �̺�Ʈ O
    (5) ������ �߰� �̺�Ʈ O
    (6) ���� �̺�Ʈ O
    (7) ���� ��� ���� O
    (8) ���� ���� O
    (9) ��Ÿ : ���� ���� �� BGM ���(ȿ����)
             : ������(�Ǹ�����_���) �߰�
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>

#define LUF_ATTACK 1 // ����
#define LUF_HOLD 2 // �������

#define CRO_ATTACK 1 // ����
#define CRO_HOLD 2 // ��
#define CRO_NONE 3 // ����

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
    //printf("==========���ǽ� part 2 ����==========\n");
    printf("�������� �� �糪�� ���Ǵ� \n���� �޸�ȣ�� Ÿ�� ������ ������.\n");
    printf("�̰��� �賭�� �ٴ� ��,\nǳ��ο� �������� �ڼ��� ���迡��\n���Ǵ� ���� �������� �� �������� ??!!!.....\n");
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
    printf("Luffy      HP: %d, ���ݷ�: %d", luffy.hp < 0 ? 0 : luffy.hp, luffy.atk, (int)pow(2, luffy.state));
    if (atk > 0) {
        printf(" + %d = %d", atk, luffy.atk + atk);
    }
    printf(", �Ǹ����� ���� : %d��", apple);
    if (luffy.state > 0)
        printf(" (�� x %d�� ����) = %d", (int)pow(2, luffy.state), (luffy.atk + atk) * (int)pow(2, luffy.state));
    printf("\nCrocodile  HP: %d, ���ݷ�: %d", crocodile.hp < 0 ? 0 : crocodile.hp, crocodile.atk);
    if (crocodile.state > 0)
        printf(" (�� ����)");
    printf("\n");
}

int luffy_action() {
    int action;
    printf("==========���� ����===========\n");
    while (1) {
        printf("1. ���� !\n2. �� ������\n==============================\n");
        printf("\n���ǰ� �� �ൿ�� �����ϼ���(1 or 2) >>>> ");
        if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // �Է°� ���� ó��
            printf("\n");
            getchar();
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n=========================\n");
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
        printf("\n������ ���� : '���� ��!' x %d\n", (int)pow(2, luffy.state));
        printf("���� atk : %d\n\n", luffy.atk + atk);
        damage = damage * (int)pow(2, luffy.state);
        if (crocodile.state > 0) { // ���� �ݰ� ��ų������
            damage = damage / 2;
            printf("ũ��Ŀ������ ���� �������� �ݰ��˴ϴ�. (������ %d)\n", damage);
        }
        printf("ũ��Ŀ���� %d - %d = %d\n", crocodile.hp, damage, crocodile.hp - damage);
        crocodile.hp -= damage;
        luffy.state = 0;
        break;
    case LUF_HOLD:
        printf("\n���ǰ� �⸦ ������ �ֽ��ϴ�...\n");
        luffy.state += 1;
        printf("���� atk : %d\n\n", (luffy.atk + atk) * (int)pow(2, luffy.state));
        break;
    }
    print_player_status();
}

int crocodile_action() {
    int action = RandomNumber(1, 3);
    crocodile.state = 0;

    if (action == CRO_HOLD) {
        printf("=======ũ��Ŀ���� ����========\n");
        printf("\nũ��Ŀ������ ���� �𷡷� �ٲߴϴ�.\n\n");
        crocodile.state = 1;
    }
    else if (action == CRO_NONE) {
        printf("=======ũ��Ŀ���� ����========\n");
        printf("\nũ��Ŀ������ ������ �θ��ϴ�:'�ϰ� ĥ���ذ� ���� �˾�?!\n\n");
    }
    return action;
}

void crocodile_attack(int action) {
    if (action == CRO_ATTACK) {
        printf("=======ũ��Ŀ���� ����========\n");
        printf("\nũ��Ŀ������ ���� : '�縷�� ��ǳ!'\n");
        if (luffy.state > 0) {
            printf("ũ��Ŀ������ �������� ������ ��� �Ⱑ ������ϴ�\n");
            printf("���� atk : %d\n\n", luffy.atk + atk);
        }
        int damage;
        damage = crocodile.atk;
        if (apple > 0) {
            printf("���ǰ� �Ǹ� ���Ÿ� �Ծ� ũ��Ŀ������ ������ ����Ͽ����ϴ�.\n");
            damage = 0;
            printf("���� %d - %d = %d\n", luffy.hp, damage, luffy.hp - damage);
            luffy.hp -= damage;
            luffy.state = 0;
            apple--;
        }
        else {
            printf("���� %d - %d = %d\n", luffy.hp, damage, luffy.hp - damage);
            luffy.hp -= damage;
            luffy.state = 0;
        }
    }
    print_player_status();
}

int check_gold() {
    if (gold <= 0) {
        printf("���� ���� ��� ���� ���Ǵ� ������ �����ϰ� �ȴ�...\n");
        return 1;
    }
    else if (gold >= 2000) {
        printf("���Ǵ� %d��带 ��� �������� �Ǿ��ٰ� �Ѵ�...\n", gold);
        return 1;
    }
    return 0;
}

int check_hp() {
    if (luffy.hp <= 0) {
        printf("=============================\n");
        printf("ĥ������ ���� �ʹ� ���Ҵ٤�^��(������ �й�) \n\n");
        printf("���ڴ� ũ��Ŀ����!\n");
        printf("ũ��Ŀ���Ͽ��� ���� ���� ��� ���Ѱ��!\n");
        gold = 0;

        return 0;
    }
    else if (crocodile.hp <= 0) {
        printf("=============================\n");
        printf("���ǰ� ũ��Ŀ������ �����߷ȴ�!!(������ �¸�)\n\n");
        printf("���ڴ� ����!\n");
        get_gold = RandomNumber(500, 1000);
        gold += get_gold;
        printf("ũ��Ŀ���Ͽ��� %d��带 �����ߴ�!!\n", get_gold);
        return 0;
    }
    else if (luffy.hp <= 0 && crocodile.hp <= 0) {
        printf("���º��Դϴ�.");
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
    if (evt == 1) { //��������
        printf("\n*********************\n�������ڸ� �߰��ߴ� !\n");
        get_gold = RandomNumber(0, 500);
        printf("�������ڿ��� %d��带 �߰��ߴ�\n", get_gold);
        gold += get_gold;
        Sleep(3000);
    }
    else if (evt == 2) { //������
        printf("\n*********************\n�������� �߰��ߴ�!\n");
        atk = RandomNumber(5, 10);
        printf("������ �߰� ���ݷ��� %d��(��) �Ǿ���.", atk);
        Sleep(3000);
    }
    else if (evt == 3) { //��Ʋ
        printf("\n*********************\n�ƴ�! �� �༮�� ĥ���� ũ��Ŀ���� !\n");
        init();
        battle();
        Sleep(3000);
    }
    else if (evt == 4) { //������ 2
        printf("\n*********************\n�������� �߰��ߴ�!\n");
        apple = RandomNumber(1, 3);
        printf("���ǰ� �Ǹ��� ���� %d���� ŉ���ߴ�.", apple);
        Sleep(3000);
    }
}

void scrollText() {
    char text[] = "          M         ?";
    int textLength = sizeof(text) - 1;
    int currentPosition = textLength - 1;
    while (!check_gold()) {
        system("cls");
        printf("������ : %d���\n���ݷ� : %d\n�Ǹ����� : %d (ȸ ��� ����)\n", gold, atk, apple);

        printf("*********************\n");
        for (int i = 0; i < textLength - 1; i++) {
            if (i == currentPosition && currentPosition == 10) { // �̺�Ʈ!
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

void play_bgm(int bgm[][3], int bgm_length) { //�߰���� : bgm ���
    printf("==========���ǽ� part 2 ����===========\n");
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
    printf("\n������Ͻðڽ��ϱ�? (1: ����� / 0: ����) >>> ");
    scanf("%d", &restart);

    if (restart == 1) { // �ٽ� ����
        printf("������ �ٽ� �����մϴ�.\n");
        system("cls");
        return 1;
    }
    else { // ����
        printf("������ �����մϴ�.\n");
        return 0;
    }
}

// ���̸�, pitch, ����ð�(ms)
// -----------------------
// �� �� �� �� �� �� ��   ��ǥ
// 3  4  5  6  7  1  2    0
// -----------------------
// ��   / 2�� / 4�� / 8�� / 16�� ��ǥ(�и��� ����)
// 1600 / 800 / 400 / 200 / 100
// 
// �Ǻ� (�츮�ǲ�, ���� ���÷� �غ�, �ι�° �� �������)
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