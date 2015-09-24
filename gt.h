/*
 * gt.h
 *
 */

#ifndef GT_H_
#define GT_H_

#include <iostream>
using namespace std;

#define Max_Vertex_Num 10

class NODE
{
public:
	int key; //id
	double value;
	double distance;
	NODE** adjacency;
	int Nsize; // neighbor size
	int color; // 2 = white, 1 = grey, 0 = black
	NODE* parent;
	int discovery_time;
	int finish_time;
	NODE()
	{
		key = 0;//rand()%100;
		distance = -1;
		value = 0;
		Nsize = 0;
		adjacency = NULL;
		color = 2;
		parent = NULL;
		discovery_time = 0;
		finish_time = 0;
	}
	NODE(int k, int nsize);
	~NODE();
	void PrintNode();
};

class GRAPH
{
public:
	int** adjacency;
	NODE** node;
	int Vsize; // number of vertexes
	int TIME;
	GRAPH()
	{
		Vsize = 0;
		adjacency = NULL;
		node = NULL;
		TIME = 0;
	}
	GRAPH(int vsize);
	~GRAPH();
	int RandomGraphGenerate();
	void PrintGraph();
	int BFS();
	int DFS(NODE* node);
};

class QUEUE
{
public:
	int size;
	int head;
	int tail;
	void** Q;

	QUEUE()
	{
		Q = NULL;
		size = 0;
		head = -1;
		tail = -1;
	}

	QUEUE(int sz)
	{
		Q = new void* [sz];
		size = sz;
		head = -1;
		tail = -1;
	}

	void* makenew(int id)
	{
		NODE* e = new NODE;
		e->key = id;
		return e;
	}

	int enqueue(void* e) // to the end
	{
		if(size )
		Q[tail] = e;
		tail++;
		tail %= size;
		if(tail == head)
			return -1; // Queue is full
		else
			return 0; // Queue is not-full
	};

	void* dequeue() // from the head
	{
		void* htemp = Q[head];
		if(htemp != NULL)
		{
			Q[head] = NULL;
			head++;
			head %= size;
		}
		return htemp;
	};
};

#endif /* GT_H_ */
