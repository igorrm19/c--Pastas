#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <vector>
#include <fstream>
#include <string>
teste

using namespace std;

// Tipos de veículos
enum TipoVeiculo { COMUM, PRIORITARIO, EMERGENCIA, SERVICO };

// Representação de um veículo
struct Veiculo {
    string placa;
    TipoVeiculo tipo;

    Veiculo(string p, TipoVeiculo t) : placa(p), tipo(t) {}
};

// Conversão do tipo para string
string tipoToString(TipoVeiculo tipo) {
    switch (tipo) {
        case COMUM: return "Comum";
        case PRIORITARIO: return "Prioritário";
        case EMERGENCIA: return "Emergência";
        case SERVICO: return "Serviço";
        default: return "Desconhecido";
    }
}

// Capacidade de vagas
const int MAX_VAGAS = 10;

// Estruturas principais
vector<Veiculo*> vagas(MAX_VAGAS, nullptr); // nullptr = vaga livre
queue<Veiculo> filaEntrada;
deque<Veiculo> filaSaida;
list<Veiculo> estacionamento;

// Adiciona veículo na fila de entrada com prioridade
void adicionarVeiculo() {
    string placa;
    int tipo;
    cout << "Placa: ";
    cin >> placa;
    cout << "Tipo (0-Comum, 1-Prioritário, 2-Emergência, 3-Serviço): ";
    cin >> tipo;

    Veiculo v(placa, static_cast<TipoVeiculo>(tipo));

    if (v.tipo == EMERGENCIA) {
        queue<Veiculo> novaFila;
        novaFila.push(v);
        while (!filaEntrada.empty()) {
            novaFila.push(filaEntrada.front());
            filaEntrada.pop();
        }
        filaEntrada = novaFila;
    } else if (v.tipo == PRIORITARIO) {
        queue<Veiculo> novaFila;
        novaFila.push(v);
        while (!filaEntrada.empty()) {
            novaFila.push(filaEntrada.front());
            filaEntrada.pop();
        }
        filaEntrada = novaFila;
    } else {
        filaEntrada.push(v);
    }

    cout << "Veículo " << placa << " adicionado à fila de entrada." << endl;
}

// Aloca veículo da fila para uma vaga
void alocarVaga() {
    for (int i = 0; i < MAX_VAGAS && !filaEntrada.empty(); ++i) {
        if (vagas[i] == nullptr) {
            Veiculo v = filaEntrada.front();
            filaEntrada.pop();
            vagas[i] = new Veiculo(v);
            estacionamento.push_back(v);
            cout << "Veículo " << v.placa << " estacionado na vaga " << i << endl;
            return;
        }
    }
    cout << "Sem vagas disponíveis." << endl;
}

// Move veículo do estacionamento para fila de saída
void moverParaSaida(string placa) {
    for (auto it = estacionamento.begin(); it != estacionamento.end(); ++it) {
        if (it->placa == placa) {
            filaSaida.push_back(*it);
            estacionamento.erase(it);
            cout << "Veículo " << placa << " movido para fila de saída." << endl;
            return;
        }
    }
    cout << "Veículo não encontrado no estacionamento." << endl;
}

// Realiza saída do estacionamento (frente ou fundo)
void sairDoEstacionamento(bool pelaFrente) {
    if (filaSaida.empty()) {
        cout << "Fila de saída vazia." << endl;
        return;
    }

    Veiculo v = (pelaFrente ? filaSaida.front() : filaSaida.back());
    if (pelaFrente)
        filaSaida.pop_front();
    else
        filaSaida.pop_back();

    for (int i = 0; i < MAX_VAGAS; ++i) {
        if (vagas[i] && vagas[i]->placa == v.placa) {
            delete vagas[i];
            vagas[i] = nullptr;
            break;
        }
    }

    ofstream hist("historico.txt", ios::app);
    hist << "Saída: " << v.placa << " (" << tipoToString(v.tipo) << ")\n";
    hist.close();

    cout << "Veículo " << v.placa << " saiu do estacionamento." << endl;
}

// Lista todos os veículos no sistema
void listar() {
    cout << "\n--- Fila de Entrada ---\n";
    queue<Veiculo> tempEntrada = filaEntrada;
    while (!tempEntrada.empty()) {
        Veiculo v = tempEntrada.front();
        tempEntrada.pop();
        cout << v.placa << " - " << tipoToString(v.tipo) << endl;
    }

    cout << "\n--- Estacionados ---\n";
    for (auto v : estacionamento) {
        cout << v.placa << " - " << tipoToString(v.tipo) << endl;
    }

    cout << "\n--- Fila de Saída ---\n";
    for (auto v : filaSaida) {
        cout << v.placa << " - " << tipoToString(v.tipo) << endl;
    }
}

// Menu principal
void menu() {
    int opcao;
    string placa;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1 - Adicionar veículo à fila de entrada\n";
        cout << "2 - Alocar veículo em vaga\n";
        cout << "3 - Mover veículo para saída\n";
        cout << "4 - Sair do estacionamento\n";
        cout << "5 - Listar status\n";
        cout << "0 - Encerrar\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                alocarVaga();
                break;
            case 3:
                cout << "Placa do veículo para mover à saída: ";
                cin >> placa;
                moverParaSaida(placa);
                break;
            case 4:
                int porta;
                cout << "Sair pela (1) frente ou (2) fundo? ";
                cin >> porta;
                sairDoEstacionamento(porta == 1);
                break;
            case 5:
                listar();
                break;
            case 0:
                cout << "Encerrando sistema.\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }

    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}