#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using namespace std;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
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
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    bool run = true;
    while (run) {
        // pred stores
        vector<int> pred(graph.size(), -1);
        queue<int> q;
        q.push(from);

        while (!q.empty()) {
          int curr = q.front();
          q.pop();
          for (int i=0; i<graph.get_ids(curr).size(); i++) {
            int id = graph.get_ids(curr)[i]; // id is an integer that indexes the edges in graph[vertex]
              const FlowGraph::Edge& e = graph.get_edge(id);
              if (pred[e.to] == -1 && e.to != from && e.capacity > e.flow) {
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
              const FlowGraph::Edge& e = graph.get_edge(pred[i]);
              g = min(g, e.capacity - e.flow);
              i = e.from;
            }
          }
          i = pred.size()-1;
          while (i!=0){
            if (pred[i] != -1){
              const FlowGraph::Edge& e = graph.get_edge(pred[i]);
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
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
