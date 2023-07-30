## Week22 (23.07.24 ~ 23.08.06)
| ���� | �� ���� | ��ũ |
| :---: | :---: | :---: |
| [���ο� ����](#���ο�-����) | ����, �ùķ��̼� | [���� ��ũ](https://www.acmicpc.net/problem/17780) |
| [��հ� �� ��ġ](#��հ�-��-��ġ) | ���� | [���� ��ũ](https://school.programmers.co.kr/learn/courses/30/lessons/60061) |
| [��� ����](#���-����) | Network Flow | [���� ��ũ](https://www.acmicpc.net/problem/2188) |

<br>

## ���ο� ����
- [���� ��ũ](https://www.acmicpc.net/problem/17780)
- ���� ���� : ����, �ùķ��̼�

<br>

## ��հ� �� ��ġ
- [���� ��ũ](https://school.programmers.co.kr/learn/courses/30/lessons/60061)
- ���� ���� : ����.
- ����ؾ� �� ���׵��� ���� ����߾��µ�.. �ٸ� ���� ������ ������!!
- [�ؼ� ��ũ](https://tech.kakao.com/2019/10/02/kakao-blind-recruitment-2020-round1/)
  - ���� 5��.
```cpp
// ��ġ => ���� => ��ġ�ϸ� 2�� ����.. ���� �ФФФФФФ�
for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];
		if (b == 0) continue; // ������ ��ŵ
		if (Map[x][y][a]) {
			answer.push_back({ x,y,a });
		}
	}

	sort(begin(answer), end(answer), [](vector<int>& first, vector<int>& second) {
		// x��ǥ �������� �������� �����ϸ�, x��ǥ�� ���� ��� y��ǥ �������� �������� ����
		// x, y��ǥ�� ��� ���� ��� ����� ������ �տ� ���� �˴ϴ�.
		if (first[0] == second[0] && first[1] == second[1]) {
			return first[2] < second[2];
		}
		else if (first[0] == second[0]) {
			return first[1] < second[1];
		}
		return first[0] < second[0];
	});
```

<br>

## ��� ����
- [���� ��ũ](https://www.acmicpc.net/problem/2188)
- ���� ���� : Network Flow
