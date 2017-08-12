#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    

void display_grid(int[3][3]);       // Display the grid
player init_player(int numPlayer);  // Let a player choose a name
void empty_buffer(void);	        // Empty the buffer

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
    player p1 = init_player(1);
    player p2 = init_player(2);
    
    printf("\nIt's your turn p1 %s :",p1.name);
       
    int grid[3][3]={
        {1,0,0},
        {0,10,0},
        {0,0,0}
    };
    display_grid(grid);
    
    return 0;
}

player init_player(int numPlayer){
    player p={malloc(sizeof(char) * 21 ),0};    // Allocation of char[21] for name
    printf("Player %d, what's your name? ",numPlayer);
    fgets(p.name, 20, stdin);
    p.name = strtok(p.name, "\n");  // remove \n of name
    return p;
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


