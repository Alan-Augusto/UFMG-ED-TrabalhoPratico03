#include <iostream>
#include <emails.h>
#include <fstream>
#include <sstream>
#include "memlog.h"
#include "msgassert.h"

using namespace std;


//FUNÇÕES GLOBAIS DO PROGRAMA
void Assert(bool x, string text){
    if(!x){
        cout << text << endl;
        exit(0);
    }
}

//EMAIL
    Email::Email(){
        ID = -1;
        recipient = -1;
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
    void Email::create(int id_email, int id_recipient, string mssg){
        ID = id_email;
        recipient = id_recipient;
        message = mssg;
    }

//NÓ DA ÁRVORE BINÁRIA
    KnotType::KnotType(){
        left = NULL;
        right = NULL;
    }

//ÁRVORE BINÁRIA
    //Construtor
    BinaryTree::BinaryTree(){
        raiz = NULL;
    }

    //Methods
    void BinaryTree::insere(Email email){
        insere_recursivo(raiz, email);
    }

    void BinaryTree::insere_recursivo(KnotType *p, Email email){
        if (p == NULL){
            p = new KnotType();
            p->email = email;
            //Quando criar um nó, escreve a posição
            escreveMemLog((long int)(&p->email), (long int)sizeof(Email), 0);
        }
        else{
            if (email.ID < p->email.ID){
                insere_recursivo(p->left, email);
            }
            else{
                insere_recursivo(p->right, email);
            }
        }
    }

    void BinaryTree::clean(){
        apaga_recursivo(raiz);
        raiz = NULL;
    }

    void BinaryTree::apaga_recursivo(KnotType *p){
        if (p != NULL){
            apaga_recursivo(p->left);
            apaga_recursivo(p->right);
            delete p;
        }
    }

    Email BinaryTree::pesquisa(Email email){
        return pesquisa_recursivo(raiz, email);
    }

    Email BinaryTree::pesquisa_recursivo(KnotType *no, Email email){
        Email aux;
        if (no == NULL){
            aux.ID = -1;
            return aux; 
        }
        if (email.ID < no->email.ID){
            return pesquisa_recursivo(no->left, email);
        }
        else if (email.ID > no->email.ID){
            return pesquisa_recursivo(no->right, email);
        }
        else{
            //Quando encontrado um nó, escreve a posição
            leMemLog((long int)(&no->email), (long int)sizeof(Email), 0);
            return no->email;
        }
    }

    void BinaryTree::remove(Email email){
        return remove_recursivo(raiz, email);
    }

    void BinaryTree::remove_recursivo(KnotType *&no, Email email){
        //Essa função só será chamada caso o email for encontrado na árvore
        KnotType *aux;
        
        if (no != NULL){
            if (email.ID < no->email.ID){
                return remove_recursivo(no->left, email);
            }
            else if (email.ID > no->email.ID)
                return remove_recursivo(no->right, email);
            //Se encontrou a mensagem
            else{
                //Se o da direira é nulo
                if (no->right == NULL){
                    //Faz apontar pro elemento da esquerda do nó.
                    aux = no;
                    no = no->left;
                    free(aux);
                }
                //Se o da esquerda é nulo
                else if (no->left == NULL){
                    //Faz apontar pro elemento da direita do nó.
                    aux = no;
                    no = no->right;
                    free(aux);
                }
                //Se aponta para 2 elementos válidos
                else{
                    antecessor(no, no->left);
                }
            }
        }
    }

    void BinaryTree::antecessor(KnotType *q, KnotType *&r){
        if (r->right != NULL){
            antecessor(q, r->right);
            return;
        }
        q->email = r->email;
        q = r;
        r = r->left;
        free(q);
    }

//TABELA HASH
    //
    HashTable::HashTable(int M, string outputName){
        tree = new BinaryTree[M];
        size = M;
        outputNameArq = outputName;
    }

    int HashTable::hash_id(Email email){
        int aux = (email.recipient % size);
        return aux;
    }

    Email HashTable::find(int id_msg, int id_recipient){
        //Email auxiliar para busca do hash
        Email email_aux;
        email_aux.create(id_msg, id_recipient, "");
        //=================================

        //Abre arquivo de saída
        ofstream OutputFile(outputNameArq, ios::app);
        Assert(OutputFile.is_open(), "Opening error in output file");

        //Traz o email que está buscando diretamente da árvore referente à tabela hash
        Email email_find;
        email_find = tree[hash_id(email_aux)].pesquisa(email_aux);


        //Se não existe ID ou o destinatário é diferente daquele procurado:
        if (email_find.ID == -1 || email_find.recipient != email_aux.recipient){
            OutputFile << "CONSULTA " << id_recipient << " " << id_msg << ": MENSAGEM INEXISTENTE" << endl;
        }
        else{
            OutputFile << "CONSULTA " << email_find.recipient << " " << email_find.ID << ": " << email_find.message << endl;
        }

        //Fechar arquivo de saída
        OutputFile.close();

        //Retorna o email buscado
        return email_find;
    }
    
    void HashTable::SendMail(Email email){
        //Arquivo de saída
        ofstream OutputFile(outputNameArq, ios::app);

        //Insere o email na árvore referente ao seu hash adequado
        tree[hash_id(email)].insere(email);

        OutputFile << "OK: MENSAGEM " << email.ID << " PARA " << email.recipient << " ARMAZENADA EM " << hash_id(email) << endl;

        //Fecha arquivo de saída
        OutputFile.close();
    }
    
    void HashTable::erease(int id_msg, int id_recipient){
        //Email auxiliar para busca do hash
        Email email_aux;
        email_aux.create(id_msg, id_recipient, "");
        //=================================

        //Arquivo de saída
        ofstream OutputFile(outputNameArq, ios::app);

        Email email_find;
        email_find = tree[hash_id(email_aux)].pesquisa(email_aux);

        if (email_find.ID == -1){
            OutputFile << "ERRO: MENSAGEM INEXISTENTE" << endl;
        }
        else{
            tree[hash_id(email_aux)].remove(email_find);
            OutputFile << "OK: MENSAGEM APAGADA" << endl;
        }

        //Fecha Arquivo saída
        OutputFile.close();
    }
