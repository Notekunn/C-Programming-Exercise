![Kết quả](https://i.imgur.com/dSFHUFH.png)

-------------------------------
# BÀI 1 - BÀI TOÁN ĐẶT QUÂN

Đề bài: Cho một bàn cờ 8x8 , gọi tọa độ của 1 ô bất kỳ là i,j (0 <= i,j <=7)

Có 2 người chơi là người A và B, 2 người sẽ lần lượt đặt quân lên bàn cờ sao cho:

   - Các vị trí xe ăn được (cùng hàng hoặc cùng cột với ô đặt vào) hoặc ô đặt vào sẽ được đánh dấu là *ô kiểm soát*.
   - Xe phải đặt ở ô chưa bị kiểm sát.

Mỗi ô chưa bị kiểm soát, nếu bị người chơi nào kiểm soát trước thì sẽ tính điểm cho người đó, mỗi ô 1 điểm.

Chơi cho đến khi toàn bộ bàn cờ hết vị trí đặt quân.

Tính số điểm của từng người và kết luận thắng thua.

Y/c: Sau mỗi bước đi in lại bàn cờ hiện tại, với A, B là vị trí đặt quân người A, B và a, b là vị trí chiếm được của A, B.

------------------------------
## BÀI LÀM

#### Khởi tạo
--------
Chúng ta sẽ xem bàn cờ như một ma trận 8 x 8.

Đầu tiên chúng ta sẽ viết 2 hàm dùng để tạo ma trận và vẽ ma trận (`createMatrix` và `drawMatrix`).

Ở đây mình define n giá trị 8 chính là số cột của bàn cờ (sau này nếu muốn đổi số ô thì chỉ cần thay đổi giá trị ở đây là được).

Code:

```c
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


int main() {
    char a[n][n];
    createMatrix(a);
    drawMatrix(a);
    printf("\n");
  
    return 0;
}
```
Chạy thử code ta được kết quả:
![Kết quả](https://i.imgur.com/cEPYKlV.png)

-------

#### Viết hàm kiểm tra điều kiện dừng

Nếu còn bất kỳ ô nào chưa được điền (phần tử ma trận đó là space) thì vẫn tiếp tục còn không thì dừng lại.
```c
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
```

-------
#### Viết hàm kiểm tra tọa độ người chơi nhập

Nếu ma trận không chứa tọa độ đó hoặc đã được điền từ trước thì nó không hợp lệ.
```c
int checkCanFill(char a[n][n], int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= n) return 0;
    return a[y][x] == ' ';
    //a[y][x] vì x là cot con y la hàng (moi hang chua cac phan tu thuoc cac cot)
}
```

-------
#### Viết hàm đặt quân và chiếm ô
```c
void fillMatrix(char a[n][n], int x, int y, char person ) //person A , B
{
    int i, j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < n; j++) {
            if((j == x || i == y) && a[i][j] == ' ') a[i][j] = person +32;//Viết thường A->a
        }
    }
    a[y][x] = person;
}
```

-------
#### Viết hàm tính điểm

```c
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
```

-------
#### Hoàn tất

Sau mỗi nước đi phải in lại bàn cờ mới nên ta sẽ dùng lệnh `system("cls")` để xóa bàn cờ cũ và in lại bàn cờ mới.

Mỗi lần người chơi nhập vào ta sẽ kiểm tra xem tọa độ có hợp lệ hay không nếu không sẽ bắt người dùng nhập lại

```c
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
    int x, y, step = 0;
    int pointA, pointB;//Step = 0 -> A , 1 ->B
    char person; // A, B
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
```













