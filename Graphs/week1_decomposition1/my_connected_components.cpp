#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;

void explore(vector<int> &visited, vector<vector<int> > &adj, vector<int> &ccnum, int cc, int v) {
  visited[v] = 1;
  ccnum[v] = cc;
  for (int j=0; j < adj[v].size(); j++){
    if (visited[adj[v][j]] == 0) {
      explore(visited, adj, ccnum, cc, adj[v][j]);
    }
  }
}

int number_of_components(vector<vector<int> > &adj) {
  //write your code here
  int cc = 0;

  vector<int> visited(adj.size());
  vector<int> ccnum(adj.size());
  for (int i=0; i < adj.size(); i++){
    if (visited[i] == 0) {
      cc+= 1;
      explore (visited, adj, ccnum, cc, i);
    }
  }

  return cc;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  cout << number_of_components(adj);
}
