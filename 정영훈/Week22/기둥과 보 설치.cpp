/*
build_frame [x, y, a, b]
	x, y : 亜稽, 室稽
	a : 0(奄逆), 1(左)
	b : 0(肢薦), 1(竺帖)
鋭帳
1. 奄逆精 郊韓 是拭 赤暗蟹 左税 廃楕 魁 採歳 是拭 赤暗蟹, 暁澗 陥献 奄逆 是拭 赤嬢醤 杯艦陥.
2. 左澗 廃楕 魁 採歳戚 奄逆 是拭 赤暗蟹, 暁澗 丞楕 魁 採歳戚 陥献 左人 疑獣拭 尻衣鞠嬢 赤嬢醤 杯艦陥.

幻鉦, 拙穣聖 呪楳廃 衣引亜 繕闇聖 幻膳馬走 省澗陥檎 背雁 拙穣精 巷獣桔艦陥.

姥繕弘精 嘘託繊 疎妊研 奄層生稽 左澗 神献楕, 奄逆精 是楕 号狽生稽 竺帖 暁澗 肢薦杯艦陥.
姥繕弘戚 違帖亀系 竺帖馬澗 井酔人, 蒸澗 姥繕弘聖 肢薦馬澗 井酔澗 脊径生稽 爽嬢走走 省柔艦陥.

置曽 姥繕弘 莫殿 [x, y, a]
	x, y : 奄逆, 左税 嘘託繊 疎妊 = 亜稽, 室稽
	a : 0(奄逆), 1(左)
	x疎妊 奄層 神硯託授 舛慶 板 x亜 旭生檎 y疎妊 奄層 神硯託授 舛慶
	x, y亜 乞砧 旭精 井酔 奄逆戚 左左陥 蒋拭
*/
// https://wadekang.tistory.com/28 凧壱..
// 巷譲聖 設公 速澗亜..
// 奄逆戚蟹 左 溌昔精 設 梅澗汽 戚雌馬惟 舛慶背辞 隔生形陥亜 叔鳶敗...
#include <bits/stdc++.h>

using namespace std;

// 神嫌 伊装遂 敗呪 2鯵
bool install_item(int n, vector<vector<vector<int>>>& Map, int x, int y, int a) {
	if (a == 0) { // 奄逆 竺帖
		if (y == 0) return true; // 郊韓是拭 赤暗蟹
		if (x > 0 && Map[x - 1][y][1]) return true; // 左税 神献楕 魁 是
		if (y < n && Map[x][y][1]) return true; // 左税 図楕 魁 是
		if (y > 0 && Map[x][y - 1][0]) return true; // 陥献 奄逆 是
	}
	else { // 左 竺帖
		if (y > 0 && Map[x][y - 1][0]) return true; // 図楕 魁 焼掘 奄逆
		if (x < n && y > 0 && Map[x + 1][y - 1][0]) return true; // 神献楕 魁 焼掘 奄逆
		if (x > 0 && x < n && Map[x - 1][y][1] && Map[x + 1][y][1]) return true; // 丞楕 魁 採歳 陥献 左
	}
	return false;
}

bool remove_item(int n, vector<vector<vector<int>>>& Map, int x, int y, int a) {
	Map[x][y][a] = 0;

	if (a == 0) { // 奄逆 肢薦
		// 是拭 奄逆 赤聖 凶, 竺帖 亜管?
		if (y < n && Map[x][y + 1][0] && !install_item(n, Map, x, y + 1, 0)) return false;

		// 是拭 左 赤聖 凶, 竺帖 亜管?
		if (y < n && Map[x][y + 1][1] && !install_item(n, Map, x, y + 1, 1)) return false;
		if (x > 0 && y < n && Map[x - 1][y + 1][1] && !install_item(n, Map, x - 1, y + 1, 1)) return false;
	}
	else {
		// 是拭 奄逆 赤聖 凶, 竺帖 亜管?
		if (Map[x][y][0] && !install_item(n, Map, x, y, 0)) return false;
		if (x < n && Map[x + 1][y][0] && !install_item(n, Map, x + 1, y, 0)) return false;

		// 陥献 左人 尻衣鞠嬢 赤聖 凶, 竺帖 亜管?
		if (x > 0 && Map[x - 1][y][1] && !install_item(n, Map, x - 1, y, 1)) return false;
		if (x < n && Map[x + 1][y][1] && !install_item(n, Map, x + 1, y, 1)) return false;
	}

	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	vector <vector<vector<int>>> Map(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 0))); // 奄逆精 n拭亀 兜聖 呪 赤製.
	// [0] : 奄逆
	// [1] : 左

	for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];

		// 鋭帳 溌昔
		if (b == 1) { // 竺帖
			if (a == 0) { // 奄逆
				// 郊韓 是拭 赤暗蟹 左税 廃楕 魁 採歳 是拭 赤暗蟹 暁澗 陥献 奄逆 是戚暗蟹.
				// if(install_item(n, Map, x, y, a)) { // 溌昔遂 坪球
				if (y == 0 || (x > 0 && Map[x-1][y][1]) || Map[x][y][1] || Map[x][y - 1][0]) {
					Map[x][y][a] = 1;
				}
			}
			else { // 左
				// 左澗 廃楕 魁 採歳戚 奄逆 是拭 赤暗蟹,丞楕 魁 採歳戚 陥献 左人 疑獣拭 尻衣鞠嬢 赤澗走
				// if (install_item(n, Map, x, y, a)) { // 溌昔遂 坪球
				if ((Map[x][y - 1][0] || Map[x + 1][y - 1][0]) || (x > 0 && Map[x - 1][y][1] && Map[x + 1][y][1])) {
					Map[x][y][a] = 1;
				}
			}
		}
		else { // 肢薦
			if (a == 0) { // 奄逆
				// if (!remove_item(n, Map, x, y, a)) Map[x][y][a] = 1; // 溌昔遂 坪球
				bool chk = true;

				// 奄逆 是拭 左亜 赤暗蟹 =>
				if (Map[x][y + 1][1]) { // right
					// 陥献 廃 楕 魁戚 奄逆戚暗蟹, 丞楕 魁拭 左亜 赤澗走 溌昔
					if (!(Map[x + 1][y][0] || (x > 0 && Map[x - 1][y + 1][1] && Map[x + 1][y + 1][1]))) {
						chk = false;
					}
				}
				if (x > 0 && Map[x - 1][y + 1][1]) { // left
					// 奄逆戚 赤暗蟹, 丞楕 魁戚 左昔走 溌昔
					if (!(Map[x - 1][y][0] || (x > 1 && Map[x - 2][y + 1][1] && Map[x][y + 1][1]))) {
						chk = false;
					}
				}
				// 奄逆 是拭 奄逆戚 赤暗蟹 => 
				if (Map[x][y + 1][0]) {
					// 陥献 左亜 赤澗走 溌昔
					if (!(Map[x][y + 1][1] || (x > 0 && Map[x - 1][y + 1][1]))) {
						chk = false;
					}
				}

				if (chk) { // 肢薦 亜管
					Map[x][y][a] = 0;
				}
			}
			else { // 左
				// if (!remove_item(n, Map, x, y, a)) Map[x][y][a] = 1; // 溌昔遂 坪球
				bool chk = true;
				// 左 丞 新拭 左亜 赤暗蟹 =>
				if(x > 0 && Map[x - 1][y][1]) { // left
					if (!(Map[x - 1][y - 1][0] || Map[x][y - 1][0])) { // 左 購拭 奄逆 溌昔
						chk = false;
					}
				}
				if (Map[x + 1][y][1]) { // right
					if (!(Map[x + 1][y - 1][0] || (x + 2 <= n && Map[x + 2][y - 1][0]))) { // 左 購拭 奄逆 溌昔
						chk = false;
					}
				}
				// 左 丞 新拭 奄逆戚 赤暗蟹 => {
				if (Map[x][y][0]) {
					// 奄逆 購拭 奄逆 溌昔 + 陥献 左 溌昔
					if (!(Map[x][y - 1][0] || (x > 0 && Map[x - 1][y][1]))) {
						chk = false;
					}
				}
				if (Map[x + 1][y][0]) {
					// 奄逆 購拭 奄逆 溌昔 + 陥献 左 溌昔
					if (!(Map[x + 1][y - 1][0] || Map[x + 1][y][1])) {
						chk = false;
					}
				}

				if (chk) { // 肢薦 亜管
					Map[x][y][a] = 0;
				}
			}
		}
	}

	/*
	// 戚惟 訊 照 吉 暗走..
	// 竺帖 => 肢薦 => 竺帖馬檎 2腰 級嬢亜革.. せせ ばばばばばばば
	for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];
		if (b == 0) continue; // 肢薦澗 什典
		if (Map[x][y][a]) {
			answer.push_back({ x,y,a });
		}
	}

	sort(begin(answer), end(answer), [](vector<int>& first, vector<int>& second) {
		// x疎妊 奄層生稽 神硯託授 舛慶馬悟, x疎妊亜 旭聖 井酔 y疎妊 奄層生稽 神硯託授 舛慶
		// x, y疎妊亜 乞砧 旭精 井酔 奄逆戚 左左陥 蒋拭 神檎 桔艦陥.
		if (first[0] == second[0] && first[1] == second[1]) {
			return first[2] < second[2];
		}
		else if (first[0] == second[0]) {
			return first[1] < second[1];
		}
		return first[0] < second[0];
	});
	*/
	for (int x{}; x <= n; ++x) {
		for (int y{}; y <= n; ++y) {
			if (Map[x][y][0]) answer.push_back({ x,y,0 });
			if (Map[x][y][1]) answer.push_back({ x,y,1 });
		}
	}

	return answer;
}

template <typename T>
void Print(vector<vector<T>>& vec) {
	for (auto& row : vec) {
		cout << '[';
		for (auto& v : row) {
			cout << v << ' ';
		}
		cout << "], ";
	}
	cout << '\n';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	vector<vector<int>> ans1 = solution(5, {{1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1}});
	Print(ans1);

	vector<vector<int>> ans2 = solution(5, {{0, 0, 0, 1}, {2, 0, 0, 1}, {4, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {2, 1, 1, 1}, {3, 1, 1, 1}, {2, 0, 0, 0}, {1, 1, 1, 0}, {2, 2, 0, 1}});
	Print(ans2);

	return 0;
}