/*
������ ���� n, ��������� ��Ÿ���� s, A�� ���������� ��Ÿ���� a, B�� ���������� ��Ÿ���� b, ���� ������ ���� �ýÿ���� ��Ÿ���� fares
�� ����� s���� ����ؼ� ������ ���� �������� �ýø� Ÿ�� ���ٰ� ������ ��, ���� ���� �ýÿ���� ���

�������� n�� 3 �̻� 200 ������ �ڿ��� => ���� ������ n * 100 => floyd-warshall ����
���� s, a, b�� 1 �̻� n ������ �ڿ����̸�, ���� ���� �ٸ� ���Դϴ�.
  ��, �������, A�� ��������, B�� ���������� ���� ��ġ�� �ʽ��ϴ�.
fares�� 2���� ���� �迭�Դϴ�.
fares �迭�� ũ��� 2 �̻� n x (n-1) / 2 �����Դϴ�.
  fares �迭�� �� ���� [c, d, f] �����Դϴ�.
  c������ d���� ������ ���� �ýÿ���� f���̶�� ���Դϴ�.
  ���� c, d�� 1 �̻� n ������ �ڿ����̸�, ���� ���� �ٸ� ���Դϴ�.
  ��� f�� 1 �̻� 100,000 ������ �ڿ����Դϴ�.
  fares �迭�� �� ���� �� ���� �ýÿ���� 1���� �־����ϴ�. ��, [c, d, f]�� �ִٸ� [d, c, f]�� �־����� �ʽ��ϴ�.
������� s���� �������� a�� b�� ���� ��ΰ� �����ϴ� ��츸 �Է����� �־����ϴ�.
*/

#include<bits/stdc++.h>

using namespace std;
constexpr int INF = 1 << 29;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    answer = INF;

    vector<vector<int>> dist(n+1, vector<int>(n+1,INF));
    for(int i=1;i<=n;++i) dist[i][i] = 0;

    for(auto& row : fares) {
      auto [from, to, cost] = make_tuple(row[0], row[1], row[2]); // self loop X, �� ���� ���� ������ ���� 1��
      dist[from][to] = dist[to][from] = cost; // ������ ����
    }

    for(int k=1;k<=n;++k) {
      for(int i=1;i<=n;++i) {
        for(int j=1;j<=n;++j) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    for(int v=1;v<=n;++v) { // v������ �Բ� �̵�
      int cost = dist[s][v] + dist[v][a] + dist[v][b];
      answer = min(answer, cost);
    }

    return answer;
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);

  vector<vector<int>> fares1{{4, 1, 10}, {3, 5, 24}, {5,6,2}, {3,1,41},{5,1,24},{4,6,50},{2,4,66},{2,3,22},{1,6,25}};
  cout << solution(6, 4, 6, 2, fares1) << '\n';

  vector<vector<int>> fares2{{5,7,9},{4,6,4},{3,6,1},{3,2,3},{2,1,6}};
  cout << solution(7,3,4,1,fares2) << '\n';

  vector<vector<int>> fares3{{2,6,6},{6,3,7},{4,6,7},{6,5,11},{2,5,12},{5,3,20},{2,4,8},{4,3,9}};
  cout << solution(6,4,5,6,fares3) << '\n';

  return 0;
}