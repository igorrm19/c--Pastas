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