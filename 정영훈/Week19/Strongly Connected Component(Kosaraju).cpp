// kosaraju
// 4416KB, 28ms

#include <bits/stdc++.h>
// iostream, vector, stack, algorithm

using namespace std;
vector<vector<int>> graph, transposeGraph;
vector<bool> visited;

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� ���� ��ȣ��.
stack<int> S;

void FillStack(int curr) {
	visited[curr] = true;

	for (int& next : graph[curr]) {
		if (!visited[next]) FillStack(next);
	}

	S.push(curr);
}

void FindSCC(int curr, vector<int>& components) {
	visited[curr] = true;
	components.push_back(curr);

	for (int& next : transposeGraph[curr]) {
		if (!visited[next]) {
			FindSCC(next, components);
		}
	}
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	int V, E;
	cin >> V >> E;
	graph.assign(V + 1, {});
	transposeGraph.assign(V + 1, {});
	visited.assign(V + 1, false);

	for (int e{}; e < E; ++e) {
		int a, b;
		cin >> a >> b; // ���⼺ ����
		graph[a].push_back(b); // ���� �׷���
		transposeGraph[b].push_back(a); // ��ġ �׷���
	}

	// Stack�� �湮�� ������� ����
	for (int v{ 1 }; v <= V; ++v) {
		if (!visited[v]) {
			FillStack(v);
		}
	}

	visited.assign(V + 1, false);
	while (!S.empty()) {
		int now = S.top(); S.pop();
		if (!visited[now]) {
			vector<int> components;
			FindSCC(now, components);
			sort(begin(components), end(components)); // ������ SCC�� ����� �� �� �ȿ� ���� �������� ������������ ���
			SCC.emplace_back(components);
		}
	}

	// ���� ���� SCC�� ���ؼ��� �� �ȿ� �����ִ� ���� ���� ������ ���� ��ȣ ������ ���
	sort(begin(SCC), end(SCC));

	cout << SCC.size() << '\n';
	for (auto& scc : SCC) {
		for (auto& v : scc) {
			cout << v << ' ';
		}
		cout << "-1\n";
	}

	return 0;
}

