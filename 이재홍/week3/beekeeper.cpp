#include <iostream>
#include <vector>
#include <algorithm>
#define DIR 6       // available direction
#define MAXLV 4     // size of pattern
#define LEN 4       // size of pattern
#define LEN2 7      // height of test ground
#define HMAX 15     // max hive height
#define WMAX 15     // max hive width
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(Coordinate p)
        {return {x + p.x, y + p.y};}
    Coordinate operator-(Coordinate p)
        {return {x - p.x, y - p.y};}
    bool operator<(const Coordinate& p)
        {return y < p.y || (y == p.y && x < p.x);}
};

int H, W;
vector<vector<Coordinate>> pattern[2]; // vector of all pattern available
vector<Coordinate> reachable; // all available nodes
vector<int> reachable_level; // track size of available nodes per level
vector<Coordinate> path; // track each pattern
int visited[LEN2][LEN] = {0,}; // test ground to find patterns available, 1: banned, 2: visited
int hive[HMAX][WMAX]; // save hive information

// declare direct array
Coordinate d[2][DIR] = { // direction array for odd and even column node
    {{-1,-1},{ 0,-1},{ 1,-1},{ 1, 0},{ 0, 1},{-1, 0}},
    {{-1, 0},{ 0,-1},{ 1, 0},{ 1, 1},{ 0, 1},{-1, 1}}
};

bool dfs_out_of_bound(const Coordinate& p) { // check out of bound
    return p.x < 0 || p.y < 0 || LEN <= p.x || LEN2 <= p.y;
}

void dfs(int level, int now_idx) { // select from all adjacent nodes included in pattern, start node at {0, LEN - 1}
    // condition check
    Coordinate now = reachable[now_idx];
    if(MAXLV <= level) { // reached max size of pattern
        pattern[0].push_back(path);
        return;
    }
    // add reachable nodes
    reachable_level[level] = reachable_level[level - 1]; // abandon previous adjacent nodes
    for(int i = 0; i < DIR; ++i) {
        Coordinate next = now + d[now.x % 2][i];
        if(dfs_out_of_bound(next)) {continue;} // skip out of bound node
        if(visited[next.y][next.x]) {continue;} // skip visited or banned node
        int ableFlag = 1; // flag to eliminate duplicate nodes
        for(int j = 0; j < DIR; ++j) { // check adjacent nodes of next node
            if(j == (i + DIR / 2) % DIR) {continue;}
            Coordinate next_next = next + d[next.x % 2][j];
            if(visited[next_next.y][next_next.x] == 2) { // if outer node exists, do not add to reachable list (already added to list)
                ableFlag = 0;
                break;}
        }
        if(ableFlag) { // if there are no adjacent nodes arount next node, add to reachable list
            reachable[reachable_level[level]] = next; // add to reachable list
            ++reachable_level[level]; // modify max reachable node size
        }
    }
    // backtracking
    for(int i = now_idx + 1; i < reachable_level[level]; ++i) { // select not checked nodes
        Coordinate next = reachable[i];
        // process
        visited[next.y][next.x] = 2;
        path.push_back(next);
        // recursive
        dfs(level + 1, i); // update level and last selected node index
        // unprocess
        visited[next.y][next.x] = 0;
        path.pop_back();
    }
    return;
}

// make all tile pattern
void make_pattern() {
    for(int i = 0; i < LEN - 1; ++i)
        {visited[i][0] = 1;} // ban nodes top of start point (start point is top at column)
        visited[LEN - 1][0] = 2; // set start node as visited
    reachable = vector<Coordinate>(MAXLV * DIR); // reserve size
    reachable[0] = {0, LEN - 1}; // start at left-most, top of pattern
    reachable_level = vector<int>(MAXLV); // reserve size
    reachable_level[0] = 1; // set size of available node at level 0 to 1 ({0, LEN - 1})
    path.push_back({0, LEN - 1}); // set start node
    // make pattern for even column
    dfs(1, 0); // find all patterns origin of {0, LEN - 1}
    vector<vector<Coordinate>>::iterator it = pattern[0].begin();
    vector<vector<Coordinate>>::iterator it_end = pattern[0].end();
    for(; it != it_end; ++it) {
        vector<Coordinate>::iterator it_it = it->begin();
        vector<Coordinate>::iterator it_it_end = it->end();
        for(; it_it != it_it_end; ++it_it)
            {*it_it = *it_it - Coordinate({0, LEN - 1}); // shift start point of pattern to {0, 0}
        }
    }
    // make pattern for odd column
    pattern[1] = vector<vector<Coordinate>>(pattern[0]); // copy even column patterns
    it = pattern[1].begin();
    it_end = pattern[1].end();
    for(; it != it_end; ++it) {
        vector<Coordinate>::iterator it_it = it->begin();
        vector<Coordinate>::iterator it_it_end = it->end();
        for(; it_it != it_it_end; ++it_it) {
            if(it_it->x % 2)
                {*it_it = *it_it + Coordinate({0, 1}); // modify odd column shifts
            }
        }
    }
}

bool out_of_bound(const Coordinate& p) { // true if out of bound
    return p.x < 0 || p.y < 0 || W <= p.x || H <= p.y;
}

int get_value(Coordinate p) { // get max value starts with position p
    vector<vector<Coordinate>>::iterator it = pattern[p.x % 2].begin();
    vector<vector<Coordinate>>::iterator it_end = pattern[p.x % 2].end();
    int max_value = 0;
    for(; it != it_end; ++it) { // iterate for all patterns
        int value = 0;
        int valid = 1;
        vector<Coordinate>::iterator it_it = it->begin();
        vector<Coordinate>::iterator it_it_end = it->end();
        for(; it_it != it_it_end; ++it_it) {
            Coordinate now = p + *it_it; // move to pattern position
            if(out_of_bound(now)) {valid = 0; break;} // skip if pattern gets out of map
            value += hive[now.y][now.x]; // sum hive value to temporal value
        }
        if(valid) {max_value = max_value < value ? value : max_value;} // update max value
    }
    return max_value;
}

int main() {
    // make pattern
    make_pattern();
    // read 2 int
    cin >> H >> W;
    // read H*W array
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            cin >> hive[i][j];
        }
    }
    // sweep pattern for each hive cell
    int max_value = 0;
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            int value = get_value({j, i}); // get value with start node {j, i}
            max_value = max_value < value ? value : max_value; // update max value
        }
    }
    // print max value
    cout << max_value;
}