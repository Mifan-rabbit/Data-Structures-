#include <iostream>
using namespace std;
#include "course.h"

int main()
{
    int command = 0, vexnum, arcnum;
    cout << "请输入学期总数： ";
    cin >> term_num;
    cout << "请输入学分上限： ";
    cin >> credit_limit;
    cout << "请输入课程总数: ";
    cin >> vexnum;
    cout << "请输入先修关系总数： ";
    cin >> arcnum;
    ALGraph G;
    Create_classGraph(G, vexnum, arcnum);
    if (JUDGEMENT(G))
    {
        cout << "\n请选择排课模式：\n[0、结束排课; 1、学生的课程学习在学分上限限制下尽可能集中在前几个学期；2：学生在每个学期负担尽量均匀；]\n\n";
        while (cin >> command)
        {
            if (command == 0)
                break;
            else if (command == 1)
                course_scheduling(G, 0);
            else if (command == 2)
                if (able_averge)
                {
                    course_scheduling(G, 1);
                }
                else
                {
                    cout << "根据培养计划，无法平均安排课程！";
                }
            else
                cout << "命令错误!\n";
        }
    }
    else
    {
        cout << "排课失败\n";
    }
    DestroyGraph(G);
    system("PAUSE");
}
