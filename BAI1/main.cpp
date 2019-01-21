#include <iostream>
#define n 8
void createMatrix(char a[n][n]) {
    int i,j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j ++) {
            a[i][j] = ' ';
        }
    }
}
void drawMatrix(char a[n][n]) {
    int i,j;
    //In chi so cot
    printf("   |");
    for(j = 0; j < n; j ++) printf("  %d|", j);
    printf("\n___|");
    for(j = 0; j < n; j ++) printf("___|");
    printf("\n");
    //In cac hang
    for(i = 0; i < 2*n; i++) {
        //In chi so hang
        if(i % 2 == 0) printf("  %d|", i/2);
        else printf("___|");
        //In ra các phan tu cua hang
        for(j = 0; j < n; j ++) {
            if(i % 2 == 0) {
                printf("  %c|", a[i/2][j]);
            }
            else printf("___|");
        }
        printf("\n");
    }
    printf("\n");
}
int checkCanFill(char a[n][n], int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= n) return 0;
    return a[y][x] == ' ';
    //a[y][x] vì x là cot con y la hàng (moi hang chua cac phan tu thuoc cac cot)
}
int fullFilled(char a[n][n])
{
    int i,j;
    for (i =0; i <n ; i++) {
        for(j =0; j <n; j++) {
            if(a[i][j] == ' ') return 0;
        }
    }
    return 1;
}
void fillMatrix(char a[n][n], int x, int y, char person)
{
    int i, j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < n; j++) {
            if((j == x || i == y) && a[i][j] == ' ') a[i][j] = person +32;
        }
    }
    a[y][x] = person;
}
int getPoint(char a[n][n],char person)
{
    int i,j,point =0;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(a[i][j] == person || a[i][j] == person + 32) point ++;
        }
    }
    return point;
}
int main() {
    char a[n][n];
    int x, y, step = 0,pointA,pointB;//Step = 0 -> A , 1 ->B
    char person;
    createMatrix(a);
    drawMatrix(a);
    printf("\n");
    while(!fullFilled(a)) {

        person = step == 0 ? 'A': 'B';
        do {
            printf("Luot di cua %c:\n", person);
            printf("Nhap toa do o muon dat quan(o chua bi chiem): ");
            scanf("%d %d", &x, &y);
        }
        while(!checkCanFill(a,x,y));

        fillMatrix(a, x, y, person);
        system("cls");
        drawMatrix(a);
        printf("\n");
        step = (step + 1) % 2;
    }
    printf("GAME OVER\n");
    pointA = getPoint(a,'A');
    pointB = getPoint(a, 'B');
    printf("DIEM: A: %d; B: %d\n",pointA, pointB);
    printf("Nguoi chien thang chinh la %c, xin chuc mung ban!", pointA > pointB ? 'A': 'B');
    return 0;
}
