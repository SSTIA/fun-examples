# -*- coding: utf-8 -*-

START = "START"
PLACE = "PLACE"
DONE = "DONE"
TURN = "TURN"
BEGIN = "BEGIN"
END = "END"

BOARD_SIZE = 15
EMPTY = 0
ME = 1
OTHER = 2

class AI:
    boardSize = BOARD_SIZE;
    # TODO: add your own attributes here if you need any


    # Constructor
    def __init__(self):
        self.board = []
        for i in range(0,BOARD_SIZE):
            self.board.append([])
            for j in range(0,BOARD_SIZE):
                self.board[i].append(EMPTY)
        # TODO: add your own contructing procedure here if necessary

    def init(self):
        # TODO: add your own initilization here if you need any
        1 == 1

    def begin(self):
        # TODO: write your own opening here
        # NOTE: this method is only called when it's your turn to begin (先手)
        # RETURN: two integer represent the axis of target position
        # The following one is a very naive sample which always put chess at the first empty slot.
        for i in range(0,BOARD_SIZE):
            for j in range(0,BOARD_SIZE):
                if self.board[i][j] == EMPTY:
                    return i, j

    def turn(self):
        # TODO: write your in-turn operation here
        # NOTE: this method is called when it's your turn to put chess
        # RETURN: two integer represent the axis of target position
        # The following one is a very naive sample which always put chess at the first empty slot.
        for i in range(0,BOARD_SIZE):
            for j in range(0,BOARD_SIZE):
                if self.board[i][j] == EMPTY:
                    return i, j

    @classmethod
    # NOTE: don't change this function
    def display(self):
        for i in range(0,BOARD_SIZE):
            print(self.board[i])

def loop(AI):
    # NOTE: don't change this function
    while True:
        buffer = input()
        buffersplitted = buffer.split(' ');
        if len(buffersplitted) == 0:
            continue
        command = buffersplitted[0]
        if command == START:
            AI.init();
        elif command == PLACE:
            x = int(buffersplitted[1])
            y = int(buffersplitted[2])
            v = int(buffersplitted[3])
            AI.board[x][y] = v
        elif command == DONE:
            print("OK")
        elif command == BEGIN:
            x, y = AI.begin()
            AI.board[x][y] = ME
            print(str(x)+" "+str(y))
        elif command == TURN:
            x = int(buffersplitted[1])
            y = int(buffersplitted[2])
            AI.board[x][y] = OTHER
            x, y = AI.turn()
            AI.board[x][y] = ME
            print(str(x)+" "+str(y))
        elif command == "print":
           AI.display()
        elif command == END:
            break

if __name__ == "__main__":
    # NOTE: don't change main function
    ai = AI()
    loop(ai)
