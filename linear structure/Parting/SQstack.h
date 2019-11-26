#ifndef _SqStack_
#define _SqStack_

//顺序栈结构
struct SqStack
{
    ElemType *base;
    int top[2]; //双栈栈顶的位置
    int size;
};

//栈的初始化，分配m个结点的顺序空间，构造一个空的顺序栈
void InitSqStack(SqStack &s, int m)
{
    s.top[0] = 0;
    s.top[1] = m - 1;
    s.base = new ElemType[m]; //new分配内存失败，默认会抛出异常的
    s.size = m;
}

//栈销毁
void DestroySqStack(SqStack &s)
{
    delete[] s.base;
    s.top[0] = 0;
    s.top[1] = 0;
    s.size = 0;
}

//判断栈是否满
bool SqStackFull(SqStack &s)
{
    return (s.top[0] > s.top[1]);
}

//判别栈是否为空
bool SqStackEmpty(SqStack s, int i = 0)
{
    if (i == 0)
    {
        return s.top[0] == 0;
    }
    else if (i == 1)
    {
        return s.top[1] == s.size - 1;
    }
    else
    {
        return false;
    }
}

//求栈中元素个数
int SqStackLength(SqStack s, int i = 0)
{
    if (i == 0)
    {
        return s.top[0];
    }
    else if (i == 1)
    {
        return s.size - 1 - s.top[1];
    }
    else
    {
        return -1;
    }
}

//取栈顶元素的值。先决条件是栈不空。
bool GetTop(SqStack s, ElemType &e, int i = 0)
{
    if (i == 0 && SqStackEmpty(s))
    {
        e = s.base[s.top[0] - 1];
        return true;
    }
    else if (i == 1 && SqStackEmpty(s, 1))
    {
        e = s.base[s.top[1] + 1];
        return true;
    }

    else
        return false;
}

//入栈，插入e到栈顶.先决条件栈不满。
void PushSqStack(SqStack &s, ElemType e, int i = 0)
{
    if (i == 0 && !SqStackFull(s))
    {
        s.base[s.top[0]++] = e;
    }
    else if (i == 1 && !SqStackFull(s))
    {
        s.base[s.top[1]--] = e;
    }
}

//出栈,先决条件是栈非空。
bool PopSqStack(SqStack &s, ElemType &e, int i = 0)
{
    if (SqStackEmpty(s, i))
    {
        return false;
    }
    else if (i == 0)
    {
        e = s.base[--s.top[0]];
    }
    else if (i == 1)
    {
        e = s.base[++s.top[1]];
    }
    return true;
}

#endif
