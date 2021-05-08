#include <iostream>
#include <string.h>

class Person
{
public:
  Person()
  {}

  ~Person()
  {}
  
protected:
  std::string first_name;
  std::string last_name;
  std::string passport;
  std::string pin;
};

class Banking : public Person
{
public:
  Banking()
  {}

  ~Banking()
  {}

  const static void Start();
  const void Create_new_account();
  const void Update_information_of_existing_account();
  const void For_transactions();
  const static void Check_the_details_of_existing_account();
  const static void Removing_existing_account();
  const static void View_customers_list();
  const static void Exit();

private:
  int number;
  int money = 0;
  std::string list;
  const std::string contein = "List.json";
};
