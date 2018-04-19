const readline = require('readline');

const BOARD_SIZE = 15;
const EMPTY = 0;
const ME = 1;
const OTHER = 2;
const START = "START";
const PLACE = "PLACE";
const DONE = "DONE";
const TURN = "TURN";
const BEGIN = "BEGIN";
const END = "END";

let board = new Array(BOARD_SIZE);

function start() {
    for (let i = 0; i < BOARD_SIZE; i++) {
        board[i] = new Array(BOARD_SIZE);
        for (let j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
    aiInit();
}

function aiInit() {

}

function aiBegin(me) {
    for (let i = 0; i < BOARD_SIZE; i++) {
        for (let j = 0; j < BOARD_SIZE; j++) {
            if (EMPTY === board[i][j]) {
                return [i, j];
            }
        }
    }
    return [0, 0];
}

function aiTurn(me, x, y) {
    for (let i = 0; i < BOARD_SIZE; i++) {
        for (let j = 0; j < BOARD_SIZE; j++) {
            if (EMPTY === board[i][j]) {
                return [i, j];
            }
        }
    }
    return [0, 0];
}

readline.createInterface({
    input: process.stdin,
}).on('line', (line) => {
    const args = line.split(' ');
    const command = args[0];
    if (command === START) {
        start();
    } else if (command === PLACE) {
        board[args[1]][args[2]] = args[3];
    } else if (command === DONE) {
        console.log("OK");
    } else if (command === BEGIN) {
        const [x, y] = aiBegin(ME);
        board[x][y] = ME;
        console.log(x, y);
    } else if (command === TURN) {
        board[args[1]][args[2]] = OTHER;
        const [x, y] = aiTurn(ME, args[1], args[2]);
        board[x][y] = ME;
        console.log(x, y);
    } else if (command === END) {
        process.exit(0);
    }

}).on('close', () => {
    process.exit(0);
});
