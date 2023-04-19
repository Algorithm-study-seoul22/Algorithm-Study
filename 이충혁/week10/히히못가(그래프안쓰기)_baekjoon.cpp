#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int MAT_MAX = 1010;
const int ry[] = { 1, -1, 0, 0, 1, 1, -1, -1 }; // �⺻ ���� �迭�� 0~3�� �����¿�
const int rx[] = { 0, 0, -1, 1, 1, -1, -1, 1 };

const int MAX_ANS = 21e8;

struct coordi {
    int y, x;
};

struct Info {
    coordi pt;
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
// 2. ���� MAT���� ����ġ�� ���� ���������� bfs �ϴµ� ���� ���� ������ ����ġ �������� �ʰ�
// ������ ���� �� ���� ������ �� ���� ����ġ��� ���� �ϸ鼭 ����

int N;
string MAT_str[MAT_MAX];
int MAT[MAT_MAX][MAT_MAX] = { 0, };  // �׷��� ���� �� ���� ���� �� number ����
int land_size = 0; // ���ĺ��� ��ġ�� ��찡 �ִ�. �ٽ� num �ٿ��ָ鼭 �� ĭ���� ���� ����
int land_cnt[MAT_MAX * MAT_MAX] = { 0, }; // �� ���� ĭ ��
set<int> start_set; // ���� �κ� ��� ����� üũ

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

int visited[MAT_MAX][MAT_MAX] = { 0, };

int bfs_ans()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            visited[i][j] = MAX_ANS;

    priority_queue<Info> pq;



    for (int i = 1; i <= N; i++)
    {
        if (start_set.find(MAT[1][i]) == start_set.end() &&
            i != 1)
        {
            start_set.insert(MAT[1][i]);
            pq.push({ {1, i}, land_cnt[MAT[1][i]]});
            visited[1][i] = land_cnt[MAT[1][i]];
        }

        if (start_set.find(MAT[i][N]) == start_set.end() &&
            i != N)
        {
            start_set.insert(MAT[i][N]);
            pq.push({ {i, N}, land_cnt[MAT[i][N]] });
            visited[i][N] = land_cnt[MAT[i][N]];
        }

    }


    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();

        if (now.pt.y == N || now.pt.x == 1)
        {
            if (ans > now.d)
                ans = now.d;
            return 0;
        }

        for (int i = 0; i < 8; i++)
        {
            Info next = now;
            next.pt.y += ry[i];
            next.pt.x += rx[i];

            if (MAT[next.pt.y][next.pt.x] <= 0) continue;

            if (MAT[now.pt.y][now.pt.x] != MAT[next.pt.y][next.pt.x])
                next.d += land_cnt[MAT[next.pt.y][next.pt.x]];

            if (visited[next.pt.y][next.pt.x] <= next.d)
            {
                continue;
            }

            visited[next.pt.y][next.pt.x] = next.d;
            pq.push(next);
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

    // 2. ����ġ ���� �׷��� �Ⱦ��� Ž�� �ϱ� (���ͽ�Ʈ�� ���)
    bfs_ans();

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