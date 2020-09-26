#include <stdio.h>
#include <stdlib.h>

char* strcat(char* pstr1, char* pstr2);

int main(){
    char str1[10] = "abcdef";
    char str2[10] = "xyz";
    char* res = strcat(str1, str2);
    for (int i = 0; res[i] != '\0'; i++) putchar(res[i]);
    printf("\n");
    return 0;
}

char* strcat(char* pstr1, char* pstr2){

    int counter = 0;
    char *presstr = (char*) calloc(1, sizeof(char));


    for (; pstr1[counter] != '\0'; counter++){
        presstr = (char*) realloc(presstr, counter*sizeof(char));
        presstr[counter] = pstr1[counter];
    }

    
    for (int i = 0; pstr2[i] != '\0'; i++){
        ++counter;
        presstr = (char*) realloc(presstr, counter*sizeof(char));
        presstr[counter] = pstr2[i];
    }
    
return presstr;
}

