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

using namespace std;

struct State
{
    int s[3][3];//八数码状态
    int f,g;    //启发函数值
    struct State* Next;
    struct State* Pre;
};

//Open列表中的节点数目
int open_N = 0;

//定义八数码初态
int init[3][3]=
{
    2,8,3,
    1,6,4,
    0,7,5
};

//八数码终态值
int final[3][3]
{
    1,2,3,
    8,0,4,
    7,6,5
};

//添加节点函数
void Add_State(State* head,State* p)
{
    State* q;
    if(head->Next)//列表非空
    {
        q=head->Next;
        if(p->f < head->Next->f)//若插入的节点估值较小
        {
            //p变为头结点
            p->Next=head->Next;
            head->Next=p;
        }
        else{
            //寻找适当位置插入
            while (q->Next) {
                if((q->f < p->f ||q->f == p->f) && (q->Next->f > p->f || q->Next->f == p->f))
                {
                    p->Next = q->Next;
                    q->Next = p;
                    break;
                }
                q = q->Next;
            }
            //插到屁股上去
            if(q->Next == NULL) q->Next = p;
        }
        
    }
    else
    {
        head->Next = p;
    }
}

void Delete_State(State * head,State * p)
{
    State * q;
    q = head;
    while(q->Next)
    {
        if(q->Next == p)
        {
            q->Next = p->Next;
            p->Next = NULL;
            if(q->Next == NULL)
                return;
        }
        q = q->Next;
    }
}

int equal_State(int s1[3][3],int s2[3][3])
{
    int i,j,flag = 0;
    for(i = 0;i<3;i++)
        for(j=0;j<3;j++)
        {
            if(s1[i][j] != s2[i][j])
            {
                flag = 1;break;
            }
        }
    if(!flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//判断后继结点是否存在
int exit_State(State* head, int s[3][3],State* Old_State)
{
    State* q = head->Next;
    int flag = 0;
    while(q)
    {
        if(equal_State(q->s, s))
        {
            flag = 1;
            Old_State->Next = q;
            return 1;
        }
        else
        {
            q = q->Next;
        }
        
    }
    if(!flag)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

//计算放错位的数码与正确位置的距离之和
int wrong_sum(int s[3][3])
{
    int i,j,fi,fj,sum = 0;
    for( i = 0;i<3;i++)
        for( j = 0;j<3;j++)
        {
            for(fi = 0;fi<3;fi++)
                for(fj = 0;fj<3;fj++)
                {
                    if(final[fi][fj] == s[i][j])
                    {
                        sum+=abs(i-fi)+abs(j-fj);
                        break;
                    }
                }
        }
    return sum;
}

//检查节点移动合法性，若合法则得到后继节点
int move_success(State* BestState,int direction,State* Successor)
{
    int i,j,ii = 0,jj = 0,temp;
    for(i = 0;i<3;i++)
        for(j = 0;j<3;j++)
        {
            Successor->s[i][j] = BestState->s[i][j];
        }
    //获取空格位置
    for(i = 0;i<3;i++)
        for(j = 0;j<3;j++)
        {
            if(BestState->s[i][j] == 0)
            {
                ii = i;
                jj = j;
                break;
            }
        }
    switch (direction) {
        case 0:
            if((ii-1)>-1)
            {
                temp = Successor->s[ii][jj];
                Successor->s[ii][jj] = Successor->s[ii-1][jj];
                Successor->s[ii-1][jj] = temp;
                return 1;
            }
            else
            {
                return 0;
            }
            break;
            
        case 1:
            if((jj-1)>-1)
            {
                temp = Successor->s[ii][jj];
                Successor->s[ii][jj] = Successor->s[ii][jj-1];
                Successor->s[ii][jj-1] = temp;
                return 1;
            }
            else
            {
                return 0;
            }
            break;
            
        case 2:
            if((jj+1)<3)
            {
                temp = Successor->s[ii][jj];
                Successor->s[ii][jj] = Successor->s[ii][jj+1];
                Successor->s[ii][jj+1] = temp;
                return 1;
            }
            else
            {
                return 0;
            }
            break;
            
        case 3:
            if((ii+1)<3)
            {
                temp = Successor->s[ii][jj];
                Successor->s[ii][jj] = Successor->s[ii+1][jj];
                Successor->s[ii+1][jj] = temp;
                return 1;
            }
            else
            {
                return 0;
            }
            break;
            
        default:
            return 0;
            break;
    }
}

//从Open列表中找最佳节点
State* get_BestNode(State* Open)
{
    return Open->Next;
}

//输出最佳路径
void print(State* head)
{
    State* q,*q1,*p;
    int i,j,count = 1;
    p = (struct State*)malloc(sizeof(State));
    
    //头插法变更节点输出次序
    p->Pre = NULL;
    q = head;
    while (q) {
        q1 = q-> Pre;
        q->Pre = p->Pre;
        p->Pre = q;
        q = q1;
    }
    q = p->Pre;
    while (q) {
        if (q == p->Pre) {
            cout<<"八数码初始态："<<endl;
        }
        else
        {
            if (q->Pre == NULL) {
                cout<<"八数码目标态："<<endl;
            }
            else
            {
                int counter = count++;
                cout<<"八数码中间态"<<counter<<"："<<endl;
            }
        }
        
        for (i = 0; i<3; i++) {
            for (j = 0; j<3; j++) {
                cout<<q->s[i][j];
                if( j == 2) cout<<endl;
            }
        }
        
        cout<<"f = "<<q->f<<"g = "<<q->g<<endl;
        q = q->Pre;
    }
}

//A*处理后积极点
void sub_A(State * Open,State* BestState,State* Closed,State* Successor)
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
            Old_State->Next->f = Old_State->g+wrong_sum(Old_State->s);
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
                Old_State->Next->f = Old_State->g+wrong_sum(Old_State->s);
                //将old节点按照正确顺序放入open表中
                Delete_State(Open, Old_State);
                Add_State(Open, Old_State);
            }
        }
        else
        {
            Successor->f = Successor->g + wrong_sum(Successor->s);
            Add_State(Open, Successor);
            open_N++;
        }
    }
}

//A*算法
void Core_Algorithm(State* Open,State* Closed)
{
    int i,j;
    State *BestNode,*initial,*Successor;
    
    initial = (State*)malloc(sizeof(State));
    
    //初始化节点
    for(i = 0;i<3;i++)
        for(j = 0;j<3;j++)
            initial->s[i][j] = init[i][j];
    
    initial->f = wrong_sum(init);
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
                    sub_A(Open, BestNode, Closed, Successor);
                }
                
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 1, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor);
                }
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 2, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor);
                }
                Successor = (State*)malloc(sizeof(State));
                Successor->Next = NULL;
                if (move_success(BestNode, 3, Successor)) {
                    sub_A(Open, BestNode, Closed, Successor);
                }
                
                
            }
            
        }
    }
}

int main() {
    State* Open = (State*)malloc(sizeof(State));
    State* Close = (State*)malloc(sizeof(State));
    Open->Next = NULL;
    Open->Pre = NULL;
    Close->Next = NULL;
    Close->Pre = NULL;
    Core_Algorithm(Open, Close);
    return 0;
}
















