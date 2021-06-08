#include <iostream>
#include <QString>
#include <QFile>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QTextStream>
using namespace std;

QTextStream in(stdin);
QTextStream out(stdout);

#define line cout << "\n-----------------------------------------------------------------------------\n"

template<typename T>
class sQVector : public QVector<T>
{
public:
    int find(T target)
    {
        int i = 0;
        for (i = 0; i < this->size(); i++)
        {
            if(target.get_name() == (*this)[i].get_name())
            {
                if(target.get_pass() == (*this)[i].get_pass())
                    return i;
                else return -1;
            }
        }
        return -1;
    }
    bool find(QString target)
    {
        int i = 0;
        for (i = 0; i < this->size(); i++)
        {
            if(target == (*this)[i].get_name()) return true;
        }
        return false;
    }
};

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
    int id = 0;
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
    int get_id()
    {
        return this->id;
    }
    void set_id(int id)
    {
        this->id = id;
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

bool signup(sQVector<admin>& admins, sQVector<user>& users, int& idu )
{
    QString entry;
    system("cls");
    if(admins.empty())
    {
        admin a;
        line;
        cout << "\n\tThere is no admin, so you are signing up as an admin!!\n\a";
        line;
        while(true)
        {
            cout << "   Enter your username: (NO SPACE, ENTER 0 TO CANCEL)\n";
            in >> entry;
            if(entry == "0")
            {
                system("cls");
                return false;
            }
            if(users.find(entry))
            {
                system("cls");
                line;
                cout << "\t\t\tUsername is in use!\a";
                line;
                continue;
            }
            break;
        }
        a.set_name(entry);
        cout << "   Enter your password: (NO SPACE, ENTER 0 TO CANCEL)\n";
        in >> entry;
        if(entry == "0")
        {
            system("cls");
            return false;
        }
        a.set_pass(entry);
        a.set_id(1);
        admins.append(a);
        return true;
    }
    user u;
    line;
    line;
    while(true)
    {
        cout << "   Enter your username: (NO SPACE, ENTER 0 TO CANCEL)\n";
        in >> entry;
        if(entry == "0")
        {
            system("cls");
            return false;
        }
        if(users.find(entry))
        {
            system("cls");
            line;
            cout << "\t\t\tUsername is in use!\a";
            line;
            continue;
        }
        break;
    }
    u.set_name(entry);
    cout << "   Enter your password: (NO SPACE, ENTER 0 TO CANCEL)\n";
    in >> entry;
    if(entry == "0")
    {
        system("cls");
        return false;
    }
    u.set_pass(entry);
    u.set_id(idu++);
    users.append(u);
    return true;
}

int login(sQVector<admin>& admins, sQVector<user>& users)
{
    int index;
    QString entry;
    system("cls");
    line;
    line;
    while(true)
    {
        cout << "   Enter your username: (ENTER 0 TO CANCEL)\n";
        in >> entry;
        if(entry == "0")
        {
            system("cls");
            return -1;
        }
        if(users.find(entry))
        {
            user u;
            u.set_name(entry);
            while(true)
            {
                cout << "   Enter your password: (ENTER 0 TO CANCEL)\n";
                in >> entry;
                if(entry == "0")
                {
                    system("cls");
                    return -1;
                }
                u.set_pass(entry);
                index = users.find(u);
                if(index != -1)
                    return index;
                system("cls");
                line;
                cout << "\t\tPassword is incorrect Try again!\a";
                line;
            }

        }
        if(admins.find(entry))
        {
            admin a;
            a.set_name(entry);
            while(true)
            {
                cout << "   Enter your password: (ENTER 0 TO CANCEL)\n";
                in >> entry;
                if(entry == "0")
                {
                    system("cls");
                    return -1;
                }
                a.set_pass(entry);
                index = admins.find(a);
                if(index != -1)
                    return index;
                system("cls");
                line;
                cout << "\t\tPassword is incorrect Try again!\a";
                line;
            }
        }
        system("cls");
        line;
        cout << "\t\tUsername is incorrect Try again!\a";
        line;
    }
}

int main()
{
    sQVector<user> users;
    QMap<product,int> pros;
    sQVector<admin> admins;
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
        if(order == 1)
        {
            if(login(admins, users) != -1) ; //mainwindow();
            else continue;
        }
        if(order == 2)
        {
            if(signup(admins, users, idu)) ;//mainwindow();
            else continue;
        }
        if(order == 3) break;
    }
    system("cls");
    line;
    cout << "\n\n|------------------------- Hope to see you again :) -------------------------|\n";
    return 0;
}
