#include <bits/stdc++.h>

using namespace std;

int weights[101];   // weights of different object
int prices[101];    // prices of different object
int n;              // n objects
int dp[101][1001];  // memoization array

int solve(int pos, int weight) {
  if (pos == n)               return 0;
  if (weight == 0)            return 0;
  if (dp[pos][weight] != -1)  return dp[pos][weight];

  int ans = solve(pos+1, weight);

  if (weights[pos] <= weight)
    ans = max(ans, prices[pos] + solve(pos+1, weight - weights[pos]));

  dp[pos][weight] = ans;

  return ans;
}

int main() {
  return 0;
}