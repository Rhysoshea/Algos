#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using namespace std;

struct Node {
  long long int key;
  long long int left;
  long long int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long int key_, long long int left_, long long int right_) : key(key_), left(left_), right(right_) {}
};

struct Position {
  Position (long long int value, int flag) :
      value(value),
      flag(flag)
    {}
    // flag to show that that left !< key or right !>= key
    // 0 if ok, 1 if problem
    long long int value;
    int flag;
};



long long int inOrderTraversal(const vector<Node>& tree, int i, bool& stop, queue<Position>& order) {
  long long int left;
  long long int right = tree[i].key;
  if (tree[i].left == -1 && tree[i].right == -1) {
    // cout << tree[i].key << "\n";
    order.push(Position(tree[i].key, 0));
    return tree[i].key;
  }

  if (tree[i].left != -1) {
    left = inOrderTraversal(tree, tree[i].left, stop, order);
    // cout << "left: " << left << " key: " << tree[i].key << "\n";
    // if (left > tree[i].key) {
    //   stop = true;
    // }
  }
  // cout << "left: " << left << " right: " << right << "\n";
  // cout << "key: " << tree[i].key << "\n";
  if (left < tree[i].key && tree[tree[i].right].key >= tree[i].key && tree[i].right != -1 && tree[i].left != -1) {
    order.push(Position(tree[i].key, 0));
  } else if (left < tree[i].key && tree[i].right == -1 && tree[i].left != -1) {
    order.push(Position(tree[i].key, 0));
  } else if (tree[tree[i].right].key >= tree[i].key && tree[i].right != -1 && tree[i].left == -1) {
    order.push(Position(tree[i].key, 0));
  } else {
    order.push(Position(tree[i].key, 1));
  }

  // cout << tree[i].key << "\n";
  if (tree[i].right != -1) {
    right = inOrderTraversal(tree, tree[i].right, stop, order);
    // cout << "key: " << tree[i].key << " right: " << right << "\n";
    // if (tree[i].key > right) {
    //   stop = true;
    // }
  }

  if (tree[i].right == -1) {
    return tree[i].key;
  }
  return right;
}


bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  queue<Position> order;

  if (tree.size() < 2){
    return true;
  }
  bool stop = false;
  inOrderTraversal(tree, 0, stop, order);

  // cout << "queue:\n";
  Position last = order.front();
  order.pop();
  while (!order.empty()) {
    Position current =  order.front();
    // cout << "last: " << last.value << " " << last.flag << " current: " << current.value << " " << current.flag << "\n";
    if (last.value > current.value) {
      return false;
    }
    if (current.flag == 1){
      return false;
    }
    last = current;
    order.pop();
  }



  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    long long int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

// int main (int argc, char **argv)
// {
// #if defined(__unix__) || defined(__APPLE__)
//   // Allow larger stack space
//   const rlim_t kStackSize = 1024 * 1024 * 1024;   // min stack size = 16 MB
//   struct rlimit rl;
//   int result;
//
//   result = getrlimit(RLIMIT_STACK, &rl);
//   if (result == 0)
//   {
//       if (rl.rlim_cur < kStackSize)
//       {
//           rl.rlim_cur = kStackSize;
//           result = setrlimit(RLIMIT_STACK, &rl);
//           if (result != 0)
//           {
//               std::cerr << "setrlimit returned result = " << result << std::endl;
//           }
//       }
//   }
//
// #endif
//   return main_test_solution();
// }
