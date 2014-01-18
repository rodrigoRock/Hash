#include "hash.h"
#include <sys/time.h>

int main(void) {
    
    char key[151], temp;
    int data;
    unsigned int size, maxSize, i, t;
    float trigger;
    
    maxSize = initialSize; //vai aumentar quando fizer rehashing (disparado pelo fator de carga limite)
    trigger = 1 + maxSize * loadFactor;
    size = 0;
    cell *table = (cell*) malloc(maxSize * sizeof(cell));
    //linkedCell *table = (linkedCell*) malloc(maxSize * sizeof(linkedCell));
    
    for(i = 0; i < maxSize; i++){
        table[i].filled = 0;
    }
    
    printf("\r\n-----------------------------------------------\r\n");
    printf("REHASH   |   SIZE  |  TIME (ms)  | RH TIME (ms)");
    printf("\r\n-----------------------------------------------\r\n\r\n");
    t = 1;
    while(1){
        
        if(t == 1){
            timer(0, START);
        }
        
        /*printf("\n|");
        for(i = 0; i < maxSize; i++){
            if(table[i].filled)
                printf(" %d |", table[i].filled);
            else
                printf("   |");
        }
        printf("\n\n\n\n\n\n\n");*/
        
        scanf("%s", key);
        
        temp = getchar();
        if(temp == ' '){
            scanf("%d", &data);
            if(size+1 == trigger){
                printf("Rehashing ");
                timer(1, START);
                maxSize = maxSize * expansionFactor;
                trigger = 1 + maxSize * loadFactor;
                table = (cell*) realloc(table, maxSize * sizeof(cell));
                if(linearRehash(table, maxSize, key, data) == 0){
                    size++;
                    printf("[%07d]", size);
                    //printf("0\n");
                    printf(" %26.3lf\r\n", timer(1, STOP));
                }
                else{
                    //printf("-1\n");
                }
            }
            else{
                //printf("Inserir:Key: '%s' ::: Data: '%d'", key, data);
                if(linearInsert(table, maxSize, key, data) == 0){
                //if(linkedInsert(table, maxSize, key, data) == 0){
                    size++;
                    //printf("[%d]\r\n", size);
                    //printf("0\n");
                }
                else{
                    //printf("-1\n");
                }
                //printf("\nsize: '%u'\n", size);
            }
        }
        else{
            if(temp == 13 || temp == 10){ //ENTER
                //printf("Buscar: Key: '%s': ", key);
                //printf("[%d]\n", linearSearch(table, maxSize, key));
            }
            else{
                printf("          [%07d]\r\n", size);
                printf("[FIM]\n");
                break;
            }
        }
        
        if(t == 1000){
            t = 0;
            printf("          [%07d]", size);
            printf(" %12.3lf\r\n", timer(0, STOP));
        }
        t++;
    }
    return (EXIT_SUCCESS);
}

double timer(short n, short mark){
    
    static short state[2] = {OFF, OFF};
    static double tIn[2] = {0.0, 0.0};
    double tOut, time;
    struct timeval getTime;
    
    switch(mark){
        
        case START:
            gettimeofday(&getTime, NULL);
            tIn[n] = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            state[n] = ON;
            return 0.0;
            break;
        
        case GET:
            if(state[n] == OFF){
                return 0.0;
            }
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            time = (tOut - tIn[n]) / 1000.0;
            return time;
            break;
    
        case STOP:
            if(state[n] == OFF){
                return 0.0;
            }
            gettimeofday(&getTime, NULL);
            tOut = (double)getTime.tv_usec + ((double)getTime.tv_sec * (1000000.0));
            time = (tOut - tIn[n]) / 1000.0;
            state[n] = OFF;
            return time;
            break;
    }
}
