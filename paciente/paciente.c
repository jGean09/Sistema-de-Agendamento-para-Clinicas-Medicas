#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
#include "paciente.h"
#include "../validacoes/validacoes.h"
typedef struct paciente Paciente;


void modulo_paciente(void){
    int opcao;
    do{
        opcao = tela_paciente();
        switch (opcao) {
        case 1:
            tela_cadastrar_paciente();
            break;
        case 2:
            tela_ver_paciente();
            break;
        case 3:
            tela_atualizar_paciente();
            break;
        case 4:
            tela_deletar_paciente();
            break;
        case 0:
            break;
        default:
            printf("Valor invalido");
            break;
        }
    }while(opcao != 0);
}

//PACIENTE
int tela_paciente(void) {
    int opcao;
    system("clear||cls");
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          ------ PACIENTE ------                             ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                             ║\n");
    printf("║                          1. Cadastrar Paciente                              ║\n");
    printf("║                          2. Pesquisar Paciente                              ║\n");
    printf("║                          3. Atualizar Paciente                              ║\n");
    printf("║                          4. Remover Paciente                                ║\n");
    printf("║                                                                             ║\n");
    printf("║                          0. Cancelar e sair                                 ║\n");
    printf("║                                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════╝\n");
    printf("║  ↪Escolha a opção desejada: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

// ##########################
// ##      Cadastrar       ##
// ##########################
void tela_cadastrar_paciente() {
    Paciente *paciente1 = malloc(sizeof(Paciente));
    system("clear||cls");
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           CADASTRAR PACIENTE                                ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════╣\n");
    solicitar_nome(paciente1->nome);
    solicitar_CPF(paciente1->CPF);
    solicitar_data_nascimento(paciente1->data_nascimento);
    solicitar_celular(paciente1->celular);
    solicitar_email(paciente1->email);
    solicitar_endereco(paciente1->endereco);
    salvar_paciente(paciente1);
    printf("\n");
    printf("CLIENTE cadastrado com sucesso.");
    printf("\n");
    printf("Pressione a tecla <ENTER> para continuar...\n");
    getchar();
}


// ##########################
// ##      Pesquisar       ##
// ##########################
void tela_ver_paciente() {
    char CPF_test[13];
    system("clear||cls");
    printf("\n");
    printf("↪ Informe o CPF do paciente que deseja ver informações: ");
    scanf("%s",CPF_test);
    buscar_paciente(CPF_test);
    getchar();
    printf("\n");
    printf("Pressione a tecla <ENTER> para continuar...\n");
    getchar();
}

void buscar_paciente(const char *cpf_busca) {
    FILE *fp = fopen("paciente/paciente.dat", "rb"); 
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    Paciente paciente;
    int encontrado = 0;
    while (fread(&paciente, sizeof(Paciente), 1, fp)) {
        if (strcmp(paciente.CPF, cpf_busca) == 0) {
            exibir_paciente(paciente);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Médico com CRM %s não encontrado.\n", cpf_busca);
    }
    fclose(fp);
}

void exibir_paciente(Paciente paciente){
    printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             EXIBIR PACIENTE                                 ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                             ║\n");
    printf("║    Nome: %-67s║\n", paciente.nome);
    printf("║    CPF: %-68s║\n", paciente.CPF);
    printf("║    Data de nascimento: %-53s║\n", paciente.data_nascimento);
    printf("║    Celular: %-64s║\n", paciente.celular);
    printf("║    Email: %-66s║\n", paciente.email);
    printf("║    Endereço: %-63s║\n", paciente.endereco);
    printf("║                                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════╝\n");
}


// ##########################
// ##       Atualizar      ##
// ##########################
void tela_atualizar_paciente() {
    char CPF_test[13];
    system("clear||cls");
    printf("\n");
    printf("↪ Informe o CPF do paciente que deseja atualizar:");
    scanf("%s",CPF_test);

    if (verificar_CPF_existente(CPF_test)) {
    alterar_paciente(CPF_test);
    } 
    else {
        printf("Paciente com CPF %s não encontrado.\n", CPF_test);
    }
    getchar();
    printf("\n");
    printf("Pressione a tecla <ENTER> para continuar...\n");
    getchar();
}

void alterar_paciente(const char *cpf_busca) {
    FILE *fp = fopen("paciente/paciente.dat", "rb+"); // Abrir para leitura e escrita binária
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    Paciente paciente;
    int encontrado = 0;
    while (fread(&paciente, sizeof(Paciente), 1, fp)) {
        if (strcmp(paciente.CPF, cpf_busca) == 0) {
            exibir_paciente(paciente);
            printf("\n");
            printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║                         ALTERAR DADOS DO PACIENTE                           ║\n");
            printf("╠═════════════════════════════════════════════════════════════════════════════╣\n");
            printf("║                                                                             ║\n");
            solicitar_nome(paciente.nome);
            solicitar_CPF(paciente.CPF);
            solicitar_data_nascimento(paciente.data_nascimento);
            solicitar_celular(paciente.celular);
            solicitar_email(paciente.email);
            solicitar_endereco(paciente.endereco);

            fseek(fp, -sizeof(Paciente), SEEK_CUR);
            fwrite(&paciente, sizeof(Paciente), 1, fp); // Sobrescreve o registro
            printf("\n╠══════ Dados do paciente atualizados com sucesso! ══════╣\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Paciente com CPF %s não encontrado.\n", cpf_busca);
    }
    fclose(fp);
}


// ##########################
// ##        Deletar       ##
// ##########################
void tela_deletar_paciente() {
    system("clear||cls");
    printf("\n");
    printf("╔═════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                            DELETAR PACIENTE                                 ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║  ↪Informe o CPF do paciente que deseja deletar:                             ║\n");
    printf("║                                                                             ║\n");
    printf("╚═════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Pressione a tecla <ENTER> para continuar...\n");
    getchar();
}


// ##########################
// ##    Funçoes de Ler    ##
// ##########################
void solicitar_nome(char *nome) {
    int valido = 0; // Inicializando como não válido
    do {
        printf("║ ↪Nome Completo:");
        scanf(" %[^\n]", nome);
        getchar();
        if (validarNome(nome)==1) { 
            valido = 1; // Marca como válido
        } else {
            printf("==⊳ Entrada inválida, digite apenas letras e espaços                          ║\n");
            printf("==⊳ DIGITE ENTER para continuar                                            ═══╝\n");
            valido = 0; // Marca como não válido
            while (getchar() != '\n'); // Limpar o buffer
        }
    } while (!valido); // até ser valido
}

void solicitar_CPF(char *CPF){
    int valido = 0; // Inicializando como não válido
    do {
        printf("║ ↪CPF:");
        scanf(" %[^\n]", CPF); 
        getchar();
        if (validar_cpf(CPF)==1) { 
            valido = 1; // Marca como válido
        } else {
            printf("==⊳ Entrada inválida, digite apenas números                                   ║\n");
            printf("==⊳ DIGITE ENTER para continuar                                            ═══╝\n");
            valido = 0; // Marca como não válido
            while (getchar() != '\n'); // Limpar o buffer
        }
    } while (!valido); // até ser valido
}

void solicitar_data_nascimento(char *data_nascimento){
    int valido = 0; // Inicializando como não válido
    do {
        printf("║ ↪Data de Nascimento:");
        scanf(" %[^\n]", data_nascimento); 
        getchar();
        if (validar_data(data_nascimento)==1) { 
            valido = 1; // Marca como válido
        } else {
            printf("==⊳ Entrada inválida, digite apenas números                                   ║\n");
            printf("==⊳ DIGITE ENTER para continuar                                            ═══╝\n");
            valido = 0; // Marca como não válido
            while (getchar() != '\n'); // Limpar o buffer
        }
    } while (!valido); // até ser valido
}

void solicitar_celular(char *celular){
    int valido = 0; // Inicializando como não válido
    do {
        printf("║ ↪Celular:");
        scanf(" %[^\n]", celular); 
        getchar();
        if (validar_celular(celular)==1) { 
            valido = 1; // Marca como válido
        } else {
            printf("==⊳ Entrada inválida, digite apenas números                                   ║\n");
            printf("==⊳ DIGITE ENTER para continuar                                            ═══╝\n");
            valido = 0; // Marca como não válido
            while (getchar() != '\n'); // Limpar o buffer
        }
    } while (!valido); // até ser valido
}

void solicitar_email(char *email){
    int valido = 0; // Inicializando como não válido
    do {
        printf("║ ↪Email:");
        scanf(" %[^\n]", email); 
        getchar();
        if (validar_email(email)==1) { 
            valido = 1; // Marca como válido
        } else {
            printf("==⊳ Entrada inválida, Digite o Email correto                                  ║\n");
            printf("==⊳ DIGITE ENTER para continuar                                            ═══╝\n");
            valido = 0; // Marca como não válido
            while (getchar() != '\n'); // Limpar o buffer
        }
    } while (!valido); // até ser valido
}

void solicitar_endereco(char *endereco){
    int valido = 0; // Inicializando como não válido
    do {
        printf("║ ↪Endereço:");
        scanf(" %[^\n]", endereco);
        printf("═══════════════════════════════════════════════════════════════════════════════\n");
        getchar();
        if (validar_endereco(endereco)==1) { 
            valido = 1; // Marca como válido
        } else {
            printf("==⊳ Entrada inválida, Digite o endereço correto                               ║\n");
            printf("==⊳ DIGITE ENTER para continuar                                            ═══╝\n");
            valido = 0; // Marca como não válido
            while (getchar() != '\n'); // Limpar o buffer
        }
    } while (!valido); // até ser valido
}


// #############################
// ##         Arquivo         ##
// #############################

void salvar_paciente(Paciente *paciente1) {
    FILE *fp = fopen("paciente/paciente.dat", "ab"); // Abrir para adicionar binário
    if (fp == NULL) {
        printf("Erro na Abertura");
        exit(1);
    }
    fwrite(paciente1, sizeof(Paciente), 1, fp); // Grava o conteúdo do struct
    fclose(fp);
    free(paciente1);
}


int verificar_CPF_existente(const char *cpf_busca) {
    FILE *fp = fopen("paciente/paciente.dat", "rb"); 
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }
    Paciente paciente;
    while (fread(&paciente, sizeof(Paciente), 1, fp)) {
        if (strcmp(paciente.CPF, cpf_busca) == 0) {
            fclose(fp);
            return 1;  
        }
    }
    fclose(fp); 
    return 0;  
}


