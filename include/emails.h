#include <iostream>
#include <string>

using namespace std;

class Email{
    public:
        int email_ID;
        int recipient_ID;
        string message;

        //Operators
        bool operator==(const Email& x);
        bool operator<(const Email& x);
        bool operator>(const Email& x);

        friend istream &operator>>( istream  &input, Email &D ) { 
            input >> D.message;
            return input;            
        }
};
