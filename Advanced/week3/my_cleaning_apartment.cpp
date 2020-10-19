#include <ios>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertHampathToSat {
    int numVertices;
    vector<Edge> edges;
    vector<vector<int> > clauses;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    int varNum(int n, int i, int j) {
        return (n*i + j);
    }

    vector< vector<int> > getAllSubsets(vector<int> &set, int size)
    {
        vector< vector<int> > subset;
        vector<int> empty;
        subset.push_back( empty );

        for (int i = 0; i < set.size(); i++)
        {
            vector< vector<int> > subsetTemp = subset;

            for (int j = 0; j < subsetTemp.size(); j++)
                subsetTemp[j].push_back( set[i] );

            for (int j = 0; j < subsetTemp.size(); j++) {
                subset.push_back( subsetTemp[j] );
            }
        }

        vector< vector<int>> subsetsToUse;
        for (int i=0; i<subset.size(); i++) {
          if (subset[i].size() == size){
            subsetsToUse.push_back(subset[i]);
          }
        }
        return subsetsToUse;
    }

    void exactlyOneof1(int n, int i, vector<int> &range) {
      vector<int> literals;
      delete range;
      for (int k=0; k<range.size(); k++){
        literals.push_back(varNum(n, i, range[k]+1));
      }

      clauses.push_back(literals);

      vector<int> set;
      for (int i=0; i<literals.size(); i++) {
        set.push_back(i);
      }
      // cout << "set size: " << set.size() << endl;
      vector< vector<int> > subsets = getAllSubsets(set, 2);
      // cout << "subset size: " << subsets.size() << endl;
      for (int j=0; j<subsets.size(); j++){
        vector<int> temp2;
        for (int z=0; z<subsets[j].size(); z++){
          temp2.push_back(-1*literals[subsets[j][z]]);
        }
        clauses.push_back(temp2);
      }
    }

    void exactlyOneof2(int n, int i, vector<int> &range) {
      vector<int> literals;

      for (int k=0; k<range.size(); k++){
        literals.push_back(varNum(n, range[k], i));
      }

      clauses.push_back(literals);

      vector<int> set;
      for (int i=0; i<literals.size(); i++) {
        set.push_back(i);
      }
      // cout << "set size: " << set.size() << endl;
      vector< vector<int> > subsets = getAllSubsets(set, 2);
      // cout << "subset size: " << subsets.size() << endl;
      for (int j=0; j<subsets.size(); j++){
        vector<int> temp2;
        for (int z=0; z<subsets[j].size(); z++){
          temp2.push_back(-1*literals[subsets[j][z]]);
        }
        clauses.push_back(temp2);
      }
    }

    void adj(int n, int i, int j, int to, int from) {
      // for (int k=1; k<4; k++) {
        // vector<int> temp;
        // cout << -1*varNum(n, i, j) << endl;
        // temp.push_back(-1*varNum(n, i, j));

        // cout << varNum(n, to, j+1) << endl;
        // temp.push_back(varNum(n, to, j+1));

        // cout << varNum(n, from, j+1) << endl;
        // temp.push_back(varNum(n, from, j+1));
        clauses.push_back({-1*varNum(n, i, j), varNum(n, to, j+1), varNum(n, from, j+1)});
      // }
    }

    void printEquisatisfiableSatFormula() {
      for (int i=0; i<clauses.size(); i++){
        for (int j=0; j<clauses[i].size(); j++) {
          cout << clauses[i][j] << " ";
        }
        cout << "0";
        cout << "\n";
      }
    }
};

int varNum(int n, int i, int j) {
    return (n*i + j);
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    vector<vector<int> > adj(n);

    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
        adj[converter.edges[i].to-1].push_back(converter.edges[i].from-1);
        adj[converter.edges[i].from-1].push_back(converter.edges[i].to-1);
    }
    // vector<int> positions;
    // for (int i=1; i<n+1; i++) {
    //   positions.push_back(i);
    // }
    vector<int> vertices;
    for (int i=0; i<n; i++) {
      vertices.push_back(i);
      // positions.push_back(i+1);
    }

    // allocations for number of vertices and positions OK
    for (int j=0; j<n; j++) {
      converter.exactlyOneof1(n, j, vertices);
      converter.exactlyOneof2(n, vertices[j]+1, vertices);

    }

    for (int j=0; j<vertices.size()-1; j++) {
      for (int i=0; i<adj.size(); i++) {
        vector<int> temp;
        // cout << -1*varNum(n, i, j) << endl;
        temp.push_back(-1*varNum(n, i, vertices[j]+1));

        for (int y=0; y<adj[i].size(); y++) {
          // converter.adj(n, i, j, converter.edges[i].to, converter.edges[i].from);

          // cout << varNum(n, adj[i][y], j+1) << endl;
          temp.push_back(varNum(n, adj[i][y], vertices[j]+2));

          // cout << varNum(n, from, j+1) << endl;
          // temp.push_back(varNum(n, from, j+1));
        }
        converter.clauses.push_back(temp);

        // converter.adj(n, converter.edges[i].from, j);
      }
    }

    cout << converter.clauses.size() << " " << n*n << endl;
    converter.printEquisatisfiableSatFormula();

    return 0;
}
