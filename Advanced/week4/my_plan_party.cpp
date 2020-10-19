#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i) {
      std::cin >> tree[i].weight;
    }


    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int dfs(Graph &tree, std::vector<int> &weights, int vertex, int parent) {
    int weight, m1, m0;
    // tree[vertex].visited = 1;
    if (tree[vertex].children.size() == 0) {
      return tree[vertex].weight;
    }
    else {

      m1 = tree[vertex].weight;

      for (int child : tree[vertex].children) {
        if (child != parent ){
          for (int gchild : tree[child].children) {
            if (gchild != vertex ){
              if (weights[gchild] != 0) {
                m1 += weights[gchild];
              } else {
                m1 = m1 + dfs(tree, weights, gchild, child);
              }
            }
          }
        }
      }
      m0 = 0;
      for (int child : tree[vertex].children) {
        if ( child != parent ){
          if (weights[child] != 0) {
            m0 += weights[child];
          } else {
            m0 = m0 + dfs(tree, weights, child, vertex);

          }
        }
      }
    }
    weight = std::max(m1, m0);
    weights[vertex] = weight;
    return weight;
}

int MaxWeightIndependentTreeSubset(Graph &tree, std::vector<int> &weights) {
    size_t size = tree.size();
    int weight, m1, m0;

    if (size == 0)
        return 0;

    weight = dfs(tree, weights, 0, -1);
    // You must decide what to return.

    return weight;
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    // const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    // struct rlimit rl;
    // int result;
    // result = getrlimit(RLIMIT_STACK, &rl);
    // if (result == 0)
    // {
    //     if (rl.rlim_cur < kStackSize)
    //     {
    //         rl.rlim_cur = kStackSize;
    //         result = setrlimit(RLIMIT_STACK, &rl);
    //         if (result != 0)
    //         {
    //             fprintf(stderr, "setrlimit returned result = %d\n", result);
    //         }
    //     }
    // }

    // Here begins the solution
    Graph tree = ReadTree();
    vector<int> weights(tree.size(), 0);
    int weight = MaxWeightIndependentTreeSubset(tree, weights);
    std::cout << weight << std::endl;
    return 0;
}
