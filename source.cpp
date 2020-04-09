#include<stdio.h>
#include<limits.h>
#include<Windows.h>
#include<time.h>
#pragma warning(disable: 4996)


int omok[21][21];
int time_limit;
int first;
time_t startTime = 0, endTime = 0;   //시간을 세기 위한 시간 변수
float gap;
int primary = 0;  //시작을 컴퓨터가 하는지 표시하는 함수

void go(int x, int y);
void print_board(int omok[][21]);
bool check_omok(int omok[][21], int num);

extern int alpha_beta();
extern int checking(int omok[][21], int num);

int main() {
	
	
	
	do {
		char tt[1001];
		bool time_c=true;
		time_limit = 0;
		go(0, 0);
		printf("시간 제한을 얼마로 하시겠습니까?(단위:sec) :        ");
		go(46, 0);
		scanf("%s", tt);
		for (int i = 0; i < strlen(tt); i++) {
			if (!(tt[i] >= '0' && tt[i] <= '9')) {
				time_c = false; break;
			}
			time_limit *= 10;
			time_limit += tt[i] - '0';
		}
		if (time_c==true) break;
	} while (1);
	do {
		go(0, 1);
		printf("누가 먼저 두시겠습니까?(컴퓨터:1 / 사용자:2) :           ");
		go(47, 1);
		scanf("%d", &first);  //1이면 컴퓨터가 먼저 둠
		if (first == 1) primary = 1;
		if (first == 1 || first == 2) break;
	} while (1);

	int now = first;
	bool finish = false; //오목이 끝났는지 확인하는 변수
	int winner = 0; //승자가 누구인지 표시하는 변수
	int a, b; // 사용자가 둘 위치를 입력받는 변수

	if (primary) {  //컴퓨터 선수일 경우 10/10 자리에 먼저 둔다
		omok[10][10] = 1;
		now = 2;
	}

	print_board(omok); // 보드 그리기

	for (int i = 0; i <= 20; i++) {  //테두리 설정
		omok[i][0] = omok[0][i] = omok[20][i] = omok[i][20] = 3;
	}

	while (1) {

		finish = check_omok(omok, 1);    //오목이 끝났는지 확인
		if (finish == true) {
			winner = 3 - now;

			go(0, 23);
			printf("컴퓨터가 당신을 이겼습니다!!!\n");
			system("pause");

			break;
		}
		finish = check_omok(omok, 2);    //오목이 끝났는지 확인
		if (finish == true) {
			winner = 3 - now;

			go(0, 23);
			printf("당신이 컴퓨터를 이겼습니다!!!\n");
			system("pause");

			break;
		}


		if (now == 1) {  //컴퓨터가 둘 차례
			startTime = clock();
			int v = alpha_beta();
			now = 2;
			go(0, 2);
			print_board(omok); // 보드 그리기

			go(0, 23);
			printf("승률:%d", v);
		}
		else {  //사용자가 둘 차례
			while (1) {
				go(0, 22);
				printf("어디에 두시겠습니까? 세로숫자/가로숫자 형태로 입력해주십시오 :          ");
				go(63, 22);
				char tt[101];
				bool check_a=false, right=true;
				scanf("%s", tt);
				a = b = 0;
				for (int i = 0; i < strlen(tt); i++) {
					if (tt[i] == '/') {
						check_a = true; continue;
					}
					if (!(tt[i] >= '0' && tt[i] <= '9')) {
						right = false;
						break;
					}
					if (check_a == false) { a *= 10; a += tt[i] - '0'; }
					else { b *= 10; b += tt[i] - '0'; }
				}
				if (right==true && check_a==true && a > 0 && b > 0 && a < 20 && b < 20 && omok[a][b] == 0) break;
				else continue;
			}

			omok[a][b] = 2;
			now = 1;
			go(0, 2);
			print_board(omok); // 보드 그리기

		}
	}
}