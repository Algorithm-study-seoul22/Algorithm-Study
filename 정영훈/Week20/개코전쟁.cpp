/*
���̿ձ��� 1�� ������,  �ڳ����ձ��� N�� ������
������ �����ϳ��� �ı����� �� 1�� �������� N�� ���������� �ִܰŸ��� �ִ��� ����Ѵ�.
�� �������̿��� �� �� �̻��� ���� �������� �ʰ� ��� ���δ� �������.
�� ���θ� �ı��ϴ� ���� ������� �� ��θ� �ı��ϴ� ��
9248KB, 76ms
*/
#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};
auto compare = [](const Edge& e1, const Edge& e2) {
	return e1.weight > e2.weight; // min heap�� compare
};
using pii = pair<int, int>; // from - to (���� ���� �����)
constexpr int INF = 1 << 29;

int GetMaximum(vector<vector<Edge>>& graph, vector<pii>& edges, int N) {
	int ret{ -1 };
	for (auto&[from, to] : edges) {
		// from -> to ���� �����ϰ� dijkstra ����
		vector<int> dist(N + 1, INF);
		dist[1] = 0;
		priority_queue<Edge, vector<Edge>, decltype(compare)> pq(compare); // to, weight
		// Edge�� ���������� �����δ� to(�ش� ����)������ weight(�Ÿ�) ����
		pq.emplace(1, 0);

		while (!pq.empty()) {
			Edge now = pq.top(); pq.pop();

			if (dist[now.to] < now.weight) continue;

			for (Edge& e : graph[now.to]) { // now.to -> e.to
				// �����ؾ� �� ����
				if (e.to == to && now.to == from) continue;
				if (now.to == to && e.to == from) continue;

				if (dist[e.to] > dist[now.to] + e.weight) {
					dist[e.to] = dist[now.to] + e.weight;
					pq.emplace(e.to, dist[e.to]);
				}
			}
		}
		ret = max(ret, dist[N]);
	}
	return ret;
}

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // ���� ����, ���� ����

	vector<vector<Edge>> graph(N + 1); // 1 ~ N
	for (int m{}; m < M; ++m) {
		int x, y, z;
		cin >> x >> y >> z;
		graph[x].emplace_back(y, z);
		graph[y].emplace_back(x, z);
	}

	const int s{ 1 }, f{ N }; // s -> f�� �ִ� ��� ���ϱ�

	// dijkstra(��� ���� �̿�)
	vector<int> dist(N + 1, INF);
	vector<int> from(N + 1, 0); // from[v] : ��𿡼� v�������� �Դ���
	dist[s] = 0;
	from[s] = -1; // start

	priority_queue<Edge, vector<Edge>, decltype(compare)> pq(compare); // to, weight
	// Edge�� ���������� �����δ� to(�ش� ����)������ weight(�Ÿ�) ����
	pq.emplace(s, 0);
	while (!pq.empty()) {
		Edge now = pq.top(); pq.pop();

		if (dist[now.to] < now.weight) continue;

		for (Edge& e : graph[now.to]) {
			if (dist[e.to] > dist[now.to] + e.weight) {
				dist[e.to] = dist[now.to] + e.weight;
				from[e.to] = now.to;
				pq.emplace(e.to, dist[e.to]);
			}
		}
	}

	// �ִ� ��ο� ����� ���� ���� ����
	vector<pii> edges;
	edges.reserve(N); // �ִ� ����� ��� �ִ� N - 1���� ����
	int to{ N };
	while (from[to] != -1) {
		edges.emplace_back(from[to], to);
		to = from[to];
	}

	int answer = GetMaximum(graph, edges, N);
	cout << answer << '\n';

	return 0;
}