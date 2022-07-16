#include <iostream>
#include <getopt.h>
#include <string>
#include <sstream>
#include <fstream>
#include <emails.h>

using namespace std;

char *inputNameArq = NULL;
char *outputNameArq  = NULL;

void Assert(bool x, string text){
    if(!x){
        cout << text << endl;
        exit(0);
    }
}

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
    ofstream OutputFile(outputNameArq);
    Assert(OutputFile.is_open(), "Opening error in output file");
    
//Variáveis
    //HashTable
    //HasTable H;
    //Linha completa
    string line;

//Execução
    //Tamanho da tabela Hash
    getline(InputFile, line);
    OutputFile << "Tamanho da atbela Hash ->" << stoi(line) << endl;

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
            
            //Área de impressão===========================
            OutputFile << "operation: " << operation << endl;
            OutputFile << "ID_recipient: " << ID_recipient << endl;
            OutputFile << "ID_email: " << ID_email << endl;
            OutputFile << "message: " << message << endl;
            //============================================
            
        }

        if(operation == "CONSULTA"){
            //Área de impressão===========================
            OutputFile << "operation: " << operation << endl;
            OutputFile << "ID_recipient: " << ID_recipient << endl;
            OutputFile << "ID_email: " << ID_email << endl;
            //============================================
        }

        if(operation == "APAGA"){
            //Área de impressão===========================
            OutputFile << "operation: " << operation << endl;
            OutputFile << "ID_recipient: " << ID_recipient << endl;
            OutputFile << "ID_email: " << ID_email << endl;
            //============================================
            
        }
    }
    

//Fecha os arquivos
    InputFile.close();
    OutputFile.close();
    return 0;
}