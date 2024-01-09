#include <iostream>
#include <vector>

constexpr int dirY[4] = {-1, 1, 0, 0};
constexpr int dirX[4] = {0, 0, 1, -1};

struct Mold{
	int s;	// s: 1초동안 곰팡이가 움직이는 거리
	int d;	// d: 이동 방향 -> 상, 하, 우, 좌
	int b;	// b: 곰팡이의 크기
};

struct Coordinate{
	int y, x;
};

int N, M, K;
std::vector<std::vector<Mold>> MAP;

int answer;	// answer: 인턴이 채취한 곰팡이의 크기의 총 합

void Solution(){

	for(int x=0; x<M; ++x){

		// 제일 빨리 발견한 곰팡이를 채취합니다.
		// 곰팡이를 채취하고 나면 해당 칸은 빈칸이 됩니다.

		for(int y=0; y<N; ++y){
			if(MAP[y][x].b == 0) {continue;}

			answer += MAP[y][x].b;
			MAP[y][x] = {0, 0, 0};
			break;
		}

		// 곰팡이는 이동을 시작합니다.

		std::vector<std::vector<Mold>> tmp;
		tmp.assign(N, std::vector<Mold>(M, {0, 0, 0}));

		for(int y=0; y<N; ++y){
			for(int x=0; x<M; ++x){
				if(MAP[y][x].b == 0) {continue;}

				Mold curr = MAP[y][x];
				Coordinate currLoc = {y, x};

				for(int s=0; s<curr.s; ++s){
					currLoc = {currLoc.y + dirY[curr.d], currLoc.x + dirX[curr.d]};

					// 벽에 도달하면 반대로 방향을 바꾸고 속력을 유지한 채로 이동합니다
					if(currLoc.y < 0 || currLoc.x < 0 || currLoc.y >= N || currLoc.x >= M) {
						if(curr.d == 0) {curr.d = 1;}
						else if(curr.d == 1) {curr.d = 0;}
						else if(curr.d == 2) {curr.d = 3;}
						else if(curr.d == 3) {curr.d = 2;}

						currLoc = {currLoc.y + dirY[curr.d], currLoc.x + dirX[curr.d]};
						currLoc = {currLoc.y + dirY[curr.d], currLoc.x + dirX[curr.d]};
					}
				}
				tmp[currLoc.y][currLoc.x] = tmp[currLoc.y][currLoc.x].b < curr.b ? curr : tmp[currLoc.y][currLoc.x];
			}
		}
		MAP = tmp;
	}

	return;
}

void Input(){

	std::cin >> N >> M >> K;

	MAP.assign(N, std::vector<Mold>(M, {0, 0, 0}));

	for(int i=0; i<K; ++i){
		int y, x, s, d, b;
		std::cin >> y >> x >> s >> d >> b;

		if(d == 1 || d == 2) {MAP[y-1][x-1] = {s % (2 * (N - 1)), d-1, b};}
		else if(d == 3 || d == 4) {MAP[y-1][x-1] = {s % (2 * (M - 1)), d-1, b};}

		
	}


	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}