// 첫 코드(스타트택시.cpp)에
// findCloseCustomer, possibleToReach 에서
// 조건 확인하는 부분을 따로 람다로 빼보면 좋을 거 같아서 해보긴 했는데, 그닥인 거 같습니다..
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 상좌우하
int dx[]{ -1,0,0,1 };
int dy[]{ 0,-1,1,0 };
int N, M, fuel; // 칸 크기, 승객 수, 연료 양

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
	bool operator<(const coord& other) const { // pq는 반대로
		if (this->x == other.x) return this->y > other.y;
		return this->x > other.x;
	}
};

struct Info {
	coord customer;
	coord goal;
	Info(coord c, coord g) : customer(c), goal(g) {}
};

coord taxi(0, 0);

template<typename T> // lambda 전달
int FunctionWithLambda(vector<vector<int>>& Map, vector<int>& customerVisited, Info& info, T func) {
	priority_queue<coord> pq;
	pq.push(taxi);

	int usefuels{};
	vector<vector<int>> visited(N, vector<int>(N, 0));
	while (!pq.empty()) {
		// int cursize{ pq.size() }; 
		// pq.size()가 unsigned __int64구나
		int cursize = static_cast<int>(pq.size());
		priority_queue<coord> tempPQ;
		for (int si{}; si < cursize; ++si) {
			coord now = pq.top();
			pq.pop();

            // 기존 구현에서 람다로 따로 처리하는 부분.
			int chk = func(now, usefuels, info);
			if (chk != -1) return chk;
			// 가까운 승객에게 갈 수 있는가? chk = 승객 인덱스
			// 승객 -> 승객이 원하는 지점에 갈 수 있는가? chk = 1이면 갈 수 있음을 의미함.

			for (int di = 0; di < 4; ++di) {
				int nx = now.x + dx[di];
				int ny = now.y + dy[di];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (visited[nx][ny]) continue;
				if (Map[nx][ny] == 1) continue;
				visited[nx][ny] = 1;
				// pq.push(coord(nx, ny));
				tempPQ.push(coord(nx, ny));
			}
		}
		while (!tempPQ.empty()) {
			coord now = tempPQ.top(); tempPQ.pop();
			pq.push(now);
		}
		usefuels++;
		if (usefuels > fuel) { // 넘 멀어
			return -1;
		}
	}
	return -1; // 도달 x
}


int main() {
	cin.tie(NULL)->sync_with_stdio(false);

	cin >> N >> M >> fuel;

	vector<vector<int>> Map(N, vector<int>(N, 0));

	for (auto& row : Map) {
		for (int& m : row) {
			cin >> m;
		}
	}
	cin >> taxi.x >> taxi.y;
	taxi.x--; taxi.y--;

	vector<Info> infos(M, Info(coord(0, 0), coord(0, 0)));
	vector<int> customerVisited(M, 0);
	for (int m{}; m < M; ++m) {
		cin >> infos[m].customer.x >> infos[m].customer.y >>
			infos[m].goal.x >> infos[m].goal.y;
		infos[m].customer.x--; infos[m].customer.y--;
		infos[m].goal.x--; infos[m].goal.y--;
		Map[infos[m].customer.x][infos[m].customer.y] = 2 + m; // 승객 번호 2부터 시작
	}

    // 따로 람다로 뺌
	auto ChkCloseCustomer = [&](coord& now, int usefuels, Info& info) -> int {
		if (Map[now.x][now.y] > 1 && !customerVisited[Map[now.x][now.y] - 2]) {
			customerVisited[Map[now.x][now.y] - 2] = 1;
			taxi = now;
			fuel -= usefuels;
			return Map[now.x][now.y] - 2; // 승객 인덱스
		}
		return -1;
	};

    // 따로 람다로 뺌
	auto ReachbleCheck = [&](coord& now, int usefuels, Info& info) -> int {
		if (now.x == info.goal.x && now.y == info.goal.y) {
			taxi = now;
			fuel += usefuels;
			return 1; // true
		}
		return -1;
	};

	int count{}; // 태운 승객 수
	while (1) {
		if (count == M) break; // 모든 승객 도착

		Info temp(coord(0, 0), coord(0, 0));
		// flood fill - 가장 가까운 승객 찾기
		// 현재 연료로 도달 가능한가?
		int nextCustomerIndex = FunctionWithLambda(Map, customerVisited, temp, ChkCloseCustomer);
		if (-1 == nextCustomerIndex) {
			fuel = -1;
			break;
		}

		// flood fill - 승객이 원하는 지점까지 가기
		// 현재 연료로 도달 가능한가?
		if (-1 == FunctionWithLambda(Map, customerVisited, infos[nextCustomerIndex], ReachbleCheck)) {
			fuel = -1;
			break;
		}
		++count;
	}
	cout << fuel << '\n';

	return 0;
}