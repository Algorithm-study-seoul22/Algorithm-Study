#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

ll solve_func(const int& K, const vector<int>& lan)
{
	ll ans = 0;
	ll left = 1;
	ll right = 22e8;
	

	while (left <= right)
	{
		ll success_flag = 0;
		ll cut = 0;
		ll mid = left + (right - left) / 2;
		

		for (auto& val : lan)
		{
			cut += val / mid;
			if (cut >= K)
			{
				success_flag = 1;
				break;
			}
		}

		if (success_flag == 1)
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
	int N, K;
	vector<int> lan;
	cin >> N >> K;

	lan.resize(N);

	for (auto& val : lan)
	{
		cin >> val;
	}

	sort(lan.begin(), lan.end(), greater<int>());

	cout << solve_func(K, lan) << "\n";

	return 0;
}