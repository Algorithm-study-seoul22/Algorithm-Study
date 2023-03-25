#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int TRIE_KIND = 10; // TRIE ���� ��
const int MAX_STR = 10101; // ���ڿ� �󸶳� ��������

struct Trie {
	Trie* Node[TRIE_KIND];
	bool node_end;

	Trie()
	{
		for (int i = 0; i < TRIE_KIND; i++)
		{
			Node[i] = nullptr; // �̸� nullptr�� �ʱ�ȭ
		}
		node_end = false;
	}

	bool insert(int index, string &str)
	{
		if (str.size() == index)
		{
			node_end = true; // ������ ���� ���� ���ڿ� node_end ����
			return true;
		}

		int num = (int)(str[index] - '0'); // char -> 10������

		if (Node[num] == nullptr)
		{
			Node[num] = new Trie();
		}
		else if(Node[num]->node_end == true) // ���� �̰� ���λ� ���
		{
			return false;
		}

		return Node[num]->insert(index + 1, str);
	}

};

int N; // ���ڿ��� ����
vector<string> vec_str;

int input()
{
	cin >> N;
	vec_str.resize(N); // ���⼭ ������ ����
	for (int i = 0; i < N; i++)
	{
		cin >> vec_str[i];
	}
	return 0;
}

bool solve_func()
{
	sort(vec_str.begin(), vec_str.end()); // insert���� ���� Ž�� �ϱ����� ����

	Trie num_trie;

	for (int i = 0; i < vec_str.size(); i++)
	{
		if (!num_trie.insert(0, vec_str[i]))
		{
			return false;
		}
	}

	return true;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int tc = 0; tc < T; tc++)
	{
		// init
		vector<string>().swap(vec_str); // ���� �ʱ�ȭ

		input();
		if (solve_func())
			cout << "YES\n";
		else
			cout << "NO\n";
	}


	return 0;
}