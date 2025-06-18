#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar matriz de habilidade em Cone
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cone apontando para baixo (forma triangular)
            if (j >= (TAM_HABILIDADE/2 - i/2) && j <= (TAM_HABILIDADE/2 + i/2) && i <= TAM_HABILIDADE/2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em Cruz
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cruz com centro no meio
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em Octaedro
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Octaedro (losango)
            int distancia = abs(i - centro) + abs(j - centro);
            if (distancia <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int linha_centro, int coluna_centro) {
    int offset = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha_tab = linha_centro - offset + i;
            int coluna_tab = coluna_centro - offset + j;
            
            // Verifica se está dentro do tabuleiro
            if (linha_tab >= 0 && linha_tab < TAM_TABULEIRO && 
                coluna_tab >= 0 && coluna_tab < TAM_TABULEIRO) {
                
                // Aplica a habilidade apenas onde a matriz de habilidade tem 1
                if (habilidade[i][j] == 1) {
                    tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    // Inicializa o tabuleiro com água
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {AGUA};
    
    // Posiciona alguns navios para exemplo
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[2][5] = NAVIO;
    
    tabuleiro[5][7] = NAVIO;
    tabuleiro[6][7] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    
    // Cria e aplica habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);
    
    // Aplica habilidades em posições específicas
    aplicarHabilidade(tabuleiro, cone, 4, 4);      // Cone no centro
    aplicarHabilidade(tabuleiro, cruz, 2, 7);      // Cruz em um navio
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);  // Octaedro em outra posição
    
    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    return 0;
}
