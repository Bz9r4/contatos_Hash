# 2 Avaliação Laboratorio de estruturas 2
# Autores:
Brendo Duarte Bezerra, Guilheme Nunes Araujo, Carlos Henryque de Andrade Soares.

Função de mapeamento: Método do multiplicação <br>
Tratamento de colisão (Endereçamento Aberto): Duplo hash.

---

# Documentação do Código

## 1. Introdução
Este codigo implementa um sistema de lista de contatos utilizando uma tabela hash com tratamento de colisão por endereçamento aberto com **hash duplo** e função de mapeamento baseada no método de **multiplicação**. O sistema permite a inserção, busca e remoção de contatos.

## 2. Estrutura do Código
A estrutura do código pode ser dividida em 7 partes principais:

### 2.1. Inclusão de Bibliotecas
Primeiro começamos incluindo as bibliotecas necessárias para operações de entrada/saída, manipulação de arquivos, manipulação de strings e vetor, além da biblioteca <cmath> para funções matemáticas.

### 2.2. Definição da Estrutura de Contato
Em seguida, é definida uma estrutura chamada Contato, que contém os campos nome, telefone e email, omde serão armazenado os dados do usuario.

### 2.3. Definição da Classe `TabelaHash`
Uma classe chamada TabelaHash é definida para representar a tabela hash e suas operações. Ela inclui métodos para inserir, buscar e remover contatos, bem como funções auxiliares para calcular os hashes.

### 2.4. Implementação das Funções de Hash
Duas funções de hash são implementadas: hash e hash2. A função **hash** utiliza o método de multiplicação para calcular o hash das chaves, enquanto a função **hash2** é utilizada para calcular o passo de incremento no tratamento de colisões.

### 2.5. Implementação das Operações da Tabela Hash
As operações principais da tabela hash, como inserção, busca e remoção, são implementadas dentro da classe TabelaHash.

### 2.6. Carregamento de Contatos do Arquivo
Uma função chamada **carregarContatos** é definida para ler os contatos de um arquivo de texto e armazená-los em um vetor.

### 2.7. Função Principal main
A função principal **main** controla a execução do programa. Ela inicializa a tabela hash, carrega os contatos do arquivo, exibe um menu interativo e processa as operações escolhidas pelo usuário.

## 3. Funcionamento do Programa
O programa funciona como um sistema de lista de contatos, onde o usuário pode realizar várias operações, como inserção, busca e remoção de contatos. Aqui está uma visão geral do funcionamento do programa:

1. **Inicialização da Tabela Hash:** O programa começa inicializando uma instância da classe **TabelaHash**, que representa a estrutura de dados principal para armazenar os contatos.

2. **Carregamento de Contatos:** Em seguida, o programa lê os contatos de um arquivo de texto chamado **"listaContato.txt"** usando a função **carregarContatos**. Cada linha do arquivo contém informações sobre um contato, incluindo nome, telefone e email. Os contatos são armazenados em uma estrutura de vetor.

3. **Menu Interativo:** Após carregar os contatos, o programa exibe um menu interativo para o usuário. O menu oferece as seguintes opções:

+ Inserir contato
+ Buscar contato
+ Remover contato específico
+ Sair do programa

4. **Inserção de Contato:** Se o usuário escolher a opção de inserir contato, o programa solicitará que o usuário forneça o nome, telefone e email do novo contato. Essas informações são então adicionadas à tabela hash usando o método inserir.

5. **Busca de Contato:** Se o usuário escolher a opção de buscar contato, o programa solicitará que o usuário insira o nome completo ou parcial do contato desejado. O programa então realiza uma busca na tabela hash usando o método buscar, retornando todos os contatos que correspondem ao critério de busca.

6. **Remoção de Contato:** Se o usuário escolher a opção de remover contato específico, o programa solicitará que o usuário forneça o nome, telefone e email do contato a ser removido. O programa então remove o contato específico da tabela hash usando o método **removerEspecifico**.

7. **Encerramento do Programa:** O programa continua a exibir o menu interativo até que o usuário escolha a opção de sair. Quando isso acontece, o programa exibe uma mensagem de encerramento e termina sua execução.

## 4. Conclusão
Em conclusão, o sistema de lista de contatos implementado oferece uma solução eficiente e robusta para gerenciar informações de contato. Utilizando uma tabela hash com tratamento de colisão por endereçamento aberto e função de mapeamento baseada no método de multiplicação, o programa demonstra uma abordagem sólida para lidar com um grande volume de dados de maneira rápida e eficaz.

Ao longo da análise do código e do funcionamento do programa, podemos observar que ele oferece funcionalidades essenciais para inserção, busca e remoção de contatos, além de lidar adequadamente com situações como colisões de hash e remoção de contatos específicos.

Em suma, o sistema de lista de contatos desenvolvido apresenta um bom equilíbrio entre eficiência, funcionalidade e facilidade de uso, fornecendo uma base sólida para futuros desenvolvimentos e personalizações conforme necessário.

---