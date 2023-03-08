#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int MAX_MAT = 10; 
const int MAX = 21e8;

// union find�� Ǭ��
// 1. ������ 2���� ������ (bitmasking ����ؼ�)
// 2. 2���� �������� �� union find�ؼ� �θ� ���� �� Ȯ�� �Ȱ����� �� ����� �� �� �׳� ����ģ��.
// 3. union find �ϸ鼭 ������ ���� �θ� ������ �ǵ� �� �θ��� �����ڼ� �� ���̸� ���

int N; // ������ ����
int MAT[MAX_MAT][MAX_MAT]; // ���� ���� ����
int town[MAX_MAT]; // ���� ������ ��

int init()
{
	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAT[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		cin >> town[i];
	}
	return 0;
}

int parent[2][MAX_MAT];
int pop[2][MAX_MAT];

int Find(int now , int group)
{
	if (now == parent[group][now])
		return now;

	return parent[group][now] = Find(parent[group][now], group);
}

int Union(int a, int b, int group)
{
	int pa = Find(a, group);
	int pb = Find(b, group);

	if (pa == pb) return 0;

	parent[group][pb] = pa;

	// ���� ���� ��ĥ �� pa �� ���� �θ�� ������
	// pa �����ڼ�(pa)�� ��� ���� �ش�. ��ġ�� �ٸ� �ϳ��� 0����

	pop[group][pa] += pop[group][pb];
	pop[group][pb] = 0;

	return 0;
}

int Union_Find(int bit_val)
{
	int group_i, group_j;
	for (int i = 0; i < N; i++)
	{
		group_i = (bit_val >> i) % 2;
		for (int j = 0; j < N; j++)
		{
			if (MAT[i][j] == 0) continue; // ������ �������� edge �� ������ 
			group_j = (bit_val >> j) % 2;
			if (group_i != group_j) continue; // ��� ���� ���� �׷��� �ٸ��� 

			Union(i, j, group_i);
		}
	}
	return 1;
}

int group_check(int bit_val)
{
	int before_index[2] = { -1, -1 }; // ���� [�׷� (0 or 1)] �� �ε��� 
	for (int i = 0; i < N; i++)
	{
		int group = (bit_val >> i) % 2;
		if (before_index[group] == -1)
		{
			before_index[group] = i;
		}
		else
		{
			if (Find(i, group) != Find(before_index[group], group))
				return 0;
		}
	}

	return 1;
}

int pop_diff()
{
	int group_pop[2];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (pop[i][j] != 0)
			{
				group_pop[i] = pop[i][j];
				break;
			}
		}
	}

	return abs(group_pop[0] - group_pop[1]);
}

int solve_func()
{
	// ��Ʈ�������� ������ �� �׷����� ����.
	int bit_val = 1; // ������ �׷��� �ǹ��ϴ� ��, 0���� �������� �ʴ°� 0�� ��� �� �׷��̶�
	int bit_limit = 1; // bit_val <= 2 ^ N - 2 ( -1 ���ϴ� ���� : ��� 1�̸� �ѱ׷�)
	for (int i = 0; i < N; i++)
		bit_limit *= 2; 
	bit_limit = bit_limit - 2;

	int ans = MAX;
	
	for (bit_val; bit_val <= bit_limit; bit_val++) // ��� �׷��� ����� ���� ���ƺ���.
	{
		// union-find �ʱ�ȭ: parent, pop
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < N; j++)
			{
				parent[i][j] = j;
				int group = (bit_val >> j) % 2;
				if (group == i)
					pop[i][j] = town[j];
				else
					pop[i][j] = 0;
			}
		}
		
		Union_Find(bit_val); // �ϴ� �׷��� �ɰ����� �׿� ���� �����ڼ��� ������

		// �α׷����� ������ �;����� ������ ��� �ʰ��ؼ� ������������ Ȯ��
		if (!group_check(bit_val)) continue;

		// �α׷� �ּڰ� ����
		int temp = pop_diff();
		if (ans > temp)
			ans = temp;
	}

	return ans;
}

int main()
{
	//freopen("input.txt", "r", stdin);

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