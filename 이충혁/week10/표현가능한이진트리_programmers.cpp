#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

vector<int> bin_num; // ������ ��

int init()
{
    bin_num.clear();
    return 0;
}

// 10������ 2���� ���ͷ� ��ȯ ( ���� �� ������ ���� �� )
int dec_to_bin(long long num) {
    while (num) {
        bin_num.push_back(int(num % 2));
        num /= 2;
    }
    return 0;
}

// ��ȭ ����Ʈ���� ����� ���� 2^x - 1 ��ŭ 0 ä��� 
// ���� �� ���� ä���� �״�� push back �ص� ��
int fill_dec()
{
    int full_size = 2;
    int bin_size = bin_num.size(); // size�� �ٲ�� ������ �̸� �����ؾ��� !!
    while (1) {
        if (bin_num.size() <= full_size - 1) break;
        full_size *= 2;
    }
    for (int i = 0; i < full_size - bin_size - 1; i++)
    {
        bin_num.push_back(0);
    }
    return 0;
}

// �ڽĳ�� ��� �ڽ��� ��� 0�̶�� ���� �ĵ� ��
int zero_check(int left, int right)
{
    for (int i = left; i <= right; i++)
    {
        if (bin_num[i] != 0)
            return 0;
    }
    return 1; 
}

// �̺�Ž�� �ϵ��� �ڸ��鼭 Ž���ϱ�
int possible_check(int left, int right) {
    if (right == left)
        return 1;
    if(zero_check(left, right)) 
        return 1;

    int mid = (right - left) / 2 + left;


    if (bin_num[mid] == 1 && possible_check(left, mid - 1) && possible_check(mid + 1, right))
        return 1;
    else 
        return 0;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    for (auto num : numbers)
    {
        init();
        dec_to_bin(num);
        fill_dec();
        answer.push_back(possible_check(0, bin_num.size() - 1));
    }
    return answer;
}


int main()
{
    vector<int> answer;
    answer = solution({ 7, 42, 5 });

    for (auto val : answer)
        cout << val << " ";


	return 0;
}