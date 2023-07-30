// https://blog.yjyoon.dev/kakao/2021/01/04/kakao-wallcheck/

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

#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 1 << 30;

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = INF;
	int weakLen = (int)weak.size();

	// ������ ���� weak �迭 ����
	for (int i = 0; i < weakLen; ++i) {
		weak.push_back(weak[i] + n);
	}

	sort(dist.begin(), dist.end()); // ���� ����� ���� ����

	do {
		for (int i = 0; i < weakLen; ++i) {
			int start = weak[i]; // �˻� ���� ����
			int finish = weak[i + weakLen - 1]; // �˻� ���� ���� ����
			for (int j = 0; j < dist.size(); ++j) {
				start += dist[j];
				if (start >= finish) { // ��� ���� �湮 �Ϸ� �� Ż��
					answer = min(answer, j + 1);
					break;
				}

				// ���� �˻� ���� ���� ���ϱ�
				// => �������� �湮�� �������� ū weak ���� �� ���� ���� ����
				auto next = upper_bound(begin(weak), end(weak), start);
				start = *next;
			}
		}
	} while (next_permutation(begin(dist), end(dist))); // ��� ������ ���� Ž��

	if (answer == INF) return -1;

	return answer;
}


int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	cout << solution(12, { 1,5,6,10 }, { 1,2,3,4 }) << '\n';
	cout << solution(12, { 1,3,4,9,10 }, { 3,5,7 }) << '\n';

	return 0;
}
