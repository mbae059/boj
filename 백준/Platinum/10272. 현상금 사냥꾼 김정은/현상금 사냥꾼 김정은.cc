#include<bits/stdc++.h>
#include <type_traits>

namespace atcoder {

    namespace internal {

#ifndef _MSC_VER
        template <class T>
        using is_signed_int128 =
            typename std::conditional<std::is_same<T, __int128_t>::value ||
            std::is_same<T, __int128>::value,
            std::true_type,
            std::false_type>::type;

        template <class T>
        using is_unsigned_int128 =
            typename std::conditional<std::is_same<T, __uint128_t>::value ||
            std::is_same<T, unsigned __int128>::value,
            std::true_type,
            std::false_type>::type;

        template <class T>
        using make_unsigned_int128 =
            typename std::conditional<std::is_same<T, __int128_t>::value,
            __uint128_t,
            unsigned __int128>;

        template <class T>
        using is_integral = typename std::conditional<std::is_integral<T>::value ||
            is_signed_int128<T>::value ||
            is_unsigned_int128<T>::value,
            std::true_type,
            std::false_type>::type;

        template <class T>
        using is_signed_int = typename std::conditional<(is_integral<T>::value&&
            std::is_signed<T>::value) ||
            is_signed_int128<T>::value,
            std::true_type,
            std::false_type>::type;

        template <class T>
        using is_unsigned_int =
            typename std::conditional<(is_integral<T>::value&&
                std::is_unsigned<T>::value) ||
            is_unsigned_int128<T>::value,
            std::true_type,
            std::false_type>::type;

        template <class T>
        using to_unsigned = typename std::conditional<
            is_signed_int128<T>::value,
            make_unsigned_int128<T>,
            typename std::conditional<std::is_signed<T>::value,
            std::make_unsigned<T>,
            std::common_type<T>>::type>::type;
#endif

        template <class T>
        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

        template <class T>
        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

        template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

    }  // namespace internal

}  // namespace atcoder


namespace atcoder {

    namespace internal {

        constexpr long long safe_mod(long long x, long long m) {
            x %= m;
            if (x < 0) x += m;
            return x;
        }

        struct barrett {
            unsigned int _m;
            unsigned long long im;

            explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

            unsigned int umod() const { return _m; }

            unsigned int mul(unsigned int a, unsigned int b) const {

                unsigned long long z = a;
                z *= b;
#ifdef _MSC_VER
                unsigned long long x;
                _umul128(z, im, &x);
#else
                unsigned long long x =
                    (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
                unsigned int v = (unsigned int)(z - x * _m);
                if (_m <= v) v += _m;
                return v;
            }
        };

        constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
            if (m == 1) return 0;
            unsigned int _m = (unsigned int)(m);
            unsigned long long r = 1;
            unsigned long long y = safe_mod(x, m);
            while (n) {
                if (n & 1) r = (r * y) % _m;
                y = (y * y) % _m;
                n >>= 1;
            }
            return r;
        }

        constexpr bool is_prime_constexpr(int n) {
            if (n <= 1) return false;
            if (n == 2 || n == 7 || n == 61) return true;
            if (n % 2 == 0) return false;
            long long d = n - 1;
            while (d % 2 == 0) d /= 2;
            constexpr long long bases[3] = { 2, 7, 61 };
            for (long long a : bases) {
                long long t = d;
                long long y = pow_mod_constexpr(a, t, n);
                while (t != n - 1 && y != 1 && y != n - 1) {
                    y = y * y % n;
                    t <<= 1;
                }
                if (y != n - 1 && t % 2 == 0) {
                    return false;
                }
            }
            return true;
        }
        template <int n> constexpr bool is_prime = is_prime_constexpr(n);

        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0) return { b, 0 };

            long long s = b, t = a;
            long long m0 = 0, m1 = 1;

            while (t) {
                long long u = s / t;
                s -= t * u;
                m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b


                auto tmp = s;
                s = t;
                t = tmp;
                tmp = m0;
                m0 = m1;
                m1 = tmp;
            }
            if (m0 < 0) m0 += b / s;
            return { s, m0 };
        }

        constexpr int primitive_root_constexpr(int m) {
            if (m == 2) return 1;
            if (m == 167772161) return 3;
            if (m == 469762049) return 3;
            if (m == 754974721) return 11;
            if (m == 998244353) return 3;
            int divs[20] = {};
            divs[0] = 2;
            int cnt = 1;
            int x = (m - 1) / 2;
            while (x % 2 == 0) x /= 2;
            for (int i = 3; (long long)(i)*i <= x; i += 2) {
                if (x % i == 0) {
                    divs[cnt++] = i;
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                divs[cnt++] = x;
            }
            for (int g = 2;; g++) {
                bool ok = true;
                for (int i = 0; i < cnt; i++) {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return g;
            }
        }
        template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

        unsigned long long floor_sum_unsigned(unsigned long long n,
            unsigned long long m,
            unsigned long long a,
            unsigned long long b) {
            unsigned long long ans = 0;
            while (true) {
                if (a >= m) {
                    ans += n * (n - 1) / 2 * (a / m);
                    a %= m;
                }
                if (b >= m) {
                    ans += n * (b / m);
                    b %= m;
                }

                unsigned long long y_max = a * n + b;
                if (y_max < m) break;
                n = (unsigned long long)(y_max / m);
                b = (unsigned long long)(y_max % m);
                std::swap(m, a);
            }
            return ans;
        }

    }  // namespace internal

}  // namespace atcoder


namespace atcoder {

    long long pow_mod(long long x, long long n, int m) {
        assert(0 <= n && 1 <= m);
        if (m == 1) return 0;
        internal::barrett bt((unsigned int)(m));
        unsigned int r = 1, y = (unsigned int)(internal::safe_mod(x, m));
        while (n) {
            if (n & 1) r = bt.mul(r, y);
            y = bt.mul(y, y);
            n >>= 1;
        }
        return r;
    }

    long long inv_mod(long long x, long long m) {
        assert(1 <= m);
        auto z = internal::inv_gcd(x, m);
        assert(z.first == 1);
        return z.second;
    }

    std::pair<long long, long long> crt(const std::vector<long long>& r,
        const std::vector<long long>& m) {
        assert(r.size() == m.size());
        int n = int(r.size());
        long long r0 = 0, m0 = 1;
        for (int i = 0; i < n; i++) {
            assert(1 <= m[i]);
            long long r1 = internal::safe_mod(r[i], m[i]), m1 = m[i];
            if (m0 < m1) {
                std::swap(r0, r1);
                std::swap(m0, m1);
            }
            if (m0 % m1 == 0) {
                if (r0 % m1 != r1) return { 0, 0 };
                continue;
            }


            long long g, im;
            std::tie(g, im) = internal::inv_gcd(m0, m1);

            long long u1 = (m1 / g);
            if ((r1 - r0) % g) return { 0, 0 };

            long long x = (r1 - r0) / g % u1 * im % u1;

            r0 += x * m0;
            m0 *= u1;  // -> lcm(m0, m1)
            if (r0 < 0) r0 += m0;
        }
        return { r0, m0 };
    }

    long long floor_sum(long long n, long long m, long long a, long long b) {
        assert(0 <= n && n < (1LL << 32));
        assert(1 <= m && m < (1LL << 32));
        unsigned long long ans = 0;
        if (a < 0) {
            unsigned long long a2 = internal::safe_mod(a, m);
            ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
            a = a2;
        }
        if (b < 0) {
            unsigned long long b2 = internal::safe_mod(b, m);
            ans -= 1ULL * n * ((b2 - b) / m);
            b = b2;
        }
        return ans + internal::floor_sum_unsigned(n, m, a, b);
    }

}  // namespace atcoder

namespace atcoder {

    namespace internal {

        struct modint_base {};
        struct static_modint_base : modint_base {};

        template <class T> using is_modint = std::is_base_of<modint_base, T>;
        template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;

    }  // namespace internal

    template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
    struct static_modint : internal::static_modint_base {
        using mint = static_modint;

    public:
        static constexpr int mod() { return m; }
        static mint raw(int v) {
            mint x;
            x._v = v;
            return x;
        }

        static_modint() : _v(0) {}
        template <class T, internal::is_signed_int_t<T>* = nullptr>
        static_modint(T v) {
            long long x = (long long)(v % (long long)(umod()));
            if (x < 0) x += umod();
            _v = (unsigned int)(x);
        }
        template <class T, internal::is_unsigned_int_t<T>* = nullptr>
        static_modint(T v) {
            _v = (unsigned int)(v % umod());
        }

        unsigned int val() const { return _v; }

        mint& operator++() {
            _v++;
            if (_v == umod()) _v = 0;
            return *this;
        }
        mint& operator--() {
            if (_v == 0) _v = umod();
            _v--;
            return *this;
        }
        mint operator++(int) {
            mint result = *this;
            ++*this;
            return result;
        }
        mint operator--(int) {
            mint result = *this;
            --*this;
            return result;
        }

        mint& operator+=(const mint& rhs) {
            _v += rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        mint& operator-=(const mint& rhs) {
            _v -= rhs._v;
            if (_v >= umod()) _v += umod();
            return *this;
        }
        mint& operator*=(const mint& rhs) {
            unsigned long long z = _v;
            z *= rhs._v;
            _v = (unsigned int)(z % umod());
            return *this;
        }
        mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

        mint operator+() const { return *this; }
        mint operator-() const { return mint() - *this; }

        mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            while (n) {
                if (n & 1) r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        mint inv() const {
            if (prime) {
                assert(_v);
                return pow(umod() - 2);
            }
            else {
                auto eg = internal::inv_gcd(_v, m);
                assert(eg.first == 1);
                return eg.second;
            }
        }

        friend mint operator+(const mint& lhs, const mint& rhs) {
            return mint(lhs) += rhs;
        }
        friend mint operator-(const mint& lhs, const mint& rhs) {
            return mint(lhs) -= rhs;
        }
        friend mint operator*(const mint& lhs, const mint& rhs) {
            return mint(lhs) *= rhs;
        }
        friend mint operator/(const mint& lhs, const mint& rhs) {
            return mint(lhs) /= rhs;
        }
        friend bool operator==(const mint& lhs, const mint& rhs) {
            return lhs._v == rhs._v;
        }
        friend bool operator!=(const mint& lhs, const mint& rhs) {
            return lhs._v != rhs._v;
        }

    private:
        unsigned int _v;
        static constexpr unsigned int umod() { return m; }
        static constexpr bool prime = internal::is_prime<m>;
    };

    template <int id> struct dynamic_modint : internal::modint_base {
        using mint = dynamic_modint;

    public:
        static int mod() { return (int)(bt.umod()); }
        static void set_mod(int m) {
            assert(1 <= m);
            bt = internal::barrett(m);
        }
        static mint raw(int v) {
            mint x;
            x._v = v;
            return x;
        }

        dynamic_modint() : _v(0) {}
        template <class T, internal::is_signed_int_t<T>* = nullptr>
        dynamic_modint(T v) {
            long long x = (long long)(v % (long long)(mod()));
            if (x < 0) x += mod();
            _v = (unsigned int)(x);
        }
        template <class T, internal::is_unsigned_int_t<T>* = nullptr>
        dynamic_modint(T v) {
            _v = (unsigned int)(v % mod());
        }

        unsigned int val() const { return _v; }

        mint& operator++() {
            _v++;
            if (_v == umod()) _v = 0;
            return *this;
        }
        mint& operator--() {
            if (_v == 0) _v = umod();
            _v--;
            return *this;
        }
        mint operator++(int) {
            mint result = *this;
            ++*this;
            return result;
        }
        mint operator--(int) {
            mint result = *this;
            --*this;
            return result;
        }

        mint& operator+=(const mint& rhs) {
            _v += rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        mint& operator-=(const mint& rhs) {
            _v += mod() - rhs._v;
            if (_v >= umod()) _v -= umod();
            return *this;
        }
        mint& operator*=(const mint& rhs) {
            _v = bt.mul(_v, rhs._v);
            return *this;
        }
        mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

        mint operator+() const { return *this; }
        mint operator-() const { return mint() - *this; }

        mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            while (n) {
                if (n & 1) r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        mint inv() const {
            auto eg = internal::inv_gcd(_v, mod());
            assert(eg.first == 1);
            return eg.second;
        }

        friend mint operator+(const mint& lhs, const mint& rhs) {
            return mint(lhs) += rhs;
        }
        friend mint operator-(const mint& lhs, const mint& rhs) {
            return mint(lhs) -= rhs;
        }
        friend mint operator*(const mint& lhs, const mint& rhs) {
            return mint(lhs) *= rhs;
        }
        friend mint operator/(const mint& lhs, const mint& rhs) {
            return mint(lhs) /= rhs;
        }
        friend bool operator==(const mint& lhs, const mint& rhs) {
            return lhs._v == rhs._v;
        }
        friend bool operator!=(const mint& lhs, const mint& rhs) {
            return lhs._v != rhs._v;
        }

    private:
        unsigned int _v;
        static internal::barrett bt;
        static unsigned int umod() { return bt.umod(); }
    };
    template <int id> internal::barrett dynamic_modint<id>::bt(998244353);

    using modint998244353 = static_modint<998244353>;
    using modint1000000007 = static_modint<1000000007>;
    using modint = dynamic_modint<-1>;

    namespace internal {

        template <class T>
        using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

        template <class T>
        using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

        template <class> struct is_dynamic_modint : public std::false_type {};
        template <int id>
        struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

        template <class T>
        using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

    }  // namespace internal

}  // namespace atcoder

namespace atcoder {

    template <class T> struct fenwick_tree {
        using U = internal::to_unsigned_t<T>;

    public:
        fenwick_tree() : _n(0) {}
        explicit fenwick_tree(int n) : _n(n), data(n) {}

        void add(int p, T x) { //add value
            assert(0 <= p && p < _n);
            p++;
            while (p <= _n) {
                data[p - 1] += U(x);
                p += p & -p;
            }
        }

        T sum(int l, int r) { //returns a[l]+...+a[r-1]
            assert(0 <= l && l <= r && r <= _n);
            return sum(r) - sum(l);
        }

    private:
        int _n;
        std::vector<U> data;

        U sum(int r) { //print sum
            U s = 0;
            while (r > 0) {
                s += data[r - 1];
                r -= r & -r;
            }
            return s;
        }
    };

}  // namespace atcoder

using namespace atcoder;
#define endl '\n'
#define INF 987654321
#define p_q priority_queue
#define pbk push_back
#define double long double
#define rep(i, a, b) for (int i=a; i<=b; i++) 
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
#define int ll
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using mii = map<int, int>;
using si = set<int>;
using qi = queue<int>;
using qpii = queue<pii>;
using tiii = tuple<int, int, int>; //get<0>(t);
using tiiii = tuple<int, int, int, int>;
using vtiii = vector<tiii>;
using vtiiii = vector<tiiii>;
using spii = set<pii>;
using qtiii = queue<tiii>;
using mint = modint;
using vm = vector<mint>;
int A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
int dy[8] = { 1,-1,0,0,1,1,-1,-1 };
int dx[8] = { 0,0,1,-1,1,-1,1,-1 };
//vvi matrix(N, vector<int>(N));
//for finding the intersection of Line(x1,y1,x2,y2) and Line(x3,y3,x4,y4)
//do not solve with tenary search
// Px= (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4)
// Py= (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4)

//int to string : to_string
//string to int : stoi

//use setw(3) to get nice format for printing out 2-d array
//ex) cout << setw(3) << "a" << endl;

//to make a sorted vector's element unique, you should do v.erase(unique(v.begin(), v.end()), v.end())

// unordered_map<char,int> dx = {{'D',0},{'L',-1},{'R',1},{'U',0}};
// unordered_map<char,int> dy = {{'D',1},{'L',0},{'R',0},{'U',-1}}

//diagonal counting. l[y+x], r[y-x+N]

//when using ett, set global g=0. g++; in[v]=g; (do dfs) out[v]=g
struct Matrix {
    vector<vector<mint>> m;
    int l;
    Matrix(int l = 10) : l(l) {
        m = vector<vector<mint>>(l + 1, vector<mint>(l + 1));
    }

    void setEye() {
        for (int i = 1;i <= l;i++) m[i][i] = 1;
    }

    Matrix operator * (const Matrix& other) const {
        Matrix ret(l);
        for (int i = 1;i <= l;i++) {
            for (int j = 1;j <= l;j++) {
                for (int k = 1;k <= l;k++) {
                    ret.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return ret;
    }

    Matrix operator + (const Matrix& other) const {
        Matrix ret;
        for (int i = 1;i <= l;i++) {
            for (int j = 1;j <= l;j++) {
                ret.m[i][j] = m[i][j] + other.m[i][j];
            }
        }
        return ret;
    }
    Matrix power(ll k) { //matrix = matrix.power(k);
        Matrix ret;
        if (k == 0) {
            ret.setEye();
            return ret;
        }
        if (k == 1) {
            return *this;
        }

        ret = power(k / 2);
        ret = ret * ret;
        if (k & 1) ret = ret * (*this);
        return ret;
    }
    void rotate90CC() {
        vector<vector<mint>> after(l + 1, vector<mint>(l + 1));
        for (int i = 1;i <= l;i++) {
            for (int j = 1;j <= l;j++) {
                after[i][j] = m[j][l - i + 1];
            }
        }
        for (int i = 1;i <= l;i++) {
            for (int j = 1;j <= l;j++) {
                m[i][j] = after[i][j];
            }
        }
    }
    void transpose() {
        vector<vector<mint>> after(l + 1, vector<mint>(l + 1));
        for (int i = 1;i <= l;i++) {
            for (int j = 1;j <= l;j++) {
                after[i][j] = m[j][i];
            }
        }
        for (int i = 1;i <= l;i++) {
            for (int j = 1;j <= l;j++) {
                m[i][j] = after[i][j];
            }
        }
    }
    void print(int n, int m) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= m;j++) {
                cout << this->m[i][j].val() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
template<typename T, class BinaryOperation = plus<T>>
struct Segtree {
    vector<T> a;
    vector<T> s;
    int n;
    BinaryOperation op;
    Segtree(int n = 1) : n(n), op(BinaryOperation()) {
        a.resize(n + 1);
        s.resize(4 * n + 1);
    }
    T segment(int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight) {
            return s[node] = a[nodeLeft];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return s[node] = op(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
    }
    void update(int node, int nodeLeft, int nodeRight, int idx, T num) {
        if (idx < nodeLeft || nodeRight < idx) return;
        if (nodeLeft == nodeRight) {
            s[node] = num;
            return;
        }
        int mid = (nodeLeft + nodeRight) / 2;
        update(node * 2, nodeLeft, mid, idx, num);
        update(node * 2 + 1, mid + 1, nodeRight, idx, num);

        s[node] = op(s[node * 2], s[node * 2 + 1]);
    }
    T query(int node, int l, int r, int nodeLeft, int nodeRight) {
        if (nodeRight < l || r < nodeLeft) return 0; //could be 0, 1e9, -1e9
        if (l <= nodeLeft && nodeRight <= r) return s[node];
        int mid = nodeLeft + nodeRight >> 1;
        return op(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
    }
    void print(int node, int nodeLeft, int nodeRight) {
        cout << nodeLeft << " " << nodeRight << " : " << s[node] << endl;
        if (nodeLeft == nodeRight) return;

        int mid = (nodeLeft + nodeRight) >> 1;
        print(node * 2, nodeLeft, mid);
        print(node * 2 + 1, mid + 1, nodeRight);
    }
};

struct lazySegtree {
    vi a;
    vi s;
    vi lazy;
    int n;
    lazySegtree(int n) : n(n) {
        a.resize(n + 1);
        s.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }

    int merge(int a, int b) {
        return a + b;
    }
    int segment(int node, int nodeLeft, int nodeRight) { // use when s, a is available and segment tree is about sum
        if (nodeLeft == nodeRight) {
            return s[node] = a[nodeLeft];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return s[node] = merge(segment(node * 2, nodeLeft, mid), segment(node * 2 + 1, mid + 1, nodeRight));
    }
    void propagation(int node, int l, int r) {
        if (lazy[node]) {
            s[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void update(int node, int l, int r, int nodeLeft, int nodeRight, int dif) { //This is for lazy propagation
        propagation(node, nodeLeft, nodeRight);
        if (nodeRight < l || r < nodeLeft) return;
        if (l <= nodeLeft && nodeRight <= r) {
            s[node] += (nodeRight - nodeLeft + 1) * dif;
            if (nodeLeft != nodeRight) {
                lazy[node * 2] += dif;
                lazy[node * 2 + 1] += dif;
            }
            return;
        }
        int mid = (nodeLeft + nodeRight) / 2;
        update(node * 2, l, r, nodeLeft, mid, dif);
        update(node * 2 + 1, l, r, mid + 1, nodeRight, dif);
        s[node] = merge(s[node * 2], s[node * 2 + 1]);
    }
    ll query(int node, int l, int r, int nodeLeft, int nodeRight) { //s should be vll
        propagation(node, nodeLeft, nodeRight);
        if (nodeRight < l || r < nodeLeft) return 0;
        if (l <= nodeLeft && nodeRight <= r) {
            return s[node];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return merge(query(node * 2, l, r, nodeLeft, mid), query(node * 2 + 1, l, r, mid + 1, nodeRight));
    }
};

struct DSU {
    vi parent;
    vi depth; //tree depth (maximum distance from root node)
    vi d;
    vi sz;
    DSU(int n = 1) {
        parent = vi(n + 1);
        depth = vi(n + 1, 0);
        d = vi(n + 1, 0);
        sz = vi(n + 1, 0);
        iota(parent.begin() + 1, parent.end(), 1);
        fill(sz.begin() + 1, sz.end(), 1);
    }
    int getParent(int num) {
        if (num == parent[num]) return num;
        int p = getParent(parent[num]);
        // d[num] += d[parent[num]];
        return parent[num] = p;
    }

    //modify merge to get difference between a and b
    void merge(int a, int b, ll w = 0) {
        a = getParent(a);
        b = getParent(b);
        if (depth[a] < depth[b]) swap(a, b);
        if (depth[a] == depth[b]) depth[a] += 1;
        parent[b] = a;
        sz[a] += sz[b];
    }
};

void print(pii a) {
    cout << a.first << " " << a.second << endl;
}
void print(tiii a) {
    auto [x, y, z] = a;
    cout << x << " " << y << " " << z << endl;
}
template<typename T>
void print(T* a, int start, int end) {
    rep(i, start, end) cout << a[i] << " ";
    cout << endl;
}

template <typename T>
void print(const T& a) {
    cout << a << endl;
}

void print(const vector<pii>& v) {
    for (auto p : v) {
        print(p);
    }
    cout << endl;
}
void print(const vtiii& v) {
    for (auto p : v) {
        print(p);
    }
    cout << endl;
}
template <typename T>
void print(const vector<T>& v) {
    for (auto i : v) cout << i << " ";
    cout << endl;
}
bool inRange(int y, int x) {
    return 1 <= y && y <= N && 1 <= x && x <= M;
}
bool inRangeN(int y, int x) {
    return 1 <= y && y <= N && 1 <= x && x <= N;
}
vector<string> split(string input, char delimiter = ' ') {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

void yesno(bool a) {
    cout << (a ? "YES" : "NO") << endl;
}

void chmin(int& x, int y) {
    x = min(x, y);
}
void chmax(int& x, int y) {
    x = max(x, y);
}
template<int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template<typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};

template<typename T>
struct Vec<1, T> : public vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};
/*
vector<int> combination;
bool visited[1005];
void dfs(int idx, int cnt) { //implement with dfs(1, 0). N and K must be global variable
    if(cnt==K) {
        for(auto i : combination) {
            cout << i << " ";
        }
        cout << endl;
        return;
    }

    for(int i=idx;i<=N;i++) { //idx, N을 잘볼것
        if(visited[i]==1) continue;

        visited[i]=1;
        combination.push_back(i);
        dfs(i+1, cnt+1); //be careful with i+1, cnt+1
        visited[i]=0;
        combination.pop_back();
    }
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*

//two dimensional fenwick tree
#define MAX 1026
ll arr[MAX][MAX];
ll fenwick[MAX][MAX];

void update(int x, int y, ll value) {
    while(x < N+1) {
        int tempy = y;
        while(tempy < N+1) {
            fenwick[x][tempy] += value;
            tempy += (tempy & -tempy);
        }

        x += (x & -x);
    }
}

//sum(x,y) means sum of arr[1][1]~arr[x][y]
ll sum(int x, int y) {
    ll ret=0;
    while(x>0) {
        int tempy = y;
        while(tempy > 0) {
            ret += fenwick[x][tempy];
            tempy -= (tempy & -tempy);
        }
        x -= (x & -x);
    }
    return ret;
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// THIS IS TARJAN ALGORITHM FOR SCC

/*
#define MAX 10001 //when used in 2-sat, you have to double node because not only x1~x100 is required but also Nx1~Nx100
vvi SCC;
int d[MAX];
bool finished[MAX];
vi edge[MAX];
int id, SN=0; //mark sn[i]
stack<int> s;
int sn[MAX]; //sn[i] is SCC number to which it belongs to. If sn is big, then it is at the start of DAG. If small, it is at the end of DAG. If one wants to start from the beginning of DAG, start from the largest of sn.
int SCCnode[MAX] {}; //if SCCbfs is needed...
int nodeValue[MAX] {}; //if SCCbfs is needed...
int dfs(int x) {
    d[x] = ++id; //노드마다 고유한 아이디 부여
    s.push(x); //스택에 자기 자신을 삽입
    int parent = d[x];
    for (auto i : edge[x]) {
        if (d[i] == 0) { //방문 안 한 이웃
            parent = min(parent, dfs(i));
        }
        else if (finished[i] == 0) { //처리 중인 이웃
            parent = min(parent, d[i]);
        }
    }
    if (parent == d[x]) {
        vector<int> scc;
        while (true) {
            int t = s.top();
            s.pop();
            scc.push_back(t);
            finished[t] = 1;
            sn[t] = SN;
            //d[t] = x; //to make scc recognizable with d
            //SCCnode[SN] += nodeValue[t];
            if (t == x) break;
        }
        SN++;
        SCC.push_back(scc); //SCC의 SN번째 그래프랑 대응된다
    }
    return parent;
}

vi SCCedge[MAX]; //index refers to SN. Could be replaced with set if you don't want to overlap
int inDegree[MAX]; //index refers to SN
void SCCtopology_sort() {
    for(int i=1;i<=N;i++) { //id starts with 1
        for(auto next : edge[i]) {
            if(sn[next]!=sn[i]) {
                SCCedge[sn[i]].pbk(sn[next]); //SN could be overlapped. Could be solved with set but it is often not needed
                inDegree[sn[next]]+=1; //If inDegree is 0, then it is the start of the SCC graph. There could be many
            }
        }
    }
}

//If SCC sum is needed
int SCCdp[MAX] {};
void SCCbfs(int x) { //x is sn. bfs graph is not vertex graph but scc graph. scc graph is DAG so visited array is not needed
    //bfs starts with x. Function flows through SCC graph (topologically)
    qi q;
    q.push(x);
    SCCdp[x] = SCCnode[x];

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(auto next : SCCedge[cur]) {
            if(SCCdp[next] < SCCdp[cur] + nodeValue[next]) {
                SCCdp[next] = SCCdp[cur] + nodeValue[next];
                q.push(next);
            }
        }
    }
}

int oppo(int num) { //This is for 2-sat
    return num % 2 ? num + 1 : num - 1;
}

int result[MAX] {}; //For finding value of each clause (x1, x2, x3)
void sat2() { // (x1 or x2) and (Nx1 or x3) //Nx1->x2, Nx2->x1. x1->x3, Nx3->Nx1
    cin >> N >> M; // N is # of node, M is # of conditions
    for (int i = 0; i < M; i++) {
        int A, B; //If num is negative #, then it is (not) positive num
        cin >> A >> B;
        A = A > 0 ? 2 * A - 1 : -2 * A; //positive num goes 1->1, 2->3, 3->5, 4->7, 5->9... and so on
        B = B > 0 ? 2 * B - 1 : -2 * B; //negative num goes -1->2, -2->4, -3->6, -4->8... and so on
        edge[oppo(A)].push_back(B);
        edge[oppo(B)].push_back(A);
    }
    for (int i = 1; i <= 2 * N; i++) { //node is 1~2*N
       if (d[i] == 0) dfs(i);
    }
    for (int i = 1; i <= N; i++) {
        if (sn[2 * i-1] == sn[2 * i]) {
            cout << "contradiction!" << " " << sn[i] << endl;
        }
    }

    //For finding out value of each clause

    memset(result, -1, sizeof(result));
    pii p[MAX];
    for(int i=1;i<=2*N;i++) {
        p[i] = {sn[i], i};
    }
    sort(p+1, p+2*N+1);

    for(int i=2*N;i>0;i--) { //Start from the beginning of DAG
        int node = p[i].second;
        int src = (node+1)/2;

        if(result[src] == -1) result[src] = node%2 ? 0 : 1;
    }

    for(int i=1;i<=N;i++) {
        cout << result[i] << " ";
    }
}
*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//This is SPFA 
/*
#define MAX 100001
bool inQ[MAX] {};
vpii edge[MAX];
int d[MAX];
int cycle[MAX] {};
void SPFA(int start) {
    fill(d+1, d+1+N, INF);
    qi q;
    d[start] =0;
    q.push(start);
    inQ[start] = 1;
    cycle[start] += 1;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        inQ[cur] = 0;
        for(auto next : edge[cur]) {
            if(d[next.first] > d[cur] + next.second) {
                d[next.first] = d[cur] + next.second;
                if(!inQ[next.first]) {
                    cycle[next.first] += 1;
                    if(cycle[next.first]>=N) {
                        cout << "CYCLE!!!!" << endl;
                        return;
                    }
                    q.push(next.first);
                    inQ[next.first] = 1;
                }
            }
        }
    }
}
*/

// This is Floyd-Warshall
/*
#define MAX 501
int dp[MAX][MAX] {}; //input should be done in dp table
void floyd_warshall() {
    rep(k, 1, N) {
        rep(i, 1, N) {
            rep(j, 1, N) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) dp[i][j] = dp[i][k] + dp[k][j];
            }
        }
    }
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//This is Network Flow with Dinic Algorithm. Time Complexity O(V^2 * E)

// 
/*
#define MAX 100 //MAX should be treated carefully since space complexity is limited. (256mb, 512mb)
vector<int> edge[MAX];
int f[MAX][MAX], c[MAX][MAX];
int level[MAX], work[MAX];
int src, sink;
int bias;

void addEdge(int s, int e, int value=1) { //Decide whether graph is directed graph or undirected graph
    edge[s].pbk(e);
    edge[e].pbk(s);
    c[s][e] = value;
}
bool bfs() { // to create level graph and decide if flow is no longer needed
    queue<int> q;
    q.push(src); //
    memset(level, -1, sizeof(level));
    level[src] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto next : edge[cur]) {
            if (level[next] == -1 && c[cur][next] - f[cur][next] > 0) {
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
    }
    if (level[sink] == -1) return false;
    else return true;
}
int dfs(int cur, int flow) { //cur node has flow to offer to the next level
    if (cur == sink) return flow;

    for (int& i = work[cur]; i < edge[cur].size(); i++) {
        int next = edge[cur][i];
        if (level[next] == level[cur] + 1 && c[cur][next] - f[cur][next] > 0) {
            int ret = dfs(next, min(flow, c[cur][next] - f[cur][next]));
            if (ret > 0) {
                f[cur][next] += ret;
                f[next][cur] -= ret; //always remember to create reverse flow
                return ret;
            }
        }
    }
    return 0;
}
int Network_Flow() {
    int totalFlow = 0;
    while (bfs()) {
        memset(work, 0, sizeof(work));
        while (true) {
            int flow = dfs(src, INF); //INF varies from range to range
            if (flow == 0) break;
            totalFlow += flow;
        }
    }
    return totalFlow;
}
*/


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//Network Flow with Edmonds Karp
/*
#define MAX 100
int d[MAX] {}; //keep track of parent
vi edge[MAX];
int f[MAX][MAX], c[MAX][MAX];
int maxFlow(int start, int end) {
    int result=0;
    while(1) {
        fill(d, d+MAX, -1);
        qi q;
        q.push(start);

        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            for(auto next : edge[cur]) {
                if(c[cur][next]-f[cur][next] > 0 && d[next]==-1) {
                    q.push(next);
                    d[next] = cur;
                    if(next==end) break;
                }
            }
        }

        if(d[end]==-1) break;

        int flow = INF;

        for(int i=end;i!=start;i=d[i]) {
            flow = min(flow, c[d[i]][i] - f[d[i]][i]);
        }

        for(int i=end;i!=start;i=d[i]) {
            f[d[i]][i] += flow;
            f[i][d[i]] -= flow;
        }
        result += flow;
    }
    return result;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//MCMF with SPFA+Edmonds-Karp

/*
#define MAX 1001
int f[MAX][MAX]; //flow
int c[MAX][MAX]; //capacity
int d[MAX][MAX]; //cost of flowing fluid. f[x][y] * d[x][y] is
int S, T;
vi edge[MAX];
int bias; //set bias in bipartite graph
//MCMF could be done with Dinic but is not effective unless it has sparse table
//https://justicehui.github.io/hard-algorithm/2020/03/24/effective-mcmf/
//but it is nonetheless more effective than SPFA+Edmonds-Karp
void MCMF() {
    //set S and T
    //input edge

    ll result =0;
    while(1) {
        int prev[MAX]{}; //record previous node
        int dist[MAX]{}; //record
        bool inQ[MAX] {};

        fill(prev, prev+MAX, -1);
        fill(dist, dist+MAX, INF);

        qi q;
        q.push(S);
        inQ[S] = 1;
        dist[S] = 0;
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            inQ[cur] =0;

            for(auto next : edge[cur]) {
                if(c[cur][next]-f[cur][next] > 0 && dist[next] > dist[cur] + d[cur][next]) {
                    dist[next] = dist[cur] + d[cur][next];
                    prev[next] = cur;

                    if(!inQ[next]) {
                        inQ[next] = 1;
                        q.push(next);
                    }
                }
            }
        }

        if(prev[T]==-1) break;

        int flow = INF;
        for(int i = T;i!=S;i=prev[i]) {
            flow = min(flow, c[prev[i]][i]-f[prev[i]][i]);
        }


        for(int i = T;i!=S;i=prev[i]) {
            result += flow * d[prev[i]][i];
            f[prev[i]][i] += flow;
            f[i][prev[i]] -= flow;
        }
    }
    cout << result;
}

*/
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// This is CCW

struct Point {
    ll x, y;
    Point(ll x=0, ll y=0) : x(x), y(y) {}
};

double getDist(Point a, Point b) {
    int dx = a.x-b.x;
    int dy = a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}

void Solve() {
    cin >> N;
    vector<Point> v(N+1);
    rep(i,1,N) {
        cin >> v[i].x >> v[i].y;
    }
    vector<vector<double>> dp(N+1, vector<double>(N+1));

    auto go = [&](auto&& self, int a, int b) -> double {
        auto& ret = dp[a][b];
        if(ret>0) return ret;
        ret = 1e9;
        if(a==N) return ret = getDist(v[b], v[N]);
        if(b==N) return ret = getDist(v[a], v[N]);
        int next = max(a,b)+1;
        return ret = min(self(self, next, b) + getDist(v[a], v[next]), self(self, a,next) + getDist(v[b], v[next]));
    };
    cout << go(go, 1,1) << endl;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--) Solve();
}