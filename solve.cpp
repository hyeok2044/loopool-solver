#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
const ll              ERROR = 909090909;

// Random value is assigned when something goes wrong.
class frac
{
private:
  ll num;
  ll den;

public:
  frac(ll num, ll den) : num(num), den(den){};
  frac(ll num) : num(num), den(1){};

  void simplify()
  {
    if (den == 0) {
      num = ERROR, den = 1;
      return;
    }
    ll div = gcd(num, den);
    num /= div;
    den /= div;
  }
  frac simplify(frac &a)
  {
    if (a.den == 0)
      return {ERROR, 1};
    ll   div = gcd(a.num, a.den);
    frac res = {a.num / div, a.den / div};
    return a;
  }

  frac operator+(const frac &other)
  {
    frac res = {num * other.den + other.num * den, den * other.den};
    return simplify(res);
  }

  frac operator-(const frac &other)
  {
    frac res = {num * other.den - other.num * den, den * other.den};
    return simplify(res);
  }

  frac operator-()
  {
    frac res = {-num, den};
    return simplify(res);
  }

  frac operator*(const frac &other)
  {
    frac res = {num * other.num, den * other.den};
    return simplify(res);
  }

  frac operator/(const frac &other)
  {
    frac res = {num * other.den, den * other.num};
    return simplify(res);
  }

  bool operator==(const frac &other)
  {
    frac a = {num, den};
    frac b = {other.num, other.den};
    a      = simplify(a);
    b      = simplify(b);
    return a.num == b.num && a.den == b.den;
  }

  // returns ERROR if the denominator is not 1.
  ll result()
  {
    simplify();
    if (den != 1)
      return ERROR;
    return num;
  }
};

// Postfix tokens
vector<string> token[5] = {
    {"a", "2", "/", "b", "+", "2", "-"},
    {"c", "2", "*", "d", "-"},
    {"e", "f", "/", "1", "+"},
    {"g", "h", "/", "4", "+"},
    {"i", "8", "+"}
};
vector<ll> alphabetMap = {1, 2, 3, 4, 5, 6, 7, 8, 9};

ll evaluateValue(int tokenNo, const vector<ll> &currentMap)
{
  stack<frac> s;
  for (const string &st : token[tokenNo]) {
    if (isalpha(st[0])) {
      s.push(currentMap[st[0] - 'a']);
    } else if (isdigit(st[0]) || (st.size() > 1 && st[0] == '-')) {
      s.push(stoll(st));
    } else {
      if (s.size() < 2)
        return ERROR;
      frac b = s.top();
      s.pop();
      frac a = s.top();
      s.pop();
      if (st == "+")
        s.push(a + b);
      else if (st == "-")
        s.push(a - b);
      else if (st == "*")
        s.push(a * b);
      else if (st == "/") {
        s.push(a / b);
      }
    }
  }
  return s.empty() ? ERROR : s.top().result();
}

void solve()
{
  int         n     = 5;
  vector<int> order = {0, 1, 2, 3, 4};
  sort(alphabetMap.begin(), alphabetMap.end());

  // 1. 토큰 연결 순서 순열
  do {
    // 2. 알파벳 숫자 할당 순열
    sort(alphabetMap.begin(), alphabetMap.end());
    do {
      bool possible = true;
      for (int i = 0; i < n; i++) {
        ll res = evaluateValue(i, alphabetMap);
        if (res == ERROR) {
          possible = false;
          break;
        }

        string target = token[order[i]][0];
        ll     targetVal =
            isalpha(target[0]) ? alphabetMap[target[0] - 'a'] : stoll(target);

        if (res != targetVal) {
          possible = false;
          break;
        }
      }

      if (possible) {
        cout << "=== Found Solution ===" << endl;
        for (int i = 0; i < n; i++)
          cout << i << " -> " << order[i] << endl;
        for (int i = 0; i < alphabetMap.size(); i++)
          cout << (char)('a' + i) << ":" << alphabetMap[i] << " ";
        cout << "\n" << endl;
      }
    } while (next_permutation(alphabetMap.begin(), alphabetMap.end()));
  } while (next_permutation(order.begin(), order.end()));
}

int main()
{
  ios_base::sync_with_stdio(false); // 속도 향상
  cin.tie(NULL);
  solve();
  cout << "=== Program Terminated ===" << endl;
  return 0;
}
