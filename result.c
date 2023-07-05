#include <stdio.h>
#include <handy.h>
#include <math.h>

#define R 50

int main()
{
    double txt_wid, txt_hei; // 画面の幅と高さ

    int x, y = 300; // にこちゃんマークの座標

    int i; // for文用

    HgOpen(800, 600);

    HgSetFont(HG_HB, 100);

    HgTextSize(&txt_wid, &txt_hei, "WHITE WIN");

    printf("wid:%lf, hei:%lf\n", txt_wid, txt_hei);

    HgText(400 - txt_wid / 2, (300 - txt_hei / 2) + 200, "WHITE WIN");

    HgSetFillColor(HG_BLACK);

    for (i = 0; i < 5; i++)
    {
        x = 80 + 160 * i;

        HgCircle(x, y, R);

        HgCircleFill(x - 20, y + 20, 5, 1); // 左目
        HgCircleFill(x + 20, y + 20, 5, 1); // 右目

        HgArc(x, y, 30, M_PI * (7 / 6), M_PI * (-1 / 6)); // 口
    }

    HgGetChar();
    HgClose();

    return 0;
}