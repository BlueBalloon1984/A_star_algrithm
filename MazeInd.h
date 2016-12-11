//
//  MazeInd.h
//  A*With8Num
//
//  Created by 李子琛 on 16/12/11.
//  Copyright © 2016年 李子琛. All rights reserved.
//

#ifndef MazeInd_h
#define MazeInd_h
#include "DataStruct.h"
using namespace std;

int wrong_sum1(int s[3][3])
{int sum = 0;
    
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            if(final[i][j] != s[i][j])
                sum++;
        }
    }
    return sum;
}

int wrong_sum2(int s[3][3])
{int sum = 0;
    int i,j,fi,fj;
    for( i = 0;i<3;i++)
        for( j = 0;j<3;j++)
        {
            for(fi = 0;fi<3;fi++)
                for(fj = 0;fj<3;fj++)
                {
                    if(final[fi][fj] == s[i][j])
                    {
                        sum+=abs(i-fi)+abs(j-fj);
                        
                    }
                }
        }
    
    return sum;
}

int wrong_sum3(int s[3][3])
{int sum = 0;
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


#endif /* MazeInd_h */
