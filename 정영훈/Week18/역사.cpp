/*
�������ķε� �����ұ�? �ߴµ�
������ �׷����� 2���� ���������� �� �׷�����
2��° �湮�ϴ� ���� 3��° �湮�ϴ� ���� ���ϰ� �Ǹ� �� �Ұ���� ����� ���;� �ϳ�..
������ �湮 ����üũ�� ���ؼ��� �׷��� �ݷ� �ذ��� �Ұ�����.
��򰡿��� �Դ����� �� �����صθ� ������ ����..?

����� ������ n(400��) => 100���� => O(N^3) ����.
floyd-warshall => O(N^3)
2680KB, 88ms
*/
#include <bits/stdc++.h>

using namespace std;
constexpr int INF = 1 << 29;

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	
	int n, m; // ����� ����, ����� ���� ������ ����
	cin >> n >> m;
	vector<vector<int>> dist(n + 1, vector<int>(n+1, INF)); // 1 ~ n
	for (int i = 1; i <= n; ++i) {
		dist[i][i] = 0; // �ڱ� �ڽ����� ���� ����ġ = 0
	}
	for (int i = 0; i < m; ++i) { // m���� ���� ���� ����
		int a, b; // a�� b���� ���� �Ͼ.
		cin >> a >> b;
		dist[a][b] = 1;
		// dist[b][a] = -1;
	}

	for (int k = 1; k <= n; ++k) { // ����
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	int s;
	cin >> s;

	for (int i = 0; i < s; ++i) {
		int a, b;
		cin >> a >> b;
		if (dist[a][b] == INF) {
			if (dist[b][a] == INF) cout << "0\n";
			else cout << "1\n";
		}
		else if (dist[a][b] > 0) cout << "-1\n";
	}

	return 0;
}