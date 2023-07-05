/*
https://m.blog.naver.com/kks227/220802704686
http://bowbowbow.tistory.com/3
������ ã��. => �ٸ� ��ȸ�ΰ� �ִ��� ������
15044KB, 180ms
*/

#include <bits/stdc++.h>
// vector, algorithm, iostream, utility

using namespace std;
using pii = pair<int, int>;

vector<vector<int>> graph;
vector<int> visited;
int visitIndex;
vector<pii> answer;

int DFS(int curr, int prev = -1) {
	visited[curr] = ++visitIndex; // 1���� ����
	int ret = visited[curr];

	for (int& next : graph[curr]) {
		if (prev == next) continue; // ������������ >= �񱳿��� ���� ������ (������������ �ʿ���)
		if (visited[next]) ret = min(ret, visited[next]);
		else { // ���� �湮
			int temp = DFS(next, curr);
			ret = min(ret, temp);
			if (temp > visited[curr]) { // ��ȣ �����ϸ� Ʋ��. (���� ���� ���� �����̾�� ��)
				// curr�� ���ؼ��� �� �� �ִ� ���� �ִٴ� ����.
				answer.emplace_back(min(curr, next), max(curr, next)); // ������ ��� ( A < B �� �����ϵ��� ���� ���)
			}
		}
	}
	
	return ret;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

	int V, E;
	cin >> V >> E;
	const int SIZE = V + 1;
	graph = vector<vector<int>>(SIZE); // 1 ~ V
	visited = vector<int>(SIZE, 0);
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

	sort(begin(answer), end(answer)); //  �������� ���������� �� �ٿ� �ϳ��� ����Ѵ�
	// pair - operator< => first ���� ���ϰ� second ����
	
	cout << answer.size() << '\n'; // �������� ����
	for (auto& a : answer) {
		cout << a.first << ' ' << a.second << '\n';
	}

	return 0;
}