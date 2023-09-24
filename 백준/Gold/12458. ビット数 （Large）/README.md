# [Gold II] ビット数 (Large) - 12458 

[문제 링크](https://www.acmicpc.net/problem/12458) 

### 성능 요약

메모리: 2084 KB, 시간: 0 ms

### 분류

다이나믹 프로그래밍, 수학

### 문제 설명

<p>f(x) を 「x を 2進数表記した時の "1" の個数を返す関数」と定義します。 例えば、5 は 101<sub>2</sub> と 2 進数表記されるので、f(5) = 2 です。</p>

<p>正の整数 <strong>N</strong> が与えられるので、 a + b = <strong>N</strong> を満たす 0 以上の整数 a, b の組の中で f(a) + f(b) が最大になるものを求め、その時の f(a) + f(b) の値を出力してください。</p>

### 입력 

 <p>最初の行はテストケースの個数 <strong>T</strong> を表す正の整数です。 各テストケースは1行の文字列で表現され、それぞれの行には <strong>N</strong> を表す正の整数が1つだけ含まれています。</p>

<h3>制約</h3>

<ul>
	<li>1 ≤ <strong>T</strong> ≤ 1000</li>
	<li><strong>N</strong> ≤ 10<sup>18</sup> (32bit整数型には収まらないことに注意)</li>
</ul>

### 출력 

 <p>各テストケースごとに、</p>

<pre>Case #X: P
</pre>

<p>という内容を1行出力してください。ここで <strong>X</strong> は 1 から始まるテストケース番号、<strong>P</strong> は f(a) + f(b) の最大値です。</p>

