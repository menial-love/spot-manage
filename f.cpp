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
#define path1 "spotname.txt"   //�����ļ���
#define path2 "edge.txt"
//��ʼ��һ����vertexnum�����㵫�ޱߵ�ͼ
LGraph initGraph(int vertexnum) {
	LGraph Graph = new GNode;
	Graph->Nv = vertexnum;  //��vertexnum������
	Graph->Ne = 0; //����Ϊ0
	//��ʼ��ͼ�ڽӱ�ı�ͷ
	for (int i = 0; i < vertexnum; i++) {
		cout << "\t\t\t    \t       �������" << i + 1 << "��������:";
		cin >> Graph->G[i].data;
		cout << endl;
	}
	//��ʼ��ͼ�ڽӾ���
	for (int i = 0; i < vertexnum; i++) {
		for (int j = 0; j < vertexnum; j++) {
			if (i == j)  Graph->M[i][j] = 0;
			else  Graph->M[i][j] = INF;
		}
	}
	return Graph;
}
//��spotname�ļ���ʼ��ͼ
LGraph InitGraph() {
	ifstream fin(path1, ios_base::in);
	if (!fin.is_open()) {
		return NULL;
	}
	LGraph Graph = new GNode;
	Graph->Ne = 0; //����Ϊ0
	int vertexnum = 0, num = 0;
	string str, str1;
	//��ʼ��ͼ�ڽӱ�ı�ͷ
	while (getline(fin, str)) {  //���д��ļ����������������ʼ��ͼ�ڽӱ�Ķ����
		stringstream ss(str);
		ss >> num >> str1;
		Graph->G[num - 1].data = str1;
		vertexnum++;     //vertexnum��¼������
	}
	Graph->Nv = vertexnum;
	//��ʼ��ͼ�ڽӾ���
	for (int i = 0; i < vertexnum; i++) {
		for (int j = 0; j < vertexnum; j++) {
			if (i == j)  Graph->M[i][j] = 0;
			else  Graph->M[i][j] = INF;
		}
	}
	fin.close();
	return Graph;
}
//����һ����(����ͼ�Ĳ���)
void insertedge(LGraph Graph, edge E) {
	node Newnode = new AdjVNode;
	//ͷ�巨����V2��V1
	Newnode->adjv = E->V2;
	Newnode->data = Graph->G[E->V2].data;
	Newnode->next = Graph->G[E->V1].frist;  
	Graph->G[E->V1].frist = Newnode;  
	Graph->M[E->V1][E->V2] = E->weight;  //�ڽӾ���
	//����������ͼ�����ҲҪ����V1,V2
	Newnode = new AdjVNode;
	Newnode->adjv = E->V1;
	Newnode->data = Graph->G[E->V1].data;
	Newnode->next = Graph->G[E->V2].frist;
	Graph->G[E->V2].frist = Newnode;
	Graph->M[E->V2][E->V1] = E->weight;
}
//����һ����(����ͼ����)
void insertedge2(LGraph Graph, edge E) {
	node Newnode = new AdjVNode;
	//ͷ�巨����V2��V1
	Newnode->adjv = E->V2;
	Newnode->data = Graph->G[E->V2].data;
	Newnode->next = Graph->G[E->V1].frist;
	Graph->G[E->V1].frist = Newnode;
	Graph->M[E->V1][E->V2] = E->weight;  //�ڽӾ���
}
LGraph buildgraph() {
	ofstream fout;
	fout.open(path2, ios_base::trunc);   //�Խض̷�ʽ���ļ����������ظ�����
	edge E = new ENode;
	int Nv;
	cout << "\t\t\t    \t       ���뾰������ĸ�����";
	cin >> Nv;
	cout << endl;
	LGraph Graph = initGraph(Nv); 
	cout << "\t\t\t    \t       ���뾰����·����";
	cin >> Graph->Ne;
	cout << endl;
	cout << "\t\t\t    \t       �������·������㡢�յ�;��룺";
	for (int i = 0; i < Graph->Ne; i++) {
		cin >> E->V1 >> E->V2 >> E->weight;
		cout << "\t\t\t    \t                                       ";
		fout << E->V1 << " " << E->V2 << " " << E->weight << endl;   //����������Ϣ�����ļ�
		insertedge(Graph, E);
	}
	cout << endl;
	fout.close();
	return Graph;
}
//�����������������Ŵ����ļ�
void save(LGraph graph) {
	if (!graph) {
		return;
	}
	ofstream fout(path1, ios_base::trunc);      //���������ظ�����
	for (int i = 0; i < graph->Nv; i++) {
		fout << i + 1 << " " << graph->G[i].data << endl;
	}
	fout.close();
}
//���ļ��ж�ȡ���ݽ��������ֲ�ͼ,������buildgraph����
LGraph read() {   
	ifstream fin(path2, ios_base::in);   //��ֻ������ʽ���ļ���Ҫ���ļ��Ѿ�����
	if (!fin.is_open()) {
		cout << "\t\t\t    \t       ��ȡ����Ϣ�ļ�ʧ�ܣ��ļ������ڣ�              " << endl;
		return NULL;
	}
	edge E = new ENode;
	int edgenum = 0;
	string str;
	LGraph Graph = InitGraph();
	if (!Graph) {
		cout << "\t\t\t    \t       ��ȡ������Ϣ�ļ�ʧ�ܣ��ļ������ڣ�              " << endl;
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
//���ڽӾ���ķ�ʽ�������ֲ�ͼ
void output(LGraph Graph) {
	if (!Graph) {
		cout << "\t\t\t    \t       �����ֲ�ͼδ������             " << endl;
		cout << "\t\t\t    \t       ��������������˵�.......             ";
		_getch();
		cout << endl;
		return;
	}
	system("color E");
	cout << "\t\t\t_________________________________\n";
	cout << "\n\t\t\t*\t�����������ֲ�ͼ\t*\n";
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
				cout << setw(11) << setiosflags(ios::left) << "��         ";
			}
			else {
				cout << setw(11) << setiosflags(ios::left) << Graph->M[i][j];
			}
		}
		cout << "\n";
	}
	cout << "          __________________________________________________________\n";
}
//�������·��ͼ��������Ϊͼ����
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
	Graph->visit[s.top()] = 1;     //��ʾ�ڵ��ѱ�����
	LGraph graph = InitGraph();   //�Ƚ��������
	E->V1 = 0;
	while (!s.empty()) {
		temp = Graph->G[s.top()].frist;
		while (temp) {
			if (Graph->visit[temp->adjv] == 0) {
				ifstream fin(path2, ios_base::in);    //ÿ�ζ����ļ���һ�п�ʼ��ȡ����
				cout << Graph->G[temp->adjv].data << "->";
				Graph->visit[temp->adjv] = 1;
				s.push(temp->adjv);
				E->V2 = temp->adjv;
				while (getline(fin, str)) {     //���ļ��ｫ��Ȩֵ�ҵ�
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
	cout << "�յ�" << endl<<endl;
	return graph;
}

//������ĵ���·��ͼ�������������ж����޻�·
status topologicalsort(LGraph graph) {
	if (!graph) {
		return ERROR;
	}
	int* stack = new int[graph->Nv+1];
	int top = 0, gettop = 0, index = 0;
	int* indegree = new int[graph->Nv]; //��¼������������
	fill(indegree, indegree + graph->Nv, 0);
	int count = 0;   //��¼�������ĸ���
	cout << "\t\t\t\t       ����ͼ����������Ϊ��";
	//����ͼ���ڽӾ�����㶥�����
	for (int i = 0; i < graph->Nv; i++) {
		for (int j = 0; j < graph->Nv; j++) {
			if (graph->M[i][j] != INF && i != j) indegree[j]++;
		}
	}
	for (int i = 0; i < graph->Nv; i++)
		if (!indegree[i]) {
			stack[++top] = i;  //�����Ϊ0�Ķ����ջ
		}
	//����������Ҫ����
	while (top != 0) {
		gettop = stack[top--];  //��ջ
		cout << graph->G[gettop].data << "->";
		count++;
		for (node e = graph->G[gettop].frist; e; e = e->next) {
			index = e->adjv;
			if (!(--indegree[index])) //����gettop������������ڽӵ���ȼ�1,�����Ϊ0��ջ
				stack[++top] = index;
		}
	}
	delete[]stack;
	delete[]indegree;
	cout << "����" << endl;
	if (count < graph->Nv) {
		cout << "\t\t\t\t       ����ͼ�д��ڻ�·!" << endl << endl;
		return OK;
	}
	else {
		cout << "\t\t\t\t       ����ͼ���޻�·!" << endl << endl;;
		return OK;
	}
}

//������������������̾��벢��ӡ�����·��
void shortestpath(LGraph Graph) {
	if (!Graph) {
		cout << "\t\t\t    \t       �����ֲ�ͼδ������             " << endl;
		cout << "\t\t\t    \t       ��������������˵�.......             ";
		_getch();
		cout << endl;
		return;
	}
	int* patharc = new int[Graph->Nv];  //patharc[i]�ĺ���Ϊ����i��ǰ������Ϊpatharc[i]
	fill(patharc, patharc + Graph->Nv, 0);
	int* shortd = new int[Graph->Nv];   //������ʼ�㵽i������·��,Ŀ�������shortd[i]��ֵ
	fill(shortd, shortd + Graph->Nv, 0);
	int* final = new int[Graph->Nv];    //final[i]=1��ʾ��ʼ�㵽i������·�������
	fill(final, final + Graph->Nv, 0);
	int stan = -1, endn = -1;
	int index = 0;
	string start, end;
	cout << "\t\t\t\t       ������ʼ�����Ŀ�ĵ�:";
	cin >> start >> end;
	cout << endl;
	//����ͼ���ڽӱ����ȷ����ʼ����Ϊ�ڼ�������
	for (int i = 0; i < Graph->Nv; i++) {
		if (Graph->G[i].data == start) {
			stan = i;
			break;
		}
	}
	//����ͼ���ڽӱ����ȷ��Ŀ�ĵ�Ϊ�ڼ�������
	for (int i = 0; i < Graph->Nv; i++) {
		if (Graph->G[i].data == end) {
			endn = i;
			break;
		}
	}
	if (stan == -1 || endn == -1) {
		if (stan == -1) {
			cout << "\t\t\t\t       �������ʼ�������Ʋ����ڣ�" << endl << endl;
		}
		if (endn == -1)
			cout << "\t\t\t\t       �����Ŀ�ĵؾ������Ʋ����ڣ�" << endl << endl;
		cout << "\t\t\t    \t       ��������������˵�.......             ";
		_getch();
		cout << endl;
		return;
	}
	//��ʼ��
	for (int v = 0; v < Graph->Nv; v++) {
		final[v] = 0;
		shortd[v] = Graph->M[stan][v];
		patharc[v] = stan;         //��ǰ���ڵ������ʼ��Ϊ��ʼ���±�
	}
	shortd[stan] = 0;
	final[stan] = 1;
	//��ѭ����ÿ��ѭ�����ҵ�Դʼ�㵽ĳ����������·����ֱ���ҵ�Ŀ�ĵؾ�������ѭ��
	for (int v = 1; v < Graph->Nv; v++) {
		int minx = INF;
		//ÿ�δ�shortd�������ҵ�����ʼ������ĵ�
		for (int w = 0; w < Graph->Nv; w++) {
			if (shortd[w] < minx && !final[w]) {   //Ҫ��final����ȷ���õ㻹δ�����С·��
				index = w;
				minx = shortd[w];
			}
		}
		if (index<0 || index>Graph->Nv) {          //����C6835���棬��ֹshort[index]Խ��
			exit(-1);
		}
		if (index == endn) {  //���ҵ�����ʼ�㵽�յ�����·��������ѭ��
			break;
		}
		final[index] = 1;  //���ҵ�������Ķ�����1
		//����shortd�����patharc����
		for (int i = 0; i < Graph->Nv; i++) {
			if (!final[i] && minx + Graph->M[index][i] < shortd[i]) {  //�ҵ��˸��̵�·��
				shortd[i] = minx + Graph->M[index][i];
				patharc[i] = index;  //�¼ӵ�shortd������ĵ����ǵ�ǰ���ڵ�Ϊindex��
			}
		}
	}
	cout << "\t\t\t\t       ���·��Ϊ:" << endl;
	stack<int> s;   //����ջ��ת���ݵ�������������·��
	s.push(index);
	for (;;) {
		int i = patharc[endn];  //iΪĿ�Ķ����ǰ������
		s.push(i);
		endn = i;
		if (i == stan)
			break;
	}
	cout << "\t\t\t\t       ���->";
	while (!s.empty()) {
		int var = s.top();
		s.pop();
		cout << Graph->G[var].data << "->";
	}
	cout << "�յ�" << endl << endl;
	cout << "\t\t\t\t       ��̾���Ϊ:" << shortd[index] << endl;
	cout << "\t\t\t    \t       ��������������˵�.......             ";
	_getch();
	cout << endl;
	delete[]patharc;
	delete[]shortd;
	delete[]final;
	return;
}

//�����·�޽��滮ͼ
/*ʹ��prim��С�������㷨��ӡ����ͼ��С�������Ĺ�������*/
void print_Minitree(LGraph Graph) {
	if (!Graph) {
		cout << "\t\t\t    \t       �����ֲ�ͼδ������             " << endl;
		cout << "\t\t\t    \t       ��������������˵�.......             ";
		_getch();
		cout << endl;
		return;
	}
	int* adjv = new int[Graph->Nv];    //ǰ���ڵ����飬adjv[i]��ʾ��i���ڵ��ǰ���ڵ�Ϊadjv[i]
	int* lowcost = new int[Graph->Nv];  //��С�������飬������С������������
	int index = 0;
	lowcost[0] = 0;                     //��lowcost[i]Ϊ0ʱ��ʾ�õ��Ѿ���������С������
	//��ʼ��
	for (int i = 0; i < Graph->Nv; i++) {
		adjv[i] = 0;                    //��ǰ���ڵ������ʼ��Ϊ0
	}
	for (int i = 1; i < Graph->Nv; i++) {
		lowcost[i] = Graph->M[0][i];
	}
	//��ѭ������ӡ��С������
	cout << "\t\t\t\t       ��·�޽��滮ͼ:" << endl << endl;
	for (int i = 1; i < Graph->Nv; i++) {
		int minx = INF;
		//ÿ�δ�lowcost���ҵ�һ��Ȩֵ��С�ı�
		for (int j = 1; j < Graph->Nv; j++) {
			if (lowcost[j] < minx && lowcost[j]) {     //����û�м��뵽��С��������Ȩֵ��С
				index = j;
				minx = lowcost[j];
			}
		}
		lowcost[index] = 0;            //������С������
		//��ӡ·��
		cout <<"\t\t\t\t       "<< i << ":" << Graph->G[adjv[index]].data << "----->" << Graph->G[index].data << endl;
		cout << endl;
		//����lowcost������
		for (int j = 1; j < Graph->Nv; j++) {
			if (Graph->M[index][j] < lowcost[j] && lowcost[j]) {
				lowcost[j] = Graph->M[index][j];
				adjv[j] = index;
			}
		}
	}
	delete[]adjv;
	delete[]lowcost;
	cout << "\t\t\t    \t       ��������������˵�.......             ";
	_getch();
	cout << endl;
	return;
}
void meau() {
	system("color E");
	cout << "\t\t\t   *********************************************" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t       ����������Ϣ����ϵͳ            *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 1.  ������������ֲ�ͼ       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 2.  �洢��������ֲ�ͼ       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 3.  ��ȡ��������ֲ�ͼ       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 4.  �����������ֲ�ͼ       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 5.  �����������·��ͼ       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 6.  ��ѯ����·��ͼ��·       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 7.  ��ѯ��������·��       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 8.  �鿴��·�޽��滮ͼ       ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *\t" << " ��  " << " 9.  �˳�ϵͳ                 ��  *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *                                           *" << endl;
	cout << "\t\t\t   *********************************************" << endl;
	cout << "����ѡ�� >>  :    ";
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
			cout << "\n\t\t\t               *       ������������ֲ�ͼ      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			Graph = buildgraph();
			if(Graph)
				cout << "\t\t\t    \t       �����ֲ�ͼ������ɣ�             " << endl;
			cout << "\t\t\t    \t       ��������������˵�.......             " << endl;
			_getch();        //ʹ��getch()���û���������һ����ʱ������������
		}
		if (choice == 2) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       ��ȡ��������ֲ�ͼ      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			save(Graph);
			string str;
			ifstream fin(path1, ios_base::in);
			if (!fin.is_open()) {
				cout << "\t\t\t    \t       ������Ϣ�ļ�����ʧ�ܣ������ݿɱ��棡              " << endl;
				cout << "\t\t\t    \t       ��������������˵�.......             ";
				_getch();
				cout << endl;
				continue;
			}
			cout << "\t\t\t    \t       ������Ϣ�ļ��ѽ�����              " << endl;
			cout << "\t\t\t    \t       ��������������˵�.......             ";
			fin.close();
			_getch();
			cout << endl;
		}
		if (choice == 3) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       ��ȡ��������ֲ�ͼ      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			Graph = read();
			if (Graph) {
				cout << "\t\t\t    \t       �����ֲ�ͼ������ɣ�             " << endl;
			}
			cout << "\t\t\t    \t       ��������������˵�.......             ";
			_getch();
			cout << endl;
		}
		if (choice == 4) {
			system("cls");
			output(Graph);
			cout << "\t\t\t    \t       ��������������˵�.......             ";
			_getch();
			cout << endl;
		}
		if (choice == 5) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       �����������·��ͼ      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			graph = dfs(Graph);    //��������������ͼ
			if (graph) {
				cout << "\t\t\t    \t       ����·��ͼ������ɣ�             " << endl;
			}
			else {
				cout << "\t\t\t    \t       ����·��ͼ����ʧ�ܣ�����ֲ�ͼδ������             " << endl;
			}
			cout << "\t\t\t    \t       ��������������˵�.......             ";
			_getch();
			cout << endl;
		}
		if (choice == 6) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       ��ѯ����·��ͼ��·      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			if (topologicalsort(graph) == ERROR) {
				cout << "\t\t\t    \t       ����·��ͼδ������             " << endl;
				cout << "\t\t\t    \t       ��������������˵�.......             ";
				_getch();
				cout << endl;
				continue;
			}
			else {
				cout << "\t\t\t    \t       ��������������˵�.......             ";
				_getch();
				cout << endl;
			}
		}
		if (choice == 7) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       ��ѯ��������·��      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			shortestpath(Graph);
		}
		if (choice == 8) {
			system("cls");
			cout << "\t\t\t               _________________________________\n";
			cout << "\n\t\t\t               *       �鿴��·�޽��滮ͼ      *\n";
			cout << "\t\t\t               _________________________________\n\n\n";
			print_Minitree(Graph);
		}
	} while (choice != 9);
}