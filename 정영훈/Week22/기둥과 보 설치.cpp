/*
build_frame [x, y, a, b]
	x, y : ����, ����
	a : 0(���), 1(��)
	b : 0(����), 1(��ġ)
��Ģ
1. ����� �ٴ� ���� �ְų� ���� ���� �� �κ� ���� �ְų�, �Ǵ� �ٸ� ��� ���� �־�� �մϴ�.
2. ���� ���� �� �κ��� ��� ���� �ְų�, �Ǵ� ���� �� �κ��� �ٸ� ���� ���ÿ� ����Ǿ� �־�� �մϴ�.

����, �۾��� ������ ����� ������ �������� �ʴ´ٸ� �ش� �۾��� ���õ˴ϴ�.

�������� ������ ��ǥ�� �������� ���� ������, ����� ���� �������� ��ġ �Ǵ� �����մϴ�.
�������� ��ġ���� ��ġ�ϴ� ����, ���� �������� �����ϴ� ���� �Է����� �־����� �ʽ��ϴ�.

���� ������ ���� [x, y, a]
	x, y : ���, ���� ������ ��ǥ = ����, ����
	a : 0(���), 1(��)
	x��ǥ ���� �������� ���� �� x�� ������ y��ǥ ���� �������� ����
	x, y�� ��� ���� ��� ����� ������ �տ�
*/
// https://wadekang.tistory.com/28 ����..
// ������ �߸� ®�°�..
// ����̳� �� Ȯ���� �� �ߴµ� �̻��ϰ� �����ؼ� �������ٰ� ������...
#include <bits/stdc++.h>

using namespace std;

// ���� ������ �Լ� 2��
bool install_item(int n, vector<vector<vector<int>>>& Map, int x, int y, int a) {
	if (a == 0) { // ��� ��ġ
		if (y == 0) return true; // �ٴ����� �ְų�
		if (x > 0 && Map[x - 1][y][1]) return true; // ���� ������ �� ��
		if (y < n && Map[x][y][1]) return true; // ���� ���� �� ��
		if (y > 0 && Map[x][y - 1][0]) return true; // �ٸ� ��� ��
	}
	else { // �� ��ġ
		if (y > 0 && Map[x][y - 1][0]) return true; // ���� �� �Ʒ� ���
		if (x < n && y > 0 && Map[x + 1][y - 1][0]) return true; // ������ �� �Ʒ� ���
		if (x > 0 && x < n && Map[x - 1][y][1] && Map[x + 1][y][1]) return true; // ���� �� �κ� �ٸ� ��
	}
	return false;
}

bool remove_item(int n, vector<vector<vector<int>>>& Map, int x, int y, int a) {
	Map[x][y][a] = 0;

	if (a == 0) { // ��� ����
		// ���� ��� ���� ��, ��ġ ����?
		if (y < n && Map[x][y + 1][0] && !install_item(n, Map, x, y + 1, 0)) return false;

		// ���� �� ���� ��, ��ġ ����?
		if (y < n && Map[x][y + 1][1] && !install_item(n, Map, x, y + 1, 1)) return false;
		if (x > 0 && y < n && Map[x - 1][y + 1][1] && !install_item(n, Map, x - 1, y + 1, 1)) return false;
	}
	else {
		// ���� ��� ���� ��, ��ġ ����?
		if (Map[x][y][0] && !install_item(n, Map, x, y, 0)) return false;
		if (x < n && Map[x + 1][y][0] && !install_item(n, Map, x + 1, y, 0)) return false;

		// �ٸ� ���� ����Ǿ� ���� ��, ��ġ ����?
		if (x > 0 && Map[x - 1][y][1] && !install_item(n, Map, x - 1, y, 1)) return false;
		if (x < n && Map[x + 1][y][1] && !install_item(n, Map, x + 1, y, 1)) return false;
	}

	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	vector <vector<vector<int>>> Map(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 0))); // ����� n���� ���� �� ����.
	// [0] : ���
	// [1] : ��

	for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];

		// ��Ģ Ȯ��
		if (b == 1) { // ��ġ
			if (a == 0) { // ���
				// �ٴ� ���� �ְų� ���� ���� �� �κ� ���� �ְų� �Ǵ� �ٸ� ��� ���̰ų�.
				// if(install_item(n, Map, x, y, a)) { // Ȯ�ο� �ڵ�
				if (y == 0 || (x > 0 && Map[x-1][y][1]) || Map[x][y][1] || Map[x][y - 1][0]) {
					Map[x][y][a] = 1;
				}
			}
			else { // ��
				// ���� ���� �� �κ��� ��� ���� �ְų�,���� �� �κ��� �ٸ� ���� ���ÿ� ����Ǿ� �ִ���
				// if (install_item(n, Map, x, y, a)) { // Ȯ�ο� �ڵ�
				if ((Map[x][y - 1][0] || Map[x + 1][y - 1][0]) || (x > 0 && Map[x - 1][y][1] && Map[x + 1][y][1])) {
					Map[x][y][a] = 1;
				}
			}
		}
		else { // ����
			if (a == 0) { // ���
				// if (!remove_item(n, Map, x, y, a)) Map[x][y][a] = 1; // Ȯ�ο� �ڵ�
				bool chk = true;

				// ��� ���� ���� �ְų� =>
				if (Map[x][y + 1][1]) { // right
					// �ٸ� �� �� ���� ����̰ų�, ���� ���� ���� �ִ��� Ȯ��
					if (!(Map[x + 1][y][0] || (x > 0 && Map[x - 1][y + 1][1] && Map[x + 1][y + 1][1]))) {
						chk = false;
					}
				}
				if (x > 0 && Map[x - 1][y + 1][1]) { // left
					// ����� �ְų�, ���� ���� ������ Ȯ��
					if (!(Map[x - 1][y][0] || (x > 1 && Map[x - 2][y + 1][1] && Map[x][y + 1][1]))) {
						chk = false;
					}
				}
				// ��� ���� ����� �ְų� => 
				if (Map[x][y + 1][0]) {
					// �ٸ� ���� �ִ��� Ȯ��
					if (!(Map[x][y + 1][1] || (x > 0 && Map[x - 1][y + 1][1]))) {
						chk = false;
					}
				}

				if (chk) { // ���� ����
					Map[x][y][a] = 0;
				}
			}
			else { // ��
				// if (!remove_item(n, Map, x, y, a)) Map[x][y][a] = 1; // Ȯ�ο� �ڵ�
				bool chk = true;
				// �� �� ���� ���� �ְų� =>
				if(x > 0 && Map[x - 1][y][1]) { // left
					if (!(Map[x - 1][y - 1][0] || Map[x][y - 1][0])) { // �� �ؿ� ��� Ȯ��
						chk = false;
					}
				}
				if (Map[x + 1][y][1]) { // right
					if (!(Map[x + 1][y - 1][0] || (x + 2 <= n && Map[x + 2][y - 1][0]))) { // �� �ؿ� ��� Ȯ��
						chk = false;
					}
				}
				// �� �� ���� ����� �ְų� => {
				if (Map[x][y][0]) {
					// ��� �ؿ� ��� Ȯ�� + �ٸ� �� Ȯ��
					if (!(Map[x][y - 1][0] || (x > 0 && Map[x - 1][y][1]))) {
						chk = false;
					}
				}
				if (Map[x + 1][y][0]) {
					// ��� �ؿ� ��� Ȯ�� + �ٸ� �� Ȯ��
					if (!(Map[x + 1][y - 1][0] || Map[x + 1][y][1])) {
						chk = false;
					}
				}

				if (chk) { // ���� ����
					Map[x][y][a] = 0;
				}
			}
		}
	}

	/*
	// �̰� �� �� �� ����..
	// ��ġ => ���� => ��ġ�ϸ� 2�� ����.. ���� �ФФФФФФ�
	for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];
		if (b == 0) continue; // ������ ��ŵ
		if (Map[x][y][a]) {
			answer.push_back({ x,y,a });
		}
	}

	sort(begin(answer), end(answer), [](vector<int>& first, vector<int>& second) {
		// x��ǥ �������� �������� �����ϸ�, x��ǥ�� ���� ��� y��ǥ �������� �������� ����
		// x, y��ǥ�� ��� ���� ��� ����� ������ �տ� ���� �˴ϴ�.
		if (first[0] == second[0] && first[1] == second[1]) {
			return first[2] < second[2];
		}
		else if (first[0] == second[0]) {
			return first[1] < second[1];
		}
		return first[0] < second[0];
	});
	*/
	for (int x{}; x <= n; ++x) {
		for (int y{}; y <= n; ++y) {
			if (Map[x][y][0]) answer.push_back({ x,y,0 });
			if (Map[x][y][1]) answer.push_back({ x,y,1 });
		}
	}

	return answer;
}

template <typename T>
void Print(vector<vector<T>>& vec) {
	for (auto& row : vec) {
		cout << '[';
		for (auto& v : row) {
			cout << v << ' ';
		}
		cout << "], ";
	}
	cout << '\n';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	vector<vector<int>> ans1 = solution(5, {{1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1}});
	Print(ans1);

	vector<vector<int>> ans2 = solution(5, {{0, 0, 0, 1}, {2, 0, 0, 1}, {4, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {2, 1, 1, 1}, {3, 1, 1, 1}, {2, 0, 0, 0}, {1, 1, 1, 0}, {2, 2, 0, 1}});
	Print(ans2);

	return 0;
}