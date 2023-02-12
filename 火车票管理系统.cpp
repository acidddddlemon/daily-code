//系统业务功能如下：
//1、售票
//2、退票
//3、按票价升序排序输出系统已售票信息
//4、按时间顺序输出系统已售票信息
//四种功能在系统中均以请求的形式呈现，请求的先后顺序代表了时间线的先后顺序。
//
//输入
//第一行输入一个正整数n，代表共有n个请求
//接下来的n行，每一行代表一个请求
//请求格式如下：
//请求	格式	含义
//售票	SALE NAME PRICE	将票以PRICE的价格售卖给NAME
//退票	REFUND NAME	NAME退掉已购买的票
//输出已售票信息	DISPLAY BY PRICE	按票价升序排序输出系统已售票信息
//输出已售票信息	DISPLAY BY TIME	按时间顺序输出系统已售票信息
//题目保证所有输入合法（即不会同时售卖给同一个人多张票且退票操作保证该用户存在已经购买的票）
//
//输出
//对于售票和退票
//售票：无需输出任何信息
//退票：无需输出任何信息
//
//对于输出已售票信息，需要按照要求的顺序将售票信息输出，每个人的售票信息单独一行，格式为
//NAME PRICE（用空格隔开）
//样例：
//输入：
//5
//SALE BOB 100
//SALE ALICE 200
//DISPLAY BY TIME
//REFUND BOB
//DISPLAY BY PRICE
//输出：
//BOB 100
//ALICE 200
//
//ALICE 200
//以下是代码部分：
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;
#define min(x,y) ((x)>(y)?(y):(x))
typedef struct TicketNode
{
    char name[20];    // 订票人的名字，不超过20个字符，中间不带空格
    int price;  // 订票的价格
    int time;
    int condition = 1;//默认售出不退
    TicketNode* next; // 指向下一个订票人的信息
} TicketNode;
//TicketNode* ticket = NULL;

//大致同于string类中的find方法
//用于查找字符串中是否有要寻找的字符，有则返回下标数，无返回-1
int search(char a[], char b)
{
    int i = 0;
    while (a[i] != '\0')
    {
        if (a[i] == b)
        {
            return i;
        }
        i++;
    }
    return -1;
}
char* substr(char a[], int pos, int n)//实现字符串的分割（实现的并不好，因为也修改了原有字符串，只是侥幸这道题能过）.用于截取从pos位置起查n个字符的字符串（n=-1则从pos截到尾部）
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
int convert(char num[])//实现数字从字符串变成真正的int数字
{
    int a = 0;
    int len = strlen(num);
    for (int i = 0; i <= len - 1; i++)
    {
        a = (num[i] - '0') + a * 10;
    }
    return a;
}
TicketNode* save(TicketNode*& a, char name[], char price[], int time)
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
void sortbyP(TicketNode*& a)//链表插入排序算法
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
void refund(TicketNode*& a, char* b)//实现退票功能（正常退票应该直接删除那个节点的，本人 too lazy, so just add a parameter in struct.）
{
    TicketNode* head = a;
    while (strcmp(head->name, b) != 0)
    {
        head = head->next;
    }
    head->condition = 0;
}
char* b[40] = { NULL };
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
        b[i] = substr(b[i], pos + 1,  -1);
        pos = search(b[i], ' ');
        char* middle = substr(b[i], 0, pos);
        b[i] = substr(b[i], pos + 1, -1);
        char* last = b[i];
        //cout << first << "\n" << middle << "\n" << last << endl;
        if (strcmp(first, "SALE") == 0)
        {
            ticket = save(ticket, middle, last, i);
        }
        else if (strcmp(last, "TIME") == 0)
        {
            sortbyT(ticket);
            myprint(ticket);
            cout << endl;
        }
        else if (strcmp(last, "PRICE") == 0)
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
