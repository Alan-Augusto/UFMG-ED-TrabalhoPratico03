#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "memlog.h"
#include "msgassert.h"

using namespace std;

//FUNÇÕES GLOBAIS DO PROGRAMA
void Assert(bool x, string text);


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
        void create(int id_email, int id_recipient, string mssg);
};

//ÁRVORE BINÁRIA
    //Nó da árvore binária:
class KnotType
{
    public:
        KnotType();
        Email email;
        KnotType *left;
        KnotType *right;
        friend class bintree;
}; 

class BinaryTree
{
    public:
        
        KnotType *raiz;

        //Methods
        BinaryTree();
        void insere(Email mensagem);
        void caminha(int tipo);
        void clean();
        Email pesquisa(Email mensagem);
        Email pesquisa_recursivo(KnotType *p, Email mensagem);
        void remove(Email mensagem);
        void remove_recursivo(KnotType *&p, Email mensagem);
        void insere_recursivo(KnotType *&p, Email mensagem);
        void apaga_recursivo(KnotType *p);
        void antecessor(KnotType *q, KnotType *&r);
        
    };

//TABELA HASH
class HashTable{
    public:
        BinaryTree *tree;
        int size;
        
        //Methods
        HashTable(int M, string outputName);
        void SendMail(Email mensagem);
        Email find(int id_msg, int id_recipient);
        void erease(int id_msg, int id_recipient);
        int hash_id(Email mensagem);
        string outputNameArq;
};