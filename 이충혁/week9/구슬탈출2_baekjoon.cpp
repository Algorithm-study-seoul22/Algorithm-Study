#include<iostream>
#include<string>
#include<queue>
using namespace std;

const int MAT_MAX = 12; // N, M�� �ִ밪
const int CNT_MAX = 12; // �ִ�� ������ �� �ִ� �� : 10 

enum {
	WALL = 1,
	HOLE = 2,
	RED = 3,
	BLUE = 4
};

struct coordi
{
	int y, x;

	bool operator==(coordi next) const
	{
		if (y == next.y && x == next.x)
			return true;
		return false;
	}

	coordi operator+(coordi next)const
	{
		coordi temp;
		temp.y = y + next.y;
		temp.x = x + next.x;
		return temp;
	}
};

const coordi dir[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


struct Info // ���� ��Ȳ red, blue
{
	coordi red;
	coordi blue;
	int cnt;
};

int N, M; // ����, ���� 
int MAT[MAT_MAX][MAT_MAX];

coordi blue_st; // ���� ��������
coordi red_st;

void input()
{
	string str;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		cin >> str;
		for (int j = 0; j < M; j++) // �� = 1, ���� = 2, ������ = 3, �Ķ��� = 4 �� �迭�� ����
		{
			switch (str[j])
			{
			case '#':
				MAT[i][j] = WALL;
				break;
			case 'O':
				MAT[i][j] = HOLE;
				break;
			case 'R':
				MAT[i][j] = RED;
				red_st = { i, j };
				break;
			case 'B':
				MAT[i][j] = BLUE;
				blue_st = { i, j };
			}
		}
	}
	return;
}




int bfs()
{
	queue<Info> q;
	q.push({ red_st, blue_st, 0 });

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		if (now.cnt == 10)
			continue;

		for (int i = 0; i < 4; i++)
		{
			Info next = now; // ���� ť�� ���� ����
			int possible_flag = 1; // �� ��츦 ť�� �־ �Ǵ°��� ���� �÷���
			int answer_flag = 0; // ������ ���� ��� 1

			while (1) // ������ ������ �� ���� ������ ����.
			{
				coordi blue_move, red_move;
				red_move = next.red + dir[i];
				blue_move = next.blue + dir[i];

				if (MAT[blue_move.y][blue_move.x] == HOLE) // �̷��� ť�� �߰� ���� �ʴ´�.
				{
					possible_flag = 0;
					answer_flag = 0; // �̰��� ������ �ȵ����� �ٽ� 0����
					break;
				}
				if (MAT[red_move.y][red_move.x] == HOLE) // ���� Ƚ���� ���� �� ã��
				{
					answer_flag = 1;
				}

				if (MAT[red_move.y][red_move.x] == WALL) // �ش� ��ǥ�� ���̸� �������� �ٲ۴�.
					red_move = next.red;

				if (MAT[blue_move.y][blue_move.x] == WALL)
					blue_move = next.blue;


				if (red_move == blue_move) // ���� ���� �Ķ����� ��ġ�� ���� X Ż��
					break;

				if (red_move == next.red &&
					blue_move == next.blue) // ������ �޶����� ���ٸ� ���� X Ż��
					break;


				next.blue = blue_move; // ����
				next.red = red_move;

			}
			next.cnt++;

			if (answer_flag)
				return next.cnt;
			if (possible_flag)
				q.push(next);

		}
	}

	return -1;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	input();

	cout << bfs();

	return 0;
}