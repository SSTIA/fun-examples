#include <utility>
#include <iostream>
#include <sstream>
#include <vector>

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
};

ostream &operator<<(ostream &out, const Position &pos) {
    out << pos.x << " " << pos.y;
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
    /*
     * TODO: Write your own ai here!
     * Here is a simple AI which just put chess at empty position!
     * 代做：在这里写下你的AI。
     * 这里有一个示例AI，它只会寻找第一个可下的位置进行落子。
     */
    int i, j;
    Position preferedPos = {0, 0};

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (EMPTY == board[i][j]) {
                preferedPos.x = i;
                preferedPos.y = j;
                return preferedPos;
            }
        }
    }

    return preferedPos;
}

Position AI::turn(const Position &other) {
    /*
     * TODO: Write your own ai here!
     * Here is a simple AI which just put chess at empty position!
     * 代做：在这里写下你的AI。
     * 这里有一个示例AI，它只会寻找第一个可下的位置进行落子。
     */
    int i, j;
    Position preferedPos = {0, 0};

    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (EMPTY == board[i][j]) {
                preferedPos.x = i;
                preferedPos.y = j;
                return preferedPos;
            }
        }
    }

    return preferedPos;
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
