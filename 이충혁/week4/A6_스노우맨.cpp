#include<iostream>
#include<queue>
using namespace std;
const int MAT_MAX = 55;
// 0, 1 (��, �� : �����̵� ), 2, 3 (��, �� : �����̵�)
const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct point
{
	int y, x;
};

struct Info // bfs���� ��ǥ�� ���� �̵� ī��Ʈ 
{
	point pt;
	int cnt;
};

// binary search �� bfs
// 0 ~ ����ũ�� �� ����Ž�� �ϸ� �ּ� ���� ã�´�
// Ž������ mid ������ bfs ������ ������ �����ϴ��� üũ

int N, M; // N: ����ũ��, M: ����ũ��
int MAT[MAT_MAX][MAT_MAX]; // �� ����
point st, ed; // st: ����� ��ġ, ed: ���� ��ġ

int input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAT[i][j];
			if (MAT[i][j] == 2)
				st = { i, j };
			else if (MAT[i][j] == 3)
				ed = { i, j };
		}
	}
	return 0;
}

int bfs(int limit) // lilmit : mid ��
{
	int visited[MAT_MAX][MAT_MAX] = { 0, };
	queue<Info> q;
	q.push({ st, 0 });
	visited[st.y][st.x] = 1;

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		if (now.pt.y == ed.y && now.pt.x == ed.x)
		{
			return 1;
		}

		// ���� �̵�
		for (int i = 0; i < 2; i++)
		{
			if (limit == 0) break; // limit�� 0�̸� �����̵� ����

			Info next;
			next.pt.y = now.pt.y + ry[i];
			next.pt.x = now.pt.x + rx[i];

			if (next.pt.y < 0 || next.pt.y >= N ||
				next.pt.x < 0 || next.pt.x >= M) continue;

			if (visited[next.pt.y][next.pt.x] == 1) continue; 

			if (MAT[next.pt.y][next.pt.x] == 0)
			{
				next.cnt = now.cnt + 1;
				if (next.cnt >= limit) continue; // �����̵� ī��Ʈ�� �Ѱ躸�� ���ų� ũ�� q�� ���� �ʴ´�.
			}
			else
			{
				next.cnt = 0; // 1�� ���̱� ������ cnt �ٽ� 0����
			}
			visited[next.pt.y][next.pt.x] = 1;
			q.push(next);
		}
		// �����̵�
		for (int i = 2; i < 4; i++)
		{
			if (now.cnt > 0) continue; // ���� �̵����̸� �����̵� ���ϱ�
			Info next;
			next.pt.y = now.pt.y + ry[i];
			next.pt.x = now.pt.x + rx[i];

			if (next.pt.y < 0 || next.pt.y >= N ||
				next.pt.x < 0 || next.pt.x >= M) continue;

			if (visited[next.pt.y][next.pt.x] == 1) continue;

			if (MAT[next.pt.y][next.pt.x] == 0) continue;

			next.cnt = 0;
			visited[next.pt.y][next.pt.x] = 1;
			q.push(next);
		}
	}

	return 0;
}

int solve_func()
{
	// binary_search

	int left = 0;
	int right = N - 1;
	int ans = right;

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (bfs(mid))
		{
			ans = mid;
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return ans;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	input();
	cout << solve_func();
	return 0;
}