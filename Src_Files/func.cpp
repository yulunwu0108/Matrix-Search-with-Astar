#include "func.h"

bool isEqual(int*** a,int** b,int n)
{
    for(int i = 0;i < M;i ++){
        for(int j = 0;j < N;j ++){
            if(a[i][j][n] != b[i][j]) return false;
        }
    }
    return true;
}

bool isEqual(int** a,int** b)
{
    for(int i = 0;i < M;i ++){
        for(int j = 0;j < N;j ++){
            if(a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

/*
//对位不同+1 作为估值函数
int evalute(int state[N][N],int target[N][N])
{
    int num = 0;
    for(int i = 0;i < N;i ++){
        for(int j = 0;j < N;j ++)
            if(state[i][j] != target[i][j]) num ++;
    }
    return num;
}
*/

//曼哈顿距离作为估值函数
int evalute(int** state,int** target)
{
    int num = 0;
    for(int i = 0;i < M;i ++){
        for(int j = 0;j < N;j ++){
            if(state[i][j] > 0){
                for(int _i = 0; _i < M; _i++){
                    for(int _j = 0; _j < N; _j++){
                        if(state[i][j] == target[_i][_j]){
                            num += abs(i - _i) + abs(j - _j);
                        }
                    }
                }
            }
        }
    }
    return num;
}

bool move(int** a,int** b,int dir)
{
    //1 up 2 down 3 left 4 right
    int x = 0,y = 0;
    for(int i = 0;i < M;i ++){
        for(int j = 0;j < N;j ++){
            b[i][j] = a[i][j];
            if(a[i][j] == 0) {
                x = i;y = j;
            }
        }
    }
    if(x == 0 && dir == 1)
        return false;
    if(x == M-1 && dir == 2)
        return false;
    if(y == 0 && dir == 3)
        return false;
    if(y == N-1 && dir == 4)
        return false;
    if(dir == 1){
        b[x-1][y] = 0;
        b[x][y] = a[x-1][y];
    }
    else if(dir == 2){
        b[x+1][y] = 0;
        b[x][y] = a[x+1][y];
    }
    else if(dir == 3){
        b[x][y-1] = 0;
        b[x][y] = a[x][y-1];
    }
    else if(dir == 4){
        b[x][y+1] = 0;
        b[x][y] = a[x][y+1];
    }
    else
        return false;
    return true;
}

void statecpy(int*** a,int** b,int n)
{

    for(int i = 0;i < M;i ++){
        for(int j = 0;j < N;j ++){
            //qDebug() << a[i][j][n];
            a[i][j][n] = b[i][j];
        }
    }
    //qDebug() << QObject::tr("g");
}

void getState(int*** a,int** b,int n)
{
    for(int i = 0;i < M;i ++){
        for(int j = 0;j < N;j ++){
            b[i][j] = a[i][j][n];
        }
    }
}

void statecpy(int** a,int** b)
{
    for(int i = 0;i < M;i++){
        for(int j = 0;j < N;j++)
            a[i][j] = b[i][j];
    }
}
int checkAdd(int*** a, int** b, int n)
{
    for(int i = 0;i < n;i ++){
        if(isEqual(a,b,i)) return i;
    }
    return -1;
}

int min(int F[maxState], bool oc[maxState], int n) {
    int mId = -1;
    for (int i = 0; i < n; i++) {
        if (oc[i]) {
            if ((mId == -1) || (F[i] < F[mId])) {
                mId = i;
            }
        }
    }
    return mId;
}


int Astar(int*** a, int** start, int** target, int path[maxState]) {

    bool open[maxState] = { false };
    bool close[maxState] = { false };

    int F_[maxState] = { 0 };
    int G_[maxState] = { 0 };

    int** CurMat = new int*[M];
    for(int i = 0; i < M; i++){
        CurMat[i] = new int[N];
    }
    for(int o = 0; o < M; o++){
        for(int q = 0; q < N; q++){
            CurMat[o][q] = 0;
        }
    }

    statecpy(CurMat, start);	//初始状态
    int Id = 0, curId = 0;

    //记f = h
    F_[Id] = evalute(CurMat, target);

    //放入open表
    open[Id] = true;

    statecpy(a, start, Id);
    Id++;

    while (true) {
        int cId = min(F_, open, Id);
        if (cId != -1) {
            open[cId] = false;
            close[cId] = true;
        }
        curId = cId;
        getState(a, CurMat, curId);

        if (isEqual(a, target, cId)) {	//成功
            delete [] CurMat;
            return curId;
        }

        for (int i = 1; i < 5; i++) {   //向四周找方向
            int** suc = new int*[M];	//临时状态SUC
            for(int p = 0; p < M; p++){
                suc[p] = new int[N];
            }
            if (move(CurMat, suc, i)) {	//利用move函数进行移动
                int g_suc = G_[curId] + 1;
                int if_ex = checkAdd(a, suc, Id);
                if (if_ex == -1) {	//不存在表中
                    statecpy(a, suc, Id);
                    F_[Id] = evalute(suc, target) + g_suc;
                    open[Id] = true;
                    path[Id] = curId;
                    Id++;
                }
                else {	//已存在
                    if ((open[if_ex] == true) || (close[if_ex] == true)) {
                        if (g_suc < G_[if_ex]) {
                            G_[if_ex] = g_suc;
                            F_[if_ex] = g_suc + evalute(suc, target);
                            path[if_ex] = curId;
                        }
                        else {
                            //open[if_ex] = true;
                            F_[if_ex] = evalute(suc, target) + g_suc;
                        }
                    }
                    else {
                        open[if_ex] = true;
                        F_[if_ex] = evalute(suc, target) + g_suc;
                    }
                }
            }
            delete [] suc;
        }
        if (Id >= maxState) {
            no_space = true;
            delete [] CurMat;
            return -1;
        }
    }
}

void show(int*** a,int n)
{
    for(int i = 0;i < M;i ++){
        for(int j =0;j < N;j ++){
            cout << a[i][j][n] << " ";
        }
        cout << endl;
    }
    return;
}

//计算逆序数
int calDe(int** a)
{
    int sum = 0;
    for(int i = 0; i < M*N; i++){
        for(int j = i+1; j < M*N ;j++){
            int m, n, c, d;
            m = i / N;
            n = i % N;
            c = j / N;
            d = j % N;
            if(a[c][d] == 0)
                continue;
            if(a[m][n] > a[c][d])
                sum ++;
        }
    }
    return sum;
}

//计算两个状态之间是否可解
bool if_can_be_solved(int** a, int** b){
    int x = 0, y = 0;
    for (int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++){
            if(a[i][j] == 0){
                x = i;
            }
            if(b[i][j] == 0){
                y = i;
            }
        }
    }
    if((abs(calDe(a) - calDe(b)) + abs(y - x)) % 2 == 0){
        return true;
    }
    return false;
}

void autoGenerate(int** a)
{
    int maxMove = 50;
    srand((unsigned)time(NULL));
    int** tmp = new int*[M];
    for (int i = 0; i < M; i++) {
        tmp[i] = new int[N];
    }
    while(maxMove --){
        int dir = rand()%4 + 1;
        if(move(a,tmp,dir))
            statecpy(a,tmp);
    }
    delete [] tmp;
}

//初始化状态
bool Init_StartState(int** a, QString str1) {
    //cout << "Please initial:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = str1.mid(i*3+j, 1).toInt();
        }
    }
    return true;
}

//搜索路径
bool Search_Route(){
    if(!if_can_be_solved(start_state, target_state)){
        return false;
    }
    srch_time = 0;
    clock_t st_t = 0, fi_t = 0;
    st_t = clock();
    res_ = Astar(all_state, start_state, target_state, path_);
    fi_t = clock();
    srch_time = double(fi_t - st_t) / CLOCKS_PER_SEC;
    if(res_ == -1){
        return false;
    }

    index = 0;
    step_num = 0;
    while(res_ != 0){
        sh_route[index++] = res_;
        res_ = path_[res_];
        step_num++;
    }

    return true;
}

//延迟函数，用于路径显示
void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//将数字转为QString以输出
QString Num2str(int n){
    QString st;
    if(n == 0){
        st = " ";
    }
    else{
        st = QString::number(n);
    }
    return st;
}

//修改M、N
void change_dims(int m, int n){
    M = m;
    N = n;
    delete [] all_state;
    delete [] start_state;
    delete [] target_state;

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
}

void init_all(){
    path_[maxState] = {0};
    res_ = -1;

    sh_route[maxState] = {0};
    index = 0;
    step_num = 0;
    srch_time = 0;
}
