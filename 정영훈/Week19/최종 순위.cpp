/*
https://mapocodingpark.blogspot.com/2020/03/BOJ3665.html ����.
��� ���� ���� ������ ������. => ���� ���� maximum 500
Adjacency Matrix�� edge ���� ���� ������.
- ���� ������ �׷��� ���� ����.
- matrix�� �����ص� ������ ������ ä��.

����, Ȯ���� ������ ã�� �� ���ٸ� "?"�� ��� => �׷� ��찡 ����..
3068KB, 36ms
*/
#include <bits/stdc++.h>
// iostream, vector, queue

using namespace std;

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<int> teams(n, 0);
		for (int& t : teams) {
			cin >> t;
		}
		vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
		vector<int> indegree(n + 1, 0);

		// ���� ���� �����
		for (int i{}; i < n; ++i) {
			for (int j{ i + 1 }; j < n; ++j) {
				adj[teams[i]][teams[j]] = 1; 
				indegree[teams[j]]++;
			}
		}

		// ���� - ���� ���� �ٲٱ�
		int m; 
		cin >> m;
		for (int i{}; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			if (adj[a][b]) {
				swap(a, b);
			}
			adj[b][a] = false;
			adj[a][b] = true;
			indegree[a]--;
			indegree[b]++;
		}

		queue<int> Q;
		for (int i{ 1 }; i <= n; ++i) {
			if (indegree[i] == 0)Q.push(i);
		}

		vector<int> answer;
		while(!Q.empty()) { // ������ N��
			int now = Q.front(); Q.pop();
			answer.push_back(now);
			
			for (int next{ 1 }; next <= n; ++next) {
				if (adj[now][next]) {
					indegree[next]--;
					if (indegree[next] == 0) Q.push(next);
				}
			}
		}
		if ((int)answer.size() == n) {
			for (int& a : answer) cout << a << ' ';
			cout << '\n';
		}
		else {
			cout << "IMPOSSIBLE\n";
		}
	}

	return 0;
}
