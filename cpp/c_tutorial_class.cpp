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
#include <sstream>
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
  public:
    void set_age(int tmp_age)
    {
	   age = tmp_age;
    }
    int get_age()
    {
        return age;
    }
    void set_first_name(string tmp_first_name)
    {
        first_name = tmp_first_name;
    }
    string get_first_name()
    {
        return first_name;
    }
    void set_last_name(string tmp_last_name)
    {
        last_name = tmp_last_name;
    }
    string get_last_name()
    {
        return last_name;
    }
    void set_standard(int tmp_standard)
    {
	   standard = tmp_standard;
    }
    int get_standard()
    {
        return standard;
    }
  private:
    string num_to_ch(int num)
    {
        return (num + 48);
    }
  public:
    string to_string()
    {
        string outstr;
        outstr = num_to_ch(age/10)+num_to_ch(age%10)+first_name+","+last_name;
        return outstr;
    }
};

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    cout << "Class\n";
    
    int age, standard;
    string first_name, last_name;
    cin >> age >> first_name >> last_name >> standard;

    Student st;

    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);

    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    cout << "\n";
    cout << st.to_string();

    return 0;
}
