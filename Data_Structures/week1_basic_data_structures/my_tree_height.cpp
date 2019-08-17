#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sys/time.h>
#include <csignal>
#include <queue>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;
using namespace std;
using std::vector;

/*
You are given a description of a rooted tree. Your task is to compute and output its height. Recall that the height of a (rooted) tree is the maximum depth of a node, or the maximum distance from a leaf to the root. You are given an arbitrary tree, not necessarily a binary tree.
*/

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

/*
Naive base function
*/

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }

  std::cout << maxHeight << std::endl;
  return 0;
}

/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}

/*
Test function
*/

// int main_test_solution() {
//   // turns off the synchronization of all the C++ standard streams with their C counterparts for faster I/O.
//   std::ios_base::sync_with_stdio(0);
//   int n;
//   cin >> n;
//   int root_index;
//   vector<Node> nodes;
//   nodes.resize(n);
//   for (int child_index = 0; child_index < n; child_index++) {
//     int parent_index;
//     cin >> parent_index;
//     if (parent_index >= 0) {
//       nodes[child_index].setParent(&nodes[parent_index]);
//     }
//     else {
//       root_index = child_index;
//     }
//     nodes[child_index].key = child_index;
//   }
//
//   // Replace this code with a faster implementation
//   int height = 1;
//   queue<Node *> q;
//   // cout << "root index: "<< root_index << "\n";
//
//   // push the root node to the queue
//   q.push(&nodes[root_index]);
//
//   while (q.empty() == false) {
//     // get the node at the front of the queue
//     Node *current_node = q.front();
//     cout << "current node: "<< current_node->key << "\n";
//     q.pop();
//
//     vector<Node *> children_of_parent = current_node->children;
//     for (int i=0; i<children_of_parent.size(); i++) {
//       cout << "children: "<< children_of_parent[i]->key << "\n";
//     }
//
//     // Node marker;
//     // marker.key = -1;
//     // marker.parent = NULL;
//     // if (current_node->key == -1) {
//     //   height++;
//     // }
//     cout << "children size: "<< children_of_parent.size() << "\n";
//     cout << "height: "<< height << "\n";
//
//     if (children_of_parent.size()>0) {
//       // height++;
//       for (int i=0; i<children_of_parent.size(); i++) {
//           q.push(children_of_parent[i]);
//       }
//       // q.push(&marker);
//     }
//
//   }
//
//   cout << height << endl;
//   return 0;
// }

void rec_tree(queue<Node *> q, int &height) {
  queue<Node *> sub_q;
  height ++;
  while (q.empty() == false) {
    // get the node at the front of the queue
    Node *current_node = q.front();
    // cout << "current node: "<< current_node->key << "\n";
    q.pop();

    vector<Node *> children_of_parent = current_node->children;

    if (children_of_parent.size()>0) {
      for (int i=0; i<children_of_parent.size(); i++) {
          sub_q.push(children_of_parent[i]);
      }
    }
  }
  if (sub_q.empty() == false) {
    rec_tree(sub_q, height);
  }
}

int main_test_solution() {
  // turns off the synchronization of all the C++ standard streams with their C counterparts for faster I/O.
  std::ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  int root_index;
  vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    cin >> parent_index;
    if (parent_index >= 0) {
      nodes[child_index].setParent(&nodes[parent_index]);
    }
    else {
      root_index = child_index;
    }
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  int height = 0;
  queue<Node *> q;
  // cout << "root index: "<< root_index << "\n";

  // push the root node to the queue
  q.push(&nodes[root_index]);

  rec_tree(q, height);

  cout <<  height;
  return 0;
}





/*
submission function
*/

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 32 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_test_solution();
}


/*
test functions
*/
// int main() {
//
//   int n = generate(100000);
//   vector<int> a(n);
//   for (size_t i = 0; i < a.size(); ++i) {
//     a[i] = generate(1000000000);
//   }
//
//   struct timespec start, end;
//
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   test_solution(a, 0, a.size());
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
//   // calculate and print time
//   double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
//   time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//   cout << "n: " << n << "\n";
//   cout << "Time taken: " << fixed << time_taken;
//   cout << "sec" << endl;
// }


/*
stress testing
*/
// int main() {
//   struct timespec start, end;
//
//   while (true) {
//     int n = generate(100000);
//     vector<int> a(n);
//     for (size_t i = 0; i < a.size(); ++i) {
//       a[i] = generate(1000000000);
//     }
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int solution_base = base_solution(a, 0, a.size());
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int solution_test = test_solution(a, 0, a.size());
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     if (solution_base != solution_test) {
//       cout << "Input: " << n << "\n";
//       cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//       // break;
//     }
//     cout << "Input: " << n << "\n";
//     cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
