#include <iostream>
using namespace std;

//数据元素类型 ：位置、密码
struct Elemtype
{
    int location;
    int password;
};

#include "DuCycleList.h"

//打印位置、密码
void Print(Elemtype &e)
{
    cout << "位置：" << e.location << "密码：" << e.password << endl;
}

void Ysfring(DuCyclelist &L, int n, int m)
{
    Elemtype e;
    int now = L.len, num = 1;
    while (n > 0)
    {
        now = (now + m) % n;
        if (now == 0)
            now = n;
        listDelete(L, now, e);
        cout << endl
             << "第" << num++ << "个出列的位序是：" << e.location;
        m = e.password;
        --now;
        --n;
    }
    L.head = L.tail = nullptr;
}
int main()
{
    DuCyclelist L;
    initList(L);
    int n, m;
    Elemtype e;
    cout << "《约瑟夫环》" << endl;
    do
    {
        cout << endl
             << "请输入人数： ";
        cin >> n;
    } while (n < 1);
    for (int i = 1; i <= n; i++)
    {
        cout << "请输入第" << i << "人密码：";
        cin >> e.password;
        e.location = i;
        listAppend(L, e);
    }
    cout << endl
         << "当前双向循环链表中的元素依次为：" << endl
         << endl;
    listTraverse(L, Print);
    cout << endl
         << "请输入初始密码：";
    cin >> m;
    Ysfring(L, n, m);
    cout << endl
         << endl;
    system("PAUSE");
    return 0;
}
