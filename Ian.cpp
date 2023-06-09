#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define GRID_SIZE 10
#define NUM_WORDS 3


int i, row, col;


char randomchar() {
    return 'A' + rand() % 26;  // Gera uma letra maiúscula aleatória de A a Z
}

void fillInBoard(char board[GRID_SIZE][GRID_SIZE], const char* word) {
    int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};  // Direções: direita, esquerda, baixo, cima, diagonal inferior direita, diagonal superior direita, diagonal inferior esquerda, diagonal superior esquerda
    int randomDirection = rand() % 8;  // Seleciona uma direção aleatória
    int wordLen = strlen(word);

    // Tenta encontrar uma posição válida para a palavra na board
    while (1) {
        // Gera uma posição inicial aleatória
        int rowGeneration = rand() % GRID_SIZE;
        int colGeneration = rand() % GRID_SIZE;

        // Verifica se a palavra pode ser inserida na posição inicial
        if (colGeneration + directions[randomDirection][1] * (wordLen - 1) >= 0 && colGeneration + directions[randomDirection][1] * (wordLen - 1) < GRID_SIZE &&
            rowGeneration + directions[randomDirection][0] * (wordLen - 1) >= 0 && rowGeneration + directions[randomDirection][0] * (wordLen - 1) < GRID_SIZE) {

            // Verifica se a posição está livre na board
            int freePosition = 1;
            for (int i = 0; i < wordLen; i++) {
                if (board[rowGeneration + directions[randomDirection][0] * i][colGeneration + directions[randomDirection][1] * i] != ' ') {
                    freePosition = 0;
                    break;
                }
            }

            // Se a posição estiver livre, preenche a palavra na board
            if (freePosition) {
                for (int i = 0; i < wordLen; i++) {
                    board[rowGeneration + directions[randomDirection][0] * i][colGeneration + directions[randomDirection][1] * i] = word[i];
                }
                break;
            }
        }
    }
}

void fillInSpaces(char board[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = randomchar();
            }
        }
    }
}

void printGrid(char board[GRID_SIZE][GRID_SIZE]) {
    printf("\n\n \t\t\t\t\t\t\t\t0  1  2  3  4  5  6  7  8  9\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("\n\t\t\t\t\t\t\t\t");
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c  ", board[i][j]);
            if (j == GRID_SIZE - 1) {
                printf(" %d", i);
            }
        }
        printf("\n");
    }
}




int searchHorizontal(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for ( row = 0; row < GRID_SIZE; row++) {
        for ( col = 0; col <= GRID_SIZE - len; col++) {
            for (i = 0; i < len; i++) {
                if (board[row][col + i] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchHorizontalReverse(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = GRID_SIZE - 1; col >= len - 1; col--) {
            for (i = 0; i < len; i++) {
                if (board[row][col - i] != word[i])
                    break;
            }
           if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchVertical(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (col = 0; col < GRID_SIZE; col++) {
        for ( row = 0; row <= GRID_SIZE - len; row++) {
            for (i = 0; i < len; i++) {
                if (board[row + i][col] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchVerticalReverse(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (col = 0; col < GRID_SIZE; col++) {
        for (row = GRID_SIZE - 1; row >= len - 1; row--) {
            for (i = 0; i < len; i++) {
                if (board[row - i][col] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchDiagonalDesc(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (row = 0; row <= GRID_SIZE - len; row++) {
        for (col = 0; col <= GRID_SIZE - len; col++) {
            for (i = 0; i < len; i++) {
                if (board[row + i][col + i] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchDiagonalDescReverse(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (row = GRID_SIZE - 1; row >= len - 1; row--) {
        for (col = GRID_SIZE - 1; col >= len - 1; col--) {
            for (i = 0; i < len; i++) {
                if (board[row - i][col - i] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchDiagonalAsc(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (row = len - 1; row < GRID_SIZE; row++) {
        for (col = 0; col <= GRID_SIZE - len; col++) {
            for (i = 0; i < len; i++) {
                if (board[row - i][col + i] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
        }
    }
    return 0;
}

int searchDiagonalAscReverse(const char board[GRID_SIZE][GRID_SIZE], const char* word, int *pointerRow,int *pointerCol) {
    int len = strlen(word);
    for (row = GRID_SIZE - len; row >= 0; row--) {
        for (col = GRID_SIZE - 1; col >= len - 1; col--) {
            for (i = 0; i < len; i++) {
                if (board[row + i][col - i] != word[i])
                    break;
            }
            if (i == len){
                *pointerCol = col;
                *pointerRow = row;
                return 1;
            }
                
        }
    }
    return 0;
}

void searchWord(const char board[GRID_SIZE][GRID_SIZE], const char* word,int *pointerChek,int *pointerRow,int *pointerCol) {
    if (searchHorizontal(board, word, pointerRow, pointerCol)) {
        printf("Palavra encontrada na posicao (%d, %d) - Horizontal\n", *pointerRow, *pointerCol);
        (*pointerChek)--; 
    }
    else if (searchHorizontalReverse(board, word, pointerRow, pointerCol)) {
        printf("Palavra encontrada na posicao (%d, %d) - Horizontal Reversa\n", *pointerRow, *pointerCol);
        (*pointerChek)--; 
    }
    else if (searchVertical(board, word, pointerRow, pointerCol)) {
       printf("Palavra encontrada na posicao (%d, %d) - Vertical\n", *pointerRow, *pointerCol);
       (*pointerChek)--;  
    }
    else if (searchVerticalReverse(board, word, pointerRow, pointerCol)) {
       printf("Palavra encontrada na posicao (%d, %d) - Vertical Reversa\n", *pointerRow, *pointerCol);
       (*pointerChek)--;  
    }
    else if (searchDiagonalDesc(board, word, pointerRow, pointerCol)) {
       printf("Palavra encontrada na posicao (%d, %d) - Diagonal Descendente\n", *pointerRow, *pointerCol);
       (*pointerChek)--;
    } 
    else if (searchDiagonalDescReverse(board, word, pointerRow, pointerCol)) {
        printf("Palavra encontrada na posicao (%d, %d) - Diagonal Descendente Reversa\n", *pointerRow, *pointerCol);
        (*pointerChek)--; 
    }
    else if (searchDiagonalAsc(board, word, pointerRow, pointerCol)){
        printf("Palavra encontrada na posicao (%d, %d) - Diagonal Ascendente\n", *pointerRow, *pointerCol);
        (*pointerChek)--;
    }
    else if (searchDiagonalAscReverse(board, word, pointerRow, pointerCol)) {
        printf("Palavra encontrada na posicao (%d, %d) - Diagonal Ascendente Reversa\n", *pointerRow, *pointerCol);
        (*pointerChek)--;
    }
    else
        printf("Palavra nao encontrada.\n");
}

void searchWords(const char board[GRID_SIZE][GRID_SIZE], const char* words[], int numWords, int *pointerChek, int *pointerRow, int *pointerCol) {
    for (int i = 0; i < numWords; i++) {
        const char* word = words[i];
        searchWord(board, word, pointerChek, pointerRow, pointerCol);
        
        system("cls");
    }
}

int tema(){
    int choice;
    
    printf("\033[31mLEMBRETE:\n");
    printf("----------------------\n");
    printf("Cada tema contem 3 palavras.\n");
    printf("----------------------\n");
    printf("\033[0m"); 

    printf("Escolha um tema:\n");
    printf("0 - Animais\n");
    printf("1 - Cores\n");
    printf("2 - Comida\n");
    printf("Opcao: ");
    scanf("%d", &choice);
    
    system("cls");

    switch (choice) {
        
        case 0:
            printf("Tema: Animais\n");
            break;
            
        case 1:
            printf("Tema: Cores\n");
            break;
            
        case 2:
            printf("Tema: Comida\n");
            break;
            
        default:
            printf("Opcao invalida\n");
            exit(1);
            break;
    }

    return choice;
}

void game(){
    
    int choice;
    int check;
    int rowFound;
    int colFound;

    int *pointerChek = &check;
    int *pointerRow = &rowFound;
    int *pointerCol = &colFound;
    
    choice = tema();
    
    char findword[50];

    char board[GRID_SIZE][GRID_SIZE];
    

    const char* words0[] = {"GATO", "RATO", "SAPO"};
    const char* words1[] = {"AZUL", "ROSA", "ROXO"};
    const char* words2[] = {"SOPA", "ARROZ", "PIZZA"};

    const char* words[NUM_WORDS];
    
    if(choice == 0){
        for (int i = 0; i < NUM_WORDS; i++) {
            words[i] = words0[i];
        }   
    }
    else if(choice == 1){
        for (int i = 0; i < NUM_WORDS; i++) {
            words[i] = words1[i];
        }  
    }
    else if(choice  == 2){
        for (int i = 0; i < NUM_WORDS; i++) {
            words[i] = words2[i];
        }  
    }
    else
        exit(1);

    int numWords = sizeof(words) / sizeof(words[0]);

    do{
        *pointerChek = 3;
        
        memset(board, ' ', sizeof(board));
        
        for (int i = 0; i < NUM_WORDS; i++) {
            fillInBoard(board, words[i]);
        }

        fillInSpaces(board);

        searchWords(board, words, numWords,pointerChek, pointerRow, pointerCol);

    }while((*pointerChek) != 0);

    printGrid(board);

    int foundWords = 0;
    int totalWords = numWords;


    do {
        printf("\nDigite a palavra encontrada: ");
        scanf("%s", findword);
        
        for (int i = 0; findword[i] != '\0'; i++) {
            findword[i] = toupper(findword[i]);
        }

        int test = 0;

        for (int i = 0; i < numWords; i++) {
            if (strcmp(findword, words[i]) == 0) {
                printf("\nParabens! Voce encontrou a palavra: %s\n", findword);
                *pointerCol = 0;
                *pointerRow = 0;
                searchWord(board,words[i],pointerChek, pointerRow, pointerCol);
                foundWords++;

                // Marcar a palavra encontrada como vazia para não ser encontrada novamente
                words[i] = "";
                test = 1;
                break;
            }
                
        }

        if (foundWords == totalWords) {
            printf("Voce encontrou todas as palavras!\n");
            break;
        }

        if (!test){ // Se a palavra não foi encontrada
            printf("Palavra nao encontrada. Tente novamente.\n");
        }

        
    } while (1);

    
    
}

int print_menu() {
    int choice;

    printf("======== JOGO ========\n");
    printf("1. Jogar\n");
    printf("2. Sair\n");
    printf("=======================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
    system ("cls");
    return choice;

}

void handle_choice(int choice) {
    switch (choice) {
        case 1:
            game(); 
            break;

        case 2:
            printf("Opcao escolhida: Sair\n");
            exit(1);
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
    }
}

int main() {
    setlocale(LC_ALL,"portuguese");
    
    srand(time(NULL));

    int choice;

    do{   
        choice = print_menu();
        
        handle_choice(choice);

        system("pause");

        system("cls");

    } while(choice);

    return 0;
}

