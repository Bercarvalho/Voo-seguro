#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <locale.h>

struct Passageiro {
    int codigo;
    std::string nome;
    std::vector<std::string> voos;
};

class SistemaDePassageiros {
private:
    std::unordered_map<int, Passageiro> passageiros;

public:
    void cadastrarPassageiro(int codigo, const std::string& nome) {
        Passageiro passageiro{codigo, nome, {}};
        passageiros[codigo] = passageiro;
    }

    void associarVoo(int codigo, const std::string& voo) {
        if (passageiros.find(codigo) != passageiros.end()) {
            passageiros[codigo].voos.push_back(voo);
        } else {
            std::cout << "Erro: Passageiro com o código " << codigo << " não encontrado." << std::endl;
        }
    }

    Passageiro* buscarPassageiro(const std::string& termo) {
        for (auto& [codigo, passageiro] : passageiros) {
            if (std::to_string(passageiro.codigo) == termo || passageiro.nome == termo) {
                return &passageiro;
            }
        }
        return nullptr;
    }

    void listarVoosPassageiro(const std::string& termo) {
        Passageiro* passageiro = buscarPassageiro(termo);
        if (passageiro != nullptr) {
            std::cout << "Voos associados ao passageiro " << passageiro->nome << ":\n";
            for (const auto& voo : passageiro->voos) {
                std::cout << "- " << voo << std::endl;
            }
        } else {
            std::cout << "Erro: Passageiro não encontrado." << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    SistemaDePassageiros sistema;
    return 0;
}
