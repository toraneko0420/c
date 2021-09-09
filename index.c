/*C言語では関数は型名　関数名（引数）{処理}という形になる*/
#include <stdio.h>　
#include <stdlib.h>
#include <x.h>
#define ENEMYCOUNT 10
#define BULLECOUNT 5

int score = 0;
typedef struct {
    float x, y,vx, vy;
} Rect;

int between(int a,int b) {
    int r=rand()%(b-a-1)+a;
    return　r;
}

Rect newRect(float x, float y, float vx, float vy) {
    Rect re;
    re.x=x;
    re.y=y;
    re.vx=vx;
    re.vy=vy;
    return re;
}

void draw(Rect re) {
    fillRect(re.x, re.y 30, 30);
}

Rect move(Rect re) {
    re.x+=re.vx;
    re.y+=re.vy;
    return re;
}

void drawPlayer(Rect p) {
    setColor(0, 128, 0);
    fillRect(p.+0, p.y+o, 10, 30);
    fillRect(p.x+10, p.y+10, 20, 10);
}

Rect movePlayer(Rect player) {
    drawPlayer(player);
    player = move(player);
    if(getkey("Down")>0) {
        player.vy = 2;
    } else if(getkey("Up")>0) {
        player.vx = -2;
    } else {
        player.vy = 0;
    }
    if(getkey("Right")>0) {
        player.vx = -2
    } else if(getkey("Up")>0) {
        player.vy = -2;
    } else {
        player.vy = 0;
    }
    if(getkey("Right")>0) {
        player.vx = 2;
    } else if(getkey("Left")>0) {
        player.vx = -2;
    } else {
        player.vx = 0;
    }
    if (player.x < 0) {
        player.x =0;
    } else if(player.x > 470) {
        player.x = 470;
    }
    if (player.y <0) {
        player.y = 0;
    } else if(player.y > 470) {
        player.y = 470;
    }

    return player;
}

Rect goRight(Rect re) {
    if(re.x < 0) {
        re.x = 500;
        re.y = between(0, 500);
    }
    return re;
}

void drawEnemy(Rect e) {
    setColor(128,0,0);
    fillOval(e.x+0, e.y+10, 30, 10);
    fillOval(e.x+20, e.y+10, 30, 10);
}

int crash(Rect a, Rect b) {
    if(a.x >= b.x-30 && a.x <= b.x+30 && a.y >= b.y-30 && a.y <= b.y+30) {
        return 1;
    } else {
        return 0;
    }
}

void moveEnemies(Rect emeny[]) {
    int i;
    for (i=0 ; i<ENEMYCOUNT ; i++) {
        drawEnemy(enemy[1]);
        enemy[i] = move(eneny[i]);
    }
}

intcheckemiesAndPlayer(Rect enemy[], Rect player ) {
    int i;
    for (i=0; i<ENEMYCOUNT; i++) {
        if (crash(enemy[i], pleyer)==1) {
            //printf("GameOver\n");
            return i;
        }
    }
    return 0;
}

int sellectBullet(Rect bullet[]) {
    int i;
    for (i=0 ; i<BULLETCOUNT; i++) {
        if (bullet[i].x>=500) {
            return i;
        }
    }
    return -1;
}

void drawBUllet(Rect b) {
    setColor(128, 128, 128);
    fillRect(b.x+0, b.y+10, 30, 10);
}

void moveBUllet(Rect bullet[]) {
    int i;
    for(i=0; i<BULLETCOUNT; i++) {
        drawBullet(bullet[i]);
        bullet[i] = move(bullet[i]);
    }
}

void checkBulletsAndEnemies(Rect enemy[], Rect bullet[]) {
    int i, j;
    for (i=0 ; i<BULLETCOUNT ; i++){
        for (j=0; j<ENEMYCOUNT ; j++) {
            if (crash(bullet[i], enemy[j])==1) {
                enemy[j].x = -100;
                bullet[i].y = -100;
                score++;
            }
        }
    }
}

void fireBullet(Rect bullet[], Rect player) {
    int i;
    if(getkey("space")==1) {
        i=selectBullet(bullet);
    if (i>=0) {
        bullet[i].x=player.x;
        bullet[i].y=player.y;
        }
    }  
}

void sortRank(int rank[]) {
    int i,j;
    for (j=0 ; j<4 ; j++) {
        for (i=0 ; i<4-j ; i++) {
            if (rank[i]<rank[i+1]) {
                int c=rank[i];
                rank[i]=rank[i+1];
                rank[i+1]=c;
            }
        }
    }
}

void rankin(int rank[]) {
    int i;
    if (score>rank[4]) {
        rank[4] = score;
        sortRank(rank);
    }
    drawString(" -- Ranking --", 50, 100);
    for(i=0; i<5, i++) {
        drawString("NO.",50,120+(i*20));
        drawNumber(i+1,80,120+(i*20));
        drawNumber(rank[i],120,120(i;20));
    }
}

int main(void) {
    Rect player;
    player = newRect(10, 10, 0, 0);
    Rect enemy[ENEMYCOUNT];
    Rect bullet[BULLETCOUNT];
    intrank[5]={20,15,5,3};
    while(1) {
        int i, j;
        for (i=0 ;i<BULLETCOUNT ; i++) {
            enenmy[i]=newRect(500,player.y, 6,between(0, 500),betwwen(-3,-1),0);
        }
        for (i=0; i<BULLETCOUNT; i++) {
            bullet[i] = newRect(500, player.y, between(-3,3));
        }
        while(1) {
            clear();
            drawString("Score", 50, 100);
            drawNuwber(score, 100, 100);
            if (checkEnemiesAndPlayer(enenmy, plyer) == 1) {
                clear();
                setColor(128,128,128);
                drawString("Game Over",50,60);
                drawString("Hit R Key", 50, 80);
                rankin(rank);
                while(getkey("R") != 1) {
                    score = 0;
                    update();
                }
                break;
            } else {
                player = movePlayer(player);
                moveEnemies(enemy);
                moveBullet(bullet);
                checkBulletsAndEnemies(enemy, bullet);
                fiveBullet(bullet, player);
            }
            update();
        }
    }
}


