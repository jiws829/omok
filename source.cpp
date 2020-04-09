#include<stdio.h>
#include<limits.h>
#include<Windows.h>
#include<time.h>
#pragma warning(disable: 4996)


int omok[21][21];
int time_limit;
int first;
time_t startTime = 0, endTime = 0;   //�ð��� ���� ���� �ð� ����
float gap;
int primary = 0;  //������ ��ǻ�Ͱ� �ϴ��� ǥ���ϴ� �Լ�

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
		printf("�ð� ������ �󸶷� �Ͻðڽ��ϱ�?(����:sec) :        ");
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
		printf("���� ���� �νðڽ��ϱ�?(��ǻ��:1 / �����:2) :           ");
		go(47, 1);
		scanf("%d", &first);  //1�̸� ��ǻ�Ͱ� ���� ��
		if (first == 1) primary = 1;
		if (first == 1 || first == 2) break;
	} while (1);

	int now = first;
	bool finish = false; //������ �������� Ȯ���ϴ� ����
	int winner = 0; //���ڰ� �������� ǥ���ϴ� ����
	int a, b; // ����ڰ� �� ��ġ�� �Է¹޴� ����

	if (primary) {  //��ǻ�� ������ ��� 10/10 �ڸ��� ���� �д�
		omok[10][10] = 1;
		now = 2;
	}

	print_board(omok); // ���� �׸���

	for (int i = 0; i <= 20; i++) {  //�׵θ� ����
		omok[i][0] = omok[0][i] = omok[20][i] = omok[i][20] = 3;
	}

	while (1) {

		finish = check_omok(omok, 1);    //������ �������� Ȯ��
		if (finish == true) {
			winner = 3 - now;

			go(0, 23);
			printf("��ǻ�Ͱ� ����� �̰���ϴ�!!!\n");
			system("pause");

			break;
		}
		finish = check_omok(omok, 2);    //������ �������� Ȯ��
		if (finish == true) {
			winner = 3 - now;

			go(0, 23);
			printf("����� ��ǻ�͸� �̰���ϴ�!!!\n");
			system("pause");

			break;
		}


		if (now == 1) {  //��ǻ�Ͱ� �� ����
			startTime = clock();
			int v = alpha_beta();
			now = 2;
			go(0, 2);
			print_board(omok); // ���� �׸���

			go(0, 23);
			printf("�·�:%d", v);
		}
		else {  //����ڰ� �� ����
			while (1) {
				go(0, 22);
				printf("��� �νðڽ��ϱ�? ���μ���/���μ��� ���·� �Է����ֽʽÿ� :          ");
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
			print_board(omok); // ���� �׸���

		}
	}
}