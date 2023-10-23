#include <stdio.h>
#include <string.h>


struct Registro {
    char email[100];
    char senha[100];
};

//  add um novo registro
void incluirRegistro(FILE *arquivo) {
    struct Registro novoRegistro;

    printf("Digite o email: ");
    scanf("%s", novoRegistro.email);
    printf("Digite a senha: ");
    scanf("%s", novoRegistro.senha);

    // Grava o registro no arquivo com "email:" e "senha:" em linhas separadas
    fprintf(arquivo, "email: %s\nsenha: %s\n", novoRegistro.email, novoRegistro.senha);
    printf("Registro incluido com sucesso!\n");
}

//  excluir um registro
void excluirRegistro(FILE *arquivo) {
    char email[100];
    char senha[100];
    char temp[200];
    int encontrado = 0;

    printf("Digite o email do registro a ser excluido: ");
    scanf("%s", email);

    FILE *tempFile = fopen("temp.txt", "w");
    rewind(arquivo);

    while (fgets(temp, sizeof(temp), arquivo) != NULL) {
        if (strstr(temp, email) != NULL) {
            encontrado = 1;
        } else {
            fputs(temp, tempFile);
        }
    }

    fclose(arquivo);
    fclose(tempFile);

    remove("registros.txt");
    rename("temp.txt", "registros.txt");

    if (encontrado) {
        printf("Registro excluido com sucesso!\n");
    } else {
        printf("Registro nao encontrado.\n");
    }
}

//  gerar um relatório com todos os email
void gerarRelatorio(FILE *arquivo) {
    char line[200];

    rewind(arquivo);
    printf("Relatorio de Registros:\n");

    while (fgets(line, sizeof(line), arquivo) != NULL) {
        printf("%s", line);
    }
}

// o menu de inclusao de registro
void menuIncluir(FILE *arquivo) {
    int opcao;
    while (1) {
        printf("\nMenu Incluir:\n");
        printf("-------------------------------\n");
        printf("| 1. Adicionar registro\n");
        printf("| 2. Voltar\n");
        printf("-------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirRegistro(arquivo);
                break;
            case 2:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

//  menu de exclusao de registro
void menuExcluir(FILE *arquivo) {
    int opcao;
    while (1) {
        printf("\nMenu Excluir:\n");
        printf("-------------------------------\n");
        printf("| 1. Excluir registro\n");
        printf("| 2. Voltar\n");
        printf("-------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                excluirRegistro(arquivo);
                break;
            case 2:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

//  menu de geraçao de relatorio
void menuRelatorio(FILE *arquivo) {
    int opcao;
    while (1) {
        printf("\nMenu Relatorio:\n");
        printf("-------------------------------\n");
        printf("| 1. Gerar relatorio\n");
        printf("| 2. Voltar\n");
        printf("-------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerarRelatorio(arquivo);
                break;
            case 2:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

// Função para o menu principal
int menuPrincipal(FILE *arquivo) {
    int opcao;
    while (1) {
        printf("\nMenu Principal:\n");
        printf("-------------------------------\n");
        printf("| 1. Incluir registro\n");
        printf("| 2. Excluir registro\n");
        printf("| 3. Gerar relatorio\n");
        printf("| 4. Sair\n");
        printf("-------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuIncluir(arquivo);
                break;
            case 2:
                menuExcluir(arquivo);
                break;
            case 3:
                menuRelatorio(arquivo);
                break;
            case 4:
                return 1;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

int main() {
    FILE *arquivo;
    arquivo = fopen("registros.txt", "a+");

    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return 1;
    }

    int sair = 0;
    while (!sair) {
        sair = menuPrincipal(arquivo);
    }

    fclose(arquivo);
    return 0;
}

