// MODULO DE LOCACOES E RELATORIOS
// Autor: Ian Leuche - RGM 04806941-8

#ifndef LOCACOES_H
#define LOCACOES_H

#include <stdio.h>
#include <string.h>

#define MAX_LOCACOES 50
#define ARQUIVO_LOCACOES "locacoes.csv"

struct Locacao {
    int idLocacao;
    int idCliente;
    char nomeCliente[50];
    int idFilme;
    char tituloFilme[50];
    int diasLocacao;
    float valorTotal;
    int devolvido;       
};

struct Locacao historicoLocacoes[MAX_LOCACOES];
int totalLocacoes = 0;

struct ItemRanking {
    int idFilme;
    char titulo[50];
    int quantidade;
};

char titulosTeste[10][50] = {"Os Caca-Fantasmas", "De Volta para o Futuro", "Os Goonies",
                             "Rambo - Programado para Matar", "Curtindo a Vida Adoidado",
                             "Top Gun - Ases Indomaveis", "O Exterminador do Futuro",
                             "Karate Kid - A Hora da Verdade",
                             "Indiana Jones e os Cacadores da Arca Perdida", "Superman - O Filme"};
float diariasTeste[10] = {5.0, 5.0, 4.5, 4.5, 4.0, 5.0, 5.0, 4.0, 4.5, 4.0};
int copiasTeste[10] = {3, 4, 2, 3, 2, 3, 2, 3, 2, 1};

int ponteBuscarFilme(int idFilme, char *tituloSaida, float *diaria, int *copias) {
    if (idFilme < 1 || idFilme > 10) {
        return 0;
    }
    strcpy(tituloSaida, titulosTeste[idFilme - 1]);
    *diaria = diariasTeste[idFilme - 1];
    *copias = copiasTeste[idFilme - 1];
    return 1;
}

void ponteAjustarCopias(int idFilme, int variacao) {
    if (idFilme >= 1 && idFilme <= 10) {
        copiasTeste[idFilme - 1] += variacao;
    }
}

void salvarLocacoesCSV() {
    FILE *arquivo = fopen(ARQUIVO_LOCACOES, "w");
    int i;

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel gravar o arquivo %s!\n", ARQUIVO_LOCACOES);
        return;
    }

    for (i = 0; i < totalLocacoes; i++) {
        fprintf(arquivo, "%d;%d;%s;%d;%s;%d;%.2f;%d\n",
                historicoLocacoes[i].idLocacao,
                historicoLocacoes[i].idCliente,
                historicoLocacoes[i].nomeCliente,
                historicoLocacoes[i].idFilme,
                historicoLocacoes[i].tituloFilme,
                historicoLocacoes[i].diasLocacao,
                historicoLocacoes[i].valorTotal,
                historicoLocacoes[i].devolvido);
    }

    fclose(arquivo);
}

void carregarLocacoesCSV() {
    FILE *arquivo = fopen(ARQUIVO_LOCACOES, "r");
    char linha[200];
    struct Locacao l;

    totalLocacoes = 0;

    if (arquivo == NULL) {
        return; 
    }

    while (totalLocacoes < MAX_LOCACOES && fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%d;%d;%49[^;];%d;%49[^;];%d;%f;%d",
                   &l.idLocacao, &l.idCliente, l.nomeCliente,
                   &l.idFilme, l.tituloFilme,
                   &l.diasLocacao, &l.valorTotal, &l.devolvido) == 8) {
            historicoLocacoes[totalLocacoes] = l;
            totalLocacoes++;
        }
    }

    fclose(arquivo);
}

int buscarIndicePorId(int idLocacao) {
    int i;
    for (i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idLocacao == idLocacao) {
            return i;
        }
    }
    return -1;
}

int proximoIdLocacao() {
    int i, maior = 0;
    for (i = 0; i < totalLocacoes; i++) {
        if (historicoLocacoes[i].idLocacao > maior) {
            maior = historicoLocacoes[i].idLocacao;
        }
    }
    return maior + 1;
}

void exibirLocacao(int i) {
    printf("#%d | %s | %s | %d dia(s) | R$ %.2f | %s\n",
           historicoLocacoes[i].idLocacao,
           historicoLocacoes[i].nomeCliente,
           historicoLocacoes[i].tituloFilme,
           historicoLocacoes[i].diasLocacao,
           historicoLocacoes[i].valorTotal,
           historicoLocacoes[i].devolvido ? "Devolvido" : "Em aberto");
}

void liberarLocacao(int posicao) {
    int posCliente;

    ponteAjustarCopias(historicoLocacoes[posicao].idFilme, 1);

    posCliente = buscarIndiceClientePorId(historicoLocacoes[posicao].idCliente);
    if (posCliente != -1 && listaClientes[posCliente].locacoesAtivas > 0) {
        listaClientes[posCliente].locacoesAtivas--;
        salvarClientesCSV();
    }
}


void cadastrarLocacao() {
    struct Locacao nova;
    float diaria;
    int copias, posCliente;

    printf("\n--- REGISTRAR LOCACAO ---\n");
    if (totalLocacoes >= MAX_LOCACOES) {
        printf("[ERRO] Limite de locacoes atingido!\n");
        return;
    }

    
    printf("ID do cliente: ");
    nova.idCliente = lerInteiro();
    posCliente = buscarIndiceClientePorId(nova.idCliente);
    if (posCliente == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        return;
    }
    if (listaClientes[posCliente].multaPendente > 0) {
        printf("[ERRO] %s tem multa pendente de R$ %.2f!\n",
               listaClientes[posCliente].nome, listaClientes[posCliente].multaPendente);
        return;
    }
    strcpy(nova.nomeCliente, listaClientes[posCliente].nome);
    printf("Cliente: %s\n", nova.nomeCliente);

    
    printf("ID do filme: ");
    nova.idFilme = lerInteiro();
    if (!ponteBuscarFilme(nova.idFilme, nova.tituloFilme, &diaria, &copias)) {
        printf("[ERRO] Filme nao encontrado!\n");
        return;
    }
    if (copias <= 0) {
        printf("[ERRO] Nenhuma copia disponivel deste filme!\n");
        return;
    }
    printf("Filme: %s | Diaria: R$ %.2f\n", nova.tituloFilme, diaria);

    // 3) dias e valor
    printf("Quantidade de dias: ");
    nova.diasLocacao = lerInteiro();
    if (nova.diasLocacao <= 0) {
        printf("[ERRO] Quantidade de dias invalida!\n");
        return;
    }
    nova.valorTotal = nova.diasLocacao * diaria;   
    nova.idLocacao = proximoIdLocacao();
    nova.devolvido = 0;

    
    historicoLocacoes[totalLocacoes] = nova;
    totalLocacoes++;
    ponteAjustarCopias(nova.idFilme, -1);
    listaClientes[posCliente].locacoesAtivas++;
    salvarClientesCSV();
    salvarLocacoesCSV();

    printf("\nLocacao %d registrada! Total: R$ %.2f\n", nova.idLocacao, nova.valorTotal);
}

void listarLocacoes() {
    int i;

    printf("\n--- LOCACOES REGISTRADAS ---\n");
    if (totalLocacoes == 0) {
        printf("Nenhuma locacao registrada ainda.\n");
        return;
    }

    for (i = 0; i < totalLocacoes; i++) {
        exibirLocacao(i);
    }
}

itulo do filme
void buscarLocacao() {
    char termo[50];
    int i, encontradas = 0;

    printf("\n--- BUSCAR LOCACAO ---\n");
    printf("Digite parte do nome do cliente ou do titulo do filme: ");
    scanf(" %49[^\n]", termo);
    limparBuffer();

    for (i = 0; i < totalLocacoes; i++) {
        if (strstr(historicoLocacoes[i].nomeCliente, termo) != NULL ||
            strstr(historicoLocacoes[i].tituloFilme, termo) != NULL) {
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

    printf("\n--- REGISTRAR DEVOLUCAO ---\n");
    printf("ID da locacao: ");
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
    liberarLocacao(posicao);
    salvarLocacoesCSV();

    printf("\nDevolucao da locacao %d registrada!\n", id);
}


void editarLocacao() {
    int id, posicao, novosDias;
    float diaria;

    printf("\n--- EDITAR LOCACAO ---\n");
    printf("ID da locacao: ");
    id = lerInteiro();
    posicao = buscarIndicePorId(id);

    if (posicao == -1) {
        printf("[ERRO] Locacao nao encontrada!\n");
        return;
    }

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

    printf("\n--- REMOVER LOCACAO ---\n");
    printf("ID da locacao: ");
    id = lerInteiro();
    posicao = buscarIndicePorId(id);

    if (posicao == -1) {
        printf("[ERRO] Locacao nao encontrada!\n");
        return;
    }

    if (historicoLocacoes[posicao].devolvido == 0) {
        liberarLocacao(posicao);
    }

    
    for (i = posicao; i < totalLocacoes - 1; i++) {
        historicoLocacoes[i] = historicoLocacoes[i + 1];
    }
    totalLocacoes--;
    salvarLocacoesCSV();

    printf("\nLocacao %d removida!\n", id);
}


void relatorioResumoPorSituacao() {
    float resumo[2][2] = {{0, 0}, {0, 0}};
    int i, linha;

    for (i = 0; i < totalLocacoes; i++) {
        linha = historicoLocacoes[i].devolvido;   
        resumo[linha][0] += 1;
        resumo[linha][1] += historicoLocacoes[i].valorTotal;
    }

    printf("\n--- RESUMO POR SITUACAO ---\n");
    printf("Em aberto : %.0f locacao(oes) | R$ %.2f a receber\n", resumo[0][0], resumo[0][1]);
    printf("Devolvidas: %.0f locacao(oes) | R$ %.2f recebidos\n", resumo[1][0], resumo[1][1]);
    printf("Faturamento total: R$ %.2f\n", resumo[0][1] + resumo[1][1]);
}


void relatorioRankingFilmes() {
    struct ItemRanking ranking[MAX_LOCACOES];
    struct ItemRanking aux;
    int n = 0, i, j, achou;


    for (i = 0; i < totalLocacoes; i++) {
        achou = -1;
        for (j = 0; j < n; j++) {
            if (ranking[j].idFilme == historicoLocacoes[i].idFilme) {
                achou = j;
            }
        }

        if (achou == -1) {   
            ranking[n].idFilme = historicoLocacoes[i].idFilme;
            strcpy(ranking[n].titulo, historicoLocacoes[i].tituloFilme);
            ranking[n].quantidade = 1;
            n++;
        } else {             
            ranking[achou].quantidade++;
        }
    }

    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (ranking[j].quantidade < ranking[j + 1].quantidade) {
                aux = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = aux;
            }
        }
    }

    
    printf("\n--- RANKING: FILMES MAIS ALUGADOS ---\n");
    if (n == 0) {
        printf("Nenhuma locacao registrada ainda.\n");
    }
    for (i = 0; i < n; i++) {
        printf("%do | %s | %d locacao(oes)\n", i + 1, ranking[i].titulo, ranking[i].quantidade);
    }
}

void menuRelatorios() {
    int opcao;

    do {
        limparTela();
        printf("\n--- [RELATORIOS DE LOCACOES] ---\n");
        printf("1. Resumo por Situacao (Em aberto x Devolvidas)\n");
        printf("2. Ranking de Filmes Mais Alugados\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                relatorioResumoPorSituacao();
                pausar();
                break;
            case 2:
                relatorioRankingFilmes();
                pausar();
                break;
            case 0:
                printf("\nVoltando ao menu de locacoes...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                pausar();
        }
    } while (opcao != 0);
}

void moduloLocacoesRelatorios() {
    int opcao;

    do {
        limparTela();
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
                pausar();
                break;
            case 2:
                listarLocacoes();
                pausar();
                break;
            case 3:
                buscarLocacao();
                pausar();
                break;
            case 4:
                devolverLocacao();
                pausar();
                break;
            case 5:
                editarLocacao();
                pausar();
                break;
            case 6:
                removerLocacao();
                pausar();
                break;
            case 7:
                menuRelatorios();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                pausar();
        }
    } while (opcao != 0);
}

#endif
