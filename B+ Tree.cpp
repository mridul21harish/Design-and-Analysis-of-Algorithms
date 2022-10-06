#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<climits>

using namespace std;
int MAX; 
class BPTree; 
class Node
{
	bool IS_LEAF;
	int *key, size;
	Node** ptr;
	friend class BPTree;
public:
	Node();
};
class BPTree
{
	Node *root;
	void Insert_Internally(int,Node*,Node*);
	void Remove_Internally(int,Node*,Node*);
	Node* Find_The_Parent(Node*,Node*);
public:
	BPTree();
	void Search(int);
	void Insert(int);
	void Remove (int);
	void Display(Node*);
	Node* Get_The_Root();	
};

int main()
{
    int order;
    cout << "Enter the order of the B Plus Tree: ";
    cin >> order;
    order--;
    BPTree tree(order);
    while(true){
        int x;
        cout << "Enter which operation you wish to perform: \n\t1)Insert\n\t2)Delete\n\t3)Traversal\n\t4)Exit" << endl;
        cin >> x;
        switch(x){
            case 1: {
                int a;
                cout << "Enter the key you wish to insertKey: ";
                cin >> a;
                tree.Insert(a);
                break;
            }
            case 2: {
                int a;
                cout << "Enter the key you wish to delete: ";
                cin >> a;
                tree.Remove(a);
                break;
            }
            case 3: {
                cout << "Tree traversal" << endl;
                tree.Display();
                break;
            }
            case 4: {
                exit(0);
            }
        }
    }
    return 0;
}
Node::Node()
{
	
	key = new int[MAX];
	ptr = new Node*[MAX+1];
}
BPTree::BPTree()
{
	root = NULL;
}
void BPTree::Search(int x)
{
	
	if(root==NULL)
	{
		
		cout<<"Tree empty\n";
	}
	else
	{
		Node* pointer = root;
		
		while(pointer->IS_LEAF == false)
		{
			for(int i = 0; i < pointer->size; i++)
			{
				if(x < pointer->key[i])
				{
					pointer = pointer->ptr[i];
					break;
				}
				if(i == pointer->size - 1)
				{
					pointer = pointer->ptr[i+1];
					break;
				}
			}
		}
	
		for(int i = 0; i < pointer->size; i++)
		{
			if(pointer->key[i] == x)
			{
				cout<<"Found\n";
				return;
			}
		}
		cout<<"Not found\n";
	}
}
void BPTree::Insert(int x)
{
	
	if(root==NULL)
	{
		root = new Node;
		root->key[0] = x;
		root->IS_LEAF = true;
		root->size = 1;
		cout<<"Created root\nInserted "<<x<<" successfully\n";
	}
	else
	{
		Node* pointer = root;
		Node* parent;
		
		while(pointer->IS_LEAF == false)
		{
			parent = pointer;
			for(int i = 0; i < pointer->size; i++)
			{
				if(x < pointer->key[i])
				{
					pointer = pointer->ptr[i];
					break;
				}
				if(i == pointer->size - 1)
				{
					pointer = pointer->ptr[i+1];
					break;
				}
			}
		}
	
		if(pointer->size < MAX)
		{
			
			int i = 0;
			while(x > pointer->key[i] && i < pointer->size) i++;
			
			for(int j = pointer->size;j > i; j--)
			{
				pointer->key[j] = pointer->key[j-1];
			}
			pointer->key[i] = x;
			pointer->size++;
			pointer->ptr[pointer->size] = pointer->ptr[pointer->size-1];
			pointer->ptr[pointer->size-1] = NULL;
			cout<<"Inserted "<<x<<" successfully\n";
		}
		else
		{
			cout<<"Inserted "<<x<<" successfully\n";
			cout<<"Overflow in leaf node!\nSplitting leaf node\n";
		
			Node* newLeaf = new Node;
			
			int virtualNode[MAX+1];
			for(int i = 0; i < MAX; i++)
			{
				virtualNode[i] = pointer->key[i];
			}
			int i = 0, j;
			while(x > virtualNode[i] && i < MAX) i++;
		
			for(int j = MAX+1;j > i; j--)
			{
				virtualNode[j] = virtualNode[j-1];
			}
			virtualNode[i] = x; 
			newLeaf->IS_LEAF = true;
		
			pointer->size = (MAX+1)/2;
			newLeaf->size = MAX+1-(MAX+1)/2;
		
			pointer->ptr[pointer->size] = newLeaf;
			
			newLeaf->ptr[newLeaf->size] = pointer->ptr[MAX];
			pointer->ptr[MAX] = NULL;
		
			for(i = 0; i < pointer->size; i++)
			{
				pointer->key[i] = virtualNode[i];
			}
			for(i = 0, j = pointer->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i] = virtualNode[j];
			}
			
			if(pointer == root)
			{
				
				Node* newRoot = new Node;
				newRoot->key[0] = newLeaf->key[0];
				newRoot->ptr[0] = pointer;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
				cout<<"Created new root\n";
			}
			else
			{
			
				Insert_Internally(newLeaf->key[0],parent,newLeaf);
			}
		}
	}
}
void BPTree::Insert_Internally(int x, Node* pointer, Node* child)
{
	if(pointer->size < MAX)
	{
		
		int i = 0;
		while(x > pointer->key[i] && i < pointer->size) i++;
		
		for(int j = pointer->size;j > i; j--)
		{
			pointer->key[j] = pointer->key[j-1];
		}
		for(int j = pointer->size+1; j > i+1; j--)
		{
			pointer->ptr[j] = pointer->ptr[j-1];
		}
		pointer->key[i] = x;
		pointer->size++;
		pointer->ptr[i+1] = child;
		cout<<"Inserted key in an Internal node successfully\n";
	}
	else
	{
		cout<<"Inserted key in an Internal node successfully\n";
		cout<<"Overflow in internal node!\nSplitting internal node\n";
	
		Node* newInternal = new Node;
		
		int virtualKey[MAX+1];
		Node* virtualPtr[MAX+2];
		for(int i = 0; i < MAX; i++)
		{
			virtualKey[i] = pointer->key[i];
		}
		for(int i = 0; i < MAX+1; i++)
		{
			virtualPtr[i] = pointer->ptr[i];
		}
		int i = 0, j;
		while(x > virtualKey[i] && i < MAX) i++;
	
		for(int j = MAX+1;j > i; j--)
		{
			virtualKey[j] = virtualKey[j-1];
		}
		virtualKey[i] = x; 
	
		for(int j = MAX+2;j > i+1; j--)
		{
			virtualPtr[j] = virtualPtr[j-1];
		}
		virtualPtr[i+1] = child; 
		newInternal->IS_LEAF = false;
		
		pointer->size = (MAX+1)/2;
		newInternal->size = MAX-(MAX+1)/2;
	
		for(i = 0, j = pointer->size+1; i < newInternal->size; i++, j++)
		{
			newInternal->key[i] = virtualKey[j];
		}
		for(i = 0, j = pointer->size+1; i < newInternal->size+1; i++, j++)
		{
			newInternal->ptr[i] = virtualPtr[j];
		}
	
		if(pointer == root)
		{
			
			Node* newRoot = new Node;
			newRoot->key[0] = pointer->key[pointer->size];
			newRoot->ptr[0] = pointer;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = false;
			newRoot->size = 1;
			root = newRoot;
			cout<<"Created new root\n";
		}
		else
		{
		
			Insert_Internally(pointer->key[pointer->size] ,Find_The_Parent(root,pointer) ,newInternal);
		}
	}
}
Node* BPTree::Find_The_Parent(Node* pointer, Node* child)
{

	Node* parent;
	if(pointer->IS_LEAF || (pointer->ptr[0])->IS_LEAF)
	{
		return NULL;
	}
	for(int i = 0; i < pointer->size+1; i++)
	{
		if(pointer->ptr[i] == child)
		{
			parent = pointer;
			return parent;
		}
		else
		{
			parent = Find_The_Parent(pointer->ptr[i],child);
			if(parent!=NULL)return parent;
		}
	}
	return parent;
}
void BPTree::Remove (int x)
{

	if(root==NULL)
	{
		cout<<"Tree empty\n";
	}
	else
	{
		Node* pointer = root;
		Node* parent;
		int leftSibling, rightSibling;
	
		while(pointer->IS_LEAF == false)
		{
			for(int i = 0; i < pointer->size; i++)
			{
				parent = pointer;
				leftSibling = i-1; 
				rightSibling =  i+1; 
				if(x < pointer->key[i])
				{	
					pointer = pointer->ptr[i];
					break;
				}
				if(i == pointer->size - 1)
				{
					leftSibling = i;
					rightSibling = i+2;
					pointer = pointer->ptr[i+1];
					break;
				}
			}
		}
	
		bool found = false;
		int pos;
		for(pos = 0; pos < pointer->size; pos++)
		{
			if(pointer->key[pos] == x)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			cout<<"Not found\n";
			return;
		}
	
		for(int i = pos; i < pointer->size; i++)
		{
			pointer->key[i] = pointer->key[i+1];
		}
		pointer->size--;
		if(pointer == root)
		{
			cout<<"Deleted "<<x<<" from leaf node successfully\n";
			for(int i = 0; i < MAX+1; i++)
			{
				pointer->ptr[i] = NULL;
			}
			if(pointer->size == 0)
			{
				cout<<"Tree died\n";
				delete[] pointer->key;
				delete[] pointer->ptr;
				delete pointer;
				root = NULL;
			}
			return;
		}
		pointer->ptr[pointer->size] = pointer->ptr[pointer->size+1];
		pointer->ptr[pointer->size+1] = NULL;
		cout<<"Deleted "<<x<<" from leaf node successfully\n";
		if(pointer->size >= (MAX+1)/2)
		{
			return;
		}
		cout<<"Underflow in leaf node!\n";
		
		if(leftSibling >= 0)
		{
			Node *leftNode = parent->ptr[leftSibling];
		
			if(leftNode->size >= (MAX+1)/2+1)
			{
			
				for(int i = pointer->size; i > 0; i--)
				{
					pointer->key[i] = pointer->key[i-1];
				}
				
				pointer->size++;
				pointer->ptr[pointer->size] = pointer->ptr[pointer->size-1];
				pointer->ptr[pointer->size-1] = NULL;
				
				pointer->key[0] = leftNode->key[leftNode->size-1];
				
				leftNode->size--;
				leftNode->ptr[leftNode->size] = pointer;
				leftNode->ptr[leftNode->size+1] = NULL;
			
				parent->key[leftSibling] = pointer->key[0];
				cout<<"Transferred "<<pointer->key[0]<<" from left sibling of leaf node\n";
				return;
			}
		}
		if(rightSibling <= parent->size)//check if right sibling exist
		{
			Node *rightNode = parent->ptr[rightSibling];
			
			if(rightNode->size >= (MAX+1)/2+1)
			{
			
				pointer->size++;
				pointer->ptr[pointer->size] = pointer->ptr[pointer->size-1];
				pointer->ptr[pointer->size-1] = NULL;
			
				pointer->key[pointer->size-1] = rightNode->key[0];
				
				rightNode->size--;
				rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size+1];
				rightNode->ptr[rightNode->size+1] = NULL;
				
				for(int i = 0; i < rightNode->size; i++)
				{
					rightNode->key[i] = rightNode->key[i+1];
				}
			
				parent->key[rightSibling-1] = rightNode->key[0];
				cout<<"Transferred "<<pointer->key[pointer->size-1]<<" from right sibling of leaf node\n";
				return;
			}
		}
	
		if(leftSibling >= 0)
		{
			Node* leftNode = parent->ptr[leftSibling];
		
			for(int i = leftNode->size, j = 0; j < pointer->size; i++, j++)
			{
				leftNode->key[i] = pointer->key[j];
			}
			leftNode->ptr[leftNode->size] = NULL;
			leftNode->size += pointer->size;
			leftNode->ptr[leftNode->size] = pointer->ptr[pointer->size];
			cout<<"Merging two leaf nodes\n";
			Remove_Internally(parent->key[leftSibling],parent,pointer);
			delete[] pointer->key;
			delete[] pointer->ptr;
			delete pointer;
		}
		else if(rightSibling <= parent->size)
		{
			Node* rightNode = parent->ptr[rightSibling];
		
			for(int i = pointer->size, j = 0; j < rightNode->size; i++, j++)
			{
				pointer->key[i] = rightNode->key[j];
			}
			pointer->ptr[pointer->size] = NULL;
			pointer->size += rightNode->size;
			pointer->ptr[pointer->size] = rightNode->ptr[rightNode->size];
			cout<<"Merging two leaf nodes\n";
			Remove_Internally(parent->key[rightSibling-1],parent,rightNode);
			delete[] rightNode->key;
			delete[] rightNode->ptr;
			delete rightNode;
		}
	}
}
void BPTree::Remove_Internally(int x, Node* pointer, Node* child)
{

	if(pointer == root)
	{
		if(pointer->size == 1)
		{
			if(pointer->ptr[1] == child)
			{
				delete[] child->key;
				delete[] child->ptr;
				delete child;
				root = pointer->ptr[0];
				delete[] pointer->key;
				delete[] pointer->ptr;
				delete pointer;
				cout<<"Changed root node\n";
				return;
			}
			else if(pointer->ptr[0] == child)
			{
				delete[] child->key;
				delete[] child->ptr;
				delete child;
				root = pointer->ptr[1];
				delete[] pointer->key;
				delete[] pointer->ptr;
				delete pointer;
				cout<<"Changed root node\n";
				return;
			}
		}
	}
	int pos;
	for(pos = 0; pos < pointer->size; pos++)
	{
		if(pointer->key[pos] == x)
		{
			break;
		}
	}
	for(int i = pos; i < pointer->size; i++)
	{
		pointer->key[i] = pointer->key[i+1];
	}

	for(pos = 0; pos < pointer->size+1; pos++)
	{
		if(pointer->ptr[pos] == child)
		{
			break;
		}
	}
	for(int i = pos; i < pointer->size+1; i++)
	{
		pointer->ptr[i] = pointer->ptr[i+1];
	}
	pointer->size--;
	if(pointer->size >= (MAX+1)/2-1)
	{
		cout<<"Deleted "<<x<<" from internal node successfully\n";
		return;
	}
	cout<<"Underflow in internal node!\n";

	if(pointer==root)return;
	Node* parent = Find_The_Parent(root, pointer);
	int leftSibling, rightSibling;
	
	for(pos = 0; pos < parent->size+1; pos++)
	{
		if(parent->ptr[pos] == pointer)
		{
			leftSibling = pos - 1;
			rightSibling = pos + 1;
			break;
		}
	}

	if(leftSibling >= 0)
	{
		Node *leftNode = parent->ptr[leftSibling];
	
		if(leftNode->size >= (MAX+1)/2)
		{
		
			for(int i = pointer->size; i > 0; i--)
			{
				pointer->key[i] = pointer->key[i-1];
			}
		
			pointer->key[0] = parent->key[leftSibling];
			parent->key[leftSibling] = leftNode->key[leftNode->size-1];
		
			for (int i = pointer->size+1; i > 0; i--)
			{
				pointer->ptr[i] = pointer->ptr[i-1];
			}
			
			pointer->ptr[0] = leftNode->ptr[leftNode->size];
			pointer->size++;
			leftNode->size--;
			cout<<"Transferred "<<pointer->key[0]<<" from left sibling of internal node\n";
			return;
		}
	}
	if(rightSibling <= parent->size)
	{
		Node *rightNode = parent->ptr[rightSibling];
	
		if(rightNode->size >= (MAX+1)/2)
		{
		
			pointer->key[pointer->size] = parent->key[pos];
			parent->key[pos] = rightNode->key[0];
			for (int i = 0; i < rightNode->size -1; i++)
			{
				rightNode->key[i] = rightNode->key[i+1];
			}
			
			pointer->ptr[pointer->size+1] = rightNode->ptr[0];
			for (int i = 0; i < rightNode->size; ++i)
			{
				rightNode->ptr[i] = rightNode->ptr[i+1];
			}
			pointer->size++;
			rightNode->size--;
			cout<<"Transferred "<<pointer->key[0]<<" from right sibling of internal node\n";
			return;
		}
	}
	
	if(leftSibling >= 0)
	{
	
		Node *leftNode = parent->ptr[leftSibling];
		leftNode->key[leftNode->size] = parent->key[leftSibling];
		for(int i = leftNode->size+1, j = 0; j < pointer->size; j++)
		{
			leftNode->key[i] = pointer->key[j];
		}
		for(int i = leftNode->size+1, j = 0; j < pointer->size+1; j++)
		{
			leftNode->ptr[i] = pointer->ptr[j];
			pointer->ptr[j] = NULL;
		}
		leftNode->size += pointer->size+1;
		pointer->size = 0;
	
		Remove_Internally(parent->key[leftSibling], parent, pointer);
		cout<<"Merged with left sibling\n";

	}
	else if(rightSibling <= parent->size)
	{
		
		Node *rightNode = parent->ptr[rightSibling];
		pointer->key[pointer->size] = parent->key[rightSibling-1];
		for(int i = pointer->size+1, j = 0; j < rightNode->size; j++)
		{
			pointer->key[i] = rightNode->key[j];
		}
		for(int i = pointer->size+1, j = 0; j < rightNode->size+1; j++)
		{
			pointer->ptr[i] = rightNode->ptr[j];
			rightNode->ptr[j] = NULL;
		}
		pointer->size += rightNode->size+1;
		rightNode->size = 0;
	
		Remove_Internally(parent->key[rightSibling-1], parent, rightNode);
		cout<<"Merged with right sibling\n";
	}
}
void BPTree::Display(Node* pointer)
{
	
	if(pointer!=NULL)
	{
		for(int i = 0; i < pointer->size; i++)
		{
			cout<<pointer->key[i]<<" ";
		}
		cout<<"\n";
		if(pointer->IS_LEAF != true)
		{
			for(int i = 0; i < pointer->size+1; i++)
			{
				Display(pointer->ptr[i]);
			}
		}
	}
}
Node* BPTree::Get_The_Root()
{
	return root;
}

