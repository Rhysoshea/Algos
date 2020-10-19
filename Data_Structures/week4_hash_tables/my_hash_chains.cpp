#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    // vector<string> elems;
    vector<vector <string> > elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i){
          hash = (hash * multiplier + s[i]) % prime;
        }
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        // cout << "elems " << elems.size() << "\n";
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        cout << (was_found ? "yes\n" : "no\n");
    }

    bool findQuery(vector<string> L, string s) {
      vector<string>::iterator it = std::find(L.begin(), L.end(), s);
      return it != L.end();
    }

    void processQuery(const Query& query) {
        elems.resize(bucket_count);

        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            vector<string> L = elems[query.ind];
            if (L.empty() != true) {
              for (int i=L.size()-1; i>=0; --i){
                cout << L[i] << " ";
              }
            }
              cout << "\n";

        } else {
            // cout << "hash " << hash_func(query.s) << "\n";
            vector<string> L = elems[hash_func(query.s)];
            // cout << "size L: " << L.size() << "\n";
            if (query.type == "find") {
              writeSearchResult(findQuery(L, query.s));

            }

            else if (query.type == "add") {
                if (findQuery(L, query.s) == false) {
                  elems[hash_func(query.s)].push_back(query.s);
                }
            }

            else if (query.type == "del") {
                for (int i=0; i < L.size(); ++i){
                  // cout << "L[i]: " << L[i] << "\n";
                  if (L[i] == query.s){
                    // cout << "query.s: " << query.s << "\n";
                    elems[hash_func(query.s)].erase(elems[hash_func(query.s)].begin()+i);
                  }
                }
            }
        }
    }

    // void processQuery(const Query& query) {
    //     if (query.type == "check") {
    //         // use reverse order, because we append strings to the end
    //         for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
    //             if (hash_func(elems[i]) == query.ind)
    //                 cout << elems[i] << " ";
    //         cout << "\n";
    //     } else {
    //         vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
    //         if (query.type == "find")
    //             writeSearchResult(it != elems.end());
    //         else if (query.type == "add") {
    //             if (it == elems.end())
    //                 elems.push_back(query.s);
    //         } else if (query.type == "del") {
    //             if (it != elems.end())
    //                 elems.erase(it);
    //         }
    //     }
    // }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
