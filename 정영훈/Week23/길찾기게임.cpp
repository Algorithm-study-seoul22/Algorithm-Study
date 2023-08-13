// ���� ��ȸ : Root - Left - Right
// ���� ��ȸ : Left - Right - Root
/*
Ʈ�� ��� ���� ��Ģ
- Ʈ���� �����ϴ� ��� ����� x, y ��ǥ ���� �����̴�.
- ��� ���� ���� �ٸ� x���� ������.
- ���� ����(level)�� �ִ� ���� ���� y ��ǥ�� ������.
- �ڽ� ����� y ���� �׻� �θ� ��庸�� �۴�.
- ������ ��� V�� ���� ���� Ʈ��(left subtree)�� �ִ� ��� ����� x���� V�� x������ �۴�.
- ������ ��� V�� ������ ���� Ʈ��(right subtree)�� �ִ� ��� ����� x���� V�� x������ ũ��.
*/
#include<bits/stdc++.h>

using namespace std;
constexpr int BORDER = 100'010;

struct Vertex{
	int x, y, index;
	Vertex(int x, int y, int index) : x(x), y(y), index(index) {}
};
int verticesSize;

void MakePreorder(vector<vector<int>>& answer, vector<int>& visited, vector<Vertex>& vertices, int index, int border = BORDER) {
	answer[0].push_back(vertices[index].index);
	visited[index] = 1;
	for (int i = index + 1; i < verticesSize; ++i) {
		if (vertices[index].y == vertices[i].y) continue;
		// ���Ŀ� ������ ����(index)���� y��ǥ�� �۴�.
		if (visited[i] == 0 && vertices[index].x > vertices[i].x && vertices[i].x < border) MakePreorder(answer, visited, vertices, i, vertices[index].x); // left
		if (visited[i] == 0 && vertices[index].x < vertices[i].x && vertices[i].x < border) MakePreorder(answer, visited, vertices, i, border); // right
	}
}

void MakePostorder(vector<vector<int>>& answer, vector<int>& visited, vector<Vertex>& vertices, int index, int border = BORDER) {
	for (int i = index + 1; i < verticesSize; ++i) {
		if (vertices[index].y == vertices[i].y) continue;
		// ���Ŀ� ������ ����(index)���� y��ǥ�� �۴�.
		if (visited[i] == 0 && vertices[index].x > vertices[i].x && vertices[i].x < border) MakePostorder(answer, visited, vertices, i, vertices[index].x); // left
		if (visited[i] == 0 && vertices[index].x < vertices[i].x && vertices[i].x < border) MakePostorder(answer, visited, vertices, i, border); // right
	}
	answer[1].push_back(vertices[index].index);
	visited[index] = 1;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2); // ���� ��ȸ, ���� ��ȸ
	vector<Vertex> vertices;

	int index = 1;
	for (vector<int>& coord : nodeinfo) {
		vertices.emplace_back(coord[0], coord[1], index++);
	}
	verticesSize = static_cast<int>(vertices.size());

	sort(begin(vertices), end(vertices), [](const Vertex& v1, const Vertex& v2){
		if (v1.y == v2.y) return v1.x < v2.x;
		return v1.y > v2.y;
	}); // y��ǥ ū �ֵ� �������� ���� (y�� ������ x�� ���� �������)
	
	vector<int> visited(verticesSize + 1, 0);
	MakePreorder(answer, visited, vertices, 0);
	visited.assign(verticesSize + 1, 0);
	MakePostorder(answer, visited, vertices, 0);

	return answer;
}

template<typename T>
void Print(vector<vector<T>>& vec) {
	for (auto& row : vec) {
		for (auto& v : row) {
			cout << v << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	auto result = solution({{5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2}});
	Print(result);
}