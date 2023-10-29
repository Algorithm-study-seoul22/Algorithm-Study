#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct UnionFind {
	vector<int> parent;
	vector<int> cnt;
	vector<int> candy;

	UnionFind(int sz) :
		parent(vector<int>(sz, -1)),
		cnt(vector<int>(sz, 1)),
		candy(vector<int>(sz)) {}

	int Find(int x) {
		if (parent[x] == -1) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int a, int b) {
		int pa = Find(a);
		int pb = Find(b);

		if (pa == pb) return;

		parent[pb] = pa;

		cnt[pa] += cnt[pb];
		cnt[pb] = 0;

		candy[pa] += candy[pb];
		candy[pb] = 0;
	}
};

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);

	int N, M, K;
	cin >> N >> M >> K;

	UnionFind uf(N);

	for (auto& c : uf.candy)
		cin >> c;

	for (int i = 0; i < M; ++i) {
		int u, v;
		cin >> u >> v;
		uf.Union(u - 1, v - 1);
	}

	vector<int> groupCnt;
	vector<int> groupCandy;

	for (int i = 0; i < N; ++i) {
		if (uf.parent[i] != -1)
			continue;

		groupCnt.push_back(uf.cnt[i]);
		groupCandy.push_back(uf.candy[i]);
	}

	vector<int> dp(K);

	for (int idx = 0; idx < groupCnt.size(); ++idx)
		for (int cnt = K - 1; cnt >= groupCnt[idx]; --cnt)
			dp[cnt] = max(dp[cnt], dp[cnt - groupCnt[idx]] + groupCandy[idx]);

	cout << dp[K - 1] << '\n';

	return 0;
}
