/*
1�� ������ ���� ���� �����̰� N�� ������ ���� ����� ������ �ȴ�
������ �� ���� ���ǿ� ���� ������ Ǯ ������ ���ϱ�� �Ͽ���
	N���� ������ ��� Ǯ��� �Ѵ�.
	���� Ǫ�� ���� ���� ������ �ִ� ������, ���� Ǫ�� ���� ���� ������ �ݵ�� ���� Ǯ��� �Ѵ�.
	�����ϸ� ���� �������� Ǯ��� �Ѵ�.
3944KB, 32ms
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int N, M;  // ���� ��, ���� ����
	cin >> N >> M;
	vector<int> indegrees(N + 1, 0); // 1 ~ N
	vector<vector<int>> graph(vector<vector<int>>(N + 1));
	// �׻� ������ ��� Ǯ �� �ִ� ��츸 �Է����� �־�����.
	for (int m = 0; m < M; ++m) {
		int a, b; // a�� b���� �ռ��� �Ѵ�.
		cin >> a >> b;
		indegrees[b]++;
		graph[a].emplace_back(b);
	}

	// ���� ������ ������ ���ؼ��� �� ���ٸ� ������ ������ pq
	priority_queue<int, vector<int>, greater<int>> q;
	for (int n = 1; n <= N;++n) {
		if (indegrees[n] == 0) q.push(n);
	}

	while (!q.empty()) {
		int now = q.top(); q.pop();
		cout << now << ' ';
		for (int& next : graph[now]) {
			indegrees[next]--;
			if (indegrees[next] == 0) q.push(next);
		}
	}
	cout << '\n';

	return 0;
}