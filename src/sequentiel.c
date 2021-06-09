   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Consts

unsigned const int GRID_SIZE = 15 ;

unsigned const int NUM_IT = 9 ;


// Variables

int gridInitial[15][15];

int gridTemp[15][15];

int grid[15][15]=
{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


unsigned const int it[9] = {50, 100 , 200 , 500 , 1000, 5000, 10000, 50000 , 100000};

// Inistialiser la grille aléatoirement
void initGrid(){
    for (size_t y = 0; y < GRID_SIZE; y++)
        for (size_t x = 0; x < GRID_SIZE; x++)
            gridInitial[y][x] = rand() % 2;
}

// grid <- gridInitial
void copyInit(){
    for (size_t y=0; y<GRID_SIZE; y++)
        for (size_t x=0; x<GRID_SIZE; x++)
            grid[y][x] = gridInitial[y][x];
}

// Retourner les cases vivantes d'une case
int getAdjCellsNum(int x, int y){
    int result = 0;
    if (x == GRID_SIZE) x = x - 1;
    if (y == GRID_SIZE) y = y - 1;
    if (x == 0) x = x + 1;
    if (y == 0) y = y + 1;
    result = grid[y+1][x] + grid[y+1][x-1] + grid[y+1][x+1] + grid[y][x+1] + grid[y][x-1] + grid[y-1][x-1] + grid[y-1][x] + grid[y-1][x+1];
    return result;
}

// Mettre à jour une case
int updateCell(int x, int y, int val){
    int result = 0;
    if (val == 1){
        if ((getAdjCellsNum(x,y) == 2) || (getAdjCellsNum(x,y) == 3)) result = 1;
        if ((getAdjCellsNum(x,y) > 3) || (getAdjCellsNum(x,y) < 2))  result = 0;
    }
    else if (getAdjCellsNum(x,y) >= 3) result = 1;
    return result;
}

// Afficher la grille
void printGrid(){
    for (size_t y = 0; y < GRID_SIZE;y++) {
        for (size_t x = 0; x < GRID_SIZE; x++){
            int cell = grid[y][x];
            char c = '0';
            if(cell == 1) c = 'X';
            printf("(%c)", c);
        }
        printf("\n");
    }
    printf("\n");
}

// Boucle principale du programme séquentiel
double startGame(int itr)
{
    clock_t start, end;
    start = clock();
    
    for (size_t i=0; i< itr; i++) { 
        for (size_t y=0; y<GRID_SIZE; y++)
            for (size_t x=0; x<GRID_SIZE; x++)
                gridTemp[y][x] = updateCell(x, y, grid[x][y]);


        for (size_t y=1; y< GRID_SIZE;y++) {
            for (size_t x=0; x<GRID_SIZE; x++) {
                grid[y][x] = gridTemp[y][x];
            }
        }
    }
    end = clock();
    double time = ((double) (end - start)) / CLOCKS_PER_SEC;
    return  (double)time;
} 


// main
int main(){
    FILE* outputFile = NULL;
    outputFile = fopen("output.txt", "w+");
    
    if (outputFile != NULL)
    {
        initGrid();
        copyInit();
        printGrid();

        fprintf(outputFile, "Itérations   Temps \n");
        printf("-----------------------------\n");
        
        for (size_t i=0; i < 9; i++){
            double exec_time = startGame(it[i]);
            printf("%6d itérations : %f (s)\n", it[i], exec_time);
            fprintf(outputFile, "%10d   %lf \n", it[i], exec_time);
        }
        fclose(outputFile);
    }
    else printf("Fichier output.txt introuvable");
    printf("\nFin de l'exécution \n");
    return 0;
}
