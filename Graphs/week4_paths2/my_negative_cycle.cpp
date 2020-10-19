#include <iostream>
#include <vector>
#include <limits>


using std::vector;
using namespace std;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, vector<int> &dist, vector<int> &prev) {
  //write your code here
  for (int i = 0; i < adj.size(); i++) {
    dist[i] = numeric_limits<int>::max();
    prev[i] = 0;
  }
  dist[s] = 0;

  for (int i = 0; i < adj.size()-1; i++) {
    dist[i] = numeric_limits<int>::max();
    prev[i] = 0;
  }

  return 0;
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

  cout << negative_cycle(adj, cost, dist, prev);
}
