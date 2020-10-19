#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using namespace std;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void inOrderTraversal(int tree, int i) {
    if (left[i] != -1) {
      inOrderTraversal(key[left[i]], left[i]);
    }
    cout << tree << " ";
    if (right[i] != -1) {
      inOrderTraversal(key[right[i]], right[i]);
    }
  }

  vector <int> in_order() {
    vector<int> result;
    inOrderTraversal(key[0], 0);
    return result;
  }

  void preOrderTraversal(int tree, int i) {
    cout << tree << " ";
    if (left[i] != -1) {
      preOrderTraversal(key[left[i]], left[i]);
    }
    if (right[i] != -1) {
      preOrderTraversal(key[right[i]], right[i]);
    }
  }

  vector <int> pre_order() {
    vector<int> result;
    preOrderTraversal(key[0], 0);
    return result;
  }

  void postOrderTraversal(int tree, int i) {
    if (left[i] != -1) {
      postOrderTraversal(key[left[i]], left[i]);
    }
    if (right[i] != -1) {
      postOrderTraversal(key[right[i]], right[i]);
    }
    cout << tree << " ";
  }

  vector <int> post_order() {
    vector<int> result;
    postOrderTraversal(key[0], 0);

    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  t.in_order();
  cout << "\n";
  t.pre_order();
  cout << "\n";
  t.post_order();
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
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

  return main_with_large_stack_space();
}
