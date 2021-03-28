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

  void Start();
  void Create_new_account();
  void Update_information_of_existing_account();
  void For_transactions();
  void Check_the_details_of_existing_account();
  void Removing_existing_account();
  void View_customers_list();
  void Exit() const;

private:
  int number;
  int money = 0;
  std::string list;
  const std::string contein = "List.json";
};
