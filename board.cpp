#include<stdio.h>
#include<Windows.h>

extern int first;
extern int primary;  //시작을 컴퓨터가 하는지 표시하는 함수

void go(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_board(int omok[][21]) {
	int i, j;
	printf("   ");
	for (i = 1; i <= 19; i++) printf("%4d", i);
	printf("\n");
	for (i = 1; i <= 19; i++) {
		printf("%3d ", i);
		for (j = 1; j <= 19; j++) {
			if (omok[i][j] == 0) printf(" ＊ ");
			else if (omok[i][j] == first) printf(" ○ ");
			else if (omok[i][j] == 3-first) printf(" ● ");
		}
		printf("\n");
	}
}

bool check_omok(int omok[][21], int num) {
	int a, b, c, d; //a 가로  b 세로  c 대각선(오른쪽위 방향)   d 대각선(오른쪽아래 방향)

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (omok[i][j] == num) {
				a = b = c = d = 0;
				for (int k = 1; k <= 4; k++) {
					if (j + k < 19 && omok[i][j] == omok[i][j + k]) a++;
					if (i + k < 19 && omok[i][j] == omok[i + k][j]) b++;
					if (i + k < 19 && j - k >= 0 && omok[i][j] == omok[i + k][j - k]) c++;
					if (i + k < 19 && j + k < 19 && omok[i][j] == omok[i + k][j + k]) d++;
				}
				if (a >= 4 || b >= 4 || c >= 4 || d >= 4) return true;
			}
		}
	}
	return false;
}

bool check_put(int omok[][21], int x, int y,int num) {
	int dx[8] = { -1,-1,-1,0,0,1,1,1 };
	int dy[8] = { -1,0,1,-1,1,-1,0,1 };
	int i;
	
	bool flag=false;

	//33금수 체크
	if (primary == 1 && num == 1) {
		int count = 0;
		for (i = 0; i < 8; i++) {
			if (x + 4 * dx[i]>0 && x + 4 * dx[i]<20 && y + 4 * dy[i]>0 && y + 4 * dy[i]<20 && omok[x - dx[i]][y - dy[i]] == 0 && omok[x + dx[i]][y + dy[i]] == 0 && omok[x + 2 * dx[i]][y + 2 * dy[i]] == 1 && omok[x + 3 * dx[i]][y + 3 * dy[i]] == 1 && omok[x + 4 * dx[i]][y + 4 * dy[i]] == 0) count++;
			if (x + 4 * dx[i]>0 && x + 4 * dx[i]<20 && y + 4 * dy[i]>0 && y + 4 * dy[i]<20 && omok[x - dx[i]][y - dy[i]] == 0 && omok[x + dx[i]][y + dy[i]] == 1 && omok[x + 2 * dx[i]][y + 2 * dy[i]] == 0 && omok[x + 3 * dx[i]][y + 3 * dy[i]] == 1 && omok[x + 4 * dx[i]][y + 4 * dy[i]] == 0) count++;
			if (x + 4 * dx[i]>0 && x + 4 * dx[i]<20 && y + 4 * dy[i]>0 && y + 4 * dy[i]<20 && omok[x - dx[i]][y - dy[i]] == 0 && omok[x + dx[i]][y + dy[i]] == 1 && omok[x + 2 * dx[i]][y + 2 * dy[i]] == 1 && omok[x + 3 * dx[i]][y + 3 * dy[i]] == 1 && !(omok[x + 4 * dx[i]][y + 4 * dy[i]] == 2 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 2)) count++;

			if (x - 3 * dx[i]>0 && x - 3 * dx[i]<20 && y - 3 * dy[i]>0 && y - 3 * dy[i]<20 && omok[x - 3 * dx[i]][y - 3 * dy[i]] == 0 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 1 && omok[x - dx[i]][y - dy[i]] == 0 && omok[x + dx[i]][y + dy[i]] == 1 && omok[x + 2 * dx[i]][y + 2 * dy[i]] == 0) count++;
			if (x + 3 * dx[i]>0 && x + 3 * dx[i]<20 && y + 3 * dy[i]>0 && y + 3 * dy[i]<20 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 0 && omok[x - dx[i]][y - dy[i]] == 1 && omok[x + dx[i]][y + dy[i]] == 0 && omok[x + 2 * dx[i]][y + 2 * dy[i]] == 1 && omok[x + 3 * dx[i]][y + 3 * dy[i]] == 0) count++;
			if (x - 3 * dx[i]>0 && x - 3 * dx[i]<20 && y - 3 * dy[i]>0 && y - 3 * dy[i]<20 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 0 && omok[x - dx[i]][y - dy[i]] == 1 && omok[x + dx[i]][y + dy[i]] == 1 && omok[x + 2 * dx[i]][y + 2 * dy[i]] == 0 && !(omok[x + 3 * dx[i]][y + 3 * dy[i]] == 2 && omok[x - 3 * dx[i]][y - 3 * dy[i]] == 2)) count++;

			if (x - 4 * dx[i]>0 && x - 4 * dx[i]<20 && y - 4 * dy[i]>0 && y - 4 * dy[i]<20 && omok[x - 4 * dx[i]][y - 4 * dy[i]] == 0 && omok[x - 3 * dx[i]][y - 3 * dy[i]] == 1 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 0 && omok[x - dx[i]][y - dy[i]] == 1 && omok[x + dx[i]][y + dy[i]] == 0) count++;
			if (x - 4 * dx[i]>0 && x - 4 * dx[i]<20 && y - 4 * dy[i]>0 && y - 4 * dy[i]<20 && omok[x - 4 * dx[i]][y - 4 * dy[i]] == 0 && omok[x - 3 * dx[i]][y - 3 * dy[i]] == 1 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 1 && omok[x - dx[i]][y - dy[i]] == 0 && omok[x + dx[i]][y + dy[i]] == 0) count++;
			if (x - 3 * dx[i]>0 && x - 3 * dx[i]<20 && y - 3 * dy[i]>0 && y - 3 * dy[i]<20 && omok[x - 3 * dx[i]][y - 3 * dy[i]] == 0 && omok[x - 2 * dx[i]][y - 2 * dy[i]] == 1 && omok[x - dx[i]][y - dy[i]] == 1 && omok[x + dx[i]][y + dy[i]] == 0 && !(omok[x + 2 * dx[i]][y + 2 * dy[i]] == 2 && omok[x - 4 * dx[i]][y - 4 * dy[i]] == 2)) count++;
		}
		if (count >= 2) return false;
	}


	for (i = 0; i < 8; i++) {
		if (omok[x + dx[i]][y + dy[i]] == 1 || omok[x + dx[i]][y + dy[i]] == 2) flag = true;
	}
	if (flag == false) return false;

	return true;
}

/*bool check_put(int omok[][21], int x, int y, int num) {
	int dx[8] = { -1,-1,-1,0,0,1,1,1 };
	int dy[8] = { -1,0,1,-1,1,-1,0,1 };
	int i;

	for (i = 0; i < 8; i++) {
		if (omok[x + dx[i]][y + dy[i]] == 1 || omok[x + dx[i]][y + dy[i]] == 2) return true;
	}
	return false;
}*/