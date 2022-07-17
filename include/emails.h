#include <iostream>
#include <string>

using namespace std;

//EMAIL
class Email{
    public:
        int ID;
        int recipient;
        string message;

        Email(int ID_email, int ID_recipient, string text);
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
        Email mensagem;
        tipo_no *left;
        tipo_no *right;
        friend class bintree;
};    
class bintree
{
    public:
        bintree();
        ~bintree();
        void insere(Email mensagem, int memlog);
        void caminha(int tipo);
        void limpa();
        Email pesquisa(Email mensagem, int memlog);
        void remove(Email mensagem, int memlog);

        void insere_recursivo(tipo_no *&p, Email mensagem, int memlog);
        void apaga_recursivo(tipo_no *p);
        Email pesquisa_recursivo(tipo_no *p, Email mensagem, int memlog);
        void remove_recursivo(tipo_no *&p, Email mensagem, int memlog);
        void antecessor(tipo_no *q, tipo_no *&r);
        tipo_no *raiz;
    };

//TABELA HASH
class hashtable
{
    public:
        hashtable(int M);
        Email pesquisa(Email mensagem, int M, int Tipo, int memlog);
        void insere(Email mensagem, int M, int memlog);
        void remove(Email mensagem, int M, int memlog);

        int hash_id(Email mensagem, int M);
        bintree *table;
};