/*
RGB�Ÿ����� ���� N�� �ִ�. �Ÿ��� �������� ��Ÿ�� �� �ְ�, 1�� ������ N�� ���� ������� �ִ�.
���� ����, �ʷ�, �Ķ� �� �ϳ��� ������ ĥ�ؾ� �Ѵ�. 
������ ���� ����, �ʷ�, �Ķ����� ĥ�ϴ� ����� �־����� ��, �Ʒ� ��Ģ�� �����ϸ鼭 ��� ���� ĥ�ϴ� ����� �ּڰ��� ���غ���.

1�� ���� ���� 2��, N�� ���� ���� ���� �ʾƾ� �Ѵ�.
N�� ���� ���� N-1�� ���� ���� ���� �ʾƾ� �Ѵ�.
i(2 �� i �� N-1)�� ���� ���� i-1��, i+1�� ���� ���� ���� �ʾƾ� �Ѵ�.
2168KB, 0ms
*/

#include <bits/stdc++.h>

constexpr int INF = (int)10e8;
using namespace std;

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	
	int N;
	cin >> N;
	vector<vector<int>> colors(N, vector<int>(3,0));
	vector<vector<int>> DP;
	for(vector<int>& row : colors) {
		cin >> row[0] >> row[1] >> row[2];
	}

	int ans = INF;
	for(int color = 0; color < 3; ++ color) { // ���ۺ��� ���ε��� ����ϱ�
		DP.assign(begin(colors), end(colors));
		DP[0][0] = DP[0][1] = DP[0][2] = INF;
		DP[0][color] = colors[0][color];
		for(int i=1;i<N;++i) {
			DP[i][0] += min(DP[i-1][1], DP[i-1][2]);
			DP[i][1] += min(DP[i-1][0], DP[i-1][2]);
			DP[i][2] += min(DP[i-1][0], DP[i-1][1]);
		}

		for(int i = 0; i < 3; ++i) {
			if(i==color) continue;
			ans = min(ans, DP[N-1][i]);
		}

	}

	cout << ans << '\n';

	return 0;
}