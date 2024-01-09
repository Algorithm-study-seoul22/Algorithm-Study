#include<iostream>
#include<cstring>
using namespace std;

/*
1. 첫번째 열 부터 탐색
2. 해당 열에서 위에서 아래로 내려가며 탐색, 제일빨리 발견한 곰팡이 채취, 채취 후 빈칸
3. 해당 열에서 채취가 끝나면 곰팡이 이동
4. 입력에서 주어진 방향과 속력으로 이동, 격자판의 벽도달하면 반대로 방향 바꿈, 속력 유지, 방향 바꿀때 시간 안걸림
5. 모든 곰팡이 이동 끝낸후 한칸에 곰팡이 두마리 이상이면 크기가 큰 곰팡이가 다른 곰팡이 잡아먹음
6. 위 모든 과정이 1초가 걸리며, 승용이는 오른쪽 열로 이동해서 위 과정 반복

승용이가 해당 격자판 모든 열 검사하고, 채취한 곰팡이 크기의 총합 구하자

2 <= n, m <= 100
0 <= k <= n*m ( 10000 )
1 ≤ x ≤ n, 1 ≤ y ≤ m, 0 ≤ s ≤ 1000, 1 ≤ d ≤ 4, 1 ≤ b ≤ 10000

d : 1 위, 2 아래, 3 오른, 4 왼

1000ms, 80mb

100 * 100 (격자 크기) * 100 : 완탐 돌려도 1초 이내

*/

enum
{
	DIS_Y = 0,
	DIS_X = 1,
	DIR = 2,
	SIZE = 3
};

const int MAT_SIZE = 111;
const int ry[] = { 0, -1, 1, 0, 0 };
const int rx[] = { 0, 0, 0, 1, -1 };

struct coordi
{
	int y, x;
};

class Mold_collect_class
{
private:
	int n, m; // n : x크기, m: y크기
	int k; // 곰팡이 수
	int mold[MAT_SIZE * MAT_SIZE][4]; // s(움직이는 거리), d(이동방향), b(곰팡이 크기)
	int MAT[MAT_SIZE][MAT_SIZE];
	int pre_MAT[MAT_SIZE][MAT_SIZE];


public:
	int input_func()
	{
		cin >> m >> n >> k;

		int x, y;
		int s, d, b;

		memset(MAT, -1, sizeof(MAT));

		for (int i = 0; i < k; i++)
		{
			int dis;
			cin >> y >> x >> dis >> mold[i][DIR] >> mold[i][SIZE];

			mold[i][DIS_Y] = dis % ((m - 1) * 2);
			mold[i][DIS_X] = dis % ((n - 1) * 2);

			MAT[y][x] = i;
		}


		return 0;
	}

	int mold_move()
	{
		memset(pre_MAT, -1, sizeof(pre_MAT));

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (MAT[i][j] == -1) continue;

				coordi next = { i, j };


				next.y += ry[mold[MAT[i][j]][DIR]] * mold[MAT[i][j]][DIS_Y];
				next.x += rx[mold[MAT[i][j]][DIR]] * mold[MAT[i][j]][DIS_X];

				// 이동과 방향 n,m -1 

				if (next.y < 1)
				{
					next.y = (next.y - 1) * -1 + 1;
					mold[MAT[i][j]][DIR] = 2;

					if (next.y > m)
					{
						next.y = (m * 2 - next.y);
						mold[MAT[i][j]][DIR] = 1;
					}
				}
				else if (next.y > m)
				{
					next.y = (m * 2 - next.y);
					mold[MAT[i][j]][DIR] = 1;

					if (next.y < 1)
					{
						next.y = (next.y - 1) * -1 + 1;
						mold[MAT[i][j]][DIR] = 2;
					}
				}

				if (next.x < 1)
				{
					next.x = (next.x - 1) * -1 + 1;
					mold[MAT[i][j]][DIR] = 3;

					if (next.x > n)
					{
						next.x = (n * 2 - next.x);
						mold[MAT[i][j]][DIR] = 4;
					}
				}
				else if (next.x > n)
				{
					next.x = (n * 2 - next.x);
					mold[MAT[i][j]][DIR] = 4;

					if (next.x < 1)
					{
						next.x = (next.x - 1) * -1 + 1;
						mold[MAT[i][j]][DIR] = 3;
					}
				}


				// 여기에 먼저 들어온 곰팡이가 있나요
				if (pre_MAT[next.y][next.x] != -1)
				{
					if (mold[pre_MAT[next.y][next.x]][SIZE] < mold[MAT[i][j]][SIZE])
						pre_MAT[next.y][next.x] = MAT[i][j];
				}
				else
					pre_MAT[next.y][next.x] = MAT[i][j];
			}
		}

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				MAT[i][j] = pre_MAT[i][j];
			}
		}

		return 0;
	}

	int solve_func()
	{
		int ans = 0;

		for (int j = 1; j <= n; j++)
		{
			// 곰팡이 채취
			for (int i = 1; i <= m; i++)
			{
				if (MAT[i][j] != -1)
				{
					ans += mold[MAT[i][j]][SIZE];

					MAT[i][j] = -1;
					break;
				}
			}

			// 곰팡이 이동
			mold_move();
		}

		return ans;
	}

};

Mold_collect_class mold_collect;

int main()
{

	cin.tie(NULL)->sync_with_stdio(false);

	mold_collect.input_func();
	cout << mold_collect.solve_func();

	return 0;
}