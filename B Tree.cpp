#include <iostream>
#include <conio.h>
 
using namespace std;
 
#define MAX 4
#define MIN 2
 
struct btreeNode 
{
    int val[MAX + 1], count;
    btreeNode *link[MAX + 1];
};
 
void free(void *ptr);
btreeNode *root;
btreeNode * createNode(int val, btreeNode *child);
void Add_Value_To_Node(int val, int pos, btreeNode *node, btreeNode *child);
void Split_The_Node(int val, int *pval, int pos, btreeNode *node,btreeNode *child, btreeNode **newNode);
int Set_Value_In_Node(int val, int *pval,btreeNode *node, btreeNode **child);
void Insertion(int val);
void Copy_The_Successor(btreeNode *myNode, int pos);
void Remove_The_Value(btreeNode *myNode, int pos);
void Do_RightShift(btreeNode *myNode, int pos);
void Do_LeftShift(btreeNode *myNode, int pos);
void Merge_The_Nodes(btreeNode *myNode, int pos);
void Adjust_The_Node(btreeNode *myNode, int pos);
int Del_Value_From_Node(int val,btreeNode *myNode);
void Deletion(int val,btreeNode *myNode);
void Searching(int val, int *pos,btreeNode *myNode);
void Traversal(btreeNode *myNode);

int main() 
{
    int val, option;
    while (true) {
        cout<<"1. Insertion\t2. Deletion\n";
        cout<<"3. Searching\t4. Traversal\n";
        cout<<"5. Exit\nEnter your choice: ";
        cin >> option;
        cout << endl;
        switch (option) {
       		case 1:
            	cout<<"Enter your input:";
            	cin >> val;
            	Insertion(val);
            	break;
        	case 2:
            	cout<<"Enter the element to delete:";
            	cin >> val;
            	Deletion(val, root);
            	break;
        	case 3:
            	cout<<"Enter the element to search:";
            	cin >> val;
            	Searching(val, &option, root);
            	break;
        	case 4:
            	Traversal(root);
            	break;
        	case 5:
            	exit(0);
        }
        cout << endl;
    }
 
    system("pause");
}

btreeNode * createNode(int val, btreeNode *child) {
    btreeNode *newNode = new btreeNode;
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}
 
void Add_Value_To_Node(int val, int pos, btreeNode *node, btreeNode *child) 
{
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}
 
void Split_The_Node(int val, int *pval, int pos, btreeNode *node,btreeNode *child, btreeNode **newNode) 
{
    int median, j;
 
    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;
 
    *newNode = new btreeNode;
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;
 
    if (pos <= MIN) {
        Add_Value_To_Node(val, pos, node, child);
    }
    else {
        Add_Value_To_Node(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}
 
int Set_Value_In_Node(int val, int *pval,btreeNode *node, btreeNode **child) 
{
 
    int pos;
    if (!node) {
        *pval = val;
        *child = NULL;
        return 1;
    }
 
    if (val < node->val[1]) {
        pos = 0;
    }
    else {
        for (pos = node->count;
            (val < node->val[pos] && pos > 1); pos--);
        if (val == node->val[pos]) {
            cout<<"Duplicates not allowed\n";
            return 0;
        }
    }
    if (Set_Value_In_Node(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            Add_Value_To_Node(*pval, pos, node, *child);
        }
        else {
            Split_The_Node(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}
 
void Insertion(int val) 
{
    int flag, i;
    btreeNode *child;
 
    flag = Set_Value_In_Node(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}
 
void Copy_The_Successor(btreeNode *myNode, int pos) 
{
    btreeNode *dummy;
    dummy = myNode->link[pos];
 
    for (; dummy->link[0] != NULL;)
        dummy = dummy->link[0];
    myNode->val[pos] = dummy->val[1];
 
}
 
void Remove_The_Value(btreeNode *myNode, int pos) 
{
    int i = pos + 1;
    while (i <= myNode->count) {
        myNode->val[i - 1] = myNode->val[i];
        myNode->link[i - 1] = myNode->link[i];
        i++;
    }
    myNode->count--;
}
 
void Do_RightShift(btreeNode *myNode, int pos) 
{
    btreeNode *x = myNode->link[pos];
    int j = x->count;
 
    while (j > 0) {
        x->val[j + 1] = x->val[j];
        x->link[j + 1] = x->link[j];
    }
    x->val[1] = myNode->val[pos];
    x->link[1] = x->link[0];
    x->count++;
 
    x = myNode->link[pos - 1];
    myNode->val[pos] = x->val[x->count];
    myNode->link[pos] = x->link[x->count];
    x->count--;
    return;
}
 
void Do_LeftShift(btreeNode *myNode, int pos) 
{
    int j = 1;
    btreeNode *x = myNode->link[pos - 1];
 
    x->count++;
    x->val[x->count] = myNode->val[pos];
    x->link[x->count] = myNode->link[pos]->link[0];
 
    x = myNode->link[pos];
    myNode->val[pos] = x->val[1];
    x->link[0] = x->link[1];
    x->count--;
 
    while (j <= x->count) {
        x->val[j] = x->val[j + 1];
        x->link[j] = x->link[j + 1];
        j++;
    }
    return;
}
 
void Merge_The_Nodes(btreeNode *myNode, int pos) 
{
    int j = 1;
    btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];
 
    x2->count++;
    x2->val[x2->count] = myNode->val[pos];
    x2->link[x2->count] = myNode->link[0];
 
    while (j <= x1->count) {
        x2->count++;
        x2->val[x2->count] = x1->val[j];
        x2->link[x2->count] = x1->link[j];
        j++;
    }
 
    j = pos;
    while (j < myNode->count) {
        myNode->val[j] = myNode->val[j + 1];
        myNode->link[j] = myNode->link[j + 1];
        j++;
    }
    myNode->count--;
    free(x1);
}
 

void Adjust_The_Node(btreeNode *myNode, int pos) 
{
    if (!pos) {
        if (myNode->link[1]->count > MIN) {
            Do_LeftShift(myNode, 1);
        }
        else {
            Merge_The_Nodes(myNode, 1);
        }
    }
    else {
        if (myNode->count != pos) {
            if (myNode->link[pos - 1]->count > MIN) {
                Do_RightShift(myNode, pos);
            }
            else {
                if (myNode->link[pos + 1]->count > MIN) {
                    Do_LeftShift(myNode, pos + 1);
                }
                else {
                    Merge_The_Nodes(myNode, pos);
                }
            }
        }
        else {
            if (myNode->link[pos - 1]->count > MIN)
                Do_RightShift(myNode, pos);
            else
                Merge_The_Nodes(myNode, pos);
        }
    }
}
 
int Del_Value_From_Node(int val,btreeNode *myNode) 
{
    int pos, flag = 0;
    if (myNode) {
        if (val < myNode->val[1]) {
            pos = 0;
            flag = 0;
        }
        else {
            for (pos = myNode->count;
                (val < myNode->val[pos] && pos > 1); pos--);
            if (val == myNode->val[pos]) {
                flag = 1;
            }
            else {
                flag = 0;
            }
        }
        if (flag) {
            if (myNode->link[pos - 1]) {
                Copy_The_Successor(myNode, pos);
                flag = Del_Value_From_Node(myNode->val[pos], myNode->link[pos]);
                if (flag == 0) {
                    cout<<"Given data is not present in B-Tree\n";
                }
            }
            else {
                Remove_The_Value(myNode, pos);
            }
        }
        else {
            flag = Del_Value_From_Node(val, myNode->link[pos]);
        }
        if (myNode->link[pos]) {
            if (myNode->link[pos]->count < MIN)
                Adjust_The_Node(myNode, pos);
        }
    }
    return flag;
}
 
void Deletion(int val,btreeNode *myNode) 
{
    btreeNode *tmp;
    if (!Del_Value_From_Node(val, myNode)) {
        cout<<"Given value is not present in B-Tree\n";
        return;
    }
    else {
        if (myNode->count == 0) {
            tmp = myNode;
            myNode = myNode->link[0];
            free(tmp);
        }
    }
    root = myNode;
    return;
}
 
void Searching(int val, int *pos,btreeNode *myNode) 
{
    if (!myNode) {
        return;
    }
 
    if (val < myNode->val[1]) {
        *pos = 0;
    }
    else {
        for (*pos = myNode->count;
            (val < myNode->val[*pos] && *pos > 1); (*pos)--);
        if (val == myNode->val[*pos]) {
            cout << "Given data is Found\n";
            return;
        }
    }
    Searching(val, pos, myNode->link[*pos]);
    return;
}
 
void Traversal(btreeNode *myNode) 
{
    int i;
    if (myNode) {
        for (i = 0; i < myNode->count; i++) {
            Traversal(myNode->link[i]);
            cout<< myNode->val[i + 1]<<' ';
        }
        Traversal(myNode->link[i]);
    }
}

void free(void *ptr)
{
}
