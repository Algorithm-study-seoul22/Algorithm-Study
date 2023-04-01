#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>
using namespace std;

const int MAT_MAX = 25;

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct coordi {
	int y, x;

	bool operator != (coordi next) const
	{
		if (y != next.y || x != next.x)
			return true;

		return false;
	}

	bool operator == (coordi next) const
	{
		if (y == next.y && x == next.x)
			return true;

		return false;
	}
};

struct Info
{
	coordi pt;
	int cnt;
};

int N, M; // N : ��ũ��, M : �°� ��
int MAT[MAT_MAX][MAT_MAX]; // �� ����
coordi taxi; //  �ý� ��ǥ 
int fuel; // �ý� ����
vector<coordi> pas_st, pas_ed; // �°� ���� ( �����, ������ )

void init()
{
	for (int i = 0; i < MAT_MAX; i++)
		for (int j = 0; j < MAT_MAX; j++)
			MAT[i][j] = 1;
	return;
}

int input()
{
	cin >> N >> M;
	cin >> fuel;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> MAT[i][j];
		}
	}

	cin >> taxi.y >> taxi.x;

	for (int i = 0; i < M; i++)
	{
		coordi st, ed;
		cin >> st.y >> st.x;
		cin >> ed.y >> ed.x;

		pas_st.push_back(st);
		pas_ed.push_back(ed);

	}

	return 0;
}

int pas_sel; // ������ �°�
unordered_set<int> us; // �°��� ſ���� ��ſ���� set����

// ������ ���Ϳ�, �°��� �ִ���
int bfs(vector<coordi>& ed, int exist)
{
	queue<Info> q;
	q.push({ taxi, 0 });
	int visited[MAT_MAX][MAT_MAX] = { 0, };
	visited[taxi.y][taxi.x] = 1;
	int pas_find = -1; // �մ��� ã�Ұ� �� �մ��� index
	int pas_dis; // ž�� �մ��� �Ÿ�

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		for (int i = 0; i < ed.size(); i++)
		{
			if (ed[i] != now.pt) continue;

			if (!exist) // ž�°� ���� ����
			{
				if (us.find(i) != us.end()) continue;
				if (pas_find < 0) // �� �Ÿ��� �°� ù �߰�
				{
					pas_find = i;
					pas_dis = now.cnt;

					us.insert(pas_find);
					pas_sel = pas_find;
					taxi = ed[pas_find];

					fuel -= now.cnt;
				}
				else
				{
					if (pas_dis < now.cnt)
					{
						us.insert(pas_find);
						pas_sel = pas_find;
						taxi = ed[pas_find];
						return 1;
					}

					int change_flag = 0;
					// ����
					if (pas_st[pas_find].y > pas_st[i].y)
					{
						change_flag = 1;
					}
					else if (pas_st[pas_find].y == pas_st[i].y)
					{
						if (pas_st[pas_find].x > pas_st[i].x)
						{
							change_flag = 1;
						}
					}


					if (change_flag)
					{
						us.erase(pas_find);
						pas_find = i;

						us.insert(pas_find);
						pas_sel = pas_find;
						taxi = ed[pas_find];
					}
				}


			}
			else // �������� ����
			{
				fuel += now.cnt;
				taxi = ed[i];
				return 1;
			}
		}

		// ���� �� �� �� ���� ���� ����
		if (now.cnt == fuel) continue;

		for (int i = 0; i < 4; i++)
		{
			coordi next = { ry[i], rx[i] };
			next.y += now.pt.y;
			next.x += now.pt.x;

			if (MAT[next.y][next.x] == 1) continue;
			if (visited[next.y][next.x] == 1) continue;

			visited[next.y][next.x] = 1;
			q.push({ next, now.cnt + 1 });
		}
	}

	if (pas_find < 0)

		return 0;

	return 1;
}


int solve_func()
{
	while (pas_st.size() != us.size())
	{
		if (!bfs(pas_st, 0))
			return -1;

		vector<coordi> sel_ed{ pas_ed[pas_sel] }; // �������� ������ ����.

		if (!bfs(sel_ed, 1))
			return -1;

	}

	return fuel;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	init();
	input();


	cout << solve_func();
	return 0;
}