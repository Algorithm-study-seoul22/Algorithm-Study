#include<iostream>
#include<vector>
using namespace std;

// ���� ����ü ( ��ǥ�� ���� )
struct Node {
	int y, x;
	int dir;
	int cnt;
};

// �ѹ� �̵��� MAP ����� ���� ����ü
struct Meet {
	int max, max_index;
	int sum;
};

// ���� ��ǥ�� ���� ����
enum {
	U, D, L, R
};

const int ry[] = { -1, 1, 0, 0 }; // �����¿�
const int rx[] = { 0, 0, -1, 1 };
const int MAX = 110;

int N, M, K; 
vector<Node> micro;

int init()
{
	micro.clear();
	return 0;
}

int input()
{
	Node temp;
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++)
	{
		cin >> temp.y >> temp.x >> temp.cnt >> temp.dir;
		temp.dir--;
		micro.push_back(temp);
	}

	return 0;
}

int solve_func()
{
	int length = micro.size();
	int sum = 0;
	for (int i = 0; i < M; i++)
	{
		Meet MAP[MAX][MAX] = { 0, };

		for (int j = 0; j < length; j++)
		{
			if (micro[j].cnt == 0) continue;

			Node next; // �̵��ϴ� ��ǥ
			next.y = micro[j].y + ry[micro[j].dir];
			next.x = micro[j].x + rx[micro[j].dir];

			//��ǰ�� ���� ���
			if (next.y == 0 || next.y == N - 1 ||
				next.x == 0 || next.x == N - 1)
			{
				micro[j].cnt = micro[j].cnt / 2;

				if (next.y == 0) micro[j].dir = D;
				else if (next.y == N - 1) micro[j].dir = U;
				else if (next.x == 0) micro[j].dir = R;
				else if (next.x == N - 1) micro[j].dir = L;
			}
			// ��ġ�� ���
			else if (MAP[next.y][next.x].sum)
			{
				if (MAP[next.y][next.x].max < micro[j].cnt)
				{
					//MAP�� �ִ� max ���� ���ο� ���� ũ�� MAP�� �̹� index ������ ���� ���� 
					// and sum �� ��������
					MAP[next.y][next.x].max = micro[j].cnt;
					MAP[next.y][next.x].sum += micro[j].cnt;
					micro[j].cnt = MAP[next.y][next.x].sum;

					micro[MAP[next.y][next.x].max_index].cnt = 0; // MAP�� ���� �Ǿ ���� 0����

					MAP[next.y][next.x].max_index = j;
				}
				else
				{
					MAP[next.y][next.x].sum += micro[j].cnt; // MAP�� ����� ���� ���� �߰�
					micro[MAP[next.y][next.x].max_index].cnt += micro[j].cnt;
					micro[j].cnt = 0;
				}
			}
			else
			{
				MAP[next.y][next.x].sum = micro[j].cnt;
				MAP[next.y][next.x].max = micro[j].cnt;
				MAP[next.y][next.x].max_index = j;
			}

			micro[j].y = next.y;
			micro[j].x = next.x;
		}

	}

	for (int j = 0; j < length; j++)
	{
		sum += micro[j].cnt;
	}
	return sum;
}



int main(int argc, char** argv)
{
	//freopen("input.txt", "r", stdin);

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		cout << "#" << test_case << " " << solve_func() << "\n";
	}
	return 0;
}