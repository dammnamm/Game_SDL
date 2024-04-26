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

int getSize(Node *head)
{
    int cnt = 0;
    Node *temp = head;
    while(temp != NULL)
    {
        cnt ++;
        temp = temp->next;
    }
    return cnt;
}

Node *insert(Node *head, int pos, int data)
{
    if(pos == 0)
    {
        head = addFirst(head, data);
    }else if(pos == getSize(head) - 1)
    {
        head = addLast(head, data);
    }else {
        Node *newNode = createNode(data);
        Node *temp = head;
        for(int i=0; i<pos; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
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
        head = addLast(head, x);
    }
    insert(head, 2, 100);
    print(head);

    return 0;
}