#ifndef _DuCycleList_
#define _DuCycleList_

//结点结构
struct DCNode
{
    Elemtype data;
    DCNode *prior;
    DCNode *next;
};

//不带头节点的双向循环链表结构
struct DuCyclelist
{
    struct DCNode *head;
    struct DCNode *tail;
    int len;
};

//不带头节点的双向循环链表初始化
void initList(DuCyclelist &L)
{
    L.head = L.tail = nullptr;
    L.len = 0;
}

//判断不带头结点的双向循环链表是否为空表，空表返回TRUE
bool listEmpty(DuCyclelist &L)
{
    return (L.len == 0);
}

//释放不带头结点的双向循环链表中的所有数据点
void clearList(DuCyclelist &L)
{
    DCNode *q;
    while (L.len--)
    {
        q = L.head->next;
        delete L.head;
        L.head = q;
    }
    L.head = L.tail = nullptr;
}

//销毁不带头节点的双向循环单链表
void destroy(DuCyclelist &L)
{
    clearList(L);
}

//求不带头结点的双向循环单链表长度
int listLength(DuCyclelist &L)
{
    return L.len;
}

//取不带头节点的双向循环链表第i个结点的地址,用p返回
bool LocateI(DuCyclelist &L, int i, DCNode *&p)
{
    if (i < 1 || i > L.len)
        return false;
    int k;
    if (i <= L.len / 2)
    {
        k = 1;
        p = L.head;
        while (p && k < i)
        {
            p = p->next;
            ++k;
        }
    }
    else
    {
        k = L.len;
        p = L.tail;
        while (p && k > i)
        {
            p = p->prior;
            --k;
        }
    }
    return true;
}

//取不带头节点的双向循环链表第i个结点的值
bool getElem(DuCyclelist &L, Elemtype &e, int i)
{
    DCNode *p = nullptr;
    LocateI(L, i, p);
    e = p->data;
    return true;
}

//在非空双向循环链表表尾插入一个结点
void listAppend(DuCyclelist &L, Elemtype e)
{
    DCNode *p = new DCNode;
    p->data = e;
    if (!L.head)
        L.head = L.tail = p;
    else
    {
        p->next = L.head;
        p->prior = L.tail;
        L.tail = L.head->prior = L.tail->next = p;
    }
    ++L.len;
}

//在不带头节点的双向循环链表中第i个数据元素之前插入新的数据元素e，可插在末尾。
bool listInsert(DuCyclelist &L, int i, Elemtype e)
{
    DCNode *p, *q;
    if (i < 1 || i > L.len + 1)
        return false; //插入位置i值不合法
    if (i == 1)
    {
        p = new DCNode;
        p->data = e;
        ++L.len;
        if (!L.head)
            L.head = L.tail = p;
        else //将p结点插入在表首
        {
            p->next = L.head;
            p->prior = L.tail;
            L.head = L.head->prior = L.tail->next = p;
        }
    }
    else
    {
        if (!L.head)
            return false;
        else
        {
            p = new DCNode;
            p->data = e;
        }

        if (i == L.len + 1)
        {
            L.tail = p;
        }
        else
        {
            LocateI(L, i - 1, q);
        }

        p->next = q->next;
        p->prior = q;
        q->next = q->next->prior = p;
        ++L.len;
    }
    return true;
}

// 在非空双向循环链表中删除第i个数据元素
bool listDelete(DuCyclelist &L, int i, Elemtype &e)
{
    DCNode *p;
    if (i == 1 && L.len > 0)
    {
        p = L.head;
        e = p->data;
        if (L.head == L.tail)
        {
            L.head = L.tail = nullptr;
        }
        else
        {
            L.tail->next = L.head = p->next;
            p->next->prior = L.tail;
        }
    }
    else
    {
        LocateI(L, i, p);
        p->next->prior = p->prior;
        p->prior->next = p->next;
        if (i == L.len)
        {
            L.tail = p->prior;
        }
    }
    e = p->data;
    delete p;
    --L.len;
    return true;
}

// 从第一个位置起查找与e匹配的数据元素，若存在则返回该数据元素的位置
int LocateElem(DuCyclelist &L, Elemtype &e, bool (*Compare)(Elemtype &e1, Elemtype &e2))
{
    if (!L.head)
        return false;
    int k = 1;
    DCNode *p = L.head;
    while (p != L.tail && !Compare(p->data, e))
    {
        k++;
        p = p->next;
    }
    if (Compare(p->data, e))
        return k;
    else
        return false;
}

// 依序对单链表中的每个数据元素进行遍历，遍历到每个数据元素时调用函数visit()一次且仅一次
void listTraverse(DuCyclelist &L, void (*Visit)(Elemtype &e))
{
    DCNode *p = L.head;
    if (p)
    {
        while (p != L.tail)
        {
            Visit(p->data);
            p = p->next;
        }
        Visit(p->data);
    }
}
#endif

