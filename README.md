# boj
This is a auto push repository for Baekjoon Online Judge created with [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub).


# This is the coding technique for problem solving(PS) in c++
Other languages isn't frequently used in PS such as python or java.

This kind of language is recommended for coding test for company as the students won't dig deep in PS.

C++ is god in PS

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
Try not to use **get<0>(q.front())** or **tie(a,b,c)** unless it is necessary.
