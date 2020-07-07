#include "graph.h"
#include<iostream>
#include<stack>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<iomanip>
#include<graphics.h>
#include<conio.h>
#define INF 0x3f3f3f
#define status int
#define ERROR 0
#define OK 1
#define path1 "spotname.txt"   //定义文件名
#define path2 "edge.txt"
//初始化一个有vertexnum个顶点但无边的图
LGraph initGraph(int vertexnum) {
	LGraph Graph = new GNode;
	Graph->Nv = vertexnum;  //有vertexnum个顶点
	Graph->Ne = 0; //边数为0
	//初始化图邻接表的表头
	for (int i = 0; i < vertexnum; i++) {
		cout << "\t\t\t    \t       请输入第" << i + 1 << "个景点名:";
		cin >> Graph->G[i].data;
		cout << endl;
	}
	//初始化图邻接矩阵
	for (int i = 0; i < vertexnum; i++) {
		for (int j = 0; j < vertexnum; j++) {
			if (i == j)  Graph->M[i][j] = 0;
			else  Graph->M[i][j] = INF;
		}
	}
	return Graph;
}
//用spotname文件初始化图
LGraph InitGraph() {
	ifstream fin(path1, ios_base::in);
	if (!fin.is_open()) {
		return NULL;
	}
	LGraph Graph = new GNode;
	Graph->Ne = 0; //边数为0
	int vertexnum = 0, num = 0;
	string str, str1;
	//初始化图邻接表的表头
	while (getline(fin, str)) {  //按行从文件里读出内容用来初始化图邻接表的顶点表
		stringstream ss(str);
		ss >> num >> str1;
		Graph->G[num - 1].data = str1;
		vertexnum++;     //vertexnum记录顶点数
	}
	Graph->Nv = vertexnum;
	//初始化图邻接矩阵
	for (int i = 0; i < vertexnum; i++) {
		for (int j = 0; j < vertexnum; j++) {
			if (i == j)  Graph->M[i][j] = 0;
			else  Graph->M[i][j] = INF;
		}
	}
	fin.close();
	return Graph;
}
//插入一条边(无向图的插入)
void insertedge(LGraph Graph, edge E) {
	node Newnode = new AdjVNode;
	//头插法插入V2，V1
	Newnode->adjv = E->V2;
	Newnode->data = Graph->G[E->V2].data;
	Newnode->next = Graph->G[E->V1].frist;  
	Graph->G[E->V1].frist = Newnode;  
	Graph->M[E->V1][E->V2] = E->weight;  //邻接矩阵
	//由于是无向图，因此也要插入V1,V2
	Newnode = new AdjVNode;
	Newnode->adjv = E->V1;
	Newnode->data = Graph->G[E->V1].data;
	Newnode->next = Graph->G[E->V2].frist;
	Graph->G[E->V2].frist = Newnode;
	Graph->M[E->V2][E->V1] = E->weight;
}
//插入一条边(有向图插入)
void insertedge2(LGraph Graph, edge E) {
	node Newnode = new AdjVNode;
	//头插法插入V2，V1
	Newnode->adjv = E->V2;
	Newnode->data = Graph->G[E->V2].data;
	Newnode->next = Graph->G[E->V1].frist;
	Graph->G[E->V1].frist = Newnode;
	Graph->M[E->V1][E->V2] = E->weight;  //邻接矩阵
}
LGraph buildgraph() {
	ofstream fout;
	fout.open(path2, ios_base::trunc);   //以截短方式打开文件避免内容重复储存
	edge E = new ENode;
	int Nv;
	cout << "\t\t\t    \t       输入景区景点的个数：";
	cin >> Nv;
	cout << endl;
	LGraph Graph = initGraph(Nv); 
	cout << "\t\t\t    \t       输入景区道路数：";
	cin >> Graph->Ne;
	cout << endl;
	cout << "\t\t\t    \t       输入各个路径的起点、终点和距离：";
	for (int i = 0; i < Graph->Ne; i++) {
		cin >> E->V1 >> E->V2 >> E->weight;
		cout << "\t\t\t    \t                                       ";
		fout << E->V1 << " " << E->V2 << " " << E->weight << endl;   //将各条边信息存入文件
		insertedge(Graph, E);
	}
	cout << endl;
	fout.close();
	return Graph;
}
//将各个景点名称与编号存入文件
void save(LGraph graph) {
	if (!graph) {
		return;
	}
	ofstream fout(path1, ios_base::trunc);      //避免内容重复储存
	for (int i = 0; i < graph->Nv; i++) {
		fout << i + 1 << " " << graph->G[i].data << endl;
	}
	fout.close();
}
//从文件中读取数据建立景区分布图,类似于buildgraph函数
LGraph read() {   
	ifstream fin(path2, ios_base::in);   //以只读的形式打开文件，要求文件已经建立
	if (!fin.is_open()) {
		cout << "\t\t\t    \t       读取边信息文件失败，文件不存在！              " << endl;
		return NULL;
	}
	edge E = new ENode;
	int edgenum = 0;
	string str;
	LGraph Graph = InitGraph();
	if (!Graph) {
		cout << "\t\t\t    \t       读取顶点信息文件失败，文件不存在！              " << endl;
		return NULL;
	}
	while (getline(fin, str)) {
		stringstream ss(str);
		ss >> E->V1 >> E->V2 >> E->weight;
		insertedge(Graph, E);
		edgenum++;
	}
    Graph->Ne = edgenum;
	fin.close();
	return Graph;
}
//以邻接矩阵的方式输出景点分布图
void output(LGraph Graph) {
	if (!Graph) {
		cout << "\t\t\t    \t       景区分布图未创建！             " << endl;
		cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
		_getch();
		cout << endl;
		return;
	}
	system("color E");
	cout << "\t\t\t_________________________________\n";
	cout << "\n\t\t\t*\t输出景区景点分布图\t*\n";
	cout << "\t\t\t_________________________________\n\n\n";
	cout << "\t";
	for (int i = 0; i < Graph->Nv; i++) {
		cout << Graph->G[i].data << "    ";
	}
	cout << "\n";
	for (int i = 0; i < Graph->Nv; i++) {
		cout << "          __________________________________________________________\n\n";
		cout << setw(8) << setiosflags(ios::left) << Graph->G[i].data << "  ";
		for (int j = 0; j < Graph->Nv; j++) {
			if (Graph->M[i][j] == INF) {
				cout << setw(11) << setiosflags(ios::left) << "∞         ";
			}
			else {
				cout << setw(11) << setiosflags(ios::left) << Graph->M[i][j];
			}
		}
		cout << "\n";
	}
	cout << "          __________________________________________________________\n";
}
//输出导游路线图并将其作为图储存
LGraph dfs(LGraph Graph) {
	if (!Graph) {
		return NULL;
	}
	fill(Graph->visit, Graph->visit + MAXNUM, 0);
	int V1, V2, weight;
	string str;
	edge E = new ENode;
	node temp = new AdjVNode;
	stack<int> s;
	s.push(0);
	cout << "\t\t\t\t       " << Graph->G[s.top()].data << "->";
	Graph->visit[s.top()] = 1;     //表示节点已被访问
	LGraph graph = InitGraph();   //先建立顶点表
	E->V1 = 0;
	while (!s.empty()) {
		temp = Graph->G[s.top()].frist;
		while (temp) {
			if (Graph->visit[temp->adjv] == 0) {
				ifstream fin(path2, ios_base::in);    //每次都从文件第一行开始读取内容
				cout << Graph->G[temp->adjv].data << "->";
				Graph->visit[temp->adjv] = 1;
				s.push(temp->adjv);
				E->V2 = temp->adjv;
				while (getline(fin, str)) {     //从文件里将边权值找到
					stringstream ss(str);
					ss >> V1 >> V2 >> weight;
					if (V1 == E->V1 && V2 == E->V2) {
						E->weight = weight;
						break;
					}
				}
				fin.close();
				insertedge2(graph, E);
				graph->Ne++;
				E->V1 = temp->adjv;
				temp = Graph->G[temp->adjv].frist;
			}
			else {
				temp = temp->next;
			}
		}
		if (!temp) {
			s.pop();
		}
	}
	cout << "终点" << endl<<endl;
	return graph;
}

//对输出的导游路线图进行拓扑排序判断有无回路
status topologicalsort(LGraph graph) {
	if (!graph) {
		return ERROR;
	}
	int* stack = new int[graph->Nv+1];
	int top = 0, gettop = 0, index = 0;
	int* indegree = new int[graph->Nv]; //记录各个顶点的入度
	fill(indegree, indegree + graph->Nv, 0);
	int count = 0;   //记录输出顶点的个数
	cout << "\t\t\t\t       导游图的拓扑序列为：";
	//根据图的邻接矩阵计算顶点入度
	for (int i = 0; i < graph->Nv; i++) {
		for (int j = 0; j < graph->Nv; j++) {
			if (graph->M[i][j] != INF && i != j) indegree[j]++;
		}
	}
	for (int i = 0; i < graph->Nv; i++)
		if (!indegree[i]) {
			stack[++top] = i;  //将入度为0的顶点进栈
		}
	//拓扑排序主要过程
	while (top != 0) {
		gettop = stack[top--];  //出栈
		cout << graph->G[gettop].data << "->";
		count++;
		for (node e = graph->G[gettop].frist; e; e = e->next) {
			index = e->adjv;
			if (!(--indegree[index])) //将第gettop个顶点的所有邻接点入度减1,若入度为0进栈
				stack[++top] = index;
		}
	}
	delete[]stack;
	delete[]indegree;
	cout << "结束" << endl;
	if (count < graph->Nv) {
		cout << "\t\t\t\t       导游图中存在回路!" << endl << endl;
		return OK;
	}
	else {
		cout << "\t\t\t\t       导游图中无回路!" << endl << endl;;
		return OK;
	}
}

//计算任意两景点间的最短距离并打印其最短路径
void shortestpath(LGraph Graph) {
	if (!Graph) {
		cout << "\t\t\t    \t       景区分布图未创建！             " << endl;
		cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
		_getch();
		cout << endl;
		return;
	}
	int* patharc = new int[Graph->Nv];  //patharc[i]的含义为顶点i的前驱顶点为patharc[i]
	fill(patharc, patharc + Graph->Nv, 0);
	int* shortd = new int[Graph->Nv];   //储存起始点到i点的最短路径,目的是求出shortd[i]的值
	fill(shortd, shortd + Graph->Nv, 0);
	int* final = new int[Graph->Nv];    //final[i]=1表示起始点到i点的最短路径已求出
	fill(final, final + Graph->Nv, 0);
	int stan = -1, endn = -1;
	int index = 0;
	string start, end;
	cout << "\t\t\t\t       输入起始景点和目的地:";
	cin >> start >> end;
	cout << endl;
	//遍历图的邻接表顶点表确定起始景点为第几个景点
	for (int i = 0; i < Graph->Nv; i++) {
		if (Graph->G[i].data == start) {
			stan = i;
			break;
		}
	}
	//遍历图的邻接表顶点表确定目的地为第几个景点
	for (int i = 0; i < Graph->Nv; i++) {
		if (Graph->G[i].data == end) {
			endn = i;
			break;
		}
	}
	if (stan == -1 || endn == -1) {
		if (stan == -1) {
			cout << "\t\t\t\t       输入的起始景点名称不存在！" << endl << endl;
		}
		if (endn == -1)
			cout << "\t\t\t\t       输入的目的地景点名称不存在！" << endl << endl;
		cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
		_getch();
		cout << endl;
		return;
	}
	//初始化
	for (int v = 0; v < Graph->Nv; v++) {
		final[v] = 0;
		shortd[v] = Graph->M[stan][v];
		patharc[v] = stan;         //将前驱节点数组初始化为起始点下标
	}
	shortd[stan] = 0;
	final[stan] = 1;
	//主循环，每次循环可找到源始点到某个顶点的最短路径，直到找到目的地景点跳出循环
	for (int v = 1; v < Graph->Nv; v++) {
		int minx = INF;
		//每次从shortd数组中找到离起始点最近的点
		for (int w = 0; w < Graph->Nv; w++) {
			if (shortd[w] < minx && !final[w]) {   //要从final数组确定该点还未求得最小路径
				index = w;
				minx = shortd[w];
			}
		}
		if (index<0 || index>Graph->Nv) {          //消除C6835警告，防止short[index]越界
			exit(-1);
		}
		if (index == endn) {  //若找到了起始点到终点的最短路径就跳出循环
			break;
		}
		final[index] = 1;  //将找到的最近的顶点置1
		//更新shortd数组和patharc数组
		for (int i = 0; i < Graph->Nv; i++) {
			if (!final[i] && minx + Graph->M[index][i] < shortd[i]) {  //找到了更短的路径
				shortd[i] = minx + Graph->M[index][i];
				patharc[i] = index;  //新加到shortd数组里的点它们的前驱节点为index点
			}
		}
	}
	cout << "\t\t\t\t       最短路径为:" << endl;
	stack<int> s;   //利用栈倒转数据的特性来输出最短路径
	s.push(index);
	for (;;) {
		int i = patharc[endn];  //i为目的顶点的前驱顶点
		s.push(i);
		endn = i;
		if (i == stan)
			break;
	}
	cout << "\t\t\t\t       起点->";
	while (!s.empty()) {
		int var = s.top();
		s.pop();
		cout << Graph->G[var].data << "->";
	}
	cout << "终点" << endl << endl;
	cout << "\t\t\t\t       最短距离为:" << shortd[index] << endl;
	cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
	_getch();
	cout << endl;
	delete[]patharc;
	delete[]shortd;
	delete[]final;
	return;
}

//输出道路修建规划图
/*使用prim最小生成树算法打印景区图最小生成树的构建过程*/
void print_Minitree(LGraph Graph) {
	if (!Graph) {
		cout << "\t\t\t    \t       景区分布图未创建！             " << endl;
		cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
		_getch();
		cout << endl;
		return;
	}
	int* adjv = new int[Graph->Nv];    //前驱节点数组，adjv[i]表示第i个节点的前驱节点为adjv[i]
	int* lowcost = new int[Graph->Nv];  //最小代价数组，用于最小生成树的生成
	int index = 0;
	lowcost[0] = 0;                     //当lowcost[i]为0时表示该点已经加入了最小生产树
	//初始化
	for (int i = 0; i < Graph->Nv; i++) {
		adjv[i] = 0;                    //将前驱节点数组初始化为0
	}
	for (int i = 1; i < Graph->Nv; i++) {
		lowcost[i] = Graph->M[0][i];
	}
	//主循环，打印最小生成树
	cout << "\t\t\t\t       道路修建规划图:" << endl << endl;
	for (int i = 1; i < Graph->Nv; i++) {
		int minx = INF;
		//每次从lowcost中找到一条权值最小的边
		for (int j = 1; j < Graph->Nv; j++) {
			if (lowcost[j] < minx && lowcost[j]) {     //顶点没有加入到最小生成树且权值最小
				index = j;
				minx = lowcost[j];
			}
		}
		lowcost[index] = 0;            //加入最小生成树
		//打印路径
		cout <<"\t\t\t\t       "<< i << ":" << Graph->G[adjv[index]].data << "----->" << Graph->G[index].data << endl;
		cout << endl;
		//更新lowcost的数组
		for (int j = 1; j < Graph->Nv; j++) {
			if (Graph->M[index][j] < lowcost[j] && lowcost[j]) {
				lowcost[j] = Graph->M[index][j];
				adjv[j] = index;
			}
		}
	}
	delete[]adjv;
	delete[]lowcost;
	cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
	_getch();
	cout << endl;
	return;
}
void meau() {
	system("color E");
	cout << "\t\t\t   *********************************************" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t       景区旅游信息管理系统            *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 1.  创建景区景点分布图       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 2.  存储景区景点分布图       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 3.  读取景区景点分布图       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 4.  输出景区景点分布图       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 5.  输出景区导游路线图       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 6.  查询导游路线图回路       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 7.  查询景点间最短路径       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 8.  查看道路修建规划图       ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ☆  " << " 9.  退出系统                 ☆  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *********************************************" << endl;
	cout << "功能选择 >>  :    ";
}
int main() {
	int choice = 0;
	LGraph Graph = NULL;
	LGraph graph = NULL;
	do {
		system("cls");
		meau();
		cin >> choice;
		if (choice == 1) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       创建景区景点分布图      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			Graph = buildgraph();
			if(Graph)
				cout << "\t\t\t    \t       景区分布图创建完成！             " << endl;
			cout << "\t\t\t    \t       按任意键返回主菜单.......             " << endl;
			_getch();        //使用getch()当用户按下任意一个键时函数立即返回
		}
		if (choice == 2) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       存取景区景点分布图      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			save(Graph);
			string str;
			ifstream fin(path1, ios_base::in);
			if (!fin.is_open()) {
				cout << "\t\t\t    \t       顶点信息文件创建失败，无内容可保存！              " << endl;
				cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
				_getch();
				cout << endl;
				continue;
			}
			cout << "\t\t\t    \t       顶点信息文件已建立！              " << endl;
			cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
			fin.close();
			_getch();
			cout << endl;
		}
		if (choice == 3) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       读取景区景点分布图      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			Graph = read();
			if (Graph) {
				cout << "\t\t\t    \t       景区分布图创建完成！             " << endl;
			}
			cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
			_getch();
			cout << endl;
		}
		if (choice == 4) {
			system("cls");
			output(Graph);
			cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
			_getch();
			cout << endl;
		}
		if (choice == 5) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       输出景区导游路线图      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			graph = dfs(Graph);    //遍历并创建导游图
			if (graph) {
				cout << "\t\t\t    \t       导游路线图创建完成！             " << endl;
			}
			else {
				cout << "\t\t\t    \t       导游路线图创建失败，景点分布图未建立！             " << endl;
			}
			cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
			_getch();
			cout << endl;
		}
		if (choice == 6) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       查询导游路线图回路      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			if (topologicalsort(graph) == ERROR) {
				cout << "\t\t\t    \t       导游路线图未创建！             " << endl;
				cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
				_getch();
				cout << endl;
				continue;
			}
			else {
				cout << "\t\t\t    \t       按任意键返回主菜单.......             ";
				_getch();
				cout << endl;
			}
		}
		if (choice == 7) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       查询景点间最短路径      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			shortestpath(Graph);
		}
		if (choice == 8) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       查看道路修建规划图      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			print_Minitree(Graph);
		}
	} while (choice != 9);
}