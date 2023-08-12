// �̺� ��Ī - Network Flow�� �ٲ㼭..
// Ford-Fulkerson
/*
��縦 M���� ĭ���� �����ϰ�, �� ĭ���� �ִ� �� ������ �Ҹ� ���� ��ȹ
SRC(0) -> �ҵ�(1~N(<=200)) -> ���(201~201+M(<=400)) -> SINK(401))
SRC -> �� : cap = 1 (�� ������ ����)
�� -> ��� : cap = INF(�� ��� ����)
��� -> SINK : cap = 1 (�� ������ ��� �� �� ����)
3476KB, 4ms
*/

#include <bits/stdc++.h>

using namespace std;

constexpr int SIZE = 450;
constexpr int INF = 1 << 29;
constexpr int BARN = 200;
constexpr int SRC = 0;
constexpr int SINK = 401;

bitset<SIZE> visited; // �γ��ϰ�

struct Edge {
	int to, c, f;
	Edge* dual;
	Edge() : Edge(-1, 0) {}
	Edge(int to, int c, int f = 0) : to(to), c(c), f(f), dual(nullptr) {}
	int RemainCap() { // ���� ������ ���� �뷮
		return c - f;
	}
	void AddFlow(int flow) {  // flow��ŭ ����ֱ�
		f += flow;
		dual->f -= flow;
	}
};
vector<vector<Edge*>> graph;

int FordFulkerson(int v, int t, int f) {
	if (v == t) return f;
	visited[v] = 1;

	for (auto e : graph[v]) { // Edge*
		if (visited[e->to]) continue;

		int remain = e->RemainCap();
		if (remain == 0) continue;

		int flow = FordFulkerson(e->to, t, min(f, remain));
		if (flow == 0) continue;
		e->AddFlow(flow);
		return flow;
	}
	return 0;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // ���� ��, ����� ��
	// �� �Ұ� ���� ���ϴ� ��翡 ���� ����

	graph.assign(SIZE, vector<Edge*>()); // �����ϴ� �������� ���� ����Ʈ�� ����

	for (int n = 1; n <= N; ++n) {
		int S;
		cin >> S; // n��° �Ұ� ���� ���ϴ� ��� ����

		// SRC(0) -> ��(n)
		Edge *ori = new Edge(n, 1), *rev = new Edge(0, 0); 
		ori->dual = rev;
		rev->dual = ori;
		graph[0].push_back(ori); // SRC -> n (��¥ ����, cap = 1)
		graph[n].push_back(rev); // n -> SRC (����, cap = 0)

		for (int s{}; s < S; ++s) {
			int a; // ��� ��ȣ
			cin >> a;
			a += BARN;

			// ��(n) -> ���(a)
			Edge *ori = new Edge(a, INF), *rev = new Edge(n, 0);
			ori->dual = rev;
			rev->dual = ori;
			graph[n].push_back(ori); // SRC -> n (��¥ ����, cap = INF)
			graph[a].push_back(rev); // n -> SRC (����, cap = 0)
		}
	}

	for (int m = 1; m <= M; ++m) {
		// ���(BARN + m) -> SINK(N+M+1)
		int barnIdx = BARN + m;
		Edge *ori = new Edge(SINK, 1), *rev = new Edge(barnIdx, 0);
		ori->dual = rev;
		rev->dual = ori;
		graph[barnIdx].push_back(ori); // SRC -> n (��¥ ����, cap = 1)
		graph[SINK].push_back(rev); // n -> SRC (����, cap = 0)
	}

	int answer{};

	while (1) {
		visited.reset();
		int flow = FordFulkerson(SRC, SINK, INF);
		if (flow == 0) break;
		answer += flow;
	}

	cout << answer << '\n';

	return 0;
}