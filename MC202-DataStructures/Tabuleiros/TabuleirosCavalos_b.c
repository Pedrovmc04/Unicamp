#include <stdio.h>
#include <string.h>
#include <malloc.h>

//////////////////////////////////////////////////////////////////////////////////

int char_to_int(char convert){
    int converted = 0;

    if(convert >= '1' && convert <= '8'){
        converted = (int)(convert-'1');
    }else{
        converted = (int)(convert-'A');
    }

    return converted;
}

//////////////////////////////////////////////////////////////////////////////////

char** new_board(){
    char** board = (char**)calloc(8, sizeof(char*));

    for(int i = 0 ; i < 8 ; i++){
        board[i] = (char*)calloc(8, sizeof(char));

        for(int j = 0 ; j < 8 ; j++){
            board[i][j] = '-';
        }
    }

    return board;
}

//////////////////////////////////////////////////////////////////////////////////

void print_board(char** board){
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////

char** read_positions(int size){
    char** positions = (char**)calloc(size, sizeof(char*));

    for(int i = 0; i < size; i++){
        positions[i] = (char*)calloc(2, sizeof(char));
        for(int j = 0 ; j < 2 ; j++){
            char temp[10];
            scanf("%s",temp);
            positions[i][j] = temp[0];
        }
    }

    return positions;
}

//////////////////////////////////////////////////////////////////////////////////

char** position_board(int size,char** positions){
    char** board = new_board();
    for(int i = 0 ; i < size ; ++i){
        int x = char_to_int(positions[i][0]);
        int y = char_to_int(positions[i][1]);
        
        board[x][y] = 'N';
    }

    return board;
}

//////////////////////////////////////////////////////////////////////////////////

void moviment_board(int x, int y){
    int dx[] = {-1,1,2,2,1,-1,-2,-2};
    int dy[] = {2,2,1,-1,-2,-2,-1,1};

    printf("walk_pos: ");

    for(int i = 0 ; i < 8 ; i++){
        int xx = x + dx[i];
        int yy = y + dy[i];

        if(xx >= 0 && yy >= 0 && xx < 8 && yy < 8){
            char moviment_x = (char)('A'+xx);
            char moviment_y = (char)('1'+yy);

            printf("%c %c ",moviment_x,moviment_y);
        }
    }

    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////

void check_war(int size,char** position,char** board){
    int dx[] = {-1,1,2,2,1,-1,-2,-2};
    int dy[] = {2,2,1,-1,-2,-2,-1,1};
    int flag = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < 8; j++){
            int xx = char_to_int(position[i][0]) + dx[j];
            int yy = char_to_int(position[i][1]) + dy[j];

            if(xx >= 0 && yy >= 0 && xx < 8 && yy < 8 && board[xx][yy] == 'N'){
                flag = 1;
            }
        }
        if(flag)break;
    }

    if(flag){
        printf("Os cavalos estao em guerra!");
    }else{
        printf("Paz no reino!");
    }
}

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

int main(){
    int n;
    scanf("%d",&n);

    char** positions = read_positions(n);

    char** board = position_board(n,positions);

    check_war(n,positions,board);

    //Free the positions and tabuleiro

    /*destroy_matrix(positions,n,2);
    destroy_matrix(board,8,8);*/

    for(int i = 0 ; i < n ; i++){
        free(positions[i]);
    }
    free(positions);
    positions = NULL;

    for(int i = 0 ; i < 8 ; i++){
        free(board[i]);
    }
    free(board);
    board = NULL;

    return 0;
}