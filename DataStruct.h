//
//  DataStruct.h
//  A*With8Num
//
//  Created by 李子琛 on 16/12/11.
//  Copyright © 2016年 李子琛. All rights reserved.
//

#ifndef DataStruct_h
#define DataStruct_h

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
    1,0,4,
    2,3,5,
    8,7,6
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



#endif /* DataStruct_h */
