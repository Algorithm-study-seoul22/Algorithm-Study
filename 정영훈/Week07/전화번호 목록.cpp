// 한 글자에 대한 처리가 미흡했음.
#include <iostream>
#include <string>

using namespace std;

struct Trie {
	bool isFinished;
	Trie* next[10]; // 0 ~ 9
	Trie(bool isFinished) : isFinished(isFinished) {
		for (int i = 0; i < 10; ++i) {
			next[i] = nullptr;
		}
	}
	Trie() = default;
	~Trie() = default;
};
Trie* trie[10];

void init() {
	for (int i{}; i < 10; ++i) {
		trie[i] = nullptr;
	}
}

void release() {
	for (int i{}; i < 10; ++i) {
		if (trie[i] == nullptr) continue;
		delete trie[i];
		// 찾아가서 다 지워줘야 하나?
	}
}

// 입력 받은 str에 대해서 Trie 만들기
// 일관성이 깨지는 경우에 대해서 false return
bool MakeTrie(string& str) {
	int idx{ 0 };
	int startNum = str[idx] - '0';
	if (trie[startNum] == nullptr) { // 새로 할당
		trie[startNum] = new Trie(false);
	}
	else { // 이미 있다
		if (trie[startNum]->isFinished) {
			return false; // 한 글자에서 끝난 친구가 있다.
		}
		else if ((int)str.length() == 1) { // startNum이 마지막 문자인 경우
			return false;
		}
	}
	Trie* now = trie[startNum];

	for (; idx + 1 < (int)str.length(); ++idx) {
		int nextNum = str[idx + 1] - '0';
		if (now->next[nextNum] == nullptr) { // 새로
			now->next[nextNum] = new Trie(false);
		}
		else { // 기존
			if (now->next[nextNum]->isFinished) { // 여기서 끝난 친구가 있는 경우
				return false;
			}
			else if (idx + 1 == (int)str.length() - 1) { // nextNum이 마지막 문자인 경우
				return false;
			}
		}
		now = now->next[nextNum];
	}
	now->isFinished = true;
	return true;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int T{}, n;
	cin >> T;

	for (int tc{ 1 }; tc <= T; ++tc) {
		init();
		cin >> n; // 전화번호 수

		bool chk{ true }; // false : 일관성 없는 상태
		for (int i{}; i < n; ++i) {
			string str;
			cin >> str;

			if (chk) { // 일관성이 이미 없어진 경우 굳이 할 필요 없음.
				bool result = MakeTrie(str);
				if (!result) chk = false; // 일관성 깨짐
			}
		}
		if (chk) cout << "YES\n";
		else cout << "NO\n";

		release();
	}

	return 0;
}