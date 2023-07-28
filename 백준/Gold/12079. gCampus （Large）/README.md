# [Gold IV] gCampus (Large) - 12079 

[문제 링크](https://www.acmicpc.net/problem/12079) 

### 성능 요약

메모리: 2740 KB, 시간: 12 ms

### 분류

데이크스트라, 플로이드–워셜, 그래프 이론

### 문제 설명

<p>Company G has a main campus with <strong>N</strong> offices (numbered from 0 to <strong>N</strong> - 1) and <strong>M</strong>bidirectional roads (numbered from 0 to <strong>M</strong> - 1). The ith road connects a pair of offices (U<sub>i</sub>, V<sub>i</sub>), and it takes C<sub>i</sub> minutes to travel on it (in either direction).</p>

<p>A path between two offices X and Y is a series of one or more roads that starts at X and ends at Y. The time taken to travel a path is the sum of the times needed to travel each of the roads that make up the path. (It's guaranteed that there is at least one path connecting any two offices.)</p>

<p>Company G specializes in efficient transport solutions, but the CEO has just realized that, embarrassingly enough, its own road network may be suboptimal! She wants to know which roads in the campus are <em>inefficient</em>. A road is inefficient if and only if it is not included in <strong>any</strong> shortest paths between <strong>any</strong> offices.</p>

<p>Given the graph of offices and roads, can you help the CEO find all of the inefficient roads?</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <strong>T</strong>. <strong>T</strong> test cases follow. Each case begins with one line with two integers <strong>N</strong> and <strong>M</strong>, indicating the number of offices and roads. This is followed by <strong>M</strong> lines containing three integers each: <strong>U<sub>i</sub></strong>, <strong>V<sub>i</sub></strong> and <strong>C<sub>i</sub></strong>, indicating the ith road is between office <strong>U<sub>i</sub></strong> and office <strong>V<sub>i</sub></strong>, and it takes <strong>C<sub>i</sub></strong> minutes to travel on it.</p>

<h3>Limits</h3>

<ul>
	<li>0 < <strong>C<sub>i</sub></strong> ≤ 1000000.</li>
	<li>1 ≤ <strong>T</strong> ≤ 3.</li>
	<li>1 ≤ <strong>N</strong> ≤ 100.</li>
	<li>1 ≤ <strong>M</strong> ≤ 10000.</li>
</ul>

### 출력 

 <p>For each test case, output one line containing "Case #x:", where x is the test case number (starting from 1). Then output the road numbers of all of the inefficient roads, in increasing order, each on its own line. (Note that road 0 refers to the first road listed in a test case, road 1 refers to the second road, etc.)</p>

