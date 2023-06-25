// 34380KB, 744ms
/*
N : 1 ~ 1000, M : 1 ~ 1000
�����̰� å�� �� �� �ִ� �ִ� �л� ���� ���Ͻÿ�.
*/

#include <bits/stdc++.h>

using namespace std;

// SRC(0) -> �л�(1 ~ 1000) -> å(1001 ~ 2000) -> SINK(2001)

constexpr int SRC = 0;
constexpr int SINK = 2001;
constexpr int BOOK = 1000;
constexpr int SIZE = 2002;
constexpr int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};

vector<vector<Edge>> graph;
bitset<SIZE> visited;

/*
�ּ� �뷮 �߰� �� �ش� �뷮 ��ȯ (�ּ� �뷮 �߰� �� �ϴ� ��� 0 ��ȯ)
*/
int fodfs(int v, int t, int f) {
	if (v == t) return f;

	visited[v] = 1;

	for (Edge& e : graph[v]) {
		if (visited[e.to]) continue;

		if (e.cap == 0) continue;

		int flow = fodfs(e.to, t, min(f, e.cap));

		if (flow == 0) continue;

		// flow �긮��
		e.cap -= flow;
		graph[e.to][e.rev].cap += flow;

		return flow;
	}
	return 0;
}

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int T; 
	cin >> T;
	while (T--) {
		graph = vector<vector<Edge>>(SIZE);
		int N, M;  // å ��, �л� ��
		cin >> N >> M;
		
		for (int m = 1; m <= M; ++m) { 
			// 1. SRC -> �� �л� ����
			int srcRev = static_cast<int>(graph[SRC].size());
			int studentRev = static_cast<int>(graph[m].size());
			graph[SRC].emplace_back(studentRev, SRC, m, 1); // cap = 1
			graph[m].emplace_back(srcRev, m, SRC, 0); // cap = 0(���� ����)

			// 2. �� �л� -> ��ȣ�ϴ� å ������ ����
			int a, b;
			cin >> a >> b; // a �̻� b ����
			for (int s = a; s <= b; ++s) {
				int bookIndex = s + BOOK;
				int bookRev = static_cast<int>(graph[bookIndex].size());
				studentRev = static_cast<int>(graph[m].size());
				graph[m].emplace_back(bookRev, m, bookIndex, INF); // cap = INF(�ƹ� ���̵��� ok)
				graph[bookIndex].emplace_back(studentRev, bookIndex, m, 0); // cap = 0(���� ����)
			}
		}

		for (int n = 1; n <= N; ++n) { // 3. å�� -> SINK ����
			int bookIndex = n + BOOK;
			int sinkRev = static_cast<int>(graph[SINK].size());
			int bookRev = static_cast<int>(graph[bookIndex].size());
			graph[bookIndex].emplace_back(sinkRev, bookIndex, SINK, 1); // cap = 1
			graph[SINK].emplace_back(bookRev, SINK, bookIndex, 0); // cap = 0(���� ����)
		}

		int s = SRC, e = SINK;
		int maxFlow = 0;
		while (1) {
			visited.reset();
			int flow = fodfs(s, e, INF);

			if (flow == 0) break;

			// maxFlow += flow; // �ִ� 1
			maxFlow++;
		}
		
		cout << maxFlow << '\n';
	}
	

	return 0;
}