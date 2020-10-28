#include <stdio.h>
#include "disalpha.h"
#include <stdint.h>

int dcmp(uint32_t* str1, unsigned int* str2); 
int backdcmp(uint32_t* str1, unsigned int* str2);
double toComparableCode(uint32_t codePoint);

double toComparableCode(uint32_t codePoint){

    if( (codePoint >= 0x41) && (codePoint <= 0x5A) ) codePoint = codePoint + 0x20;
    if( (codePoint >= 0x410) && (codePoint <= 0x42F) ) codePoint = codePoint + 0x20;
    if( codePoint == 0x401 ) codePoint = 0x451;

    switch (codePoint) {
    case 0x451: return 1077.5; break;
    case 0x415: return 1045.5; break;
    default: return codePoint;
    }

}


int backdcmp(uint32_t* str1, unsigned int* str2){
    
    uint32_t readchar = 0;

    int len1 = 0;
    int len2 = 0;

    for(; str1[len1] != 0; len1++);
    for(; str2[len2] != 0; len2++);

    int counter1 = len1;
    int counter2 = len2;

    double letterCode1 = 0;
    double letterCode2 = 0;

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


        letterCode1 = toComparableCode(str1[counter1]);
        letterCode2 = toComparableCode(str2[counter2]);
        if( letterCode1 > letterCode2 ) return 1;
        else if( letterCode1 < letterCode2 ) return -1;

        counter1--;
        counter2--;

    }



    return 0;
}


int dcmp(uint32_t* str1, unsigned int* str2){

    int counter1 = 0;
    double letterCode1 = 0;
    int counter2 = 0;
    double letterCode2 = 0; //char1 and char2 are needed to have a way of moving codepoints if they are not where you expect them
    uint32_t readchar = 0;

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

        letterCode1 = toComparableCode(str1[counter1]);
        letterCode2 = toComparableCode(str2[counter2]);
        if( letterCode1 > letterCode2 ) return 1;
        else if( letterCode1 < letterCode2 ) return -1;

        counter1++;
        counter2++;

    }

    return 0;
    
}
