#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using namespace std;

const int MIN_OVERLAP = 12;
const int MAX_ERRORS = 2;
const int INPUT_SIZE = 1618;

class OverlapGraph {
public:
    struct Edge {
        int from, to, weight;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit OverlapGraph(size_t n): graph(n) {}

    // int check_overlap(const std::string & a, const std::string & b) noexcept
    // {
    //     for (int i = 0, n = 1 + a.size()-MIN_OVERLAP; i < n; ++i){
    //       cout << "b.c_str(): " << b.c_str() << " a.c_str()+i: " << a.c_str()+i << " a.size()-i: " << a.size()-i << endl;
    //       if(strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0)
    //           return a.size() - i;
    //     }
    //
    //     return 0;
    // }

    int check_overlap(const std::string & a, const std::string & b) {
      for (int i = 0, n = 1 + a.size()-MIN_OVERLAP; i < n; ++i)  {
        int errors = 0;
        for(int j = 0, s = a.size() - i; j < s && errors <= MAX_ERRORS; ++j)
            if(a[i+j] != b[j]) ++errors;

        if(errors <= MAX_ERRORS) return a.size() - i;
      }
      return 0;
    }


    void construct_overlap(vector<string> &input) {
      for (int i=0; i<graph.size(); i++) {
        for (int j=0; j<graph.size(); j++) {
          if(i != j) {
            int mer = check_overlap(input[i], input[j]);
            cout << "mer: " << mer << endl;
            if (mer > MIN_OVERLAP) {
              Edge connect = {i, j, mer};
              graph[i].push_back(edges.size());
              edges.push_back(connect);

            }
          }
        }
      }
    }

    string build_genome(vector<string> &input){
      int node = 0;
      string start = input[0];
      string genome;
      string current = "";
      genome = start;

      // while (start.compare(current) != 0) {
      while (strncmp(start.c_str(), current.c_str(), start.size()) != 0) {
        int max_weight=0;
        int index=0;
        // cout << "graph[node].size(): " << graph[node].size() << endl;
        for (int i : graph[node]) {
          // cout << "i: " << i << endl;
          if (edges[i].weight > max_weight) {
            // cout << "from: " << input[edges[i].from] << " to: " << input[edges[i].to] << " weight: " << edges[i].weight << endl;
            max_weight = edges[i].weight;
            index = edges[i].to;
          }
        }
        // cout << "index: " << index << " max_weight: " << max_weight << endl;

        node = index;
        current = input[node];
        // cout << "current: " << current << endl;

        // if the read is not the starting read then add to genome
        if (strncmp(start.c_str(), current.c_str(), start.size()) != 0) {
          // cout << "substring: " << current.substr(max_weight, current.size()-max_weight) << endl;
          genome += current.substr(max_weight, current.size()-max_weight);
          // cout << "genome: " << genome << endl;
        }
        if (strncmp(start.c_str(), current.c_str(), start.size()) == 0) {
          genome.erase(genome.end()-max_weight, genome.end());
        }
      };

      return genome;
    }
};

vector<string> read_data(int num_inputs) {
  vector<string> input;
  string read;

  for (int i=0; i<num_inputs; i++){
    cin >> read;
    input.push_back(read);
  }
  return input;
}


void removeDuplicates(vector<string> &input)
{
    // STL function to sort the array of string
    sort(input.begin(), input.end());

    for (int i = 1; i<input.size(); i++)
        if (input[i-1] == input[i])
            input.erase(input.begin()+i);
}


int main() {

  std::ios::sync_with_stdio(false); // disables C and C++ synchronization
  std::cin.tie(NULL); // unties cin and cout

  std::vector<std::string> input;
  input.reserve(INPUT_SIZE); //sets the minimum capacity for the vector
  std::string s;

  // constructs the vector of input with multiple inputs s
  while(std::cin >> s)
      if(input.back() != s) input.emplace_back(std::move(s));

  // input = read_data(INPUT_SIZE);
  removeDuplicates(input);
  OverlapGraph graph(input.size());
  graph.construct_overlap(input);

  string genome = graph.build_genome(input);
  cout << genome << endl;
  return 0;
}
