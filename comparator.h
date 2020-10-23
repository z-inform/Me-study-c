#include <stdio.h>
#include "disalpha.h"

int dcmp(unsigned int* str1, unsigned int* str2); 
int backdcmp(unsigned int* str1, unsigned int* str2);

int backdcmp(unsigned int* str1, unsigned int* str2){
    
    unsigned int readchar = 0;

    int len1 = 0;
    int len2 = 0;

    for(; str1[len1] != 0; len1++);
    for(; str2[len2] != 0; len2++);

    int counter1 = len1;
    int counter2 = len2;

    while( (counter1 != 0) && (counter2 != 0) ){

        readchar = str1[counter1];
        while( (disalpha(readchar) == 0) && (counter1 != 0) ){
            counter1--;
            readchar = str1[counter1];
        }
        
        readchar = str2[counter2];
        while( (disalpha(readchar) == 0) && (counter2 != 0) ){
            counter2--;
            readchar = str2[counter2];
        }


        if( str1[counter1] > str2[counter2] ) return 1;
        else if( str1[counter1] < str2[counter2] ) return -1;
        counter1--;
        counter2--;

    }



    return 0;
}


int dcmp(unsigned int* str1, unsigned int* str2){

    int counter1 = 0;
    int counter2 = 0;
    unsigned int readchar = 0;

    while( !( ( str1[counter1] == 0 ) && (str2[counter2] == 0) ) ){

        readchar = str1[counter1];
        while( (disalpha(readchar) == 0) && (readchar != 0) ){
            counter1++;
            readchar = str1[counter1];
        }

        readchar = str2[counter2];
        while( (disalpha(readchar) == 0) && (readchar != 0) ){
            counter2++;
            readchar = str2[counter2];
        }

        if( str1[counter1] > str2[counter2] ) return 1;
        else if( str1[counter1] < str2[counter2] ) return -1;

        counter1++;
        counter2++;

    }

    return 0;



    
}
