#include <string.h>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;
#define min(x,y) ((x)>(y)?(y):(x))
#define MAX 100
typedef struct TicketNode
{
	char name[20];    // 订票人的名字，不超过20个字符，中间不带空格
	int price;  // 订票的价格
    int time;
    int condition = 1;//默认售出不退
	TicketNode* next; // 指向下一个订票人的信息
} TicketNode;
//TicketNode* ticket = NULL;
int search(char a[], char b)
{
    int i = 0;
    while (a[i] != '\0')
    {
        if (a[i] ==b)
        {
            return i;
        }
        i++;
    }
    return -1;
}
char* substr(char a[], int pos, int n)
{ 
    char* b = a + pos;
    b[n] = '\0';
    return b;
}
void myprint(TicketNode* a)
{
    while (a != NULL)
    {
        if (a->condition != 0)
        {
            cout << a->name << " " << a->price << endl;
        }
        a = a->next;
    }
}
int convert(char num[])
{
    int a = 0;
    int len = strlen(num);
    for (int i = 0; i <= len - 1; i++)
    {
        a = (num[i] - '0') + a * 10;
    }
    return a;
}
TicketNode* save(TicketNode*& a,char name[],char price[],int time)
{
    int price2 = convert(price);
    TicketNode* b = new TicketNode;
    b->price = price2;
    b->time = time;
    int i = 0;
    while (name[i] != '\0')
    {
        b->name[i] = name[i];
        i++;
    }
    b->name[i] = '\0';
    b->next = NULL;
    if (a == NULL)
        a = b;
    else
    {
        TicketNode* cur = a;
        while (cur->next)
            cur = cur->next;
        cur->next = b;
    }
    return a;
}
void insertbyT(TicketNode*& a, TicketNode*& b)
{
    if (b->time < a->time)
    {
        b->next = a;
        a = b;
    }
    else {
        TicketNode* prev = a;
        TicketNode* cur = a;
        while (cur)
        {
            if (b->time < cur->time)
                break;
            prev = cur;
            cur = cur->next;
        }
        b->next = prev->next;
        prev->next = b;
        return;
    }
}
void insertbyP(TicketNode*& a, TicketNode*& b)
{
    if (b->price < a->price)
    {
        b->next = a;
        a = b;
    }
    else {
        TicketNode* prev = a;
        TicketNode* cur = a;
        while (cur)
        {
            if (b->price < cur->price)
                break;
            prev = cur;
            cur = cur->next;
        }
        b->next = prev->next;
        prev->next = b;
        return;
    }
}
void sortbyP(TicketNode*& a)
{
    if (a == NULL || a->next == NULL)
        return;
    else {
        TicketNode* cur = a->next;
        a->next = NULL;
        while (cur)
        {
            TicketNode* prev = cur;
            cur = cur->next;
            insertbyP(a, prev);
        }
    }
}
void sortbyT(TicketNode*& a)
{
    if (a == NULL || a->next == NULL)
        return;
    else {
        TicketNode* cur = a->next;
        a->next = NULL;
        while (cur)
        {
            TicketNode* prev = cur;
            cur = cur->next;
            insertbyT(a, prev);
        }
    }
}
void refund(TicketNode*& a,char *b)
{
    TicketNode* head = a;
    while (strcmp(head->name, b) != 0)
    {
        head = head->next;
    }
    head->condition = 0;
}
char *b[40]={NULL};
char a[100][100];
int main()
{
    int n;
    cin >> n;
    TicketNode* ticket = NULL;
    TicketNode* head = ticket;
    getchar();
    for (int i = 0; i < n; i++)
    {
        cin.getline(a[i], 50);
        b[i] = a[i];
    }
    for (int i = 0; i < n; i++)
    {
        int pos = search(b[i], ' ');
        char* first = substr(b[i], 0, pos);
        int len = strlen(b[i]);
        b[i] = substr(b[i], pos + 1, len-pos-1);
        pos = search(b[i], ' ');
        char* middle = substr(b[i], 0, pos);
        len= strlen(b[i]);
        b[i] = substr(b[i], pos + 1, len-pos-1);
        char* last = b[i];
        //cout << first << "\n" << middle << "\n" << last << endl;
        if (strcmp(first,"SALE")==0)
        {
            ticket = save(ticket, middle, last,i);
        }
        else if (strcmp(last, "TIME")==0)
        {
            sortbyT(ticket);
            myprint(ticket);
            cout << endl;
        }
        else if (strcmp(last, "PRICE")==0)
        {
            sortbyP(ticket);
            myprint(ticket);
            cout << endl;
        }
        else if (strcmp(first, "REFUND") == 0)
        {
            refund(ticket, middle);
        }
    }
	return 0;
}
