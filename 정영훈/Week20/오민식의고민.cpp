/*
���ν��� ������ A���ÿ��� �����ؼ� B���ÿ��� ������.

��, ���� ���ø� ���� �� �湮�� �� ������, �� ���ø� �湮�� ������ ���� ���� �ȴ�. 
��� ���� ������ �Է����� �־��� �������θ� �̿��� �� ������, ���� �� �̿��� ���� �ִ�. => �ܹ���

���� ���ν��� ���� ���ÿ� �����ϴ� ���� �Ұ��� => gg
���ν��� ���� ���ÿ� �������� �� ���� ������ ���� ������ ���� �� �ִٸ� => Gee
�� ���� ��쿡�� ���� �׼��� �ִ밪�� ���
2024KB, 0ms
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
struct Edge {
	int to;
	ll weight;
	Edge(int to, ll weight) : to(to), weight(weight) {}
};
constexpr ll INF = 1LL << 61;

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
	int N, A, B, M; // ������ ��, ���� ����, ���� ����, ���� ���� ����
	cin >> N >> A >> B >> M;
	vector<vector<Edge>> graph(N); // 0 ~ N
	for (int m{}; m < M; ++m) {
		int a, b, c; // a -> b (cost = c)
		cin >> a >> b >> c;
		graph[a].emplace_back(b, static_cast<ll>(c));
	}

	vector<int> earning(N, 0);
	for (int& e : earning) {
		cin >> e;
	}

	// ���� edge�� earning �ݿ�
	for (int n{}; n < N; ++n) {
		for (Edge& e : graph[n]) {
			e.weight -= earning[e.to]; // ���������� �� �� �ִ� ���� ���ֱ�.
		}
	}

	// Bellman-Ford
	vector<ll> dist(N, INF);
	vector<int> negVertex; // negative cycle�� ����� ������ ǥ��
	negVertex.reserve(N);
	bool negCycle{ false };
	dist[A] = -earning[A];
	for (int t{ 1 }; t <= N; ++t) { 
		bool nowUpdate{ false };
		for (int n{}; n < N; ++n) {
			if (dist[n] == INF) continue; // ���� �湮���� �ʾ����� skip
			for (Edge& e : graph[n]) {
				if (dist[e.to] > dist[n] + e.weight) {
					dist[e.to] = dist[n] + e.weight;
					nowUpdate = true;
					if (t == N) { // N��° update => neg cycle
						negVertex.push_back(n);
						negCycle = true;
					}
				}
			}
		}
		if (!nowUpdate) break; // ���� ������Ʈ�� ������ �����ε� ���� => ���� ���� ����
	}

	if (dist[B] == INF) cout << "gg\n"; // ���� �Ұ���
	else if (negCycle) { // negCycle�� ����� ���, �ش� cycle���� ������ ���� ���� ���� Ȯ�� �ʿ�
		bool chk{ false };
		for (int& v : negVertex) { // negCycle�� ����� ������ ǥ��
			// BFS�� ���� �ش��ϴ� �������� B(������)�� ���ް������� Ȯ��
			auto result = [&graph, v, B, N]() -> bool {
				vector<int> visited(N, 0);
				queue<int> q;
				q.push(v);
				visited[v] = 1;
				while (!q.empty()) {
					int now = q.front(); q.pop();
					for (Edge& e : graph[now]) {
						if (e.to == B) return true; // ���� ����
						if (!visited[e.to]) {
							q.push(e.to);
							visited[e.to] = 1;
						}
					}
				}
				return false; // ���� �Ұ���
			} ();
			if (result) {
				chk = true;
				break;
			}
		}
		if (chk) cout << "Gee\n"; // negCycle���� B�� ���� ����
		else cout << -dist[B] << '\n';
	}
	else cout << -dist[B] << '\n';

	return 0;
}