#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <assert.h>

char* strcat(char* pstr1, char* pstr2);
char* strtok(char* str, char* del);

int main(){
    char str1[500] = "LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOng";
    char str2[100] = "NEWSTR";
    char str3[10] = ",,,,";
    char str4[2] = "";
    char str5[50] = "-,-alylala,,,, 15 - lastly-";
    char del[5] = ",-";
    char* res;
    res = strtok(str2, del);
    if( res != NULL ) puts(res);
    else printf("Но тут же одни делимитеры\n");
    res = strtok(str5, del);
    while(res != NULL){
        puts(res);
        res = strtok(NULL, del);
    }

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

    static char* endpointer; //static указатель, хранящий между вызовами функции адрес начала обрабатываемой строки
    char* begpointer = NULL; //адрес начала отделенного токена. Возвращается функцией
    bool inDelimiter = false; //Показывает, что мы находимся в последовательности делимитеров
    bool isDelimiter = false; //Используется в определении конца последовательности делимитеров. Объявлен здесь из-за какой-то фигни с областями видимости
    static bool beginningFlag = true; //Используется для отсечения начальных делимитеров сроки. Static потому что сохранятеся между вызовами с одной строкой
    int i = 0; //Счетчик внешнего цикла. Хранится вне его для корректной обработки конца строки
    int tokenEnd; //Хранит конец первого токена, чтобы в конце работы функции заменить его на \0. Его необходимость обнаружена в результате боли и дебага.

    if( str != NULL ){
        endpointer = str; //Проверка на вызов с аргументом NULL. Вызов с NULL вызывет обработку строки, переданной ранее
        beginningFlag = true;
    }

    assert(endpointer != NULL); //Вот очень не работать с NULL-ом. Надо бы заменить на более понятное сообщение о том, что в первый раз вызывать strtok с аргументом NULL - плохо

    if( *endpointer == '\0' ) return NULL; //Возвращаем NULL если достигли конца строки

    for(; endpointer[i] != '\0'; i++){ 

        if( !inDelimiter ){                       //Проверяем на первый делимитер
            for(int c = 0; del[c] != '\0'; c++){
                if( del[c] == endpointer[i] ){
                    tokenEnd = i;
                    inDelimiter = true;
                }
            }
        }

        if( inDelimiter ){  //Если уже вошли в последовательность делимитров, то проверяем на ее конец. Не if - else по той же причине, что и tokenEnd.
            isDelimiter = false;
            for(int c = 0; del[c] != '\0'; c++){
                if( endpointer[i] == del[c] ) isDelimiter = true;
            }
        }            

        if( !isDelimiter && inDelimiter ) { //При выходе из последовательности делимитров изменяем адрес начала строки для следющего вызова, ставим конец строки первому токену, возвращаем указатель на его начало
            if( beginningFlag ){ //Проверка на конец последовательности делимитеров в начале строки
                beginningFlag = false;
                begpointer = endpointer + i;
                inDelimiter = false;
                isDelimiter = false;
            }
            else{
                if( begpointer == NULL ) begpointer = endpointer; //Если адрес начала токена не был изменен из-за делимитеров в начале строки
                endpointer[tokenEnd] = '\0';
                endpointer += i;
                return begpointer;
            }

        }
        
        if( !inDelimiter && beginningFlag ) beginningFlag = false;     

    }   
    
    if( inDelimiter ) endpointer[tokenEnd] = '\0'; //В случае выхода из-за конца строки так же ставим \0 в конце токена, но не перемещаем endpointer на следующий символ (а то segfault будет) 
    if( inDelimiter && beginningFlag ) return NULL; //Вся строка состоит из делимитеров, поэтому возвращаем NULL. По идее больше случаев когда может вернуться пустая строка нет. Надеюсь
    begpointer = endpointer;
    endpointer += i;
    return begpointer;
}















