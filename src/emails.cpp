#include <iostream>
#include <emails.h>

using namespace std;

//EMAIL
    Email::Email(int ID_email, int ID_recipient, string text){
        ID = ID_email;
        recipient = ID_recipient;
        message = text;
    }
    //Operators
    bool Email::operator==(const Email& x){
        if (recipient == x.recipient) {
            return true;
        }
        else{
            return false;
        }
        
    }
    
    bool Email::operator<(const Email& x){
        if (ID < x.ID) {
            return true;
        }
        else{
            return false;
        }
        
    }

    bool Email::operator>(const Email& x){
        if (ID > x.ID) {
            return true;
        }
        else{
            return false;
        }
        
    }

    //Methods

//HASH TABLE

//EMAILS TREE