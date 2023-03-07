#include<iostream>
#include<vector>
using namespace std;

int N, T; // N : ��� ��, T : �� ����
vector<int> person; // ��� ���� ����
vector<int> prefix_sum; // ��� �� ������

int mx = 0;

int input()
{
	int sum = 0;
	prefix_sum.push_back(0); // ���������� �ڸ� �� index: 0 �� 0 �̾�� ��

	cin >> N >> T;
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		person.push_back(temp);
		sum += temp;
		prefix_sum.push_back(sum); // ���� �� ����

		if (mx < temp)
			mx = temp;
	}
	return 0;
}


// �̹� mid�� ���Ϸ� �����°� �������� Ȯ��
int possible_func(int mid)
{
	int sub_num; // ������ ���� ( �׷��� �ڸ��� �������� ���� ī���� �� �� ���� ���ŵ� )
	int team_cnt;

	for (int i = 0; i <= N; i++) // ���� ���� �ٲٱ�
	{
		if (prefix_sum[i] > mid) // ���� ���� ������ ���� ������ �ѵ��̷� ����, mid ���� ũ�� ��
			break;

		team_cnt = 1;
		sub_num = prefix_sum[i];

		for (int j = i + 1; j <= N; j++)
		{
			if (prefix_sum[j] - sub_num > mid) // ���� ���� �κ��� �ִ밪 ���� ũ��
			{
				sub_num = prefix_sum[j - 1]; // ���� ���� �������� ����
				team_cnt++;
			}
		}
		if (prefix_sum[i] + prefix_sum[N] - sub_num > mid) // ������ ���� �� ������ ���������� �ѵ��̶� mid���� ũ�� �ǳ� ��
			continue;

		if (team_cnt <= T)
			return 1;
	}
	return 0;
}


int solve_func()
{
	int left = mx; // �ϳ��� ���� ���� ���ų� Ŀ�� ��
	int right = prefix_sum[N - 1]; // ������ ���� ���� ũ�� �ȵ�
	int ans;

	while (left <= right)
	{
		int mid = (left + right) / 2; 

		if (possible_func(mid))
		{
			ans = mid;
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	cout << ans;
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	input();
	solve_func();
	return 0;
}