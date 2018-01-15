#include <utility>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define BOARD_SIZE 15
#define EMPTY 0
#define ME 1
#define OTHER 2

#define START "START"
#define PLACE "PLACE"
#define DONE  "DONE"
#define TURN  "TURN"
#define BEGIN "BEGIN"
#define END   "END"

struct Position {
    int x;
    int y;

    Position operator+(const Position &that) const {
        return {x + that.x, y + that.y};
    }

    Position operator-() const {
        return {-x, -y};
    }

    Position &operator+=(const Position &that) {
        x += that.x;
        y += that.y;
        return *this;
    }

    bool operator==(const Position &that) const {
        return x == that.x && y == that.y;
    }

    bool isValid() {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }
};

ostream &operator<<(ostream &out, const Position &pos) {
    return out << pos.x << " " << pos.y;
}

class AI {
private:
    /*
     * You can define your own struct and variable here
     * 你可以在这里定义你自己的结构体和变量
     */
    size_t boardSize;
    const vector<vector<int> > &board;
public:
    explicit AI(const vector<vector<int> > &board);

    void init();

    Position begin();

    Position turn(const Position &other);

    pair<int, int> simple(Position pos, const Position &dir);

    Position naive();
};

AI::AI(const vector<vector<int> > &board) : board(board) {
    this->boardSize = board.size();
}

class REPL {
private:
    vector<vector<int> > board;
    AI ai;
public:
    REPL();

    ~REPL() = default;

    void loop();
};

REPL::REPL() : ai(board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.emplace_back(move(vector<int>(BOARD_SIZE, 0)));
    }
}

void REPL::loop() {
    while (true) {
        string buffer;
        getline(cin, buffer);
        istringstream ss(buffer);

        string command;
        ss >> command;
        if (command == START) {
            ai.init();
        } else if (command == PLACE) {
            int x, y, z;
            ss >> x >> y >> z;
            board[x][y] = z;
        } else if (command == DONE) {
            cout << "OK" << endl;
        } else if (command == BEGIN) {
            Position pos = ai.begin();
            board[pos.x][pos.y] = ME;
            cout << pos << endl;
        } else if (command == TURN) {
            int x, y;
            ss >> x >> y;
            board[x][y] = OTHER;
            Position pos = ai.turn({x, y});
            board[pos.x][pos.y] = ME;
            cout << pos << endl;
        } else if (command == END) {
            break;
        }
    }
}

/*
 * YOUR CODE BEGIN
 * 你的代码开始
 */

/*
 * You should init your AI here
 * 在这里初始化你的AI
 */
void AI::init() {

}


/*
 * Game Start, you will put the first chess.
 * Warning: This method will only be called when after the initialize of the map,
 * it is your turn to put the chess, or this method will not be called.
 * You should return a valid Position variable.
 * 棋局开始，首先由你来落子
 * 请注意：只有在当棋局初始化后，轮到你落子时才会触发这个函数。如果在棋局初始化完毕后，轮到对手落子，则这个函数不会被触发。详见项目要求。
 * 你需要返回一个结构体Position，在x属性和y属性填上你想要落子的位置。
 */
Position AI::begin() {
    return naive();
}

Position AI::turn(const Position &other) {
    return naive();
}

pair<int, int> AI::simple(Position pos, const Position &dir) {
    int max = 0, current = 0;
    bool flag = true, continous = true;
    while (flag) {
        pos += dir;
        if (!pos.isValid()) break;
        switch (board[pos.x][pos.y]) {
            case OTHER:
                flag = false;
                break;
            case ME:
                max++;
                if(continous) current++;
                break;
            case EMPTY:
                max++;
                continous = false;
                break;
            default:
                abort();
        }
    }
    return {max, current};
}

Position AI::naive() {
    /**
     * This function will find a point which have largest chance to get five
     * There are five directions for each point, 225 points in total
     * Though there are many cleverer algorithms than calculating every point,
     * this simple method won't exceeds time limit in about k*4*15^4 operations
     */
    const vector<Position> DIRS = {{1, 0},   // below / above
                                   {0, 1},   // right / left
                                   {1, 1},   // below right / above left
                                   {1, -1}}; // below left / above right
    vector<pair<int, int>> data(BOARD_SIZE * BOARD_SIZE);
    const auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    };

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                for (int k = 0; k < DIRS.size(); k++) {
                    // search from positive / negative direction
                    Position pos = {i, j};
                    auto positive = simple(pos, DIRS[k]);
                    auto negative = simple(pos, -DIRS[k]);
                    auto max = 1 + positive.first + negative.first;
                    auto current = positive.second + negative.second;
                    if (max >= 5) {
                        auto index = i * BOARD_SIZE + j;
                        data[index] = std::max(data[index], {max, current}, cmp);
                    }
                }
            }
        }
    }
    auto maxDataIt = std::max_element(data.begin(), data.end(), cmp);
    auto index = (int) std::distance(data.begin(), maxDataIt);
    return {index / BOARD_SIZE, index % BOARD_SIZE};
}

/*
 * YOUR CODE END
 * 你的代码结束 
 */

int main(int argc, char *argv[]) {
    REPL repl;
    repl.loop();
    return 0;
}
