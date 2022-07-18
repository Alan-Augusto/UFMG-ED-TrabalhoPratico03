#include <iostream>
#include <emails.h>
#include <fstream>
#include <sstream>

using namespace std;

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

//NÓ DA ÁRVORE BINÁRIA
    tipo_no::tipo_no(){
        left = NULL;
        right = NULL;
    }

//ÁRVORE BINÁRIA
    //Construtor
    bintree::bintree(){
        raiz = NULL;
    }

    //Methods
    void bintree::insere(Email email){
        insere_recursivo(raiz, email);
    }

    void bintree::insere_recursivo(tipo_no *&p, Email email){
        if (p == NULL){
            p = new tipo_no();
            p->email = email;
        }
        else{
            //LEMEMLOG============================
            if (email.ID < p->email.ID){
                insere_recursivo(p->left, email);
            }
            else{
                insere_recursivo(p->right, email);
            }
        }
    }

    void bintree::clean(){
        apaga_recursivo(raiz);
        raiz = NULL;
    }

    void bintree::apaga_recursivo(tipo_no *p){
        if (p != NULL){
            apaga_recursivo(p->left);
            apaga_recursivo(p->right);
            delete p;
        }
    }

    Email bintree::pesquisa(Email email){
        return pesquisa_recursivo(raiz, email);
    }

    Email bintree::pesquisa_recursivo(tipo_no *no, Email email){
        Email aux;
        if (no == NULL){
            aux.ID = -1;
            return aux; 
        }
        //LEMEMLOG================================
        if (email.ID < no->email.ID){
            return pesquisa_recursivo(no->left, email);
        }
        else if (email.ID > no->email.ID){
            return pesquisa_recursivo(no->right, email);
        }
        else{
            return no->email;
        }
    }

    void bintree::remove(Email email){
        return remove_recursivo(raiz, email);
    }

    void bintree::remove_recursivo(tipo_no *&no, Email email){
        tipo_no *aux;

        //IMPRESSÃO
        //ofstream saida(name_output, ios::app);

        if (no == NULL){
            cout << "ERRO: MENSAGEM INEXISTENTE" << endl;
        }
        //LEMEMLOG================================
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

            cout << "OK: MENSAGEM APAGADA" << endl;
            
            //Fecha arquivo de saída
            //saida.close();
        }
    }

    void bintree::antecessor(tipo_no *q, tipo_no *&r){
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
    hashtable::hashtable(int M){
        this->table = new bintree[M];
        size = M;
    }

    int hashtable::hash_id(Email email){
        int aux = (email.ID % size);
        return aux;
    }

    Email hashtable::pesquisa(int id_msg, int id_recipient){
        int pos;

        //Email auxiliar para busca do hash
        Email email_aux;
        email_aux.ID = id_msg;
        email_aux.recipient = id_recipient;
        //=================================

        //Pega a posição do email que está buscando
        pos = hash_id(email_aux);

        //Tentar fazer assim...
        //email_aux = table[hash_id(email)].pesquisa(email_aux);

        //Traz o email que está buscando diretamente da árvore referente à tabela hash
        Email email_find;
        email_find = table[pos].pesquisa(email_aux);

        //Arquivo de impressão
        //ofstream saida(name_output, ios::app);

        //Se não existe ID ou o destinatário é diferente daquele procurado:
        if (email_find.ID == -1 || email_find.recipient != email_aux.recipient){
            cout << "CONSULTA " << email_find.recipient << " " << email_find.ID << ": MENSAGEM INEXISTENTE" << endl;
        }
        else{
            cout << "CONSULTA " << email_find.recipient << " " << email_find.ID << ": " << email_find.message << endl;
        }

        //Fechar arquivo de saída
        //saida.close();

        //Retorna o email buscado
        return email_find;
    }
    
    void hashtable::insere(Email email, int M){
        int pos;

        //Arquivo de saída
        //ofstream saida(name_output, ios::app);

        //Busca a posição da árvore binária correta
        pos = hash_id(email);
        //Insere o email na árvore adequada
        table[pos].insere(email);

        cout << "OK: MENSAGEM " << email.ID << " PARA " << email.recipient << " ARMAZENADA EM " << pos << endl;

        //FEcha arquivo de saída
        //saida.close();
    }
    
    void hashtable::remove(int id_msg, int id_recipient){
        int pos;

        //Email auxiliar para busca do hash
        Email email_aux;
        email_aux.ID = id_msg;
        email_aux.recipient = id_recipient;
        //=================================

        //Arquivo de saída
        //ofstream saida(name_output, ios::app);

        pos = hash_id(email_aux);

        Email email_find;
        email_find = table[pos].pesquisa(email_aux);

        if (email_find.ID == -1){
            cout << "ERRO: MENSAGEM INEXISTENTE" << endl;
        }
        else{
            table[pos].remove(email_find);
        }

        //Fecha Arquivo saída
        //saida.close();
    }
