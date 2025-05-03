#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

enum TipoVeiculo { COMUM, PRIORITARIO, EMERGENCIA, SERVICO };

struct Veiculo {
    string placa;
    TipoVeiculo tipo;

    Veiculo(string p, TipoVeiculo t) : placa(p), tipo(t) {}
};

string tipoToString(TipoVeiculo tipo) {
    switch (tipo) {
        case COMUM: return "Comum";
        case PRIORITARIO: return "Prioritário";
        case EMERGENCIA: return "Emergência";
        case SERVICO: return "Serviço";
        default: return "Desconhecido";
    }
}

const int MAX_VAGAS = 10;
vector<Veiculo*> vagas(MAX_VAGAS, nullptr);
deque<Veiculo> filaEntrada;
deque<Veiculo> filaSaida;
list<Veiculo> estacionamento;

void adicionarVeiculo() {
    string placa;
    int tipo;

    cout << "Placa: ";
    cin >> placa;

    cout << "Tipo (0-Comum, 1-Prioritário, 2-Emergência, 3-Serviço): ";
    cin >> tipo;

    if (tipo < 0 || tipo > 3) {
        cout << "Tipo inválido!" << endl;
        return;
    }

    Veiculo v(placa, static_cast<TipoVeiculo>(tipo));

    if (v.tipo == EMERGENCIA) {
        filaEntrada.push_front(v);
    } else if (v.tipo == PRIORITARIO) {
        auto it = filaEntrada.begin();
        while (it != filaEntrada.end() && it->tipo == EMERGENCIA)
            ++it;
        filaEntrada.insert(it, v);
    } else {
        filaEntrada.push_back(v);
    }

    cout << "Veículo " << placa << " adicionado à fila de entrada." << endl;
}
void adicionarVeiculo() {
    string placa;
    int tipo;

    cout << "Placa: ";
    cin >> placa;

    cout << "Tipo (0-Comum, 1-Prioritário, 2-Emergência, 3-Serviço): ";
    cin >> tipo;

    if (tipo < 0 || tipo > 3) {
        cout << "Tipo inválido!"<< endl ;
        return;
    }

    Veiculo v(placa, static_cast<TipoVeiculo>(tipo));

    if (v.tipo == EMERGENCIA) {
        filaEntrada.push_front(v);
    } else if (v.tipo == PRIORITARIO) {
        auto it = filaEntrada.begin();
        while (it != filaEntrada.end() && it->tipo == EMERGENCIA)
            ++it;
        filaEntrada.insert(it, v);
    } else {
        filaEntrada.push_back(v);
    }

    cout << "Veículo " << placa << " adicionado à fila de entrada." << endl;
}

void alocarVaga() {
    for (int i = 0; i < MAX_VAGAS && !filaEntrada.empty(); ++i) {
        if (vagas[i] == nullptr) {
            Veiculo v = filaEntrada.front();
            filaEntrada.pop_front();
            vagas[i] = new Veiculo(v);
            estacionamento.push_back(v);
            cout << "Veículo " << v.placa << " estacionado na vaga "<<i<< << endl;
            return;
        }
    }
    cout << "Sem vagas disponíveis." << eendl;
}
void moverParaSaida(string placa) {
    for (auto it = estacionamento.begin(); it != estacionamento.end(); ++it) {
        if (it->placa == placa) {
            for (int i = 0; i < MAX_VAGAS; ++i) {
                if (vagas[i] && vagas[i]->placa == placa) {
                    delete vagas[i];
                    vagas[i] = nullptr;
                    break;
                }
            }

            filaSaida.push_back(*it);
            estacionamento.erase(it);
            cout << "Veículo " << placa << " movido para fila de saída." << endl;
            return;
        }
    }
    cout << "Veículo não encontrado no estacionamento." << endl;
}

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

    ofstream hist("historico.txt", ios::app);
    hist << "Saída: " << v.placa << " (" << tipoToString(v.tipo) << ")\n";
    hist.close();

    cout << "Veículo " << v.placa << " saiu do estacionamento." << endl;
}
