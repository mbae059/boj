# [Gold V] Game Moves - 13766 

[문제 링크](https://www.acmicpc.net/problem/13766) 

### 성능 요약

메모리: 2020 KB, 시간: 0 ms

### 분류

수학

### 문제 설명

<p>2048 is a puzzle game where the objective is to slide numbered tiles on a grid to combine them into tiles with larger and larger values. While the initial aim of the game is to make a 2048 tile, the game continues until no more moves are possible, whether or not a 2048 tile has been made. The game starts with two tiles placed in random positions on the board, each having a value of either 2 or 4.</p>

<p>The game proceeds in a series of moves, with each move having five distinct phases (choice of direction; movement; merging; gap closing; birth) as follows:</p>

<ol>
	<li>Choice of direction: the player chooses one of the directions up, down, left or right. The chosen direction will be called “downstream”.</li>
	<li>Movement: the player moves all pieces downstream as far as they will go, closing any gaps. The edge of the board towards which all pieces move is called the “blocking edge”.</li>
	<li>Merging: working upstream, away from the blocking edge, any piece that has the same value as its upstream neighbour is merged with it, to form a new tile with the combined value of the two merging tiles. A merged tile is not a candidate for any further merging. Whenever a pair of tiles merge, the game score increases by the value of the new tile.</li>
	<li>Gap closing: all pieces are again moved downstream as far as they will go to close any gaps.</li>
	<li>Birth: a new tile with value 2 or 4 appears on an empty square on the board. The value (2 or 4) and the birth location are both random.</li>
</ol>

<p>The board must change in some way during the second or third stage of this process for a new tile to appear for this to be considered a valid move.</p>

<p>The game score starts at zero and whenever two tiles combine the score increases by the value of the new tile. The game is usually played on a 4 × 4 grid but other variants are available where the grid is a different size but still square.</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.32.27.png" style="height:160px; width:160px">(a) Score is 16</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.32.32.png" style="height:160px; width:160px">(b) Down - Score is 24</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.32.40.png" style="height:163px; width:160px">(c) Down - Score is 32</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.32.45.png" style="height:160px; width:160px">(d) Down - Score is 48</p>

<p>Figure 1: Score progression for a series of moves - new values are shown in blue</p>

<p>Figure 1 shows a progression of moves with the score progressing from 16 to 24 to 32 to 48. The progression starts with Figure 1(a) which has been reached after seven moves. The player uses a Down move and the two vertical pairs of 2s in the third and fourth columns merge to become 4s. Because two 4s are generated, the score increases by 8. The resulting board is shown in Figure 1(b) with a new 2 randomly appearing in the second column. The player uses a second Down move and the vertical pair of 4s in the fourth column merge to become an 8. The score increases by the sum of the merged values (i.e. by 8). The board becomes that shown in Figure 1(c) with a new 4 randomly appearing in the fourth column. Finally, the player moves Down again and the vertical pair of 8s in the fourth column merge to become a 16, which increases the score by 16. The resulting board is shown in Figure 1(d).</p>

<p>Figure 2 is demonstrative and shows how values merge and move. This demonstration will not show any new values appearing on the board. Assuming the game board is in the state shown in Figure 2(a) then if the player moves Right, the two horizontal pairs of 2s in the bottom row merge to become 4s as shown in Figure 2(b), however only the rightmost pair of 4s in the top row merge to become an 8. If the player then moves left, the horizontal pair of 4s in the bottom row merge to become a single 8 as shown in Figure 2(c) and the values in the top row move but do not merge.</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.35.08.png" style="height:161px; width:160px">(a) Current State</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.35.14.png" style="height:160px; width:160px">(b) After move Right</p>

<p><img alt="" src="https://onlinejudgeimages.s3.amazonaws.com/problem/13766/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-19%20%EC%98%A4%EC%A0%84%202.35.22.png" style="height:158px; width:160px">(c) After move Left</p>

<p>Figure 2: How values merge and move</p>

<p>Given the state of a game and the current score, write a program to determine the number of moves it has taken to get to that state.</p>

### 입력 

 <p>The input will contain a single test case.</p>

<p>The first line of input for each test case is the size of the square grid, n (2 ≤ n ≤ 7). The following n lines contain n space separated integer values indicating the current state of a game. A value of 0 is used to indicate an empty grid square. All non-empty grid squares will have a value that is a power of 2 between 2 and 2<sup>50</sup>, inclusive. This is followed by a line containing a single integer value being the score, s, for the current state of the game (0 ≤ s ≤ 108 086 391 056 891 712).</p>

<p>All test cases will consist of a valid game state.</p>

### 출력 

 <p>Output the number of moves it has taken to achieve the current state of the game. The solution will have a value less than 2<sup>63</sup> .</p>

