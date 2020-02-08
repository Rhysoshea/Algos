#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;

void explore(vector<int> &visited, vector<vector<int> > &adj, int v) {
  visited[v] = 1;
  for (int j=0; j < adj[v].size(); j++){
    if (visited[adj[v][j]] == 0) {
      explore(visited, adj, adj[v][j]);
    }
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here

  vector<int> visited(adj.size());
  explore (visited, adj, x);

  if (visited[y] == 1) {
    return 1;
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  cin >> x >> y;
  cout << reach(adj, x - 1, y - 1);
}
