#include <iostream>
using namespace std;

class Person
{
    public:
        /* instance variable */
        int age;
        /* constructor */
        Person(int initialAge);
        /* instance methods (functions) */
        void amIOld();
        void yearPasses();
};

Person::Person(int initialAge)
{
    // add some code to run some checks on initialAge
    if (initialAge < 0)
    {
        Person::age = 0;
        cout << "Age is not valid, setting age to 0.\n";
    }
    else
    {
        Person::age = initialAge;
    }
    // debug message
    cout << "You have entered age = " << Person::age << "\n";
}

void Person::amIOld()
{
    // do some computations in hear and print out the correct statement to console
    if (Person::age < 13)
    {
        cout << "You are young.\n";
    }
    else if (Person::age >= 13 && Person::age < 18)
    {
        cout << "You are a teenager.\n";
    }
    else
    {
        cout << "You are old.\n";
    }
}

void Person::yearPasses()
{
    // increment the age of the person in here
    Person::age++;
}

int main(void)
{
    /* t: number of test cases */
    int t;
    int age;
    cin >> t;
    
    while ((t < 1) || (t > 4))
    {
        cin >> t;
    }
    
    for (int i = 0; i < t; i++)
    {
        cin >> age;
        Person p (age);
        p.amIOld();
        for (int j = 0; j < 3; j++)
        {
            p.yearPasses();
        }
        p.amIOld();
        cout << '\n';
    }
    
    return 0;
}
