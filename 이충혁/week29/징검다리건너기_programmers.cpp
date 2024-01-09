#include<iostream>

#include <string>
#include <vector>

using namespace std;

/*
이분 탐색!

200,000,000 <= 2^28

시간 복잡도 == 200,000 * 28 

*/

int solution(vector<int> stones, int k) {
    int answer = 0;

    int left = 1;
    int right = 2e8;
    
    while (left <= right)
    {
        int mid = (left + right) / 2;

        int pre_jump = -1;
        int success_flag = 1;
        for (int i = 0; i < stones.size(); i++)
        {
            if (i - pre_jump > k)
            {
                success_flag = 0;
                break;
            }

            if (stones[i] >= mid)
            {
                pre_jump = i;
            }
        }

        if (stones.size() - pre_jump > k)
            success_flag = 0;

        if (success_flag)
        {
            answer = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }

    return answer;
}



int main()
{
    int ans = 0;

    ans = solution({ 2, 4, 5, 3, 2, 1, 4, 2, 5, 1 },	3);

    cout << ans << endl;

    return 0;
}