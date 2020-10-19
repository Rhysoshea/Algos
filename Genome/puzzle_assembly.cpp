#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using std::cin;
using std::cout;

// Reconstruct a square puzzle with square puzzle pieces, where the colours of each edge must match the neighbors.

const int INPUT_SIZE = 25;
// const int ROW = sqrt(INPUT_SIZE);
struct puzzlePiece {
    std::string up,left,down,right;
    int id;


};

bool operator<(const puzzlePiece &lhs, const puzzlePiece &rhs) { return lhs.id < rhs.id; }


struct Jigsaw {
    puzzlePiece left_up, right_up, left_down, right_down;
    std::vector<puzzlePiece> left_border, right_border, up_border, down_border, middle_section;

    // int puzzle_size(){
    //   return left_border.size()*up_border.size();
    // }
    const std::string black = "black";


    void insert_piece(puzzlePiece piece) {
      // set the corner pieces
      if (piece.up == black && piece.left == black)
        left_up = std::move(piece);
      else if (piece.up == black && piece.right == black)
        right_up = std::move(piece);
      else if (piece.down == black && piece.left == black)
        left_down = std::move(piece);
      else if (piece.down == black && piece.right == black)
        right_down = std::move(piece);
      // set the edge pieces to a possible location
      else if (piece.left == black)
        left_border.emplace_back(std::move(piece));
      else if (piece.up == black)
        up_border.emplace_back(std::move(piece));
      else if (piece.right == black)
        right_border.emplace_back(std::move(piece));
      else if (piece.down == black)
        down_border.emplace_back(std::move(piece));
      // anything that is not an edge piece goes into the middle section
      else
        middle_section.emplace_back(std::move(piece));
    }

    void read_data() {
      int id = 0;
      // std::string up, left, down, right, tmp;
      // while(getline(std::cin, up, ','))
      //     {
      //         up = up.substr(1);
      //         getline(std::cin, left, ',');
      //         getline(std::cin, down, ',');
      //         getline(std::cin, right, ')');
      //         right = right.substr(0, right.size());
      //         getline(std::cin, tmp, '\n');
      //         insert_piece(puzzlePiece{std::move(up), std::move(left), std::move(down), std::move(right), id++});
      //     }

      for (int i=0; i<INPUT_SIZE; i++) {
        std::string str;
        cin>>str;
        str.erase(0,1); str.pop_back();
        std::stringstream stream(str);
        puzzlePiece piece;

        getline(stream,piece.up,',');
        getline(stream,piece.left,',');
        getline(stream,piece.down,',');
        getline(stream,piece.right,')');
        // cout << piece.up << " " << piece.left << " " << piece.down << " " << piece.right << std::endl;
        piece.id = id;
        insert_piece(piece);
        id++;

      }
    }

    void print_puzzle() {
      // print top row
      cout << "(" << left_up.up << "," << left_up.left << "," << left_up.down << "," << left_up.right << ");";
      for (int i=0; i<up_border.size(); i++){
        cout << "(" << up_border[i].up << "," << up_border[i].left << "," << up_border[i].down << "," << up_border[i].right << ");";
      }
      cout << "(" << right_up.up << "," << right_up.left << "," << right_up.down << "," << right_up.right << ")" << std::endl;

      // print middle rows
      for (int i=0; i<up_border.size(); i++) {
        cout << "(" << left_border[i].up << "," << left_border[i].left << "," << left_border[i].down << "," << left_border[i].right << ");";
        for (int j=0; j<up_border.size(); j++) {
            cout << "(" << middle_section[i*up_border.size() + j].up << "," << middle_section[i*up_border.size() + j].left << "," << middle_section[i*up_border.size() + j].down << "," << middle_section[i*up_border.size() + j].right << ");";
          }
        cout << "(" << right_border[i].up << "," << right_border[i].left << "," << right_border[i].down << "," << right_border[i].right << ")" << std::endl;
      }

      // print bottom row
      cout << "(" << left_down.up << "," << left_down.left << "," << left_down.down << "," << left_down.right << ");";
      for (int i=0; i<down_border.size(); i++){
        cout << "(" << down_border[i].up << "," << down_border[i].left << "," << down_border[i].down << "," << down_border[i].right << ");";
      }
      cout << "(" << right_down.up << "," << right_down.left << "," << right_down.down << "," << right_down.right << ")" << std::endl;
    }

    bool check_puzzle() {
      // top side
      for (int i=0; i<up_border.size(); i++) {
        if (middle_section[i].up != up_border[i].down)
          return false;
      }
      // left side
      for (int i=0; i<left_border.size(); i++) {
        if (middle_section[i*left_border.size()].left != left_border[i].right)
          return false;
      }
      // right side
      for (int i=0; i<right_border.size(); i++) {
        if (middle_section[i*right_border.size()+(right_border.size()-1)].right != right_border[i].left)
          return false;
      }
      // bottom side
      for (int i=1; i<=down_border.size(); i++) {
        if (middle_section[middle_section.size()-i].down != down_border[down_border.size()-i].up)
          return false;
      }
      return true;
    }

    void solve_puzzle() {
      // check both corners and the 2nd and 3rd positions in the row
      // this checks all 5 pieces in the row
      // next_permutation reorders the vector to its next lexographically greater order
      // top row
      while(left_up.right != up_border[0].left || up_border[0].right != up_border[1].left || up_border.back().right != right_up.left ) {
          std::next_permutation(up_border.begin(), up_border.end());
        }
      // bottom row
      while(left_down.right != down_border[0].left || down_border[0].right != down_border[1].left || down_border.back().right != right_down.left )
          std::next_permutation(down_border.begin(), down_border.end());
      // left side
      while(left_up.down != left_border[0].up || left_border[0].down != left_border[1].up || left_border.back().down != left_down.up )
          std::next_permutation(left_border.begin(), left_border.end());
      // right side
      while(right_up.down != right_border[0].up || right_border[0].down != right_border[1].up || right_border.back().down != right_down.up )
          std::next_permutation(right_border.begin(), right_border.end());
      // middle section
      while (not check_puzzle()) {
        std::next_permutation(middle_section.begin(), middle_section.end());
      }
    }
};


int main() {

  std::ios::sync_with_stdio(false); // disables C and C++ synchronization
  std::cin.tie(NULL); // unties cin and cout

  // input format (up,left,down,right)

  Jigsaw puzzle;
  puzzle.read_data();
  puzzle.solve_puzzle();
  // cout << "here\n";

  puzzle.print_puzzle();

  return 0;
}
