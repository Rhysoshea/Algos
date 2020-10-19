#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;
using namespace std;

void partition3(vector<vector< double> > &a, double l, double r, int &m1, int &m2) {
  double x = a[l][2];
  m1 = l;
  m2 = r;

  if (r - l <= 1) {
    if (a[r][2] < a[l][2]) {
      swap(a[r], a[l]);
    }
    m1 = l;
    m2 = r;
    return;
  }
  while (l <= r)  {

    if (a[l][2] < x) {
      swap(a[l], a[m1]);
      m1++;
      l++;
    }
    else if (a[l][2] == x) {
      l++;
    }
    else if (a[l][2] > x) {
      swap(a[l], a[m2]);
      m2--;
      r--;
    }
  }
  return;
}

void quick_sort(vector<vector< double> > &a, double l, double r) {
  if (l >= r) {
    return;
  }

  int m1, m2;
  partition3(a, l, r, m1, m2);


  quick_sort(a, l, m1-1);
  quick_sort(a, m2+1, r);

}

int find(vector< vector<int> > &vertices, int node) {
  if (vertices[node][0] == node) {
    return node;
  }
  find(vertices, vertices[node][0]);
  return 0;
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  int n = (x.size()*(x.size()-1))/2;
  cout << "n: " << n << "\n";
  vector<vector< double> > edges(n, vector<double>());
  // edges[i][x y distance]
  vector< vector<int> > vertices(x.size(), vector<int>(2));
  // vertices[parent][connected] index based

  int count = 0;
  for (int i = 0; i < x.size(); i++) {
    vertices[i][0] = i;
    vertices[i][1] = 0;
    for (int j = i+1; j < x.size(); j++) {
      edges[count].push_back(i);
      edges[count].push_back(j);
      double dist = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
      edges[count].push_back(dist);
      count ++;
      // cout << "i: " << i << " j: " << j << " count: " << count << "\n";
    }
  }

  // // print out edges
  // for (int i =0; i<edges.size(); i++) {
  //   for (int j=0; j<edges[i].size(); j++) {
  //     cout << edges[i][j] << "\n";
  //   }
  // }
  // for (int i =0; i<vertices.size(); i++) {
  //   cout << vertices[i] << "\n";
  // }

  // sort edges according to distance
  quick_sort(edges, 0, edges.size()-1);

  // cout << "sorted\n";
  //
  // for (int i =0; i<edges.size(); i++) {
  //   for (int j=0; j<edges[i].size(); j++) {
  //     cout << edges[i][j] << "\n";
  //   }
  // }

  int root = edges[0][0];
  cout << "root: " << root << "\n";
  vertices[root][1] = 1; // make the root connected

  for (int edge = 0; edge<edges.size(); edge++) {
    cout << "find 1: " << find(vertices, edges[edge][0]) << " find 2: " << find(vertices, edges[edge][1]) << "\n";
    if (find(vertices, edges[edge][0]) != find(vertices, edges[edge][1])) {
      if (vertices[edges[edge][1]][0] == 0 || vertices[edges[edge][1]][1] == 0) {

        cout << "1: " << edges[edge][0] << " 2: " << edges[edge][1] << " distance: " << edges[edge][2] << "\n";
        result += edges[edge][2];
        // union();
        vertices[edges[edge][1]][0] = vertices[edges[edge][0]][0];
        if (find(vertices, edges[edge][0]) == root) {
          vertices[edges[edge][0]][1] = 1;
        }
        if (find(vertices, edges[edge][1]) == root) {
          vertices[edges[edge][1]][1] = 1;
        }
        // vertices[edges[edge][1]][1] = 1;
        cout << "find 1: " << find(vertices, edges[edge][0]) << " find 2: " << find(vertices, edges[edge][1]) << "\n";

      }
    }
  }
  cout << "connected\n";

  for (int i =0; i<vertices.size(); i++) {
      cout << vertices[i][1] << "\n";
  }

  return result;
}

int main() {

  size_t n;
  cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
