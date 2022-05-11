#include <stdio.h>

// プロトタイプ宣言
void  gameInit();
void boardInit();
void boardPrint();
void inputPutPos();
void changeTurn();
bool checkOutPos(int x, int y);
bool checkAdjacent(int x, int y);

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

    boardInit();
    boardPrint();
    inputPutPos();
    inputPutPos();

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
    if(turnNum == 0) {
    printf("●の番ですが、一手目は中央に置きます。\n");
        x = FIRST_POS_X;
        y = FIRST_POS_Y;
    } else {
        printf("●(or ○)の番です。どこに置きますか？　(行番号　列番号) \n>");
        while(1) {
            scanf("%d%d", &y,&x);
            y--;
            x--;
            if (checkOutPos(x, y) == 0 || board[y][x] != eSTONE_SPACE) {
                printf("不正な入力です。\n>");
            } else if(checkAdjacent(x,y)) {
                break;
            } else {
                printf("隣接する駒がありません。\n>");
            }
        }
        board[y][x] = turn;
    }
}

void changeTurn() {
    if(turn == eSTONE_BLACK) {
        turn = eSTONE_WHITE;
    } else {
        turn = eSTONE_BLACK;
    }
}

bool checkOutPos(int x, int y) {
    if (BOARD_SIZE > x >= 0 && BOARD_SIZE > y >= 0) {
        return;
    }
}

bool checkAdjacent(int x, int y) {

}
