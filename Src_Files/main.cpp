#include "mainwindow.h"
#include "func.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    all_state = new int**[M];
    for(int i = 0; i < M; i++){
        all_state[i] = new int*[N];
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            all_state[i][j] = new int[maxState];
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < maxState; k++){
                all_state[i][j][k] = 0;
            }
        }
    }

    start_state = new int*[M];
    for(int i = 0; i < M; i++){
        start_state[i] = new int[N];
    }
    for(int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) {
            start_state[i][j] = i*N + j;
        }
    }

    target_state = new int*[M];
    for(int i = 0; i < M; i++){
        target_state[i] = new int[N];
    }
    for(int i = 0; i < M; i++){
        for (int j = 0; j < N; j++) {
            target_state[i][j] = i*N + j;
        }
    }

    //qDebug() << QObject::tr("111");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
