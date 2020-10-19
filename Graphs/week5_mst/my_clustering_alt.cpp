#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;
using namespace std;

// Only need to adap kruskal's algorithm here to run until a number of connections has been made that is equal to the number of vertices less the number of clusters to make. Because all the clusters will be made first then the next step will start to link the clusters, with the first edge being the shortest distance between any two clusters.

// quick sort
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
//---------------------

// int find(vector< vector<int> > &vertices, int node) {
//   if (vertices[node][0] == node) {
//     return node;
//   }
//   find(vertices, vertices[node][0]);
//   return 0;
// }

// disjoin set
struct DisjointSetsElement {
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int find(int vertice) {
		// find parent and compress path
    if (vertice != sets[vertice].parent) {
      sets[vertice].parent = find(sets[vertice].parent);
    }
    return sets[vertice].parent;
	}

	void merge(int destination, int source) {
		int realDestination = find(destination);
		int realSource = find(source);

		if (realDestination != realSource) {
			// merge two components
			// use union by rank heuristic
                        // update max_table_size
      if (sets[realSource].rank > sets[realDestination].rank) {
        sets[realDestination].parent = realSource;
        sets[realSource].size += sets[realDestination].size;
        sets[realDestination].size = 0;
        max_table_size = max(max_table_size, sets[realSource].size);
      }
      else {
        sets[realSource].parent = realDestination;
        sets[realDestination].size += sets[realSource].size;
        sets[realSource].size = 0;
        max_table_size = max(max_table_size, sets[realDestination].size);

        if (sets[realDestination].rank == sets[realSource].rank) {
          sets[realDestination].rank = sets[realDestination].rank + 1;
        }
      }
		}
	}
};
//-------------

double clustering(vector<int> x, vector<int> y, int k) {
  double result = 0.;
  //write your code here
  int n = (x.size()*(x.size()-1))/2;
  // cout << "n: " << n << "\n";
  if (x.size() < 2) {
    return 0;
  }
  vector<vector< double> > edges(n, vector<double>());
  // cout << "x size: " << x.size() << "\n";
  DisjointSets vertices(x.size());

  for (auto &vertice : vertices.sets) {
		vertice.size = 1;
		vertices.max_table_size = max(vertices.max_table_size, vertice.size);
	}

  int count = 0;
  for (int i = 0; i < x.size(); i++) {

    for (int j = i+1; j < x.size(); j++) {
      edges[count].push_back(i);
      edges[count].push_back(j);
      double dist = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
      edges[count].push_back(dist);
      count ++;
    }
  }

  // sort edges according to distance
  quick_sort(edges, 0, edges.size()-1);
  double last = 0.;
  int counter = 0;

  for (int edge = 0; edge<edges.size()+k+1; edge++) {

    if (vertices.find(edges[edge][0]) != vertices.find(edges[edge][1])) {
      last =  edges[edge][2];
      vertices.merge(edges[edge][0], edges[edge][1]);
      counter += 1;
      }
    if (counter >= x.size()-k+1) {
      break;
    }
    }

  return last;
}

int main() {

  size_t n;
  int k;
  cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  cin >> k;
  cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
