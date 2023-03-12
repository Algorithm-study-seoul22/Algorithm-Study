#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 21e8;

// 1. DFS�� ���� ������ �������� �ִ� �˰�� �ڵ��� �̴�
// 3. ����ġ��1: �˰�� �ڵ����� �պ��� ��°� ���ٸ� ���� ���� �ʴ´�.


struct Info_limit {
  int alp, cop;
};

enum PB_CONST {
  alp_req, cop_req, alp_rwd, cop_rwd, cost
};

Info_limit min_limit, max_limit; // �ּ�, �ִ� �˰�� �ڵ���
int now_time = 0; // dfs ���µ� �ð�
int min_time = MAX;

int dfs(int alp, int cop, vector<vector<int>>& problems) // level
{
  // ���� ����
  if (alp >= max_limit.alp && cop >= max_limit.cop)
  {
    if (now_time < min_time)
      min_time = now_time;
    return 0;
  }

  for (int i = 0; i < problems.size(); i++)
  {
    if (problems[i][alp_rwd] + problems[i][cop_rwd] <= problems[i][cost]) // ���� �ڽ�Ʈ ��� ��� �����尡 ���� ��
      continue;

    if (problems[i][alp_req] > alp || problems[i][cop_req] > cop) // ���� �䱸������ ���� �ȵɶ�
      continue;

    now_time += problems[i][cost];

    dfs(alp + problems[i][alp_rwd], cop + problems[i][cop_rwd], problems);

    now_time -= problems[i][cost];
  }

  now_time += 1;

  if(alp < max_limit.alp)
    dfs(alp + 1, cop, problems);

  if (cop < max_limit.cop)
    dfs(alp, cop + 1, problems);

  now_time -= 1;

  return 0;
}

int solution(int alp, int cop, vector<vector<int>> &problems) {
  int answer = 0;
  
  // init 
  min_limit = { MAX, MAX };
  max_limit = { 0, 0 };

  // �˰��, �ڵ����� �ִ� �ּҸ� ����
  for (int i = 0; i < problems.size(); i++)
  {
    if (max_limit.alp < problems[i][alp_req])
      max_limit.alp = problems[i][alp_req];

    if (max_limit.cop < problems[i][cop_req])
      max_limit.cop = problems[i][cop_req];
  }

  dfs(alp, cop, problems);
  answer += min_time;

  return answer;
}


// ���⼭���ʹ� ����¿�

int input(int &alp, int &cop, vector<vector<int>> &temp_pb)
{
  cin >> alp;
  cin >> cop;

  int size;
  cin >> size;

  int temp[5];
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < 5; j++)
      cin >> temp[j];

    temp_pb.push_back({ temp[0], temp[1], temp[2], temp[3], temp[4] });
  }

  return 0;
}

int main()
{
  freopen("input.txt", "r", stdin);


  int alp, cop ;
  vector<vector<int>> temp_pb;
  input(alp, cop, temp_pb);
  cout << solution(alp, cop, temp_pb);

  return 0;
}
