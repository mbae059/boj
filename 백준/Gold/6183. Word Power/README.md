# [Gold IV] Word Power - 6183 

[문제 링크](https://www.acmicpc.net/problem/6183) 

### 성능 요약

메모리: 3080 KB, 시간: 272 ms

### 분류

브루트포스 알고리즘, 문자열

### 문제 설명

<p>Farmer John wants to evaluate the quality of the names of his N (1 <= N <= 1000) cows. Each name is a string with no more than 1000 characters, all of which are non-blank.</p>

<p>He has created a set of M (1 <= M <= 100) 'good' strings (no longer than 30 characters and fully non-blank). If the sequence letters of a cow's name contains the letters of a 'good' string in the correct order as a subsequence (i.e., not necessarily all next to each other), the cow's name gets 1 quality point.</p>

<p>All strings is case-insensitive, i.e., capital letters and lower case letters are considered equivalent.  For example, the name "Bessie" contains the letters of "Be", "sI", "EE", and "Es" in the correct order, but not "is" or "eB". Help Farmer John determine the number of quality points in each of his cow's names.</p>

### 입력 

 <ul>
	<li>Line 1: Two space-separated integers: N and M</li>
	<li>Lines 2..N+1: Line i+1 contains a string that is the name of the ith cow</li>
	<li>Lines N+2..N+M+1: Line N+i+1 contains the ith good string</li>
</ul>

<p> </p>

### 출력 

 <ul>
	<li>Lines 1..N+1: Line i+1 contains the number of quality points of the ith name</li>
</ul>

