#include <iostream>
#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
using namespace std;

#define line cout << "\n-----------------------------------------------------------------------------\n"
class product
{
private:
    QString name = "N/A";
    QString producer = "N/A";
    int remaining = 0;
    QString category = "N/A";
    bool sailable = false;
    unsigned int price;
public:
    QString get_name()
    {
        return this->name;
    }
    QString get_producer()
    {
        return this->producer;
    }
    int get_remaining()
    {
        return this->remaining;
    }
    QString get_category()
    {
        return this->category;
    }
    bool get_sailable()
    {
        return this->sailable;
    }
    unsigned int get_price()
    {
        return this->price;
    }
    void set_name(QString name)
    {
        this->name = name;
    }
    void set_producer(QString producer)
    {
        this->producer = producer;
    }
    void set_remaining(int remaining)
    {
        this->remaining = remaining;
    }
    void set_category(QString category)
    {
        this->category = category;
    }
    void set_sailable(bool sailable)
    {
        this->sailable = sailable;
    }
    void set_price(unsigned int price)
    {
        this->remaining = price;
    }
};

class user
{
protected:
    QString name = "N/A";
    QString pass = "N/A";
    bool buy = false;
    QVector<product> history;
public:
    QString get_name()
    {
        return this->name;
    }
    QString get_pass()
    {
        return this->pass;
    }
    bool get_buy()
    {
        return this->buy;
    }
    void set_name(QString name)
    {
        this->name = name;
    }
    void set_pass(QString pass)
    {
        this->pass = pass;
    }
    void set_buy(bool buy)
    {
        this->buy = buy;
    }
};

class admin : public user
{

};

template<typename T>
bool check_error(T order, T first, T sec)
{
    if(order < first || order > sec)
    {
        system("cls");
        cin.clear();
        cin.ignore();
        cout << "\n-------------------------- Wrong Input Try Again! --------------------------\a\n";
        return true;
    }
    return false;
}

int main()
{
    QMap<user,int> users;
    QMap<product,int> pros;
    QMap<admin,int> admins;
    int idp = 12000, idu = 1500, order;
    while(true)
    {
        cout << "\n\t   ********* Welcome to the Soroush Shoping Mall *********" << endl;
        line;
        cout << "\n   Enter one of the numbers below :\n";
        cout << "\n\n\t1)Login\t\t2)Sign up\t3)Exit\n\n";
        line;
        cin >> order;
        if(check_error(order, 1, 3)) continue;
        if(order == 3) break;
    }
    system("cls");
    line;
    cout << "\n\n|------------------------- Hope to see you again :) -------------------------|\n";
    return 0;
}
