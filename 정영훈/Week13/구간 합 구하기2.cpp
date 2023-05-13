// Segment Tree ����
// Lazy Propagation (������ ���� �����̹Ƿ� �׳� segment tree�δ� �ð����� �Ұ�����)
// https://yabmoons.tistory.com/442

#include <iostream>
#include <cmath> // ceil, log2
#include <vector>

using namespace std;

vector<long long> SegmentTree, Arr, Lazy;

long long Make_SegmentTree(int Node, int Start, int End)
{
    if (Start == End)
        return SegmentTree[Node] = Arr[Start];

    int Mid = (Start + End) / 2; // overflow ����

    long long Left_Result = Make_SegmentTree(Node * 2, Start, Mid);        // ���� �ڽ�
    long long Right_Result = Make_SegmentTree(Node * 2 + 1, Mid + 1, End); // ������ �ڽ�

    return SegmentTree[Node] = Left_Result + Right_Result;
}

void Lazy_Update(int Node, int Start, int End)
{
    if (Lazy[Node] != 0) // 0�� �ƴ� ��
    {
        SegmentTree[Node] = SegmentTree[Node] + (End - Start + 1) * Lazy[Node];
        if (Start != End) // ������ ��� �ڽĿ��� ����
        {
            Lazy[Node * 2] += Lazy[Node];
            Lazy[Node * 2 + 1] += Lazy[Node];
        }
        Lazy[Node] = 0;
    }
}

void UpdateSegmentTree(int Node, int Start, int End, int Left, int Right, long long Value)
{
    Lazy_Update(Node, Start, End); // ó���� ���� lazy �����ϱ�
    if (Right < Start || Left > End)
        return;
    if (Left <= Start && End <= Right) // ���� ã�� ����[Left, Right]�� �� ū ���
    {
        SegmentTree[Node] = SegmentTree[Node] + (End - Start + 1) * Value;
        if (Start != End) // �����̶�� �ڽĿ��� ����
        {
            Lazy[Node * 2] += Value;
            Lazy[Node * 2 + 1] += Value;
        }
        return; // �� �� �ʿ� ������ return
    }

    int Mid = (Start + End) / 2;
    UpdateSegmentTree(Node * 2, Start, Mid, Left, Right, Value);       // ���� �ڽ�
    UpdateSegmentTree(Node * 2 + 1, Mid + 1, End, Left, Right, Value); // ������ �ڽ�
    SegmentTree[Node] = SegmentTree[Node * 2] + SegmentTree[Node * 2 + 1];
}

long long Sum(int Node, int Start, int End, int Left, int Right)
{
    Lazy_Update(Node, Start, End); // ó���� ���� lazy ����
    if (Right < Start || Left > End)
        return 0; // �� �ʿ� ����(�ʿ��� ������ �ƴ�)
    if (Left <= Start && End <= Right)
        return SegmentTree[Node]; // �� ������ �ʿ� ����.

    int Mid = (Start + End) / 2;
    long long Left_Result = Sum(Node * 2, Start, Mid, Left, Right);        // ���� �ڽ�
    long long Right_Result = Sum(Node * 2 + 1, Mid + 1, End, Left, Right); // ������ �ڽ�
    return Left_Result + Right_Result;
}

int main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    int N, M, K;
    cin >> N >> M >> K;
    Arr.resize(N);
    for (int n = 0; n < N; ++n)
    {
        cin >> Arr[n];
    }

    int Tree_Height = (int)ceil(log2(N));
    int Tree_Size = (1 << (Tree_Height + 1));
    SegmentTree.resize(Tree_Size);
    Lazy.resize(Tree_Size);
    Make_SegmentTree(1, 0, N - 1);

    for (int t = 0; t < M + K; ++t)
    {
        int a, b, c;
        long long d;
        cin >> a >> b >> c;
        if (a == 1)
        { // b��° �� ~ c��° ���� += d
            cin >> d;
            UpdateSegmentTree(1, 0, N - 1, b - 1, c - 1, d);
        }
        else
        { // [b, c] ��
            cout << Sum(1, 0, N - 1, b - 1, c - 1) << '\n';
        }
    }

    return 0;
}