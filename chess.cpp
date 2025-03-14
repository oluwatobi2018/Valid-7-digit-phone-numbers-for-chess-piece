#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

// Base class to generate all possible paths in a given board
class Piece {
public:
    virtual vector<vector<int>> buildPath(const vector<vector<char>>& board) = 0;
    virtual ~Piece() = default;
    
protected:
    bool isNumber(char c) {
        return c >= '0' && c <= '9';
    }
};

/* Knight moves in an "L" shape */
class Knight : public Piece {
public:
    vector<vector<int>> buildPath(const vector<vector<char>>& board) override {
        vector<vector<int>> paths(10);
        int row = board.size();
        int col = board[0].size();
        vector<pair<int, int>> moves = {{2, 1}, {1, 2}, {2, -1}, {1, -2}};

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (isNumber(board[i][j])) {
                    int currentDigit = board[i][j] - '0';
                    for (auto [dx, dy] : moves) {
                        int x = i + dx, y = j + dy;
                        if (x < row && y >= 0 && y < col && isNumber(board[x][y])) {
                            int nextDigit = board[x][y] - '0';
                            paths[currentDigit].push_back(nextDigit);
                            paths[nextDigit].push_back(currentDigit);
                        }
                    }
                }
            }
        }
        return paths;
    }
};

/* Bishop moves diagonally */
class Bishop : public Piece {
private:
    void addDiagonalPaths(const vector<vector<char>>& board, vector<vector<int>>& paths, int rowDir, int colDir) {
        int row = board.size();
        int col = board[0].size();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (isNumber(board[i][j])) {
                    int currentDigit = board[i][j] - '0';
                    int x = i + rowDir, y = j + colDir;
                    
                    while (x >= 0 && x < row && y >= 0 && y < col) {
                        if (isNumber(board[x][y])) {
                            int nextDigit = board[x][y] - '0';
                            paths[currentDigit].push_back(nextDigit);
                            paths[nextDigit].push_back(currentDigit);
                        }
                        x += rowDir;
                        y += colDir;
                    }
                }
            }
        }
    }

public:
    vector<vector<int>> buildPath(const vector<vector<char>>& board) override {
        vector<vector<int>> paths(10);
        addDiagonalPaths(board, paths, 1, 1);
        addDiagonalPaths(board, paths, 1, -1);
        addDiagonalPaths(board, paths, -1, 1);
        addDiagonalPaths(board, paths, -1, -1);
        return paths;
    }
};

/* Factory class for creating chess pieces */
class ChessFactory {
public:
    static unique_ptr<Piece> createInstance(const string& type) {
        if (type == "knight") return make_unique<Knight>();
        return make_unique<Bishop>();
    }
};

/* Class for computing valid phone numbers based on a chess piece's movement */
class PhoneBook {
private:
    int tel_len;
    vector<int> start_digits;
    vector<vector<char>> board;
    vector<vector<int>> path;
    
    int countValidNumbers(int digit, int length, vector<int>& memo) {
        if (length == 1) return 1;
        if (memo[digit] != -1) return memo[digit];

        int count = 0;
        for (int nextDigit : path[digit]) {
            count += countValidNumbers(nextDigit, length - 1, memo);
        }
        return memo[digit] = count;
    }

public:
    PhoneBook(string pieceType, int length, vector<int> start, vector<vector<char>> boardGrid)
        : tel_len(length), start_digits(move(start)), board(move(boardGrid)) {
        path = ChessFactory::createInstance(pieceType)->buildPath(board);
    }

    int getValidNum() {
        int totalCount = 0;
        vector<int> memo(10, -1);
        for (int digit : start_digits) {
            totalCount += countValidNumbers(digit, tel_len, memo);
        }
        return totalCount;
    }
};

/* Utility function to validate piece type */
bool isValidPieceType(const string& type) {
    return type == "knight" || type == "bishop";
}

int main() {
    string pieceType;
    int tel_len, row, col;

    cin >> pieceType;
    if (!isValidPieceType(pieceType)) {
        cout << "Only knight and bishop are allowed." << endl;
        return -1;
    }

    cin >> tel_len;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> start_digits;
    string line;
    getline(cin, line);
    istringstream iss(line);
    int num;
    while (iss >> num) {
        start_digits.push_back(num);
    }

    cin >> row >> col;
    vector<vector<char>> board(row, vector<char>(col));

    for (auto& rowVec : board) {
        for (char& cell : rowVec) {
            cin >> cell;
        }
    }

    PhoneBook pb(pieceType, tel_len, start_digits, board);
    cout << pb.getValidNum() << endl;

    return 0;
}
