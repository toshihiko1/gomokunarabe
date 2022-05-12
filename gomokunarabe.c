#include <stdio.h>

// プロトタイプ宣言
void  gameInit();
void boardInit();
void boardPrint();
void inputPutPos();
void changeTurn();
int checkOutPos(int copX, int copY);
int checkAdjacent(int adX, int adY);
int lenCheck(int lenX, int lenY);
int gameEndProcess();

// 変数定義
int board[9][9];
int turn = 0;
int turnNum = 0;

// 定数定義
const int BOARD_SIZE = 9;
const int FIRST_POS_X = 4;
const int FIRST_POS_Y = 4;


// 列挙型定義
enum STONE_KIND
{
    eSTONE_SPACE,
    eSTONE_BLACK,
    eSTONE_WHITE
};

/****メイン****/

int main(void) {

    printf("五目並べ\n");
    gameInit();
    boardInit();
    boardPrint();
    while(1) {
        turnNum++;
        inputPutPos();
        changeTurn();
        boardPrint();
        if(gameEndProcess() == 1) {
            break;
        }
    }


    return 0;
}

/****メソッド****/

void gameInit() {
    turn = eSTONE_BLACK;
    turnNum = 0;
}

void boardInit() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            board[i][j] = eSTONE_SPACE;
        }
    }
}

void boardPrint() {
    printf("\t");
    for(int i = 1; i <= BOARD_SIZE; i++) {
        printf("%d\t", i);
    }
    printf("\n\n");

    for(int i = 1; i <= BOARD_SIZE; i++) {
        printf("%d\t", i);
        for(int j = 0;j < BOARD_SIZE; j++) {
            if(board[i - 1][j] == eSTONE_SPACE) {
                printf("・\t");
            } else if (board[i - 1][j] == eSTONE_BLACK) {
                printf("●\t");
            } else {
                printf("○\t");
            }
        }
        printf("\n\n");
    }
}

void inputPutPos() {
    int x = 0;
    int y = 0;

    if(turnNum == 1) {
    printf("●の番ですが、一手目は中央に置きます。\n");
    x = FIRST_POS_X;
    y = FIRST_POS_Y;

    }
    else if (turnNum >= 2) {
        printf("●(or ○)の番です。どこに置きますか？　(行番号　列番号) \n>");
        while(1) {
            scanf("%d%d", &x,&y);
            x--;
            y--;
            if (checkOutPos(x, y) == 0 || board[x][y] != eSTONE_SPACE) {
                printf("不正な入力です。\n>");
            } else if(checkAdjacent(x,y) == 1) {
                break;
            } else {
                printf("隣接する駒がありません。\n>");
            }
        }
    }
    board[x][y] = turn;
}

void changeTurn() {
    if(turn == eSTONE_BLACK) {
        turn = eSTONE_WHITE;
    } else {
        turn = eSTONE_BLACK;
    }
}

int checkOutPos(int copX, int copY)
{
    if (BOARD_SIZE > copX && copX >= 0 && BOARD_SIZE > copY && copY >= 0) {
        return 1;
    } else {
        return 0;
    }
}

int checkAdjacent(int adX, int adY) {
    int x = adX;
    int y = adY;
    int targetPos[8][2] = {
       //x   y
        {-1, -1},
        {0, -1},
        {1, -1},
        {-1, 0},
        {1, 0},
        {-1, 1},
        {0, 1},
        {1, 1}
    };

    for(int i = 0; i < 8; i++) {
        x = adX + targetPos[i][0];
        y = adY + targetPos[i][1];
        if(checkOutPos(x,y) == 1) {
            if (board[x][y] != eSTONE_SPACE) {
                return 1;
            }
        }
    }
    return 0;
}

int lenCheck(int lenX, int lenY) {
    int x = lenX;
    int y = lenY;
    int judge;

    int chkPos[4][2] = {
       //x  y
        {0, 1},
        {1, 0},
        {1, 1},
        {-1, 1}
    };

    for (int i = 0; i < 4; i++) {
        judge = 1;
        for(int j = 0; j < 4; j++) {
            x = x + chkPos[i][0];
            y = y + chkPos[i][1];
            if (checkOutPos(x, y) == 1) {
                if (board[lenX][lenY] != board[x][y]) {
                    judge = 0;
                    break;
                }
            } else {
                judge = 0;
                break;
            }

        }
        if(judge == 1) {
            break;
        }
    }
    return judge;
}

int gameEndProcess() {
    int judge = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != eSTONE_SPACE) {
                if(lenCheck(i, j) == 1) {
                    if (board[i][j] == eSTONE_BLACK) {
                        printf("●の勝ちです");
                    } else if (board[i][j] == eSTONE_WHITE) {
                        printf("○の勝ちです");
                    }
                    judge = 1;
                    break;
                }
            }
        }
        if(judge == 1) {
            break;
        }
    }
    return judge;
}
