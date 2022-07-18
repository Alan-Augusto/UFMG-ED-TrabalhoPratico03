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
    //Linha completa
    string line;
    
    //Cria a tabela hash de acordo com o valor informado na primeira linha
    getline(InputFile, line);
    hashtable Server(stoi(line));

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
            Em.ID = ID_email;
            Em.recipient = ID_recipient;
            Em.message = message;

            //Entrga o email na posição correta da tabela hash existente
            //Hash.SendMail();
            
        }

        if(operation == "CONSULTA"){
            //Consulta um email na tabela hash existente
            //Hash.ConsultMail();

        }

        if(operation == "APAGA"){
            //Apaga um email da tabela hash existente
            //Hash.DeleteMail();
                       
        }
    }
    

//Fecha os arquivos
    InputFile.close();
    OutputFile.close();
    return 0;
}