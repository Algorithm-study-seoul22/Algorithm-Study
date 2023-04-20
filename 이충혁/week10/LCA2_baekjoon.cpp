#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int TREE_SIZE = 101010;
const int DEPTH_SIZE = 20; // log2(50000) = 15,   15�̻�����
const int NODE_SIZE = 101010;

struct INFO { // LCA ���� 2�� ���
	int a, b;
};


int N, M; // N: ����� ����, M �˰���� ���� ����
int parent[TREE_SIZE][DEPTH_SIZE]; //����� ���̰� ���� �ش��ϴ� �θ� ����
int depth[TREE_SIZE]; // ��� �� ���� ����
vector<int> graph[TREE_SIZE];
vector<INFO> LCA_vals;

int init()
{
	for (int i = 0; i < TREE_SIZE; i++)
	{
		depth[i] = -1;
	}

	depth[1] = 0; // ��Ʈ ��� : 1

	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < N - 1; i++) // (����) Ʈ���� ���� ������ ��� ���� -1 
	{
		int from, to;
		cin >> from >> to;
		graph[from].push_back(to);
		graph[to].push_back(from); // ��������� ����
	}

	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		LCA_vals.push_back({ a, b });
	}
	return 0;
}

int dfs_parent(int now) // �ڽ� ��� ���� ���� ���� + 1�� ����, �ڽĳ���� �������� �θ� ��尪 ����
{
	for (int node : graph[now])
	{
		if (depth[node] == -1)
		{
			depth[node] = depth[now] + 1;
			parent[node][0] = now;
			dfs_parent(node);
		}
	}

	return 0;
}

int connect() // ���� ���� ���� �θ� �� ����
{
	for (int i = 1; i < DEPTH_SIZE; i++)
	{
		for (int now = 2; now <= N; now++)
			parent[now][i] = parent[parent[now][i - 1]][i - 1];
	}
	return 0;
}

int solve_func()
{
	// 1. LCA �ϱ� ���� parent, depth �����
	dfs_parent(1); 
	connect(); 

	for (auto val : LCA_vals)
	{
		// 2. LCA �ϱ� ���� ���� ���߱�
		if (depth[val.a] < depth[val.b]) // ���̰� ū�� a�� �ٲٰ�
		{
			swap(val.a, val.b);
		}

		int dist = depth[val.a] - depth[val.b];

		for (int i = 0; dist != 0; i++)
		{
			if (dist % 2 == 1)
				val.a = parent[val.a][i]; // 2�� �¼� ��ŭ ���� �θ�� ���� �� ���� ���� �̵��� ����
			dist /= 2;
		}

		// 3. ���̸� ������ �� ��尡 ���ٸ� ���� �θ�� b
		if (val.a == val.b)
		{
			cout << val.b << "\n";
			continue;
		}

		// 4. ���̰� ���������� �ö� ����
		for (int i = DEPTH_SIZE - 1; i >= 0; i--) // ���� ���� �� ó�� �����ؼ� ã��
		{
			if (parent[val.a][i] != 0 && parent[val.b][i] != 0 &&
				parent[val.a][i] != parent[val.b][i])
			{
				val.a = parent[val.a][i];
				val.b = parent[val.b][i];
			}
		}

		cout << parent[val.b][0] << "\n";
	}



	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	init();
	input();
	solve_func();

	return 0;
}