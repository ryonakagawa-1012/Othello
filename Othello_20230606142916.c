/*
    Othello.c
    8*8のオセロゲーム
    g2354017  Ryo Nakagawa
*/

#include <stdio.h>
#include <handy.h>

#define WINDOW_MAIN_SIZE 800  // オセロウィンドウのサイズ
#define WINDOW_START_SIZE 400 // スタート画面のサイズ

#define CELL_SIZE 100 // 1マスのサイズ

void update(); // update関数の宣言(配列とウィンドウを同期させる関数)

void Othello_Algorithm(int, int); // Othello_Algorithm関数の宣言(オセロのアルゴリズムを実装する関数)



int board[10][10] = {}; // 8*8のマス目(白を1,黒を2,0は何も置かれていない,3は石を置くことができることを表す)(配列外を読み込むことを防ぐため,外枠は-1とする)

int main()
{
    int x, y;                             // クリックされた座標
    int White_color = 2, Black_color = 2; // 石の数

    int i, j, k, l, m, n, o, p; // カウンタ変数

    hgevent *event; // イベントに関する変数

    /**********配列の外枠の初期化**********/
    for (o = 0; o < 10; o++)
    {
        board[0][o] = -1;
        board[o][0] = -1;
        board[9][o] = -1;
        board[o][9] = -1;
    }
    /**********ここまで**********/

    /**********どんなスクリーンでもウィンドウがスクリーンの真ん中に表示されるようにする**********/
    double X_WINDOW_COORDINATE_MAX; // スクリーンの幅
    double Y_WINDOW_COORDINATE_MAX; // スクリーンの高さ

    HgScreenSize(&X_WINDOW_COORDINATE_MAX, &Y_WINDOW_COORDINATE_MAX); // スクリーンの幅と高さを調べ、その値をそれぞれ格納する。

    double X_WINDOW_COORDINATE = (X_WINDOW_COORDINATE_MAX - WINDOW_MAIN_SIZE) / 2; // オセロウィンドウの左下のx座標
    double Y_WINDOW_COORDINATE = (Y_WINDOW_COORDINATE_MAX - WINDOW_MAIN_SIZE) / 2; // オセロウィンドウの左下のy座標

    double X_WINDOW_START_COORDINATE = (X_WINDOW_COORDINATE_MAX - WINDOW_START_SIZE) / 2; // スタート画面の左下のx座標
    double Y_WINDOW_START_COORDINATE = (Y_WINDOW_COORDINATE_MAX - WINDOW_START_SIZE) / 2; // スタート画面の左下のy座標

    /**********ここまで**********/

    /**********スタート画面を作成**********/

    // HgWOpen(X_WINDOW_START_COORDINATE, Y_WINDOW_START_COORDINATE, WINDOW_START_SIZE, WINDOW_START_SIZE);  // スタート画面を作成

    // HgWSetFont(0,HG_GB, 50); // フォントを設定

    // HgWText(0, 0, 0, "Othello"); // スタート画面にOthelloを表示

    // HgWText(0, 0, -100, "Click to start"); // スタート画面にClick to startを表示

    // HgSetEventMask(HG_MOUSE_DOWN); // マウスクリックを検出するように設定

    // HgGetChar(); // 何かキーを押すまで待つ

    // HgLClear(0); // スタート画面を消去

    /**********ここまで**********/

    /**********標準ウィンドウを作成**********/

    HgWOpen(X_WINDOW_COORDINATE, Y_WINDOW_COORDINATE, WINDOW_MAIN_SIZE, WINDOW_MAIN_SIZE);

    HgSetTitle("Othello"); // ウィンドウのタイトルをOthelloにする

    /**********ここまで**********/

    /**********石の数を表示するウィンドウを作成**********/
    HgWOpen(X_WINDOW_COORDINATE_MAX - X_WINDOW_COORDINATE, Y_WINDOW_COORDINATE_MAX - Y_WINDOW_COORDINATE - (CELL_SIZE * 2), CELL_SIZE * 2.7, CELL_SIZE * 2);

    HgWSetTitle(1, "Score"); // ウィンドウのタイトルをScoreにする

    HgWSetFont(1, HG_HB, 50); // フォントを設定

    int Layer1 = HgWAddLayer(1); // ウィンドウにレイヤを追加

    HgWText(1, 0, 100, "White:");                 // ScoreにWhite:を表示
    HgWText(Layer1, 200, 100, "%d", White_color); // Scoreにスコアを表示

    HgWText(1, 0, 0, "Black:");                 // ScoreにBlack:を表示
    HgWText(Layer1, 200, 0, "%d", Black_color); // Scoreにスコアを表示

    /**********ここまで**********/

    HgSetEventMask(HG_MOUSE_DOWN); // マウスクリックを検出するように設定

    /**********8*8のマス目を描写**********/
    for (i = 1; i < 8; i++)
    {
        HgLine(CELL_SIZE * i, 0, CELL_SIZE * i, WINDOW_MAIN_SIZE);
        HgLine(0, CELL_SIZE * i, WINDOW_MAIN_SIZE, CELL_SIZE * i);
    }
    /**********ここまで**********/

    /**********盤面中央の4マスに黒石と白石を2つずつ置く**********/
    board[4][4] = 1;

    board[5][5] = 1;

    board[4][5] = 2;

    board[5][4] = 2;

    update(); // 配列とウィンドウを同期させる

    /**********ここまで**********/

    /**********オセロゲームに関する繰り返し**********/
    for (j = 1;; j++)
    {
        /**********石を置けるかどうかの判定**********/
       
        /**********ここまで**********/

        event = HgEvent(); // マウスクリックを待つ。
        x = event->x;      // クリックされたx座標を取り出す
        y = event->y;      // クリックされたy座標を取り出す

        /*
        printf("clicked (%d, %d)\n", x, y); // 確認のため
        */

        int xCell = (x / CELL_SIZE) + 1; // クリックされたマスの番号を計算
        int yCell = (y / CELL_SIZE) + 1; // クリックされたマスの番号を計算

        /*
        printf("xCell: %d\n", xCell); // 確認のため
        printf("yCell: %d\n", yCell); // 確認のため
        */

        /**********描写に関する条件**********/
        if (j % 2 == 1) // 奇数回なら
        {
            if (board[xCell][yCell] == 0) // 置けるマスなら
            {
                board[xCell][yCell] = 1; // 白
            }
            else // 描写されていたら
            {
                j--;
            }
        }
        else // 偶数回なら
        {
            if (board[xCell][yCell] == 0) // 置けるマスなら
            {
                board[xCell][yCell] = 2; // 黒
            }
            else // 描写されていたら
            {
                j--;
            }
        }

        update(); // 配列とウィンドウを同期させる

        /**********ここまで**********/

        /**********石を裏返す判定**********/
        Othello_Algorithm(xCell, yCell); // ここで裏返す
        update();                        // 配列とウィンドウを同期させる
        /**********ここまで**********/

        /**********石を数えてScoreに表示する**********/
        White_color = 0; // リセット
        Black_color = 0; // リセット

        for (m = 1; m < 9; m++)
        {
            for (n = 1; n < 9; n++)
            {
                switch (board[m][n])
                {
                case 1: // 白だったら
                    White_color++;
                    break;
                case 2: // 黒だったら
                    Black_color++;
                    break;
                default:
                    break;
                }
            }
        }

        /*
        printf("White: %d\n", White_color); // 確認のため
        printf("Black: %d\n", Black_color); // 確認のため
        */

        HgLClear(Layer1); // レイヤをクリア

        HgWText(Layer1, 200, 100, "%d", White_color); // Scoreにスコアを表示
        HgWText(Layer1, 200, 0, "%d", Black_color);   // Scoreにスコアを表示

        /**********ここまで**********/

        /**********勝利判定**********/

        /*
        printf("turn: %d\n" , j); //確認のため
        */

        if (j == 60)
        {
            if (White_color > Black_color)
            {
                printf("White WIN\n");
            }
            else if (Black_color > White_color)
            {
                printf("Black WIN\n");
            }
            else
            {
                printf("No WINNER\n");
            }
        }

        /**********ここまで**********/
    }
    /**********ここまで**********/

    HgGetChar();
    HgClose();

    return 0;
}

/**********update関数**********/
void update()
{
    int i, j; // カウンタ変数

    int xCenter, yCenter; // 描写する円の中心座標

    for (i = 1; i < 9; i++)
    {
        for (j = 1; j < 9; j++)
        {
            if (board[i][j] == 1) // 白だったら
            {
                xCenter = CELL_SIZE / 2 + (CELL_SIZE * (i - 1)); // セルの中心座標を計算
                yCenter = CELL_SIZE / 2 + (CELL_SIZE * (j - 1)); // セルの中心座標を計算

                HgSetFillColor(HG_WHITE);
                HgCircleFill(xCenter, yCenter, CELL_SIZE / 2, 1); // 白を置く
            }
            if (board[i][j] == 2) // 黒だったら
            {
                xCenter = CELL_SIZE / 2 + (CELL_SIZE * (i - 1)); // セルの中心座標を計算
                yCenter = CELL_SIZE / 2 + (CELL_SIZE * (j - 1)); // セルの中心座標を計算

                HgSetFillColor(HG_BLACK);
                HgCircleFill(xCenter, yCenter, CELL_SIZE / 2, 1); // 黒を置く
            }
        }
    }
}
/**********ここまで**********/

/**********Othello_Algorithm関数**********/
void Othello_Algorithm(int x, int y)
{
    int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, z; // カウンタ変数

    int color; // 白or黒の判定用(白を1,黒を2とする)

    /**********挟まれていたら裏返す**********/
    for (color = 1; color <= 2; color++)
    {
        if (board[x][y] == color) // 白or黒だったら
        {
            /***********右向きの判定***********/
            for (i = 1; i < 9; i++)
            {
                if (board[x + i][y] == color) // 右が白or黒だったら
                {
                    for (j = 0; j <= i; j++)
                    {
                        board[x + j][y] = color; // 間を全て白or黒にする
                        update();                // 配列とウィンドウを同期させる
                        HgSleep(0.1);            // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x + i][y] == 0) // 右が空白だったら
                {
                    break;
                }
                else if (board[x + i][y] == -1) // 右が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********上向きの判定***********/
            for (k = 1; k < 9; k++)
            {
                if (board[x][y + k] == color) // 上が白or黒だったら
                {
                    for (l = 0; l <= k; l++)
                    {
                        board[x][y + l] = color; // 間を全て白or黒にする
                        update();                // 配列とウィンドウを同期させる
                        HgSleep(0.1);            // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x][y + k] == 0) // 上が空白だったら
                {
                    break;
                }
                else if (board[x][y + k] == -1) // 上が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********左向きの判定***********/
            for (m = 1; m < 9; m++)
            {
                if (board[x - m][y] == color) // 左が白or黒だったら
                {
                    for (n = 0; n <= m; n++)
                    {
                        board[x - n][y] = color; // 間を全て白or黒にする
                        update();                // 配列とウィンドウを同期させる
                        HgSleep(0.1);            // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x - m][y] == 0) // 左が空白だったら
                {
                    break;
                }
                else if (board[x - m][y] == -1) // 左が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********下向きの判定***********/
            for (o = 1; o < 9; o++)
            {
                if (board[x][y - o] == color) // 下が白or黒だったら
                {
                    for (p = 0; p <= o; p++)
                    {
                        board[x][y - p] = color; // 間を全て白or黒にする
                        update();                // 配列とウィンドウを同期させる
                        HgSleep(0.1);            // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x][y - o] == 0) // 下が空白だったら
                {
                    break;
                }
                else if (board[x][y - o] == -1) // 下が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********右上向きの判定***********/
            for (q = 1; q < 9; q++)
            {
                if (board[x + q][y + q] == color) // 右上が白or黒だったら
                {
                    for (r = 0; r <= q; r++)
                    {
                        board[x + r][y + r] = color; // 間を全て白or黒にする
                        update();                    // 配列とウィンドウを同期させる
                        HgSleep(0.1);                // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x + q][y + q] == 0) // 右上が空白だったら
                {
                    break;
                }
                else if (board[x + q][y + q] == -1) // 右上が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********左上向きの判定***********/
            for (s = 1; s < 9; s++)
            {
                if (board[x - s][y + s] == color) // 左上が白or黒だったら
                {
                    for (t = 0; t <= s; t++)
                    {
                        board[x - t][y + t] = color; // 間を全て白or黒にする
                        update();                    // 配列とウィンドウを同期させる
                        HgSleep(0.1);                // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x - s][y + s] == 0) // 左上が空白だったら
                {
                    break;
                }
                else if (board[x - s][y + s] == -1) // 左上が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********左下向きの判定***********/
            for (u = 1; u < 9; u++)
            {
                if (board[x - u][y - u] == color) // 左下が白or黒だったら
                {
                    for (v = 0; v <= u; v++)
                    {
                        board[x - v][y - v] = color; // 間を全て白or黒にする
                        update();                    // 配列とウィンドウを同期させる
                        HgSleep(0.1);                // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x - u][y - u] == 0) // 左下が空白だったら
                {
                    break;
                }
                else if (board[x - u][y - u] == -1) // 左下が壁だったら
                {
                    break;
                }
            }
            /**********ここまで**********/

            /***********右下向きの判定***********/
            for (w = 1; w < 9; w++)
            {
                if (board[x + w][y - w] == color) // 右下が白or黒だったら
                {
                    for (z = 0; z <= w; z++)
                    {
                        board[x + z][y - z] = color; // 間を全て白or黒にする
                        update();                    // 配列とウィンドウを同期させる
                        HgSleep(0.1);                // 0.1秒待つ
                    }
                    break;
                }
                else if (board[x + w][y - w] == 0) // 右下が空白だったら
                {
                    break;
                }
                else if (board[x + w][y - w] == -1) // 右下が壁だったら
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

