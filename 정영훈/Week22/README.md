## Week22 (23.07.24 ~ 23.08.06)
| 薦鯉 | 鎧 羨悦 | 元滴 |
| :---: | :---: | :---: |
| [歯稽錘 惟績](#歯稽錘-惟績) | 姥薄, 獣皇傾戚芝 | [庚薦 元滴](https://www.acmicpc.net/problem/17780) |
| [奄逆引 左 竺帖](#奄逆引-左-竺帖) | 姥薄 | [庚薦 元滴](https://school.programmers.co.kr/learn/courses/30/lessons/60061) |
| [逐紫 壕舛](#逐紫-壕舛) | Network Flow | [庚薦 元滴](https://www.acmicpc.net/problem/2188) |

<br>

## 歯稽錘 惟績
- [庚薦 元滴](https://www.acmicpc.net/problem/17780)
- 庚薦 政莫 : 姥薄, 獣皇傾戚芝

<br>

## 奄逆引 左 竺帖
- [庚薦 元滴](https://school.programmers.co.kr/learn/courses/30/lessons/60061)
- 庚薦 政莫 : 姥薄.
- 壱形背醤 拝 紫牌級精 穿採 壱形梅醸澗汽.. 陥献 汽辞 庚薦亜 持医製!!
- [背竺 元滴](https://tech.kakao.com/2019/10/02/kakao-blind-recruitment-2020-round1/)
  - 庚薦 5腰.
```cpp
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
```

<br>

## 逐紫 壕舛
- [庚薦 元滴](https://www.acmicpc.net/problem/2188)
- 庚薦 政莫 : Network Flow, 戚歳 古暢
