#include <iostream>
#include <string>  
#include <fstream>  

using namespace std; 

  // Define uma estrutura chamada contato para armazenar informações de contato
  struct contato {
        string nome;     // Nome do contato
        string telefone; // Número de telefone do contato
        string email;    // Endereço de e-mail do contato
    };

struct arquivo
{
    string arquivoNome = "./nome.txt";
    string arquivoTemporario = "./email.txt";
};



void add() { 

    // Declara uma variável novoContato do tipo contato para armazenar as informações do novo contato
    contato novoContato;
    arquivo Arquivo;


    
    fstream arqAdd(Arquivo.arquivoNome , ios::out | ios::app);

    // Verifica se o arquivo foi aberto com sucesso
    if (arqAdd.is_open()) {
        // Solicita ao usuário para inserir informações de contato
        cout << "Nome: ";
        cin >> novoContato.nome;
        // Escreve o nome do contato no arquivo
        arqAdd << "Nome: " << novoContato.nome << endl;

        cout << "Telefone: ";
        cin >> novoContato.telefone;
        arqAdd << "Telefone: " << novoContato.telefone << endl;

        cout << "Email: ";
        cin >> novoContato.email;
        arqAdd << "Email: " << novoContato.email << endl;

        // Informa ao usuário que o contato foi adicionado com sucesso
        cout << "Contato adicionado com sucesso!" << endl;

        // Fecha o arquivo
        arqAdd.close();
    } else {
        // Se o arquivo não puder ser aberto, informa ao usuário
        cout << "O arquivo não foi aberto ou não existe" << endl;
    }
}




void removeContatoNome() {

    
    // Declara uma variável novoContato do tipo contato para armazenar as informações do novo contato
    contato novoContato;
    arquivo Arquivo;



    cout << "Digite o nome do contato a ser removido: ";
    cin >> novoContato.nome;

    

    // Abre o arquivo original em modo de leitura
    ifstream arqOriginal(Arquivo.arquivoNome);


    // Cria um arquivo temporário para armazenar os contatos restantes
    ofstream arqTemp(Arquivo.arquivoTemporario);

    if (arqOriginal.is_open() && arqTemp.is_open()) {
        string linha;



        bool contatoEncontrado = false;


        // Lê o arquivo original linha por linha
        while (getline(arqOriginal, linha)) {


            // Se a linha contém o nome do contato a ser removido, pula para a próxima linha
            if (linha.find("Nome: " + novoContato.nome) != string::npos) {
                contatoEncontrado = true;


                // Pula as próximas duas linhas correspondentes ao telefone e e-mail
                getline(arqOriginal, linha);
                getline(arqOriginal, linha);
                continue;
            }
            // Escreve a linha no arquivo temporário
            arqTemp << linha << endl;
        }



        arqOriginal.close();
        arqTemp.close();

        // Remove o arquivo original e renomeia o arquivo temporário para o nome original
        remove("./nome.txt");
        rename("./email.txt", ".nome.txt");

        if (contatoEncontrado) {
            cout << "Contato removido com sucesso!" << endl;
        } else {
            cout << "Contato não encontrado." << endl;
        }
    } else {
        cout << "Não foi possível abrir os arquivos." << endl;
    }

     
}



void removeContatoEmail() {

    
    // Declara uma variável novoContato do tipo contato para armazenar as informações do novo contato
    contato novoContato;
    arquivo Arquivo;



    cout << "Digite o email do contato a ser removido: ";
    cin >> novoContato.email;

    

    // Abre o arquivo original em modo de leitura
    ifstream arqOriginal(Arquivo.arquivoNome);


    // Cria um arquivo temporário para armazenar os contatos restantes
    ofstream arqTemp(Arquivo.arquivoTemporario);

    if (arqOriginal.is_open() && arqTemp.is_open()) {
        string linha;



        bool contatoEncontrado = false;


        // Lê o arquivo original linha por linha
        while (getline(arqOriginal, linha)) {


            // Se a linha contém o nome do contato a ser removido, pula para a próxima linha
            if (linha.find("Email: " + novoContato.email) != string::npos) {
                contatoEncontrado = true;


                // Pula as próximas duas linhas correspondentes ao telefone e e-mail
                getline(arqOriginal, linha);
                getline(arqOriginal, linha);
                continue;
            }
            // Escreve a linha no arquivo temporário
            arqTemp << linha << endl;
        }



        arqOriginal.close();
        arqTemp.close();

        // Remove o arquivo original e renomeia o arquivo temporário para o nome original
        remove("./nome.txt");
        rename("./email.txt", ".nome.txt");

        if (contatoEncontrado) {
            cout << "Contato removido com sucesso!" << endl;
        } else {
            cout << "Contato não encontrado." << endl;
        }
    } else {
        cout << "Não foi possível abrir os arquivos." << endl;
    }

    
}



void removeContatoTelefone() {

    
    // Declara uma variável novoContato do tipo contato para armazenar as informações do novo contato
    contato novoContato;
    arquivo Arquivo;



    cout << "Digite o telefone do contato a ser removido: ";
    cin >> novoContato.telefone;

    

    // Abre o arquivo original em modo de leitura
    ifstream arqOriginal(Arquivo.arquivoNome);


    // Cria um arquivo temporário para armazenar os contatos restantes
    ofstream arqTemp(Arquivo.arquivoTemporario);

    if (arqOriginal.is_open() && arqTemp.is_open()) {
        string linha;



        bool contatoEncontrado = false;


        // Lê o arquivo original linha por linha
        while (getline(arqOriginal, linha)) {


            // Se a linha contém o nome do contato a ser removido, pula para a próxima linha
            if (linha.find("Telefone: " + novoContato.telefone) != string::npos) {
                contatoEncontrado = true;


                // Pula as próximas duas linhas correspondentes ao telefone e e-mail
                getline(arqOriginal, linha);
                getline(arqOriginal, linha);
                continue;
            }
            // Escreve a linha no arquivo temporário
            arqTemp << linha << endl;
        }



         arqOriginal.close();
         arqTemp.close();


        // Remove o arquivo original e renomeia o arquivo temporário para o nome original
        remove("./nome.txt");
        rename("./email.txt", ".nome.txt");

        if (contatoEncontrado) {
            cout << "Contato removido com sucesso!" << endl;
        } else {
            cout << "Contato não encontrado." << endl;
        }
    } else {
        cout << "Não foi possível abrir os arquivos." << endl;
    }
 

}




int main(){

   add();


   removeContatoNome();
   //removeContatoEmail();
   //removeContatoTelefone();

    return 0;
}