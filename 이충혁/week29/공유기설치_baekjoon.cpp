#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int N, C;
vector<int> router;

int solve_func()
{
	int ans = 1;

	int left = 0;
	int right = 1e9;

	while (left <= right)
	{
		int install = 1;
		int store_value = router[0];
		int mid = left + (right - left) / 2;

		for (int i = 1; i < N; i++)
		{
			if (router[i] - store_value >= mid)
			{
				store_value = router[i];
				install++;
				if (install >= C)
				{
					break;
				}
			}
		}


		if (install >= C)
		{
			left = mid + 1;
			ans = mid;
		}
		else
		{
			right = mid - 1;
		}
	}

	return ans;

}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> C;
	router.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> router[i];
	}
	sort(router.begin(), router.end());

	cout << solve_func();

	return 0;
}