#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using namespace std;

int distance(vector<vector<int> > &adj, vector<int> &dist, vector<int> &prev, queue<int> &Q, int s, int t) {
  //write your code here
  for (int i = 0; i < adj.size(); i++) {
    dist[i] = 1000000;
    prev[i] = 0;
  }
  dist[s] = 0;

  Q.push(s);

  while (Q.empty() == false) {
    int u = Q.front();
    Q.pop();
    for (int v = 0; v < adj[u].size(); v++) {
      if (dist[adj[u][v]] == 1000000) {
        Q.push(adj[u][v]);
        dist[adj[u][v]] = dist[u] + 1;
        prev[adj[u][v]] = u;
      }
    }
  }

  if (dist[t] == 1000000) {
    return -1;
  }
  return dist[t];

  // vector<int> result;
  //
  // while (t != s) {
  //   result.push_back(t);
  //   t = prev[t];
  // }
  //
  // return result.size();
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  vector<int> dist(adj.size());
  vector<int> prev(adj.size());
  queue<int> Q;
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, dist, prev, Q, s, t);
}
