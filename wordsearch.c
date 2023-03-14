#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

//Vector Struct template
typedef struct {
    int* data;
    size_t size;    
    size_t capacity;
} Vector;

//add push_back method to reallocate capacity of vector
Vector* push_back(Vector* v, int element) {
    if (v->size == v->capacity) {
        v->capacity = (v->capacity == 0) ? 1 : v->capacity * 2;
        v->data = (int*)realloc(v->data, v->capacity * sizeof(int));
    }
    v->data[v->size] = element;
    v->size++;
    return v;
}

//will search for word at given position
//add index of first word to sol
void checkForWord(char** arr, char* word, Vector* pos, int wSize, int count, int i, int j){ 
    // for(int i = 0; i < pos->size; i++){
    //     printf("%d, ", pos->data[i]);
    // }
    // printf("\n");
    // printf("wSize: %d COUNT: %zu Letter found: %c, Letter to Find: %c\n",wSize, pos->size / 2,word[count-1], word[count]);
    // printf("[%d,%d]\n",i,j); 

    if (count == wSize){
        return;
    }
    else{
    if(i-1 >= 0 && j-1 >= 0 && arr[i-1][j-1] == word[count]){
        push_back(pos,i-1);
        push_back(pos,j-1);
        checkForWord(arr,word,pos,wSize,count+1,i-1,j-1);
        if(pos->size / 2 == wSize)
        return;
    }
    if(i-1 >= 0 && arr[i-1][j] == word[count]){
        push_back(pos,i-1);
        push_back(pos,j);
        checkForWord(arr,word,pos,wSize,count+1,i-1,j);
        if(pos->size / 2 == wSize)
        return;
    }
    if(i-1 >= 0 && j+1 < bSize && arr[i-1][j+1] == word[count]){
        push_back(pos,i-1);
        push_back(pos,j+1);
        checkForWord(arr,word,pos,wSize,count+1,i-1,j+1);
        if(pos->size / 2 == wSize)
        return;
    }
    if(j-1 >= 0 && arr[i][j-1] == word[count]){
        push_back(pos,i);
        push_back(pos,j-1);
        checkForWord(arr,word,pos,wSize,count+1,i,j-1);
        if(pos->size / 2 == wSize)
        return;
    }
    if(j+1 < bSize && arr[i][j+1] == word[count]){
        push_back(pos,i);
        push_back(pos,j+1);
        checkForWord(arr,word,pos,wSize,count+1,i,j+1);
        if(pos->size / 2 == wSize)
        return;
        
    }
    if(j-1 >= 0 && i+1 < bSize && arr[i+1][j-1] == word[count]){
        push_back(pos,i+1);
        push_back(pos,j-1);
        checkForWord(arr,word,pos,wSize,count+1,i+1,j-1);
        if(pos->size / 2 == wSize)
        return;
       
    }
    if(i+1 < bSize && arr[i+1][j] == word[count]){
        push_back(pos,i+1);
        push_back(pos,j);
        checkForWord(arr,word,pos,wSize,count+1,i+1,j);
        if(pos->size / 2 == wSize)
        return;
        
    }
    if(i+1 < bSize && j+1 < bSize && arr[i+1][j+1] == word[count]){
        push_back(pos,i+1);
        push_back(pos,j+1);
        checkForWord(arr,word,pos,wSize,count+1,i+1,j+1);
        if(pos->size / 2 == wSize)
        return;
    }
    }
    if(pos->size / 2 == wSize)
        return;   
    pos->size = count;
    pos->capacity = count;
    printf("GOING BACK \n");
}

void printPuzzle(char** arr) {
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%c ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printSol(int** arr) {
    printf("Word found!\n");
    printf("Printing the search path:\n");
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

void editPuzzle(char** arr, int** sol, Vector* pos){
    int count = pos->size / 2;
    for(int i = pos->size - 1; i > 0; i-=2){
        sol[pos->data[i-1]][pos->data[i]] *= 10;
        sol[pos->data[i-1]][pos->data[i]] += count;
        arr[pos->data[i-1]][pos->data[i]] = '!';
        count--;
    }
}

void searchPuzzle(char** arr, char* word) {
    int wSize = strlen(word); //length of word
    int count = 0; //iteration for the word
    int found = 0; //bool value on whether or not we found a word
    int k = 0; //used to check all 8 possible positions
    int **sol = malloc(bSize * sizeof(int*));
//Solution board ot be filled w zeros
    Vector* pos = malloc(sizeof(Vector));
    pos->data = NULL;
    pos->size = 0;
    pos->capacity = 0;

    for (int i = 0; i < bSize; i++) {
        sol[i] = malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++) {
            sol[i][j] = 0;
        }
    }
    for(int i = 0; i < wSize; i++){
        if(word[i] >= 'a' && word[i])
            word[i] -= ('a' - 'A');
    }

    for(int i = 0; i < bSize; i++){ //check board for first letter
        for(int j = 0; j < bSize; j++){
            if (arr[i][j] == word[count]){ 
                push_back(pos,i);
                push_back(pos,j);
                count++;
               checkForWord(arr,word,pos,wSize,count, i, j);
               if(pos->size / 2 == wSize){
                    editPuzzle(arr, sol, pos); //adds ! to arr and numbers to sol 
                    found += 1;
               }
            }
                pos->size = 0;
                pos->capacity = 0;
            count = 0;
        }
    }
    if(found){
    printSol(sol);
    }else{
        printf("Word not found!");
    }
    free(pos);
}

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}
