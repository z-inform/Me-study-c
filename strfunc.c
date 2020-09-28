#include <stdio.h>
#include <stdlib.h>
#include <cstring>

char* strcat(char* pstr1, char* pstr2);
char* strtok(char* str, char* del);

int main(){
    char str1[500] = "LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOng";
    char str2[100] = "NEWSTR";
    char str3[10] = "    ";
    char str4[2] = "";
    char str5[50] = "alylala, 15 - lastly";
    char del[5] = ",-";
    char* res = strcat(str1, str3);
    res = strcat(res, str2);
    res = strcat(res, str4);
    res = strcat(res, str2);
    res = strtok(str5, del);
    puts(res);
    printf("\n");
    return 0;
}

char* strcat(char* pstr1, char* pstr2){

    int counter = 0;
    char *presstr = (char*) calloc(strlen(pstr1) + strlen(pstr2) + 1, sizeof(char));


    for (; pstr1[counter] != '\0'; counter++){
        presstr[counter] = pstr1[counter];
    }

    
    for (int i = 0; pstr2[i] != '\0'; i++){
        presstr[counter] = pstr2[i];
        counter++;
    }
    
    return presstr;
}

char* strtok(char* str, char* del){

    char* lex = (char*) calloc(strlen(str) + 1, sizeof(char));

    for(int i = 0; (str[i] != '\0'); i++){

        for(int c = 0; del[c] != '\0'; c++){
            if( str[i] == del[c]){
                lex = (char*) realloc(lex, (strlen(lex) + 1)*sizeof(char));
                return lex;
            }
            else lex[i] = str[i];
        }

    }
    return lex;
}
    
