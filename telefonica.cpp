#include <iostream> // Biblioteca para entrada/saída padrão
#include <fstream> // Biblioteca para manipulação de arquivos
#include <string> // Biblioteca para manipulação de strings
#include <vector> // Biblioteca para uso de vetores
#include <cmath> // Biblioteca para funções matemáticas

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
    static const int TAMANHO_TABELA = 15013; // Primo próximo de 10.000 / 0.75
    vector<Contato> tabela[TAMANHO_TABELA]; // Vetor de listas para armazenar os contatos
    int hash(string chave); // Função de hash
    int hash2(string chave); // Segunda função de hash para endereçamento duplo
public:
    void inserir(Contato c); // Função para inserir um contato
    Contato buscar(string chave); // Função para buscar um contato
    void remover(string chave); // Função para remover um contato
};

// Função de hash usando o método de multiplicação
int TabelaHash::hash(string chave) {
    unsigned long hash = 0;
    for (char c : chave) {
        hash = (hash * 31) + c; // Multiplicação por 31 e adição do código ASCII do caractere
    }
    return hash % TAMANHO_TABELA; // Retorno do valor do hash módulo o tamanho da tabela
}

// Segunda função de hash para endereçamento duplo
int TabelaHash::hash2(string chave) {
    unsigned long hash = 0;
    for (char c : chave) {
        hash = (hash * 37) + c; // Multiplicação por 37 e adição do código ASCII do caractere
    }
    return (hash % (TAMANHO_TABELA - 2)) + 1; // Retorno de um valor entre 1 e TAMANHO_TABELA - 2
}

// Função para inserir um contato na tabela hash
void TabelaHash::inserir(Contato c) {
    int index = hash(c.nome); // Calcula o índice usando a função de hash
    int step = hash2(c.nome); // Calcula o passo usando a segunda função de hash
    while (!tabela[index].empty()) { // Enquanto o slot não estiver vazio
        index = (index + step) % TAMANHO_TABELA; // Aplica o passo circularmente
    }
    tabela[index].push_back(c); // Insere o contato no slot vazio
}

// Função para buscar um contato na tabela hash
Contato TabelaHash::buscar(string chave) {
    int index = hash(chave); // Calcula o índice usando a função de hash
    int step = hash2(chave); // Calcula o passo usando a segunda função de hash
    while (!tabela[index].empty()) { // Enquanto o slot não estiver vazio
        for (Contato &contato : tabela[index]) { // Percorre os contatos no slot
            if (contato.nome == chave) { // Se o nome do contato corresponder à chave
                return contato; // Retorna o contato encontrado
            }
        }
        index = (index + step) % TAMANHO_TABELA; // Aplica o passo circularmente
    }
    // Retornar um contato vazio se não encontrado
    return Contato{"", "", ""};
}

// Função para remover um contato na tabela hash
void TabelaHash::remover(string chave) {
    int index = hash(chave); // Calcula o índice usando a função de hash
    int step = hash2(chave); // Calcula o passo usando a segunda função de hash
    while (!tabela[index].empty()) { // Enquanto o slot não estiver vazio
        for (auto it = tabela[index].begin(); it != tabela[index].end(); ++it) { // Percorre os contatos no slot
            if (it->nome == chave) { // Se o nome do contato corresponder à chave
                tabela[index].erase(it); // Remove o contato encontrado
                return; // Sai da função
            }
        }
        index = (index + step) % TAMANHO_TABELA; // Aplica o passo circularmente
    }
}

// Função para carregar contatos do arquivo inicial
vector<Contato> carregarContatos() {
    vector<Contato> contatos; // Vetor para armazenar os contatos
    ifstream arquivo("listaContato.txt"); // Abre o arquivo para leitura
    if (arquivo.is_open()) { // Se o arquivo foi aberto com sucesso
        string linha;
        Contato c; // Variável temporária para armazenar os contatos lidos
        while (getline(arquivo, linha)) { // Lê cada linha do arquivo
            if (linha.find("Nome: ") != string::npos) { // Se a linha contiver "Nome: "
                c.nome = linha.substr(6); // Remove "Nome: " e armazena o nome
            } else if (linha.find("Telefone: ") != string::npos) { // Se a linha contiver "Telefone: "
                c.telefone = linha.substr(10); // Remove "Telefone: " e armazena o telefone
            } else if (linha.find("Email: ") != string::npos) { // Se a linha contiver "Email: "
                c.email = linha.substr(7); // Remove "Email: " e armazena o email
                contatos.push_back(c); // Adiciona o contato ao vetor
                c = Contato(); // Limpa a variável temporária para o próximo contato
            }
        }
        arquivo.close(); // Fecha o arquivo
    }
    return contatos; // Retorna o vetor de contatos lidos do arquivo
}

// Função para exibir o menu e receber a escolha do usuário
char exibirMenu() {
    cout << "\n\nMenu:\n";
    cout << "1. Inserir contato\n";
    cout << "2. Buscar contato\n";
    cout << "3. Remover contato\n";
    cout << "4. Sair\n";
    cout << "Escolha uma opção: ";
    char opcao;
    cin >> opcao; // Lê a opção escolhida pelo usuário
    return opcao; // Retorna a opção escolhida
}

int main() {
    TabelaHash tabela; // Instância da classe TabelaHash

    // Carregar contatos do arquivo inicial
    vector<Contato> contatos = carregarContatos();

    // Inserir contatos na tabela hash
    for (Contato c : contatos) {
        tabela.inserir(c);
    }

    char opcao;
    do {
        opcao = exibirMenu(); // Exibe o menu e lê a opção escolhida pelo usuário
        switch (opcao) {
            case '1': {
                Contato novoContato; // Variável para armazenar o novo contato a ser inserido
                cout << "\nInserir novo contato:\n";
                cout << "Nome: ";
                cin.ignore(); // Limpa o buffer do teclado
                getline(cin, novoContato.nome); // Lê o nome do novo contato
                cout << "Telefone: ";
                getline(cin, novoContato.telefone); // Lê o telefone do novo contato
                cout << "Email: ";
                getline(cin, novoContato.email); // Lê o email do novo contato
                tabela.inserir(novoContato); // Insere o novo contato na tabela hash
                cout << "Contato inserido com sucesso!\n";
                break;
            }
            case '2': {
                string nomeBuscar; // Variável para armazenar o nome do contato a ser buscado
                cout << "\nBuscar contato:\n";
                cout << "Nome: ";
                cin.ignore(); // Limpa o buffer do teclado
                getline(cin, nomeBuscar); // Lê o nome do contato a ser buscado
                Contato encontrado = tabela.buscar(nomeBuscar); // Busca o contato na tabela hash
                if (encontrado.nome != "") { // Se o contato foi encontrado
                    cout << "Contato encontrado: " << encontrado.nome << ", " << encontrado.telefone << ", " << encontrado.email << endl;
                } else { // Se o contato não foi encontrado
                    cout << "Contato não encontrado." << endl;
                }
                break;
            }
            case '3': {
                string nomeRemover; // Variável para armazenar o nome do contato a ser removido
                cout << "\nRemover contato:\n";
                cout << "Nome: ";
                cin.ignore(); // Limpa o buffer do teclado
                getline(cin, nomeRemover); // Lê o nome do contato a ser removido
                tabela.remover(nomeRemover); // Remove o contato da tabela hash
                cout << "Contato removido com sucesso!\n";
                break;
            }
            case '4':
                cout << "\nSaindo do programa.\n"; // Exibe mensagem de saída
                break;
            default:
                cout << "\nOpção inválida. Tente novamente.\n"; // Exibe mensagem de opção inválida
        }
    } while (opcao != '4'); // Repete até que o usuário escolha sair

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
