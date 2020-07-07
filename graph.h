#pragma once
#ifndef GRAPH_H_
#define GRAPH_H

#include<iostream>
using namespace std;
#define Adjtype string
#define MAXNUM 100
//边的定义
typedef struct ENode {
	int V1, V2;    //边V1，V2
	int weight;    //边权重
}*edge;
//邻接点的定义
typedef struct AdjVNode {
	int adjv;    //储存该点对应的下标
	Adjtype data;
	struct AdjVNode* next;
	AdjVNode() {
		adjv = 0;
		data = '\0';
		next = NULL;
	}
}*node;
//邻接表的表头节点
typedef struct Vnode {
	node frist;
	Adjtype data;
	Vnode() {
		frist = new AdjVNode;
	}
}Adjlist[MAXNUM];
//图的定义
typedef struct GNode {
	int Nv;   //顶点数
	int Ne;   //边数
	Adjlist G;  //图的邻接表
	int M[MAXNUM][MAXNUM];  //图邻接矩阵
	int visit[MAXNUM];
	GNode(){
		Nv = 0;
		Ne = 0;
		fill(M[0], M[0] + MAXNUM * MAXNUM, 0);
		fill(visit, visit + MAXNUM, 0);
	}
}*LGraph;

#endif // !GRAPH_H_
