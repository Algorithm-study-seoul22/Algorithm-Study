/*
���� ������ n * 100�� ��.
floyd-warshall => O(N^3)
2152KB, 24ms
*/
#include <bits/stdc++.h>

using namespace std;
constexpr int INF = 1 << 29;

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	
	int n;
	cin >> n; // ������ ����
	vector<vector<int>> dist(n, vector<int>(n, INF));
	for (int i = 0; i < n; ++i) {
		dist[i][i] = 0; // �ڱ� �ڽ����� ���� ��� = 0
	}
	int m;
	cin >> m; // ������ ����
	for (int i = 0; i < m; ++i) {
		int a, b, c; // a -> b (��� = c)
		cin >> a >> b >> c;
		--a, --b;
		// ���� ���ÿ� ���� ���ø� �����ϴ� �뼱�� �ϳ��� �ƴ� �� �ִ�.
		dist[a][b] = min(dist[a][b], c);
	}

	// floyd-warshall
	for (int k = 0; k < n; ++k) { // ����
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (auto& row : dist) {
		for (auto& v : row) {
			// ����, i���� j�� �� �� ���� ��쿡�� �� �ڸ��� 0�� ����Ѵ�. - ���Ծ���
			if (v == INF) cout << 0 << ' ';
			else cout << v << ' ';
		}
		cout << '\n';
	}

	return 0;
}