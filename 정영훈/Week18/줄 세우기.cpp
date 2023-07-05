/*
N���� �л����� Ű ������� �� �����.
�Ϻ� �л����� Ű�� ���� ����� �־����� ��, ���� ����� ���α׷� �ۼ��ϱ�. => Topological sort
3944KB, 36ms
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int N, M;  // �л� ��, �� Ƚ��
	cin >> N >> M;
	vector<int> indegrees(N + 1, 0); // 1 ~ N
	vector<vector<int>> graph(vector<vector<int>>(N + 1));
	for (int m = 0; m < M; ++m) {
		int a, b; // a�� b���� �ռ��� �Ѵ�.
		cin >> a >> b;
		indegrees[b]++;
		graph[a].emplace_back(b);
	}

	queue<int> q;
	for (int n = 1; n <= N;++n) {
		if (indegrees[n] == 0) q.push(n);
	}

	while (!q.empty()) {
		int now = q.front(); q.pop();
		cout << now << ' ';
		for (int& next : graph[now]) {
			indegrees[next]--;
			if (indegrees[next] == 0) q.push(next);
		}
	}
	cout << '\n';

	return 0;
}