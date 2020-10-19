#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


// Task. Given a network with lower bounds and capacities on edges, find a circulation if it exists.

using std::vector;
using namespace std;

class flowGraph {
public:
    struct Edge {
        int from, to, flow, cap, low;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit flowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int cap, int low) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, 0, cap, low};
        Edge backward_edge = {to, from, 0, 0, low};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);

        // cout << "edges size: " << edges.size() << "\n";
    }

    size_t size() const {
        return graph.size();
    }

    // returns a list of edge IDs associated with a vertex
    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    // returns the parameters of an edge by its ID
    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }

    // bool check_flow() {
    //   for (Edge e : edges) {
    //     if (e.flow < e.lower) {
    //       return false;
    //     }
    //   }
    //   return true;
    // }
    void printEdges(int edge_count){
      int count=0;

      // for (int i=0;i < edges.size(); i++) {
      //   cout << edges[i].flow << std::endl;
      // }
      // for (int i=0;i < edges.size(); i++) {
      //   cout << "from: " << edges[i].from << " to: " << edges[i].to << " flow: " << edges[i].flow << std::endl;
      // }
      while (count < edge_count) {
        cout << edges[2*count].flow + edges[2*count].low << std::endl;
        count++;
      }
    }

    int numEdges() {
      // cout << edges.size() << std::endl;
      return edges.size();
    }
};

flowGraph read_data(int vertex_count, int edge_count, vector<int> &in, vector<int> &out) {
    flowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int from, to, lower, cap;
        std::cin >> from >> to >> lower >> cap;
        in[to-1] += lower;
        out[from-1] += lower;
        int capacity = cap - lower;
        // cout << "capacity: " << capacity << std::endl;
        graph.add_edge(from, to, capacity, lower);
    }
    // add s and t vertices and connect them to every vertex with a capacity equal to the lower bound of the edges going in and out of that vertex;
    for (int i=1; i<graph.size()-1; i++){
      // s vertex connections
      graph.add_edge(0, i, in[i], 0);
      // t vertex connections
      graph.add_edge(i, graph.size()-1, out[i], 0);
    }

    return graph;
}

int circulation(flowGraph& graph, int from, int to) {
    int flow = 0;
    bool run = true;

    while (run) {
        // pred stores
        vector<int> pred(graph.size(), -1);
        queue<int> q;
        q.push(from);
        int minFlow = 0;

        while (!q.empty()) {
          int curr = q.front();
          q.pop();
          for (int i=0; i<graph.get_ids(curr).size(); i++) {
            int id = graph.get_ids(curr)[i]; // id is an integer that indexes the edges in graph[vertex]
              const flowGraph::Edge& e = graph.get_edge(id);

              if (pred[e.to] == -1 && e.to != from && e.cap > e.flow) {
                pred[e.to] = id;
                q.push(e.to);
              }
              if (pred[to] != -1){
                break;
              }
          }
        }

        if (pred[to] == -1) {
          run = false;
        }

        if (run) {
          int g = 1000000; // needs to be bigger than biggest possible flow
          int i = pred.size()-1;

          while (i!=0){
            if (pred[i] != -1){
              const flowGraph::Edge& e = graph.get_edge(pred[i]);
              g = min(g, e.cap - e.flow);
              i = e.from;
            }
          }
          i = pred.size()-1;
          while (i!=0){
            if (pred[i] != -1){
              const flowGraph::Edge& e = graph.get_edge(pred[i]);
              // cout << "flow: " << g << std::endl;
              graph.add_flow(pred[i], g);
              i = e.from;
            }
          }
          flow += g;
        }
    }
    return flow;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    vector<int> in(vertex_count,0);
    vector<int> out(vertex_count,0);

    flowGraph graph = read_data(vertex_count+2, edge_count, in, out);
    // graph.printNumEdges();
    // graph.printEdges();
    // cout << "\n";
    int maxFlow = circulation(graph, 0, vertex_count+1);
    int D=0;
    // cout << "in: " << std::endl;
    for (int i=0; i<in.size(); i++) {
      // cout << in[i] << "\n";
      D+=in[i];
    }
    cout << "maxFlow: " << maxFlow << " D: " << D << std::endl;
    if (D == maxFlow) {
      cout << "YES\n";
      graph.printEdges(edge_count);
    } else {
      cout << "NO\n";
    }
    return 0;
}
