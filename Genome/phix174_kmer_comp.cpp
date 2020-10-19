#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <math.h>

using std::cin;
using std::cout;

// Task. Let the “k-mer composition” of a string Text be defined as the list of every k-mer in Text (in any order). For example, the 3-mer composition of the circular string ACGTA is [ACG, CGT, GTA, TAC, AAC]. Given the k-mer composition of some unknown string, perform the task of Genome Assembly and return the circular genome from which the k-mers came. In other words, return a string whose k-mer composition is equal to the given list of k-mers.

struct EulerianGraph {

  private:
      /* These adjacency lists store only indices of edges in the edges list */
      std::vector<std::vector<int> > graph;

  public:
    explicit EulerianGraph(int n): graph(n) {}


    int graph_size(){
      return graph.size();
    }

    std::vector<int> find_path(int source) {
      std::vector<int> cycle;

      std::stack<int> curr_path;

      std::unordered_map<int,int> edge_count;
      for (int i=0; i<graph.size(); i++){
        edge_count[i] = graph[i].size();
      }

      curr_path.push(source);
      int curr_v = source;

      while(!curr_path.empty()) {

        if (edge_count[curr_v]) {
          curr_path.push(curr_v);
          int next_v = graph[curr_v].back();

          edge_count[curr_v]--;
          graph[curr_v].pop_back();

          curr_v = next_v;
        }
        else {
          cycle.push_back(curr_v);
          curr_v = curr_path.top();
          curr_path.pop();
        }
      }

      // add up the cycles

      return cycle;
    }


    void print_path(std::vector<int> &cycle) {
        for (int i=0;i<cycle.size()-1;i++) {
          cout << cycle[i]%2;
        }
    }

    void read_data(int p) {
      for (int i=0; i<p; i++) {
        int from, to;
        from = (i*2)%p;
        // cout << "i: " << i << std::endl;
        // cout << "from: " << from << std::endl;
        to = (i*2)%p+1;
        // cout << "to: " << to << std::endl;

        graph[i].emplace_back(from);
        graph[i].emplace_back(to);
      }
    }
};

// std::vector<std::string> generateBinaryStrings(std::vector<std::string> &arr, std::string str, int mer, int i) {
//     if (i == mer) {
//       arr[i] = str;
//       return arr;
//     }
//
//     str[i] = '0';
//     generateBinaryStrings(arr, str, mer, i+1);
//
//     str[i] = '1';
//     generateBinaryStrings(arr, str, mer, i+1);
// }

int main() {

  std::ios::sync_with_stdio(false); // disables C and C++ synchronization
  std::cin.tie(NULL); // unties cin and cout

  int mer;
  cin >> mer;
  // std::vector<int> balancer(v,0);
  // std::string str = "0000";
  // std::vector<std::string> arr(pow(2,mer));
  // std::vector<std::string> array = generateBinaryStrings(arr, str, mer, 0);

  // for (std::string str : array) {
  //   cout << str << std::endl;
  // }
  // cout << pow(2,mer) << std::endl;
  int p = pow(2,mer);
  EulerianGraph graph(p);
  graph.read_data(p);

  std::vector<int> cycle = graph.find_path(0);
  graph.print_path(cycle);

  return 0;
}
