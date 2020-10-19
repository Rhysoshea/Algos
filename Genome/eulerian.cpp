#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>

using std::cin;
using std::cout;

// Task. Given a directed graph, find an Eulerian cycle in the graph or report that none exists.

struct EulerianGraph {
  private:
      /* These adjacency lists store only indices of edges in the edges list */
      std::vector<std::vector<int> > graph;

  public:
    explicit EulerianGraph(int n): graph(n) {}


    int graph_size(){
      return graph.size();
    }

    bool check_balanced(std::vector<int> &balancer){
      for (int v : balancer) {
        if (v % 2 != 0){
          return false;
        }
      }
      return true;
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

      return cycle;
    }


    void print_path(std::vector<int> &cycle) {

        cout << 1 << std::endl;
        for (int i=cycle.size()-1;i>0;i--) {
          cout << cycle[i]+1 << " ";
        }
    }

    void read_data(std::vector<int> &balancer, int e) {
      for (int i=0; i<e; i++) {
        int from, to;
        cin >> from;
        cin >> to;
        graph[from-1].emplace_back(to-1);
        balancer[from-1]++;
        balancer[to-1]++;

      }
    }
};


int main() {

  std::ios::sync_with_stdio(false); // disables C and C++ synchronization
  std::cin.tie(NULL); // unties cin and cout

  int v,e;
  cin >> v;
  cin >> e;
  std::vector<int> balancer(v,0);

  EulerianGraph graph(v);
  graph.read_data(balancer,e);
  if (!graph.check_balanced(balancer)) {
    cout << 0;
  }
  else {
  std::vector<int> cycle = graph.find_path(0);
  graph.print_path(cycle);
  }

  return 0;
}
