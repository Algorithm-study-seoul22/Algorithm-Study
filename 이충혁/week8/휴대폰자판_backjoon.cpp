#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int TRIE_KIND = 30; // TRIE ���� �� ( ������ )

struct Trie {
	Trie* Node[TRIE_KIND];
	bool node_end;
	int node_cnt;

	Trie()
	{
		for (int i = 0; i < TRIE_KIND; i++)
		{
			Node[i] = nullptr;
		}
		node_end = false;
		node_cnt = 0;
	}

	~Trie() // �Ҹ��ڷ� ��� ���� ������Ѵ�
	{
		for (int i = 0; i < TRIE_KIND; i++)
		{
			if (Node[i] != nullptr)
			{
				delete Node[i];
			}
		}
	}

	int insert(int index, string& str)
	{
		if (str.size() == index)
		{
			node_end = true;
			return 0;
		}

		int num = (int)(str[index] - 'a');

		if (Node[num] == nullptr)
		{
			Node[num] = new Trie();
			node_cnt++; // �������� �þ�� cnt ++
		}
		Node[num]->insert(index + 1, str);
		return 0;
	}

	int find_cnt(int index, string& str, int cnt) // index : ��� ���ڿ� ���� �ִ���, cnt : ���ڿ� ã������ Ÿ������ ����
	{
		if (str.size() == index) // �������� : ���ڿ� ������ Ž��
		{
			return cnt;
		}

		if ((node_cnt > 1 || node_end == true) &&
			index != 0) // node_cnt �� node_end �κ��� ���� ����� Ʋ�� ( Ÿ�� '�ѹ�'�ϸ� �´� ������ ����)
		{
			cnt++;
		}

		int num = (int)(str[index] - 'a');
		return Node[num]->find_cnt(index + 1, str, cnt);
	}

};

int N; // ������ ���� �ܾ� ����


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	cout << fixed;
	cout.precision(2);

	while (cin >> N)
	{
		Trie* dictionary = new Trie();
		vector<string> words;
		words.resize(101010);
		int ans = 0;

		for (int i = 0; i < N; i++)
		{
			string temp;
			cin >> temp;
			words[i] = temp;
			dictionary->insert(0, temp);
		}

		for (int i = 0; i < N; i++)
		{
			ans += dictionary->find_cnt(0, words[i], 1);
		}

		cout << (double)ans / N << endl;

		delete dictionary;
	}

	return 0;
}