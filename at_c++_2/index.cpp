#include <iostream>
#include <stack>
#include <string>

std::string validarExpressao(const std::string& expressao) {
    std::stack<char> pilha;
    int indice = 0;

    for (char caractere : expressao) {
        indice++;

        if (caractere == '(' || caractere == '[' || caractere == '{') {
            pilha.push(caractere);
        } else if (caractere == ')' || caractere == ']' || caractere == '}') {
            if (pilha.empty()) {
                return "Erro na posição " + std::to_string(indice) + ": '" + caractere + "' sem par de abertura!";
            }

            char topo = pilha.top();
            pilha.pop();

            if ((caractere == ')' && topo != '(') ||
                (caractere == ']' && topo != '[') ||
                (caractere == '}' && topo != '{')) {
                return "Erro na posição " + std::to_string(indice) + 
                       ": '" + caractere + "' não fecha corretamente '" + topo + "'!";
            }
        }
    }

    if (!pilha.empty()) {
        return "Erro: " + std::to_string(pilha.size()) + 
               " parêntese(s) não fechado(s) (último: '" + pilha.top() + "')!";
    }

    return "Expressão correta!";
}

int main() {
    std::string entrada;
    std::cout << "Digite a expressão: ";
    getline(std::cin, entrada);

    std::cout << "\n=== Resultado ===\n" << validarExpressao(entrada) << std::endl;

    return 0;
}