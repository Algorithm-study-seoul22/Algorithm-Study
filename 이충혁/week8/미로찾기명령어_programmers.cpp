#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int DIR = 4;

enum {
    DOWN, LEFT, RIGHT, UP
};

struct coordi {
    int x, y;
};

bool possible_func(int dist, int k)
{
    // 1. �Ÿ��� k ���� Ŭ ��
    if (dist > k)
        return false;

    // 2. dist �� k �� Ȧ¦�� �ٸ� ��
    if (dist % 2 != k % 2)
        return false;

    return true;
}


// n, m : ���� ��ǥ
// x, y : ��� - x, r �� ������ �̴� ��������
// r, c : ����
string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";

    // 4���� ���� DAT (������� ī��Ʈ)
    int DAT[DIR] = { 0, };

    int dist = abs(x - r) + abs(y - c);

    // ������ �� ������ �������� �Ǵ� ( �Ÿ�, Ȧ�� ¦�� )
    if (!possible_func(dist, k)) {
        answer = "impossible";
        return answer;
    }

    // ������ ����� ���̷� �ʼ��� ������ �ϴ� ���� ���� ���
    if (r - x >= 0)
        DAT[DOWN] = r - x;
    else
        DAT[UP] = x - r;

    if (c - y >= 0)
        DAT[RIGHT] = c - y;
    else
        DAT[LEFT] = y - c;

    // k �� dist���� / 2 ��ŭ �Ӵٰ��� �ؾ���
    // �Ӵٰ��� �� ���� ��
    // 1. ������ ��ǥ �Ѱ踦 �ʰ��ϸ� �ȵǰ�
    // 2. (d, u), (l, r), (r, l) �� �Ӵٰ��ٸ� ��ȿ�� (u, d)�� ������� �и�
    // 3. (d, u), (l, r)�� ���� �ȼ��� ������ (r, l) �� l ���ڿ� �߰��ϴ� �κ� �ڿ� �߰� �� �����̹Ƿ� ���� ����
    int return_cnt = (k - dist) / 2;
    coordi now = { x + DAT[DOWN], y - DAT[LEFT] }; // ���ڿ� ��θ� down�� left�� �������� �̸� ���Ѵ�.
    int RL_cnt = 0;
    while (return_cnt > 0)
    {
        return_cnt--; // continue �ҰŶ� �̸� cnt ���ֱ�

        if (now.x + 1 <= n) // ���������� ������ ����
        {
            DAT[DOWN]++;
            DAT[UP]++;
            now.x++;
            continue;
        }

        else if (now.y - 1 > 0)
        {
            DAT[LEFT]++;
            DAT[RIGHT]++;
            now.y--;
            continue;
        }

        // ������ �� r, l 
        RL_cnt++;
    }


    // answer ���ڿ��� ������
    //  DOWN, LEFT, RIGHT, UP ����
    for (int i = 0; i < 4; i++) // ���� ������ �������
    {
        while (DAT[i] > 0)
        {
            switch (i)
            {
            case 0:
                answer += 'd';
                break;
            case 1:
                answer += 'l';
                break;
            case 2:
                answer += 'r';
                break;
            case 3:
                answer += 'u';
                break;

            }

            DAT[i]--;
        }

        if (i == LEFT)
        {
            while (RL_cnt > 0)
            {
                answer += "rl";
                RL_cnt--;
            }
        }
    }

    return answer;
}

int main()
{
    //cout <<solution(3,	3,	1,	2,	3,	3,	4);
    //cout << solution(3, 4, 2, 3, 3, 1, 5);
    //cout << solution(2, 2, 1, 1, 2, 2, 2);

    return 0;
}