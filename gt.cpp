/*
 * gt.cpp
 *
 */

#include "gt.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	GRAPH graph(10);
	graph.RandomGraphGenerate();
	//graph.PrintGraph();
	//graph.BFS();
	for(int i = 0; i < graph.Vsize; i++)
		graph.DFS(graph.node[i]);
	graph.PrintGraph();
	return 0;
}

int GRAPH::DFS(NODE* v)
{
	if(v->color == 2) //2=white: for non-connected graph is necessary
	{
		v->color--; //1=grey
		v->discovery_time = TIME;
		TIME++;

		for(int i = 0; i < v->Nsize; i++)
			if(v->adjacency[i]->color == 2) // it seems redundant to the top "if" but it is necessary for parent setting
			{
				v->adjacency[i]->parent = v;
				DFS(v->adjacency[i]); // can be out of if
			}

		v->color--; //0=black
		v->finish_time = TIME;
		TIME++;
	}
	//node->PrintNode();
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
	TIME = 0;
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
	this->discovery_time = 0;
	this->finish_time = 0;
}

void NODE::PrintNode()
{
	cout << "Node[" << key << "]: Nsize = " << Nsize
			<< ", Color = " << color << ", distance = " << distance
			<< ", Discovery = " << discovery_time << ", Finish = " << finish_time
			<< ", Value = " << value;

	if(parent != NULL)
		cout << ", Parent = " << parent->key << "\n";
	else
		cout << ", Parent = NULL\n";

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
