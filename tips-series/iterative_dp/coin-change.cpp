#include <bits/stdc++.h>

using namespace std;

int coins[101];     // values of different coins
int n;              // n coins
int dp[101][1001];  // memoization array

int solve(int pos, int amount) {
  if (amount == 0)            return 1;
  if (pos == n)               return 0;
  if (dp[pos][amount] != -1)  return dp[pos][amount];

  int ans = solve(pos+1, amount);

  for (int i=1;i<=(amount/coins[pos]);i++) {
    ans += solve(pos+1, amount - (i * coins[pos]));
  }

  dp[pos][amount] = ans;

  return ans;
}

int solveIterative(int amount) {
  for (int i=n;i>=0;i--) {
    for (int j=0;j<=amount;j++) {
      if (j == 0)     dp[i][j] = 1;
      if (i == n)     dp[i][j] = 0;

      int ans = dp[i+1][j];

      for (int k=1;k<=(j / coins[i]); k++) {
        ans += dp[i+1][j - (k * coins[i])];
      }

      dp[i][j] = ans;
    }
  }

  // solve(0, amount);
  return dp[0][amount];
}

int main() {
  return 0;
}