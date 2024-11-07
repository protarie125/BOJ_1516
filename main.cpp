#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;

ll N;
vl Time;
vvl Prev;
vl numPrev;
vl ans;

void solve() {
  queue<ll> Q{};
  for (auto i = 1; i <= N; ++i) {
    if (numPrev[i] == 0) {
      Q.push(i);
      ans[i] = Time[i];
    }
  }

  while (!Q.empty()) {
    auto f = Q.front();
    Q.pop();

    for (const auto& x : Prev[f]) {
      numPrev[x] -= 1;

      ans[x] = max(ans[x], ans[f] + Time[x]);
      if (numPrev[x] == 0) Q.push(x);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N;
  Time = vl(N + 1, 0);
  Prev = vvl(N + 1, vl{});
  numPrev = vl(N + 1, 0);
  for (auto i = 1; i <= N; ++i) {
    cin >> Time[i];

    ll x = 0;
    while (true) {
      cin >> x;
      if (x == -1) break;

      Prev[x].push_back(i);
      numPrev[i] += 1;
    }
  }
  ans = vl(N + 1, 0);

  solve();
  for (auto i = 1; i <= N; ++i) {
    cout << ans[i] << '\n';
  }

  return 0;
}