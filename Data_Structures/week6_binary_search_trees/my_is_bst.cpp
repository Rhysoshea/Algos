#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

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

long long int inOrderTraversal(const vector<Node>& tree, int i, bool& stop, queue<int>& order) {
  long long int left;
  long long int right = tree[i].key;
  if (tree[i].left == -1 && tree[i].right == -1) {
    // cout << tree[i].key << "\n";
    order.push(tree[i].key);
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
  order.push(tree[i].key);


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
  queue<int> order;

  if (tree.size() < 2){
    return true;
  }
  bool stop = false;
  // int aux_node = -100000000000;
  inOrderTraversal(tree, 0, stop, order);

  // cout << "queue:\n";
  int last = order.front();
  order.pop();
  while (!order.empty()) {
    int current =  order.front();
    // cout << "last: " << last << " current: " << current << "\n";
    if (last > current) {
      return false;
    }
    last = current;
    order.pop();
  }

  // if (stop == true ) {
  //   return false;
  // }


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
