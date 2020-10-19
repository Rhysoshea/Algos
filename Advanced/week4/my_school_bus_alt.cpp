#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <map>

using std::vector;
using namespace std;
typedef vector<vector<int> > Matrix;

const int INF = 1e9;

Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

struct Back_pair {
  int first = -1;
  int second = -1;
};

vector< vector<int> > getAllSubsets(vector<int> &set)
{
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i < set.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( set[i] );

        for (int j = 0; j < subsetTemp.size(); j++) {
            subset.push_back( subsetTemp[j] );
        }
    }
    return subset;
}

void print_backtrack(vector<vector< Back_pair>> backtrack) {
  for (vector< Back_pair> row : backtrack) {
    for (Back_pair pair : row) {
      cout << pair.first << " " << pair.second << endl;
    }
    cout << "; ";
  }
  cout << endl;
}

std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
    // This solution tries all the possible sequences of stops.
    // It is too slow to pass the problem.
    // Implement a more efficient algorithm here.
    size_t n = graph.size();
    vector<int> set;
    for (int i=0; i<n; i++){
      set.push_back(i);
    }

    vector<vector<int>> subsets;

    // std::map<string, vector<int>> C(pow(2.0, n), vector<int>(n));
    vector<vector< int>> C(1<<n, vector<int>(n, INF));
    vector<vector< Back_pair>> backtrack(1<<n, vector<Back_pair>(n));

    // cout << "size C: " << C[0].size() << endl;
    C[1][0] = 0;

    // for (int value : set) {
    //   cout << set[value] << " ";
    // }
    // cout << endl;

    subsets = getAllSubsets(set);
    // for (vector<int> row : subsets) {
    //   for (int value : row) {
    //     cout << value;
    //   }
    //   cout << endl;
    // }

    for (int s=1; s<n; s++) {
      for (vector<int> subset : subsets) {
        if (subset.size() == s) {
          vector<int> S(subset.begin(), subset.end());

          // cout << "S size: " << S.size() << endl;
          // for (int i : S){
          //   cout << S[i] << " ";
          // }
          // cout << endl;

          S.insert(S.begin(), 0);

          // cout << "S adj: " << endl;
          // for (int i : S){
          //   cout << S[i] << " ";
          // }
          // cout << endl;

          int k = 0;
          for (int i : S) {
            cout << "i: " << i << endl;
            k += 1 << i;
            cout << "k: " << k << endl;

          }
          // cout << "k: " << k << endl;
          for (int i : S) {
            if (i != 0) {
              for (int j : S) {
                // cout << "j: " << j << endl;
                if (i != j) {
                  // if k corresponds to subset how to get subset - {j}
                  // k^(1<<j)
                  int curr = C[k ^ (1<<i)][j] + graph[i][j];
                  if (curr < C[k][i]) {
                    C[k][i] = curr;
                    backtrack[k][i].first = k ^ (1<<i);
                    backtrack[k][i].second = j;
                  }
                }
              }
            }
          }
        }
      }
    }
    int best_ans = INF;
    int currIndex2 = 0;
    for (int i=0; i<n; i++) {
      if (C[(1<<n) - 1][i] + graph[0][i] < best_ans) {
        best_ans = C[(1<<n) - 1][i] + graph[0][i];
        currIndex2 = i;
      }
    }

    if (best_ans >= INF)
        best_ans = -1;

    vector<int> best_path;
    int currIndex1 = (1<<n) - 1;
    // cout << "currIndex1: " << currIndex1 << endl;
    //
    // cout << "currIndex2: " << currIndex2 << endl;
    // cout << "backtrack:\n";
    // print_backtrack(backtrack);
    while (currIndex1 != -1) {
      // cout << "currIndex1: " << currIndex1 << endl;
      best_path.insert(best_path.begin(), currIndex2+1);
      Back_pair row = backtrack[currIndex1][currIndex2];
      currIndex1 = row.first;
      currIndex2 = row.second;
      // cout << "currIndex1: " << currIndex1 << endl;
      // cout << "currIndex2: " << currIndex2 << endl;

    }
    // cout << "best path size: " << best_path.size() << endl;
    return std::make_pair(best_ans, best_path);
}

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}
