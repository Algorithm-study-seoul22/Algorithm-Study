#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

/*
n * n 좌석에 입력 순서대로 학생 들이 앉는다.
3 <= n <= 20

1. 격자 벗어 나지 않게 4방향 인접한 칸 중 좋아하는 친구가 가장 많은 위치로 간다.
2. 1번이 여러개면 그중 인접한 칸 중 비어 있는 칸의 수가 가장 많은 위치로 간다.
3. 2번이 여러개면 행번호 가 가장 작게, 그 다음 열번호가 가장 작게 간다.

최종 점수는 다 탑승 후 주변에 좋아하는 친구의 수 마다 점수가 다르게 합해짐
0 ~ 4 명 순서대로 : 0, 1, 10, 100, 1000


입력되는 정보 저장
좋아하는 친구가 map에 좌표값이 있는지 확인
그 좌표값 상하좌우 4방향에 
1) 자리가 있는지
2) 그 자리에 앉으면 좋아하는 친구가 주변에 몇명인지
3) 빈 공간은 몇갠지
4) 행이랑 열 값은?

이걸 순서대로 따지며 확인 하고 기준에 더 부합하는 값이 있다면 덮어쓰자

위에서 값이 안 정해지면
1) 자리가 있는지
2) 그 자리 주변 빈공간은 몇갠지
3) 행이랑 열 값이 갱신 되야 하는지 
위 규칙으로 다시 찾는다.

최종 행, 열 값이 정해 지면 map 과 seat에 넣자

마지막 input 까지 끝나면 점수를 계산한다.

*/

const int FAVORITE_FRIENDS_SIZE = 4;
const int ry[] = {-1, 1, 0, 0};
const int rx[] = {0, 0, -1, 1};
const int EXTRA_SCORE[] = { 0, 1, 10, 100, 1000 };




struct Studoent_info
{
	int num;
	int freinds[FAVORITE_FRIENDS_SIZE];
};

struct Coordi
{
	int y, x;

	bool operator==(const Coordi &next)const
	{
		if (y == next.y && x == next.x)
			return true;

		return false;
	}
};

const Coordi NOT_COORDI = { 1000, 1000 };

class Amusement_ride
{
private:
	int n;
	vector<Studoent_info> students;
	unordered_map<int, Coordi> um;
	vector<vector<int>> visited;

public:
	int input_func()
	{
		cin >> n;

		students.resize(n * n);
		visited.resize(n);
		for (auto& val : visited)
			val.assign(n, 0);

		for (int i = 0; i < n * n; i++)
		{
			cin >> students[i].num;
			for (int j = 0; j < 4; j++)
				cin >> students[i].freinds[j];
		}

		return 0;
	}

	// 참조로 배열 전달하기 : https://stackoverflow.com/questions/5724171/passing-an-array-by-reference
	int around_friend(const Coordi &pt, const int (&friends)[FAVORITE_FRIENDS_SIZE])
	{
		int ret = 0;

		for (int i = 0; i < 4; i++)
		{
			Coordi around_pt = pt;
			
			around_pt.y += ry[i];
			around_pt.x += rx[i];

			if (around_pt.y < 0 || around_pt.y >= n ||
				around_pt.x < 0 || around_pt.x >= n) continue;

			for (int j = 0; j < 4; j++)
			{
				if (um.find(friends[j]) == um.end()) continue;

				if (um[friends[j]] == around_pt)
				{
					ret++;
					break;
				}
			}
		}

		return ret;
	}

	int around_empty(const Coordi& pt)
	{
		int ret = 0;

		for (int i = 0; i < 4; i++)
		{
			Coordi around_pt = pt;

			around_pt.y += ry[i];
			around_pt.x += rx[i];

			if (around_pt.y < 0 || around_pt.y >= n ||
				around_pt.x < 0 || around_pt.x >= n) continue;

			if (visited[around_pt.y][around_pt.x] == 0)
				ret++;
		}

		return ret;
	}

	int solve_func()
	{
		int ans = 0;

		for (auto& student : students)
		{
			Coordi pt = NOT_COORDI;
			int friend_cnt = -1;
			int empty_cnt = -1;
		
			// 1) 친구가 이미 앉았나?
			for (int i = 0; i < 4; i++)
			{
				if (um.find(student.freinds[i]) == um.end()) continue;

				for (int j = 0; j < 4; j++)
				{
					Coordi next = um[student.freinds[i]];
					
					next.y += ry[j];
					next.x += rx[j];

					if (next.y < 0 || next.y >= n ||
						next.x < 0 || next.x >= n) continue;

					// 2) 빈자리인가?
					if (visited[next.y][next.x] != 0) continue;

					// 3) 좋아하는 친구수가 저장된 수 이상인가?
					int tmp_friend = around_friend(next, student.freinds);
					int tmp_empty = around_empty(next);
					
					if (friend_cnt > tmp_friend) continue;

					else if (friend_cnt == tmp_friend)
					{
						// 4) 빈자리 수가 저장된 수이상인가?
						if (empty_cnt > tmp_empty) continue;

						else if (empty_cnt == tmp_empty)
						{
							// 5) 행열은 작은가?
							if (next.y > pt.y) continue;

							else if (next.y == pt.y)
							{
								if (next.x > pt.x) continue;
							}
						}
					}

					
					pt = next;
					friend_cnt = tmp_friend;
					empty_cnt = tmp_empty;
				}

			}

			// 친구가 안 앉았다면?
			if (pt == NOT_COORDI)
			{
				

				for (int y = 0; y < n; y++)
				{
					for (int x = 0; x < n; x++)
					{
						// 1) 자리가 있는지
						if (visited[y][x] != 0) continue;
						


						// 2) 빈자리 수가 저장된 수이상인가?
						int tmp_empty = around_empty({y, x});
						
						if (empty_cnt > tmp_empty) continue;

						else if (empty_cnt == tmp_empty)
						{
							// 3) 행열은 작은가?
							if (y > pt.y) continue;

							else if (y == pt.y)
							{
								if (x > pt.x) continue;
							}
						}


						pt = { y, x };
						friend_cnt = 0;
						empty_cnt = tmp_empty;
					}
				}
			}
		
			um.insert({ student.num, pt });
			visited[pt.y][pt.x] = student.num;
		}

		for (auto& student : students)
		{
			ans += EXTRA_SCORE[around_friend(um[student.num], student.freinds)];
		}



		return ans;
	}

};

Amusement_ride ride;

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	ride.input_func();

	cout << ride.solve_func();

	return 0;
}