#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <windows.h>
#include <process.h>
#define SNAKE_UP 72
#define SNAKE_DOWN 80
#define SNAKE_LEFT 75
#define SNAKE_RIGHT 77
int Length;
int Bend_snake_num;
int Len;
char KEY;
void GameRecord();
void LoadGame();
int LIFE;
void Delaygame(long double);
void Movesnake();
void Food_snake();
int Gamescore();
void print();
void goto_xy(int x, int y);
void Goto_xy(int x,int y);
void Bend_snake();
void Boarder();
void Snake_down();
void Snake_left();
void Snake_up();
void Snake_right();
void Quit_game();
int Game_score_only();
struct coordinate{
int x;
int y;
int direction;
};
typedef struct coordinate coordinate;
coordinate head, bend_snake[500],food_snake,body[30];
int main()
{
char KEY;
print();
system("cls");
LoadGame();
Length=5;
head.x=25;
head.y=20;
head.direction=SNAKE_RIGHT;
Boarder();
Food_snake();
LIFE=3;
bend_snake[0]=head;
Movesnake();
return 0;
}
void Movesnake()
{
int a,i;
do{
Food_snake();
fflush(stdin);
Len=0;
for(i=0;i<30;i++)
{
body[i].x=0;
body[i].y=0;
if(i==Length)
break;
}
Delaygame(Length);
Boarder();
if(head.direction==SNAKE_RIGHT)
Snake_right();
else if(head.direction==SNAKE_LEFT)
Snake_left();
else if(head.direction==SNAKE_DOWN)
Snake_down();
else if(head.direction==SNAKE_UP)
Snake_up();
Quit_game();
}while(!kbhit());
a=getch();
if(a==27)
{
system("cls");
exit(0);
}
KEY=getch();
if((KEY==SNAKE_RIGHT&&head.direction!=SNAKE_LEFT&&head.direction!=SNAKE_RIGHT)||(KEY==SNAKE_LEFT&&head.direction!=SNAKE_RIGHT&&head.direction!=SNAKE_LEFT)||(KEY==SNAKE_UP&&head.direction!=SNAKE_DOWN&&head.direction!=SNAKE_UP)||(KEY==SNAKE_DOWN&&head.direction!=SNAKE_UP&&head.direction!=SNAKE_DOWN))
{
Bend_snake_num++;
bend_snake[Bend_snake_num]=head;
head.direction=KEY;
if(KEY==SNAKE_UP)
head.y--;
if(KEY==SNAKE_DOWN)
head.y++;
if(KEY==SNAKE_RIGHT)
head.x++;
if(KEY==SNAKE_LEFT)
head.x--;
Movesnake();
}
else if(KEY==27)
{
system("cls");
exit(0);
}
else
{
printf("\a");
Movesnake();
}
}
void goto_xy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Goto_xy(int x, int y)
{
HANDLE a;
COORD b;
fflush(stdout);
b.X = x;
b.Y = y;
a = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(a,b);
}
void LoadGame(){
int row,col,r,c,q;
goto_xy(36,14);
printf("LoadGameing...");
goto_xy(30,15);
for(r=1;r<=20;r++){
for(q=0;q<=100000000;q++);
printf("%c",177);}
getch();
}
void Snake_down()
{
int i;
for(i=0;i<=(head.y-bend_snake[Bend_snake_num].y)&&Len<Length;i++)
{
Goto_xy(head.x,head.y-i);
{
if(Len==0)
printf("v");
else
printf("-");
}
body[Len].x=head.x;
body[Len].y=head.y-i;
Len++;
}
Bend_snake();
if(!kbhit())
head.y++;
}
void Delaygame(long double k)
{
Gamescore();
long double i;
for(i=0;i<=(10000000);i++);
}
void Quit_game()
{
int i,check=0;
for(i=4;i<Length;i++)
{
if(body[0].x==body[i].x&&body[0].y==body[i].y)
{
check++;
}
if(i==Length||check!=0)
break;
}
if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
{
LIFE--;
if(LIFE>=0)
{
head.x=25;
head.y=20;
Bend_snake_num=0;
head.direction=SNAKE_RIGHT;
Movesnake();
}
else
{
system("cls");
printf("Three lives are finished\nWell Played!!!\nClick any button to exit the game\n");
GameRecord();
exit(0);
}
}
}
void Food_snake()
{
if(head.x==food_snake.x&&head.y==food_snake.y)
{
Length++;
time_t a;
a=time(0);
srand(a);
food_snake.x=rand()%70;
if(food_snake.x<=10)
food_snake.x+=11;
food_snake.y=rand()%30;
if(food_snake.y<=10)
food_snake.y+=11;
}
else if(food_snake.x==0)
{
food_snake.x=rand()%70;
if(food_snake.x<=10)
food_snake.x+=11;
food_snake.y=rand()%30;
if(food_snake.y<=10)
food_snake.y+=11;
}
}
void Snake_left()
{
int i;
for(i=0;i<=(bend_snake[Bend_snake_num].x-head.x)&&Len<Length;i++)
{
Goto_xy((head.x+i),head.y);
{
if(Len==0)
printf("<");
else
printf("-");
}
body[Len].x=head.x+i;
body[Len].y=head.y;
Len++;
}
Bend_snake();
if(!kbhit())
head.x--;
}
void Snake_right()
{
int i;
for(i=0;i<=(head.x-bend_snake[Bend_snake_num].x)&&Len<Length;i++)
{
body[Len].x=head.x-i;
body[Len].y=head.y;
Goto_xy(body[Len].x,body[Len].y);
{
if(Len==0)
printf(">");
else
printf("-");
}
Len++;
}
Bend_snake();
if(!kbhit())
head.x++;
}
void Bend_snake()
{
int i,j,diff;
for(i=Bend_snake_num;i>=0&&Len<Length;i--)
{
if(bend_snake[i].x==bend_snake[i-1].x)
{
diff=bend_snake[i].y-bend_snake[i-1].y;
if(diff<0)
for(j=1;j<=(-diff);j++)
{
body[Len].x=bend_snake[i].x;
body[Len].y=bend_snake[i].y+j;
Goto_xy(body[Len].x,body[Len].y);
printf("-");
Len++;
if(Len==Length)
break;
}
else if(diff>0)
for(j=1;j<=diff;j++)
{
body[Len].x=bend_snake[i].x;
body[Len].y=bend_snake[i].y-j;
Goto_xy(body[Len].x,body[Len].y);
printf("-");
Len++;
if(Len==Length)
break;
}
}
else if(bend_snake[i].y==bend_snake[i-1].y)
{
diff=bend_snake[i].x-bend_snake[i-1].x;
if(diff<0)
for(j=1;j<=(-diff)&&Len<Length;j++)
{
body[Len].x=bend_snake[i].x+j;
body[Len].y=bend_snake[i].y;
Goto_xy(body[Len].x,body[Len].y);
printf("-");
Len++;
if(Len==Length)
break;
}
else if(diff>0)
for(j=1;j<=diff&&Len<Length;j++)
{
body[Len].x=bend_snake[i].x-j;
body[Len].y=bend_snake[i].y;
Goto_xy(body[Len].x,body[Len].y);
printf("-");
Len++;
if(Len==Length)
break;
}
}
}
}
void Boarder()
{
system("cls");
int i;
Goto_xy(food_snake.x,food_snake.y);
printf("F");
for(i=10;i<71;i++)
{
Goto_xy(i,10);
printf("$");
Goto_xy(i,30);
printf("$");
}
for(i=10;i<31;i++)
{
Goto_xy(10,i);
printf("$");
Goto_xy(70,i);
printf("$");
}
}
void PRINT()
{
//Goto_xy(10,12);
printf("\t Mini Snake game welcomes you.(press any button to advance)\n");
getch();
system("cls");
printf("\tYou should follow these Game rules:\n");
printf("\n-> Make Use of the arrow keys given in the keyboard to make the snake move.\n\n-> Food will appear at the several coordinates of the window which you have to make the snake eat.Each time you eat food the snake will increase by 1 element and the score will also increase.\n\n-> In this game you are given three lives. Your lives will be decreased by 1 as you come across the wall or snake's body.\n\n-> You can stop the game in its middle by tapping any key. To continue the stopped game press any other key.\n\n-> If you wish to exit the game press esc. \n");
printf("\n\nTap any button to play the snake game...");
if(getch()==27)
exit(0);
}
void GameRecord(){
char plname[20],nplname[20],cha,c;
int i,j,px;
FILE -info;
info=fopen("GameRecord.txt","a+");
getch();
system("cls");
printf("Enter your name\n");
scanf("%[^\n]",plname);
for(j=0;plname[j]!='\0';j++){
nplname[0]=tosnake_upper(plname[0]);
if(plname[j-1]==' '){
nplname[j]=tosnake_upper(plname[j]);
nplname[j-1]=plname[j-1];}
else nplname[j]=plname[j];
}
nplname[j]='\0';
fprintf(info,"Player Name :%s\n",nplname);
time_t mytime;
mytime = time(NULL);
fprintf(info,"Played Date:%s",ctime(&mytime));
fprintf(info,"Gamescore:%d\n",px=Game_score_only());
//fprintf(info,"\nLevel:%d\n",10);
for(i=0;i<=50;i++)
fprintf(info,"%c",'_');
fprintf(info,"\n");
fclose(info);
printf("If you wish to see the previous highest scores press 'h'\n");
cha=getch();
system("cls");
if(cha=='y'){
info=fopen("GameRecord.txt","r");
do{
putchar(c=getc(info));
}while(c!=EOF);}
fclose(info);
}
int Gamescore()
{
int Gamescore;
Goto_xy(20,8);
Gamescore=Length-5;
printf("GAMESCORE : %d",(Length-5));
Gamescore=Length-5;
Goto_xy(50,8);
printf("Your Lives : %d",LIFE);
return Gamescore;
}
int Game_score_only()
{
int Gamescore=Gamescore();
system("cls");
return Gamescore;
}
void Snake_up()
{
int i;
for(i=0;i<=(bend_snake[Bend_snake_num].y-head.y)&&Len<Length;i++)
{
Goto_xy(head.x,head.y+i);
{
if(Len==0)
printf("^");
else
printf("-");
}
body[Len].x=head.x;
body[Len].y=head.y+i;
Len++;
}
Bend_snake();
if(!kbhit())
head.y--;
}