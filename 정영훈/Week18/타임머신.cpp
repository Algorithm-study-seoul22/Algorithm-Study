/*
���� cost�� ������ �� ����. => dijkstra �� ��.
Bellman-Ford
2152KB, 8ms
*/
#include <iostream>
#include <vector>

using namespace std;
constexpr long long INF = 1LL << 60;
constexpr int START = 1;

struct Edge {
	int to, weight;
	Edge(int t, int w) : to(t), weight(w) {}
};

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

	int N, M;
	cin >> N >> M;// ������ ����, ���� �뼱�� ����
	vector<vector<Edge>> graph(N+1); // 1  ~ N
	for (int m = 0; m < M; ++m) {
		int a, b, c;
		cin >> a >> b >> c; // a -> b (��� = c)
		graph[a].emplace_back(b, c);
	}

	// 1�� ����(START) -> �� ����
	bool negCycle = false;
	vector<long long> dist(N + 1, INF);
	dist[START] = 0;
	for (int t = 0; t < N; ++t) {
		bool nowUpdate = false;
		for (int now = 1; now <= N; ++now) {
			if (dist[now] == INF) continue; // ���� �� �� ����.
			for (auto& e : graph[now]) {
				if (dist[e.to] > dist[now] + e.weight) {
					dist[e.to] = dist[now] + e.weight;
					nowUpdate = true;
				}
			}
		}
		if (!nowUpdate) break; // �� �̻� ����ġ ������Ʈ�� ������ ����
		if (t == N - 1 && nowUpdate) negCycle = true; // N��° ����ġ ������Ʈ -> negative cycle ����
	}
	
	if (negCycle) cout << "-1\n";
	else {
		for (int d = 2; d <= N; ++d) {
			if (dist[d] == INF) cout << "-1\n";
			else cout << dist[d] << '\n';
		}
	}

	return 0;
}