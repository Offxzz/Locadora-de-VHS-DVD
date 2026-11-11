
// MODULO DE LOCACOES E RELATORIOS
// Autor: Ian Leuche - RGM 04806941-8

#ifndef LOCACOES_H
#define LOCACOES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LOCACOES 50
#define ARQUIVO_LOCACOES "locacoes.csv"


// ============================================================================
// PARTE 1: DADOS
// ============================================================================

struct Locacao {
    int idLocacao;
    int idCliente;
    char nomeCliente[50];   // guardado como estava no dia da locacao (como uma nota)
    int idFilme;
    char tituloFilme[50];
    int tipoMidia;          // 1 = VHS, 2 = DVD
    int diasLocacao;
    float valorTotal;
    int devolvido;          // 1 = devolvido, 0 = em aberto
};

struct Locacao historicoLocacoes[MAX_LOCACOES];
int totalLocacoes = 0;

// Usada nos rankings: um item por filme (ou por cliente)
struct ItemRanking {
    int id;
    char nome[50];
    int quantidade;
    float total;
};


// ============================================================================
// PARTE 2: PONTE COM OS MODULOS DOS COLEGAS  (*** TEMPORARIA ***)
// Estas 3 funcoes serao trocadas para consultar os vetores reais de
// clientes.h e filmes.h. Os dados abaixo sao so de teste.
// ============================================================================

char clientesTeste[8][50] = {"Ana Souza", "Bruno Lima", "Carla Dias", "Diego Rocha",
                             "Elisa Prado", "Fabio Nunes", "Gabriela Reis", "Hugo Matos"};
char filmesTeste[8][50] = {"De Volta para o Futuro", "Matrix", "Titanic", "O Rei Leao",
                           "Jurassic Park", "Tubarao", "Ghost", "Os Cacas-Fantasmas"};
int midiasTeste[8] = {1, 2, 1, 2, 2, 1, 1, 2};
float diariasTeste[8] = {4.0, 5.0, 4.5, 3.5, 5.0, 4.0, 3.5, 4.5};
int copiasTeste[8] = {3, 2, 2, 4, 3, 1, 2, 3};

// Devolve 1 se o cliente existe (e copia o nome em nomeSaida), 0 se nao existe
int ponteBuscarCliente(int idCliente, char *nomeSaida) {
    if (idCliente < 1 || idCliente > 8) {
        return 0;
    }
    strcpy(nomeSaida, clientesTeste[idCliente - 1]);
    return 1;
}

// Devolve 1 se o filme existe (e preenche titulo, midia, diaria e copias), 0 se nao
int ponteBuscarFilme(int idFilme, char *tituloSaida, int *tipoMidia, float *diaria, int *copias) {
    if (idFilme < 1 || idFilme > 8) {
        return 0;
    }
    strcpy(tituloSaida, filmesTeste[idFilme - 1]);
    *tipoMidia = midiasTeste[idFilme - 1];
    *diaria = diariasTeste[idFilme - 1];
    *copias = copiasTeste[idFilme - 1];
    return 1;
}

// Soma "variacao" as copias do filme (-1 ao alugar, +1 ao devolver)
void ponteAjustarCopias(int idFilme, int variacao) {
    if (idFilme >= 1 && idFilme <= 8) {
        copiasTeste[idFilme - 1] += variacao;
    }
}


// ============================================================================
// PARTE 3: ARQUIVO CSV
// ============================================================================

// Reescreve o arquivo inteiro com o que esta no vetor (modo "w" apaga e regrava)
void salvarLocacoesCSV() {
    FILE *arquivo = fopen(ARQUIVO_LOCACOES, "w");
    int i;

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel gravar o arquivo %s!\n", ARQUIVO_LOCACOES);
        return;
    }

    for (i = 0; i < totalLocacoes; i++) {
        fprintf(arquivo, "%d;%d;%s;%d;%s;%d;%d;%.2f;%d\n",
                historicoLocacoes[i].idLocacao,
                historicoLocacoes[i].idCliente,
                historicoLocacoes[i].nomeCliente,
                historicoLocacoes[i].idFilme,
                historicoLocacoes[i].tituloFilme,
                historicoLocacoes[i].tipoMidia,
                historicoLocacoes[i].diasLocacao,
                historicoLocacoes[i].valorTotal,
                historicoLocacoes[i].devolvido);
    }

    fclose(arquivo);
}

// Chamada uma vez ao abrir o programa: le o arquivo e enche o vetor
void carregarLocacoesCSV() {
    FILE *arquivo = fopen(ARQUIVO_LOCACOES, "r");
    char linha[200];
    struct Locacao l;

    totalLocacoes = 0;

    if (arquivo == NULL) {
        return; // primeira execucao: o arquivo ainda nao existe
    }

    while (totalLocacoes < MAX_LOCACOES && fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%d;%d;%49[^;];%d;%49[^;];%d;%d;%f;%d",
                   &l.idLocacao, &l.idCliente, l.nomeCliente,
                   &l.idFilme, l.tituloFilme, &l.tipoMidia,
                   &l.diasLocacao, &l.valorTotal, &l.devolvido) == 9) {
            historicoLocacoes[totalLocacoes] = l;
            totalLocacoes++;
        }
    }

    fclose(arquivo);
}


// ============================================================================
// PARTE 4: FUNCOES AUXILIARES
// ============================================================================

// Le um inteiro do teclado. Se digitarem letra, descarta e devolve -1
int lerInteiro() {
    int valor, c;

    if (scanf("%d", &valor) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
            // limpa o que sobrou digitado
        }
        return -1;
    }
    return valor;
}

// Copia origem para destino com tudo em minusculo (busca sem diferenciar maiuscula)
void paraMinusculo(const char *origem, char *destino) {
    int i;
    for (i = 0; origem[i] != '\0'; i++) {
        destino[i] = tolower((unsigned char)origem[i]);
    }
    destino[i] = '\0';
}

// Procura uma locacao pelo ID. Devolve a posicao no vetor, ou -1 se nao achar
int buscarIndicePorId(int idLocacao) {
    int i;
    for (i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idLocacao == idLocacao) {
            return i;
        }
    }
    return -1;
}

// Proximo ID = maior ID existente + 1 (evita repetir ID depois de remover)
int proximoIdLocacao() {
    int i, maior = 0;
    for (i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idLocacao > maior) {
            maior = historicoLocacoes[i].idLocacao;
        }
    }
    return maior + 1;
}

// Mostra uma locacao (a que esta na posicao i do vetor) em uma linha
void exibirLocacao(int i) {
    printf("#%d | %s | %s (%s) | %d dia(s) | R$ %.2f | %s\n",
           historicoLocacoes[i].idLocacao,
           historicoLocacoes[i].nomeCliente,
           historicoLocacoes[i].tituloFilme,
           historicoLocacoes[i].tipoMidia == 1 ? "VHS" : "DVD",
           historicoLocacoes[i].diasLocacao,
           historicoLocacoes[i].valorTotal,
           historicoLocacoes[i].devolvido ? "Devolvido" : "Em aberto");
}


// ============================================================================
// PARTE 5: FUNCOES DO MODULO (CADASTRAR, LISTAR, BUSCAR, DEVOLVER, EDITAR, REMOVER)
// ============================================================================

void cadastrarLocacao() {
    struct Locacao nova;
    float diaria;
    int copias;

    if (totalLocacoes >= MAX_LOCACOES) {
        printf("\n[ERRO] Limite de locacoes atingido!\n");
        return;
    }

    printf("\nID do cliente: ");
    nova.idCliente = lerInteiro();
    if (!ponteBuscarCliente(nova.idCliente, nova.nomeCliente)) {
        printf("[ERRO] Cliente nao encontrado!\n");
        return;
    }
    printf("Cliente: %s\n", nova.nomeCliente);

    printf("ID do filme: ");
    nova.idFilme = lerInteiro();
    if (!ponteBuscarFilme(nova.idFilme, nova.tituloFilme, &nova.tipoMidia, &diaria, &copias)) {
        printf("[ERRO] Filme nao encontrado!\n");
        return;
    }
    if (copias <= 0) {
        printf("[ERRO] Nenhuma copia disponivel de \"%s\"!\n", nova.tituloFilme);
        return;
    }
    printf("Filme: %s | Diaria: R$ %.2f | Copias: %d\n", nova.tituloFilme, diaria, copias);

    printf("Quantidade de dias: ");
    nova.diasLocacao = lerInteiro();
    if (nova.diasLocacao <= 0) {
        printf("[ERRO] Quantidade de dias invalida!\n");
        return;
    }

    nova.idLocacao = proximoIdLocacao();
    nova.valorTotal = nova.diasLocacao * diaria;   // calculado automaticamente
    nova.devolvido = 0;

    ponteAjustarCopias(nova.idFilme, -1);          // uma copia a menos no estoque

    historicoLocacoes[totalLocacoes] = nova;
    totalLocacoes++;
    salvarLocacoesCSV();

    printf("\nLocacao %d registrada! Total: R$ %.2f\n", nova.idLocacao, nova.valorTotal);
}

void listarLocacoes() {
    int i;

    if (totalLocacoes == 0) {
        printf("\nNenhuma locacao registrada ainda.\n");
        return;
    }

    printf("\n--- LOCACOES REGISTRADAS (%d) ---\n", totalLocacoes);
    for (i = 0; i < totalLocacoes; i++) {
        exibirLocacao(i);
    }
}

// Busca textual: acha o trecho digitado no nome do cliente OU no titulo do filme
void buscarLocacao() {
    char termo[50] = "";
    char termoMin[50], nomeMin[50], tituloMin[50];
    int i, encontradas = 0;

    printf("\nDigite parte do nome do cliente ou do titulo do filme: ");
    scanf(" %49[^\n]", termo);
    paraMinusculo(termo, termoMin);

    printf("\n--- RESULTADO DA BUSCA ---\n");
    for (i = 0; i < totalLocacoes; i++) {
        paraMinusculo(historicoLocacoes[i].nomeCliente, nomeMin);
        paraMinusculo(historicoLocacoes[i].tituloFilme, tituloMin);

        if (strstr(nomeMin, termoMin) != NULL || strstr(tituloMin, termoMin) != NULL) {
            exibirLocacao(i);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma locacao encontrada para \"%s\".\n", termo);
    }
}

void devolverLocacao() {
    int id, posicao;

    printf("\nID da locacao a devolver: ");
    id = lerInteiro();
    posicao = buscarIndicePorId(id);

    if (posicao == -1) {
        printf("[ERRO] Locacao nao encontrada!\n");
        return;
    }
    if (historicoLocacoes[posicao].devolvido == 1) {
        printf("[AVISO] Esta locacao ja foi devolvida.\n");
        return;
    }

    historicoLocacoes[posicao].devolvido = 1;
    ponteAjustarCopias(historicoLocacoes[posicao].idFilme, 1);   // a copia volta ao estoque
    salvarLocacoesCSV();

    printf("\nDevolucao da locacao %d registrada!\n", id);
}

// Edita a quantidade de dias e recalcula o valor com a mesma diaria
void editarLocacao() {
    int id, posicao, novosDias;
    float diaria;

    printf("\nID da locacao a editar: ");
    id = lerInteiro();
    posicao = buscarIndicePorId(id);

    if (posicao == -1) {
        printf("[ERRO] Locacao nao encontrada!\n");
        return;
    }

    printf("Locacao atual: ");
    exibirLocacao(posicao);

    printf("Novo numero de dias: ");
    novosDias = lerInteiro();
    if (novosDias <= 0) {
        printf("[ERRO] Quantidade de dias invalida!\n");
        return;
    }

    diaria = historicoLocacoes[posicao].valorTotal / historicoLocacoes[posicao].diasLocacao;
    historicoLocacoes[posicao].diasLocacao = novosDias;
    historicoLocacoes[posicao].valorTotal = novosDias * diaria;
    salvarLocacoesCSV();

    printf("\nLocacao %d atualizada! Novo total: R$ %.2f\n", id, historicoLocacoes[posicao].valorTotal);
}

void removerLocacao() {
    int id, posicao, i;
    char confirmacao;

    printf("\nID da locacao a remover: ");
    id = lerInteiro();
    posicao = buscarIndicePorId(id);

    if (posicao == -1) {
        printf("[ERRO] Locacao nao encontrada!\n");
        return;
    }

    printf("Locacao: ");
    exibirLocacao(posicao);
    printf("Confirma a remocao? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Remocao cancelada.\n");
        return;
    }

    // Se ainda estava em aberto, a copia volta ao estoque
    if (historicoLocacoes[posicao].devolvido == 0) {
        ponteAjustarCopias(historicoLocacoes[posicao].idFilme, 1);
    }

    // Puxa todas as locacoes seguintes uma posicao para tras (fecha o buraco)
    for (i = posicao; i < totalLocacoes - 1; i++) {
        historicoLocacoes[i] = historicoLocacoes[i + 1];
    }
    totalLocacoes--;
    salvarLocacoesCSV();

    printf("\nLocacao %d removida!\n", id);
}


// ============================================================================
// PARTE 6: RELATORIOS
// ============================================================================

// Matriz 2D: linhas = tipo de midia (0 VHS, 1 DVD); colunas = quantidade, dias, faturamento
void relatorioResumoPorMidia() {
    float resumo[2][3] = {{0, 0, 0}, {0, 0, 0}};
    int i, linha;

    for (i = 0; i < totalLocacoes; i++) {
        linha = historicoLocacoes[i].tipoMidia - 1;
        resumo[linha][0] += 1;
        resumo[linha][1] += historicoLocacoes[i].diasLocacao;
        resumo[linha][2] += historicoLocacoes[i].valorTotal;
    }

    printf("\n--- RESUMO POR TIPO DE MIDIA ---\n");
    printf("%-6s | %-9s | %-6s | %s\n", "Midia", "Locacoes", "Dias", "Faturamento");
    printf("%-6s | %-9.0f | %-6.0f | R$ %.2f\n", "VHS", resumo[0][0], resumo[0][1], resumo[0][2]);
    printf("%-6s | %-9.0f | %-6.0f | R$ %.2f\n", "DVD", resumo[1][0], resumo[1][1], resumo[1][2]);
    printf("Faturamento total: R$ %.2f\n", resumo[0][2] + resumo[1][2]);
}

// Conta as locacoes agrupando por filme (porFilme = 1) ou por cliente (porFilme = 0)
int montarRanking(struct ItemRanking ranking[], int porFilme) {
    int i, j, id, achou, n = 0;
    char *nome;

    for (i = 0; i < totalLocacoes; i++) {
        if (porFilme) {
            id = historicoLocacoes[i].idFilme;
            nome = historicoLocacoes[i].tituloFilme;
        } else {
            id = historicoLocacoes[i].idCliente;
            nome = historicoLocacoes[i].nomeCliente;
        }

        achou = -1;
        for (j = 0; j < n; j++) {
            if (ranking[j].id == id) {
                achou = j;
            }
        }

        if (achou == -1) {
            ranking[n].id = id;
            strcpy(ranking[n].nome, nome);
            ranking[n].quantidade = 1;
            ranking[n].total = historicoLocacoes[i].valorTotal;
            n++;
        } else {
            ranking[achou].quantidade++;
            ranking[achou].total += historicoLocacoes[i].valorTotal;
        }
    }
    return n;
}

// Bubble Sort: do maior para o menor numero de locacoes
void ordenarRanking(struct ItemRanking ranking[], int n) {
    int i, j;
    struct ItemRanking aux;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (ranking[j].quantidade < ranking[j + 1].quantidade) {
                aux = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = aux;
            }
        }
    }
}

void relatorioRanking(int porFilme) {
    struct ItemRanking ranking[MAX_LOCACOES];
    int n, i;

    if (totalLocacoes == 0) {
        printf("\nNenhuma locacao registrada ainda.\n");
        return;
    }

    n = montarRanking(ranking, porFilme);
    ordenarRanking(ranking, n);

    if (porFilme) {
        printf("\n--- RANKING: FILMES MAIS ALUGADOS ---\n");
    } else {
        printf("\n--- RANKING DE CLIENTES (1o = CLIENTE VIP) ---\n");
    }

    for (i = 0; i < n; i++) {
        printf("%do | %s | %d locacao(oes) | R$ %.2f\n",
               i + 1, ranking[i].nome, ranking[i].quantidade, ranking[i].total);
    }
}

void relatorioEmAberto() {
    int i, abertas = 0;
    float totalAberto = 0;

    printf("\n--- LOCACOES EM ABERTO ---\n");
    for (i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].devolvido == 0) {
            exibirLocacao(i);
            abertas++;
            totalAberto += historicoLocacoes[i].valorTotal;
        }
    }

    if (abertas == 0) {
        printf("Nenhuma locacao em aberto.\n");
    } else {
        printf("Total em aberto: %d locacao(oes) | R$ %.2f\n", abertas, totalAberto);
    }
}


// ============================================================================
// PARTE 7: MENUS
// ============================================================================

void menuRelatorios() {
    int opcao;

    limparTela();
    do {
        printf("\n--- [RELATORIOS DE LOCACOES] ---\n");
        printf("1. Resumo por Tipo de Midia (VHS x DVD)\n");
        printf("2. Ranking de Filmes Mais Alugados\n");
        printf("3. Ranking de Clientes (Cliente VIP)\n");
        printf("4. Locacoes em Aberto\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                relatorioResumoPorMidia();
                break;
            case 2:
                relatorioRanking(1);
                break;
            case 3:
                relatorioRanking(0);
                break;
            case 4:
                relatorioEmAberto();
                break;
            case 0:
                printf("\nVoltando ao menu de locacoes...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
    limparTela();
}

void moduloLocacoesRelatorios() {
    int opcao;

    limparTela();
    do {
        printf("\n--- [MODULO 4: LOCACOES E RELATORIOS] ---\n");
        printf("1. Registrar Nova Locacao\n");
        printf("2. Listar Locacoes\n");
        printf("3. Buscar Locacao (cliente ou filme)\n");
        printf("4. Registrar Devolucao\n");
        printf("5. Editar Locacao\n");
        printf("6. Remover Locacao\n");
        printf("7. Relatorios\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                cadastrarLocacao();
                break;
            case 2:
                listarLocacoes();
                break;
            case 3:
                buscarLocacao();
                break;
            case 4:
                devolverLocacao();
                break;
            case 5:
                editarLocacao();
                break;
            case 6:
                removerLocacao();
                break;
            case 7:
                menuRelatorios();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

#endif
