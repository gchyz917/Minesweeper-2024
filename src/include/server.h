#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>

/*
 * You may need to define some global variables for the information of the game map here.
 * Although we don't encourage to use global variables in real cpp projects, you may have to use them because the use of
 * class is not taught yet. However, if you are member of A-class or have learnt the use of cpp class, member functions,
 * etc., you're free to modify this structure.
 */
int rows;         // The count of rows of the game map. You MUST NOT modify its name.
int columns;      // The count of columns of the game map. You MUST NOT modify its name.
int total_mines=0;  // The count of mines of the game map. You MUST NOT modify its name. You should initialize this
                  // variable in function InitMap. It will be used in the advanced task.初始化雷的数量
int game_state;  // The state of the game, 0 for continuing, 1 for winning, -1 for losing. You MUST NOT modify its name.
char a[35][35];
bool b[35][35];
/**
 * @brief The definition of function InitMap()
 *
 * @details This function is designed to read the initial map from stdin. For example, if there is a 3 * 3 map in which
 * mines are located at (0, 1) and (1, 2) (0-based), the stdin would be
 *     3 3
 *     .X.
 *     ...
 *     ..X
 * where X stands for a mine block and . stands for a normal block. After executing this function, your game map
 * would be initialized, with all the blocks unvisited.
 */
void InitMap() {
  std::cin >> rows >> columns;
  // TODO (student): Implement me!
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      std::cin>>a[i][j];
      if(a[i][j]=='X') {
        b[i][j]=0;
        total_mines++;
      }else  b[i][j]=1;
      a[i][j]='?';
    }
  }

}

/**
 * @brief The definition of function VisitBlock(int, int)
 *
 * @details This function is designed to visit a block in the game map. We take the 3 * 3 game map above as an example.
 * At the beginning, if you call VisitBlock(0, 0), the return value would be 0 (game continues), and the game map would
 * be
 *     1??
 *     ???
 *     ???
 * If you call VisitBlock(0, 1) after that, the return value would be -1 (game ends and the players loses) , and the
 * game map would be
 *     1X?
 *     ???
 *     ???
 * If you call VisitBlock(0, 2), VisitBlock(2, 0), VisitBlock(1, 2) instead, the return value of the last operation
 * would be 1 (game ends and the player wins), and the game map would be
 *     1@1
 *     122
 *     01@
 *
 * @param r The row coordinate (0-based) of the block to be visited.
 * @param c The column coordinate (0-based) of the block to be visited.
 *
 * @note You should edit the value of game_state in this function. Precisely, edit it to
 *    0  if the game continues after visit that block, or that block has already been visited before.
 *    1  if the game ends and the player wins.
 *    -1 if the game ends and the player loses.
 *
 * @note For invalid operation, you should not do anything.
 */
int min(int a,int b){
  return (a<b)?a:b;
}
int max(int a,int b){
  return (a>b)?a:b;
}
void num(int x,int y){
  int number=0;
  for(int i=max(x-1,0);i<=min(x+1,rows-1);i++){
    for(int j=max(y-1,0);j<=min(y+1,columns-1);j++){
      if(b[i][j]==0) {
        number++;
      }
    }
  }
  a[x][y]=number+'0';
  if(a[x][y]=='0'){
    for(int i=max(x-1,0);i<=min(x+1,rows-1);i++){
      for(int j=max(y-1,0);j<=min(y+1,columns-1);j++){
        if((i!=x||j!=y)&&a[i][j]=='?') num(i,j);
      }
    }
  }
}
void VisitBlock(int r, int c) {
  // TODO (student): Implement me!
  if(b[r][c]==0&&a[r][c]!='@'){
    a[r][c]='X';
    game_state=-1;
  }else if(b[r][c]==1){
    num(r,c);
    game_state=1;
    for(int i=0;i<rows;i++){
      for(int j=0;j<columns;j++){
        if(b[i][j]==1&&a[i][j]=='?') {
          game_state=0;
          break;
        }
      }
      if(game_state==0) break;
    }
    if(game_state==1) {
      for(int i=0;i<rows;i++) {
        for(int j=0;j<columns;j++) {
          if(b[i][j]==0) a[i][j]='@';
          else if(a[i][j]=='?') num(i,j);
        }
      }
    }
  }
}

/**
 * @brief The definition of function MarkMine(int, int)
 *
 * @details This function is designed to mark a mine in the game map.
 * If the block being marked is a mine, show it as "@".
 * If the block being marked isn't a mine, END THE GAME immediately. (NOTE: This is not the same rule as the real
 * game) And you don't need to 注意 标记错雷也直接结束游戏 return -1
 *
 * For example, if we use the same map as before, and the current state is:
 *     1?1
 *     ???
 *     ???
 * If you call MarkMine(0, 1), you marked the right mine. Then the resulting game map is:
 *     1@1
 *     ???
 *     ???
 * If you call MarkMine(1, 0), you marked the wrong mine(There's no mine in grid (1, 0)).
 * The game_state would be -1 and game ends immediately. The game map would be:
 *     1?1
 *     X??
 *     ???
 * This is different from the Minesweeper you've played. You should beware of that.
 *
 * @param r The row coordinate (0-based) of the block to be marked.
 * @param c The column coordinate (0-based) of the block to be marked.
 *
 * @note You should edit the value of game_state in this function. Precisely, edit it to
 *    0  if the game continues after visit that block, or that block has already been visited before.
 *    1  if the game ends and the player wins.
 *    -1 if the game ends and the player loses.
 *
 * @note For invalid operation, you should not do anything.
 */
void MarkMine(int r, int c) {
  // TODO (student): Implement me!
  if(b[r][c]==0){
    a[r][c]='@';
    game_state=0;
    int d=0;
    for(int i=0;i<rows;i++){
      for(int j=0;j<columns;j++){
        if(a[i][j]=='@') d++;
      }
    }
    if(d==total_mines) game_state=1;
  }else{
    if(a[r][c]=='?') {
      a[r][c]='X';
      game_state=-1;
    }
  }
  if(game_state==1) {
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        if(b[i][j]==0) a[i][j]='@';
        else if(a[i][j]=='?') num(i,j);
      }
    }
  }
}

/**
 * @brief The definition of function AutoExplore(int, int)
 *
 * @details This function is designed to auto-visit adjacent blocks of a certain block.
 * See README.md for more information
 *
 * For example, if we use the same map as before, and the current map is:
 *     ?@?
 *     ?2?
 *     ??@
 * Then auto explore is available only for block (1, 1). If you call AutoExplore(1, 1), the resulting map will be:
 *     1@1
 *     122
 *     01@
 * And the game ends (and player wins).
 */
void AutoExplore(int r, int c) {
  int m=0;
  for(int i=max(0,r-1);i<=min(r+1,rows-1);i++) {
    for(int j=max(0,c-1);j<=min(c+1,columns-1);j++) {
      if(a[i][j]=='@') m++;
    }
  }
  if(a[r][c]==m+'0') {
    for(int i=max(0,r-1);i<=min(r+1,rows-1);i++) {
      for(int j=max(0,c-1);j<=min(c+1,columns-1);j++) {
        if((a[i][j]!='@')&&(i!=r||j!=c)) num(i,j);
      }
    }
  }
  game_state=1;
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      if(b[i][j]==1&&a[i][j]=='?') {
        game_state=0;
        break;
      }
    }
    if(game_state==0) break;
  }
  if(game_state==1) {
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        if(b[i][j]==0) a[i][j]='@';
        else if(a[i][j]=='?') num(i,j);
      }
    }
  }
  // TODO (student): Implement me!
}

/**
 * @brief The definition of function ExitGame()
 *
 * @details This function is designed to exit the game.
 * It outputs a line according to the result, and a line of two integers, visit_count and marked_mine_count,
 * representing the number of blocks visited and the number of marked mines taken respectively.
 *
 * @note If the player wins, we consider that ALL mines are correctly marked.
 */
void ExitGame() {
  int visit_count=0,marked_mine_count=0;
  if(game_state==1) {
    std::cout<<"YOU WIN!"<<std::endl;
    std::cout<<rows*columns-total_mines<<" "<<total_mines;
  }else {
    std::cout<<"GAME OVER!"<<std::endl;
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        if(a[i][j]>='0'&&a[i][j]<='8') visit_count++;
        if(a[i][j]=='@') marked_mine_count++;
      }
    }
    std::cout<<visit_count<<" "<<marked_mine_count;
  }
  // TODO (student): Implement me!
  exit(0);// Exit the game immediately
}

/**
 * @brief The definition of function PrintMap()
 *
 * @details This function is designed to print the game map to stdout. We take the 3 * 3 game map above as an example.
 * At the beginning, if you call PrintMap(), the stdout would be
 *    ???
 *    ???
 *    ???
 * If you call VisitBlock(2, 0) and PrintMap() after that, the stdout would be
 *    ???
 *    12?
 *    01?
 * If you call VisitBlock(0, 1) and PrintMap() after that, the stdout would be
 *    ?X?
 *    12?
 *    01?
 * If the player visits all blocks without mine and call PrintMap() after that, the stdout would be
 *    1@1
 *    122
 *    01@
 * (You may find the global variable game_state useful when implementing this function.)
 *
 * @note Use std::cout to print the game map, especially when you want to try the advanced task!!!
 */
void PrintMap() {
  // TODO (student): Implement me!
  for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
          std::cout<<a[i][j];
      }
      std::cout<<std::endl;
  }
}

#endif
