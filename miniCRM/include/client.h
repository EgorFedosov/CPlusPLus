#ifndef CLIENT_H
#define CLIENT_H

struct Client
{
    char name[100];
    char phone[20];
    char product[100];
    int day;
    int month;
    int year;
    int quantity;
    double amount;
};

#endif 
