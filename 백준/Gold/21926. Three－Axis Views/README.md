# [Gold V] Three-Axis Views - 21926 

[문제 링크](https://www.acmicpc.net/problem/21926) 

### 성능 요약

메모리: 3056 KB, 시간: 4 ms

### 분류

그리디 알고리즘, 구현

### 문제 설명

<p>A friend of yours is an artist designing Image-Containing Projection Cubes (ICPCs). An ICPC is a crystal cube with its side of integer length. Some of its regions are made opaque through an elaborate laser machining process. Each of the opaque regions is a cube of unit size aligned with integer coordinates.</p>

<p>Figure A.1 depicts an ICPC as given in the Sample Input 1. Here, the green wires correspond to the edges of the crystal cube. The blue small cubes correspond to the cubic opaque regions inside the crystal.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/48a02d41-65dc-4419-b888-e0a41051c833/-/preview/" style="width: 101px; height: 114px;"></p>

<p style="text-align: center;">Figure A.1. ICPC of Sample Input 1</p>

<p>ICPCs are meant to enjoy the silhouettes of its opaque regions projected by three parallel lights perpendicular to its faces. Figure A.2 depicts the ICPC and its three silhouettes.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/c1ae0c35-f7f3-4ac7-8c3a-bbb1caf51914/-/preview/" style="width: 225px; height: 247px;"></p>

<p style="text-align: center;">Figure A.2. ICPC of Sample Input 1 and its silhouettes (dashed-dotted lines are the edges of the parallel light perpendicular to the left face)</p>

<p>Your job is to write a program that decides whether there exists an ICPC that makes the given silhouettes.</p>

### 입력 

 <p>The input consists of a single test case of the following format.</p>

<pre>n
s<sub>1</sub>
.
.
.
s<sub>n</sub>
t<sub>1</sub>
.
.
.
t<sub>n</sub>
u<sub>1</sub>
.
.
.
u<sub>n</sub></pre>

<p>Here, n is the size of the ICPC, an integer between 1 and 100, inclusive.</p>

<p>The ICPC of size n makes three silhouettes of n × n squares of dark and bright cells. Cells are dark if they are covered by the shadows of opaque unit cubes, and are bright, otherwise. The 3n lines, each with n digits, starting from the second line of the input denote the three silhouettes of the ICPC, where ‘0’ represents a bright cell and ‘1’ represents a dark cell. At least one of the digits in the 3n lines is ‘1’.</p>

<p>First comes the data for the silhouette on the yz-plane, where the first line s<sub>1</sub> gives the cells of the silhouettes with the largest z-coordinate value. They are in the order of their y-coordinates. The following lines, s<sub>2</sub>, . . . , s<sub>n</sub>, give the cells with the decreasing values of their z-coordinates.</p>

<p>Then comes the data for the silhouette on the zx-plane, where the first line, t<sub>1</sub>, gives the cells with the largest x-coordinate value, in the order of their z-coordinates. The following lines, t<sub>2</sub>, . . . , t<sub>n</sub>, give the cells with the decreasing values of their x-coordinates.</p>

<p>Finally comes the data for the silhouette on the xy-plane, where the first line, u<sub>1</sub>, gives the cells with the largest y-coordinate value, in the order of their x-coordinates. The following lines, u<sub>2</sub>, . . . , u<sub>n</sub>, give the cells with the decreasing values of their y-coordinates.</p>

<p>The following figure depicts the three silhouettes of the ICPC given in the Sample Input 1.</p>

<table class="table table-bordered td-center">
	<tbody>
		<tr>
			<td><img alt="" src="https://upload.acmicpc.net/e11c82dd-b090-4bad-a1f0-67fb2ae89c27/-/crop/216x220/0,0/-/preview/" style="width: 108px; height: 110px;"></td>
			<td><img alt="" src="https://upload.acmicpc.net/e11c82dd-b090-4bad-a1f0-67fb2ae89c27/-/crop/214x220/248,0/-/preview/" style="width: 107px; height: 110px;"></td>
			<td><img alt="" src="https://upload.acmicpc.net/e11c82dd-b090-4bad-a1f0-67fb2ae89c27/-/crop/212x220/492,0/-/preview/" style="width: 106px; height: 110px;"></td>
		</tr>
		<tr>
			<td>⇓</td>
			<td>⇓</td>
			<td>⇓</td>
		</tr>
		<tr>
			<td>
			<pre>0 <strong>1</strong> 0
0 <strong>1</strong> 0
<strong>1</strong> <strong>1</strong> <strong>1</strong>
</pre>

			<p>(yz-plane)</p>
			</td>
			<td>
			<pre><strong>1</strong> 0 0
<strong>1</strong> <strong>1</strong> <strong>1</strong>
<strong>1</strong> 0 <strong>1</strong></pre>

			<p>(zx-plane)</p>
			</td>
			<td>
			<pre>0 <strong>1</strong> <strong>1</strong>
<strong>1</strong> <strong>1</strong> <strong>1</strong>
0 <strong>1</strong> 0</pre>

			<p>(xy-plane)</p>
			</td>
		</tr>
	</tbody>
</table>

<p style="text-align: center;">Figure A.3. 0-1 representations of silhouettes (Sample Input 1)</p>

### 출력 

 <p>Print “Yes” if it is possible to make an ICPC with the given silhouettes. Print “No”, otherwise.</p>

