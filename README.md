# boj
This is a auto push repository for Baekjoon Online Judge created with [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub).


# This is the coding technique for problem solving(PS) in c++

# List-initialization 

List-initialization was first introduced in [C++11](https://en.cppreference.com/w/cpp/language/list_initialization)
This syntax is widely known.

```c++
queue<tuple<int,int,int>> q;
q.push({1,2,3});
```


# Structured binding

Structured binding was first introduced in [C++17](https://en.cppreference.com/w/cpp/language/structured_binding).
It is often used together with list-initialization.
In short, this kind of coding is possible.

```c++
queue<tuple<int, int, int>> q;
q.push({1,2,3});
auto [a,b,c] = q.front();
```

Before this, we used [tie](https://en.cppreference.com/w/cpp/utility/tuple/tie). 

```c++
queue<tuple<int, int, int>> q;
q.push({1,2,3});
int a, b, c;
tie(a,b,c) = q.front();
```

As you can see, structured binding is better.

# Range-based for loop

```c++
vector<int> v(5);
iota(v.begin(), v.end(), 1);
for(auto i : v) {
    cout << i << endl;
}
```

```c++
int now = 3;
for(auto next : {now-1, now+1, now*2}) {
    if(next>0) cout << next << endl;
}
```

This could be used when you want to move in an 2*2 matrix. For example {{-1,0},{1,0}}...





The template code i use for PS is template_code.cpp.

# List of Algorithms included in template_code.cpp

1. Basic Combination (Permuation could be made also)
2. segment tree. lazy propagation. persistent segment tree. fenwick tree
3. tarjan algorithm. DAG and DP with SCC. 2-SAT
4. Shortest Path(Dijkstra, SPFA, Floyd-Warshall)
5. DSU, Kruskal
6. Network Flow (Dinic, Edmonds Karp)
7. MCMF (Edmonds Karp+SPFA)
8. CCW. Line Intersection
9. LCA
10. LIS
11. Trie, aho-corasick
12. KMP
13. Extented Euclidian
