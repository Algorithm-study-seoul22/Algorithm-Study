#include <string>
#include <vector>
#define DIR 4

using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &pos) {return {x + pos.x, y + pos.y};}
};

Coordinate d[DIR] = {{ 1, 0}, { 0,-1}, { 0, 1}, {-1, 0}}; // direction array
string s = "dlru"; // order by dictionary

bool out(int n, int m, Coordinate &pos) { // return if pos is out of map from (1,1) to (n,m)
    return pos.x < 1 || pos.y < 1 || n < pos.x || m < pos.y;
}

int get_len(Coordinate &pos1, Coordinate &pos2) { // get minimum route length from pos1 to pos2
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = ""; // initiate answer string
    Coordinate now = {x, y}; // current position
    Coordinate end = {r, c}; // destination
    int len = get_len(now, end); // get minimum route length from start to destination
    if(k < len || ((k ^ len) & 1)) {return "impossible";} // can't reach (length, odd-even)
    for(int iter = 1; iter <= k; ++iter) { // gready approach
        for(int dir = 0; dir < DIR; ++dir) { // select fastest available direction in dictionary order
            Coordinate next = now + d[dir];
            if(k - iter < get_len(next, end) || out(n, m, next)) {continue;} // destination not reachable, out of map
            now = next;
            answer += s[dir];
            break; // s[dir] is fastest available character
        }
    }
    return answer;
}