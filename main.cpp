//
//  main.cpp
//  A*With8Num
//
//  Created by 李子琛 on 16/11/23.
//  Copyright © 2016年 李子琛. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "A_star.h"

using namespace std;

int main() {
    State* Open = (State*)malloc(sizeof(State));
    State* Close = (State*)malloc(sizeof(State));
    Open->Next = NULL;
    Open->Pre = NULL;
    Close->Next = NULL;
    Close->Pre = NULL;
    cout<<"请选择搜索的估值函数类型："<<endl;
    cout<<"1. 八数码不在位数"<<endl;
    cout<<"2. 八数码当前各位与正确位距离之和"<<endl;
    cout<<"3. 无估值函数（宽度优先搜索）"<<endl;
    cout<<"输入估值函数类型编号：";
    int flag;
    cin>>flag;
    Core_Algorithm(Open, Close,flag);
    cout << "程序耗时：" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;
    return 0;
}
















