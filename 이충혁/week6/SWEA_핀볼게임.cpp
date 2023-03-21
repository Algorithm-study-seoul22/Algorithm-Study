#include<iostream>
#include<vector>
using namespace std;

const int MAT_MAX = 110;

enum COORDI_ENUM {
	U, R, D, L
};

const int ry[] = { -1, 0, 1, 0 }; // ���� ��ǥ 12�ú��� �ð����
const int rx[] = { 0, 1, 0, -1 };

// ���� Ž��, �ùķ��̼����� ����
struct coordi {
	int y, x;
	bool operator !=(coordi next) const
	{
		if (y != next.y || x != next.x)
			return true;

		return false;
	}
};

int N;
int MAT[MAT_MAX][MAT_MAX];
vector <coordi> wormhole[15];




int init()
{
	for (int i = 0; i < MAT_MAX; i++)
		for (int j = 0; j < MAT_MAX; j++)
		{
			MAT[i][j] = 5;
		}

	for (int i = 0; i < 10; i++)
		wormhole[i].clear();


	return 0;
}

int input()
{
	cin >> N;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			cin >> MAT[i][j];
			if (MAT[i][j] > 5) // ��Ȧ ���� ���?
			{
				wormhole[MAT[i][j]].push_back({ i, j });
			}
		}

	return 0;
}


// ���� �̵����� ����� ���� ���� �� �Է� �޴´�.
int bump_wall(int& dir, int wall)
{
	switch (wall)
	{
	case 1:
		switch (dir)
		{
		case U:
			dir = (dir + 2) % 4;
			break;
		case D:
			dir = R;
			break;
		case R:
			dir = (dir + 2) % 4;
			break;
		case L:
			dir = U;
			break;
		}
		break;
	case 2:
		switch (dir)
		{
		case U:
			dir = R;
			break;
		case D:
			dir = (dir + 2) % 4;
			break;
		case R:
			dir = (dir + 2) % 4;
			break;
		case L:
			dir = D;
			break;
		}
		break;
	case 3:
		switch (dir)
		{
		case U:
			dir = L;
			break;
		case D:
			dir = (dir + 2) % 4;
			break;
		case R:
			dir = D;
			break;
		case L:
			dir = (dir + 2) % 4;
			break;
		}
		break;
	case 4:
		switch (dir)
		{
		case U:
			dir = (dir + 2) % 4;
			break;
		case D:
			dir = L;
			break;
		case R:
			dir = U;
			break;
		case L:
			dir = (dir + 2) % 4;
			break;
		}
		break;
	case 5:
		dir = (dir + 2) % 4;
		break;

	}
	return 0;
}




// ��ǥ�� �̵���Ű�⸸ �ؼ� ��� �Ⱦ�
int dfs(coordi st, int dir)
{
	int ret = 0;
	coordi now = st;
	coordi temp_worm;

	do
	{
		coordi next = now;
		next.y += ry[dir];
		next.x += rx[dir];

		// ��Ȧ �� ��
		if (MAT[next.y][next.x] == -1) break;

		// ���� �ε����� ��
		if (MAT[next.y][next.x] >= 1 && MAT[next.y][next.x] <= 5)
		{
			// �ݴ� ���� ���ܰ�� �������� �״��
			bump_wall(dir, MAT[next.y][next.x]);

			ret++;
		}

		// ��Ȧ �� ��
		else if (MAT[next.y][next.x] > 5)
		{
			// ��Ȧ �߿� �ٸ� �������� ��ǥ �̵�
			for (int i = 0; i < 2; i++)
			{
				temp_worm = wormhole[MAT[next.y][next.x]][i];
				if (temp_worm.y == next.y && temp_worm.x == next.x) continue;

				now = temp_worm;
			}
			continue;
		}
		// �ϰ͵� �ƴ� ��

		now = next;



	} while (now != st);


	return ret;
}

int solve_func()
{
	int ans = 0;

	for (int i = 1; i <= N; i++) // y��ǥ
	{
		for (int j = 1; j <= N; j++) // x ��ǥ
		{
			if (MAT[i][j] != 0) continue;

			for (int dir = 0; dir < 4; dir++)
			{
				int temp = dfs({ i, j }, dir);

				if (ans < temp)
					ans = temp;
			}

		}
	}


	return ans;
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

		cout << "#" << test_case << " " << solve_func() << "\n";

	}
	return 0;
}