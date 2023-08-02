#include <stdio.h>
#include <string.h>

int char_to_int(char convert){
    int converted = 0;

    if(convert >= '1' && convert <= '8'){
        converted = (int)(convert-'1');
    }else{
        converted = (int)(convert-'A');
    }

    return converted;
}

void moviment_board(int x, int y){
    int dx[] = {-1,1,2,2,1,-1,-2,-2};
    int dy[] = {2,2,1,-1,-2,-2,-1,1};


    for(int i = 0 ; i < 8 ; i++){
        int xx = x + dx[i];
        int yy = y + dy[i];

        if(xx >= 0 && yy >= 0 && xx < 8 && yy < 8){
            char moviment_x = (char)('A'+xx);
            char moviment_y = (char)('1'+yy);

            printf("%c %c\n",moviment_x,moviment_y);
        }
    }
}

int main(){
    char x,y;

    scanf("%c %c",&x,&y);
    
    moviment_board(char_to_int(x),char_to_int(y));

    return 0;
}