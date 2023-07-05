/*
N���� ������ �ְ� N���� ���� ���̿��� M���� ���ο� W���� ��Ȧ�� �ִ�
�� ���δ� ������ ������ ��Ȧ�� ������ �ִ�.
����� �Ͽ��� ������ �ð��� �ǵ��ư� �ִ� ��찡 �ִ��� ������ �ñ�������.

��Ȧ�� ������ ���δ� ���⼺�� ���� ������ ���������� negative cycle�� ������ �����ϴٸ�,
negative cycle���� ��Ȧ���� �����ϴ� �͵� �翬�� ������.
���� �������� ������ ���� ������ negative cycle ���縸 �� �� ������ ��.

negative cycle �ľ��� ���� 
��� ������ ���� bellman-ford�� �ؾ� �Ѵٰ� ������ �� ������
(��� ������ ���� bellman-ford(O(VE)) ���� �� T * V * VE => 3,125,000,000 (TLE)
�ϳ��� ����(�ƹ��ų� ��Ƶ�)���� �����ص�
dist[d] != INF�� ���������ν� negative cycle �Ǵ��� ��������.
https://www.acmicpc.net/board/view/72995
2152KB, 32ms
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
	int T;
	cin >> T;
	while (T--) {
		int N, M, W;
		cin >> N >> M >> W; // ������ ����, ������ ����, ��Ȧ�� ����
		vector<vector<Edge>> graph(N + 1); // 1 ~ N
		for (int m = 0; m < M; ++m) { // ���δ� ������ ������
			int s, e, t;
			cin >> s >> e >> t;
			graph[s].emplace_back(e, t);
			graph[e].emplace_back(s, t);
		}

		for (int w = 0; w < W; ++w) { // ��Ȧ�� ������ �ִ�
			int s, e, t;
			cin >> s >> e >> t;
			graph[s].emplace_back(e, -t);
		}

		bool negCycle = false;
		vector<long long> dist(N + 1, INF);
		dist[1] = 0;
		for (int c = 0; c < N; ++c) {
			bool nowUpdate = false; // neg cycle ã�� ���� ����� �� �־ �ʿ� ����.
			for (int now = 1; now <= N; ++now) {
				// if (dist[now] == INF) continue;
				for (auto& e : graph[now]) {
					if (dist[e.to] > dist[now] + e.weight) {
						dist[e.to] = dist[now] + e.weight;
						nowUpdate = true;
					}
				}
			}
			// neg cycle ã�� ���� ����� �� �־ �ʿ� ����.
			// if (!nowUpdate) break; // �� �̻� ����ġ ������Ʈ�� ������ ����
			if (c == N - 1 && nowUpdate) negCycle = true; // N��° Ƚ������ ����ġ ������Ʈ -> negative cycle ����.
		}

		if (negCycle) cout << "YES\n";
		else cout << "NO\n";
	}
	

	return 0;
}