#include <iostream>
#include <locale.h>
#include <string>
#include <vector>

using namespace std;

// Estrutura do passageiro
class passageiro {
public:
    string nome;
    string endereco;
    string telefone;
    int fidelidade = 0;
    int codigo;
    int pontos = 0;

    // Imprime no console as informações do passageiro
    void mostrarDados() const {
        cout << "Código: " << codigo << endl;
        cout << "Nome: " << nome << endl;
        cout << "Endereço: " << endereco << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "Pontos de fidelidade: " << pontos << endl;
        cout << "Fidelidade: " << (fidelidade ? "Sim" : "Não") << endl;
        cout << "=========================================" << endl;
    }
};

// Vetor global para armazenar passageiros
vector<passageiro> passageiros;

// Verifica se o código já está cadastrado
bool verificarCodigoExistente(int codigo) {
    for (const auto& p : passageiros) {
        if (p.codigo == codigo) {
            return true; // Código já existe
        }
    }
    return false; // Código não encontrado
}

// Valida se o telefone tem exatamente 11 caracteres
bool validarTelefone(const string& telefone) {
    return telefone.length() == 11;
}

// Cadastra um novo passageiro.
void cadastrarPassageiros() {
    passageiro p;
    cout << "Digite o código do passageiro: ";
    cin >> p.codigo;

    // Verifica se o código já existe
    if (verificarCodigoExistente(p.codigo)) {
        cout << "Erro: Código já cadastrado. Voltando ao menu inicial." << endl;
        return;
    }

    cin.ignore();
    cout << "Digite o nome do passageiro: ";
    getline(cin, p.nome);

    cout << "Digite o endereço do passageiro: ";
    getline(cin, p.endereco);

    cout << "Digite o telefone do passageiro: ";
    getline(cin, p.telefone);

    // Valida o telefone
    if (!validarTelefone(p.telefone)) {
        cout << "Erro: O telefone deve conter exatamente 11 caracteres. Voltando ao menu inicial." << endl;
        return;
    }

    passageiros.push_back(p);
    cout << "Passageiro cadastrado com sucesso!" << endl;
}

// Exibe as informações de um passageiro com base no código fornecido.
void mostrarPassageiros() {
    if (passageiros.empty()) {
        cout << "Nenhum passageiro cadastrado." << endl;
        return;
    }

    int codigo;
    cout << "Digite o código do passageiro que deseja visualizar: ";
    cin >> codigo;

    bool encontrado = false;
    for (const auto& p : passageiros) {
        if (p.codigo == codigo) {
            p.mostrarDados();
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Nenhum passageiro encontrado com o código informado." << endl;
    }
}

// Cadastra a fidelidade de um passageiro.
void cadastroFidelidade() {
    if (passageiros.empty()) {
        cout << "Nenhum passageiro cadastrado." << endl;
        return;
    }
    int codigo;
    cout << "Digite o código do passageiro: ";
    cin >> codigo;
    bool encontrado = false;
    for (auto& p : passageiros) {
        if (p.codigo == codigo) {
            p.fidelidade = 1;
            encontrado = true;
            break;
        }
    }
    if (encontrado) {
        cout << "Fidelidade cadastrada com sucesso!" << endl;
    } else {
        cout << "Passageiro não encontrado." << endl;
    }
}

// Mostra as informações de todos os passageiros com fidelidade cadastrados.
void mostrarFidelidade() {
    bool encontrado = false;
    for (const auto& p : passageiros) {
        if (p.fidelidade == 1) {
            p.mostrarDados();
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "Nenhum passageiro cadastrado com fidelidade." << endl;
    }
}

// Atualiza os pontos de fidelidade de um passageiro.
void atualizarFidelidade() {
    if (passageiros.empty()) {
        cout << "Nenhum passageiro cadastrado." << endl;
        return;
    }

    int codigo;
    cout << "Digite o código do passageiro para atualizar a fidelidade: ";
    cin >> codigo;

    bool encontrado = false;
    for (auto& p : passageiros) {
        if (p.codigo == codigo) {
            int novosPontos;
            cout << "Digite o novo valor de pontos de fidelidade: ";
            cin >> novosPontos;

            // Atualiza os pontos
            p.pontos = novosPontos;
            encontrado = true;
            cout << "Pontos de fidelidade atualizados com sucesso!" << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Passageiro não encontrado." << endl;
    }
}

/**
 * Exibe um menu de opções ao usuário e executa as ações
 * correspondentes. O programa permanece em loop até que o
 * usuário escolha a opção de sair.
 */
int main() {
    setlocale(LC_ALL, "portuguese");

    int opcao;
    do {
        cout << "=========================================" << endl;
        cout << "1 - Cadastrar Passageiro" << endl;
        cout << "2 - Mostrar Passageiro" << endl;
        cout << "3 - Cadastro de Fidelidade" << endl;
        cout << "4 - Mostrar Fidelidade" << endl;
        cout << "5 - Atualizar Fidelidade" << endl;  // Nova opção para atualizar fidelidade
        cout << "6 - Sair" << endl;
        cout << "=========================================" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
        case 1:
            cadastrarPassageiros();
            break;
        case 2:
            mostrarPassageiros();
            break;
        case 3:
            cadastroFidelidade();
            break;
        case 4:
            mostrarFidelidade();
            break;
        case 5:
            atualizarFidelidade();  // Chama a função para atualizar fidelidade
            break;
        case 6:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opção inválida! Por favor, tente novamente." << endl;
        }
    } while (opcao != 6);

    return 0;
}
