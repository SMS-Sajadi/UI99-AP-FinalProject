#include <iostream>
#include <string>
#include <QVector>
#include <iomanip>
#include <fstream>
using namespace std;

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
    int find(string target)
    {
        int i = 0;
        for (i = 0; i < this->size(); i++)
        {
            if(target == (*this)[i].get_name()) return i;
        }
        return -1;
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
    double price;
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
    double get_price()
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
        if (remaining == 0) this->set_saleable(false);
    }
    void set_category(string category)
    {
        this->category = category;
    }
    void set_saleable(bool saleable)
    {
        this->saleable = saleable;
    }
    void set_price(double price)
    {
        this->price = price;
    }
    bool search(string target)
    {
        unsigned int j = 0;
        for(unsigned int i = 0; i < this->name.size(); i++)
        {
            if(target[0] == name[i])
            {
                j++;
                i++;
                while(j < target.size() && i < name.size())
                {
                    if(target[j] != name[i]) break;
                    j++;
                    i++;
                }
                if(j == target.size()) return true;
                j = 0;
            }
        }
        j = 0;
        for(unsigned int i = 0; i < this->producer.size(); i++)
        {
            if(target[0] == producer[i])
            {
                j++;
                i++;
                while(j < target.size() && i < producer.size())
                {
                    if(target[j] != producer[i]) break;
                    j++;
                    i++;
                }
                if(j == target.size()) return true;
                j = 0;
            }
        }
        j = 0;
        for(unsigned int i = 0; i < this->category.size(); i++)
        {
            if(target[0] == category[i])
            {
                j++;
                i++;
                while(j < target.size() && i < category.size())
                {
                    if(target[j] != category[i]) break;
                    j++;
                    i++;
                }
                if(j == target.size()) return true;
                j = 0;
            }
        }
        return false;
    }
};

class user
{
    friend void save_data();
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

        for(int i = 0; i < history.size(); i++)
        {
            cout << "\tProduct :\n" << history[i].get_name() << endl;
            cout << "\tID :\n" << history[i].get_id() << endl;
            cout << "\tCategory :\n" << history[i].get_category() << endl;
            cout << "\tNumbers :\n" << history[i].get_remaining() << endl;
            cout << "\tPrice :\n" << history[i].get_price() << endl;
            cout << "\t\t----------------------------------------------\n\n";
        }
    }
    void add_history(product p)
    {
        this->history.append(p);
    }
    void save_history(ofstream& file)
    {
        file << history.size() << endl;
        for(int i = 0; i < history.size(); i++)
        {
            file << history[i].get_name() << endl;
            file << history[i].get_producer() << endl;
            file << history[i].get_category() << endl;
            file << history[i].get_saleable() << endl;
            file << history[i].get_remaining() << endl;
            file << history[i].get_id() << endl;
            file << history[i].get_price() << endl;
        }
    }
    void load_history(ifstream& file)
    {
        int size, entry;
        double price;
        product p;
        string c;
        file >> size;
        file.ignore();
        for(int i = 0; i < size; i++)
        {
            getline(file, c);
            p.set_name(c);
            getline(file, c);
            p.set_producer(c);
            getline(file, c);
            p.set_category(c);
            file >> entry;
            p.set_saleable(bool(entry));
            file >> entry;
            p.set_remaining(entry);
            file >> entry;
            p.set_id(entry);
            file >> price;
            p.set_price(price);
            this->history.append(p);
            file.ignore();
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
class cQVector : public QVector<T>
{
public:
    int find(string target)
    {
        int i = 0;
        for (i = 0; i < this->size(); i++)
        {
            if(target == (*this)[i]) return i;
        }
        return -1;
    }
    void show()
    {
        line;
        for(int i = 0; i < this->size(); i++)
        {
            cout << "\t" << i+1 << ") " << (*this)[i] << endl;
        }
        if(this->size() == 0) cout << "\t\t\t~~~ Empty! ~~~";
        line;
    }
    void change(sQVector<product>& pros, string target, string newc = "N/A")
    {
        for(int i = 0; i < pros.size(); i++)
        {
            if(pros[i].get_category() == target)
                pros[i].set_category(newc);
        }
    }
    void show(sQVector<product>& pros, bool user, int index)
    {
        line;
        if(!user)
        {
            for(int i = 0; i < pros.size(); i++)
            {
                if(pros[i].get_category() == (*this)[index])
                {
                    cout << " NAME:" << "               " << pros[i].get_name() << "ID:" << "               " << pros[i].get_id() << endl;
                    cout << " PRICE:" << "               " << pros[i].get_price() << "REMAINING:" << "               " << pros[i].get_remaining() << endl;
                    cout << " PRODUCER:" << "               " << pros[i].get_producer() << endl;
                    cout << " SALEABLE:" << "               ";
                    if(pros[i].get_saleable()) cout << "TRUE" << endl;
                    else cout << "FALSE" << endl;
                    cout << "\t\t----------------------------------------------\n\n";
                }
            }
            line;
            return;
        }
        for(int i = 0; i < pros.size(); i++)
        {
            if(pros[i].get_saleable() && pros[i].get_category() == (*this)[index])
            {
                cout << " NAME:" << "               " << pros[i].get_name();
                cout << " PRICE:" << "               " << pros[i].get_price() <<  endl << "REMAINING:" << "               " << pros[i].get_remaining();
                cout << " PRODUCER:" << "               " << pros[i].get_producer() << endl;
                cout << "\t\t----------------------------------------------\n\n";
            }
        }
        line;
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
        cout << "\n|-------------------------- Wrong Input Try Again! --------------------------|\a\n\n";
        return true;
    }
    return false;
}

template<typename T>
bool check_error(T num)
{
    if(num < 0)
    {
        system("cls");
        cin.clear();
        cin.ignore();
        cout << "\n|-------------------------- Wrong Input Try Again! --------------------------|\a\n\n";
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
            if(users.find(entry) != -1)
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
        if((users.find(entry) != -1) || (admins.find(entry) != -1))
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
        if(users.find(entry) != -1)
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
        if(admins.find(entry) != -1)
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
    for(int i = 0; i < data.size(); i++)
    {
        cout << "  NAME :" << "\t\t" << data[i].get_name() << endl;
        cout << "  ID :" << setw(20) << data[i].get_id() << setw(15) << "BLOCK :";
        if(data[i].get_buy()) cout << "     NO" << endl;
        else cout << "     YES" << endl;
        if(i != data.size() - 1) cout << "\t\t----------------------------------------------\n\n";
    }
    if(data.empty()) cout << "\t\t\t~~~ Empty! ~~~";
}

void tablep(sQVector<product>& pros, bool user)
{
    line;
    bool print = false;
    if(!user)
    {
        for(int i = 0; i < pros.size(); i++)
        {
            cout << " NAME :" << "    \t\t" << pros[i].get_name() << endl;
            cout << " PRODUCER :" << "\t\t" << pros[i].get_producer() << endl;
            cout << " CATEGORY :" << "\t\t" << pros[i].get_category() << endl << endl;
            cout << " ID :" << setw(20) << pros[i].get_id() << setw(10) << "PRICE :" << setw(20) << pros[i].get_price() << setw(17);
            cout << " REMAINING :" << setw(15) << pros[i].get_remaining() << setw(15);
            cout << " SALEABLE :";
            if(pros[i].get_saleable()) cout << "     YES" << endl;
            else cout << "     NO" << endl;
            if(i != pros.size() - 1) cout << "\t\t--------------------------------------------------\n\n";
        }
        if(pros.empty()) cout << "\t\t\t~~~ Empty! ~~~";
        return;
    }
    for(int i = 0; i < pros.size(); i++)
    {
        if(pros[i].get_saleable())
        {
            if(print) cout << "\t\t--------------------------------------------------\n\n";
            cout << " NAME :" << "    \t\t" << pros[i].get_name() << endl;
            cout << " PRODUCER :" << "\t\t" << pros[i].get_producer() << endl;
            cout << " CATEGORY :" << "\t\t" << pros[i].get_category() << endl << endl;
            cout << " PRICE :" << setw(20) << pros[i].get_price() << setw(17) << "REMAINING :" << setw(15) << pros[i].get_remaining() << endl;
            print = true;
        }
    }
}

bool search_c(string category, string target)
{
    unsigned int j = 0;
    for(unsigned int i = 0; i < category.size(); i++)
    {
        if(target[0] == category[i])
        {
            j++;
            i++;
            while(j < target.size() && i < category.size())
            {
                if(target[j] != category[i]) break;
                j++;
                i++;
            }
            if(j == target.size()) return true;
            j = 0;
        }
    }
    return false;
}

void search(sQVector<product>& pros, cQVector<string>& category, string target)
{
    bool print = false;
    line;
    cout << "\t\tProducts are:\n";
    cout << "\t\t--------------------------------------------------\n\n";
    for(int i = 0; i < pros.size(); i++)
    {
        if(pros[i].search(target))
        {
            if(print) cout << "\t\t--------------------------------------------------\n\n";
            cout << " NAME :" << "    \t\t" << pros[i].get_name() << endl;
            cout << " PRODUCER :" << "\t\t" << pros[i].get_producer() << endl;
            cout << " CATEGORY :" << "\t\t" << pros[i].get_category() << endl << endl;
            cout << " PRICE :" << setw(20) << pros[i].get_price() << setw(17) << "REMAINING :" << setw(15) << pros[i].get_remaining() << endl;
            print = true;
        }
    }
    if(print == false) cout << "\t\t\t~~~ Empty! ~~~";
    line;
    print = false;
    cout << "\t\tCategories are:\n";
    cout << "\t\t----------------------------------------------\n\n";
    for(int i = 0; i < category.size(); i++)
    {
        if(search_c(category[i], target))
        {
            print = true;
            cout << "\t--" << category[i] << endl;
        }
    }
    if(print == false) cout << "\t\t\t~~~ Empty! ~~~";
    line;
}

void mainwindow(sQVector<admin>& admins, sQVector<user>& users, int id, sQVector<product>& pros, int& idp, cQVector<string>& category)
{
    int order, idd, index;
    system("cls");
    if(id < 1500)
    {
        while(true)
        {
            line;
            cout << "\t\t\t * Welcome " << admins[id - 1].get_name() << " *";
            line;
            cout << "\t\tEnter one of the numbers below:\n\n";
            cout << "\t1)Log Out\n\t2)View Users\n\t3)View Products\n\t4)View Categories\n\t5)View Purchase Log\n\t6)Change Settings\n";
            line;
            cin >> order;
            if(check_error(order, 1, 6)) continue;
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
                   cout << "\t1)Return\t2)Add product\t3)Delete product\t4)Change product\t5)Clear\n";
                   cin >> order;
                   if(check_error(order, 1, 5)) continue;
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
                           if(category.find(entry) == -1)
                           {
                               category.append(entry);
                           }
                           while(true)
                           {
                               double price;
                               cout << "  Enter the price:\n";
                               cin >> price;
                               if(check_error(price)) continue;
                               p.set_price(price);
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
                   if(order == 3)
                   {
                       while(true)
                       {
                           cout << "  Enter the product id to delete: (ENTER 0 TO CANCEL)\n";
                           cin >> idd;
                           if(idd == 0)
                           {
                               system("cls");
                               break;
                           }
                           if(admins[id - 1].delu(pros, idd) != -1)
                           {
                               system("cls");
                               line;
                               cout << "\t\t\tProduct deleted!\a";
                               line;
                               break;
                           }
                           system("cls");
                           line;
                           cout << "\t\t\tID is incorrect!\a";
                           line;
                           cout << "\tproducts are:";
                           tablep(pros, false);
                           line;
                       }
                       continue;
                   }
                   if(order == 4)
                   {
                       int index;
                       while(true)
                       {
                           cout << "  Enter the product id to change: (ENTER 0 TO CANCEL)\n";
                           cin >> idd;
                           if(idd == 0)
                           {
                               system("cls");
                               break;
                           }
                           index = pros.find(idd);
                           if(index != -1)
                           {
                               system("cls");
                               string entry;
                               while(true)
                               {
                                   line;
                                   cout << " NAME :" << "    \t\t" << pros[index].get_name() << endl;
                                   cout << " PRODUCER :" << "\t\t" << pros[index].get_producer() << endl;
                                   cout << " CATEGORY :" << "\t\t" << pros[index].get_category() << endl << endl;
                                   cout << " ID :" << setw(20) << pros[index].get_id() << setw(10) << "PRICE :" << setw(20) << pros[index].get_price() << setw(17);
                                   cout << " REMAINING :" << setw(15) << pros[index].get_remaining() << setw(15);
                                   cout << " SALEABLE :";
                                   if(pros[index].get_saleable()) cout << "     YES" << endl;
                                   else cout << "     NO" << endl;
                                   line;
                                   line;
                                   cout << "  Enter one of the numbers below:\n";
                                   cout << "\t1)Return\n\t2)Change name\n\t3)Change producer\n\t4)Change category\n\t5)Change price\n\t6)Change remaining\n\t7)Change saleablity\n";
                                   cin >> order;
                                   if(check_error(order, 1, 7)) continue;
                                   cin.ignore();
                                   if(order == 1)
                                   {
                                       system("cls");
                                       break;
                                   }
                                   if(order == 2)
                                   {
                                       cout << "  Enter the new name: (ENTER 0 TO CANCEL)\n";

                                       getline(cin, entry);
                                       if(entry == "0")
                                       {
                                           system("cls");
                                           continue;
                                       }
                                       pros[index].set_name(entry);
                                       system("cls");
                                       line;
                                       cout << "\t\t\tName chagned!\a";
                                       line;
                                       continue;
                                   }
                                   if(order == 3)
                                   {
                                       cout << "  Enter the new producer: (ENTER 0 TO CANCEL)\n";
                                       getline(cin, entry);
                                       if(entry == "0")
                                       {
                                           system("cls");
                                           continue;
                                       }
                                       pros[index].set_producer(entry);
                                       system("cls");
                                       line;
                                       cout << "\t\t\tProducer chagned!\a";
                                       line;
                                       continue;
                                   }
                                   if(order == 4)
                                   {
                                       cout << "  Enter the new category: (ENTER 0 TO CANCEL)\n";
                                       getline(cin, entry);
                                       if(entry == "0")
                                       {
                                           system("cls");
                                           continue;
                                       }
                                       if(category.find(entry) == -1)
                                       {
                                           category.append(entry);
                                       }
                                       pros[index].set_category(entry);
                                       system("cls");
                                       line;
                                       cout << "\t\t\tCategory chagned!\a";
                                       line;
                                       continue;
                                   }
                                   if(order == 5)
                                   {
                                       double price;
                                       while(true)
                                       {
                                           cout << "  Enter the new price:\n";
                                           cin >> price;
                                           if(check_error(price)) continue;
                                           cin.ignore();
                                           pros[index].set_price(price);
                                           system("cls");
                                           line;
                                           cout << "\t\t\tPrice chagned!\a";
                                           line;
                                           break;
                                       }
                                       continue;
                                   }
                                   if(order == 6)
                                   {
                                       while(true)
                                       {
                                           cout << "  Enter the new remaining:\n";
                                           cin >> idd;
                                           if(check_error(idd)) continue;
                                           cin.ignore();
                                           pros[index].set_remaining(idd);
                                           system("cls");
                                           line;
                                           cout << "\t\t\tRemaining chagned!\a";
                                           line;
                                           break;
                                       }
                                       continue;
                                   }
                                   if(order == 7)
                                   {
                                       if(pros[index].get_remaining() == 0)
                                       {
                                           system("cls");
                                           line;
                                           cout << "\t\t\tIt cant be changed!\a";
                                           line;
                                           continue;
                                       }
                                       pros[index].set_saleable(!pros[index].get_saleable());
                                       system("cls");
                                       line;
                                       cout << "\t\t\tSalebility changed!\a";
                                       line;
                                       continue;
                                   }
                               }
                               break;
                           }
                           system("cls");
                           line;
                           cout << "\t\t\tID is incorrect!\a";
                           line;
                           cout << "\tproducts are:";
                           tablep(pros, false);
                           line;
                       }
                       continue;
                   }
                   if(order == 5)
                   {
                       system("cls");
                       while(true)
                       {
                           line;
                           cout << "\n  Are you sure to clear products?\a" << endl;
                           cout << "\n\t1)YES\n2)\tNO\n";
                           line;
                           cin >> idd;
                           if(check_error(idd, 1, 2)) continue;
                           if(idd == 1)
                           {
                               pros.clear();
                               idp = 12000;
                               system("cls");
                               line;
                               cout << "\t\tProducts removed!";
                               line;
                               break;
                           }
                           if(idd == 2)
                           {
                               system("cls");
                               break;
                           }
                       }
                       continue;
                   }
                }
                continue;
            }
            if(order == 4)
            {
                string entry;
                system("cls");
                while(true)
                {
                    category.show();
                    cout << "\n  Enter one of the numbers below:\n";
                    cout << "\t1)Return\t2)Add\t3)Delete\t4)Change name\t5)Show products\n";
                    cin >> idd;
                    if(check_error(idd, 1, 5)) continue;
                    cin.ignore();
                    if(idd == 1)
                    {
                        system("cls");
                        break;
                    }
                    if(idd == 2)
                    {
                        system("cls");
                        while(true)
                        {
                            cout << "  Enter the name of new category: (ENTER 0 TO CANCEL)\n";
                            getline(cin, entry);
                            if(entry == "0")
                            {
                                system("cls");
                                break;
                            }
                            if(category.find(entry) == -1)
                            {
                                category.append(entry);
                                system("cls");
                                line;
                                cout << "\t\t\tCategory added!\a";
                                line;
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tCategory exist!\a";
                            line;
                            category.show();
                        }
                        continue;
                    }
                    if(idd == 3)
                    {
                        system("cls");
                        while(true)
                        {
                            cout << "  Enter the name of category to delete: (ENTER 0 TO CANCEL)\n";
                            getline(cin, entry);
                            if(entry == "0")
                            {
                                system("cls");
                                break;
                            }
                            if(category.find(entry) != -1)
                            {
                                category.remove(category.find(entry));
                                category.change(pros, entry);
                                system("cls");
                                line;
                                cout << "\t\t\tCategory deleted!\a";
                                line;
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tCategory dosent exist!\a";
                            line;
                            category.show();
                        }
                        continue;
                    }
                    if(idd == 4)
                    {
                        system("cls");
                        int index;
                        while(true)
                        {
                            line;
                            cout << "  Enter the name of category to change: (ENTER 0 TO CANCEL)\n";
                            getline(cin, entry);
                            if(entry == "0")
                            {
                                system("cls");
                                break;
                            }
                            index = category.find(entry);
                            if(index != -1)
                            {
                                cout << "  Enter the new name: (ENTER 0 TO CANCEL)\n";
                                getline(cin, entry);
                                if(entry == "0")
                                {
                                    system("cls");
                                    break;
                                }
                                category.change(pros, category[index], entry);
                                category[index] = entry;
                                system("cls");
                                line;
                                cout << "\t\t\tCategory name changed!\a";
                                line;
                                break;
                            }
                            system("cls");
                            line;
                            cout << "\t\t\tCategory dosnt exist!\a";
                            line;
                        }
                        continue;
                    }
                    if(idd == 5)
                    {
                        while(true)
                        {
                            line;
                            line;
                            cout << "  Enter the number of category:\n";
                            cin >> idd;
                            if(check_error(idd, 1, category.size()))
                            {
                                category.show();
                                continue;
                            }
                            category.show(pros, false, idd);
                            cout << "  Enter any key to return:\n";
                            system("pause");
                            system("cls");
                            break;
                        }
                        continue;
                    }
                }
                continue;
            }
            if(order == 5)
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
            if(order == 6)
            {
                string entry;
                system("cls");
                while(true)
                {
                    line;
                    cout << "  Enter one of the numbers below:\n";
                    cout << "\t1)Return\n\t2)Change username\n\t3)Change password\n";
                    cin >> idd;
                    if(check_error(idd, 1, 3)) continue;
                    cin.ignore();
                    if(idd == 1)
                    {
                        system("cls");
                        break;
                    }
                    if(idd == 2)
                    {
                        system("cls");
                        while(true)
                        {
                            line;
                            line;
                            cout << "   Enter your new username: (NO SPACE, ENTER 0 TO CANCEL)\n";
                            cin >> entry;
                            if(entry == "0")
                            {
                                system("cls");
                                break;
                            }
                            if((users.find(entry) != -1) || (admins.find(entry) != -1))
                            {
                                system("cls");
                                line;
                                cout << "\t\t\tUsername is in use!\a";
                                line;
                                continue;
                            }
                            system("cls");
                            admins[id - 1].set_name(entry);
                            line;
                            cout << "\t\t\tUsername changed!\a";
                            line;
                            break;
                        }
                        continue;
                    }
                    if(idd == 3)
                    {
                        system("cls");
                        line;
                        line;
                        cout << "   Enter your password: (NO SPACE, ENTER 0 TO CANCEL)\n";
                        cin >> entry;
                        if(entry == "0")
                        {
                            system("cls");
                            continue;
                        }
                        system("cls");
                        admins[id - 1].set_pass(entry);
                        line;
                        cout << "\t\t\tPassword changed!\a";
                        line;
                        continue;
                    }
                }
                continue;
            }
        }
    }
    index = users.find(id);
    while(true)
    {
        line;
        cout << "\t\t\t * Welcome " << users[index].get_name() << " *";
        line;
        cout << "\t\tEnter one of the numbers below:\n\n";
        cout << "\t1)Log Out\n\t2)View Products\n\t3)Search\n\t4)View Categories\n\t5)View Purchase history\n\t6)Change Settings\n";
        line;
        cin >> order;
        cin.ignore();
        if(check_error(order, 1, 6)) continue;
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
               cout << "\tProducts are:";
               tablep(pros, true);
               line;
               cout << "  Enter one of the numbers below:\n\n";
               cout << "\t1)Return\t2)Buy product\n";
               cin >> order;
               if(check_error(order, 1, 2)) continue;
               cin.ignore();
               if(order == 1)
               {
                   system("cls");
                   break;
               }
               if(order == 2)
               {
                   string entry;
                   int num, indexi;
                   product p;
                   system("cls");
                   if(!users[index].get_buy())
                   {
                       system("cls");
                       line;
                       cout << "\t\tYou dont have permission!\a\n";
                       cout << "\tContanct the admins for more information.";
                       line;
                       continue;
                   }
                   cout << "\tProducts are:";
                   tablep(pros, true);
                   line;
                   while(true)
                   {
                       cout << "  Enter the name of product: (ENTER 0 TO CANCEL)\n";
                       getline(cin, entry);
                       if(entry == "0")
                       {
                           system("cls");
                           break;
                       }
                       indexi = pros.find(entry);
                       if((indexi != -1) && (pros[indexi].get_saleable()))
                       {
                           p.set_name(entry);
                           while(true)
                           {
                               cout << "  Enter the number you want: (ENTER 0 TO CANCEL)\n";
                               cin >> num;
                               if(num == 0)
                               {
                                   system("cls");
                                   break;
                               }
                               if(check_error(num, 1, pros[indexi].get_remaining())) continue;
                               p.set_remaining(num);
                               p.set_price(pros[indexi].get_price());
                               p.set_producer(pros[indexi].get_producer());
                               p.set_id(pros[indexi].get_id());
                               p.set_category(pros[indexi].get_category());
                               pros[indexi].set_remaining(pros[indexi].get_remaining() - num);
                               users[index].add_history(p);
                               p.set_name(users[indexi].get_name());
                               admins[0].add_history(p);
                               system("cls");
                               line;
                               cout << "  Your total bill:\t" << num * pros[indexi].get_price();
                               line;
                               cout << "  Enter any key to return:\n";
                               system("pause");
                               system("cls");
                               break;
                           }
                           break;
                       }
                       system("cls");
                       line;
                       cout << "\t\t\tThe name in incorrect!\a";
                       line;
                       cout << "\tProducts are:";
                       tablep(pros, true);
                       line;
                   }
                   continue;
               }
            }
            continue;
        }
        if(order == 3)
        {
            string entry;
            while(true)
            {
                system("cls");
                line;
                line;
                cout << "  Enter to search: (ENTER 0 TO CANCEL)\n";
                getline(cin, entry);
                if(entry == "0")
                {
                    system("cls");
                    break;
                }
                search(pros, category, entry);
                cout << "  Enter any key to continue:\n";
                system("pause");
            }
            continue;
        }
        if(order == 4)
        {
            string entry;
            system("cls");
            while(true)
            {
                category.show();
                cout << "\n  Enter one of the numbers below:\n";
                cout << "\t1)Return\t2)Show products\n";
                cin >> idd;
                if(check_error(idd, 1, 2)) continue;
                if(idd == 1)
                {
                    system("cls");
                    break;
                }
                if(idd == 2)
                {
                    while(true)
                    {
                        line;
                        line;
                        cout << "  Enter the number of category:\n";
                        cin >> idd;
                        if(check_error(idd, 1, category.size()))
                        {
                            category.show();
                            continue;
                        }
                        category.show(pros, true, idd);
                        cout << "  Enter any key to return:\n";
                        system("pause");
                        system("cls");
                        break;
                    }
                    continue;
                }
            }
            continue;
        }
        if(order == 5)
        {
            system("cls");
            line;
            users[index].show_history();
            line;
            cout << "  Enter any key to return:\n";
            system("pause");
            system("cls");
            continue;
        }
        if(order == 6)
        {
            string entry;
            system("cls");
            while(true)
            {
                line;
                cout << "  Enter one of the numbers below:\n";
                cout << "\t1)Return\n\t2)Change username\n\t3)Change password\n";
                cin >> idd;
                if(check_error(idd, 1, 3)) continue;
                cin.ignore();
                if(idd == 1)
                {
                    system("cls");
                    break;
                }
                if(idd == 2)
                {
                    system("cls");
                    while(true)
                    {
                        line;
                        line;
                        cout << "   Enter your new username: (NO SPACE, ENTER 0 TO CANCEL)\n";
                        cin >> entry;
                        if(entry == "0")
                        {
                            system("cls");
                            break;
                        }
                        if((users.find(entry) != -1) || (admins.find(entry) != -1))
                        {
                            system("cls");
                            line;
                            cout << "\t\t\tUsername is in use!\a";
                            line;
                            continue;
                        }
                        system("cls");
                        users[index].set_name(entry);
                        line;
                        cout << "\t\t\tUsername changed!\a";
                        line;
                        break;
                    }
                    continue;
                }
                if(idd == 3)
                {
                    system("cls");
                    line;
                    line;
                    cout << "   Enter your password: (NO SPACE, ENTER 0 TO CANCEL)\n";
                    cin >> entry;
                    if(entry == "0")
                    {
                        system("cls");
                        continue;
                    }
                    system("cls");
                    users[index].set_pass(entry);
                    line;
                    cout << "\t\t\tPassword changed!\a";
                    line;
                    continue;
                }
            }
            continue;
        }
    }
}

void load_data(sQVector<admin>& admins, sQVector<user>& users, sQVector<product>& pros, cQVector<string>& category, int& idp, int& idu)
{
    string c;
    user u;
    admin a;
    product p;
    double price;
    int size, entry;
    ifstream filec("cat_data.txt");
    while(getline(filec,c))
    {
        category.append(c);
    }
    filec.close();
    ifstream fileu("user_data.txt");
    fileu >> size;
    fileu.ignore();
    for(int i = 0; i < size; i++)
    {
        getline(fileu, c);
        u.set_name(c);
        getline(fileu, c);
        u.set_pass(c);
        fileu >> entry;
        u.set_buy(entry);
        fileu >> entry;
        u.set_id(entry);
        u.load_history(fileu);
        users.append(u);
    }
    if(size == 0) idu = 1500;
    else idu = entry + 1;
    fileu.close();
    ifstream filea("admin_data.txt");
    filea >> size;
    filea.ignore();
    for(int i = 0; i < size; i++)
    {
        getline(filea, c);
        a.set_name(c);
        getline(filea, c);
        a.set_pass(c);
        filea >> entry;
        a.set_id(entry);
        filea >> entry;
        a.set_buy(entry);
        a.load_history(filea);
        admins.append(a);
    }
    filea.close();
    ifstream filep("product_data.txt");
    filep >> size;
    filep.ignore();
    for(int i = 0; i < size; i++)
    {
        getline(filep, c);
        p.set_name(c);
        getline(filep, c);
        p.set_producer(c);
        getline(filep, c);
        p.set_category(c);
        filep >> entry;
        p.set_saleable(bool(entry));
        filep >> entry;
        p.set_remaining(entry);
        filep >> entry;
        p.set_id(entry);
        filep >> price;
        p.set_price(price);
        pros.append(p);
        filep.ignore();
    }
    if(size == 0) idp = 12000;
    else idp = entry + 1;
    filep.close();
}

void save_data(sQVector<admin>& admins, sQVector<user>& users, sQVector<product>& pros, cQVector<string>& category)
{
   ofstream filec("cat_data.txt");
   for(int i = 0; i < category.size(); i++)
   {
       filec << category[i] << endl;
   }
   filec.close();
   ofstream fileu("user_data.txt");
   fileu << users.size() << endl;
   for(int i = 0; i < users.size(); i++)
   {
       fileu << users[i].get_name() << endl;
       fileu << users[i].get_pass() << endl;
       fileu << users[i].get_buy() << endl;
       fileu << users[i].get_id() << endl;
       users[i].save_history(fileu);
   }
   fileu.close();
   ofstream filea("admin_data.txt");
   filea << admins.size() << endl;
   for(int i = 0; i < admins.size(); i++)
   {
       filea << admins[i].get_name() << endl;
       filea << admins[i].get_pass() << endl;
       filea << admins[i].get_id() << endl;
       filea << admins[i].get_buy() << endl;
       admins[i].save_history(filea);
   }
   filea.close();
   ofstream filep("product_data.txt");
   filep << pros.size() << endl;
   for(int i = 0; i < pros.size(); i++)
   {
       filep << pros[i].get_name() << endl;
       filep << pros[i].get_producer() << endl;
       filep << pros[i].get_category() << endl;
       filep << pros[i].get_saleable() << endl;
       filep << pros[i].get_remaining() << endl;
       filep << pros[i].get_id() << endl;
       filep << pros[i].get_price() << endl;
   }
   filep.close();
}

int main()
{
    sQVector<user> users;
    sQVector<product> pros;
    sQVector<admin> admins;
    cQVector<string> category;
    int idp, idu, order, check;
    load_data(admins, users, pros, category, idp, idu);
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
            if(check != -1) mainwindow(admins, users, check, pros, idp, category);
            else continue;
        }
        if(order == 2)
        {
            check = signup(admins, users, idu);
            if(check != -1) mainwindow(admins, users, check, pros, idp, category);
            else continue;
        }
        if(order == 3) break;
    }
    save_data(admins, users, pros, category);
    system("cls");
    line;
    cout << "\n|------------------------- Hope to see you again :) -------------------------|\n\n";
    return 0;
}
