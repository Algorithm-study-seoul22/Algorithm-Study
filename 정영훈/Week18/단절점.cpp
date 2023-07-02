/*
https://m.blog.naver.com/kks227/220802704686
http://bowbowbow.tistory.com/3
������ ã��. => �ٸ� ��ȸ�ΰ� �ִ��� ������
���� A�� ��Ʈ ��� �϶�
	: �ڽ� ���� 2�̻��϶� ������
���� A�� ��Ʈ ��尡 �ƴ� ��
	: ���� A�� �ڽ� ��尡 ���� A������ �湮�� ��忡  ���� A�� ��ġ�� �ʰ� ������ �� ������ ������
4600KB, 24ms
*/

#include <bits/stdc++.h>
// vector, algorithm, iostream

using namespace std;

vector<vector<int>> graph;
vector<int> visited, cutVertex;
int visitIndex;

int DFS(int curr, int prev = -1) {
	visited[curr] = ++visitIndex; // 1���� ����
	int ret = visited[curr];

	int childCnt = 0;
	for (int& next : graph[curr]) {
		// if (prev == next) continue;
		if (visited[next]) ret = min(ret, visited[next]);
		else { // ���� �湮
			int temp = DFS(next, curr);
			ret = min(ret, temp);
			++childCnt;
			if (prev != -1 && temp >= visited[curr]) {
				// curr�� ���ؼ��� �� �� �ִ� ���� �ִٴ� ����.
				cutVertex[curr] = 1;
			}
		}
	}

	// root�� ��� ���� ó��
	if (prev == -1 && childCnt >= 2) {
		cutVertex[curr] = 1;
	}
	return ret;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

	int V, E;
	cin >> V >> E;
	const int SIZE = V + 1;
	graph = vector<vector<int>>(SIZE); // 1 ~ V
	visited = vector<int>(SIZE, 0);
	cutVertex = vector<int>(SIZE, 0);
	for (int e = 0; e < E; ++e) {
		int a, b;
		cin >> a >> b; // ������
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int v = 1; v <= V; ++v) {
		if (visited[v] == 0) {
			DFS(v);
		}
	}

	vector<int> answer;
	answer.reserve(SIZE);
	for (int v = 1; v <= V; ++v) {
		if (cutVertex[v]) answer.push_back(v);
	}

	cout << answer.size() << '\n'; // �������� ����
	for (int& a : answer) { //  �������� ��ȣ�� �������� ������ ������������ ���
		cout << a << ' ';
	}
	cout << '\n';

	return 0;
}