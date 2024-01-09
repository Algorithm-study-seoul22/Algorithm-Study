#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

// 방향 벡터
constexpr int dirY[4] = { 0, 1, 0, -1 };
constexpr int dirX[4] = { 1, 0, -1, 0 };

struct Coordinate {	// 좌표
	int y, x;
};

struct Student {

	int likeCnt;
	int emptyCnt;
	Coordinate coordi;

	bool operator < (const Student& next) const {
		if (likeCnt != next.likeCnt) return likeCnt < next.likeCnt;
		if (emptyCnt != next.emptyCnt) return emptyCnt < next.emptyCnt;
		if (coordi.y != next.coordi.y) return coordi.y > next.coordi.y;
		if (coordi.x != next.coordi.x) return coordi.x > next.coordi.x;

		return false;
	}
};

const bool Cmp(const std::vector<int>& left, const std::vector<int>& right) {
	if (left[0] != right[0]) return left[0] < right[0];

	return false;
}

int Solution(const int& n, std::vector<std::vector<int>>& student) {

	int answer = 0;	// answer: 모든 학생들이 놀이기구에 탑승한 이후의 최종 점수

	std::vector<std::vector<int>> MAP;	// MAP[i][j]: 놀이기구의 i 행 j 열에 탑승한 학생 번호
	MAP.assign(n, std::vector<int>(n, 0));

	for (int i = 0; i < n * n; ++i) {
		std::vector<int> curr = student[i];	// curr: 탑승할 학생이 좋아하는 학생의 번호
		std::priority_queue<Student> pq;	// pq: 학생들의 정보를 저장할 우선 순위 큐

		int currStudentNum = curr[0];	// currStudentNum: 탑승하고자 하는 학생 번호

		for (int y = 0; y < n; ++y) {
			for (int x = 0; x < n; ++x) {
				Coordinate currCoordi = { y, x };	// currCoordi: 현재 좌표
				Student currScore = { 0, 0, {0, 0} };	// currScore: 현재 점수 -> {좋아하는 친구의 수, 비어있는 칸의 수, 좌표}

				if (MAP[currCoordi.y][currCoordi.x] != 0) { continue; }	// 이미 자리가 찼다면 continue

				for (int dir = 0; dir < 4; ++dir) {
					Coordinate nextCoordi = { currCoordi.y + dirY[dir], currCoordi.x + dirX[dir] };	// nextCoordi: 다음 좌표

					if (nextCoordi.y < 0 || nextCoordi.x < 0 || nextCoordi.y >= n || nextCoordi.x >= n) { continue; }	// 범위 벗어나면 continue

					for (int j = 1; j <= 4; ++j) {	// 좋아하는 학생
						if (MAP[nextCoordi.y][nextCoordi.x] == curr[j]) { ++currScore.likeCnt; }
					}

					if (!MAP[nextCoordi.y][nextCoordi.x]) { ++currScore.emptyCnt; }	// 비어 있는 칸

					currScore.coordi = { y, x };	// 좌표
					pq.push(currScore);	// 우선 순위 큐에 넣음
				}
			}
		}		
		Student decision = pq.top();	// 가장 우선 순위가 높은 자리에 앉음

		MAP[decision.coordi.y][decision.coordi.x] = currStudentNum;	// 놀이기구 탑승 기록
	}

	// 점수 계산 -> 인덱스로 접근하기 위해 정렬
	std::sort(student.begin(), student.end(), Cmp);

	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			Coordinate curr = { y, x };	// curr: 좌표
			int currStudentNum = MAP[curr.y][curr.x] - 1;	// currStudentNum: 학생 번호
			int likeCnt = 0;	// likeCnt: 좋아하는 학생의 수

			for (int dir = 0; dir < 4; ++dir) {
				Coordinate next = { y + dirY[dir], x + dirX[dir] };

				if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n) { continue; }	// 범위 벗어나면 continue

				for (int i = 1; i <= 4; ++i) {
					if (student[currStudentNum][i] == MAP[next.y][next.x]) {
						++likeCnt;	// 좋아하는 학생 발견
						break;
					}
				}
			}

			if (!likeCnt) { continue; }	// 좋아하는 학생이 없다면 continue
			answer += std::pow(10, likeCnt - 1);
		}
	}

	return answer;
}

void Input(int& n, std::vector<std::vector<int>>& student) {

	std::cin >> n;

	student.assign(n * n, std::vector<int>(5, 0));

	for (int i = 0; i < n*n; ++i) {
		std::cin >> student[i][0] >> student[i][1] >> student[i][2] >> student[i][3] >> student[i][4];
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;	// n: 격자의 크기 -> 3<=n<=20
	std::vector<std::vector<int>> student;	// student[i][j]: i 학생에 좋아하는 j 번째 학생의 번호

	Input(n, student);

	std::cout << Solution(n, student);

	return 0;
}