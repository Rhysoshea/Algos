#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using namespace std;

void shortest_paths(vector<vector<long long> > &adj, vector<vector<long long> > &cost, long long s, vector<long long> &distance, vector<long long> &prev, vector<long long> &reachable) { //, vector<long long> &shortest) {
  //write your code here
  //set distance for source to 0 then relax all edges from source
  int latest_relaxed;
  distance[s] = 0;
  reachable[s] = 1;
  for (long long v=0; v<adj[s].size(); v++) {
    if (distance[adj[s][v]] > distance[s] + cost[s][v]) {
      distance[adj[s][v]] = distance[s] + cost[s][v];
      prev[adj[s][v]] = s;
      reachable[adj[s][v]] = 1;
    }
  }

  // for all edges of all vertices check if distance can be reduced, if it can then set the previous vertice
  // do this twice
  // at the very end save the latest relaxed vertice
  // cout << "infinity "<< std::numeric_limits<long long>::infinity() << "\n";
  for (long long i=0;i < 2*adj.size(); i++) {
    for (long long u=0; u<adj.size(); u++) {
      for (long long v=0; v<adj[u].size(); v++) {
        // cout << adj[u][v] << "\n";
        // cout << "current distance " << distance[adj[u][v]] << " this distance " << distance[u] << " weight " <<  cost[u][v] << "\n";
        // cout << distance[u] + cost[u][v] << "\n";
        if (distance[u] == std::numeric_limits<long long>::min() && reachable[u]) {
          for (long long v=0; v<adj[u].size(); v++) {
            distance[adj[u][v]] = std::numeric_limits<long long>::min();
          }
        }
        if (prev[adj[u][v]]!= -1 && reachable[prev[adj[u][v]]]) {
          reachable[adj[u][v]] = 1;
        }
        if (distance[adj[u][v]] > distance[u] + cost[u][v] && reachable[prev[adj[u][v]]]) {
          distance[adj[u][v]] = distance[u] + cost[u][v];
          prev[adj[u][v]] = u;
          latest_relaxed = adj[u][v];
        }
      }
    }
  // }
  // cout << "latest relaxed " << latest_relaxed << "\n";
  int x = latest_relaxed;

  // for the latest relaxed vertice check if it is in a negative cycle
  // if it is in a negative cycle then add all vertices to a list then set the distance of the whole list to '-'.
  for (long long u=0; u < reachable.size(); u++) {
    if (reachable[u]) {
      for (long long v=0; v<adj[u].size(); v++) {
        reachable[adj[u][v]] = 1;
      }
    }
  }
  for (long long v=0; v<adj.size(); v++) {
    vector<long long> cycle;
    if (x == -1) {
      continue;
    }
    cycle.push_back(x);
    x = prev[x];
    // cout << "x " << x << "\n";
    if (x == latest_relaxed) {
      if (!cycle.empty()) {
        for (long long u=0; u<cycle.size(); u++) {
          // cout << "cycle " << cycle[u] << "\n";
          distance[cycle[u]] = std::numeric_limits<long long>::min();
            for (long long v=0; v<adj[cycle[u]].size(); v++) {
              if (reachable[cycle[u]]) {
                distance[adj[cycle[u]][v]] = std::numeric_limits<long long>::min();
              }
            }
          }
      }
      break;
    }
  }
  // cout << "done\n";
  // cout << "distance 2 "<< distance[1] << "\n";
  // check the distances again for any vertices in a negative cycle. All of the edges coming from the cycle should have vertices with distance '-'

  for (long long u=0; u < distance.size(); u++) {
    if (distance[u] == std::numeric_limits<long long>::min() && reachable[u]) {
      for (long long v=0; v<adj[u].size(); v++) {
        distance[adj[u][v]] = std::numeric_limits<long long>::min();
        reachable[adj[u][v]] = 1;
      }
    }
  }
  // cout << "distance 2 "<< distance[1] << "\n";
  // go through all vertices and edges again to check for any more negative cycles
  for (long long u=0; u<adj.size(); u++) {
    for (long long v=0; v<adj[u].size(); v++) {
      vector <long long> cycle_new;
      if (reachable[prev[adj[u][v]]]) {
        reachable[adj[u][v]] = 1;
      }
      if (distance[adj[u][v]] != std::numeric_limits<long long>::min()) {
        x = adj[u][v];
        // cout << "x " << x << "\n";

        for (long long j=0; j<adj.size(); j++){
          if (x == -1) {
            continue;
          }
          cycle_new.push_back(x);
          x = prev[x];
          // cout << "x " << x << "\n";

          if (x == adj[u][v]) {
            if (!cycle_new.empty()){
              // cout << "x " << x << " adj " << adj[u][v] << "\n";
              for (long long u=0; u<cycle_new.size(); u++) {
                // cout << "cycle " << cycle[u] << "\n";
                distance[cycle_new[u]] = std::numeric_limits<long long>::min();
                  for (long long v=0; v<adj[cycle_new[u]].size(); v++) {
                    if (reachable[cycle_new[u]]){
                      distance[adj[cycle_new[u]][v]] = std::numeric_limits<long long>::min();
                    }
                  }
                }
              }
            break;
          }

        }
      }
    }
  }
  for (int z=0; z<distance.size(); z++){
    if (distance[z] == std::numeric_limits<long long>::min() && reachable[z]) {
      for (long long v=0; v<adj[z].size(); v++) {
        distance[adj[z][v]] = std::numeric_limits<long long>::min();
        reachable[adj[z][v]] = 1;
      }
    }
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
  for (long long i=0; i<prev.size();i++) {
    cout << prev[i] << "\n";
  }
  cout << "\n";
  for (long long i=0; i<reachable.size();i++) {
    cout << reachable[i] << "\n";
  }
  cout << "\n";
  for (long long i = 0; i < n; i++) {
    if (distance[i] == 10000000000 && reachable[i]) {
      cout << "*\n";
    } else if (!reachable[i]) {
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
