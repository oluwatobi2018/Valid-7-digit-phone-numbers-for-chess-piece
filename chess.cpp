nes (202 sloc)  7.23 KB

//============================================================================
// Name        : Chess.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Base class to generate all possible paths in a given board
class Piece{
    public:
       virtual vector<vector<int>> buildPath(vector<vector<char> > &board) = 0;
       virtual ~Piece() {}
       bool isNumber(const char& c){
           return c>='0' && c<='9';
       }
};

/* Derived Knight method from Piece class. When it moves, it can move to a square that is two squares horizontally
 * and one square vertically, or two squares vertically and one square horizontally. The complete move therefore looks
 * like the letter L. It can jump over non number characters.
 */
class Knight : public Piece{

    public:
       vector<vector<int>> buildPath(vector<vector<char> > &board){
           vector<vector<int> > paths(10, vector<int>());
           int row = board.size();
           int col = board[0].size();

           vector<pair<int,int> > pos = {{2,1}, {1,2}, {2,-1}, {1, -2}};
           int xpos = 0;
           int ypos = 0;
           for(int i=0; i<row; ++i)
               for(int j=0; j<col; ++j){
                   char c = board[i][j];
                   if (isNumber(c)){
                       for(pair<int,int>& p:pos){
                           xpos = i+p.first;
                           ypos = j+p.second;
                           if ( xpos<row && ypos>=0 && ypos<col && isNumber(board[xpos][ypos]) ){
                               paths[c-'0'].push_back(board[xpos][ypos]-'0');
                               paths[board[xpos][ypos]-'0'].push_back(c-'0');
                           }
                       }
                   }
           }

           return paths;
       }
};

/* Derived Bishop method from Piece class. Bishop has no restrictions in distance for each move, but is limited to
 * diagonal movement. Bishops, like all other pieces except the knight, cannot jump over other pieces.
 */
class Bishop : public Piece{

         void subcombine(vector<int>& nums, vector<vector<int> > &res, vector<int> &array, int level){
              if (array.size()==2){
                  res.push_back(array);
                  return;
              }

              for(int i=level; i<nums.size(); i++){
                  array.push_back(nums[i]);
                  subcombine(nums, res, array, i+1);
                  array.pop_back();
              }
         }

        // All possible ways to choose only two items from input array nums where second item is behind the first
        vector<vector<int> > permutation(vector<int>& nums){
            vector<vector<int> > res;
            if (nums.size()<2)
            	return res;

            vector<int> array;
            subcombine(nums, res, array, 0);

            return res;
        }

        // Build path from start to end with direction ( true with row false with column ) and sign (true for increase and false for decrease)
        void partBuild(vector<vector<char> > &board, vector<vector<int> > &paths, int start, int end, bool sign, bool direction){
        	 int row = board.size();
        	 int col = board[0].size();

        	 int xpos = 0;
        	 int ypos = 0;
        	 for(int i=start; (direction? i< end:i>end ); (direction? ++i:--i) ){
        	    vector<int> varray;
        	    xpos = direction ? (sign ? i:0) : (sign ? i:0);
        	    ypos = direction ? (sign ? 0:i) : (sign ? col-1:i);
        	    while(xpos>=0 && xpos<row && ypos>=0 && ypos<col){
        	          if ( isNumber(board[xpos][ypos]) )
        	             varray.push_back(board[xpos][ypos]-'0');
        	          xpos++;
        	          if (direction)
        	        	  ypos++;
        	          else
        	        	  ypos--;
                }

        	    vector<vector<int> > allperm = permutation(varray);
        	    for(int k=0; k<allperm.size(); ++k){
        	          paths[allperm[k][0]].push_back(allperm[k][1]);
        	          paths[allperm[k][1]].push_back(allperm[k][0]);
        	    }
        	}
        }

    public:
        vector<vector<int>> buildPath(vector<vector<char> > &board){
           vector<vector<int> > paths(10, vector<int>());
           int row = board.size();
           int col = board[0].size();
           int xpos = 0;
           int ypos = 0;

           partBuild(board, paths, 0, row-1, true, true);
           partBuild(board, paths, 1, col-1, false, true);
           partBuild(board, paths, col-1, 0, false, false);
           partBuild(board, paths, row-2, 0, true, false);

           return paths;
        }
};

// Factory pattern close modification to call API buildPath()
class ChessFactory{
    public:
       Piece* createInstance(const string& s){
           if ( s=="knight")
               return new Knight;
           else
               return new Bishop;
       }
};

// Generate Phone board with given phone board, the start digits, the move mode (Knight or Bishop) and total length of phone number.
// getValidNum() will return the number of valid phone numbers.
class PhoneBook{
    private:
       string piecetype;
       int tel_len;
       vector<int> start_digits;
       vector<vector<char> > board;
       vector<vector<int> > path;

       int subCount(int digit, int length){
           if (length==1)
               return 1;

           int count = 0;
           for(int& d: path[digit]){
               count += subCount(d, length-1);
           }

           return count;
       }
    public:
       PhoneBook(string s, int t, vector<int> sd, vector<vector<char>> b){
           piecetype = s;
           tel_len = t;
           start_digits = sd;
           board = b;
       }
       int getValidNum(){
           ChessFactory *cf = new ChessFactory;
           Piece* piece = cf->createInstance(piecetype);

           path = piece->buildPath(board);

           int count = 0;
           for(int &d:start_digits){
               count += subCount(d, tel_len);
           }

           delete cf;
           delete piece;
           return count;
       }

};

bool checkPieceType(string& s){
    return s=="knight" || s=="bishop";
}

int main() {
/* Enter your code here. Read input from STDIN. Print output to STDOUT */

    string piecetype = "";
    int tel_len = 0;
    vector<int> start_digits;
    int row = 0;
    int col = 0;

    cin >> piecetype;
    if (!checkPieceType(piecetype)){
        cout << "Only knight and bishop are allowed." << endl;
        return -1;
    }

    cin >> tel_len;
    cin.ignore(256, '\n');

    int num = 0;
    string line;
    getline(cin, line);
    istringstream iss(line);
    while ( iss >> num ){
        start_digits.push_back(num);
    }

    cin >> row;
    cin >> col;
    vector< vector<char> > board(row, vector<char>(col,'0'));
    for(int i=0; i<row; ++i)
       for(int j=0; j<col; ++j){
           char c;
           cin >> c;
           board[i][j] = c;
    }

    PhoneBook *pb = new PhoneBook(piecetype, tel_len, start_digits, board);
    int count = pb->getValidNum();
    cout << count << endl;
    delete pb;

    return 0;
}
