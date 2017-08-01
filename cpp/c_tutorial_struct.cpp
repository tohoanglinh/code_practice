/**
 * File   : c_tutorial_struct.cpp
 * Author : To Hoang Linh
 * Date   : 2017-07-24
 * ForWhat: struct is a way to combine multiple fields to represent a composite
 * data structure, which further lays the foundation for Object Oriented Programming.
 * For example, we can store details related to a student in a struct consisting
 * of his age (int), first_name (string), last_name (string) and standard (int).
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

/* access specifier default of struct member: public */
struct Student{
    int age;
    string first_name;
    string last_name;
    int standard;
};

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    cout << "Struct\n";
    
    /* input */
    Student st1;
    
    cin >> st1.age >> st1.first_name >> st1.last_name >> st1.standard;
    cout << st1.age << " " << st1.first_name << " " << st1.last_name << " " << st1.standard;
    
    return 0;
}
