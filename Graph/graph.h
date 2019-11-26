#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stack>
#define MAX_VERTEX_NUM 100 //这里是课程数
int ve[MAX_VERTEX_NUM];
int LONGEST_PATH;

struct ArcBox // 弧结点
{
  dataElem head;
  dataElem tail;
  ArcBox *headnext;
  ArcBox *tailnext;
};

struct VexNode // 顶点结点
{
  VElemType data;
  ArcBox *firstout;
  ArcBox *firstin;
};

struct ALGraph
{
  VexNode list[MAX_VERTEX_NUM]; // 表头向量(数组)
  int vexnum, arcnum;           // 有向图的当前顶点数和弧数
};

void CreateGraph(ALGraph &G, int vexnum, int arcnum);  //采用十字链表存储表示，构造有向图G
void DestroyGraph(ALGraph &G);                         //销毁图G
bool InsertArc(ALGraph &G, dataElem v, dataElem w);    //插入弧
bool TopologicalOrder(ALGraph &G);                     //拓扑逆向排序
void set_vexinfo(ALGraph &G, int i);                   //输入顶点信息
bool identical(VElemType &u, dataElem &v);             //判断是否是同个顶点
int LocateVex(ALGraph G, dataElem u);                  //找到该顶点在图中的位置，若失败，返回-1
int get_vexnum(ALGraph &G);                            //获得顶点数
VElemType get_vexdata(ALGraph &G, int i);              //获得顶点数据
void set_vexdata(ALGraph &G, int i, VElemType temp);   //修改顶点数据
bool set_firstin(ALGraph &G, int i, ArcBox *temp);     //设置以顶点i为弧头的的第一个弧结点信息
bool set_firstout(ALGraph &G, int i, ArcBox *temp);    //设置以顶点i为弧尾的的第一个弧结点信息
void FindInDegree(const ALGraph &G, int indegree[]);   //获得入度
void FindOutDegree(const ALGraph &G, int outdegree[]); //获得出度

//采用十字链表存储表示，构造有向图G
void CreateGraph(ALGraph &G, int vexnum, int arcnum, string tips1 = "请输入顶点信息。\n", string tips2 = "请输入相邻的顶点。\n")
{
  dataElem v, w;
  G.vexnum = vexnum;
  G.arcnum = arcnum;
  cout << tips1; //输出提示信息
  for (int i = 0; i < G.vexnum; ++i)
  {
    G.list[i].firstout = G.list[i].firstin = nullptr;
    set_vexinfo(G, i);
  }
  cout << tips2; //输出提示信息
  for (int i = 0; i < G.arcnum; i++)
  {
    cin >> v >> w;
    InsertArc(G, v, w);
  }
}

//销毁图G
void DestroyGraph(ALGraph &G)
{
  int i;
  ArcBox *p, *q;
  for (i = 0; i < G.vexnum; ++i)
  {
    p = G.list[i].firstout;
    while (p)
    {
      q = p->tailnext;
      delete (p);
      p = q;
    }
    G.list[i].firstout = G.list[i].firstin = nullptr;
  }
  G.vexnum = 0;
  G.arcnum = 0;
}

//判断是否是同个顶点
bool identical(VElemType &u, dataElem &v);

//找到该顶点在图中的位置，若失败，返回-1
int LocateVex(ALGraph G, dataElem u)
{
  for (int i = 0; i < G.vexnum; ++i)
    if (identical(G.list[i].data, u))
      return i;
  return -1;
}

//获得顶点数
int get_vexnum(ALGraph &G)
{
  return G.vexnum;
}

//设置顶点数据
void set_vexdata(ALGraph &G, int i,VElemType temp)
{
  G.list[i].data = temp;
}

//得到顶点数据
VElemType get_vexdata(ALGraph &G, int i)
{
  return G.list[i].data;
}

//更改以该顶点为弧头的的第一个弧结点信息
bool set_firstin(ALGraph &G, int i, ArcBox *temp)
{
  if (i < G.vexnum && i > -1)
  {
    G.list[i].firstin = temp;
    return false;
  }
  else
  {
    return true;
  }
}

//更改以该顶点为弧尾的的第一个弧结点信息
bool set_firstout(ALGraph &G, int i, ArcBox *temp)
{
  if (i < G.vexnum && i > -1)
  {
    G.list[i].firstout = temp;
    return true;
  }
  else
  {
    return false;
  }
}

//插入弧
bool InsertArc(ALGraph &G, dataElem v, dataElem w)
{
  int i, j;
  i = LocateVex(G, v); // 弧尾或边的序号,即先修课
  j = LocateVex(G, w); // 弧头或边的序号
  if (i < 0 || j < 0)
    return false;
  ArcBox *p = new ArcBox;
  p->head = w;
  p->tail = v;
  p->tailnext = G.list[i].firstout;
  p->headnext = G.list[j].firstin;
  G.list[i].firstout = p;
  G.list[j].firstin = p;
  return true;
}

//获得入度
void FindInDegree(const ALGraph &G, int indegree[])
{
  int i;
  ArcBox *p;
  for (i = 0; i < G.vexnum; i++)
    indegree[i] = 0; //初始化
  for (i = 0; i < G.vexnum; i++)
  {
    p = G.list[i].firstout;
    while (p)
    {
      indegree[LocateVex(G, p->head)]++;
      p = p->tailnext;
    }
  }
}

//获得出度
void FindOutDegree(const ALGraph &G, int outdegree[])
{
  int i;
  ArcBox *p;
  for (i = 0; i < G.vexnum; i++)
    outdegree[i] = 0; //初始化
  for (i = 0; i < G.vexnum; i++)
  {
    p = G.list[i].firstout;
    while (p)
    {
      outdegree[LocateVex(G, p->tail)]++;
      p = p->tailnext;
    }
  }
}

//拓扑逆向排序
bool TopologicalOrder(ALGraph &G)
{
  int j, k, count = 0, outdegree[MAX_VERTEX_NUM] = {0};
  stack<int> S;
  VexNode *p;
  FindOutDegree(G, outdegree);
  for (int j = 0; j < G.vexnum; ++j)
    if (!outdegree[j])
      S.push(j);
  for (j = 0; j < G.vexnum; ++j) // 初始化最大值
    ve[j] = LONGEST_PATH;
  while (!S.empty())
  {
    j = S.top();
    S.pop();
    ++count;
    for (ArcBox *p = G.list[j].firstin; p; p = p->headnext)
    { // 对j号顶点的每个邻接点的入度减1
      k = LocateVex(G, p->tail);
      if (--outdegree[k] == 0)
      {
        S.push(k);
        if (ve[j] - 1 < ve[k])
          ve[k] = ve[j] - 1;
      }
    }
  }
  if (count < G.vexnum)
  {
    return false;
  }
  else
    return true;
}

#endif
