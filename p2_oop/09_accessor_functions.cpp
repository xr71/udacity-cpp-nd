#include <iostream>
#include <cassert>
#include <vector>
#include <string>


// Accessor functions are public member functions that allow users to
// access an object's data, albeit indirectly.

// NOTE
// Accessors should only retrieve data. They should not change the
// data stored in the object.
//
// The main role of the const specifier in accessor methods is to protect
// member data. When you specify a member function as const, the compiler
// will prohibit that function from changing any of the object's member data.


#include <iostream>
#include <string>

class BankAccount
{
  private:
      // TODO: declare member variables
      std::string name;
      std::string account_number;
      float funds;

  public:
      BankAccount(std::string name, std::string account_number, float funds);
      // TODO: declare setters
      void setName(std::string n);
      void setFunds(float f);
      void setAcctNum(std::string acctnum);

      // TODO: declare getters
      std::string getName() const { return name; }
      std::string getAcctNum() const { return account_number; }
      float getFunds() const { return funds; }
};

// constructor
BankAccount::BankAccount(std::string n, std::string acctnum, float f) : name(n), account_number(acctnum), funds(f) {

}

void BankAccount::setFunds(float f)
{
    BankAccount::funds = f;
}


int main(){

    BankAccount ba1("bob", "123", 100.00);
    ba1.setFunds(10000);
    std::cout << ba1.getName() << ba1.getAcctNum() << ba1.getFunds() << std::endl;

}

