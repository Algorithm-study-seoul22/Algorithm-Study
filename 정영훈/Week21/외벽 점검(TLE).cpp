/*
�ּ����� ģ������ ������ ��� ������ �����ϰ� ������ ģ������ ���� ���縦 ������
���� �� ��������� ���� ���� ������ 0���� ��Ÿ����,
��� ������ ��ġ�� ���� ���� �������κ��� �ð� �������� ������ �Ÿ��� ��Ÿ���ϴ�.
��, ģ������ ��� �������� �ð�, Ȥ�� �ݽð� �������� �ܺ��� ���󼭸� �̵��մϴ�.
TLE : 40��
*/

#include <bits/stdc++.h>

using namespace std;

/*
�ܺ��� ���� n : n�� 1 �̻� 200 ������ �ڿ���
��� ������ ��ġ�� ��� �迭 weak : weak�� ���̴� 1 �̻� 15 �����Դϴ�.
	���� �ٸ� �� ������� ��ġ�� ���� ���� �־����� �ʽ��ϴ�.
	��� ������ ��ġ�� ������������ ���ĵǾ� �־����ϴ�.
	weak�� ���Ҵ� 0 �̻� n - 1 ������ �����Դϴ�.
�� ģ���� 1�ð� ���� �̵��� �� �ִ� �Ÿ��� ��� �迭 dist : dist�� ���̴� 1 �̻� 8 �����Դϴ�.
	dist�� ���Ҵ� 1 �̻� 100 ������ �ڿ����Դϴ�.
��� ������ �����ϱ� ���� ������ �ϴ� ģ�� ���� �ּҰ��� return(��� �����ص� �� �Ǹ� -1 ����)
*/

constexpr int INF = 1 << 30;
constexpr int NEEDFORCHECK = 1;
constexpr int FINISHCHECK = 2;
int ans = INF, weakNum, friendNum;

vector<int> weakVisited, friendVisited;

void DFS(vector<int>&weak, vector<int>&dist, int n, int friendCnt, int fixedCnt, int index) { // index = weak�� �ε���
	if (fixedCnt == weakNum) {
		ans = min(ans, friendCnt);
		return;
	}

	if (index == weakNum) {
		return;
	}

	if (friendCnt > ans) return;

	vector<int> weakVisitedCopy(weakVisited);
	if (weakVisited[weak[index]] == FINISHCHECK) {
		DFS(weak, dist, n, friendCnt, fixedCnt, index + 1);
	}
	for (int f = 0; f < friendNum; ++f) {
		if (friendVisited[f]) continue; // �̹� ���� ��
		friendVisited[f] = 1;

		// + �ð�
		int start = weak[index];
		int step = dist[f];
		int cnt = 0;
		for (int s = 0; s <= step; ++s) {
			if (weakVisited[(start + s) % n] == NEEDFORCHECK) {
				weakVisited[(start + s) % n] = FINISHCHECK;
				++cnt;
			}
		}
		DFS(weak, dist, n, friendCnt + 1, fixedCnt + cnt, index + 1);
		weakVisited = weakVisitedCopy;

		// - �ݽð�
		cnt = 0;
		for (int s = 0; s <= step; ++s) {
			if (weakVisited[(start - s + n) % n] == NEEDFORCHECK) {
				weakVisited[(start - s + n) % n] = FINISHCHECK;
				++cnt;
			}
		}
		DFS(weak, dist, n, friendCnt + 1, fixedCnt + cnt, index + 1);
		weakVisited = weakVisitedCopy;
		friendVisited[f] = 0;
	}
	DFS(weak, dist, n, friendCnt, fixedCnt, index + 1);
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	weakNum = (int)weak.size();
	friendNum = (int)dist.size();
	ans = INF;

	// set visited
	weakVisited = vector<int>(n, 0);
	friendVisited = vector<int>(n, 0);

	for (int& w : weak) weakVisited[w] = NEEDFORCHECK;

	DFS(weak, dist, n, 0, 0, 0);

	answer = ans;
	if (answer == INF) answer = -1;
	return answer;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	cout << solution(12, { 1,5,6,10 }, { 1,2,3,4 }) << '\n';
	cout << solution(12, { 1,3,4,9,10 }, { 3,5,7 }) << '\n';

	return 0;
}