#include<stdio.h>
#include<limits.h>
#include<time.h>
#include<stdlib.h>

int time_over;
extern int omok[21][21];
int x_saved, y_saved;
extern time_t startTime, endTime;
extern int time_limit;
extern float gap;

extern bool check_omok(int omok[][21], int num);
extern bool check_put(int omok[][21], int x, int y,int num);
extern int checking(int omok[][21], int num);
extern void print_board(int omok[][21]);
extern void go(int x, int y);

int min_value(int alpha, int beta, int deep);
int max_value(int alpha, int beta, int deep);



int terminal_test(int num, int deep) {
	int a, b;
	if (deep == 0) {  //deep이 0이면 종단 노드이므로 evaluation function 값을 반환해야함

		a = check_omok(omok, 2);  //오목이 완성됐는지 확인
		if (a == true) return INT_MIN;
		a = check_omok(omok, 1);
		if (a == true) return INT_MAX;


		a = checking(omok, 1);  //완성 안됐을시 evaluation function을 통해 가중치를 준다
		b = checking(omok, 2);

		if (b == INT_MAX) return INT_MIN;

		if (a == INT_MAX) return INT_MAX;


		return a - b;



	}
	else {  //deep이 0은 아니지만 오목이 완성되었을때의 가중치
		a = check_omok(omok, 2);
		if (a == true) return INT_MIN;
		int a = check_omok(omok, 1);
		if (a == true) return INT_MAX;
	}
}

int min_value(int alpha, int beta, int deep) {
	if (time_over == 1) return INT_MIN;
	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);  //시간 차이 계산
	if (gap >= (float)time_limit) {
		time_over = 1;
		return INT_MIN;
	}

	int a = terminal_test(2, deep);
	if (deep == 0 || a == INT_MAX || a == INT_MIN) return a;

	int v = INT_MAX, v2;
	int i, j;
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (check_put(omok, i, j,2) && omok[i][j] == 0) {
				omok[i][j] = 2;
				v2 = max_value(alpha, beta, deep - 1);

				omok[i][j] = 0;
				if (time_over == 1) return INT_MIN;
				if (v > v2) v = v2;

				if (v <= alpha) return v;
				if (beta > v) beta = v;
			}
		}
	}
	return v;
}

int max_value(int alpha, int beta, int deep) {
	if (time_over == 1) return INT_MIN;
	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);  //시간 차이 계산
	if (gap >= (float)time_limit) {
		time_over = 1;
		return INT_MIN;
	}

	int a = terminal_test(1, deep);
	if (deep == 0 || a == INT_MAX || a == INT_MIN) return a;

	int v = INT_MIN, v2;
	int i, j;
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (check_put(omok, i, j,1) && omok[i][j] == 0) {
				omok[i][j] = 1;

				v2 = min_value(alpha, beta, deep - 1);
				omok[i][j] = 0;
				if (time_over == 1) return INT_MIN;
				if (v < v2) v = v2;
				if (v >= beta) return v;
				if (alpha < v) alpha = v;
			}
		}
	}
	return v;
}

int first_max(int alpha, int beta, int deep) {  //컴퓨터가 결국 한 수를 두기 위해 처음 시작하는 max_value 함수는 위치를 기억하게끔 따로 만들어둠
	if (time_over == 1) return INT_MIN;
	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);  //시간 차이 계산
	if (gap >= (float)time_limit) {
		time_over = 1;
		return INT_MIN;
	}

	int a = terminal_test(1, deep);
	if (deep == 0 || a == INT_MAX || a == INT_MIN) return a;

	int v = INT_MIN, v2;
	int i, j;
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (omok[i][j] == 0 && check_put(omok, i, j,1)) {
				omok[i][j] = 1;
				v2 = min_value(alpha, beta, deep - 1);

				omok[i][j] = 0;
				if (time_over == 1) return INT_MIN;
				if (v < v2) {
					v = v2;
					x_saved = i;
					y_saved = j;
				}
				if (v >= beta) return v;
				if (alpha < v) alpha = v;
			}
		}
	}
	return v;
}

int alpha_beta() {
	int v = 0;
	int v_last, x_last, y_last;
	int i;
	time_over = 0;
	v_last = 0;
	x_saved = y_saved = -1;
	for (i = 2; ; i += 2) {
		v = first_max(INT_MIN, INT_MAX, i);
		if (v != INT_MIN) {
			v_last = v;
			x_last = x_saved;
			y_last = y_saved;
		}
		if (time_over == 1) { i -= 2; break; }
	}

	if (time_over == 1) {
		go(0, 25);
		printf("%d수까지 계산\n", i);
		v = v_last;
		x_saved = x_last;
		y_saved = y_last;
	}


	if (v == INT_MIN) {  //컴퓨터가 어디에 둬야할지 못찾는 경우
		for (int i = 1; i < 20; i++) {
			for (int j = 1; j < 20; j++) {
				if (check_put(omok, i, j,1)) {
					go(0, 24);
					printf("%2d/%2d에 두었습니다\n", i, j);
					omok[i][j] = 1;
					return 0;
				}
			}
		}
	}
	else {
		go(0, 24);
		printf("%2d/%2d에 두었습니다\n", x_saved,y_saved);
		omok[x_saved][y_saved] = 1;
		return v;
	}
}