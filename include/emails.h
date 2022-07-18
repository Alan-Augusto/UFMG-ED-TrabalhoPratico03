#include <iostream>
#include <string>

using namespace std;

//EMAIL
class Email{
    public:
        int ID;
        int recipient;
        string message;

        Email();
        //Operators
        bool operator==(const Email& x);
        bool operator<(const Email& x);
        bool operator>(const Email& x);
        friend istream &operator>>( istream  &input, Email &D ) { 
            input >> D.message;
            return input;            
        }

        //Methods
};

//ÁRVORE BINÁRIA
    //Nó da árvore binária:
class tipo_no
{
    public:
        tipo_no();
        Email email;
        tipo_no *left;
        tipo_no *right;
        friend class bintree;
}; 

class bintree
{
    public:
        bintree();
        void insere(Email mensagem);
        void caminha(int tipo);
        void clean();
        Email pesquisa(Email mensagem);
        void remove(Email mensagem);

        void insere_recursivo(tipo_no *&p, Email mensagem);
        void apaga_recursivo(tipo_no *p);
        Email pesquisa_recursivo(tipo_no *p, Email mensagem);
        void remove_recursivo(tipo_no *&p, Email mensagem);
        void antecessor(tipo_no *q, tipo_no *&r);
        tipo_no *raiz;
    };

//TABELA HASH
class hashtable
{
    public:
        int size;
        hashtable(int M);
        void insere(Email mensagem, int M);
        Email pesquisa(int id_msg, int id_recipient);
        void remove(int id_msg, int id_recipient);

        int hash_id(Email mensagem);
        bintree *table;
};