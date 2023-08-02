/*
N x N ü����, K���� ��.
�̵������� �����¿�.
��� -> �׳� �ø���
������ -> ����� �ø���
ü���� ����ų� �Ķ��� -> ���� �ݴ�� �� ĭ�̵�(���� �ٲٰ� �Ķ����̸� �̵����� �ʰ� ���⸸ ����)

���� ĭ�� ���� �� �� �̻� �ִ� ���� �Է����� �־����� �ʴ´�.

���� ����Ǵ� �߿� ���� 4�� �̻� ���̴� ���� ������ ����ȴ�.
������ ����Ǵ� ���� ��ȣ�� ���غ���.
�� ���� 1,000���� ũ�ų� ����� ������ ������� �ʴ� ��쿡�� -1�� ���
*/

#include <bits/stdc++.h>

using namespace std;
constexpr int WHITE = 0;
constexpr int RED = 1;
constexpr int BLUE = 2;
constexpr int dx[]{ 0,0,-1,1 };
constexpr int dy[]{ 1,-1,0,0 };

struct piece{
	int num, x, y, d, floor;
	piece(int num, int x, int y, int d, int floor) : num(num), x(x), y(y), d(d), floor(floor) {}
};

bool MovePieces(vector<vector<vector<int>>>& curBoard, vector<piece>& pieces, int px,int py, int nx, int ny) {
	bool gameOver{ false };
	int floor = (int)curBoard[nx][ny].size();
	for (int i{}; i < (int)curBoard[px][py].size(); ++i) {
		int& pIdx = curBoard[px][py][i];
		curBoard[nx][ny].push_back(pIdx);
		pieces[pIdx - 1].x = nx;
		pieces[pIdx - 1].y = ny;
		pieces[pIdx - 1].floor = floor + i;
	}
	if (curBoard[nx][ny].size() >= 4) gameOver = true;
	vector<int>().swap(curBoard[px][py]); // swap with empty vector
	return gameOver;
}

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
	int N, K; // ü���� ũ��, ���� ����
	cin >> N >> K;
	vector<vector<int>> board(N + 2, vector<int>(N + 2, BLUE));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> board[i][j];
		}
	}
	
	vector<vector<vector<int>>> curBoard(N + 2, vector<vector<int>>(N + 2));
	vector<piece> pieces(K, piece(0, 0, 0, 0, 0));
	for (int k{}; k < K;++k) {
		piece& p = pieces[k];
		cin >> p.x >> p.y >> p.d;
		p.d--; // 1 ~ 4 -> 0 ~ 3
		p.num = k + 1;
		curBoard[p.x][p.y].push_back(k + 1); // index�� ����
	}

	int t = 1;
	bool gameOver{ false };
	for (;t<=1000; ++t) {
		for (int k{}; k < K; ++k) { // �� ��
			piece& p = pieces[k]; 
			if (p.floor > 0) continue;
			int nx = p.x + dx[p.d], ny = p.y + dy[p.d];
			if (board[nx][ny] == BLUE) {
				// ���� �ݴ�� �� ĭ�̵�(���� �ٲٰ� �Ķ����̸� �̵����� �ʰ� ���⸸ ����)
				p.d^=1;
				nx = p.x + dx[p.d], ny = p.y + dy[p.d];
				if (board[nx][ny] == BLUE) continue;
			}
			if(board[nx][ny] == RED) {
				// ����� �ø���
				reverse(begin(curBoard[p.x][p.y]), end(curBoard[p.x][p.y]));
				gameOver = MovePieces(curBoard, pieces, p.x, p.y, nx, ny);
			}
			else { // WHITE
				// �׳� �ø���
				gameOver = MovePieces(curBoard, pieces, p.x, p.y, nx, ny);
			}
			if (gameOver) break;
		}
		if (gameOver) break;
	}

	if (gameOver) cout << t << '\n';
	else cout << "-1\n";

	return 0;
}