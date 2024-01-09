#include <string>
#include <vector>
#include <algorithm>

int solution(std::vector<int> stones, int k) {	// stones[i]: i 번째 디딤돌의 내구도, k: 건너뛸 수 있는 디딤돌의 최대 칸수
    int answer = 1;	// 최대 징검다리를 건널 수 있는 니니즈 친구들
    
    int left = 21e8, right = 0;	// left, right: 이분 탐색
    
    for(const int& stone : stones) {
        left = std::min(left, stone);
        right = std::max(right, stone);
    }
    
    if(k==1) {	// 건너뛸 수 있는 디딤돌의 수가 1이라면 최소값 return
		return left;
	}
    
    while(left <= right) {
        int middle = (left + right) / 2;	// middle: 니니즈 친구들의 수
        
        bool flag = true;	// flag: 징검다리를 건널 수 있다면 true
        int zeroLen = 0;	// zeroLen: 연속된 건널 수 없는 징검다리의 수
        for(const int& stone : stones) {
            if(stone - middle > 0) {	// 건널 수 있음
                zeroLen = 0;
            }
            else{	// 건널 수 없음
                ++zeroLen;
                if(zeroLen >= k) {	// k 보다 건널 수 없는 디딤돌의 수가 많다면 false 후 break
                    flag = false;
                    break;
                }
            }
        }
        
        if(flag) {	// 건널 수 있는 경우
            left = middle + 1;
            answer = std::max(middle, answer);
        }
        else {	// 건널 수 없는 경우
            right = middle - 1;
        }        
    }    
    
    return answer + 1;
}