#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int MAT_MAX = 1010;
const int ry[] = { 1, -1, 0, 0 }; // �⺻ ���� �迭�� 0~3�� �����¿�
const int rx[] = { 0, 0, -1, 1 };

const int cy[] = { 0, 1, 1, 1 }; // graph ���ῡ ����� ���� �迭
const int cx[] = { 1, 1, 0, -1 };

const int MAX_ANS = 21e8;

struct coordi {
    int y, x;
};

struct Info {
    int to;
    int d;

    bool operator < (Info next) const
    {
        if (d > next.d)
            return true;
        return false;
    }
};


// 1. �� ������ ĭ�� ����
// ĭ�� ���鼭 MAT �迭�� �� ���� num(bfs �ѹ� ���� �� ���� 1�� Ŀ��)
// �� ���� ĭ�� land_cnt�� �����Ѵ�. ( MAT �迭�� visited ���ҵ� ���� �Ѵ� )
// 2. �ֺ��� ���� ���� �׷����� ����
// graph���� ����ġ�� ���� �� ��庰 ����ġ��
// �׸��� �� �� ���� ���� ���� ������ ������
// 3. ���� ������ ���۶� ���� ���ͽ�Ʈ�� ������
// �ּڰ� ã�� ã���߿� �ּڰ� ������ ����ġ��

int N;
string MAT_str[MAT_MAX];
int MAT[MAT_MAX][MAT_MAX] = { 0, };  // �׷��� ���� �� ���� ���� �� number ����
int land_size = 0; // ���ĺ��� ��ġ�� ��찡 �ִ�. �ٽ� num �ٿ��ָ鼭 �� ĭ���� ���� ����
int land_cnt[MAT_MAX * MAT_MAX] = { 0, }; // �� ���� ĭ ��
set<int> us[MAT_MAX * MAT_MAX]; // us[from].find(set) ���� ������ �Ǿ��ִ��� �뵵�� ������ 

vector<Info> graph[MAT_MAX * MAT_MAX];
set<int> st_land, ed_land; // ���� ��, ���� ��
int dist[MAT_MAX * MAT_MAX];

int ans = MAX_ANS;

int init()
{
    for (int i = 0; i < MAT_MAX; i++)
    {
        for (int j = 0; j < MAT_MAX; j++)
        {
            MAT[i][j] = -1; // ��Ÿ��
        }
    }

    return 0;
}

int input()
{
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            MAT[i][j] = 0; // ��Ÿ�� ���� �κ� �ٽ� 0����
        }
    }

    string str;
    for (int i = 1; i <= N; i++)
    {
        cin >> str;
        MAT_str[i] = ' ' + str;
    }

    return 0;
}

// ������ ĭ�� ���� �� ������ MAT int �迭�� �ٲ���
int bfs_cnt(coordi st)
{
    land_size++;
    land_cnt[land_size] = 1;
    queue<coordi> q;
    q.push(st);
    MAT[st.y][st.x] = land_size;
    char land_name = MAT_str[st.y][st.x];

    while (!q.empty())
    {
        coordi now = q.front();
        q.pop();


        for (int i = 0; i < 4; i++)
        {
            coordi next = now;
            next.y += ry[i];
            next.x += rx[i];

            if (MAT[next.y][next.x] != 0) continue;
            if (land_name != MAT_str[next.y][next.x]) continue;

            MAT[next.y][next.x] = land_size;
            land_cnt[land_size]++;

            q.push(next);
        }
    }

    return 0;
}

int dijkstra()
{
    // dijk init
    for (int i = 1; i <= land_size; i++)
        dist[i] = MAX_ANS;

    priority_queue<Info> pq;

    for (int i = 1; i <= land_size; i++)
    {
        auto iter = st_land.find(i);
        if (iter == st_land.end()) continue; // ���� ���� �ƴϸ� �ǳ� ��

        iter = ed_land.find(i);
        if (iter != ed_land.end()) // ���� ������ �� ���� �����̸� 
        {
            if (ans > land_cnt[i])
                ans = land_cnt[i];
            continue;
        }
        pq.push({ i, land_cnt[i] });
        dist[i] = land_cnt[i];
    }


    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();
        if (dist[now.to] < now.d)
            continue;

        if (ed_land.find(now.to) != ed_land.end())
        {
            ans = dist[now.to];
            return 0;
        }

        for (auto next : graph[now.to])
        {
            int ndist = now.d + next.d;
            if (dist[next.to] <= ndist) continue;
            if (ans <= ndist) continue;
            dist[next.to] = ndist;

            pq.push({ next.to, ndist });
        }
    }

    return 0;
}

int solve_func()
{
    // 1. ����� �κ� ���� ĭ �� ����

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (MAT_str[i][j] == '.') continue;
            if (MAT[i][j] != 0) continue;

            bfs_cnt({ i, j });
        }
    }

    // 2. �׷����� ���� 
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (MAT[i][j] == 0) continue;
            for (int k = 0; k < 4; k++)
            {
                coordi next = { i, j };
                next.y += cy[k];
                next.x += cx[k];


                if (MAT[next.y][next.x] <= 0) continue; // �ι̿� �ٸ���, ��Ÿ���� �ǳ� ��
                if (MAT[next.y][next.x] == MAT[i][j]) continue; // ���� ���̸� �ǳ� ��

                auto iter = us[MAT[i][j]].find(MAT[next.y][next.x]);
                if (iter != us[MAT[i][j]].end()) continue;

                us[MAT[i][j]].insert(MAT[next.y][next.x]);
                us[MAT[next.y][next.x]].insert(MAT[i][j]);

                graph[MAT[i][j]].push_back({ MAT[next.y][next.x], land_cnt[MAT[next.y][next.x]] });
                graph[MAT[next.y][next.x]].push_back({ MAT[i][j] , land_cnt[MAT[i][j]] });

            }


            // ���� ���� ���� ������ �� ��ƾ���� ���� ã��
            if ((i == 1 || j == N) && !(i == 1 && j == 1))
            {
                auto iter = st_land.find(MAT[i][j]);
                if (iter == st_land.end())
                {
                    st_land.insert(MAT[i][j]);
                }
            }

            if ((i == N || j == 1) && !(i == N && j == N))
            {
                auto iter = ed_land.find(MAT[i][j]);
                if (iter == ed_land.end())
                {
                    ed_land.insert(MAT[i][j]);
                }
            }

        }
    }

    // 3. ���ͽ�Ʈ�� �������� ������ ����
    dijkstra(); // ans ���⼭ ����


    return 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    init();
    input();
    solve_func();

    cout << ans;

    return 0;
}