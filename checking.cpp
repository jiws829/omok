#include<stdio.h>
#include<limits.h>

extern int primary;
extern void go(int x, int y);

int checking(int omok[][21], int num) {  //evaluation function 값을 정하는 함수
	int dx[9] = { 0,-1,-1,-1,0,0,1,1,1 };
	int dy[9] = { 0,-1,0,1,-1,1,-1,0,1 };
	int dd[9];  //연속된 갯수를 셈
	int db[9];  //bloc 끝이 막혀있나를 표시

	int x[5] = { 0,0,1,-1,1 }; //가로, 세로, 대각선(오른쪽위 방향), 대각선(오른쪽아래 방향)
	int y[5] = { 0,1,0,1,1 };

	int opp = 3 - num;
	int i, j, k, l;
	int count = 0;

	//교차지점 확인
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (omok[i][j] == num) {
				for (k = 0; k < 9; k++) dd[k] = db[k] = 0;  //dd값 초기화

				for (k = 1; k < 9; k++) {  //k는 방향
					for (l = 0;; l++) { //연속된게 몇개인지 셈
						if (omok[i][j] != omok[i + l * dx[k]][j + l * dy[k]]) break;
					}
					dd[k] = l;  //연속된 갯수 저장
					if (omok[i + l * dx[k]][j + l * dy[k]] == opp || omok[i + l * dx[k]][j + l * dy[k]] == 3) db[k] = 1;  // 막혀있으면 db=1
				}
				int cnt[5][2] = { 0, };  //두번째 colum : 0 다 뚫림 / 1 한쪽 막힘
				for (k = 1; k <= 4; k++) {
					if (dd[k] + dd[9 - k] - 1 >= 5) continue;
					if (db[k] == 1 && db[9 - k] == 1) continue;
					if (db[k] == 0 && db[9 - k] == 0) cnt[dd[k] + dd[9 - k] - 1][0]++;
					else cnt[dd[k] + dd[9 - k] - 1][1]++;
				}

				if (cnt[4][0] >= 2) count += 1000000;  //case 2
				if (cnt[4][0] >= 1 && cnt[3][0] >= 1) count += 1000000; //case 3
				if (cnt[4][0] >= 1 && cnt[3][1] >= 1) count += 70;  //case 4
				if (cnt[3][0] >= 2) {
					if (primary == 1 && num == 1) return INT_MIN;  //33금수
					else count += 1000000;  //case 9
				}
				if (cnt[3][0] == 1 && cnt[2][0] >= 1) count += 21;  //case 10

				if (cnt[3][0] == 1 && cnt[3][1] >= 1) count += 8; //case 14
				if (cnt[2][0] >= 3) count += 10;  //case 11
			}
		}
	}
	if (count >= 1000000) return count;

	//직선 확인
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (omok[i][j] == num) {
				for (k = 1; k <= 4; k++) {  //방향
					if (omok[i - x[k]][j - y[k]] == num) continue;
					for (l = 0;; l++) {
						if (omok[i][j] != omok[i + l * x[k]][j + l * y[k]]) break;
					}
					if (l == 5) return INT_MAX;
					if ((omok[i - x[k]][j - y[k]] == opp || omok[i - x[k]][j - y[k]] == 3) && (omok[i + l * x[k]][j + l * y[k]] == opp || omok[i + l * x[k]][j + l * y[k]] == 3)) continue;
					if (l == 4 && omok[i - x[k]][j - y[k]] == 0 && omok[i + l * x[k]][j + l * y[k]] == 0) count+=1000000; //case 5
					else if (l == 3 && omok[i - x[k]][j - y[k]] == 0 && omok[i + l * x[k]][j + l * y[k]] == 0) count += 10; //case 12
					else if (l == 4 && (omok[i - x[k]][j - y[k]] == 0 || omok[i + l * x[k]][j + l * y[k]] == 0)) count += 9; //case 13
					else if (l == 3 && (omok[i - x[k]][j - y[k]] == 0 || omok[i + l * x[k]][j + l * y[k]] == 0)) count += 3; //case 19
					else if (l == 2 && omok[i - x[k]][j - y[k]] == 0 && omok[i + l * x[k]][j + l * y[k]] == 0) count += 2; //case 20
					else if (l == 2 && (omok[i - x[k]][j - y[k]] == 0 || omok[i + l * x[k]][j + l * y[k]] == 0)) count += 1; //case 21
				}
			}
		}
	}
	if (count >= 1000000) return count;

	

	//띄어진 경우 확인
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (omok[i][j] == num) {
				for (k = 1; k <= 4; k++) {
					if (i + 4 * x[k] < 20 && j + 4 * y[k] < 20) {
						if (omok[i - x[k]][j - y[k]] != num && omok[i + x[k]][j + y[k]] == num && omok[i + 2 * x[k]][j + 2 * y[k]] == num && omok[i + 3 * x[k]][j + 3 * y[k]] == 0 && omok[i + 4 * x[k]][j + 4 * y[k]] == num && omok[i + 5 * x[k]][j + 5 * y[k]] != num) {  //○○○ ○
							if ((omok[i - x[k]][j - y[k]] == opp || omok[i - x[k]][j - y[k]] == 3) && (omok[i + 5 * x[k]][j + 5 * y[k]] == opp || omok[i + 5 * x[k]][j + 5 * y[k]] == 3)) count += 31; //case 8 양쪽 막힘
							else if (omok[i - x[k]][j - y[k]] == 0 && omok[i + 5 * x[k]][j + 5 * y[k]] == 0) count += 33; // case 6 양쪽 뚫림
							else count += 32; //case 7 한쪽만 막힘
						}
						if (omok[i - x[k]][j - y[k]] != num && omok[i + x[k]][j + y[k]] == 0 && omok[i + 2 * x[k]][j + 2 * y[k]] == num && omok[i + 3 * x[k]][j + 3 * y[k]] == num && omok[i + 4 * x[k]][j + 4 * y[k]] == num && omok[i + 5 * x[k]][j + 5 * y[k]] != num) {  //○ ○○○
							if ((omok[i - x[k]][j - y[k]] == opp || omok[i - x[k]][j - y[k]] == 3) && (omok[i + 5 * x[k]][j + 5 * y[k]] == opp || omok[i + 5 * x[k]][j + 5 * y[k]] == 3)) count += 31; //case 8 양쪽 막힘
							else if (omok[i - x[k]][j - y[k]] == 0 && omok[i + 5 * x[k]][j + 5 * y[k]] == 0) count += 33; // case 6 양쪽 뚫림
							else count += 32; //case 7 한쪽만 막힘
						}
					}

					if (i + 3 * x[k] < 20 && j + 3 * y[k] < 20) {
						if (omok[i - x[k]][j - y[k]] != num && omok[i + x[k]][j + y[k]] == num && omok[i + 2 * x[k]][j + 2 * y[k]] == 0 && omok[i + 3 * x[k]][j + 3 * y[k]] == num && omok[i + 4 * x[k]][j + 4 * y[k]] != num) {  //○○ ○
							if ((omok[i - x[k]][j - y[k]] == opp || omok[i - x[k]][j - y[k]] == 3) && (omok[i + 4 * x[k]][j + 4 * y[k]] == opp || omok[i + 5 * x[k]][j + 5 * y[k]] == 3)) continue; //양쪽 막힘
							else if (omok[i - x[k]][j - y[k]] == 0 && omok[i + 4 * x[k]][j + 4 * y[k]] == 0) count += 10; // case 15 양쪽 뚫림
							else count += 6; //case 16 한쪽만 막힘
						}
						if (omok[i - x[k]][j - y[k]] != num && omok[i + x[k]][j + y[k]] == 0 && omok[i + 2 * x[k]][j + 2 * y[k]] == num && omok[i + 3 * x[k]][j + 3 * y[k]] == num && omok[i + 4 * x[k]][j + 4 * y[k]] != num) {  //○ ○○
							if ((omok[i - x[k]][j - y[k]] == opp || omok[i - x[k]][j - y[k]] == 3) && (omok[i + 4 * x[k]][j + 4 * y[k]] == opp || omok[i + 5 * x[k]][j + 5 * y[k]] == 3)) continue; //양쪽 막힘
							else if (omok[i - x[k]][j - y[k]] == 0 && omok[i + 4 * x[k]][j + 4 * y[k]] == 0) count += 10; // case 15 양쪽 뚫림
							else count += 6; //case 16 한쪽만 막힘
						}
					}
				}
			}
		}
	}

	return count;
}