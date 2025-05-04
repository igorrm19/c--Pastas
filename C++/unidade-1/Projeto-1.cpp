#include <iostream>
#include <stack>
#include <string>

// Retorna uma mensagem detalhada em vez de apenas true/false
std::string verificarBalanceamento(const std::string& expressao) {
    std::stack<char> pilha;
    int posicao = 0; // Rastreia a posição do caractere atual

    for (char caractere : expressao) {
        posicao++;

        // Caso 1: Caractere de abertura
        if (caractere == '(' || caractere == '[' || caractere == '{') {
            pilha.push(caractere);
        }

        // Caso 2: Caractere de fechamento
        else if (caractere == ')' || caractere == ']' || caractere == '}') {
            if (pilha.empty()) {
                return "ERRO na posição " + std::to_string(posicao) + ": Fechamento '" + caractere + "' sem abertura correspondente!";
            }

            char topo = pilha.top();
            pilha.pop();

            // Verifica correspondência
            if ((caractere == ')' && topo != '(') ||
                (caractere == ']' && topo != '[') ||
                (caractere == '}' && topo != '{')) {
                return "ERRO na posição " + std::to_string(posicao) + 
                       ": Fechamento '" + caractere + "' não corresponde à abertura '" + topo + "'!";
            }
        }
    }

    // Caso 3: Sobram aberturas não fechadas
    if (!pilha.empty()) {
        return "ERRO: " + std::to_string(pilha.size()) + 
               " abertura(s) não fechada(s) (último aberto: '" + pilha.top() + "')!";
    }

    return "Expressão balanceada!";
}

int main() {
    std::string expressao;
    std::cout << "Digite a expressão matemática: ";
    getline(std::cin, expressao);

    std::string resultado = verificarBalanceamento(expressao);
    std::cout << "\n=== Resultado ===\n" << resultado << std::endl;

    return 0;
}