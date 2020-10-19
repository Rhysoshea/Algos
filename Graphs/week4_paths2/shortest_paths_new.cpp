#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

void shortest_paths(vector<vector<long long> > &adj, vector<vector<long long> > &cost, long long s, vector<long long> &distance, vector<long long> &prev, vector<long long> &reachable) {
  //write your code here
  //set distance for source to 0 then relax all edges from source and set connected vertices to reachable
  distance[s] = 0;
  reachable[s] = 1;
  for (int v=0; v<adj[s].size(); v++){
    reachable[adj[s][v]] = 1;
    if (distance[adj[s][v]] > distance[s] + cost[s][v]) {
      distance[adj[s][v]] = distance[s] + cost[s][v];
      prev[adj[s][v]] = s;
    }
  }
  bool changed = false;

  for (int y=0; y<2*adj.size(); y++) {
    // explore reachable nodes
    // for (int y=0; y<adj.size(); y++) {
    changed = false;
        for (int i=0; i<reachable.size(); i++) {
          if (reachable[i]) {
            for (int v=0; v<adj[i].size(); v++) {
              reachable[adj[i][v]] = 1;
            }
          }
        }
      // }

      long long latest_relaxed;
      // check further reachable nodes and relax them
      for (int u=0; u<adj.size(); u++) {
        for (int v=0; v<adj[u].size(); v++){
          if (prev[adj[u][v]]!= -1 && reachable[prev[adj[u][v]]]) {
            reachable[adj[u][v]] = 1;
          }
          if (distance[adj[u][v]] > distance[u] + cost[u][v] && reachable[adj[u][v]]) {
            distance[adj[u][v]] = distance[u] + cost[u][v];
            if (distance[u] == std::numeric_limits<long long>::min()) {
              distance[adj[u][v]] = std::numeric_limits<long long>::min();
            }
            prev[adj[u][v]] = u;
            latest_relaxed = adj[u][v];
            changed = true;
          }
        }
      }

      // check for negative cycles and update distances
      for (int u=0; u<adj.size(); u++) {
        for (int v=0; v<adj[u].size(); v++){
          vector <long long> cycle;
          long long x = adj[u][v];
          if (prev[adj[u][v]]!= -1 && reachable[prev[adj[u][v]]]) {
            reachable[adj[u][v]] = 1;
          }
          for (int i=0; i<adj.size(); i++){
            if (x == -1) {
              break;
            }
            if (reachable[x]) {
              cycle.push_back(x);
            }
            x = prev[x];
            if (x == adj[u][v]) {
              if (!cycle.empty()){
                for (int j=0; j<cycle.size(); j++){
                  // cout << "x " << cycle[j] << "\n";
                  distance[cycle[j]] = std::numeric_limits<long long>::min();
                  for (int z=0; z<adj[cycle[j]].size(); z++){
                    distance[adj[cycle[j]][z]] = std::numeric_limits<long long>::min();
                  }
                }
              }
              break;
            }
          }
        }
      }

      for (int i=0; i<distance.size(); i++) {
        if (distance[i] == std::numeric_limits<long long>::min() && reachable[distance[i]]) {

          for (int v=0; v<adj[i].size(); v++) {
            if (distance[adj[i][v]] != std::numeric_limits<long long>::min()){
              distance[adj[i][v]] = std::numeric_limits<long long>::min();
              reachable[adj[i][v]] = 1;
              changed = true;
            }
          }
        }
      }
      if (changed == false) {
        break;
      }
    }  
}


int main() {
  long long n, m, s;
  cin >> n >> m;
  vector<vector<long long> > adj(n, vector<long long>());
  vector<vector<long long> > cost(n, vector<long long>());
  for (long long i = 0; i < m; i++) {
    long long x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  cin >> s;
  s--;
  vector<long long> distance(n, 10000000000);
  vector<long long> prev(n, -1);
  vector<long long> reachable(n, 0);
  // vector<long long> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, prev, reachable);// shortest);
  // for (long long i=0; i<prev.size();i++) {
  //   cout << prev[i] << "\n";
  // }
  // cout << "\n";
  // for (long long i=0; i<reachable.size();i++) {
  //   cout << reachable[i] << "\n";
  // }
  // cout << "\n";
  for (long long i = 0; i < n; i++) {
    if (!reachable[i]) {
        cout << "*\n";
    } else if (distance[i] == std::numeric_limits<long long>::min()) {
      cout << "-\n";
    } else {
      cout << distance[i] << "\n";
    }
  }
}




// Test cases
// 9 10
// 4 5 1
// 4 1 2
// 1 2 1
// 2 3 2
// 3 1 -5
// 4 6 2
// 6 7 1
// 7 8 2
// 8 6 -5
// 8 9 1
// 4
// -
// -
// -
// 0
// 1
// -
// -
// -
// -
//
//
// 6 8
// 2 3 -1
// 3 2 -1
// 1 4 1
// 1 5 1
// 1 6 1
// 2 4 1
// 2 5 1
// 2 6 1
// 1
// 0
// *
// *
// 1
// 1
// 1
//
// 4 4
// 1 2 1
// 2 3 1
// 3 1 -3
// 3 4 5
// 1
// -
// -
// -
// -
//
// 10 11
// 6 1 -1
// 1 2 10
// 1 3 100
// 2 3 5
// 3 5 7
// 3 7 2
// 5 4 10
// 5 8 3
// 8 10 2
// 4 3 -18
// 4 9 5
// 1
// 0
// 10
// -
// -
// -
// *
// -
// -
// -
// -
//
// 4 5 1 2 1 2 3 1 3 1 -3 3 4 1 4 3 1 4
// -
// -
// -
// -
//
// 6 7
// 1 2 10
// 2 3 5
// 1 3 100
// 3 5 7
// 5 4 10
// 4 3 -18
// 6 1 -1
// 3
// *
// *
// -
// -
// -
// *
//
// 3 2
// 2 3 -1
// 3 2 -1
// 1
// 0
// *
// *
//
// 5 4
// 1 2 1
// 4 1 2
// 2 3 2
// 3 1 -5
// 4
// -
// -
// -
// 0
// *
//
// 6 7
// 1 2 10
// 2 3 5
// 1 3 100
// 3 5 7
// 5 4 10
// 4 3 -18
// 6 1 -1
// 1
// 0
// 10
// -
// -
// -
// *
//
//
// 5 7
// 1 2 10
// 2 3 5
// 1 3 100
// 3 5 7
// 5 4 10
// 4 3 -18
// 5 1 -1
// 1
// -
// -
// -
// -
// -
