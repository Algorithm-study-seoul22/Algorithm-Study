#include <string>
#include <vector>

using namespace std;

int solution(vector<int> stones, int k) {
    int left = stones[0];
    int right = stones[0];
    for(const int stone : stones) {
        left = left < stone ? left : stone;
        right = right > stone ? right : stone;
    }
    while(left <= right) {
        int mid = (left + right) >> 1;
        int steps = 0;
        bool is_available = true;
        for(const int stone : stones) {
            ++steps;
            if(k < steps) {is_available = false; break;}
            if(mid <= stone) {steps = 0;}
        }
        if(k <= steps) {is_available = false;}
        if(is_available) {left = mid + 1;}
        else {right = mid - 1;}
    }
    return right;
}