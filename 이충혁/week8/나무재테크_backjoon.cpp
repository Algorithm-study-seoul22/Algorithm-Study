#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAT_MAX = 13;

const int ry[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
const int rx[] = { 0, 0, -1, 1, 1, -1, 1, -1 };


int N, M, K; // N: ���簢�� ���� ����, M: ������ ����, K: ��� Ű�����
int robot_work[MAT_MAX][MAT_MAX]; // �κ��� �ִ� ��� ����
int land[MAT_MAX][MAT_MAX]; // ���� ���� ��� ��Ȳ
int dead_trees[MAT_MAX][MAT_MAX]; // ���� ���� ����

vector<int> tree[MAT_MAX][MAT_MAX]; // �������� 

struct coordi {
	int y, x;
};

int init()
{
	for (int i = 0; i < MAT_MAX; i++)
	{
		for (int j = 0; j < MAT_MAX; j++)
		{
			land[i][j] = 5;
		}
	}

	return 0;
}

int input()
{
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> robot_work[i][j];
		}
	}

	for (int i = 0; i < M; i++)
	{
		int y, x, age;
		cin >> y >> x >> age;

		tree[y][x].push_back(age);
	}
	return 0;
}

int solve_func()
{
	int ans = 0;

	while (K--)
	{
		memset(dead_trees, 0, sizeof(dead_trees));
		vector<coordi> five_tree; // ���� ���� ����

		// �� : ��� �Կ��� ���� + , �������� ���̱�
		for (int i = 1; i <= N; i++) // i, j �� ��ǥ, k �� ���̰�
		{
			for (int j = 1; j <= N; j++)
			{

				if (tree[i][j].empty()) continue;

				vector<int> temp;

				sort(tree[i][j].begin(),tree[i][j].end()); // ���� ������ ���� ��� �ַ���

				for (int k = 0; k < tree[i][j].size(); k++) 
				{
					if (land[i][j] < tree[i][j][k]) 
					{
						dead_trees[i][j] += tree[i][j][k] / 2; // ��� ������� ������ ���̱�
					}

					else 
					{
						land[i][j] -= tree[i][j][k];
						temp.push_back(tree[i][j][k] + 1);
						if ((tree[i][j][k] + 1) % 5 == 0) // 5�� ��� ���� �� ���� �̸� ��Ƴ�
							five_tree.push_back({ i, j });
					}
				}

				tree[i][j] = temp; // ��Ƴ� ���� 1�� ������ ���� �ٽ� �־��ֱ�
			}
		}

		// ���� : ���� ���� ��� �ֱ�
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (dead_trees[i][j] == 0) continue;
				land[i][j] += dead_trees[i][j];
			}
		}
		// ���� : ���� ����, �����ϴ� ������ ���̰� 5�� ���, ������ ��� ĭ�� ���� 1�� ���� ����
		while (!five_tree.empty())
		{
			coordi now = five_tree.back();
			five_tree.pop_back();

			for (int i = 0; i < 8; i++)
			{
				coordi next;
				next.x = now.x + rx[i];
				next.y = now.y + ry[i];

				if (next.y < 1 || next.y > N || 
					next.x < 1 || next.x > N) continue;

				tree[next.y][next.x].push_back(1);
			}
		}


		// �ܿ� : �κ��� ���� ��� �߰� �� ĭ�� �߰��Ǵ� ��� A[r][c]

		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
				land[i][j] += robot_work[i][j];
		}
	}
	

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			ans += tree[i][j].size();
	}

	return ans;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	init();
	input();
	
	cout << solve_func();

	return 0;
}