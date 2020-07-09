#include <bits/stdc++.h>

using namespace std;

int weights[101];   // weights of different object
int n;              // n objects
int dp[101][1001];  // memoization array

int solve(int pos, int weight) {
  if (pos == n)               return 0;
  if (weight == 0)            return 0;
  if (dp[pos][weight] != -1)  return dp[pos][weight];

  int ans = solve(pos+1, weight);

  if (weights[pos] <= weight)
    ans = max(ans, 1 + solve(pos+1, weight - weights[pos]));

  dp[pos][weight] = ans;

  return ans;
}

int solveIterative(int weight) {
  for (int i=n;i>=0;i--) {
    for (int j=0;j<=weight;j++) {
      if (i == n)   dp[i][j] = 0;
      if (j == 0)   dp[i][j] = 0;

      int ans = dp[i+1][j];

      if (weights[i] <= weight)
        ans = max(ans, 1 + dp[i+1][j - weights[i]]);

      dp[i][j] = ans;
    }
  }

  // solve(0, weight);
  return dp[0][weight];
}

int main() {
  return 0;
}