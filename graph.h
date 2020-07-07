#pragma once
#ifndef GRAPH_H_
#define GRAPH_H

#include<iostream>
using namespace std;
#define Adjtype string
#define MAXNUM 100
//�ߵĶ���
typedef struct ENode {
	int V1, V2;    //��V1��V2
	int weight;    //��Ȩ��
}*edge;
//�ڽӵ�Ķ���
typedef struct AdjVNode {
	int adjv;    //����õ��Ӧ���±�
	Adjtype data;
	struct AdjVNode* next;
	AdjVNode() {
		adjv = 0;
		data = '\0';
		next = NULL;
	}
}*node;
//�ڽӱ�ı�ͷ�ڵ�
typedef struct Vnode {
	node frist;
	Adjtype data;
	Vnode() {
		frist = new AdjVNode;
	}
}Adjlist[MAXNUM];
//ͼ�Ķ���
typedef struct GNode {
	int Nv;   //������
	int Ne;   //����
	Adjlist G;  //ͼ���ڽӱ�
	int M[MAXNUM][MAXNUM];  //ͼ�ڽӾ���
	int visit[MAXNUM];
	GNode(){
		Nv = 0;
		Ne = 0;
		fill(M[0], M[0] + MAXNUM * MAXNUM, 0);
		fill(visit, visit + MAXNUM, 0);
	}
}*LGraph;

#endif // !GRAPH_H_
