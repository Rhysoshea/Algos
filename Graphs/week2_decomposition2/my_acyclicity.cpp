#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;

void explore(vector<int> &visited, vector<vector<int> > &adj, int cc, int v, int &ans) {
  visited[v] = 1;
  for (int j=0; j < adj[v].size(); j++){
    // cout << "cc: " << cc << "\n";
    // cout << "adj: " << adj[v][j] << "\n";
    if (adj[v][j] == cc) {
      ans = 1;
    }
    if (visited[adj[v][j]] == 0) {
      explore(visited, adj, cc, adj[v][j], ans);
    }
  }
}


int acyclic(vector<vector<int> > &adj) {
  //write your code here
  int ans = 0;
  vector<int> visited(adj.size());
  for (int i=0; i < adj.size(); i++){
    // cout << "i: " << i << "\n";
    if (visited[i] == 0) {
      int cc = i;
      explore(visited, adj, cc, i, ans);
    }
  }
  if ( ans == 1) {
    return 1;
  }
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  cout << acyclic(adj);
}
