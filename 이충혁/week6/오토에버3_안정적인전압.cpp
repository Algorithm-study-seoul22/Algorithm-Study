#include<iostream>
#include<unordered_map>
using namespace std;
const int MAX_ARR = 202020;

int N;

long long ori_arr[MAX_ARR]; // ���� ���� ���� ����
long long add_arr[MAX_ARR]; // ���� ���� ��� (������ ������ ����)
long long zero_cnt[MAX_ARR]; // �� �κ� ���� 0�� ī��Ʈ ( left )
unordered_map<int, int> DAT; // ���� + MAX_ARR �� DAT

int input()
{
    cin >> N;

    cin >> ori_arr[0];
   

    for (int i = 0; i < N; i++)
    {
        cin >> ori_arr[i];
        
        if (i == 0)
        {
            add_arr[i] = ori_arr[i];
            if (add_arr[i] == 0) // i�� 0�� �� i-1 ���� ���ؼ� ����
                zero_cnt[i] = 1;
            else
                zero_cnt[i] = 0;
        }
        else
        {
            add_arr[i] = add_arr[i - 1] + ori_arr[i];
            if (add_arr[i] == 0)
                zero_cnt[i] = zero_cnt[i - 1] + 1;
            else
                zero_cnt[i] = zero_cnt[i - 1];
        }


        // DAT�� �־��ֱ�

        if (DAT.find(add_arr[i]) == DAT.end())
        {
            DAT.insert({ add_arr[i], 1});
        }
        else
        {
            DAT[add_arr[i]]++;
        }
    }

    return 0;
}

// 

int solve_func()
{
    int ans = 0;

    for (int i = 0; i < N; i++)
    {
        int zero_now = 0; // �̹� index�� 0 ����
        
        if (i != 0) // ���� �ٲ�� ���� left�� �ִ� 0 ������ ����
        {
            zero_now += zero_cnt[i - 1];
        }

        // �ٲ�� index ���� 0���� �ٲ� �� �ִ� ������ ���  ���� (right)
        if (DAT.find(ori_arr[i]) != DAT.end())
        {
            zero_now += DAT[ori_arr[i]];
        
        }

        DAT[add_arr[i]]--;

        if (ans < zero_now)
            ans = zero_now;
    }

    return ans;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);

    input();
    

    cout << solve_func();
    return 0;
}