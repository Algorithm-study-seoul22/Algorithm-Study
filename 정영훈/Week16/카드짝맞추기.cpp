/*
ī�� 16���� �޸��� �����Ͽ� 4 x 4 ũ���� ���� ���·� ǥ�õǾ� �ֽ��ϴ�.
�� ī���� �ո鿡�� īī�������� ĳ���� �׸��� �׷��� ������,
8������ ĳ���� �׸��� �׷��� ī�尡 ���� 2�徿 ȭ�鿡 �������� ��ġ�Ǿ� �ֽ��ϴ�.
������ ī�带 2�� �����Ͽ� �ո����� �������� �� ���� �׸��� �׷��� ī���
�ش� ī��� ���� ȭ�鿡�� �������, ���� �׸��� �ƴ϶�� ���� ���·� �޸��� ���̵��� �������ϴ�.
�̿� ���� ������� ��� ī�带 ȭ�鿡�� ������� �ϸ� ������ ����˴ϴ�.

Ŀ���� [Ctrl] Ű�� ����Ű�� ���� �̵��Ǹ� Ű ���۹��� ������ �����ϴ�.
- ����Ű�� ���� 1ĭ �̵�
- [Ctrl] Ű + ����Ű�� �̵�. (���� Ű ���⿡ �ִ� ���� ����� ī��� �� ���� �̵�)
	- ī�尡 ���ٸ� ���� ������ ĭ���� �̵�.
	- ���� �̵� ������ ī�� �Ǵ� �� ������ ���� �̵��� �� ���ٸ� �������� ����.
- ī�带 ������ ���ؼ��� [Enter] Ű�� �Է�

���� ���� �� ī���� ¦�� ���� �� �� ���ŵ� ���¿��� ī�� �ո��� �׸��� �˰� �ִٸ�,
���� ī�带 ��� �����ϴµ� �ʿ��� Ű ���� Ƚ���� �ּڰ��� ���� ������ �մϴ�.
����Ű = 1ȸ
[Enter] Ű = 1ȸ
[Ctrl] Ű + ����Ű = 1ȸ

board = 4 x 4
�� ���Ҵ� 0 �̻� 6������ �ڿ���
0�� ī�尡 ���ŵ� �� ĭ��
1 ~ 6������ �ڿ����� 2���� ��� ������ ���� ���ڴ� ���� �׸��� ī�带 �ǹ���.
*/
#include <bits/stdc++.h>

using namespace std;

constexpr int SIZE = 4;
constexpr int INF = 1 << 30;
constexpr int dr[]{ -1,1,0,0 };
constexpr int dc[]{ 0,0,-1,1 };

struct coord {
	int r, c;
	coord(int r, int c) : r(r), c(c) {}
};
vector<vector<coord>> cards(7); // 1 ~ 6
// cards[i][0] : card��ȣ�� i���� ù ��° ī���� ��ġ(coord)
// cards[i][1] : card��ȣ�� i���� �� ��° ī���� ��ġ(coord)

int minimumCnt{ INF };
int maxCard{ -1 };
int row, col;
vector<int> cardVisit;
vector<int> cardOrder;
vector<vector<int>> originBoard, copyBoard;

int GetDistance(vector<vector<int>>& board, coord start, coord target) {
	vector<vector<int>> visited(SIZE, vector<int>(SIZE, INF));
	queue<coord> q;
	q.push(start);
	visited[start.r][start.c] = 1;
	while (!q.empty()) {
		coord now = q.front(); q.pop();
		if (now.r == target.r && now.c == target.c) {
			break;
		}
		for (int dir{}; dir < SIZE; ++dir) { // ����Ű �̵�
			int nr = now.r + dr[dir], nc = now.c + dc[dir];
			if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) continue;
			if (visited[nr][nc] > visited[now.r][now.c] + 1) {
				q.emplace(nr, nc);
				visited[nr][nc] = visited[now.r][now.c] + 1;
			}
		}

		for (int dir{}; dir < SIZE; ++dir) { // [Ctrl] Ű + ����Ű
			for (int dist{ 1 }; dist < 4; ++dist) {
				int nr = now.r + dr[dir] * dist, nc = now.c + dc[dir] * dist;
				if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) break; // ó������ ���.
				if (board[nr][nc]) { // �߰ߵ� ī�尡 �ְų�
					if (visited[nr][nc] > visited[now.r][now.c] + 1) {
						q.emplace(nr, nc);
						visited[nr][nc] = visited[now.r][now.c] + 1;
					}
					break;
				}
				if ((dir == 0 && nr == 0) || (dir == 1 && nr == SIZE - 1) ||
					(dir == 2 && nc == 0) || (dir == 3 && nc == SIZE - 1)) { // ���̰ų�
					if (visited[nr][nc] > visited[now.r][now.c] + 1) {
						q.emplace(nr, nc);
						visited[nr][nc] = visited[now.r][now.c] + 1;
					}
					break;
				}
			}
		}
	}
	return visited[target.r][target.c] - 1; // -1 �ؾ� �湮Ƚ�� ����� ��ȯ
}

void Simulate(coord now, int orderIndex, int sum) {
	if (orderIndex == maxCard) {
		minimumCnt = min(minimumCnt, sum);
		return;
	}
	for (int t{}; t < 2; ++t) {
		int order = cardOrder[orderIndex], cnt{};

		coord& first = cards[order][t];
		coord& second = cards[order][(t + 1) % 2];

		// now -> first
		cnt += GetDistance(copyBoard, now, first);
		copyBoard[first.r][first.c] = 0;
		// first -> second
		cnt += GetDistance(copyBoard, first, second);
		copyBoard[second.r][second.c] = 0;
		Simulate(second, orderIndex + 1, sum + cnt);

		copyBoard[cards[order][0].r][cards[order][0].c] = order;
		copyBoard[cards[order][1].r][cards[order][1].c] = order;
	}
}

void MakeOrder(int index) {
	if (index == maxCard) {
		coord start{ row,col };
		copyBoard = { begin(originBoard), end(originBoard) };
		Simulate(start, 0, 0);
		return;
	}

	for (int c{ 1 }; c <= maxCard; ++c) {
		if (cardVisit[c]) continue;
		cardVisit[c] = 1;
		cardOrder.push_back(c);
		MakeOrder(index + 1);
		cardVisit[c] = 0;
		cardOrder.pop_back();
	}
}

int solution(vector<vector<int>> board, int r, int c) {
	int answer{};
	for (int n{}; n < SIZE; ++n) {
		for (int m{}; m < SIZE; ++m) {
			if (board[n][m]) {
				cards[board[n][m]].emplace_back(n, m);
				maxCard = max(maxCard, board[n][m]);
			}
		}
	}
	cardVisit.assign(maxCard + 1, 0);
	originBoard = { begin(board), end(board) };
	row = r, col = c;

	MakeOrder(0);

	answer = minimumCnt;
	answer += (maxCard << 1);
	return answer;
}

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	vector<vector<int>> board{ {1,0,0,3}, {2,0,0,0},{0,0,0,2},{3,0,1,0} };
	int r = 1, c = 0;
	cout << solution(board, r, c) << '\n';

	vector<vector<int>> board1{ {3,0,0,2}, {0,0,1,0},{0,1,0,0},{2,0,0,3} };
	int r1 = 0, c1 = 1;
	cout << solution(board1, r1, c1) << '\n';

	return 0;
}