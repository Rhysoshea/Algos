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

// vector< vector<int> > getAllSubsets(vector<int> &set)
// {
//     vector< vector<int> > subset;
//     vector<int> empty;
//     subset.push_back( empty );
//
//     for (int i = 0; i < set.size(); i++)
//     {
//         vector< vector<int> > subsetTemp = subset;
//
//         for (int j = 0; j < subsetTemp.size(); j++)
//             subsetTemp[j].push_back( set[i] );
//
//         for (int j = 0; j < subsetTemp.size(); j++) {
//             subset.push_back( subsetTemp[j] );
//         }
//     }
//     return subset;
// }

string convert_vert_to_bin_string(vector<int> sub) {
  string str = "00000000";
  for (int num : sub) {
    cout << "num: " << num << endl;
    str[str.size()-num-1] = '1';
  }
  return str;
}


std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
    // This solution tries all the possible sequences of stops.
    // It is too slow to pass the problem.
    // Implement a more efficient algorithm here.
    size_t n = graph.size();
    // vector<int> p(n);
    // for (size_t i = 0; i < n; ++i){
    //   p[i] = i+1;
    // }
    vector<vector<int>> subsets;

    vector<int> best_path;

    std::map<string,int> ref;
    vector<vector< int>> C(pow(2.0, n), vector<int>(n));
    cout << "size C: " << C[0].size() << endl;

    // convert from decimal to binary string
    for (int i=0; i<=pow(2.0,n)-1; i++) {
      std::string binary = std::bitset<8>(i).to_string();
      std::cout << binary << endl;
      ref[binary] = i;
      // cout << "size binary: " << binary.size() << endl;
      vector<int> temp;
      for (int j=binary.size(); j>0; j--) {
        if (binary[j] == '1') {
          // cout << "binary j: " << binary[j] << endl;
          temp.push_back(binary.size() - 1 - j);
        }
      }
      subsets.push_back(temp);
    }

    // subsets = getAllSubsets(p);
    for (vector<int> row : subsets) {
      for (int value : row) {
        cout << value;
      }
      cout << endl;
    }

    // // convert from binary string to decimal
    // unsigned long decimal = std::bitset<8>(binary).to_ulong();
    // std::cout<<decimal<<"\n";
    // return 0;
    // }

    for (int s=2; s<n+1; s++) {
      cout << "s: " << s << endl;

      for (vector<int> subset : subsets) {
        if (subset.size() == s && subset[0] == 0) {
          string str = convert_vert_to_bin_string(subset);
          // cout << "string: " << str << endl;
          int index = ref.find(str)->second;
          // cout << "index: " << index << endl;
          // cout << "C index: " << C[index][0] << endl;
          C[index][0] = INF;
          for (int i : subset) {
            cout << "i: " << i << endl;
            if (i != 1) {
              for (int j : subset) {
                cout << "j: " << j << endl;
                cout << "i: " << i << endl;
                if (i != j) {
                  // if k corresponds to subset how to get subset - {j}
                  // k^(1<<j)
                  cout << "here" << endl;

                  string index_l = str;
                  index_l[j] = '0';
                  cout << "index_l: " << index_l << endl;
                  int index_less = ref.find(index_l)->second;
                  // cout << "index_less: " << index_less << endl;
                  cout << "index: " << index << endl;
                  cout << "index_less: " << index_less << endl;
                  cout << "C index: " << C[index][i] << endl;
                  cout << "C index_less: " << C[index_less][j] << endl;
                  cout << "graph: " << graph[i][j] << endl;


                  C[index][i] = min(C[index][i], C[index_less][j] + graph[i][j]);
                  cout << "C index: " << C[index][i] << endl;

                }
              }
            }
          }
        }
      }
    }
    // while (std::next_permutation(p.begin(), p.end()) {
    //     int cur_sum = 0;
    //     bool ok = true;
    //     for (size_t i = 1; i < n && ok; ++i)
    //         if (graph[p[i - 1]][p[i]] == INF)
    //             ok = false;
    //         else
    //             cur_sum += graph[p[i - 1]][p[i]];
    //     if (graph[p.back()][p[0]] == INF)
    //         ok = false;
    //     else
    //         cur_sum += graph[p.back()][p[0]];
    //
    //     if (!ok)
    //         continue;
    //     if (cur_sum < best_ans) {
    //         best_ans = cur_sum;
    //         best_path = p;
    //     }
    // };
    string binary = std::bitset<8>(pow(2.0,n)-1).to_string();
    cout << "binary: " << binary << endl;
    int index = ref.find(binary)->second;
    cout << "index: " << index << endl;
    int best_ans = INF;
    for (int i : C[index]){
      cout << C[index][i] << endl;
      if (C[index][i] < best_ans){
        best_ans = C[index][i];
      }
    }
    if (best_ans == INF)
        best_ans = -1;
    for (size_t i = 0; i < best_path.size(); ++i)
        ++best_path[i];
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
