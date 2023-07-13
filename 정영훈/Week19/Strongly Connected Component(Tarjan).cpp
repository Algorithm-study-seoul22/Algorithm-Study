// tarjan
// https://m.blog.naver.com/kks227/220802519976
// 3580KB, 24ms

#include <bits/stdc++.h>
// iostream, vector, stack, algorithm

using namespace std;
vector<vector<int>> graph;
vector<int> dfsN; // �湮 ����
int dfsNIndex;

vector<bool> finished; // SCC �и��� ���� ������ true

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� ���� ��ȣ��.
stack<int> S;

int DFS(int curr) {
	dfsN[curr] = ++dfsNIndex;
	S.push(curr);

	// curr���� �� �� �ִ� ���� �� dfsn �ּ� ���� result�� ����
	int result = dfsN[curr];
	for (int& next : graph[curr]) {
		if (dfsN[next] == 0) { // ���� �湮���� ���� �̿�
			result = min(result, DFS(next));
		}
		else if (!finished[next]) { // �湮�� ������ ���� SCC�� ��������� ���� �̿�.
			result = min(result, dfsN[next]);
		}
	}

	// �ڽ�, �ڽ��� �ڼյ��� ���� ������ ���� ���� ������ �ڽ��� ��� SCC ����
	if (result == dfsN[curr]) {
		vector<int> currSCC;
		while (true) {
			int t = S.top(); S.pop();
			currSCC.push_back(t);
			finished[t] = true;
			if (t == curr) break;
		}
		sort(begin(currSCC), end(currSCC)); // ������ SCC�� ����� �� �� �ȿ� ���� �������� ������������ ���
		SCC.push_back(currSCC);
	}
	
	return result;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	int V, E;
	cin >> V >> E;
	const int SIZE = V + 1;
	graph.assign(SIZE, {});
	dfsN.assign(SIZE, {});
	finished.assign(SIZE, false);

	for (int e{}; e < E; ++e) {
		int a, b;
		cin >> a >> b; // ���⼺ ����
		graph[a].push_back(b); 
	}

	// �� �������� DFS�ϸ鼭 SCC ����.
	// ���� �׷����� �ƴ� ���� �ֱ� ������ �ݺ����� �ʿ���.
	for (int v{ 1 }; v <= V; ++v) {
		if (!dfsN[v]) { // dfsN[v] == 0 -> v�� �̹湮
			DFS(v);
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
