#include <stdio.h>
#include <stdlib.h>
#include "chardecode.h"
#include "comparator.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void printText(FILE* resFile, int* charArr);
void getText(FILE* orig, int* charArr, int** strArr, int* strCount); 
int countLen(FILE* orig);
void printStr(FILE* resFile, int* str);
void putChar(FILE* resFile, int unicodeChar);
int sortCompar(const void* str1, const void* str2);
int backsortCompar(const void* str1, const void* str2);


int main(){

    FILE* resFile = fopen("result-onegin", "wb");
    if( resFile == NULL ){
       printf("file open error\n");
       return 1;
     }



    FILE* orig = fopen("gin.txt", "rb");
    if( orig == NULL ){
       printf("file open error\n");
       return 1;
     }

    struct stat filestats = {0};

    stat("gin.txt", &filestats);

    int* charArr = (int*) calloc(filestats.st_size + 1, sizeof(int));

    int** strArr = (int**) calloc(countLen(orig) + 1, sizeof(int*));
    
    int strCountSort = 0;
    getText(orig, charArr, strArr, &strCountSort);

    fprintf(resFile, "---------------------Original Text-----------------\n"); 
    printText(resFile, charArr); 
    fprintf(resFile, "---------------------End of original---------------\n\n");


    fprintf(resFile, "---------------------Strings-----------------\n"); 
    for(int i = 0; strArr[i] != NULL; i++){
        printStr(resFile, strArr[i]);
    }
    fprintf(resFile, "---------------------End of strings-----------------\n\n"); 


    fprintf(resFile, "---------------------Sorted-----------------\n"); 
    qsort(strArr, strCountSort, sizeof(int**), (int(*) (const void*, const void*)) sortCompar);
    for(int i = 0; strArr[i] != NULL; i++){
        printStr(resFile, strArr[i]);
    }



    fprintf(resFile, "---------------------End of sorted-----------------\n\n"); 


    fprintf(resFile, "---------------------Backsorted-----------------\n"); 
    qsort(strArr, strCountSort, sizeof(int**), (int(*) (const void*, const void*)) backsortCompar);
    for(int i = 0; strArr[i] != NULL; i++){
        printStr(resFile, strArr[i]);
    }
    fprintf(resFile, "---------------------End of backsorted-----------------\n\n"); 

    fclose(orig);
    fclose(resFile);
    free(charArr);
    free(strArr);



    return 0;
}

int backsortCompar(const void* str1, const void* str2){
    return backdcmp((unsigned int*) *(int**)str1, (unsigned int*) *(int**)str2);
}


int sortCompar(const void* str1, const void* str2){
    return dcmp((unsigned int*) *(int**)str1, (unsigned int*) *(int**)str2);
}

void putChar(FILE* resFile, int unicodeChar){
    for(int move = 0; (move < 4); move++){
        char pointChar = (encodeChar(unicodeChar) << move * 8) >> 3*8;
        if( pointChar != 0x0 )  fputc(pointChar, resFile);
    }

}

void printStr(FILE* resFile, int* str){

    for(int stri = 0; ( (str[stri] != 0) && (str[stri] != -1) ); stri++){
        putChar(resFile, str[stri]);
    }
    fputc(0xA, resFile);

}

int countLen(FILE* orig){
    rewind(orig);
    int counter = 0;
    int readchar = fgetc(orig);
    while( readchar != EOF ){
        if( readchar == '\n') counter++;
        readchar = fgetc(orig);
    }
    rewind(orig);
    return counter;
}

void getText(FILE* orig, int* charArr, int** strArr, int *strCount){

    int readchar = 0;
    int scount = 0;
    int pcount = 1;

    fseek(orig, 0, SEEK_SET);
    readchar = fgetc(orig);
    charArr[0] = readchar;
    strArr[0] = charArr;

    while( readchar != EOF ){
        if( readchar == 0xA ) charArr[scount] = 0;
        else charArr[scount] = decodeChar(orig, readchar);
        scount++;

        long curPos = ftell(orig);

        if( readchar == '\n' ){
            readchar = fgetc(orig);
            bool emptyFlag = true;
            while( (emptyFlag) && (readchar != EOF) && (readchar != '\n') ){
                readchar = decodeChar(orig, readchar);
                if( (disalpha(readchar) == 1) && 
                    (readchar != 0x49) && 
                    (readchar != 0x56) &&
                    (readchar != 0x58) ) emptyFlag = false;
                readchar = fgetc(orig);
            }

            if( !emptyFlag ){
                strArr[pcount] = &charArr[scount];
                pcount++;
            }
        fseek(orig, curPos, SEEK_SET);
        }

        readchar = fgetc(orig);

    }

    charArr[scount+1] = -1; 
    strArr[pcount+1] = NULL;
    *strCount = pcount;

}

void printText(FILE* resFile, int* arr){
    for(int i = 0; arr[i] != -1; i++){
        if( arr[i] == 0 ) fputc(0xA, resFile);
        else putChar(resFile, arr[i]);
    }
}





