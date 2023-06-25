/*
�� �Ǹſ��� �̸��� ���� �迭 enroll
	���� = 1 �̻� 10,000 ����
	��ȣ�� �̸��� ����.
�� �Ǹſ��� �ٴܰ� ������ ������Ų �ٸ� �Ǹſ��� �̸��� ���� �迭 referral
	enroll�� ���� ����
	i��°�� �ִ� �̸��� enroll ������ i��°�� �ִ� �Ǹſ��� ������ ������Ų ����� �̸�.
	"-"�� ��쿡 ������ ��õ�� ���� ������ ���� => center �ؿ�
	enroll�� �����ϴ� �̸��� ������ ������ ������ ����
�Ǹŷ� ���� �������� �Ǹſ� �̸��� ������ �迭 seller
	���� = 1 �̻� 100,000 ����
	i��° �̸��� i���� �Ǹ� ���� �����Ͱ� ��� �Ǹſ��� ���� �������� ��Ÿ��.
	���� �̸� �ߺ��� ����!
�Ǹŷ� ���� �������� �Ǹ� ������ ������ �迭 amount
	seller�� ���̿� ����.
	i��° �Ǹ� ���� �������� �Ǹŷ��� ��Ÿ��.
	�Ǹŷ��� ������ 1 �̻� 100������ �ڿ���

ĩ�� �� ���� �Ǹ��Ͽ� ������� ���� = 100��
��� ���� ���������� �̸��� 10 ���� �̳��� ���� ���ĺ� �ҹ��ڵ�θ� �̷����.

�� �Ǹſ��� ���� ���ͱ��� ������ �迭�� return �ϵ��� solution �Լ��� �ϼ����ּ���.
	�Ǹſ����� ��е� ���ͱ��� ������ ����Ͽ�(����������), 
	�Է����� �־��� enroll�� �̸��� ���Ե� ������ ���� �����ϸ� �˴ϴ�
*/

#include <bits/stdc++.h>

using namespace std;

constexpr int PRICE = 100;

unordered_map<string, int> um;

vector<vector<int>> graph;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
	vector<int> answer;
	const int SIZE = static_cast<int>(enroll.size()); // ��� ��
	answer.assign(SIZE, 0);
	graph = vector<vector<int>>(SIZE);

	for (int i = 0; i < SIZE; ++i) {
		um.emplace(enroll[i], i); // ���� enroll string�� �ش��ϴ� index ����
		if (referral[i] == "-") continue;
		graph[i].push_back(um[referral[i]]); // ���� index�� ���ſ� �����ߴ� enroll string�� �ش��ϴ� index ���� (�θ� index ����)
	}

	const int ALLSALE = static_cast<int>(seller.size());
	for (int i = 0; i < ALLSALE; ++i) {
		int earning = PRICE * amount[i];
		int index = um[seller[i]];
		while (earning) {
			int upper = earning / 10;
			if (upper == 0) {
				answer[index] += earning;
				break;
			}
			answer[index] += (earning - upper);
			earning /= 10;
			if (graph[index].size() == 0) break; // �θ� center
			index = graph[index][0];
		}
	}

	return answer;
}

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	// TC 1
	vector<string> enroll1{ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
	vector<string> referral1{ "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
	vector<string> seller1{ "young", "john", "tod", "emily", "mary" };
	vector<int> amount1{ 12,4,2,5,10 };
	for (int& a : solution(enroll1, referral1, seller1, amount1)) {
		cout << a << ' ';
	}
	cout << '\n';

	// TC 2
	vector<string> enroll2{ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
	vector<string> referral2{ "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
	vector<string> seller2{ "sam", "emily", "jaimie", "edward" };
	vector<int> amount2{ 2, 3, 5, 4 };
	for (int& a : solution(enroll2, referral2, seller2, amount2)) {
		cout << a << ' ';
	}
	cout << '\n';

	return 0;
}