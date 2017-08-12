#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAY_VALUE_1 1
#define PLAY_VALUE_2 10

typedef struct {
    char * name;
    int score;
    int play_value;
    char character;
} player;

typedef struct {
    int x;
    int y;
} point;

// Linked list keeping the history of the game
typedef struct histo {
    point point;
    player player;
    struct histo * next;
} history;


void display_grid(int[3][3],player *,player *);// Display the grid
player init_player(int,int,char);   // Let a player choose a name
point input_play(int[3][3]);        // Ask user input and convert it to point
void do_play(int[3][3],player *);   // Let a player play in the grid
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
    player p1 = init_player(1,PLAY_VALUE_1,'X');
    player p2 = init_player(2,PLAY_VALUE_2,'O');
    
    while(1){   // TODO : replace by menu "Play again ? Exit ?"
        int grid[3][3]={
            {0,0,0},
            {0,0,0},
            {0,0,0}
        };
        int result = 0;
        player *current_player = &p1;
        
        // Game
        do{
            display_grid(grid,&p1,&p2);
            printf("\nIt's your turn %s :\n",current_player->name);
            do_play(grid,current_player);        
            result = check_grid(grid);
            if(current_player == &p1)
                current_player = &p2;
            else
                current_player = &p1;
            
         }while(!result);
         
         display_grid(grid,&p1,&p2);
         switch (result){
            case 1 :
                printf("\n%s won !!!\n",p1.name);
                p1.score += 1;
                break;
            case 2 :
                printf("\n%s won !!!\n",p2.name);
                p2.score += 1;
                break;
            case 3 :
                printf("\nDraw game.\n");
                break;
            default :
                printf("\nError occured.\n");
                return 1;
                break;
         }
         printf("\nScores :\n%d - %s\n%d : %s\n",p1.score,p1.name,p2.score,p2.name);
    }
    return 0;
}

player init_player(int numPlayer, int play_value, char character){
    player p={malloc(sizeof(char) * 21 ),0,play_value,character}; // Allocation of char[21] for name
    printf("Player %d, what's your name? ",numPlayer);
    fgets(p.name, 20, stdin);
    p.name = strtok(p.name, "\n");  // remove \n of name
    return p;
}

void display_grid(int grid[3][3],player *p1, player *p2){
    int x,y;
    printf("_____________________________\n  A B C");
    for(x=0; x<3;x++){
        printf("\n%d ",x+1);
        for(y=0; y<3; y++){
            int val = grid[x][y];
            if(val == PLAY_VALUE_1)
                printf("%c ",p1->character);
            else if(val==PLAY_VALUE_2)
                printf("%c ",p2->character);
            else
                printf("  ");
        }
    }
    printf("\n");
}

point input_play(int grid[3][3]){
    int valid=0,x=0,y=0;
    char input[4];  // = [a,1,\n,\0]
    const char *valid_col = "abcABC";
    const char *valid_row = "123";
    char col='a',row='1';
    
    do{
        valid = 1;
        printf("Play where ? (ex : a1) ");
        fgets(input, 4, stdin);
        int length = strlen(input);
        
        // Check size
        if(length!=3)
            valid = 0;
        else{
            // if last char different from \n, it means the buffer is not empty
            if(input[2]!='\n')
                empty_buffer();
            
            // Check format
            col = input[0];
            row = input[1];
            if(!strchr(valid_col, col) || !strchr(valid_row,row))
                valid = 0;
        }
                
        if(valid==0)
            printf("Invalid input\n\n");
    }while(!valid);
    
    // Convert input to point
    switch(col){
        case 'a' :
        case 'A' :
            y = 0;
            break;
        case 'b' :
        case 'B' :
            y = 1;
            break;
        case 'c' :
        case 'C' :
            y = 2;
            break;
    }
    switch(row){
        case '1' :
            x = 0;
            break;
        case '2' :
            x = 1;
            break;
        case '3' :
            x = 2;
            break;
    }    
    point p={x,y};
    
    // If the point is already played, error msg then recursive call
    if(grid[x][y] != 0){
        printf("You can't play here!\n\n");
        return input_play(grid);
    }
    
    return p;
}

void do_play(int grid[3][3],player *p){
    point play_point = input_play(grid);
    grid[play_point.x][play_point.y] = p->play_value;
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
        if(sum==PLAY_VALUE_1*3)
            return 1;
        if(sum==PLAY_VALUE_2*3)
            return 2;
    }
    
    // Check vertical
    for(y=0;y<3;y++){
        sum = 0;
        for(x=0;x<3;x++){
            sum+=grid[x][y];
        }
        if(sum==PLAY_VALUE_1*3)
            return 1;
        if(sum==PLAY_VALUE_2*3)
            return 2;
    }
    
    // Check diagonal 1
    sum = grid[0][0] + grid[1][1] + grid[2][2];
    if(sum==PLAY_VALUE_1*3)
        return 1;
    if(sum==PLAY_VALUE_2*3)
        return 2;
        
    // Check diagonal 1
    sum = grid[0][2] + grid[1][1] + grid[2][0];
    if(sum==PLAY_VALUE_1*3)
        return 1;
    if(sum==PLAY_VALUE_2*3)
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
    }while(c != '\n' && c != EOF);
}


