# LoopooL Solver

LoopooL Solver is a brute-force solver for LoopooL-style equation cycles,
where expressions form a closed loop of equalities.

> You only need to assign numbers so that all expressions form a “loop.”  
> A loop means that one or more expressions are connected by equal signs and circulate in a circular chain.

# Instruction

Users should manually fix the file given cpp file.
This is an example input for
Numbers: 1 ~ 9,

- A / 2 + B - 2
- C X 2 - D
- E / F + 1
- G / H + 4
- I + 8

```
// Postfix tokens
vector<string> token[5] = { // [1]
    {"a", "2", "/", "b", "+", "2", "-"},
    {"c", "2", "\*", "d", "-"},
    {"e", "f", "/", "1", "+"},
    {"g", "h", "/", "4", "+"},
    {"i", "8", "+"}
};

vector<ll> alphabetMap = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // [2]

...

void solve()
{
    int n = 5; // [3]
    vector<int> order = {0, 1, 2, 3, 4}; // [3]
```

## 1. Insert the tokens in a [postfix](https://en.wikipedia.org/wiki/Reverse_Polish_notation) manner.

Each tokens can be in a form of:

1.  lowercase alphabet
2.  numbers within the range of [-2^63, 2^63 -1]
3.  operators +, -, /, \*

## 2. Insert the number constraints

This does not account for duplicates for now.

## 3. Change the number of equations

orders should be in a form of 0, 1, 2, 3, ...

## 4. Execute the code.

`g++ -o solve solve.cpp && ./solve`

# Example output:

```
=== Found Solution ===
0 -> 0
1 -> 4
2 -> 1
3 -> 3
4 -> 2
a:6 b:5 c:4 d:7 e:9 f:3 g:8 h:2 i:1

=== Program Terminated ===
```

First part shows the loop order.
Second part shows the alphabet order.

## Limitations

- No duplicate number handling
- Manual code modification required
- Brute-force approach (not optimized)
