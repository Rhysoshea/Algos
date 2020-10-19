#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using namespace std;

int bipartite(vector<vector<int> > &adj, vector<int> &dist, queue<int> &Q) {
  //write your code here
  for (int i = 0; i < adj.size(); i++) {
    dist[i] = numeric_limits<int>::max();
  }
  dist[0] = 0;

  Q.push(0);

  while (Q.empty() == false) {
    int u = Q.front();
    Q.pop();
    for (int v = 0; v < adj[u].size(); v++) {
      if (dist[adj[u][v]] == numeric_limits<int>::max()) {

        Q.push(adj[u][v]);
        if (dist[u] == 0) {
          dist[adj[u][v]] = 1;
        } else {
          dist[adj[u][v]] = 0;
        }
      }
      else {
        if (dist[u] == dist[adj[u][v]]) {
          return 0;
        }
      }
    }
  }
  return 1;
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
  cout << bipartite(adj, dist, Q);
}
