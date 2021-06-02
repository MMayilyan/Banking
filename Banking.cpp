#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include "json.hpp"
#include "Banking.h" 

using json = nlohmann::json;

const void Banking::Start()
{
  std::cout << "\n\n" << "     CUSTOMER ACCOUNT BANKING MANAGMENT SYSTEM\n" 
            << "            WELCOM TO THE MAIN MENU\n\n"
            << "1. Create new account\n"
            << "2. Update information of existing account\n"
            << "3. For transactions\n"
            << "4. Check the details of existing account\n"
            << "5. Removing existing account\n"
            << "6. View customer's list\n"
            << "7. Exit\n\n"
            << "   Enter your choise: ";
  int n;
  std::cin >> n;
  std::cout << "\n"; 
  Banking b;

  switch (n) {
    case 1:
      b.Create_new_account();
      return Start();
    case 2:
      b.Update_information_of_existing_account();
      return Start();
    case 3:
      b.For_transactions();
      return Start();
    case 4:
      b.Check_the_details_of_existing_account();
      return Start();
    case 5:
      b.Removing_existing_account();
      break;
    case 6:
      b.View_customers_list();
      return Start();
    case 7: 
      b.Exit();
      break;
    default:
      std::cout << "Sellect correct paragraph!\n";
      return Start(); 
  }
}

const void Banking::Create_new_account()
{
  Banking ps;
  json acc;
  bool flag = false;

  std::ifstream ls;
  ls.open(contein);
  if(!ls.is_open()) {
    std::ofstream file;
    flag = true;
    file.open(ps.contein, std::ios::out);
    if (file.is_open()) {
      file.close();
    } else {
      std::cout << "Cannot open file!\n";
    }
  }
  
  std::cout << "Enter your first name:  ";
  std::cin >> first_name;
  std::cout << "Enter your last name:  ";
  std::cin >> last_name;
  std::cout << "Enter your passport number:  ";
  std::cin >> passport;
  std::cout << "Enter pin code:  ";
  std::cin >> pin;
  std::cout << "\n";
  
  if(!flag) {
    ls >> acc;
  }

  acc[pin] = {
  {"First name", first_name},
  {"Last name", last_name},
  {"Passport number",  passport},
  {"Money", money} };
 

  std::ofstream cust;
  cust.open(contein);
  if (cust.is_open()) {
    cust << std::setw(4) << acc << std::endl;
    cust.close();
   } else {
    std::cout << "Cannot open file! Try again\n";
    Create_new_account();
  }
  std::cout << "Your account successesfully created!\n";
}

const void Banking::Update_information_of_existing_account()
{
  json key;
  std::fstream upd;
  upd.open("List.json");
  if (upd.is_open()) {
    upd >> key;
    upd.close();
  }

  std::string pass;
  std::cout << "Enter pin code: ";
  std::cin >> pass;
  std::cout << "\n";

  for (json::iterator i = key.begin(); i != key.end(); ++i) {
    if (i.key() == pass) {
      std::cout << "What do you want to change?\n" 
                << "1. First name\n"
                << "2. Last name\n\n"
                << "   Enter your choise: ";
      std::cin >> number;
      
      if (number == 1) {
        for (json::iterator j = i -> begin(); j != i -> end(); ++j) {
          if (j.key() == "First name") {
            std::string tmp;
            std::cout << "Enter new first name: ";
            std::cin >> tmp;
            j.value() = tmp;
            std::cout << "\n" << "Your first name successesfully updated!";
          }
        } 
      } else if (number == 2) {
        for (json::iterator j = i -> begin(); j != i -> end(); ++j) {
          if (j.key() == "Last name") {
            std::string tmp;
            std::cout << "\nEnter new last name: ";
            std::cin >> tmp;
            j.value() = tmp;
            std::cout << "\n" << "Your last name successesfully updated!";
          }
        } 
      } else {
        std::cout << "Error! Try again.";
        return Update_information_of_existing_account();
      }
    }
  }

  std::ofstream temp;
  temp.open("List.json", std::ios::out);
  if (temp.is_open()) {
    temp << std::setw(4) << key << std::endl;
    temp.close();
  } else {
    std::cout << "Cannot open file! Try again.\n";
    return Update_information_of_existing_account();
  }
  std::cout << "\n";
}

const void Banking::For_transactions()
{
  json trans;
  std::fstream upd;
  upd.open("List.json");
  if (upd.is_open()) {
    upd >> trans;
    upd.close();
  }
  
  std::string pass;
  std::cout << "Enter pin code: ";
  std::cin >> pass;
  int amount;

  for (json::iterator i = trans.begin(); i != trans.end(); ++i) {
    if (i.key() == pass) {
      std::cout << "\n" << "1. Add money\n"
                << "2. Withdraw money\n\n"
                << "   Enter your choise: ";
      std::cin >> number;

      if (number == 1) {
        std::cout << "\n" << "Enter the amount: ";
        std::cin >> amount;
        
        for (json::iterator j = i -> begin(); j != i -> end(); ++j) {
          if (j.key() == "Money") {
            int money = j.value();
            j.value() = money + amount;
            std::cout << "Done!";
          }
        }

        std::ofstream out;
        out.open("List.json", std::ios::out);
        if (out.is_open()) {
          out << std::setw(4) << trans << std::endl;
          out.close(); 
        } else {
          std::cout << "Cannot open file! Try again.\n";
          For_transactions();
        }
        return Start();  
      } else if (number == 2) {
        std::cout << "\n" << "Enter the amount: ";
        std::cin >> amount;

        for (json::iterator j = i -> begin(); j != i -> end(); ++j) {
          if (j.key() == "Money") {
            if (amount > 0 && amount <= j.value()) {
              int money = j.value();
              j.value() = money - amount;
              std::cout << "Done!";
            } else {
              std::cout << "\n" << "There is not enough money on your account!\n";
            } 
          } 
        }

        std::ofstream out;
        out.open("List.json", std::ios::out);
        if (out.is_open()) {
          out << std::setw(4) << trans << std::endl;
          out.close(); 
        } else {
          std::cout << "Cannot open file! Try again.\n";
          For_transactions();
        }  
      } else {
        std::cout << "Error! Try again.\n";
        return For_transactions(); 
      }
    }
  }
  std::cout << "\n"; 
}

const void Banking::Check_the_details_of_existing_account()
{
  json check;
  std::fstream upd;
  upd.open("List.json");
  if (upd.is_open()) {
    upd >> check;
    upd.close();
  }
  
  std::string pass;
  std::cout << "Enter pin code: ";
  std::cin >> pass;
  std::cout << "\n";
  int amount;
  
  for (json::iterator i = check.begin(); i != check.end(); ++i) {
    if (i.key() == pass) {
      for (json::iterator j = i -> begin(); j != i -> end(); ++j) {
        std::cout << j.key() << " " << j.value() << "\n";
      }
    }
  }
}

const void Banking::Removing_existing_account()
{
  json remove;
  std::fstream upd;
  upd.open("List.json");
  if (upd.is_open()) {
    upd >> remove;
    upd.close();
  }
  
  std::string pass;
  std::cout << "Enter pin code: ";
  std::cin >> pass;
  char agree;

  for (json::iterator i = remove.begin(); i != remove.end(); ++i) {
    if (i.key() == pass) {
      std::cout << "\n" << "Are you sure? Y/N: ";
      std::cin >> agree;
      if (agree == 'Y' || agree == 'y') {
        remove.erase(pass);
        std::ofstream out;
        out.open("List.json", std::ios::out);
        if (out.is_open()) {
          out << std::setw(4) << remove << std::endl;
          out.close();
        } else {
          std::cout << "\nCannot open file! Try again.\n";
          return Removing_existing_account();
        }
        std::cout << "Done!\n"; 
      } else if (agree == 'N' || agree == 'n') {
        return Start();
      }
    } 
  }
}

const void Banking::View_customers_list()
{
  json list;
  std::fstream upd;
  upd.open("List.json");
  if (upd.is_open()) {
    upd >> list;
    upd.close();
  }

  for (json::iterator i = list.begin(); i != list.end(); ++i) {
    for (json::iterator j = i -> begin(); j != i -> end(); ++j) {
      if (j.key() == "Money") {
        continue;
      }
      std::cout << j.key() << " " << j.value() << std::endl;
    }
    std::cout << "\n";
  }
}

const void Banking::Exit()
{
  std::cout << "Have a nice day!\n";
}
