#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAX_MAT = 33;
const int MAX = 21e8;

const int ry[] = { 0, 1 };
const int rx[] = { 1, 0 };

struct point
{
	int y, x;
};

struct Info_route
{
	point to; // ���� ����
	int fuel; // ������� ���� �ϱ� ���� ���� �� 

	bool operator < (Info_route next) const
	{
		if (fuel < next.fuel)
			return false;

		if (fuel > next.fuel)
			return true;

		return false;
	}
};

struct Info_turnel
{
	point pt1, pt2; // �ͳ� �� �Ա�
	int fuel; // �ͳ� ����� ��� ����
};

// ���ͽ�Ʈ��� Ǯ��
// MAT ���� ���� ������ ��� ������ ����
// �ͳε� ������ ���� 1,1 ��ǥ���� ���� �ּҷ� ��� ����� Ž��

int N, M; // N: ���� ���� ����, M: �ͳ��� ����
int MAT[MAX_MAT][MAX_MAT]; // ���� ���� ��
vector<Info_route> graph[MAX_MAT][MAX_MAT]; // ���ͽ�Ʈ�� ��� ����
Info_turnel tunnel[MAX_MAT];


int init()
{
	for (int i = 0; i < MAX_MAT; i++)
		for (int j = 0; j < MAX_MAT; j++)
		{
			MAT[i][j] = -1;
			graph[i][j].clear();

		}

	memset(tunnel, 0, sizeof(tunnel));

	return 0;
}

int input()
{
	cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> MAT[i][j];
	}

	point A, B;
	int fuel;

	for (int i = 0; i < M; i++)
	{
		cin >> A.y >> A.x >> B.y >> B.x >> fuel;

		tunnel[i] = { A, B, fuel };
	}

	return 0;
}


int dijk(point start)
{
	priority_queue<Info_route> pq;
	int fuel[MAX_MAT][MAX_MAT]; // �� ��ǥ���� �ּ� �� �Ǵ� ����� ���� �� ����
	// ��ǥ���� ���� ���� MAX�� �ʱ�ȭ
	for (int i = 0; i < MAX_MAT; i++)
		for (int j = 0; j < MAX_MAT; j++)
			fuel[i][j] = MAX;

	pq.push({ start, 0 });
	fuel[start.y][start.x] = 0;

	while (!pq.empty())
	{
		Info_route now = pq.top();
		pq.pop();

		// pq���� ���� now ���� �̹� ���� ���ᰡ ��� ��찡 fuel�� ������
		if (fuel[now.to.y][now.to.x] < now.fuel) continue;

		for (int i = 0; i < graph[now.to.y][now.to.x].size(); i++)
		{
			Info_route next = graph[now.to.y][now.to.x][i];
			next.fuel = next.fuel + now.fuel;

			// �̹� Ž�� �� ��ǥ��
			if (fuel[next.to.y][next.to.x] <= next.fuel) continue;

			fuel[next.to.y][next.to.x] = next.fuel;
			pq.push(next);
		}
	}

	return fuel[N][N]; // N, N ���� ª�� ���
}

int solve_func()
{

	// ���ͽ�Ʈ�� �ϱ� ���� ��� ���� ���ֱ� 
	// 1. �������� ���� ��� vector�� ����
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{

			for (int k = 0; k < 2; k++)
			{
				// i, j �� from
				point to;
				to.y = i + ry[k];
				to.x = j + rx[k];

				if (MAT[to.y][to.x] == -1) continue;

				// to �� from ���� ���� ũ�� 
				// �����⿡ ��� ���� = ���� * 2
				// �����⿡ ��� ���� = 0
				if (MAT[to.y][to.x] > MAT[i][j])
				{
					graph[i][j].push_back({ to, (MAT[to.y][to.x] - MAT[i][j]) * 2 });
					graph[to.y][to.x].push_back({ { i, j }, 0 });
				}
				// to �� from ���� ���� ������
				// �����⿡ ��� ���� = 0
				// �����⿡ ��� ���� = ���� * 2
				else if (MAT[to.y][to.x] < MAT[i][j])
				{
					graph[i][j].push_back({ to, 0 });
					graph[to.y][to.x].push_back({ { i, j }, (MAT[i][j] - MAT[to.y][to.x]) * 2 });
				}
				else
				{
					graph[i][j].push_back({ to, 1 });
					graph[to.y][to.x].push_back({ { i, j }, 1 });
				}
			}
		}
	}
	// turnel ��� ���
	for (int i = 0; i < M; i++)
	{
		graph[tunnel[i].pt1.y][tunnel[i].pt1.x].push_back({ tunnel[i].pt2, tunnel[i].fuel });
		graph[tunnel[i].pt2.y][tunnel[i].pt2.x].push_back({ tunnel[i].pt1, tunnel[i].fuel });
	}




	return dijk({ 1, 1 });
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;


	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		cout << "#" << tc << " " << solve_func() << "\n";
	}
	return 0;
}