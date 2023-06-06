# [Gold II] TOWER - 3261 

[문제 링크](https://www.acmicpc.net/problem/3261) 

### 성능 요약

메모리: 2200 KB, 시간: 4 ms

### 분류

자료 구조, 분리 집합

### 문제 설명

<p>There are empty plastic glasses marked with numbers from 1 to N which can be put one into another, standing on the table.</p>

<p>You are given number of moves a→b that mean that you should move the bunch containing glass a to the bunch containing glass b. If a is equal to b, or glasses a and b are in the same bunch, than that move does nothing.</p>

<p>For example, we have 7 glasses and moves 1→3, 2→6, 3→6, 4→7 and 4→2, then situation on the table will change as follows:</p>

<pre style="text-align: center;">                                                                        4
                                                                        7
                                                    1         1         1
                                                    3         3         3
                    1             1     2           2         2 4       2
1 2 3 4 5 6 7 --> 2 3 4 5 6 7 --> 3 4 5 6 7 --> 4 5 6 7 --> 5 6 7 --> 5 6</pre>

<p>Moves must be made in the given order.</p>

<p>Write a program that will choose zero move, which is move that should be made before the first move in the given order. You should choose such zero move that will maximize the number of glasses in the largest bunch.</p>

### 입력 

 <p>In the first line of input there are two integers N and M, 2 ≤ N ≤ 10000, 0 ≤ M ≤ 100000. N is the number of glasses standing at the table and M is the number of moves to be made.</p>

<p>Next M lines contain moves to be made. In each of those lines are two integers a and b which represent move a→b.</p>

### 출력 

 <p>One and only line of output file should contain zero move a→b represented by two integers a and b separated by one space.</p>

<p>Note: solution need not to be unique.</p>

