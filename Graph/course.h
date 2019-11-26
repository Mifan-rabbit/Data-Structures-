#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <math.h>
#define MAX_CLASS_NUM 100
#define MAX_TERM_NUM 12    //最大学期数
#define MAX_CREDIT_NUM 100 //最大学分数

struct VElemType
{
    string name;    //课程名
    string classID; //课程代号
    int credit;     //学分
    int late;       //最晚学习时间
};
typedef string dataElem;
#include "graph.h"

int all_credit;             //总学分
int the_term[MAX_TERM_NUM]; //记录每学期要修的学分
bool able_averge;           //能否平均分配课程
int averge_credit;          //每门课的平均学分
int mean_square;            //学分均方差
int term_num;
int credit_limit;

//求两个数中的最大值
int max(int a, int b)
{
    return a > b ? a : b;
}

//求数组中的最小值
int min(int n, int *ve)
{
    int minst = MAX_TERM_NUM;
    for (int i = 0; i < n; i++)
    {
        if (ve[i] < minst)
            minst = ve[i];
    }
    return minst;
}

//计算每学期学分
void sum_per_term_credit(ALGraph &G)
{
    VElemType temp;
    for (int i = 0; i < get_vexnum(G); i++)
    {
        the_term[ve[i] - 1] += get_vexdata(G, i).credit;
    }
}

//计算学分方差
void sum_up_mean_square(ALGraph &G)
{
    averge_credit = all_credit / get_vexnum(G);
    mean_square = 0;
    for (int i = 0; i < get_vexnum(G); i++)
    {
        mean_square += (get_vexdata(G, i).credit - averge_credit) * (get_vexdata(G, i).credit - averge_credit);
    }
    mean_square = sqrt(mean_square);
}

//判断课程代号是否相同
bool identical(VElemType &u, string &v)
{
    return (u.classID == v);
}

//输入课程相关信息
void set_vexinfo(ALGraph &G, int i)
{
    VElemType temp = get_vexdata(G, i);
    cin >> temp.name;    //课程名
    cin >> temp.classID; //课程号
    cin >> temp.credit;  //该课程学分
    set_vexdata(G, i, temp);
    all_credit += temp.credit;
    set_firstin(G, i, nullptr);
    set_firstout(G, i, nullptr);
}
// 关于能否排课的判断
bool JUDGEMENT(ALGraph &G)
{
    LONGEST_PATH = term_num;
    if (all_credit > credit_limit * term_num || !TopologicalOrder(G))
    {
        return false;
    }
    int min_term = min(get_vexnum(G), ve);
    if (min_term < 1)
    {
        return false;
    }
    for (int i = 0; i < get_vexnum(G); i++)
    {
        VElemType temp = get_vexdata(G, i);
        temp.late = ve[i];
        set_vexdata(G, i, temp);
    }
    sum_per_term_credit(G);
    if (min_term == 1)
    {
        able_averge = false;
        for (int i = 0; i < term_num; i++) //考虑学期数够，但部分学期超学分
        {
            if (the_term[i] > credit_limit)
            {
                return false;
            }
        }
    }
    sort(G.list, G.list + get_vexnum(G), [](VexNode v1, VexNode v2) { return v1.data.late < v2.data.late; }); //将课程按最迟结束时间排序
    return true;
}

//背包模型，充分利用每学期的学分，并把课程安排记录在study中
void my_pack(ALGraph &G, int now_credit_limit, vector<int> &able_study, vector<int> &study)
{
    int status[MAX_CLASS_NUM][MAX_CREDIT_NUM] = {0}, max_credit = 0;
    for (int i = get_vexdata(G, able_study[0]).credit; i <= now_credit_limit; i++)
    {
        status[0][i] = get_vexdata(G, able_study[0]).credit; //初始化第一行
    }
    for (int i = 1; i < able_study.size(); i++)
    {
        for (int j = 0; j <= now_credit_limit; j++)
        {
            if (j - get_vexdata(G, able_study[i]).credit >= 0)
            {
                status[i][j] = max(status[i - 1][j], (status[i - 1][j - get_vexdata(G, able_study[i]).credit] + get_vexdata(G, able_study[i]).credit));
                max_credit = max(max_credit, status[i][j]);
            }
            else
            {
                status[i][j] = status[i - 1][j];
            }
        }
    }
    for (int i = able_study.size() - 1; i >= 0 && max_credit > 0; i--)
    {
        if (status[i][max_credit] != status[i - 1][max_credit])
        {
            max_credit -= get_vexdata(G, able_study[i]).credit;
            study.push_back(able_study[i]);
        }
    }
}

//排课
void course_scheduling(ALGraph &G, int command)
{
    vector<int> able_study; //记录本学期能上的课
    vector<int> study;      //记录本学期要上的课
    int j, indegree[MAX_CLASS_NUM], c[2] = {credit_limit, (all_credit + mean_square) / term_num + (((all_credit + mean_square) % term_num) != 0)};
    FindInDegree(G, indegree);
    for (int i = 0; i < term_num; i++)
    {
        for (int k = 0; k < get_vexnum(G); k++) //记录本学期可以修读的课
        {
            if (indegree[k] == 0)
            {
                able_study.push_back(k);
            }
        }

        if (able_study.empty())
        {
            cout << "第" << i + 1 << "学期无课程安排!";
        }
        else
        {
            cout << "第" << i + 1 << "学期需要学习的课程为： \n";
            my_pack(G, c[command], able_study, study); //查找本学期要读的课
            able_study.clear();
            while (!study.empty())
            {
                j = study.back();
                study.pop_back();
                indegree[j] = -1;                                                               //防止重复入栈
                cout << get_vexdata(G, j).name << "(" << get_vexdata(G, j).credit << "学分)\t"; //输出课程名与学分
                for (ArcBox *p = G.list[j].firstout; p; p = p->tailnext)
                    --indegree[LocateVex(G, p->head)];
            }
        }
        if (i == term_num - 1)
        {
            for (int k = 0; k < get_vexnum(G); k++) //若均分，最后一学期可能超平均学分输出
            {
                if (indegree[k] != -1)
                {
                    cout << get_vexdata(G, k).name << "(" << get_vexdata(G, j).credit << "学分)\t"; //输出课程名与学分
                }
            }
        }
        cout << "\n\n";
    }
}

//构造课程专属图
void Create_classGraph(ALGraph &G, int vexnum, int arcnum)
{
    for (int i = 0; i < MAX_TERM_NUM; i++)
        the_term[MAX_TERM_NUM] = 0; //初始化每学期要修的学分
    able_averge = true;
    all_credit = 0;
    CreateGraph(G, vexnum, arcnum, "\n请输入课程名称，课程代号，课程学分。\n", "\n请输入有先修关系的两门课。");
    sum_up_mean_square(G);
}

