//
//  A_star.h
//  A*With8Num
//
//  Created by 李子琛 on 16/12/11.
//  Copyright © 2016年 李子琛. All rights reserved.
//

#ifndef A_star_h
#define A_star_h
#include "DataStruct.h"
#include "MazeInd.h"
//A*处理后积极点
void sub_A(State * Open,State* BestState,State* Closed,State* Successor,int flag)
{
    State* Old_State = (State*)malloc(sizeof(State));
    //将当前节点设为BestState的后继节点
    Successor->Pre = BestState;
    //计算后继节点G值
    Successor->g = BestState->g+1;
    //如果当前节点存在于open表中
    if (exit_State(Open, Successor->s, Old_State)) {
        //如果新的路径更优
        if(Successor->g < Old_State->g)
        {
            //Old_State的父节点更改为BestState,修改f，g值
            Old_State->Next->Pre = BestState;
            Old_State->Next->g = Successor->g;
            
            if (flag == 1) {
                Old_State->Next->f = Old_State->g+wrong_sum1(Old_State->s);
            } else {
                if (flag == 2) {
                    Old_State->Next->f = Old_State->g+wrong_sum2(Old_State->s);
                } else {
                    Old_State->Next->f = Old_State->g+wrong_sum3(Old_State->s);
                }
            }
            
            //将old节点按照正确顺序放入open表中
            Delete_State(Open, Old_State);
            Add_State(Open, Old_State);
        }
    }
    else
    {
        //如果当前节点存在于Close表中
        if (exit_State(Closed, Successor->s, Old_State)) {
            //如果新的路径更优
            if(Successor->g < Old_State->g)
            {
                //Old_State的父节点更改为BestState,修改f，g值
                Old_State->Next->Pre = BestState;
                Old_State->Next->g = Successor->g;

                if (flag == 1) {
                    Old_State->Next->f = Old_State->g+wrong_sum1(Old_State->s);
                } else {
                    if (flag == 2) {
                        Old_State->Next->f = Old_State->g+wrong_sum2(Old_State->s);
                    } else {
                        Old_State->Next->f = Old_State->g+wrong_sum3(Old_State->s);
                    }
                }
                
                //将old节点按照正确顺序放入open表中
                Delete_State(Open, Old_State);
                Add_State(Open, Old_State);
            }
        }
        else
        {
            
            if (flag == 1) {
                Successor->f = Successor->g + wrong_sum1(Successor->s);
            } else {
                if (flag == 2) {
                    Successor->f = Successor->g + wrong_sum2(Successor->s);
                } else {
                    Successor->f = Successor->g + wrong_sum3(Successor->s);
                }
            }
            Add_State(Open, Successor);
            open_N++;
        }
    }
}

//A*算法
void Core_Algorithm(State* Open,State* Closed,int flag)
{
    int i,j;
    State *BestNode,*initial,*Successor;
    
    initial = (State*)malloc(sizeof(State));
    
    //初始化节点
    for(i = 0;i<3;i++)
        for(j = 0;j<3;j++)
            initial->s[i][j] = init[i][j];
    
    if (flag == 1) {
        initial->f = wrong_sum1(init);
    } else {
        if (flag == 2) {
            initial->f = wrong_sum2(init);
        } else {
            initial->f = wrong_sum3(init);
        }
    }
    initial->g = 0;
    initial->Pre = NULL;
    initial->Next = NULL;
    
    Add_State(Open, initial);
    open_N++;
    while (1)
    {
        if (open_N == 0) {
            cout<<"失败"<<endl;
            return ;
        }
        else
        {
            //将Open表f值最小的加入Close表
            BestNode = get_BestNode(Open);
            Delete_State(Open, BestNode);
            open_N--;
            Add_State(Closed, BestNode);
            
            //如果搜索完结
            if(equal_State(BestNode->s, final))
            {
                cout<<"成功"<<endl;
                print(BestNode);
                return;
            }
            //否则，进行棋子移动
            else
            {
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 0, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor,flag);
                }
                
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 1, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor,flag);
                }
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 2, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor,flag);
                }
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 3, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor,flag);
                }
                
                
            }
            
        }
    }
}

#endif /* A_star_h */
