#include "global.h"

int M = 3;
int N = 3;

int*** all_state = nullptr;
int** start_state = nullptr;
int** target_state = nullptr;

int path_[maxState] = {0};
int res_ = -1;

int sh_route[maxState] = {0};
int index = 0;

bool no_space = false;
int step_num = 0;
double srch_time = 0;
