#include <iostream>
using namespace std;

int n, present = 0;
//汽车数据类型
struct ElemType
{
    int id;
    int time;
    char type;
};
#include "SqStack.h"
#include "LinkQueue.h"

//报车辆类型(A代表小汽车，B代表客车，C代表卡车)
void car_type(char c)
{
    switch (c)
    {
    case 'A':
        cout << "小汽车";
        break;
    case 'B':
        cout << "客车";
        break;
    case 'C':
        cout << "卡车";
        break;
    default:
        break;
    }
}

//在便道里寻找某车，若存在则，返回其位置,并驶离便道。此时排在它前面的汽车要先开走让路，然后再依次排到队尾
int isInShortcut(int time, int id, char type, LinkQueue &Q)
{
    int pos = 1;
    ElemType temporary_car;
    for (pos; pos <= QueueLength(Q); pos++)
    {
        DeQueue(Q, temporary_car);
        if (temporary_car.id == id && temporary_car.type == type)
        {
            break;
        }
        EnQueue(Q, temporary_car);
    }
    if (pos == QueueLength(Q) + 1)
    {
        return -1;
    }
    else
    {
        car_type(type);
        cout << id << "号汽车出便道" << pos << "\n在便道停留时间: " << time - temporary_car.time << endl
             << endl;
        return pos;
    }
}

//模拟汽车入停车场，若停车场满，汽车进入便道等待
void Enter(ElemType &e, SqStack &s, LinkQueue &Q)
{
    if (s.top[0] >= s.size - 1 || present + e.type - 'A' + 1 > n || !QueueEmpty(Q))
    {
        EnQueue(Q, e);
        car_type(e.type);
        cout << e.id << "号汽车进入便道\n"
             << "进入便道时间: " << e.time << "\n便道位置: " << QueueLength(Q) << endl
             << endl;
    }
    else
    {
        PushSqStack(s, e);
        car_type(e.type);
        present += e.type - 'A' + 1;
        cout << e.id << "号汽车进入停车场\n"
             << "进入停车场时间: " << e.time << "\n停车位置: " << SqStackLength(s) << endl
             << endl;
    }
}
//模拟汽车驶出停车场，若便道有汽车等待，便道中的第一辆车停入停车场
void departure(int n, int id, char type, int time, SqStack &s, LinkQueue &Q)
{
    ElemType temporary_car;
    while (PopSqStack(s, temporary_car))
    {
        if (temporary_car.id == id && temporary_car.type == type)
        {
            break;
        }
        PushSqStack(s, temporary_car, 1);
    }
    if (temporary_car.id == id && temporary_car.type == type)
    {
        car_type(temporary_car.type);
        present = present - temporary_car.type + 'A' - 1;
        cout << temporary_car.id << "号汽车出停车场\n停车场停留时间: " << time - temporary_car.time << "\n应该缴纳的费用(单价: 5): " << 5 * (time - temporary_car.time) << endl
             << endl;
        while (!SqStackEmpty(s, 1)) //将临时停车场里的车停回停车场
        {
            PopSqStack(s, temporary_car, 1);
            PushSqStack(s, temporary_car);
        }
        while (GetHead(Q, temporary_car) && present + temporary_car.type - 'A' + 1 <= n)
        {
            DeQueue(Q, temporary_car);
            temporary_car.time = time;
            //车进入停车场
            PushSqStack(s, temporary_car);
            car_type(temporary_car.type);
            present += temporary_car.type - 'A' + 1;
            cout << temporary_car.id << "号汽车进入停车场\n"
                 << "进入停车场时间: " << temporary_car.time << "\n停车位置: " << SqStackLength(s) << endl
                 << endl;
        }
    }
    else if (isInShortcut(time, id, type, Q) == -1)
    {
        cout << "请输入正确的车牌号码\n";
    }

    while (!SqStackEmpty(s, 1))
    {
        PopSqStack(s, temporary_car, 1);
        PushSqStack(s, temporary_car);
    }
}

int main()
{
    //获取可停放汽车数量
    cout << "输入狭长通道可停放汽车数量: ";
    cin >> n;

    //停车场初始化
    SqStack park;
    InitSqStack(park, n + 1);

    //便道初始化
    LinkQueue shortcut;
    InitQueue(shortcut);

    //声明临时变量
    char command, temp_type;
    int temp_id, temp_time;
    ElemType temp_car;

    cout << "请输入数据（A：汽车到达；D：汽车离去；E：结束）| 汽车ID | 当前时间 | 车辆类型(A代表小汽车，B代表客车，C代表卡车)\n";

    while (cin >> command >> temp_id >> temp_time >> temp_type)
    {

        if (command == 'E')
            break;
        else if (command == 'A') /*汽车到达*/
        {
            temp_car.id = temp_id;
            temp_car.time = temp_time;
            temp_car.type = temp_type;
            Enter(temp_car, park, shortcut);
        }
        else if (command == 'D') /*汽车离去*/
        {
            departure(n, temp_id, temp_type, temp_time, park, shortcut);
        }
    }
    system("pause");
    return 0;
}

