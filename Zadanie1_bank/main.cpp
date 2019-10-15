#include <iostream>
#include "test.h"

using namespace std;

class Human
{
public:
    Human(string p_name) : name(p_name) {}
    string getName() {return name; }

private:
    string name;
};

class Bank
{
public: 

    int registerAccount(Human*) {return 0;}
    bool registerTransaction(int sourceAccount, int targetAccount, int amount) {return true;}
    void addCashToAccount(int account, int amount) {}
    int getBalance(int) {return 0;}
    int getTotalBalance(Human*) {return 0;}
};

int main()
{
    Bank bank;
    Human jan ("Jan Kowalski");
    Human janina ("Janina Nowak");

    int janAccountId = bank.registerAccount(&jan);
    Test("New account is always empty", [&]()
    {
        return bank.getBalance(janAccountId) == 0;
    }).run();
    
    bank.addCashToAccount(janAccountId, 100);
    Test("Now there is 100$ in account", [&]()
    {
        return bank.getBalance(janAccountId) == 100;
    }).run();
    
    int janinaFirstAccountId = bank.registerAccount(&janina);
    Test("New account is always empty", [&]()
    {
        return bank.getBalance(janinaFirstAccountId) == 0;
    }).run();
    
    int janinaSecondAccountId = bank.registerAccount(&janina);
    bank.addCashToAccount(janinaSecondAccountId, 200);
    Test("Janina first account is still empty", [&]()
    {
        return bank.getBalance(janinaFirstAccountId) == 0;
    }).run();
    Test("There is 200$ in Janina second account", [&]()
    {
        return bank.getBalance(janinaSecondAccountId) == 200;
    }).run();

    bool result = bank.registerTransaction(janAccountId, janinaFirstAccountId, 10);
    Test("Jan can afford to buy a book", [&]()
    {
        return result == true;
    }).run();
    
    result = bank.registerTransaction(janAccountId, janinaFirstAccountId, 10000);
    Test("Bun he can't afford to buy her car", [&]()
    {
        return result == false;
    }).run();
    
    Test("Now she has 210$ in total", [&]()
    {
        return bank.getTotalBalance(&janina) == 210;
    }).run();
    
    Test("And he has only 90$ left", [&]()
    {
        return bank.getTotalBalance(&jan) == 90;
    }).run();

    return 0;
}
