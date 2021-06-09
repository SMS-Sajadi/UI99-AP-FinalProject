#include <iostream>
#include <string>
#include <QVector>
using namespace std;


//QTextStream in(stdin);
//QTextStream out(stdout);

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
    bool find(string target)
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
    string name = "N/A";
    string producer = "N/A";
    int remaining = 0;
    string category = "N/A";
    bool sailable = false;
    unsigned int price;
public:
    string get_name()
    {
        return this->name;
    }
    string get_producer()
    {
        return this->producer;
    }
    int get_remaining()
    {
        return this->remaining;
    }
    string get_category()
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
    void set_name(string name)
    {
        this->name = name;
    }
    void set_producer(string producer)
    {
        this->producer = producer;
    }
    void set_remaining(int remaining)
    {
        this->remaining = remaining;
    }
    void set_category(string category)
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
    string name = "N/A";
    string pass = "N/A";
    bool buy = false;
    int id = 0;
    QVector<product> history;
public:
    string get_name()
    {
        return this->name;
    }
    string get_pass()
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
    void set_name(string name)
    {
        this->name = name;
    }
    void set_pass(string pass)
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

int signup(sQVector<admin>& admins, sQVector<user>& users, int& idu )
{
    string entry;
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
            cin >> entry;
            if(entry == "0")
            {
                system("cls");
                return -1;
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
        cin >> entry;
        if(entry == "0")
        {
            system("cls");
            return -1;
        }
        a.set_pass(entry);
        a.set_id(1);
        admins.append(a);
        return 1;
    }
    user u;
    line;
    line;
    while(true)
    {
        cout << "   Enter your username: (NO SPACE, ENTER 0 TO CANCEL)\n";
        cin >> entry;
        if(entry == "0")
        {
            system("cls");
            return -1;
        }
        if(users.find(entry) || admins.find(entry))
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
    cin >> entry;
    if(entry == "0")
    {
        system("cls");
        return -1;
    }
    u.set_pass(entry);
    u.set_id(idu++);
    users.append(u);
    return idu - 1;
}

int login(sQVector<admin>& admins, sQVector<user>& users)
{
    int index;
    string entry;
    system("cls");
    line;
    line;
    while(true)
    {
        cout << "   Enter your username: (ENTER 0 TO CANCEL)\n";
        cin >> entry;
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
                cin >> entry;
                if(entry == "0")
                {
                    system("cls");
                    return -1;
                }
                u.set_pass(entry);
                index = users.find(u);
                if(index != -1)
                    return users[index].get_id();
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
                cin >> entry;
                if(entry == "0")
                {
                    system("cls");
                    return -1;
                }
                a.set_pass(entry);
                index = admins.find(a);
                if(index != -1)
                    return admins[index].get_id();
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
    QVector<product> pros;
    sQVector<admin> admins;
    int idp = 12000, idu = 1500, order, check;
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
            check = login(admins, users);
            if(check != -1) ; //mainwindow();
            else continue;
        }
        if(order == 2)
        {
            check = signup(admins, users, idu);
            if(check != -1) ;//mainwindow();
            else continue;
        }
        if(order == 3) break;
    }
    system("cls");
    line;
    cout << "\n\n|------------------------- Hope to see you again :) -------------------------|\n";
    return 0;
}
