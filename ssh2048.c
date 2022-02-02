#include <ncurses.h>
#include <cstdlib>
#include <ctime>
using namespace std;

    int sq_h=3;
    int sq_w=6;

    int starty=4;
    int startx=4;

    const int size = 4; //TODO choice

    WINDOW * win2 [size][size];
    int game[size][size];


    
    void printToBox(WINDOW*, int);
    void createField();
    void createStartData();
    void keyUpPressed();
    void keyRightPressed();
    void keyLeftPressed();
    void keyDownPressed();
    void updateAllBoxes();
    void generateRandomNumbers();

int main(int argc, char ** argv)
{
    srand(static_cast<unsigned int>(time(0))); //#love cpp random functionality
    initscr();

    //refresh(); CHECK REFRESH IN FUNC
    createStartData();
    createField();

    
    noecho();
    keypad (curscr, true); 

    
    int c = 0;
    

    while(c!='q'){
        c = wgetch(curscr);
        if(c==KEY_UP)
            keyUpPressed();
        if(c==KEY_DOWN)
            keyDownPressed();
        if(c==KEY_LEFT)
            keyLeftPressed();
        if(c==KEY_RIGHT)
            keyRightPressed();
        //printw("%d ", c);
    }
    
    
    

    //wait for input
    // int c = getch();
    // printw("%d", c);
    
    
    //end curses
    //getch();
    endwin();
    return 0;
}

void createField(){
    refresh();
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++){
            win2[i][j] = newwin(sq_h, sq_w, starty+i*sq_h, startx+j*sq_w);
            box(win2[i][j], 0, 0);
            printToBox(win2[i][j], game[i][j]);
            wrefresh(win2[i][j]);
            refresh();
        }
    refresh();
}

void createStartData(){
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++){
            game[i][j]=-1;
        }
    for(int i=0; i<2; i++){ 
        int x = rand() % size;
        int y = rand() % size;
        //printw("%d %d", x,y);
        game[x][y]=2;
    }

}

void printToBox(WINDOW* win, int value){
    if(value ==-1)
        mvwprintw(win, 1, 1, "    ");
        else
            if(value / 10 == 0 && value < 0)
                mvwprintw(win, 1, 1, " %d   ", value );
                    else
                        if(value / 100 == 0)
                            mvwprintw(win, 1, 1, " %d ", value );
                                else
                                    if(value / 1000 == 0)
                                        mvwprintw(win, 1, 1, " %d", value );
                                            else
                                                if(value / 10000 == 0 && value > 0)
                                                    mvwprintw(win, 1, 1, "%d", value );
    wrefresh(win);
    refresh();
}

void keyUpPressed(){
    for(int j = 0; j<size; j++){
        for(int i=0; i<size; i++)
        if(game[i][j]!=-1)
            for(int k = i+1; k<size; k++)
                if(game[k][j]!=-1){
                    if(game[k][j]==game[i][j]){
                        game[i][j]+=game[k][j];
                        game[k][j]=-1;
                    }
                    k=size;
                }

        for(int i=0; i<size; i++){ 
            if(game[i][j]==-1)
                for(int k = i+1; k<size; k++)
                    if(game[k][j]!=-1){
                        game[i][j]=game[k][j];
                        game[k][j]=-1;
                        k=size;
                    }  
        }
    }
    generateRandomNumbers();
    //updateAllBoxes();
}

void keyDownPressed(){
    for(int j = 0; j<size; j++){
        for(int i=size-1; i>=0; i--)
        if(game[i][j]!=-1)
            for(int k = i-1; k>=0; k--)
                if(game[k][j]!=-1){
                    if(game[k][j]==game[i][j]){
                        game[i][j]+=game[k][j];
                        game[k][j]=-1;
                    }
                    k=-1;
                }

        for(int i=size-1; i>=0; i--){ 
            if(game[i][j]==-1)
                for(int k = i-1; k>=0; k--){
                    if(game[k][j]!=-1){
                        game[i][j]=game[k][j];
                        game[k][j]=-1;
                        k=-1;
                    }
                }
        }
    }
    generateRandomNumbers();
    //updateAllBoxes();
}

void keyLeftPressed(){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++)
        if(game[i][j]!=-1)
            for(int k=j+1; k<size; k++)
            if(game[i][k]!=-1){
                if(game[i][k]==game[i][j]){
                    game[i][j]+=game[i][k];
                    game[i][k]=-1;
                }
                k=size;
            }
        for(int j=0; j<size; j++){ 
            if(game[i][j]==-1)
                for(int k = j+1; k<size; k++)
                    if(game[i][k]!=-1){
                        game[i][j]=game[i][k];
                        game[i][k]=-1;
                        k=size;
                    }  
        }
    }
    generateRandomNumbers();
    //updateAllBoxes();
}

void keyRightPressed(){
    for(int i=0; i<size; i++){
        for(int j=size-1; j>=0; j--)
        if(game[i][j]!=-1)
            for(int k=j-1; k>=0; k--)
            if(game[i][k]!=-1){
                if(game[i][k]==game[i][j]){
                    game[i][j]+=game[i][k];
                    game[i][k]=-1;
                }
                k=-1;
            }
        for(int j=size-1; j>=0; j--){ 
            if(game[i][j]==-1)
                for(int k = j-1; k>=0; k--)
                    if(game[i][k]!=-1){
                        game[i][j]=game[i][k];
                        game[i][k]=-1;
                        k=-1;
                    }  
        }
    }
    generateRandomNumbers();
    //updateAllBoxes();
}

void updateAllBoxes(){
    
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++){
            printToBox(win2[i][j], game[i][j]);
            wrefresh(win2[i][j]);
            refresh();
        }
    refresh();
}

void generateRandomNumbers(){
    int freeBox[size*size][2];
    int freeCount=0;
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            if(game[i][j]==-1){
                freeBox[freeCount][0]=i;
                freeBox[freeCount][1]=j;
                freeCount++;
               // printw("%d %d \n", i, j);
            }
        }
    
    if(freeCount>0){
        int amount=rand()%2;
        for(int i=0; i<=amount; i++){
            int cur = rand()%freeCount;
            int f = rand()%2;
            int a = freeBox[cur][0];
            int b = freeBox[cur][1];
            if(f==0) game[a][b]=2; 
                else 
                    game[a][b]=4;
        }
    } else 
    updateAllBoxes();
}
