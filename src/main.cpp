#include <iostream>
#include <getopt.h>
#include <string>
#include <sstream>
#include <fstream>
#include <emails.h>

using namespace std;

char *inputNameArq = NULL;
char *outputNameArq  = NULL;

void parse_args(int argc,char ** argv){
     // variaveis externas do getopt
     extern char * optarg;
 
     // variavel auxiliar
     int c;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((c = getopt(argc, argv, "i:I:o:O:")) != EOF)
       switch(c) {
         case 'i':
            inputNameArq = optarg;
            break;

         case 'I':
            inputNameArq = optarg;
            break;

         case 'o':
            outputNameArq = optarg;
            break;

         case 'O':
            outputNameArq = optarg;
            break;

         default:
                  exit(1);

       }
}

int main(int argc, char ** argv)
{
//Avalia linha de comando
    parse_args(argc,argv);
    
//Abre Arquivo de entrada
    ifstream InputFile(inputNameArq);
    Assert(InputFile.is_open(), "Opening error in input file");
    //Abre o arquivo de saída
    
//Variáveis
    //Linha completa
    string line;
    
    //Cria a tabela hash de acordo com o valor informado na primeira linha
    getline(InputFile, line);
    hashtable Server(stoi(line), outputNameArq);

//Execução
    //interpreta operação recebida em uma linha:
    while (getline(InputFile, line))
    {
        //Cria variável de iteração da linha
        stringstream lineIT(line);

        //Variáveis de operação:
        string operation;
        int ID_recipient;
        int ID_email;

        //Recebe as 3 primeiras informações:
        lineIT >> operation;
        lineIT >> ID_recipient;
        lineIT >> ID_email;

        if(operation == "ENTREGA"){
            //Variáveis exclusivas de entrega
            int textSize;
            string message;
            
            //Recolhe tamanho do texto
            lineIT >> textSize;

            //Recolhe o texto:
            for (int i = 0; i < textSize; i++)
            {
                string aux;
                lineIT >> aux;

                message += aux;

                if(i < textSize-1){
                    message += " ";
                }
            }
            
            //Cria um email com as informações coletadas;
            Email Em;
            Em.create(ID_email, ID_recipient, message);

            //Entrga o email na posição correta da tabela hash existente
            Server.SendMail(Em);
            
        }

        if(operation == "CONSULTA"){
            //Recolhe informações da consulta
            lineIT >> ID_recipient;
            lineIT >> ID_email;

            Server.find(ID_email, ID_recipient);
            

        }

        if(operation == "APAGA"){
            //Recolhe informações da consulta
            lineIT >> ID_recipient;
            lineIT >> ID_email;

            Server.erease(ID_email, ID_recipient);    
        }
    }
    

//Fecha os arquivos
    InputFile.close();
    return 0;
}