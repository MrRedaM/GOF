   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Consts

unsigned const int GRID_SIZE = 15 ;

unsigned const int NUM_IT = 9 ;


// Variables

int * gridInitial;

int * gridTemp;

int * grid;

#define grid( _i_, _j_ ) grid[ GRID_SIZE * (_j_) + (_i_) ]
#define gridInitial( _i_, _j_ ) gridInitial[ GRID_SIZE * (_j_) + (_i_) ]
#define gridTemp( _i_, _j_ ) gridTemp[ GRID_SIZE * (_j_) + (_i_) ]

unsigned const int it[9] = {50, 100 , 200 , 500 , 1000, 5000, 10000, 50000 , 100000};

// Inistialiser la grille aléatoirement
void initGrid(){
    for (size_t y = 0; y < GRID_SIZE; y++)
        for (size_t x = 0; x < GRID_SIZE; x++)
            gridInitial(y,x) = 0; //rand() % 2;
}

// grid <- gridInitial
void copyInit(){
    for (size_t y=0; y<GRID_SIZE; y++)
        for (size_t x=0; x<GRID_SIZE; x++)
            grid(y,x) = gridInitial(y,x);
}

// Retourner les cases vivantes d'une case
int getAdjCellsNum(int x, int y){
    int result = 0;
    if (x == GRID_SIZE) return result;
    if (y == GRID_SIZE) return result;
    if (x == 0) return result;
    if (y == 0) return result;
    result = grid(y+1,x) + grid(y+1,x-1) + grid(y+1,x+1) + grid(y,x+1) + grid(y,x-1) + grid(y-1,x-1) + grid(y-1,x) + grid(y-1,x+1);
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
    for (size_t y = 1; y < GRID_SIZE - 1;y++) {
        for (size_t x = 1; x < GRID_SIZE - 1; x++){
            int cell = grid(y,x);
            char c = '.';
            if(cell == 1) c = 'O'; else if(cell != 0) c = '?';
            printf(" %c", c);
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
                gridTemp(y,x) = updateCell(x, y, grid(x,y));


        for (size_t y=1; y< GRID_SIZE;y++) {
            for (size_t x=0; x<GRID_SIZE; x++) {
                grid(y,x) = gridTemp(y,x);
            }
        }
    }

    end = clock();
    double time = ((double) (end - start)) / CLOCKS_PER_SEC;
    return  (double)time;
} 


// main
int main(){

    gridInitial = (int *) malloc(GRID_SIZE * GRID_SIZE * sizeof(int));   
    gridTemp = (int *) malloc(GRID_SIZE * GRID_SIZE * sizeof(int));    
    grid = (int *) malloc(GRID_SIZE * GRID_SIZE * sizeof(int));

    FILE* outputFile = NULL;
    outputFile = fopen("output.txt", "w+");
    
    if (outputFile != NULL)
    {
        initGrid();
        copyInit();
	    grid(6,7) = 1;
        grid(7,7) = 1;
        grid(8,7) = 1;

	printGrid();

        fprintf(outputFile, "Itérations   Temps \n");
        //printf("-----------------------------\n");
	printf("Après 1 itération\n\n");
        
        //for (size_t i=0; i < 1; i++){
            double exec_time = startGame(1);
          //  printf("%6d itérations : %f (s)\n", it[i], exec_time);
            //fprintf(outputFile, "%10d   %lf \n", it[i], exec_time);
        //}
        fclose(outputFile);

        printGrid();

    }
    else printf("Fichier output.txt introuvable");
    printf("\nFin de l'exécution \n");
    return 0;
}
