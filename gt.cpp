/*
 * gt.cpp
 *
 */

#include "gt.h"

//int a[2][3] = { {1,2,3}, {4,5,6} };

int main(int argc, char* argv[])
{
	GRAPH graph(10);
	graph.RandomGraphGenerate();
	graph.PrintGraph();
	cout << "\n\n\n";
	graph.BFS();
	return 0;
}











int GRAPH::BFS()
{
	QUEUE queue(Vsize);
	int DIST = 0;
	node[0]->parent = NULL;
	node[0]->color--; //1
	node[0]->distance = DIST;
	queue.enqueue(node[0]);
	while(queue.size > 0)
	{
		DIST++;
		NODE* node = (NODE*)(queue.dequeue());
		//node->PrintNode();
		for(int i = 0; i < node->Nsize; i++)
		{
			NODE* child = node->adjacency[i];
			if(child->color == 2)
			{
				child->parent = node;
				child->color--;
				child->distance = DIST;
				queue.enqueue(child);
				//child->PrintNode();
			}
		}
		node->color--; //0
		node->PrintNode();
	}
	return 0;
}

void GRAPH::PrintGraph()
{
	if(this->node != NULL)
		for(int i = 0; i < this->Vsize; i++)
			this->node[i]->PrintNode();
}

int GRAPH::RandomGraphGenerate()
{
	if(Vsize == 0)
		return -1;
	this->node = new NODE* [Vsize];
	for(int i = 0; i < this->Vsize; i++)
		node[i] = new NODE; //this is mandatory to create node* addresses
	for(int i = 0; i < this->Vsize; i++)
	{
		int Nsize = 0;
		adjacency[i][i] = 0;
		for(int j = 0; j < this->Vsize; j++)
		{
			if(j > i)
			{
				this->adjacency[i][j] = rand()%2;
				this->adjacency[j][i] = this->adjacency[i][j];
			}
			if(adjacency[i][j] == 1)
				Nsize++;
		}
		node[i]->key = i;
		node[i]->adjacency = new NODE* [Nsize];
		node[i]->Nsize = Nsize;
		int cNsize = 0;
		for(int j = 0; j < this->Vsize; j++)
		{
			if(adjacency[i][j] == 1)
			{
				node[i]->adjacency[cNsize] = node[j];
				cNsize++;
			}
		}
	}
	return 0;
}

GRAPH::GRAPH(int vsize)
{
	Vsize = vsize;
	this->node = new NODE* [vsize];
	this->adjacency = new int* [vsize];
	for(int i = 0; i < vsize; i++)
		this->adjacency[i] = new int [vsize];
}

GRAPH::~GRAPH()
{
	for(int i = 0; i < Vsize; i++)
	{
		if(node[i] != NULL)
			delete (node[i]);
		if(adjacency[i] != NULL)
			delete (adjacency[i]);
	}
/*	if(node != NULL)
		delete node;
	if(adjacency != NULL)
		delete node;*/
}

NODE::NODE(int k, int nsize)
{
	this->key = k;
	this->distance = -1;
	this->Nsize = nsize;
	this->value = 0;
	this->adjacency = new NODE* [nsize];
	this->color = 2;
	this->parent = NULL;
}

void NODE::PrintNode()
{
	cout << "Node[" << key << "]: Nsize = " << Nsize
			<< ", Color = " << color << ", distance = " << distance << ", Value = " << value << "\n";
	for(int i = 0; i < Nsize; i++)
		if(adjacency[i] != NULL)
			cout << " N[" << i << "]:" << this->adjacency[i]->key << " ";
	cout << "\n";
}

NODE::~NODE()
{
	//for(int i = 0; i < Nsize; i++)
	//	if(adjacency[i] != NULL)
	//		delete adjacency[i];
	if(adjacency != NULL)
		delete adjacency;
}
