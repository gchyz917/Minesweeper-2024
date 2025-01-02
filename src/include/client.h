#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <utility>

extern int rows;         // The count of rows of the game map.
extern int columns;      // The count of columns of the game map.
extern int total_mines;  // The count of mines of the game map.
char a[35][35];

// You MUST NOT use any other external variables except for rows, columns and total_mines.

/**
 * @brief The definition of function Execute(int, int, bool)
 *
 * @details This function is designed to take a step when player the client's (or player's) role, and the implementation
 * of it has been finished by TA. (I hope my comments in code would be easy to understand T_T) If you do not understand
 * the contents, please ask TA for help immediately!!!
 *
 * @param r The row coordinate (0-based) of the block to be visited.
 * @param c The column coordinate (0-based) of the block to be visited.
 * @param type The type of operation to a certain block.
 * If type == 0, we'll execute VisitBlock(row, column).
 * If type == 1, we'll execute MarkMine(row, column).
 * If type == 2, we'll execute AutoExplore(row, column).
 * You should not call this function with other type values.
 */
void Execute(int r, int c, int type);

/**
 * @brief The definition of function InitGame()
 *
 * @details This function is designed to initialize the game. It should be called at the beginning of the game, which
 * will read the scale of the game map and the first step taken by the server (see README).
 */
void InitGame() {
  // TODO (student): Initialize all your global variables!
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      a[i][j]='?';
    }
  }
  int first_row, first_column;
  std::cin>>first_row >> first_column;
  Execute(first_row, first_column, 0);
}

/**
 * @brief The definition of function ReadMap()
 *
 * @details This function is designed to read the game map from stdin when playing the client's (or player's) role.
 * Since the client (or player) can only get the limited information of the game map, so if there is a 3 * 3 map as
 * above and only the block (2, 0) has been visited, the stdin would be
 *     ???
 *     12?
 *     01?
 */
void ReadMap() {
  // TODO (student): Implement me!
  for(int i=0;i<rows;i++) {
    for(int j=0;j<columns;j++) {
      std::cin>>a[i][j];
    }
  }
}

/**
 * @brief The definition of function Decide()
 *
 * @details This function is designed to decide the next step when playing the client's (or player's) role. Open up your
 * mind and make your decision here!
 */
int min(int a,int b){
  return (a<b)?a:b;
}
int max(int a,int b){
  return (a>b)?a:b;
}
void Decide() {
  // TODO (student): Implement me!
  while (true) {
    bool flag1=0,flag2=0,flag3=0;
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        int num1=0,num2=0,m=0;
        int K[8],L[8];
        if(a[i][j]>='1'&&a[i][j]<='8') {
          for(int k=max(0,i-1);k<=min(rows-1,i+1);k++) {
            for(int l=max(0,j-1);l<=min(columns-1,j+1);l++) {
              if(a[k][l]=='?') {
                num1++;
                K[m]=k;
                L[m]=l;
                m++;
              }else if(a[k][l]=='@'){
                num2++;
              }
            }
          }
          if((a[i][j]==(num1+num2)+'0')&&num1!=0) {
            for(int k=max(0,i-1);k<=min(rows-1,i+1);k++) {
              for(int l=max(0,j-1);l<=min(columns-1,j+1);l++) {
                if(a[k][l]=='?') {
                  Execute(k,l,1);
                  flag1=1;
                  break;
                }
              }
              if(flag1==1) break;
            }
          }
        }
        if(flag1==1) break;
      }
      if(flag1==1) break;
    }
    if(flag1==1) break;
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        if(a[i][j]>='1'&&a[i][j]<='8') {
          int num=0;
          bool sign=0;
          for(int k=max(0,i-1);k<=min(rows-1,i+1);k++) {
            for(int l=max(0,j-1);l<=min(columns-1,j+1);l++) {
              if(k!=i||l!=j) {
                if(a[k][l]=='@') num++;
              }
              if(a[k][l]=='?') sign=1;
            }
          }
          if((a[i][j]==num+'0')&&sign) {
            Execute(i,j,2);
            flag2=1;
            break;
          }
        }
      }
      if(flag2==1) break;
    }
    if(flag2==1) break;
    int number1=0,number2=0;
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        if(a[i][j]=='@') number1++;
        else if(a[i][j]=='?') number2++;//number of undiscoveries
      }
    }
    number1=total_mines-number1;//number of mines
    for(int i=0;i<rows;i++) {
      for(int j=0;j<columns;j++) {
        if(a[i][j]=='?') {
          flag3=1;
          if(number1<=number2)Execute(i,j,0);
          else Execute(i,j,1);
          break;
        }
      }
      if(flag3==1) break;
    }
    if(flag3==1) break;
  }
}

#endif
