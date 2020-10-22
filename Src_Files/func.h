#include "global.h"
#ifndef FUNC_H
#define FUNC_H

bool isEqual(int*** a,int** b,int n);
bool isEqual(int** a,int** b);
int evalute(int** state,int** target);
//void findBrack(int** a,int x,int y);
bool move(int** a,int** b,int dir);
void statecpy(int*** a,int** b,int n);
void getState(int*** a,int** b,int n);
void statecpy(int** a,int** b);
int checkAdd(int*** a,int** b,int n);

int min(int F[maxState], bool oc[maxState], int n);
int Astar(int*** a,int** start,int** target,int path[maxState]);
void show(int*** a,int n);
int calDe(int** a);
void autoGenerate(int** a);

bool Init_StartState(int** a, QString str1);
bool Search_Route();
void sleep(unsigned int msec);
QString Num2str(int n);

void change_dims(int m, int n);
void init_all();
bool if_can_be_solved(int** a, int** b);

#endif // FUNC_H
