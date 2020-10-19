#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using namespace std;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
  if (adj[x].size()==0 && used[x] == 0){
    used[x] = 1;
    order.push_back(x);
  } else {
    for (int j=0; j < adj[x].size(); j++){
      if (used[adj[x][j]] == 0) {
        dfs(adj, used, order, adj[x][j]);
      }
    } if (used[x] == 0) {
      used[x] = 1;
      order.push_back(x);
    }
  }
}

vector<int> toposort(vector<vector<int> > adj) {
  // used works in a similar way to visited
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  for (int i=0; i<adj.size(); i++) {
    dfs(adj, used, order, i);
  }
  return order;
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
  vector<int> order = toposort(adj);
  for (int i = order.size()-1; i >= 0; i--) {
    cout << order[i] + 1 << " ";
  }
}
