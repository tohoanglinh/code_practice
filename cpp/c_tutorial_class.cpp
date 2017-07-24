/**
 * File   : c_tutorial_class.cpp
 * Author : To Hoang Linh
 * Date   : 2017-07-24
 * ForWhat: Classes in C++ are user defined types declared with keyword class
 * that has data and functions. Although classes and structures have the same
 * type of functionality, there are some basic differences. The data members
 * of a class are private by default and the members of a structure are public
 * by default. Along with storing multiple data in a common block, it also
 * assigns some functions (known as methods) to manipulate/access them. It serves
 * as the building block of OOP.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
using namespace std;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MACRO1 2

/* access specifier default of class member: private */
class Student{
  private:
    int age;
    string first_name;
    string last_name;
    int standard;
  private:
    void to_string();
  public:
    void get_age()
    {
        cin >> age;
    }
    void set_age()
    {
	cout << age;
    }
};

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    cout << "Hello\n";
    return 0;
}
