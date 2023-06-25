
# CONTROLE DE EVENTOS 

O projeto consiste em um sistema de controle de listas para gerenciar e coordenadar a entrada de pessoas a determinados eventos. Desse modo,  o objetivo principal pauta-sem em garantir uma lista de entradas eficiente. Assim esse mecanismo fornece uma forma de criação, modificação e cancelamento desses eventos. 


## Autores

- Hadassa Gouvêa 
- Marcelle Andrade Peraira 


## About/Descrição

### Problema 

A carência de um sistema especializado no controle de listas de participantes de grandes eventos pode ser uma lacuna significativa na gestão eficiente dessas ocasiões. A organização de eventos de grande porte requer um gerenciamento adequado dos participantes, desde o registro inicial até a presença no local. Sem um sistema especializado para lidar com essas listas, podem surgir diversos desafios e problemas.

Um sistema especializado permite automatizar e simplificar o processo de gerenciamento, facilitando a organização do evento e proporcionando uma experiência mais agradável tanto para os organizadores quanto para os participantes. Como: 

     Registros e atualizações manuais: Sem um sistema especializado, os registros dos participantes e as atualizações nas listas devem ser feitos manualmente, o que pode ser demorado e propenso a erros. Além disso, lidar com grandes volumes de informações se torna uma tarefa complexa e difícil de gerenciar eficientemente.

### Objetivo

Promover a facilitação do gerenciamento de listas de participantes de eventos envolvendo a adoção de medidas e recursos que tornam o processo mais eficiente, preciso e conveniente tanto para os organizadores quanto para os participantes.

    Sistema especializado;
    Automação de processos;
    Análise de dados e relatórios;


## Funcionalidades

- Criar lista de Eventos; 
- Remover lista de Eventos;
- Adicionar Novos participantes; 
- Imprimir Relatórios;

## Requisitos


#### SOBRE O CADASTRO DE NOVO EVENTO

|_ID_|      _DESCRIÇÃO DO REQUISITO_   |
|------|-------------------------------|
|R01|O sistema terá a possibilidade de que o usuário crie um novo cadastro através do menu|
|R02|O usuário poderá adicionar eventos com o complemto de nome, data, hora e quantidade de participantes|
|R03|O usuário poderá visualizar lista de consulta para a remoção do evento|
|R04|O usuário poderá remover lista de eventos criadas através de pesquisa informado o ID e o Nome do Evento|

#### SOBRE O CADASTRO DE PARTICIPANTE 
|_ID_|      _DESCRIÇÃO DO REQUISITO_   |
|------|-------------------------------|
|R01|O sistema terá a possibilidade de que o usuário crie um novo participante, desde de que o número seja definido na opção de criação da lista|
|R02|O usuário ao inserir participante ao evento devera adicionar informações como nome, telefone e e-mail|
|R03|O sistema ao remover o evento também removerá os participantes existentes no mesmo.|

#### SOBRE O RELATÓRIO
|_ID_|      _DESCRIÇÃO DO REQUISITO_   |
|------|-------------------------------|
|R01|O sistema terá a vizualização dos relatórios através do menu com a opção de vizualizar relatórios|


##  TO DO
|_ITEM_|             _ESPOÇO GERAL_                | _Descrição_| _CONCLUÍDA_|
|------|-------------------------------------------|---------------|------------|
|`0`|`COMPONENTE DO TODO`|`CRIAÇÃO DO BANCO DE DADOS (ARQUIVO)`|100%|
|`1`|`SELECIONAR EVENTO -> SELECIONAR LISTA`|`GERENCIAMENTO DE ENTRADAS`|100%|
|1.1|Selecionar Lista| Criação de  Paricipante |100%|
|`2`|`EVENTO -> LISTA DE PARTICIPANTES`|`GERENCIAMENTO DE EVENTOS E LISTAS`|100%|
|2.1|Criação Lista| CRD Evento |100%|
|2.2|Criação Lista| CRD Lista de Participantes |100%|
|`3`|`BANCO DE DADOS ARQUIVO`|`CONTROLE DE EVENTOS`|100%|
|3.1|Criação de arquivo binário| CRD Evento |100%|
|2.2|Criação de arquivo temporário| CRD Lista de Participantes |100%|


## Instrução de Uso de Código 
### Para Modificações no Código 
#### Windows 

    1. Para abrir um projeto no Code::Blocks, siga estas etapas:
- Baixe os arquivos correspondentes ao projeto no Win pelo repositório; 
- Abra o Code::Blocks em seu computador.
- No menu principal, clique em "File" (Arquivo).
- No menu suspenso, selecione "Open" (Abrir).
- Navegue até o diretório onde o projeto está localizado.
- Selecione o arquivo de projeto com a extensão ".cbp". Por exemplo, se o seu projeto se chama "MeuProjeto", você deve selecionar o arquivo "MeuProjeto.cbp".
- Clique em "Open" (Abrir) para abrir o projeto.
- O Code::Blocks carregará o projeto e exibirá a estrutura do projeto no painel lateral esquerdo. Você poderá ver os arquivos-fonte, cabeçalhos e outros recursos do projeto.
- Realize as contribuições ou modificações necessárias. 

A partir desse ponto, você pode compilar e executar o projeto clicando no botão "Build and Run" (Compilar e Executar) ou usando os atalhos de teclado relevantes. Certifique-se de ter configurado corretamente as opções de compilação e vinculação do projeto antes de tentar compilar e executar.

Lembre-se de que, para abrir um projeto no Code::Blocks, você precisa ter o Code::Blocks instalado em seu computador e o projeto deve ter sido criado ou configurado corretamente dentro do Code::Blocks.

OBSERVAÇÃO: Há uma função no código para a limpeza do menu que pode ser ultilizado apenas no Linux sendo o clearsrc();, porém caso ultilize no Windows esta opção função ainda fará efeito poré haverá um warning no código. 

### Linux 

    2. Para abrir um projeto no Code::Blocks no Linux, você pode seguir estas etapas:

- Baixe os arquivos correspondentes ao projeto no Linux pelo repositório; 
- Abra o terminal em seu sistema Linux. Você pode encontrar o terminal na lista de aplicativos ou usar o atalho de teclado Ctrl + Alt + T.
- Navegue até o diretório onde o projeto está localizado usando o comando cd. Por exemplo, se o seu projeto estiver em 
    "/home/usuario/MeuProjeto"
        você pode usar o comando:
    _cd /home/usuario/MeuProjeto_
- Após navegar até o diretório do projeto, digite o comando codeblocks no terminal e pressione Enter. Isso abrirá o Code::Blocks e carregará o projeto automaticamente.

- A partir desse ponto, você pode compilar e executar o projeto usando os recursos do Code::Blocks.

- Certifique-se de ter configurado corretamente as opções de compilação e vinculação do projeto antes de tentar compilar e executar.

- Lembre-se de que essas instruções pressupõem que o projeto foi criado ou configurado corretamente dentro do Code::Blocks e que você tenha o Code::Blocks instalado em seu sistema Linux.

### Para uso da Aplicação 
#### Windows 

 1. Para abrir um executável no Windows, siga estas etapas:

- Navegue até o local onde o arquivo executável está armazenado no seu computador. Isso pode ser feito usando o Explorador de Arquivos. Você pode abrir o Explorador de Arquivos clicando no ícone da pasta na barra de tarefas ou pressionando a tecla Windows + E.

- Localize o arquivo executável com a extensão ".exe" que você deseja abrir.

- Dê um duplo clique no arquivo executável. Isso iniciará a execução do programa.

- Alternativamente, você também pode abrir um executável usando o Prompt de Comando:

- Abra o Prompt de Comando. Você pode pesquisar por "Prompt de Comando" na barra de pesquisa do menu Iniciar ou pressionar a tecla Windows + R, digitar "cmd" e pressionar Enter.

- Navegue até o diretório onde o arquivo executável está localizado. Use o comando cd seguido do caminho completo do diretório. Por exemplo:
    cd C:\Caminho\para\o\arquivo
- Digite o nome do arquivo executável com a extensão ".exe" e pressione Enter. Isso iniciará a execução do programa.

### Para uso da Aplicação 
#### Linux
    1. Compilação:

- Abra o terminal ou prompt de comando.

- Navegue até o diretório onde o arquivo do código-fonte (ex: main.c) está localizado.

- Execute o comando de compilação para gerar o executável do programa. Por exemplo: gcc -Wall -Wextra -g3 main.c ../lib/users.c ../lib/client.c ../lib/pecas.c ../lib/config.c -o main.exe
- Execução: No terminal ou prompt de comando, execute o programa compilado. Por exemplo: ./main.exe

###### Trecho Retirado do repositório : https://github.com/djouni/GEA/


## Roteiro de Testes 
    O roteiro de teste do da aplicação se faz em: 

        1. Cadastro de novo Evento; 
            1.1 Adicionar informações: nome, data e hora; 
            1.2 Informar número de participantes (Quantidade máx 4); 
            1.3 Informar dados dos participantes: nome, telefone e e-mail;
        2, Vizualizar cadastros: Quantidade de participantes e quantidade de eventos; 
        3. Remover evento; 
            3.1. Consulta de id e nome do evento; 
            3.2. Remoção do evento; 
        4. Finalizar Programa(Sair); 
## Devs e bugs 
### Desenvolvimento 

    1. void criaListas(LSE_Evento *e) = Cria listas de novos eventos; 
    2. void cadastro(LSE_Evento *e) = Cria novos cadastros de pessoas; 
    3. void insereEArquiva(LSE_Evento *e, Evento *evento, int nParticipantes) = insere e arquiva cadastros; 
    4. int imprimeCadastros(LSE_Evento *e) = imprime cadastros; 
    5. int imprimeConsulta(LSE_Evento *e) = imprime lista de colnsulta para a remoção; 
    6. Evento *pesquisaEvento(LSE_Evento *e, char nomeEvento[20], int idEvento) = pesquisa evento para a remoção; 
    7. void removeEDesarquivaCadastro(LSE_Evento *e, Evento *evento)= remove eventos; 
    8. int i = variavel global de controle; 

### Bugs
    1. Comnado fgets pulava a leitura  de string = substituição por scanf; 
    2. Erro na função de remover arquivo, pois não estava removendo; 


## Demonstração

<img src="fotos/CODE BLOCKS .png"/>
<img src="fotos/vs code.png"/>


## Referências 

Repositórios: 

https://github.com/djouni/GEA/blob/main/README.md
