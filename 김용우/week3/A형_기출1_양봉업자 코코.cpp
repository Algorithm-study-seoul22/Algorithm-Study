#include <iostream>
#include <algorithm>

int N, M;	// N: ���� ũ��, M: ���� ũ��
int MAP[16][16];	// ���� ����
int dirY[2][6] = { {-1,0,0,1,1,1},{-1,-1,-1,0,0,1} }, dirX[2][6] = { {0,-1,1,-1,0,1}, {-1,0,1,-1,1,0} };
int visited[16][16];	// �湮 �ߴ���
int maxCost = -21e8;	// ����

void funcY(int y, int x) {	// y�� ����̳� �������� y�� ����� DFS�� ����Ͽ� Ž���� �Ұ���...
	int cost = 0;

	if (y < 1 || x < 1 || y >= N - 1 || x >= M - 1) return;	// y�� �������� y�� ���� �� ���� ��� return

	// y ���
	if (x % 2 == 0) {	// x�� ¦���� ���
		cost += MAP[y][x];
		cost += MAP[y - 1][x - 1];
		cost += MAP[y - 1][x + 1];
		cost += MAP[y + 1][x];
	}
	else {	// x�� Ȧ���� ���
		cost += MAP[y][x];
		cost += MAP[y][x - 1];
		cost += MAP[y][x + 1];
		cost += MAP[y + 1][x];	
	}
	maxCost = std::max(maxCost, cost);

	cost = 0;
	// �������� y ���
	if (x % 2 == 0) {	// x�� ¦���� ���
		cost += MAP[y][x];
		cost += MAP[y - 1][x];
		cost += MAP[y][x - 1];
		cost += MAP[y][x + 1];
	}
	else {	// x�� Ȧ���� ���
		cost += MAP[y][x];
		cost += MAP[y - 1][x];
		cost += MAP[y + 1][x - 1];
		cost += MAP[y + 1][x + 1];
	}
	maxCost = std::max(maxCost, cost);

	return;
}

void func(int y, int x, int d, int cost) {	// ���� y ��ǥ, ���� x ��ǥ, ���õ� �� d, ������� ��� cost

	if (d == 3) {	// d�� 0���� �����Ͽ��� ������ d = 3�̸� 4ĭ ������ ��
		maxCost = std::max(maxCost, cost);	// 4�� �� ���������� maxCost�� ���Ͽ� ����
		return;
	}

	for (int i = 0; i < 6; i++) {
		int newY = y + dirY[(x+1)%2][i];	// �̵��� y��ǥ
		int newX = x + dirX[(x+1)%2][i];	// �̵��� x��ǥ
		int newCost;	// �̵��� �������� ���

		if (newY < 0 || newX < 0 || newY >= N || newX >= M) continue;	// ���� ���
		if (visited[newY][newX] != 0) continue;	// �̹� �湮��

		newCost = cost + MAP[newY][newX];	// �ݾ� ����
		visited[newY][newX] = 1;	// �湮 üũ
		func(newY, newX, d + 1, newCost);
		visited[newY][newX] = 0;	// �湮 ����
	}

	return;
}

int main() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {	// ���� ���� �Է�
		for (int i = 0; i < M; i++) {
			std::cin >> MAP[j][i];
		}
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			visited[j][i] = 1;
			func(j, i, 0, MAP[j][i]);	// (j,i)�������� 4��
			funcY(j, i);	// (j, i)������ y�ڿ� �������� ���
			visited[j][i] = 0;
		}
	}
	std::cout << maxCost;
	return 0;
}