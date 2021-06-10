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
    int find(int id)
    {
        int i = 0;
        for (i = 0; i < this->size(); i++)
        {
            if(id == (*this)[i].get_id()) return i;
        }
        return -1;
    }
};

class product
{
private:
    string name = "N/A";
    string producer = "N/A";
    int remaining = 0;
    int id = 0;
    string category = "N/A";
    bool saleable = false;
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
    bool get_saleable()
    {
        return this->saleable;
    }
    unsigned int get_price()
    {
        return this->price;
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
    void set_saleable(bool saleable)
    {
        this->saleable = saleable;
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
    bool buy = true;
    int id = 0;
    sQVector<product> history;
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
    void show_history()
    {
        cout << " Product"<<"                    " << "ID" << "       " << "Category" << "          " << "Number" << "   " << "Price" << endl;
        for(int i = 0; i < history.size(); i++)
        {
            cout << history[i].get_name() << history[i].get_id() << history[i].get_category() << history[i].get_remaining() << history[i].get_price() << endl;
        }
    }
};

class admin : public user
{
public:
    template<typename T>
    int delu(T& data, int id)
    {
        int index = data.find(id);
        if(index != -1)
        {
            data.remove(index);
            return 1;
        }
        return -1;
    }
    int add_admin(int id, sQVector<admin>& admins, sQVector<user>& users)
    {
        admin a;
        int index = users.find(id);
        if(index != -1)
        {
            a.set_name(users[index].get_name());
            a.set_pass(users[index].get_pass());
            a.set_id(admins.size() + 1);
            admins.append(a);
            users.remove(index);
            return 1;
        }
        return -1;
    }
    bool ch_block(sQVector<user>& users, int id)
    {
        int index = users.find(id);
        if(index != -1)
        {
            users[index].set_buy(!users[index].get_buy());
            return true;
        }
        return false;
    }
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

bool check_error(int num)
{
    if(num < 0)
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

template<typename T>
void table(T& data)
{
    line;
    cout << " NAME" << "                    " << "ID" << "                   " << "BLOCK\n\n";
    for(int i = 0; i < data.size(); i++)
    {
        cout << "  " << data[i].get_name() << " -------------- " << data[i].get_id() << " -------------- ";
        if(data[i].get_buy()) cout << "FALSE" << endl;
        else cout << "TRUE" << endl;
    }
}

void tablep(sQVector<product>& pros, bool user)
{
    line;
    if(!user)
    {
        for(int i = 0; i < pros.size(); i++)
        {
            cout << " NAME:" << "               " << pros[i].get_name() << "ID:" << "               " << pros[i].get_id() << endl;
            cout << " PRICE:" << "               " << pros[i].get_price() << "REMAINING:" << "               " << pros[i].get_remaining() << endl;
            cout << " PRODUCER:" << "               " << pros[i].get_producer() << "CATEGOTY:" << "               " << pros[i].get_category() << endl;
            cout << " SALEABLE:" << "               ";
            if(pros[i].get_saleable()) cout << "TRUE" << endl;
            else cout << "FALSE" << endl;
            if(i != pros.size() - 1) cout << "\t\t----------------------------------------------\n\n";
        }
        return;
    }
    for(int i = 0; i < pros.size(); i++)
    {
        if(pros[i].get_saleable())
        {
            cout << " NAME:" << "               " << pros[i].get_name() << "ID:" << "               " << pros[i].get_id() << endl;
            cout << " PRICE:" << "               " << pros[i].get_price() << "REMAINING:" << "               " << pros[i].get_remaining() << endl;
            cout << " PRODUCER:" << "               " << pros[i].get_producer() << "CATEGOTY:" << "               " << pros[i].get_category() << endl;
            cout << "\t\t----------------------------------------------\n\n";
        }
    }
}

void mainwindow(sQVector<admin>& admins, sQVector<user>& users, int id, sQVector<product>& pros, int& idp)
{
    int order, idd;
    system("cls");
    if(id < 1500)
    {
        while(true)
        {
            line;
            cout << "\t\t\t * Welcome " << admins[id - 1].get_name() << " *";
            line;
            cout << "\t\tEnter of the numbers below:\n";
            cout << "\t1)Log Out\n\t2)View Users\n\t3)View Products\n\t4)View Purchase Log\n";
            line;
            cin >> order;
            if(check_error(order, 1, 4)) continue;
            if(order == 1)
            {
                system("cls");
                return;
            }
            if(order == 2)
            {
                system("cls");
                while(true)
                {
                    cout << "\tAdmins are:";
                    table(admins);
                    line;
                    cout << "\tUsers are:";
                    table(users);
                    line;
                    cout << "  Enter one of the numbers below:\n\n";
                    cout << "\t1)Return\t2)Add admin\t3)Delete User\t4)Block/Unblock user\t5)View User History\n";
                    cin >> order;
                    if(check_error(order, 1, 5)) continue;
                    if(order == 1)
                    {
                        system("cls");
                        break;
                    }
                    if(order == 2)
                    {
                        while(true)
                        {
                            cout << "  Enter the user id to add as an admin: (ENTER 0 TO CANCEL)\n";
                            cin >> idd;
                            if(idd == 0)
                            {
                                system("cls");
                                break;
                            }
                            if(admins[id - 1].add_admin(idd, admins, users) != -1)
                            {
                                system("cls");
                                line;
                                cout << "\t\t\tAdmin added!\a";
                                line;
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tID is incorrect!\a";
                            line;
                            cout << "\tAdmins are:";
                            table(admins);
                            line;
                            cout << "\tUsers are:";
                            table(users);
                            line;
                        }
                        continue;
                    }
                    if(order == 3)
                    {
                        while(true)
                        {
                            cout << "  Enter the user id to delete: (ENTER 0 TO CANCEL)\n";
                            cin >> idd;
                            if(idd == 0)
                            {
                                system("cls");
                                break;
                            }
                            if(admins[id - 1].delu(users, idd) != -1)
                            {
                                system("cls");
                                line;
                                cout << "\t\t\tUser deleted!\a";
                                line;
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tID is incorrect!\a";
                            line;
                            cout << "\tAdmins are:";
                            table(admins);
                            line;
                            cout << "\tUsers are:";
                            table(users);
                            line;
                        }
                        continue;
                    }
                    if(order == 4)
                    {
                        while(true)
                        {
                            cout << "  Enter the user id to block/unblock: (ENTER 0 TO CANCEL)\n";
                            cin >> idd;
                            if(idd == 0)
                            {
                                system("cls");
                                break;
                            }
                            if(admins[id - 1].ch_block(users, idd))
                            {
                                system("cls");
                                line;
                                cout << "\t\t\tUser blocked/unblocked!\a";
                                line;
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tID is incorrect!\a";
                            line;
                            cout << "\tAdmins are:";
                            table(admins);
                            line;
                            cout << "\tUsers are:";
                            table(users);
                            line;
                        }
                        continue;
                    }
                    if(order == 5)
                    {
                        while(true)
                        {
                            cout << "  Enter the user id to see history: (ENTER 0 TO CANCEL)\n";
                            cin >> idd;
                            if(idd == 0)
                            {
                                system("cls");
                                break;
                            }
                            int index = users.find(idd);
                            if(index != -1)
                            {
                                line;
                                users[index].show_history();
                                line;
                                cout << "  Enter any key to return:\n";
                                system("pause");
                                system("cls");
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tID is incorrect!\a";
                            line;
                            cout << "\tAdmins are:";
                            table(admins);
                            line;
                            cout << "\tUsers are:";
                            table(users);
                            line;
                        }
                        continue;
                    }
                }
                continue;
            }
            if(order == 3)
            {
                system("cls");
                while(true)
                {
                   cout << "\tProducts are:";
                   tablep(pros, false);
                   line;
                   cout << "  Enter one of the numbers below:\n\n";
                   cout << "\t1)Return\t2)Add product\t3)Delete product\t4)Change product\n";
                   cin >> order;
                   if(check_error(order, 1, 4)) continue;
                   if(order == 1)
                   {
                       system("cls");
                       break;
                   }
                   if(order == 2)
                   {
                       system("cls");
                       product p;
                       string entry;
                       int num;
                       while(true)
                       {
                           cout << "  Enter the name of product: (ENTER 0 TO CANCEL)\n";
                           cin.ignore();
                           getline(cin, entry);
                           if(entry == "0")
                           {
                               system("cls");
                               break;
                           }
                           p.set_name(entry);
                           cout << "  Enter the name of producer: (ENTER 0 TO CANCEL)\n";
                           getline(cin, entry);
                           if(entry == "0")
                           {
                               system("cls");
                               break;
                           }
                           p.set_producer(entry);
                           cout << "  Enter the category: (ENTER 0 TO CANCEL)\n";
                           getline(cin, entry);
                           if(entry == "0")
                           {
                               system("cls");
                               break;
                           }
                           p.set_category(entry);
                           while(true)
                           {
                               cout << "  Enter the price:\n";
                               cin >> num;
                               if(check_error(num)) continue;
                               p.set_price(num);
                               break;
                           }
                           while(true)
                           {
                               cout << "  Enter the remaining:\n";
                               cin >> num;
                               if(check_error(num)) continue;
                               p.set_remaining(num);
                               break;
                           }
                           while(true)
                           {
                               cout << "  Do you want to make it saleable? (1 == YES, 2 == NO)\n";
                               cin >> num;
                               if(check_error(num, 1, 2)) continue;
                               if(num == 1) p.set_saleable(true);
                               else p.set_saleable(false);
                               break;
                           }
                           p.set_id(idp++);
                           pros.append(p);
                           system("cls");
                           line;
                           cout << "\t\t\tProduct added!\a";
                           line;
                           break;
                       }
                       continue;
                   }
                }
                continue;
            }
            if(order == 4)
            {
                system("cls");
                line;
                admins[0].show_history();
                line;
                cout << "  Enter any key to return:\n";
                system("pause");
                system("cls");
                continue;
            }
        }
    }
}

int main()
{
    sQVector<user> users;
    sQVector<product> pros;
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
            if(check != -1) mainwindow(admins, users, check, pros, idp);
            else continue;
        }
        if(order == 2)
        {
            check = signup(admins, users, idu);
            if(check != -1) mainwindow(admins, users, check, pros, idp);
            else continue;
        }
        if(order == 3) break;
    }
    system("cls");
    line;
    cout << "\n\n|------------------------- Hope to see you again :) -------------------------|\n";
    return 0;
}
