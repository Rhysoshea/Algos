#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

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

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
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
      }
      MySwapLines(a, b, used_rows, pivot_element, i, j);
    }
    // PrintMatrix(a, b);

    return pivot_element;

    // goes through each row then each column to find which element to find next
}


void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
    // Write your code here
    // cout << "pivot: " << pivot_element.row << " " << pivot_element.column << "\n";

    // rescale to make pivot 1
    double factor = a[pivot_element.row][pivot_element.column];
    for (int j=0; j<a[pivot_element.row].size(); j++){
      a[pivot_element.row][j] = a[pivot_element.row][j]/factor;
    }
    b[pivot_element.row] = b[pivot_element.row]/factor;

    for (int i = 0; i < a.size(); i++) {
      //factor between pivot and corresponding value in each row
      if (i!=pivot_element.row){

        double f = a[i][pivot_element.column]/a[pivot_element.row][pivot_element.column];

        // scale row by factor f

        // cout << "f: " << f << "\n";
        // subtract row from others to make other entries in column 0
        for (int j=0; j<a[i].size(); j++){

          a[i][j] -= a[pivot_element.row][j]*f;
        }
        b[i] -= b[pivot_element.column]*f;
      }
    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        // select left most non-zero in non-pivot row
        Position pivot_element = SelectPivotElement(a, b, used_rows, used_columns);
        // cout << pivot_element.row << " " << pivot_element.column << "\n";
        // for (int i=0; i<used_columns.size(); i++){
        //   cout << used_columns[i] << " ";
        // }
        // cout << "\n";
        // for (int i=0; i<used_rows.size(); i++){
        //   cout << used_rows[i] << " ";
        // }
        // cout << "\n";
        // swap row to top of non-pivot rows
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
        // PrintMatrix(a, b);

    }

    return b;
}

void PrintColumn(const Column &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << std::endl;
}

int main() {
    Equation equation = ReadEquation();
    Column solution = SolveEquation(equation);
    PrintColumn(solution);
    return 0;
}
