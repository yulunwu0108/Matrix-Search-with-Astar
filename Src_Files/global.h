#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <QString>
#include <qmessagebox.h>
#include <windows.h>
#include <QTime>
#include <cmath>
#include <qcoreapplication.h>
#include <QDebug>
#include <QObject>
#include <ctime>
#include <time.h>

#define maxState 200000
#define maxBLK 25

using namespace std;

extern int M;   //行数
extern int N;   //列数

extern int*** all_state;
extern int** start_state;
extern int** target_state;

extern int path_[maxState];
extern int res_;
extern bool no_space;

extern int sh_route[maxState];
extern int index;

extern int step_num;
extern double srch_time;

#endif // GLOBAL_H
