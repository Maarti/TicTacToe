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
player init_player(int);            // Let a player choose a name
int check_grid(int[3][3]);          // Check if win or finish
void empty_buffer(void);            // Empty the buffer


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
    
    // Welcome message
    char *welcome = "Welcome to TicTacToe!\n"; //this string can only be read
    printf("%s",welcome);
    
    // Game initialization
    history * histo = malloc(sizeof(history));
    player p1 = init_player(1);
    player p2 = init_player(2);
    int grid[3][3]={
        {1,10,1},
        {1,10,10},
        {10,1,0}
    };
    int result = 0;
    
    // Game    
    printf("\nIt's your turn %s :",p1.name);
    display_grid(grid);
    result = check_grid(grid);
    printf(" result = %d \n",result);
    
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

int check_grid(int grid[3][3]){
    /*  return 0 : continue playing
        return 1 : player 1 won
        return 2 : player 2 won
        return 3 : draw
    */
    
    int x,y,sum=0;
    
    // Check horizontal
    for(x=0;x<3;x++){
        sum = 0;
        for(y=0;y<3;y++){
            sum+=grid[x][y];
        }
        if(sum==3)
            return 1;
        if(sum==30)
            return 2;
    }
    
    // Check vertical
    for(y=0;y<3;y++){
        sum = 0;
        for(x=0;x<3;x++){
            sum+=grid[x][y];
        }
        if(sum==3)
            return 1;
        if(sum==30)
            return 2;
    }
    
    // Check diagonal 1
    sum = grid[0][0] + grid[1][1] + grid[2][2];
    if(sum==3)
        return 1;
    if(sum==30)
        return 2;
        
    // Check diagonal 1
    sum = grid[0][2] + grid[1][1] + grid[2][0];
    if(sum==3)
        return 1;
    if(sum==30)
        return 2;
    
    // Check if finished
    for(x=0; x<3;x++){
        for(y=0; y<3; y++){
            if(grid[x][y] == 0)
                return 0;
        }
    }
        
    return 3;
}

void empty_buffer(void){
    int c;
  
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


