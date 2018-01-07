#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 15
#define EMPTY 0
#define ME 1
#define OTHER 2

#define TRUE 1
#define FALSE 0

#define MAX_BYTE 10000

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

char buffer[MAX_BYTE] = {0};
int board[BOARD_SIZE][BOARD_SIZE] = {0};

void debug(const char *str) {
    printf("DEBUG %s\n", str);
    fflush(stdout);
}

/*
 * YOUR CODE BEGIN
 * 你的代码开始 
 */

/* 
 * You can define your own struct and variable here
 * 你可以在这里定义你自己的结构体和变量
 */


/*
 * You should init your AI here
 * 在这里初始化你的AI
 */
void initAI() {

}

/*
 * Game Start, you will put the first chess.
 * Warning: This method will only be called when after the initialize ofi the  map, it is your turn to put the chess. 
 * Or this method will not be called.
 * You should return a valid Position variable.
 * 棋局开始，首先由你来落子
 * 请注意：只有在当棋局初始化后，轮到你落子时才会触发这个函数。如果在棋局初始化完毕后，轮到对手落子，则这个函数不会被触发。详见项目要求。
 * 在这里，me的取值只可能是ME(1)，即board(棋盘)上为ME(1)的位置表示你的棋子，board(棋盘)上为OTHER(2)的位置表示对手的棋子。
 * 你需要返回一个结构体Position，在x属性和y属性填上你想要落子的位置。 
 */
struct Position aiBegin(const char board[BOARD_SIZE][BOARD_SIZE], int me) {
    /*
     * TODO: Write your own ai here!
     * Here is a simple AI which just put chess at empty position!
     * 代做：在这里写下你的AI。 
     * 这里有一个示例AI，它只会寻找第一个可下的位置进行落子。 
     */
    int i, j;
    struct Position preferedPos = {0, 0};

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
 * Game ongoing, the competitor put the chess at the position (otherX, otherY). You should put your chess.
 * You should return a valid Position variable.
 * 棋局进行中，对方上一步落子在(otherX, otherY)的位置，轮到你落子了。
 * 在这里，me的取值只可能是ME(1)，即board(棋盘)上为ME(1)的位置表示你的棋子，board(棋盘)上为OTHER(2)的位置表示对手的棋子。
 * 你需要返回一个结构体Position，在x属性和y属性填上你想要落子的位置。 
 */
struct Position aiTurn(const char board[BOARD_SIZE][BOARD_SIZE], int me, int otherX, int otherY) {
    /*
     * TODO: Write your own ai here!
     * Here is a simple AI which just put chess at empty position!
     * 代做：在这里写下你的AI。 
     * 这里有一个示例AI，它只会寻找第一个可下的位置进行落子。 
     */
    int i, j;
    struct Position preferedPos = {0, 0};

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

void place(int x, int y, int z) {
    board[x][y] = z;
}

void done() {
    printf("OK\n");
    fflush(stdout);
}

void start() {
    memset(board, 0, sizeof(board));
    initAI();
}

void turn(int x, int y) {
    board[x][y] = OTHER;

    // AI
    struct Position pos = aiTurn((const char (*)[BOARD_SIZE]) board, ME, x, y);
    board[pos.x][pos.y] = ME;
    printf("%d %d\n", pos.x, pos.y);
    fflush(stdout);
}

void end(int x) {

}

void loop() {
    while (TRUE) {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, MAX_BYTE, stdin);

        if (strstr(buffer, START)) {
            start();
        } else if (strstr(buffer, PLACE)) {
            char tmp[MAX_BYTE] = {0};
            int x, y, z;
            sscanf(buffer, "%s %d %d %d", tmp, &x, &y, &z);
            place(x, y, z);
        } else if (strstr(buffer, DONE)) {
            done();
        } else if (strstr(buffer, BEGIN)) {
            // AI
            struct Position pos = aiBegin((const char (*)[BOARD_SIZE]) board, ME);
            board[pos.x][pos.y] = ME;
            printf("%d %d\n", pos.x, pos.y);
            fflush(stdout);
        } else if (strstr(buffer, TURN)) {
            char tmp[MAX_BYTE] = {0};
            int x, y;
            sscanf(buffer, "%s %d %d", tmp, &x, &y);
            turn(x, y);
        } else if (strstr(buffer, END)) {
            char tmp[MAX_BYTE] = {0};
            int x;
            sscanf(buffer, "%s %d", tmp, &x);
            end(x);
            break;
        }
    }
}


int main(int argc, char *argv[]) {
    loop();
    return 0;
}
