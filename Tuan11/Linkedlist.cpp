#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node* createNode(int data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void print(Node *head)
{
    Node *read = head;
    while(read != NULL)
    {
        cout << read->data << " ";
        read = read->next;
    }
}

Node *addLast(Node* head, int data)
{
    Node* temp = createNode(data);
    if(head == NULL)
    {
        return temp;
    }
    Node *p = head;
    while( p->next != NULL)
    {
        p = p->next;
    }
    p->next = temp;
    return head;
}

Node *addFirst(Node* head, int data)
{
    Node *temp = createNode(data);
    if(head == NULL)
    {
        return temp;
    }
    temp->next = head;
    head = temp;
    return head;
}

int main()
{
    int n, x;
    cin >> n >> x;

    Node *head = createNode(x);
    for(int i=1; i<n; i++)
    {
        cin >> x;
        head = addFirst(head, x);
    }
    print(head);

    return 0;
}