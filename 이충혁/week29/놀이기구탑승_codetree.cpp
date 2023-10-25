#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

/*
n * n �¼��� �Է� ������� �л� ���� �ɴ´�.
3 <= n <= 20

1. ���� ���� ���� �ʰ� 4���� ������ ĭ �� �����ϴ� ģ���� ���� ���� ��ġ�� ����.
2. 1���� �������� ���� ������ ĭ �� ��� �ִ� ĭ�� ���� ���� ���� ��ġ�� ����.
3. 2���� �������� ���ȣ �� ���� �۰�, �� ���� ����ȣ�� ���� �۰� ����.

���� ������ �� ž�� �� �ֺ��� �����ϴ� ģ���� �� ���� ������ �ٸ��� ������
0 ~ 4 �� ������� : 0, 1, 10, 100, 1000


�ԷµǴ� ���� ����
�����ϴ� ģ���� map�� ��ǥ���� �ִ��� Ȯ��
�� ��ǥ�� �����¿� 4���⿡ 
1) �ڸ��� �ִ���
2) �� �ڸ��� ������ �����ϴ� ģ���� �ֺ��� �������
3) �� ������ ���
4) ���̶� �� ����?

�̰� ������� ������ Ȯ�� �ϰ� ���ؿ� �� �����ϴ� ���� �ִٸ� �����

������ ���� �� ��������
1) �ڸ��� �ִ���
2) �� �ڸ� �ֺ� ������� ���
3) ���̶� �� ���� ���� �Ǿ� �ϴ��� 
�� ��Ģ���� �ٽ� ã�´�.

���� ��, �� ���� ���� ���� map �� seat�� ����

������ input ���� ������ ������ ����Ѵ�.

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

	// ������ �迭 �����ϱ� : https://stackoverflow.com/questions/5724171/passing-an-array-by-reference
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
		
			// 1) ģ���� �̹� �ɾҳ�?
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

					// 2) ���ڸ��ΰ�?
					if (visited[next.y][next.x] != 0) continue;

					// 3) �����ϴ� ģ������ ����� �� �̻��ΰ�?
					int tmp_friend = around_friend(next, student.freinds);
					int tmp_empty = around_empty(next);
					
					if (friend_cnt > tmp_friend) continue;

					else if (friend_cnt == tmp_friend)
					{
						// 4) ���ڸ� ���� ����� ���̻��ΰ�?
						if (empty_cnt > tmp_empty) continue;

						else if (empty_cnt == tmp_empty)
						{
							// 5) �࿭�� ������?
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

			// ģ���� �� �ɾҴٸ�?
			if (pt == NOT_COORDI)
			{
				

				for (int y = 0; y < n; y++)
				{
					for (int x = 0; x < n; x++)
					{
						// 1) �ڸ��� �ִ���
						if (visited[y][x] != 0) continue;
						


						// 2) ���ڸ� ���� ����� ���̻��ΰ�?
						int tmp_empty = around_empty({y, x});
						
						if (empty_cnt > tmp_empty) continue;

						else if (empty_cnt == tmp_empty)
						{
							// 3) �࿭�� ������?
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