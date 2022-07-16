#include <iostream>
#include <emails.h>

using namespace std;

//EMAIL
    //Operators
    bool Email::operator==(const Email& x){
        if (recipient_ID == x.recipient_ID) {
            return true;
        }
        else{
            return false;
        }
        
    }
    
    bool Email::operator<(const Email& x){
        if (email_ID < x.email_ID) {
            return true;
        }
        else{
            return false;
        }
        
    }

    bool Email::operator>(const Email& x){
        if (email_ID > x.email_ID) {
            return true;
        }
        else{
            return false;
        }
        
    }

    //Methods

//HASH TABLE

//EMAILS TREE