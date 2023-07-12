/*
    Othello.c
    8*8のオセロゲーム
    奇数ターンは白のターン,偶数ターンは黒のターン
    石を置きたい場所にマウスをクリックすると石を置くことができる
    g2354017  Ryo Nakagawa
*/

#include <handy.h>
#include <math.h>
#include <stdio.h>

#define WINDOW_MAIN_SIZE 800      // オセロウィンドウのサイズ
#define WINDOW_START_SIZE 400     // スタート画面のサイズ
#define X_WINDOW_RESULT_SIZE 800  // リザルト画面のXサイズ
#define Y_WINDOW_RESULT_SIZE 600  // リザルト画面のYサイズ

#define CELL_SIZE 100  // 1マスのサイズ

void update();  // update関数の宣言(配列とウィンドウを同期させる関数)

void Othello_Algorithm(
    int,
    int);  // Othello_Algorithm関数の宣言(オセロのアルゴリズムを実装する関数)

void CAN_PUT(int, int,
             int);  // CAN_PUT関数の宣言(石を置けるかどうかを判定する関数)

void Result(int, double,
            double);  // Result関数の宣言(リザルト画面を作成する関数)

int board[10][10] =
    {};  // 8*8のマス目(白を1,黒を2,0は何も置かれていない,3は石を置くことができることを表す)(配列外を読み込むことを防ぐため,外枠は-1とする)

int main() {
    int x, y;                              // クリックされた座標
    int Wid_ID;                            // ウィンドウのID
    int White_color = 2, Black_color = 2;  // 石の数
    int Turn = 1;  // 奇数は白のターン,偶数は黒のターン

    int i, j, k, l, m, n, o, p, q, r, s;  // カウンタ変数

    hgevent *event;  // イベントに関する変数

    /**********配列の外枠の初期化**********/
    for (o = 0; o < 10; o++) {
        board[0][o] = -1;
        board[o][0] = -1;
        board[9][o] = -1;
        board[o][9] = -1;
    }
    /**********ここまで**********/

    /**********どんなスクリーンでもウィンドウがスクリーンの真ん中に表示されるようにする**********/
    double X_WINDOW_COORDINATE_MAX;  // スクリーンの幅
    double Y_WINDOW_COORDINATE_MAX;  // スクリーンの高さ

    HgScreenSize(
        &X_WINDOW_COORDINATE_MAX,
        &Y_WINDOW_COORDINATE_MAX);  // スクリーンの幅と高さを調べ、その値をそれぞれ格納する。

    double X_WINDOW_COORDINATE = (X_WINDOW_COORDINATE_MAX - WINDOW_MAIN_SIZE) /
                                 2;  // オセロウィンドウの左下のx座標
    double Y_WINDOW_COORDINATE = (Y_WINDOW_COORDINATE_MAX - WINDOW_MAIN_SIZE) /
                                 2;  // オセロウィンドウの左下のy座標

    double X_WINDOW_START_COORDINATE =
        (X_WINDOW_COORDINATE_MAX - WINDOW_START_SIZE) /
        2;  // スタート画面の左下のx座標
    double Y_WINDOW_START_COORDINATE =
        (Y_WINDOW_COORDINATE_MAX - WINDOW_START_SIZE) /
        2;  // スタート画面の左下のy座標

    double X_WINDOW_RESULT_COORDINATE =
        (X_WINDOW_COORDINATE_MAX - X_WINDOW_RESULT_SIZE) /
        2;  // リザルト画面の左下のx座標
    double Y_WINDOW_RESULT_COORDINATE =
        (Y_WINDOW_COORDINATE_MAX - Y_WINDOW_RESULT_SIZE) /
        2;  // リザルト画面の左下のy座標

    /**********ここまで**********/

    /**********標準ウィンドウを作成**********/

    HgWOpen(X_WINDOW_COORDINATE, Y_WINDOW_COORDINATE, WINDOW_MAIN_SIZE,
            WINDOW_MAIN_SIZE);  // ウィンドウを作成

    HgSetTitle("Othello");  // ウィンドウのタイトルをOthelloにする

    /**********ここまで**********/

    /**********石の数を表示するウィンドウを作成**********/
    HgWOpen(X_WINDOW_COORDINATE_MAX - X_WINDOW_COORDINATE,
            Y_WINDOW_COORDINATE_MAX - Y_WINDOW_COORDINATE - (CELL_SIZE * 2),
            CELL_SIZE * 2.7, CELL_SIZE * 2);

    HgWSetTitle(1, "Score");  // ウィンドウのタイトルをScoreにする

    HgWSetFont(1, HG_HB, 50);  // フォントを設定

    int Wid1_Layer1 = HgWAddLayer(1);  // ウィンドウにレイヤを追加

    HgWText(1, 0, 100, "White:");  // ScoreにWhite:を表示
    HgWText(Wid1_Layer1, 200, 100, "%d", White_color);  // Scoreにスコアを表示

    HgWText(1, 0, 0, "Black:");                       // ScoreにBlack:を表示
    HgWText(Wid1_Layer1, 200, 0, "%d", Black_color);  // Scoreにスコアを表示

    /**********ここまで**********/

    /**********Skipボタンのウィンドウを追加**********/
    HgWOpen(X_WINDOW_COORDINATE_MAX - X_WINDOW_COORDINATE, Y_WINDOW_COORDINATE,
            CELL_SIZE * 2.7, CELL_SIZE * 2);

    HgWSetTitle(2, "Skip");  // ウィンドウのタイトルをSkipにする

    HgWSetFont(2, HG_HB, CELL_SIZE);  // フォントを設定

    HgWText(2, 20, 50, "Skip");  // SkipにSkipを表示

    /**********ここまで**********/

    /**********ターンを表示させるウィンドウを追加**********/
    HgWOpen(X_WINDOW_COORDINATE - (CELL_SIZE * 2.7),
            Y_WINDOW_COORDINATE_MAX - Y_WINDOW_COORDINATE - (CELL_SIZE * 2),
            CELL_SIZE * 2.7, CELL_SIZE * 2);

    HgWSetTitle(3, "Turn");  // ウィンドウのタイトルをTurnにする

    int Wid3_Layer1 = HgWAddLayer(3);  // ウィンドウにレイヤを追加

    HgWSetFont(3, HG_HB, 50);            // フォントを設定
    HgWSetFont(Wid3_Layer1, HG_HB, 50);  // フォントを設定

    /**********ここまで**********/

    HgSetEventMask(
        HG_MOUSE_DOWN);  // 標準ウィンドウのマウスクリックを検出するように設定

    HgWSetEventMask(
        2,
        HG_MOUSE_DOWN);  // ウィンドウIDが2のウィンドウのマウスクリックを検出するように設定

    /**********8*8のマス目を描写**********/
    for (i = 1; i < 8; i++) {
        HgLine(CELL_SIZE * i, 0, CELL_SIZE * i, WINDOW_MAIN_SIZE);
        HgLine(0, CELL_SIZE * i, WINDOW_MAIN_SIZE, CELL_SIZE * i);
    }
    /**********ここまで**********/

    /**********盤面中央の4マスに黒石と白石を2つずつ置く**********/
    board[4][4] = 1;

    board[5][5] = 1;

    board[4][5] = 2;

    board[5][4] = 2;

    update();  // 配列とウィンドウを同期させる

    /**********ここまで**********/

    /**********オセロゲームに関する繰り返し**********/
    for (j = 1;; j++) {
        /**********ターンを表示**********/
        HgLClear(Wid3_Layer1);  // レイヤーを消去

        Turn = j;  // ターンをカウント

        HgWText(Wid3_Layer1, 0, 70, "Turn:");  // TurnにTurnを表示

        HgWText(Wid3_Layer1, 200, 70, "%d", Turn);  // Turnにターンを表示

        /**********ここまで**********/

        /**********石を置けるかどうかの判定**********/
        for (k = 1; k <= 8; k++) {
            for (l = 1; l <= 8; l++) {
                CAN_PUT(Turn, l, k);
            }
        }

        update();  // 配列とウィンドウを同期させる
        /**********ここまで**********/

        /**********デバック用**********/

        /*
        for (p = 1; p < 9; p++)
        {
            for (q = 1; q < 9; q++)
            {
                printf("%d", board[p][q]); // デバック用
            }
            printf("\n");
        }
        printf("\n");
        */

        /**********ここまで**********/

        event = HgEvent();  // マウスクリックを待つ。
        x = event->x;       // クリックされたx座標を取り出す
        y = event->y;       // クリックされたy座標を取り出す
        Wid_ID = event->wid;  // クリックされたウィンドウのIDを取り出す

        /*
        printf("clicked (%d, %d)\n", x, y); // デバック用
        */

        int xCell =
            -1;  // クリックされたマスの番号を格納する変数(なぜ-1で初期化しているかわからない)
        int yCell =
            -1;  // クリックされたマスの番号を格納する変数(なぜ-1で初期化しているかわからない)

        if (Wid_ID == 0)  // クリックされたウィンドウが標準ウィンドウなら
        {
            xCell = (x / CELL_SIZE) + 1;  // クリックされたマスの番号を計算
            yCell = (y / CELL_SIZE) + 1;  // クリックされたマスの番号を計算
        }

        /*
        printf("xCell: %d\n", xCell); // デバック用
        printf("yCell: %d\n", yCell); // デバック用
        */

        /**********描写に関する条件**********/
        if (Wid_ID == 0)  // クリックされたウィンドウが標準ウィンドウなら
        {
            if (j % 2 == 1)  // 奇数回なら
            {
                if (board[xCell][yCell] == 0)  // 置けるマスなら
                {
                    board[xCell][yCell] = 1;  // 白
                } else                        // 描写されていたら
                {
                    j--;
                }
            } else  // 偶数回なら
            {
                if (board[xCell][yCell] == 0)  // 置けるマスなら
                {
                    board[xCell][yCell] = 2;  // 黒
                } else                        // 描写されていたら
                {
                    j--;
                }
            }
        } else if (Wid_ID == 2)  // クリックされたウィンドウがSkipなら
        {
            // ターンをスキップ
        }

        update();  // 配列とウィンドウを同期させる

        /**********ここまで**********/

        /**********石を裏返す判定**********/
        Othello_Algorithm(xCell, yCell);  // ここで裏返す
        update();  // 配列とウィンドウを同期させる
        /**********ここまで**********/

        /**********石を数えてScoreに表示する**********/
        White_color = 0;  // リセット
        Black_color = 0;  // リセット

        for (m = 1; m < 9; m++) {
            for (n = 1; n < 9; n++) {
                switch (board[m][n]) {
                    case 1:  // 白だったら
                        White_color++;
                        break;
                    case 2:  // 黒だったら
                        Black_color++;
                        break;
                    default:
                        break;
                }
            }
        }

        /*
        printf("White: %d\n", White_color); // デバック用
        printf("Black: %d\n", Black_color); // デバック用
        */

        HgLClear(Wid1_Layer1);  // レイヤをクリア

        HgWText(Wid1_Layer1, 200, 100, "%d",
                White_color);  // Scoreにスコアを表示
        HgWText(Wid1_Layer1, 200, 0, "%d", Black_color);  // Scoreにスコアを表示

        /**********ここまで**********/

        /**********勝利判定**********/

        /*
        printf("turn: %d\n" , j); //デバック用
        */

        int stone_num;  // 石の数を数える変数

        for (r = 1; r < 9; r++) {
            for (s = 1; s < 9; s++) {
                if (board[r][s] == 1)  // 白の石なら
                {
                    stone_num++;
                } else if (board[r][s] == 2)  // 黒の石なら
                {
                    stone_num++;
                }
            }
        }

        /*
        printf("stone_num: %d\n", stone_num); // デバック用
        */

        if (stone_num == 64 || White_color == 0 ||
            Black_color ==
                0)  // 石の数が64個になったらまたはどちらかの石が0個になったら
        {
            if (White_color > Black_color)  // 白の勝ちならば
            {
                Result(1, X_WINDOW_RESULT_COORDINATE,
                       Y_WINDOW_RESULT_COORDINATE);
                printf("White WIN\n");
            } else if (Black_color > White_color)  // 黒の勝ちならば
            {
                Result(2, X_WINDOW_RESULT_COORDINATE,
                       Y_WINDOW_RESULT_COORDINATE);
                printf("Black WIN\n");
                break;
            } else  // 引き分けならば
            {
                printf("No WINNER\n");
                break;
            }
        }
        stone_num = 0;  // リセット

        /**********ここまで**********/
    }
    /**********ここまで**********/

    HgGetChar();
    HgClose();

    return 0;
}

/**********update関数**********/
void update() {
    int i, j;  // カウンタ変数

    int xCenter, yCenter;  // 描写する円の中心座標

    int x, y;  // 描写する正方形の左下隅の座標

    for (i = 1; i < 9; i++) {
        for (j = 1; j < 9; j++) {
            if (board[i][j] == 1)  // 白だったら
            {
                xCenter = CELL_SIZE / 2 +
                          (CELL_SIZE * (i - 1));  // セルの中心座標を計算
                yCenter = CELL_SIZE / 2 +
                          (CELL_SIZE * (j - 1));  // セルの中心座標を計算

                x = CELL_SIZE * (i - 1);  // セルの左下隅の座標を計算
                y = CELL_SIZE * (j - 1);  // セルの左下隅の座標を計算

                HgSetFillColor(HG_WHITE);
                HgBoxFill(x, y, CELL_SIZE, CELL_SIZE, 1);  // 白の正方形を描く

                HgSetFillColor(HG_WHITE);
                HgCircleFill(xCenter, yCenter, CELL_SIZE / 3, 1);  // 白を置く
            } else if (board[i][j] == 2)  // 黒だったら
            {
                xCenter = CELL_SIZE / 2 +
                          (CELL_SIZE * (i - 1));  // セルの中心座標を計算
                yCenter = CELL_SIZE / 2 +
                          (CELL_SIZE * (j - 1));  // セルの中心座標を計算

                x = CELL_SIZE * (i - 1);  // セルの左下隅の座標を計算
                y = CELL_SIZE * (j - 1);  // セルの左下隅の座標を計算

                HgSetFillColor(HG_WHITE);
                HgBoxFill(x, y, CELL_SIZE, CELL_SIZE, 1);  // 白の正方形を描く

                HgSetFillColor(HG_BLACK);
                HgCircleFill(xCenter, yCenter, CELL_SIZE / 3, 1);  // 黒を置く
            } else if (board[i][j] == 3)  // 石を置くことができるマスならば
            {
                x = CELL_SIZE * (i - 1);  // セルの左下隅の座標を計算
                y = CELL_SIZE * (j - 1);  // セルの左下隅の座標を計算

                HgSetFillColor(HG_GREEN);
                HgBoxFill(x, y, CELL_SIZE, CELL_SIZE, 1);  // 緑の正方形を描く
            } else if (board[i][j] == 0)  // 石を置くことができないマスならば
            {
                x = CELL_SIZE * (i - 1);  // セルの左下隅の座標を計算
                y = CELL_SIZE * (j - 1);  // セルの左下隅の座標を計算

                HgSetFillColor(HG_WHITE);
                HgBoxFill(x, y, CELL_SIZE, CELL_SIZE, 1);  // 白の正方形を描く
            }
                }
    }
}
/**********ここまで**********/

/**********Othello_Algorithm関数**********/
void Othello_Algorithm(int x, int y) {
    int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, z;  // カウンタ変数

    int color;  // 白or黒の判定用(白を1,黒を2とする)

    /**********挟まれていたら裏返す**********/
    for (color = 1; color <= 2; color++) {
        if (board[x][y] == color)  // 白or黒だったら
        {
            /***********右向きの判定***********/
            for (i = 1; i < 9; i++) {
                if (board[x + i][y] == color)  // 右が白or黒だったら
                {
                    for (j = 0; j <= i; j++) {
                        board[x + j][y] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x + i][y] == 0)  // 右が空白だったら
                {
                    break;
                } else if (board[x + i][y] == -1)  // 右が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********上向きの判定***********/
            for (k = 1; k < 9; k++) {
                if (board[x][y + k] == color)  // 上が白or黒だったら
                {
                    for (l = 0; l <= k; l++) {
                        board[x][y + l] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x][y + k] == 0)  // 上が空白だったら
                {
                    break;
                } else if (board[x][y + k] == -1)  // 上が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********左向きの判定***********/
            for (m = 1; m < 9; m++) {
                if (board[x - m][y] == color)  // 左が白or黒だったら
                {
                    for (n = 0; n <= m; n++) {
                        board[x - n][y] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x - m][y] == 0)  // 左が空白だったら
                {
                    break;
                } else if (board[x - m][y] == -1)  // 左が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********下向きの判定***********/
            for (o = 1; o < 9; o++) {
                if (board[x][y - o] == color)  // 下が白or黒だったら
                {
                    for (p = 0; p <= o; p++) {
                        board[x][y - p] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x][y - o] == 0)  // 下が空白だったら
                {
                    break;
                } else if (board[x][y - o] == -1)  // 下が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********右上向きの判定***********/
            for (q = 1; q < 9; q++) {
                if (board[x + q][y + q] == color)  // 右上が白or黒だったら
                {
                    for (r = 0; r <= q; r++) {
                        board[x + r][y + r] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x + q][y + q] == 0)  // 右上が空白だったら
                {
                    break;
                } else if (board[x + q][y + q] == -1)  // 右上が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********左上向きの判定***********/
            for (s = 1; s < 9; s++) {
                if (board[x - s][y + s] == color)  // 左上が白or黒だったら
                {
                    for (t = 0; t <= s; t++) {
                        board[x - t][y + t] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x - s][y + s] == 0)  // 左上が空白だったら
                {
                    break;
                } else if (board[x - s][y + s] == -1)  // 左上が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********左下向きの判定***********/
            for (u = 1; u < 9; u++) {
                if (board[x - u][y - u] == color)  // 左下が白or黒だったら
                {
                    for (v = 0; v <= u; v++) {
                        board[x - v][y - v] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x - u][y - u] == 0)  // 左下が空白だったら
                {
                    break;
                } else if (board[x - u][y - u] == -1)  // 左下が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********右下向きの判定***********/
            for (w = 1; w < 9; w++) {
                if (board[x + w][y - w] == color)  // 右下が白or黒だったら
                {
                    for (z = 0; z <= w; z++) {
                        board[x + z][y - z] = color;  // 間を全て白or黒にする
                        update();  // 配列とウィンドウを同期させる
                        HgSleep(0.1);  // 0.1秒待つ
                    }
                    break;
                } else if (board[x + w][y - w] == 0)  // 右下が空白だったら
                {
                    break;
                } else if (board[x + w][y - w] == -1)  // 右下が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/
        }
    }
    /**********ここまで**********/
}
/**********ここまで**********/

/**********CAN_PUT関数**********/
void CAN_PUT(int turn, int x, int y) {
#define WHITE 1  // 白の石
#define BLACK 0  // 黒の石

    int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, z;  // for文用

    int color = turn % 2;  // 石の色を表す変数(1:白,0:黒)

    /*
printf("color = %d\n", color); // デバッグ用
*/

    if (color == WHITE)  // 白のターンなら
    {
        if (board[x + 1][y] == BLACK)  // 隣が黒ならば
        {
            /**********右方向の判定**********/
            for (i = 2; i < 8; i++) {
                if (board[x + i][y] == WHITE)  // 白ならば
                {
                    if (board[x - 1][y] == 0)  // 左が空白ならば
                    {
                        board[x - 1][y] = 3;  // 左に置けることを示す
                    }
                }
                if (board[x + i][y] == 0)  // 空白ならば
                {
                    break;
                }
                if (board[x + i][y] == -1)  // 壁ならば
                {
                    break;
                }
            }
            /**********ここまで**********/

            /**********左方向の判定**********/
            for (j = 2; j < 8; j++) {
                if (board[x - j][y] == WHITE)  // 白ならば
                {
                    if (board[x + 1][y] == 0)  // 右が空白ならば
                    {
                        board[x + 1][y] = 3;  // 右に置けることを示す
                    }
                }
                if (board[x - j][y] == 0)  // 空白ならば
                {
                    break;
                }
                if (board[x - j][y] == -1)  // 壁ならば
                {
                    break;
                }
            }
            /**********ここまで**********/
        }
    } else if (color == BLACK)  // 黒のターンなら
    {
    }
}

/**********ここまで**********/

/**********Result関数**********/
void Result(int result, double Wid_x, double Wid_y) {
#define R 50  // にこちゃんマークの半径

    HgWOpen(Wid_x, Wid_y, X_WINDOW_RESULT_SIZE,
            Y_WINDOW_RESULT_SIZE);  // ウィンドウを開く

    double txt_wid, txt_hei;  // 画面の幅と高さ

    int x, y = 300;  // にこちゃんマークの座標

    int i;  // for文用

    if (result == 1) {                // 白の勝ちならば
        HgWSetTitle(4, "WHITE WIN");  // ウィンドウのタイトルを設定

        HgWSetFont(4, HG_HB, 100);  // フォントを設定

        HgWTextSize(4, &txt_wid, &txt_hei,
                    "WHITE WIN");  // テキストの幅と高さを取得

        /*
                printf("wid:%lf, hei:%lf\n", txt_wid, txt_hei);  //
           デバッグ用
        */

        HgWText(4, 400 - txt_wid / 2, (300 - txt_hei / 2) + 200,
                "WHITE WIN");  // テキストを表示

        HgWSetFillColor(4, HG_BLACK);  //  塗りつぶす色を設定

        for (i = 0; i < 5; i++) {  // にこちゃんマークを表示
            x = 80 + 160 * i;

            HgWCircle(4, x, y, R);

            HgWCircleFill(4, x - 20, y + 20, 5, 1);  // 左目
            HgWCircleFill(4, x + 20, y + 20, 5, 1);  // 右目

            HgWArc(4, x, y, 30, M_PI * (7 / 6), M_PI * (-1 / 6));  // 口
        }

        HgGetChar();
        HgClose();
    } else if (result == 2) {         // 黒の勝ちならば
        HgWSetTitle(4, "BLACK WIN");  // ウィンドウのタイトルを設定

        HgWSetFont(4, HG_HB, 100);  // フォントを設定

        HgWSetColor(4, HG_WHITE);  // 線の色を設定

        HgWTextSize(4, &txt_wid, &txt_hei,
                    "BLACK WIN");  // テキストの幅と高さを取得

        /*
                printf("wid:%lf, hei:%lf\n", txt_wid, txt_hei);  //
           デバッグ用
        */

        HgWSetFillColor(4, HG_BLACK);  // 塗りつぶす色を設定

        HgWBoxFill(4, 0, 0, 800, 600, 0);  // 背景を黒にする

        HgWText(4, 400 - txt_wid / 2, (300 - txt_hei / 2) + 200,
                "BLACK WIN");  // テキストを表示

        HgWSetFillColor(4, HG_WHITE);  // 塗りつぶす色を設定

        for (i = 0; i < 5; i++) {
            x = 80 + 160 * i;

            HgWCircle(4, x, y, R);

            HgWCircleFill(4, x - 20, y + 20, 5, 1);  // 左目
            HgWCircleFill(4, x + 20, y + 20, 5, 1);  // 右目

            HgWArc(4, x, y, 30, M_PI * (7 / 6), M_PI * (-1 / 6));  // 口
        }

        HgGetChar();
        HgClose();
    }
}
/**********ここまで**********/