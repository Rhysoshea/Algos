#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

int varNum(int vertex, int color) {
    return (3*(vertex-1) + color);
}

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;
    vector<vector<int> > clauses;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    int varNum(int vertex, int color) {
        return (3*(vertex-1) + color);
    }

    vector< vector<int> > getAllSubsets(vector<int> set, int size)
    {
        vector< vector<int> > subset;
        vector<int> empty;
        subset.push_back( empty );

        for (int i = 0; i < set.size(); i++)
        {
            vector< vector<int> > subsetTemp = subset;

            for (int j = 0; j < subsetTemp.size(); j++)
                subsetTemp[j].push_back( set[i] );

            for (int j = 0; j < subsetTemp.size(); j++)
                subset.push_back( subsetTemp[j] );
        }

        vector< vector<int>> subsetsToUse;
        for (int i=0; i<subset.size(); i++) {
          if (subset[i].size() == size){
            subsetsToUse.push_back(subset[i]);
          }
        }
        return subsetsToUse;
    }

    void exactlyOneof(int i) {
      vector<int> literals;

      for (int k=1; k<4; k++){
        literals.push_back(varNum(i, k));
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

    void adj(int to, int from) {
      for (int k=1; k<4; k++) {
        vector<int> temp;
        temp.push_back(-1*varNum(to, k));
        temp.push_back(-1*varNum(from, k));
        clauses.push_back(temp);
      }
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

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }
    int numVertices = n;
    vector<int> colors{1,2,3};

    for (int j=1; j<numVertices+1; j++) {
      converter.exactlyOneof(j);
    }

    for (int i=0; i<converter.edges.size(); i++) {
      converter.adj(converter.edges[i].to, converter.edges[i].from);
    }

    cout << converter.clauses.size() << " " << n*3 << endl;
    converter.printEquisatisfiableSatFormula();

    return 0;
}
