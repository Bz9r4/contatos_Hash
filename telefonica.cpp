#include <iostream>  // Biblioteca para entrada e saída de dados padrão
#include <fstream>   // Biblioteca para manipulação de arquivos
#include <string>    // Biblioteca para manipulação de strings
#include <vector>    // Biblioteca para uso de vetores
#include <cmath>     // Biblioteca para operações matemáticas

using namespace std; // Permite usar direto os elementos do namespace std, evitando a necessidade de usar std:: antes de cada elemento

// Definimos a estrutura de cada contato
struct Contato {
    string nome;
    string telefone;
    string email;
};

// Definimos a classe para a tabela hash
class TabelaHash {
private:
    static const int TAMANHO_TABELA = 15013;               // Tamanho da tabela hash
    vector<vector<Contato>> tabela[TAMANHO_TABELA];         // Vetor de listas de contatos
    int hash(string chave);                                // Função de hash
    int hash2(string chave);                               // Segunda função de hash
public:
    void inserir(Contato c);                               // Função para inserir um contato
    vector<Contato> buscar(string chave);                  // Função para buscar contatos
    void remover(string chave);                            // Função para remover contatos
    void removerEspecifico(string chave, Contato contatoRemover);  // Função para remover um contato específico
};

// Função de hash usando o método de multiplicação
int TabelaHash::hash(string chave) {
    unsigned long hash = 0;
    for (char c : chave) {
        hash = (hash * 31) + c;  // Multiplica o hash atual por 31 e adiciona o valor ASCII do caractere
    }
    return hash % TAMANHO_TABELA;  // Retorna o hash mapeado para o tamanho da tabela
}

// Segunda função de hash para endereçamento duplo
int TabelaHash::hash2(string chave) {
    unsigned long hash = 0;
    for (char c : chave) {
        hash = (hash * 37) + c;  // Multiplica o hash atual por 37 e adiciona o valor ASCII do caractere
    }
    return (hash % (TAMANHO_TABELA - 2)) + 1;  // Retorna o hash mapeado para um intervalo de 1 a TAMANHO_TABELA - 2
}

// Função para inserir um contato na tabela hash
void TabelaHash::inserir(Contato c) {
    int index = hash(c.nome);         // Obtém o índice na tabela hash usando a função de hash
    int step = hash2(c.nome);          // Obtém o passo usando a segunda função de hash
    while (!tabela[index].empty()) {  // Enquanto a lista de contatos não estiver vazia
        index = (index + step) % TAMANHO_TABELA;  // Aplica o passo para encontrar uma posição vazia na tabela
    }
    tabela[index].push_back({c});  // Insere o contato na posição encontrada
}

// Função para buscar um contato na tabela hash
vector<Contato> TabelaHash::buscar(string chave) {
    vector<Contato> contatosEncontrados;  // Vetor para armazenar os contatos encontrados
    for (int index = 0; index < TAMANHO_TABELA; ++index) {   // Percorre toda a tabela hash
        for (const auto& listaContatos : tabela[index]) {    // Percorre cada lista de contatos na posição index
            for (const auto& contato : listaContatos) {      // Percorre cada contato na lista
                if (contato.nome.find(chave) != string::npos) {  // Verifica se o nome do contato contém a chave
                    contatosEncontrados.push_back(contato);  // Adiciona o contato aos contatos encontrados
                }
            }
        }
    }
    return contatosEncontrados;  // Retorna os contatos encontrados
}

// Função para remover um contato na tabela hash
void TabelaHash::remover(string chave) {
    int index = hash(chave);          // Obtém o índice na tabela hash usando a função de hash
    int step = hash2(chave);          // Obtém o passo usando a segunda função de hash
    while (!tabela[index].empty()) {  // Enquanto a lista de contatos não estiver vazia
        if (tabela[index][0][0].nome == chave) {  // Verifica se o primeiro contato na lista tem o mesmo nome
            tabela[index].clear();  // Remove todos os contatos com o mesmo nome
            return;
        }
        index = (index + step) % TAMANHO_TABELA;  // Aplica o passo para procurar na próxima posição
    }
}

// Função para remover um contato específico na tabela hash
void TabelaHash::removerEspecifico(string chave, Contato contatoRemover) {
    int index = hash(chave);           // Obtém o índice na tabela hash usando a função de hash
    int step = hash2(chave);           // Obtém o passo usando a segunda função de hash
    while (!tabela[index].empty()) {   // Enquanto a lista de contatos não estiver vazia
        for (size_t i = 0; i < tabela[index].size(); ++i) {   // Percorre todos os contatos na lista
            if (tabela[index][i][0].nome == chave && tabela[index][i][0].telefone == contatoRemover.telefone &&
                tabela[index][i][0].email == contatoRemover.email) {  // Verifica se o contato corresponde ao especificado
                tabela[index].erase(tabela[index].begin() + i);  // Remove o contato específico
                return;
            }
        }
        index = (index + step) % TAMANHO_TABELA;  // Aplica o passo para procurar na próxima posição
    }
}

// Função para carregar contatos do arquivo inicial
vector<Contato> carregarContatos() {
    vector<Contato> contatos;            // Vetor para armazenar os contatos
    ifstream arquivo("listaContato.txt");  // Abre o arquivo para leitura
    if (arquivo.is_open()) {              // Verifica se o arquivo foi aberto com sucesso
        string linha;
        Contato c;
        while (getline(arquivo, linha)) {  // Lê cada linha do arquivo
            if (linha.find("Nome: ") != string::npos) {       // Se a linha contém "Nome: "
                c.nome = linha.substr(6);                      // Extrai o nome do contato
            } else if (linha.find("Telefone: ") != string::npos) {  // Se a linha contém "Telefone: "
                c.telefone = linha.substr(10);                      // Extrai o telefone do contato
            } else if (linha.find("Email: ") != string::npos) {     // Se a linha contém "Email: "
                c.email = linha.substr(7);                          // Extrai o email do contato
                contatos.push_back(c);                              // Adiciona o contato ao vetor de contatos
                c = Contato();                                      // Reinicia a variável de contato
            }
        }
        arquivo.close();  // Fecha o arquivo após a leitura
    }
    return contatos;   // Retorna o vetor de contatos
}

// Função para exibir o menu e receber a escolha do usuário
char exibirMenu() {
    cout << "\n\nMenu:\n";
    cout << "1. Inserir contato\n";
    cout << "2. Buscar contato\n";
    cout << "3. Remover contato específico\n";
    cout << "4. Sair\n";
    cout << "Escolha uma opção: ";
    char opcao;
    cin >> opcao;
    return opcao;
}

// Função principal
int main() {
    TabelaHash tabela;   // Cria uma instância da classe TabelaHash

    // Carregar contatos do arquivo inicial
    vector<Contato> contatos = carregarContatos();

    // Inserir contatos na tabela hash
    for (Contato c : contatos) {
        tabela.inserir(c);
    }

    char opcao;
    do {
        opcao = exibirMenu();   // Exibe o menu e obtém a opção do usuário
        switch (opcao) {
            case '1': {          // Caso a opção seja 1 (Inserir contato)
                Contato novoContato;
                cout << "\nInserir novo contato:\n";
                cout << "Nome: ";
                cin.ignore(); // limpar o buffer de entrada padrão
                getline(cin, novoContato.nome);   // Obtém o nome do novo contato
                cout << "Telefone: ";
                getline(cin, novoContato.telefone);  // Obtém o telefone do novo contato
                cout << "Email: ";
                getline(cin, novoContato.email);     // Obtém o email do novo contato
                tabela.inserir(novoContato);         // Insere o novo contato na tabela hash
                cout << "Contato inserido com sucesso!\n";
                break;
            }
            case '2': {            // Caso a opção seja 2 (Buscar contato)
                string nomeBuscar;
                cout << "\nBuscar contato:\n";
                cout << "Nome: ";
                cin.ignore(); // limpar o buffer de entrada padrão
                getline(cin, nomeBuscar);   // Obtém o nome a ser buscado
                vector<Contato> encontrados = tabela.buscar(nomeBuscar);  // Busca os contatos com o nome fornecido
                if (!encontrados.empty()) {   // Se foram encontrados contatos
                    cout << "Contatos encontrados:\n";
                    for (Contato encontrado : encontrados) {   // Para cada contato encontrado
                        cout << encontrado.nome << ", " << encontrado.telefone << ", " << encontrado.email << endl;  // Exibe as informações do contato
                    }
                } else {   // Se nenhum contato foi encontrado
                    cout << "Contato não encontrado." << endl;
                }
                break;
            }
            case '3': {          // Caso a opção seja 3 (Remover contato específico)
                string nomeRemover;
                cout << "\nRemover contato específico:\n";
                cout << "Nome: ";
                cin.ignore(); // limpar o buffer de entrada padrão
                getline(cin, nomeRemover);   // Obtém o nome do contato a ser removido
                cout << "Telefone: ";
                string telefoneRemover;
                getline(cin, telefoneRemover);   // Obtém o telefone do contato a ser removido
                cout << "Email: ";
                string emailRemover;
                getline(cin, emailRemover);   // Obtém o email do contato a ser removido
                Contato contatoRemover;
                contatoRemover.nome = nomeRemover;
                contatoRemover.telefone = telefoneRemover;
                contatoRemover.email = emailRemover;
                tabela.removerEspecifico(nomeRemover, contatoRemover);   // Remove o contato específico da tabela hash
                cout << "Contato removido com sucesso!\n";
                break;
            }
            case '4':   // Caso a opção seja 4 (Sair)
                cout << "\nSaindo do programa.\n";
                break;
            default:    // Caso a opção seja inválida
                cout << "\nOpção inválida. Tente novamente.\n";
        }
    } while (opcao != '4');   // Repete o loop até que o usuário escolha sair

    return 0;   // Retorna 0 indicando sucesso na execução do programa
}