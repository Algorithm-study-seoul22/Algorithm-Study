#include <string>
#include <vector>
#include <deque>

using namespace std;

int solution(vector<int> stones, int k) {
    const int MAXIMUM{200'000'000};
    deque<int> maximum_stone;
    deque<int> index;
    maximum_stone.push_back(MAXIMUM);
    index.push_back(0);
    int answer{MAXIMUM};
    int stone_it{1};
    for(const int stone : stones) {
        if(index.front() + k <= stone_it) {
            maximum_stone.pop_front();
            index.pop_front();
        }
        while(!maximum_stone.empty() && (maximum_stone.back() < stone)) {
            maximum_stone.pop_back();
            index.pop_back();
        }
        maximum_stone.push_back(stone);
        index.push_back(stone_it);
        int front_stone = maximum_stone.front();
        answer = answer < front_stone ? answer : front_stone;
        ++stone_it;
    }
    return answer;
}