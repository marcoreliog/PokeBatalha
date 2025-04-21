// Jogo de Batalha Pokémon com Gameplay Aprimorado
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

typedef struct {
    char nome[20];
    int ataque;
    int defesa;
    int vida;
    char tipo[20];
    int especial_usado;
    int xp;
    int nivel;
} Pokemon;

typedef struct {
    int pocao;
    int super_pocao;
    int reviver;
} Inventario;

int def_tipo(char *tipo);
double calcular_o_dano(Pokemon ataque, Pokemon defesa);
void print_barra_de_vida(int vida, int max_vida);
void mostrar_menu();
void limpar_tela();
void usar_item(Inventario *inv, Pokemon *poke);

void print_barra_de_vida(int vida, int max_vida) {
    int blocos = (vida * 10) / max_vida;
    double porcentagem = (double)vida / max_vida;

    const char *cor;
    if (porcentagem > 0.5)
        cor = GREEN;
    else if (porcentagem > 0.2)
        cor = YELLOW;
    else
        cor = RED;

    printf("[");
    for (int i = 0; i < 10; i++) {
        if (i < blocos) printf("%s#", cor);
        else printf(" ");
    }
    printf(RESET "] %d HP\n", vida > 0 ? vida : 0);
}

void mostrar_menu() {
    printf(CYAN "============================\n");
    printf("   Bem-vindo ao PokeBatalha!\n");
    printf("============================" RESET "\n\n");

    printf(YELLOW "[1]" RESET " Iniciar Batalha\n");
    printf(YELLOW "[2]" RESET " Sair\n\n");
    printf("Escolha uma opcao: ");
}

void limpar_tela() {
    printf("\033[H\033[J");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    mostrar_menu();
    scanf("%d", &opcao);
    if (opcao != 1) {
        printf("Saindo...\n");
        return 0;
    }

    limpar_tela();
    FILE *arquivo = fopen("C:/Projetos/tp.pds/teste.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int N, M;
    fscanf(arquivo, "%d %d", &N, &M);
    Pokemon j1[100], j2[100];
    for (int i = 0; i < N; i++) {
        fscanf(arquivo, "%s %d %d %d %s", j1[i].nome, &j1[i].ataque, &j1[i].defesa, &j1[i].vida, j1[i].tipo);
        j1[i].especial_usado = 0;
        j1[i].xp = 0;
        j1[i].nivel = 1;
    }
    for (int j = 0; j < M; j++) {
        fscanf(arquivo, "%s %d %d %d %s", j2[j].nome, &j2[j].ataque, &j2[j].defesa, &j2[j].vida, j2[j].tipo);
        j2[j].especial_usado = 0;
        j2[j].xp = 0;
        j2[j].nivel = 1;
    }
    fclose(arquivo);

    Inventario inv1 = {2, 1, 1};
    Inventario inv2 = {2, 1, 1};

    int vivo_jogador1 = N, vivo_jogador2 = M;
    int i = 0, j = 0, turno = 1;

    printf("\n Batalha Comeca! \n\n");
    sleep(1);

    while (vivo_jogador1 > 0 && vivo_jogador2 > 0) {
        Pokemon *atacante = (turno == 1) ? &j1[i] : &j2[j];
        Pokemon *defensor = (turno == 1) ? &j2[j] : &j1[i];
        Inventario *inv_atual = (turno == 1) ? &inv1 : &inv2;

        printf(MAGENTA "\n%s (%s) [Nv. %d]\n", atacante->nome, atacante->tipo, atacante->nivel);
        print_barra_de_vida(atacante->vida, 20);

        if (turno == 1) {
            printf("\n[1] Atacar\n[2] Usar Item\n[3] Trocar Pokemon\nEscolha sua acao: ");
            int acao;
            scanf("%d", &acao);

            if (acao == 1) {
                double mult = calcular_o_dano(*atacante, *defensor);
                int dano = atacante->ataque * mult - defensor->defesa;
                if (dano <= 0) dano = 1;
                defensor->vida -= dano;
                printf(RED "Dano causado: %d\n" RESET, dano);
            } else if (acao == 2) {
                usar_item(inv_atual, atacante);
                turno = 2;
                continue;
            } else if (acao == 3) {
                // Troca de Pokemon futura
                turno = 2;
                continue;
            }
        } else {
            if (defensor->vida <= 8 && inv2.pocao > 0) {
                defensor->vida += 10;
                if (defensor->vida > 20) defensor->vida = 20;
                inv2.pocao--;
                printf(YELLOW "Jogador 2 usou uma Pocao!\n" RESET);
            } else {
                double mult = calcular_o_dano(*atacante, *defensor);
                int dano = atacante->ataque * mult - defensor->defesa;
                if (dano <= 0) dano = 1;
                defensor->vida -= dano;
                printf(RED "Dano causado: %d\n" RESET, dano);
            }
        }

        print_barra_de_vida(defensor->vida > 0 ? defensor->vida : 0, 20);

        if (defensor->vida <= 0) {
            printf(GREEN "%s foi derrotado!\n" RESET, defensor->nome);
            if (turno == 1) {
                j++;
                vivo_jogador2--;
            } else {
                i++;
                vivo_jogador1--;
            }
            sleep(1);
        }

        turno = (turno == 1) ? 2 : 1;
    }

    printf("\n\U0001F389 Resultado Final:\n");
    if (vivo_jogador1 > 0)
        printf(GREEN "Jogador 1 venceu!\n" RESET);
    else if (vivo_jogador2 > 0)
        printf(RED "Jogador 2 venceu!\n" RESET);
    else
        printf("Empate!\n");

    return 0;
}

void usar_item(Inventario *inv, Pokemon *poke) {
    int escolha;
    printf("Itens disponiveis:\n");
    printf("[1] Pocao (%d)\n[2] Super Pocao (%d)\n[3] Reviver (%d)\nEscolha: ", inv->pocao, inv->super_pocao, inv->reviver);
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            if (inv->pocao > 0) {
                poke->vida += 10;
                if (poke->vida > 20) poke->vida = 20;
                inv->pocao--;
                printf(GREEN "Voce usou uma Pocao!\n" RESET);
            }
            break;
        case 2:
            if (inv->super_pocao > 0) {
                poke->vida = 20;
                inv->super_pocao--;
                printf(GREEN "Voce usou uma Super Pocao!\n" RESET);
            }
            break;
        case 3:
            if (inv->reviver > 0 && poke->vida <= 0) {
                poke->vida = 10;
                inv->reviver--;
                printf(GREEN "Voce usou um Reviver!\n" RESET);
            }
            break;
        default:
            printf("Item invalido ou esgotado.\n");
    }
}

int def_tipo(char *tipo) {
    return (strcmp(tipo, "fogo") == 0 || strcmp(tipo, "agua") == 0 || strcmp(tipo, "pedra") == 0 ||
            strcmp(tipo, "gelo") == 0 || strcmp(tipo, "eletrico") == 0);
}

double calcular_o_dano(Pokemon ataque, Pokemon defesa) {
    double mult = 1.0;
    if (strcmp(ataque.tipo, "eletrico") == 0) {
        if (strcmp(defesa.tipo, "agua") == 0) mult = 1.2;
        else if (strcmp(defesa.tipo, "pedra") == 0) mult = 0.8;
    } else if (strcmp(ataque.tipo, "agua") == 0) {
        if (strcmp(defesa.tipo, "fogo") == 0) mult = 1.2;
        else if (strcmp(defesa.tipo, "eletrico") == 0) mult = 0.8;
    } else if (strcmp(ataque.tipo, "fogo") == 0) {
        if (strcmp(defesa.tipo, "gelo") == 0) mult = 1.2;
        else if (strcmp(defesa.tipo, "agua") == 0) mult = 0.8;
    } else if (strcmp(ataque.tipo, "gelo") == 0) {
        if (strcmp(defesa.tipo, "pedra") == 0) mult = 1.2;
        else if (strcmp(defesa.tipo, "fogo") == 0) mult = 0.8;
    } else if (strcmp(ataque.tipo, "pedra") == 0) {
        if (strcmp(defesa.tipo, "eletrico") == 0) mult = 1.2;
        else if (strcmp(defesa.tipo, "gelo") == 0) mult = 0.8;
    }
    return mult;
}