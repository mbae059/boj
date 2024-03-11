# [Gold I] 산림의 수호자 - 31568 

[문제 링크](https://www.acmicpc.net/problem/31568) 

### 성능 요약

메모리: 18520 KB, 시간: 60 ms

### 분류

깊이 우선 탐색, 다이나믹 프로그래밍, 트리에서의 다이나믹 프로그래밍, 그래프 이론, 그래프 탐색, 그리디 알고리즘, 트리

### 제출 일자

2024년 3월 11일 21:58:40

### 문제 설명

<blockquote>
<p><em>근성은 나무에 관심이 많다.</em></p>
</blockquote>

<p>드루이드 근성은 <strong>나무</strong>를 관리하는 산림의 수호자이다. 근성이 관리하는 나무는 트리 형태를 이루고 있으며, 얼마나 관리가 잘 됐는지 무려 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>개나 되는 정점을 가지고 있다. 근성은 모든 정점을 소중하게 여겨서 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>개의 정점들에 각각 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c></mjx-mn></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mn>1</mn></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$1$</span></mjx-container>에서부터 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>까지의 고유한 정점 번호를 일일이 매겨놓았다.</p>

<p>어느 날, 근성의 멋진 나무를 항상 시기해 오던 사악한 악당 영도가 근성의 나무에 불을 지르고 말았다! 근성이 나무를 최대한 온전히 보존하기 위해서는, 나무가 완전히 타서 없어지기 전에 나무의 각 정점에 저장된 데이터들을 최대한 많이 복제해야 한다.</p>

<p>초기에 영도는 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44E TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>a</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$a$</span></mjx-container>번 정점을 불태웠고, 근성은 불에 타지 않은 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44F TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>b</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$b$</span></mjx-container>번 정점 위에 서 있다. 근성은 불에 타지 않은 정점 위에서 다음 행동 중 하나를 선택하여 수행할 수 있다.</p>

<ul>
	<li>복제하기: 근성이 현재 정점에서 데이터를 복제한다. 이 행동은 시간을 소모하지 않는다. 단, 데이터를 이미 복제한 정점에서는 다시 데이터를 복제할 수 없다.</li>
	<li>이동하기: 근성이 현재 정점에서 간선을 따라 이웃한 불에 타지 않은 정점 중 한 곳으로 이동한다.</li>
	<li>기다리기: 근성이 현재 정점에서 이동하지 않고 대기한다.</li>
</ul>

<p>만약 근성이 이동하기 또는 기다리기를 선택했다면, 수행하는 시간 동안 불타는 정점과 이웃한 관계에 있는 아직 불타지 않는 정점들로 불이 옮겨 붙는다.</p>

<p>만약 근성이 다음 행동으로 불타는 정점 위에 있게 된다면, 그 즉시 근성은 더 이상의 나무 보존 작업을 포기하고 나무에서 탈출할 것이다. 근성이 정점에 도착함과 동시에 해당 정점으로 불이 옮겨붙는다면 근성은 해당 정점에서 데이터를 복제할 수 없다.</p>

<p>당신이 해야 할 일은 근성이 탈출하기 전까지 데이터를 복제할 수 있는 나무의 정점 개수의 최댓값을 구하여 근성에게 알려주는 것이다. 산림의 수호자 근성이 최대한 많은 데이터를 보존할 수 있도록 도와주자!</p>

### 입력 

 <p>첫 번째 줄에 나무의 정점의 개수 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>이 주어진다.</p>

<p>두 번째 줄부터 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c2212"></mjx-c></mjx-mo><mjx-mn class="mjx-n" space="3"><mjx-c class="mjx-c31"></mjx-c></mjx-mn></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi><mo>−</mo><mn>1</mn></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N-1$</span></mjx-container>개의 줄에 걸쳐 나무의 간선 정보 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D462 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n"><mjx-c class="mjx-c2C"></mjx-c></mjx-mo><mjx-mi class="mjx-i" space="2"><mjx-c class="mjx-c1D463 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>u</mi><mo>,</mo><mi>v</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$u, v$</span></mjx-container>가 공백으로 구분되어 주어진다. 이는 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D462 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>u</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$u$</span></mjx-container>번 정점과 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D463 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>v</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$v$</span></mjx-container>번 정점 사이에 간선이 존재한다는 뜻이다.</p>

<p><mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"> <mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c2B"></mjx-c></mjx-mo><mjx-mn class="mjx-n" space="3"><mjx-c class="mjx-c31"></mjx-c></mjx-mn></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi><mo>+</mo><mn>1</mn></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N+1$</span></mjx-container>번째 줄에 최초로 불타는 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44E TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>a</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$a$</span></mjx-container>번 정점과 근성이 위치한 <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44F TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>b</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$b$</span></mjx-container>번 정점의 번호가 공백으로 구분되어 주어진다.</p>

### 출력 

 <p>가능한 모든 경우들 중 근성이 탈출하기 전까지 데이터를 복제할 수 있는 나무의 정점 개수의 최댓값을 출력한다.</p>

