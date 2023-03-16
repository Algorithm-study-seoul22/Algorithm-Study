#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int MAX = 21e8;
const int MAX_MAT = 15;
const int ry[] = { -1, 1, 0 , 0 };
const int rx[] = { 0, 0, -1, 1 };

struct Point {
	int y, x;
};

struct Ans_Info {
	int core_connect; // ����� �ھ�
	int wire_length; // ���� ����
};

// dfs
struct Path_Info {
	int MAT[MAX_MAT][MAX_MAT]; // �� ���� (�Է�)
	Ans_Info current; // ������� ����� �ھ��, ��������
};

int N; // ũ��
vector <Point> core; // �ھ��� ��ǥ�� 
int core_cnt; // �ھ� ����  DFS ������������ ������ vector size() 
// ���°Ŷ� ū ���̰� ����?

Ans_Info ans;
// dfs path �ε� �Է� ��ǥ���� ���� ����
Path_Info path;


int init()
{
	// path ���� �ʱ�ȭ 
	path = { {0,}, {0, 0} };

	ans = { 0, MAX };
	core.clear();
	return 0;
}

int input()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> path.MAT[i][j];
			if (path.MAT[i][j] == 1)
				core.push_back({ i, j });
		}
	}

	core_cnt = core.size();

	return 0;
}

// �� �� �������� ������ ��������
int possible_func(Point now,  int dir)
{
	Point next;
	next = now;
	next.y += ry[dir];
	next.x += rx[dir];

	while (next.y > 0 && next.y <= N &&
		next.x > 0 && next.x <= N)
	{
		if (path.MAT[next.y][next.x] != 0)
			return 0; // �ϳ��� ���� �ִٸ� ���� �ȵ�

		next.y += ry[dir];
		next.x += rx[dir];
	}

	return 1; // ��� ���̽� ��� ���� ����
}

// ���� ���ִ� �Լ�
int connect_func(Point now, int dir)
{
	int ret = 0; // ����� wire �� ��ȯ
	Point next;
	next = now;
	next.y += ry[dir];
	next.x += rx[dir];

	while (next.y > 0 && next.y <= N &&
		next.x > 0 && next.x <= N)
	{
		path.MAT[next.y][next.x] = 1;
		ret++;

		next.y += ry[dir];
		next.x += rx[dir];
	}
	return ret;
}

// ���� �ִ� �Լ�
int sprt_func(Point now, int dir)
{
	Point next;
	next = now;
	next.y += ry[dir];
	next.x += rx[dir];

	while (next.y > 0 && next.y <= N &&
		next.x > 0 && next.x <= N)
	{
		path.MAT[next.y][next.x] = 0;
		next.y += ry[dir];
		next.x += rx[dir];
	}
	return 0;
}

int dfs(int level)
{
	if (level == core_cnt)
	{
		if (ans.core_connect < path.current.core_connect) // �ھ ������ ����Ǹ� ����
		{
			ans = path.current;
		}
		else if (ans.core_connect == path.current.core_connect &&
			ans.wire_length > path.current.wire_length) // ���� �ھ� ������ ���� �������̰� ª���� ����
		{
			ans = path.current;
		}

		return 0;
	}

	Point now = core[level]; // ���� Ž���ϴ� �ھ��� ��ǥ
	
	// ����ġ�� 1.  1, N �� y, x�� ������ �״�� ����� ���μ��� ���� + 1 �ϰ� �״�� ����
	if (now.y == 1 || now.y == N ||
		now.x == 1 || now.x == N)
	{
		path.current.core_connect += 1;
		dfs(level + 1);
		path.current.core_connect -= 1;

		return 0;
	}

	// ����ġ�� 2.  N-1 �� y, x�� "������ ���� ���μ����� �ִ��� Ȯ�� ��" ������ + 1 ����� ���μ��� ����  + 1 �ϰ�
	// MAP ���� ������ ����. MAT �� ������ �߰����� �ʴ°� 1 �κ��� ������ ������ �ھ ������ ���� �����̴�.
	if (now.y == 2 || now.y == N - 1 ||
		now.x == 2 || now.x == N - 1)
	{
		int possible_flag = 0; // ������ ���� ���μ����� ������ flag -> 1
		if (now.y == 2)
		{
			if (path.MAT[1][now.x] == 0)
			{
				possible_flag = 1;
			}
		}
		if (now.y == N - 1)
		{
			if (path.MAT[N][now.x] == 0)
			{
				possible_flag = 1;
			}
		}
		if (now.x == 2)
		{
			if (path.MAT[now.y][1] == 0)
			{
				possible_flag = 1;
			}
		}
		if (now.x == N - 1)
		{
			if (path.MAT[now.y][N] == 0)
			{
				possible_flag = 1;
			}
		}

		if (possible_flag) // �����ϸ� �������� �Ѿ
		{
			path.current.core_connect += 1;
			path.current.wire_length += 1;
			dfs(level + 1);
			path.current.core_connect -= 1;
			path.current.wire_length -= 1;

			return 0;
		}
	}

	dfs(level + 1);

	for (int dir = 0; dir < 4; dir++)
	{
		if (!possible_func(now, dir)) continue;
		
		int temp = connect_func(now, dir);
		path.current.core_connect += 1;
		path.current.wire_length += temp;
		dfs(level + 1);
		path.current.core_connect -= 1;
		path.current.wire_length -= temp;

		sprt_func(now, dir);
	}

	return 0;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		dfs(0);

		cout << "#" << test_case << " " << ans.wire_length << "\n";
	}
	return 0;
}