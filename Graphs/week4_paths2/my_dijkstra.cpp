#include <iostream>
#include <vector>
#include <queue>
#include <limits>


using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int> &dist, vector<int> &prev, int s, int t, queue<int> &Q) {
  //write your code here
  for (int i = 0; i < adj.size(); i++) {
    dist[i] = numeric_limits<int>::max();
    prev[i] = 0;
  }
  dist[s] = 0;

  Q.push(s);

  while (Q.empty() == false) {
    int u = Q.front();
    Q.pop();
    for (int v = 0; v < adj[u].size(); v++) {
      if (dist[adj[u][v]] > dist[u] + cost[u][v]) {
        dist[adj[u][v]] = dist[u] + cost[u][v];
        prev[adj[u][v]] = u;
        Q.push(adj[u][v]);
      }
    }
  }
  if (dist[t] == numeric_limits<int>::max()) {
    return -1;
  }
  return dist[t];
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  vector<int> dist(adj.size());
  vector<int> prev(adj.size());
  queue<int> Q;
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, cost, dist, prev, s, t, Q);
}
