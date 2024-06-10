#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <unistd.h>
#include "myio.h"

#define DELAY 1000000

int pat[20][50] = {{0, 0}};

void mkpat()
{
    int i;
    int r;
    for (i = 0; i < 19; i++)
    {
        memcpy(pat[i], pat[i + 1], sizeof(int) * 50);
    }
    memset(pat[19], 0, sizeof(int) * 50);
    r = rand() % 5 + 2;
    for (i = 0; i < r; i++)
    {
        pat[19][i] = 1;
    }
    for (i = 50 - (8 - r); i < 50; i++)
    {
        pat[19][i] = 1;
    }
    r = rand() % 10;
    if (r == 0)
    {
        r = rand() % 35 + 5;
        pat[19][r] = 2;
        pat[19][r + 1] = 3;
        pat[19][r + 2] = 3;
        pat[19][r + 3] = 5;
        pat[19][r + 4] = 3;
        pat[19][r + 5] = 3;
        pat[19][r + 6] = 4;
    }
}

void disppat(int pos, int sts, int jmp)
{
    int x;
    int y;
    for (y = 0; y < 20; y++)
    {
        for (x = 0; x < 50; x++)
        {
            locate(x + 1, y + 2);
            switch (pat[y][x])
            {
            case 1:
                printf("#");
                break;
            case 2:
                printf("[");
                break;
            case 3:
                printf("-");
                break;
            case 4:
                printf("]");
                break;
            case 5:
                printf("$");
                break;
            case 11:
                printf("\\");
                break;
            case 12:
                printf("|");
                break;
            case 13:
                printf("/");
                break;
            case 14:
                printf("@");
                break;
            default:
                printf(" ");
                break;
            }

            if (x == pos && y == 7)
            {
                if (jmp > 0)
                {
                    locate(pos + 1, 9);
                    printf("y");
                }
                else if (sts < 100)
                {
                    locate(pos + 1, 9);
                    switch (sts)
                    {
                    case 0:
                        printf("Y");
                        break;
                    case 1:
                    case 5:
                        printf("X");
                        break;
                    case 2:
                    case 6:
                        printf("v");
                        break;
                    case 3:
                    case 7:
                        printf("^");
                        break;
                    case 4:
                    case 8:
                        printf("v");
                        break;
                    case 9:
                        printf("Y");
                        break;
                    default:
                        printf("@");
                        break;
                    }
                }
            }
            if (y == 12 && sts >= 100)
            {
                locate(20, 12);
                printf(" GAME OVER ");
            }
        }
    }
}

// 戻り値 点数 <0 は、激突
int chkcol(int pos, int prepos)
{
    int ret = 0;
    if (pat[7][pos] == 1 || pat[7][pos] == 2 || pat[7][pos] == 4)
    {
        pat[7][pos] = 14;
        // 障害物当たり表示
        ret = -1;
    }
    else
    {
        ret = pat[7][pos];
        pat[7][pos] = (pos == prepos) ? 12 : (pos > prepos) ? 11
                                                            : 13;
    }
    return ret;
}

int main(void)
{
    int cnt = 0;
    int key;
    int pos = 20;
    int prepos = 20;
    int dp = 0;
    int col = 0; // col を定義
    int sts = 0;
    int jmpsts = 0;
    int sc = 0;
    int miss = 0;
    srand((unsigned int)time(NULL));
    raw_mode(true);
    cls();
    key = 0;
    while (key != '0')
    {
        cnt++;
        if (kbhit())
        {
            key = getchar();
            if (dp == 0 && jmpsts == 0)
            {
                if (key == 'z')
                {
                    dp = -1;
                }
                if (key == 'x')
                {
                    dp = 1;
                }
                if (key == ' ')
                {
                    dp = 10;
                }
            }
        }
        if (cnt > DELAY)
        {
            if (col >= 0)
            {
                mkpat();
                prepos = pos;
                if (dp == 10)
                {
                    jmpsts = 5;
                }
                else
                {
                    pos += dp;
                }
            }
            disppat(pos, sts, jmpsts);
            if (jmpsts > 0)
                jmpsts--;
            dp = 0;

            if (col < 0 || miss >= 3)
            {
                sts++;
                if (sts > 15 && sts < 100)
                {
                    sts = 0;
                    if (miss < 3)
                    {
                        col = 0;
                    }
                    else
                    {
                        sts = 100;
                    }
                }
            }
            else
            {
                if (jmpsts == 0)
                {
                    col = chkcol(pos, prepos);
                    if (col >= 0)
                    {
                        sc += col;
                    }
                    else
                    {
                        sts = 1;
                        miss++;
                    }
                }
            }
            locate(39, 0);
            printf("SCORE");
            locate(46, 0);
            printf("%5d", sc);
            locate(1, 0);
            printf("MISS");
            locate(7, 0);
            printf("%2d", miss);
            cnt = 0;
        }
    }
    cls();
    raw_mode(false);
    printf("finish!!\n");
    return 0;
}
