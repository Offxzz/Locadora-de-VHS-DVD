# Locadora-de-VHS-DVD

Sistema de gestão para uma locadora de fitas VHS e DVDs, desenvolvido em linguagem C como projeto em grupo da disciplina **Algoritmos e Pensamento Computacional**.

O programa funciona no terminal e simula o dia a dia de uma locadora clássica: cadastro de clientes, catálogo de filmes, compra de mídias de fornecedores, locações, devoluções e relatórios. Os dados ficam em memória durante a execução e são gravados em arquivos `.csv`, então continuam disponíveis na próxima vez que o sistema for aberto.

##  Menu principal

Ao iniciar, o sistema carrega os dados salvos e exibe o menu com os módulos:

```
1. Módulo de Clientes
2. Módulo de Filmes / Catálogo
3. Módulo de Compras / Fornecedores
4. Módulo de Locações e Relatórios
0. Encerrar o Sistema
```

##  Funcionalidades

- **Clientes:** cadastro e gerenciamento de clientes
- **Filmes / Catálogo:** cadastro e consulta dos títulos disponíveis na locadora
- **Compras / Fornecedores:** aquisição de novas mídias (VHS/DVD) de fornecedores
- **Locações e Relatórios:** registro de locações e devoluções, com relatórios sobre a locadora
- **Persistência:** os dados são carregados automaticamente ao abrir o sistema e gravados em arquivos `.csv`

##  Módulos e responsáveis

Cada módulo foi desenvolvido por um integrante e é integrado pelo `main.c`.

| Módulo | Responsável |
|---|---|
| Clientes | Leonardo Bartoszewski Pinheiro |
| Filmes / Catálogo | Matheus Souza dos Santos |
| Compras / Fornecedores | Jaison Alan |
| Locações e Relatórios | Ian Leuche |

## 📂 Estrutura do projeto

```
├── projeto/
│   ├── clientes - Leonardo Bartoszewski Pinheiro/
│   ├── compras - Jaison Alan/
│   ├── filmes - Matheus Souza dos Santos/
│   ├── locacoes - Ian Leuche/
│   ├── main.c         # Menu principal, carrega os dados e chama os módulos
│   ├── utils.h        # Funções utilitárias compartilhadas
│   ├── filmes.csv     # Dados do catálogo
│   └── locacoes.csv   # Dados das locações
└── README.md
```

##  Como compilar e executar

```bash
cd projeto
gcc main.c -o locadora
./locadora
```

> **Observação:** o projeto foi desenvolvido para **Windows** (usa `setlocale(LC_CTYPE, "Portuguese")` para os acentos). No Windows, o executável será `locadora.exe`. Execute sempre de dentro da pasta `projeto/`, para que os arquivos `.csv` sejam encontrados.

##  Tecnologias

- Linguagem C
- Programação modular, com um módulo por integrante
- Funções utilitárias compartilhadas em `utils.h`
- Persistência de dados em arquivos `.csv`
