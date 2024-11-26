#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

struct Voo {
    int codigo;
    string data;
    string hora;
    string origem;
    string destino;
    int codigoAviao;
    vector<int> codigosTripulacao; // Primeiro e segundo são piloto e copiloto, seguidos pelos comissários
    float tarifa;
    bool ativo;
};

void cadastrarVoo() {
    Voo voo;
    cout << "Código do voo: ";
    cin >> voo.codigo;
    cout << "Data (dd/mm/aaaa): ";
    cin >> voo.data;
    cout << "Hora (hh:mm): ";
    cin >> voo.hora;
    cout << "Origem: ";
    cin >> voo.origem;
    cout << "Destino: ";
    cin >> voo.destino;
    cout << "Código do avião: ";
    cin >> voo.codigoAviao;
    
    int codigoTripulacao;
    cout << "Digite os códigos dos tripulantes (piloto, copiloto, comissários). Digite -1 para encerrar: " << endl;
    while (true) {
        cin >> codigoTripulacao;
        if (codigoTripulacao == -1) {
            break;
        }
        voo.codigosTripulacao.push_back(codigoTripulacao);
    }
    
    cout << "Tarifa: ";
    cin >> voo.tarifa;

    // Validação da tripulação
    if (voo.codigosTripulacao.size() >= 2) {
        voo.ativo = true;
    } else {
        voo.ativo = false;
        cout << "Tripulação insuficiente. O voo será marcado como inativo." << endl;
    }

    // Salvando os dados em um arquivo binário
    ofstream arquivo("voos.bin", ios::binary | ios::app);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    // Escrever os dados no arquivo
    arquivo.write(reinterpret_cast<char*>(&voo.codigo), sizeof(voo.codigo));
    arquivo.write(voo.data.c_str(), voo.data.size() + 1);
    arquivo.write(voo.hora.c_str(), voo.hora.size() + 1);
    arquivo.write(voo.origem.c_str(), voo.origem.size() + 1);
    arquivo.write(voo.destino.c_str(), voo.destino.size() + 1);
    arquivo.write(reinterpret_cast<char*>(&voo.codigoAviao), sizeof(voo.codigoAviao));

    int tripulacaoSize = voo.codigosTripulacao.size();
    arquivo.write(reinterpret_cast<char*>(&tripulacaoSize), sizeof(tripulacaoSize));
    for (int codigo : voo.codigosTripulacao) {
        arquivo.write(reinterpret_cast<char*>(&codigo), sizeof(codigo));
    }

    arquivo.write(reinterpret_cast<char*>(&voo.tarifa), sizeof(voo.tarifa));
    arquivo.write(reinterpret_cast<char*>(&voo.ativo), sizeof(voo.ativo));

    arquivo.close();
    cout << "Voo cadastrado com sucesso!" << endl;

    // Testes
    if (voo.ativo) {
        cout << "Teste: Voo cadastrado com tripulação mínima está ativo." << endl;
    } else {
        cout << "Teste: Voo sem tripulação mínima está inativo." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    char opcao;
    do {
        cadastrarVoo();
        cout << "Deseja cadastrar outro voo? (s/n): ";
        cin >> opcao;
    } while (opcao == 's' || opcao == 'S');
    
    return 0;
}
