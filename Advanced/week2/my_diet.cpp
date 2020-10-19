#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

typedef vector<vector<double>> matrix;

const double EPS = 1e-6;
const int PRECISION = 20;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation ReadEquation(int n, int m, matrix A, vector<double> B) {
    int size = n+m+1;
    Matrix a(size, std::vector <double> (m, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < m; ++column)
            a[row][column] = A[row][column];
        b[row] = B[row];
    }
    for (int row = n; row < n+m; ++row) {
        for (int column = 0; column < m; ++column) {
          if (column == row - n) {
            a[row][column] = -1;
          } else {
            a[row][column] = 0;
          }
        }
        b[row] = 0;
    }
    for (int column = 0; column < m; ++column) {
      a[n+m][column] = 1;
    }
    b[n+m] = 1000000000;
    return Equation(a, b);
}

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element) {
    // simulates swapping 2 rows around, needs to do this in all data structures of continuity
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void MySwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element, int i, int j) {
    // simulates swapping 2 rows around, needs to do this in all data structures of continuity
    std::swap(a[i], a[j]);
    std::swap(b[i], b[j]);
    std::swap(used_rows[i], used_rows[j]);
    // pivot_element.row = pivot_element.column;
}

void PrintMatrix(Matrix &a, Column &b) {
    int size = a.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row) {
      for (int col = 0; col < a[row].size(); ++col){
        std::cout << a[row][col] << " ";
      }
      std::cout << b[row];
      std::cout << "\n";
    }
}

Position SelectPivotElement(
  Matrix &a, Column &b,
  std::vector <bool> &used_rows,
  std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    // You'll need to improve it to pass the problem.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row]){
      ++pivot_element.row;
    }
    while (used_columns[pivot_element.column]){
      ++pivot_element.column;
    }
    if (a[pivot_element.row][pivot_element.column] == 0) {
      int i = pivot_element.row;
      int j = i;
      while (a[j][pivot_element.column] == 0) {
        j++;
        if (j>=b.size()){
          pivot_element.row = -1;
          pivot_element.column = -1;
          return pivot_element;
        }
      }
      MySwapLines(a, b, used_rows, pivot_element, i, j);
    }
    // PrintMatrix(a, b);
    // cout << "pivot: " << pivot_element.row << " " << pivot_element.column << "\n";
    return pivot_element;

    // goes through each row then each column to find which element to find next
}

// Position SelectPivotElement(
//   Matrix &a, Column &b,
//   std::vector <bool> &used_rows,
//   std::vector <bool> &used_columns) {
//     // This algorithm selects the first free element.
//     // You'll need to improve it to pass the problem.
//     Position pivot_element(0, 0);
//     while (used_rows[pivot_element.row]){
//       ++pivot_element.row;
//     }
//     while (used_columns[pivot_element.column]){
//       ++pivot_element.column;
//     }
//     while (a[pivot_element.row][pivot_element.column] == 0 || used_rows[pivot_element.row]) {
//       ++pivot_element.row;
//       if (pivot_element.row > a.size()-1){
//         pivot_element.row = -1;
//         pivot_element.column = -1;
//         return pivot_element;
//       }
//     }
//       // MySwapLines(a, b, used_rows, pivot_element, i, j);
//     // }
//     // PrintMatrix(a, b);
//     // cout << "pivot: " << pivot_element.row << " " << pivot_element.column << "\n";
//     return pivot_element;
//
//     // goes through each row then each column to find which element to find next
// }


void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // rescale to make pivot 1
    double factor = a[pivot_element.row][pivot_element.column];
    for (int j=0; j<a[pivot_element.row].size(); j++){
      a[pivot_element.row][j] = a[pivot_element.row][j]/factor;
      // a[pivot_element.row][j] = 1;
    }
    a[pivot_element.row][pivot_element.column] = 1;

    b[pivot_element.row] = b[pivot_element.row]/factor;

    for (int i = 0; i < a.size(); i++) {
      //factor between pivot and corresponding value in each row
      if (i!=pivot_element.row){
        double f = a[i][pivot_element.column]/a[pivot_element.row][pivot_element.column];
        // subtract row from others to make other entries in column 0
        for (int j=0; j<a[i].size(); j++){
          if (j==pivot_element.column){
            a[i][j] = 0;
          } else {
            a[i][j] -= a[pivot_element.row][j]*f;
          }
        }
        // std::cout.precision(PRECISION);

        // cout << "b: " << b[i] << "\n";
        // if (b[i] != 1000000000 || b[i] != -1000000000){
        if (b[i] < 1000000000 && b[i] > -1000000000){
          b[i] -= b[pivot_element.column]*f;
        }
      }
    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

int SolveEquation(Equation& equation, int n, int m) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();
    // PrintMatrix(a, b);
    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        // select left most non-zero in non-pivot row
        Position pivot_element = SelectPivotElement(a, b, used_rows, used_columns);
        // PrintMatrix(a, b);

        // cout << "Size: " << size << "\n";
        if (pivot_element.row == -1 && pivot_element.column == -1){
          return 0;
        }
        SwapLines(a, b, used_rows, pivot_element);
        // cout << "swapped\n";
        ProcessPivotElement(a, b, pivot_element);
        // cout << "processed\n";

        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
        // cout << "marked\n";

    }

    // PrintMatrix(a, b);

    return 1;
}

vector< vector<int> > getAllSubsets(vector<int> set)
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
    return subset;
}

double dotProduct(vector<double> c, vector<double> s)
{

    double product = 0;

    // Loop for calculate cot product
    for (int i = 0; i < c.size(); i++){
      // cout << "dot product : "<< c[i] << " " << s[i] << "\n";
      // if (s[i] == 1000000000){
      //   product += 1000000000;
      // } else if (s[i] == -1000000000){
      //   product -= 1000000000;
      // }
      // else {
        product += c[i] * s[i];
      // }
    }

    return product;
}

pair<int, vector<double>> solve_diet_problem(
    int n,
    int m,
    matrix A,
    vector<double> b,
    vector<double> c) {

  // Write your code here
  // add additional inequalities to matrix
  Equation equation = ReadEquation(n, m, A, b);
  pair<int, vector<double>> solutions;
  vector< vector<double> > possibleSolutions;

  // split equation into subsets of size m
  vector<int> set;
  for (int i=0; i<equation.a.size(); i++) {
    set.push_back(i);
  }

  vector< vector<int> > subsets = getAllSubsets(set);
  vector< vector<int> > subsetsToUse;
  for (int i=0; i<subsets.size(); i++) {
    if (subsets[i].size() == m){
      subsetsToUse.push_back(subsets[i]);
    }
  }
  // cout << "\n";
  // for (int i=0; i<subsetsToUse.size(); i++) {
  //   for (int j=0; j<subsetsToUse[i].size(); j++) {
  //     cout << subsetsToUse[i][j] << " ";
  //   }
  //   cout << "\n";
  // }
  // cout << "\n";

  for (int i=0; i<subsetsToUse.size(); i++) {
    Matrix A;
    Column B;
    for (int j=0; j<subsetsToUse[i].size(); j++){
      A.push_back(equation.a[subsetsToUse[i][j]]);
      B.push_back(equation.b[subsetsToUse[i][j]]);
    }
    Equation newEquation(A, B);
    // cout << "---------\n";
    //
    // PrintMatrix(A, B);
    // cout << "---------\n";
    // solve each equation
    int sol = SolveEquation(newEquation, n, m);
    // cout << "sol: " << sol << "\n";
    if (sol == 0) {
      continue;
      // break;
    }
    bool solution = true;
    for (int i=0; i<equation.a.size(); i++){
      // double sum;
      // for (int j=0; j<equation.a[i].size(); j++){
      double sum = dotProduct(equation.a[i], newEquation.b);
      for (int i=0; i<newEquation.b.size(); i++){
        cout << newEquation.b[i] << " ";
      }
      cout << "sum : " << sum << " R: " << equation.b[i] << "\n";
      if (sum > 1000000000){
        sum = 1000000000;
      }
      if (sum > equation.b[i]+EPS){
        solution = false;
      }
    }
    if (solution) {
      possibleSolutions.push_back(newEquation.b);
    }
  }
  // solve each equation
  // Column solution = SolveEquation(equation, n, m);
  // cout << "size: " << possibleSolutions.size() << "\n";
  if (possibleSolutions.size() == 0){
    solutions.first = -1;
    return solutions;
  }
  double max = -1000000000;
  int index;
  for (int i=0; i<possibleSolutions.size(); i++){
    double dot = dotProduct(c, possibleSolutions[i]);
    if (dot > max) {
      max = dot;
      index = i;
    }
    cout << "size: " << possibleSolutions[i].size() << "\n";

    for (int j=0; j<possibleSolutions[i].size(); j++) {
      cout << possibleSolutions[i][j] << " ";
    }
    cout << "\n";
    cout << "dot: " << dot << "\n";
    cout << "\n";
  }
  // cout << "index: " << index << "\n";
  // cout << possibleSolutions[index].size();
  for (int i=0; i<possibleSolutions[index].size(); i++){
    // cout << possibleSolutions[index][i] << "\n";
    solutions.second.push_back(possibleSolutions[index][i]);
    if (possibleSolutions[index][i] > 10000000){
      solutions.first = 1;
    }
  }

  return solutions;
}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1:
      printf("No solution\n");
      break;
    case 0:
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;
  }
  return 0;
}
