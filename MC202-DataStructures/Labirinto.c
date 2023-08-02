#include <stdio.h>
#include <stdlib.h>

typedef struct _maze{
    char **maze;
    int x,y,k;
    int startx,starty;
    int endx,endy;
}maze;

maze new_maze(char *path){
    FILE *f = fopen(path,"r");

    maze temp;
    
    fscanf(f,"%d %d %d",&temp.y,&temp.x,&temp.k);
    temp.maze = (char**)calloc(temp.x,sizeof(char*));
    
    for(int i = 0 ; i < temp.x ; i++){
        temp.maze[i] = (char*)calloc(temp.y,sizeof(char));

        fscanf(f,"%s\n",temp.maze[i]);
    }

    for(int i = 0 ; i < temp.x ; i++){
        for(int j = 0 ; j < temp.y ; j++){
            if(temp.maze[i][j] == 'E'){
                temp.startx = i;
                temp.starty = j;
            }
            if(temp.maze[i][j] == 'S'){
                temp.endx = i;
                temp.endy = j;
            }
        }
    }

    fclose(f);

    return temp;
}

void print_maze(maze labirinto){
    printf("%d %d %d\n",labirinto.y,labirinto.x,labirinto.k);
    for(int i = 0 ; i < labirinto.x ; i++){
        for(int j = 0 ; j < labirinto.y ; j++){
            printf("%c",labirinto.maze[i][j]);
        }
        printf("\n");
    }

    printf("start:%d %d\nend:%d %d\n", labirinto.startx, labirinto.starty,labirinto.endx,labirinto.endy);
}

int search_maze(maze lab,int x,int y){
    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};
    int ans = 0;

    for(int i = 0 ; i < 4 ; i++){
        int xx = x + dx[i];
        int yy = y + dy[i];

        if(xx >= 0 && xx < lab.x && yy >= 0 && yy < lab.y && lab.maze[xx][yy] != 'X'){
            if(lab.maze[xx][yy] == 'P'){
                char temp = lab.maze[x][y];
                lab.maze[x][y] = 'X';   //maked positions
                ans = search_maze(lab,xx,yy);
                lab.maze[x][y] = temp;
                if(ans == 1)return ans;
            }else{
                return 1;
            }
        }
    }

    return ans;
}

int main(int argc, char *argv[]){
    char *path = argv[1];
    
    maze maze = new_maze(path);
    
    if(search_maze(maze,maze.startx,maze.starty) && search_maze(maze,maze.endx,maze.endy)){
        printf("Encontrou a saida em (%d,%d)\n",maze.endy,maze.endx);
    }else{
        printf("Labirinto sem saida\n");
    }

    for(int i = 0 ; i < maze.x ; i++){
        if(maze.maze[i] != NULL){
            free(maze.maze[i]);
        }
    }
    free(maze.maze);

    return 0;
}