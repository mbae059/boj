# [Gold IV] Jenga Game - 32466 

[문제 링크](https://www.acmicpc.net/problem/32466) 

### 성능 요약

메모리: 2088 KB, 시간: 32 ms

### 분류

게임 이론

### 제출 일자

2024년 10월 22일 23:51:37

### 문제 설명

<p>Yesyes and Nono are playing the Jenga game. Jenga has the following rules:</p>

<p>There is a tower consisting of <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D45B TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>n</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$n$</span></mjx-container> layers of blocks. Each layer consists of three long blocks. The blocks in each layer lie parallel to each other. The blocks in two neighboring layers are perpendicular to each other. Some blocks might be missing at the start of the game. Two players make their moves alternately. During one move a player must choose a block and remove it from the tower if it remains stable afterward. The tower is stable if all the following conditions are met:</p>

<ul>
	<li>Each layer contains at least one block.</li>
	<li>If a layer contains exactly one block, it’s the middle one.</li>
	<li>The top layer consists of three blocks.</li>
</ul>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/f751c365-520c-4197-8d93-ec9311c05c64/-/preview/" style="width: 200px; height: 226px;"></p>

<p>A player who is unable to make any move loses. Given the starting state of the tower, possibly with some blocks already removed, it is always guaranteed that the initial state of the given Jenga tower is stable. Your task is to determine which player will win. Both players always use the best strategy to win against each other. Yesyes plays first. Yesyes and Nono are experts at Jenga, so they don’t make any mistakes while removing a block.</p>

<p>Notice that in this version of Jenga, players do not put the blocks on the top of the tower.</p>

### 입력 

 <p>The first line of input contains the number of test cases <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D447 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>T</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$T$</span></mjx-container>.</p>

<p>The first line of input for each test case contains the initial height of the Jenga tower <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container>.</p>

<p>Each of the next <mjx-container class="MathJax" jax="CHTML" style="font-size: 109%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>N</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$N$</span></mjx-container> lines contains the initial state of each layer as a string of length 3 consisting of <code>0</code>s and <code>1</code>s, starting from the top layer. <code>0</code> means that there is no block at that position and <code>1</code> means there is a block at that position. It is always guaranteed that the initial state of the given Jenga tower is stable.</p>

### 출력 

 <p>Print the winner in one line for each test case.</p>

