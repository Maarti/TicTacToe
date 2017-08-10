#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char * name;
    int score;
} player;

typedef struct {
    char x;
    int y;
} point;

// Linked list keeping the history of the game
typedef struct histo {
    point point;
    player player;
    struct histo * next;
} history;
    

void display_grid(int[3][3]);   // Display the grid
void init_player(player *);     // Let a player choose a name
void empty_buffer(void);		// Empty buffer

int main(int argc, char *argv[]) {
    
    // Init mode GUI (=1) or CLI (=0)
    int mode = 0;
    if(argc > 1){
        if(strcmp(argv[1], "cli") == 0)
            mode = 0;
        else if(strcmp(argv[1], "gui") == 0)
            mode = 1;
        else{
        	printf("Bad argument - use %s [gui|cli]\n",argv[0]);
        	return 1;
        }
    }else{
        char modeType[2];
        mode = -1;
        while(mode != 0 && mode != 1 ){
            printf("Choose mode :\n0 = CLI\n1 = GUI\n");
			scanf ("%d",&mode);
			empty_buffer();
        }
    }
    
    char *welcome = "Welcome to TicTacToe!\n"; //this string can only be read
    printf("%s",welcome);
    
    history * histo = malloc(sizeof(history));
    player p1, p2;
    init_player(&p1);
    init_player(&p2);
    
    printf("\nIt's your turn %s :",p1.name);
    
    int grid[3][3]={
        {1,0,0},
        {0,10,0},
        {0,0,0}
    };
    display_grid(grid);
    
    return 0;
}

void init_player(player * p){
    (*p).name = "Player1";
    (*p).score = 0;
}

void display_grid(int grid[3][3]){
    int x,y;
    for(x=0; x<3;x++){
        printf("\n");
        for(y=0; y<3; y++){
            printf("-%d",grid[x][y]);
        }
    }
    printf("\n");
}

void empty_buffer(void){
    int c;
  
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


