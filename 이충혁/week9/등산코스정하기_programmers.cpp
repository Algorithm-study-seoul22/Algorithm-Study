#include <iostream>
#include<string> // �̰� ����
#include <vector>
#include <queue>

using namespace std;
const int MAX_NUM = 21e8;
const int MAX_NODE = 50505;

struct Info { // �׷��� ����ü
    int to;
    int time; // �ɸ��� �ð�

    bool operator<(Info next) const
    {
        if (time > next.time)
            return true;

        return false;
    }
};

// �ּ� ����ġ�� ��� ���ϴ� ����� �ƴ� �ѹ� �� üũ�ϴ� ������ ���ͽ�Ʈ��� Ǯ��
// ������ ���� �ּ� �ð��Ѱ� + �ּ� ���츮 �� �̱� ������ �������� ���


vector<Info> graph[MAX_NODE]; // ����(���, ��ȣ)
int dist[MAX_NODE]; // ���ͽ�Ʈ�� �ִ� ( �������� ���� ���� �ִ� �� ���길 �� )

int summit_check[MAX_NODE] = { 0, };

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {

    for (int i = 0; i < paths.size(); i++) 
    {
        graph[paths[i][0]].push_back({ paths[i][1], paths[i][2] });
        graph[paths[i][1]].push_back({ paths[i][0], paths[i][2] });
    }

    // ���� ���� ����
    for (int i = 0; i < summits.size(); i++)
        summit_check[summits[i]] = 1;

    for (int i = 0; i < MAX_NODE; i++)
    {
        dist[i] = 21e8;
    }

    priority_queue<Info> pq;
    for (int i = 0; i < gates.size(); i++)
    {
        dist[gates[i]] = 0;
        pq.push({ gates[i], dist[gates[i]] });
    }
    while (!pq.empty()) 
    {
        Info now = pq.top(); 
        pq.pop();
        if (dist[now.to] != now.time)
            continue;
        for (int i = 0; i < graph[now.to].size(); i++) 
        {
            if (dist[graph[now.to][i].to] <= max(dist[now.to], graph[now.to][i].time))
                continue;
            dist[graph[now.to][i].to] = max(dist[now.to], graph[now.to][i].time);
            if (!summit_check[graph[now.to][i].to])
                pq.push({ graph[now.to][i].to, dist[graph[now.to][i].to] });
        }
    }

    // ������ ���츮�� �� ���ؿ� �´°� ã��
    int ans = summits[0];
    for (int i=0; i<summits.size(); i++)
    {
        if (dist[summits[i]] < dist[ans])
            ans = summits[i];
        else if (dist[summits[i]] == dist[ans] && summits[i] < ans)
            ans = summits[i];
    }
    return vector<int>({ ans, dist[ans] });
}


int main()
{
    vector<int> ans;
    ans = solution(6, { {1, 2, 3},{2, 3, 5},{2, 4, 2}, {2, 5, 4},{3, 4, 4},{4, 5, 3},{4, 6, 1},{5, 6, 1} }, { 1, 3 }, { 5 });
    
    cout << ans[0] << " " << ans[1];
    return 0;
}