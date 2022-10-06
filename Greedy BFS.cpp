//LOGIC;
//Greedy 1 : Run BFS on the graph and check for cross edges with the same colour and remove them until the graph is bipartite.
//Greedy 2 : Check for odd cycles in the graph and removing the vertice with maximum degree until the graph is bipartite.

//Note : The given code contains the creation of the graph and running BFS on that graph.

#include<iostream>
using namespace std;

struct node
{
	int data;
	int weight;

	struct node *next;
};

struct node* insert(int data,  struct node *head, int w)
{
	struct node *insert=(struct node*)malloc(sizeof(struct node));
	insert->data = data;
	insert->weight = w;
	 if(head!=NULL)
	 {
	 	insert->next = head->next;
	 	head->next = insert;
	 }
	 else
	 {
	 	insert->next = NULL;
	 	return insert;
	 }

	 return head;

}

void printList(struct node *head)
{
	struct node *temp = head;

	while(temp!=NULL)
	{
		cout << temp->data << "  ";
		temp = temp->next;
	}
}

class Graph
{
	public :
	int n;

	struct node *N[100];

	Graph()
	{
		for(int i=0; i<n; i++)
		{
			N[i] = NULL;
		}
	}

	void insertEdge(int n1, int n2, int w)
	{
		N[n1] = insert(n2, N[n1], w);
		N[n2] = insert(n1, N[n2], w);
	}

	void print()
	{
		for(int i=0; i<n; i++)
		{
			printList(N[i]);
			cout<<endl;
		}
	}

};

struct node* front;
struct node* rear;
struct node* head = front = rear = NULL;

void enqueue(int x)
{
	struct node* temp = (struct node*) malloc (sizeof(struct node));
	temp->data = x;
	if(head == NULL){
		front = temp;
		rear = temp;
		temp->next = temp;
		head = temp;
	}
	else{
		rear->next = temp;
		rear = temp;
		temp->next = NULL;
	}
}

int dequeue()
{
    int x=front->data;
	front = front->next;
	head = head->next;
	rear->next = NULL;
    return x;
}

int empty(){
    if(front == rear)
        return 1;
    return 0;
}


void BFS(Graph G)
{
    bool visit[G.n];
    for(int i = 0; i < G.n; i++)
        visit[i] = false;
    visit[0] = true;
    enqueue(0);
    while(!empty()){
        int x = dequeue();
        cout<<x<<" ";
        struct node* temp = G.N[x];
        int i;
        while(temp){
            i = temp->data;
            if(!visit[i]){
                visit[i] = true;
                enqueue(i);
                temp = temp->next;
            }
        }
    }
}

