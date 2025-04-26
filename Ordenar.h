#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ordernar(FILE* fp, char* fileName) {

   int opt = 0;

    if (fp == NULL) {
       printf("Erro ao abrir o arquivo");
       return;
    } else {
      char tmp[256];
      fgets(tmp, sizeof(tmp), fp); // pula o header
      do {
         char linha[256], linha2[256], linhaCpy[256], linha2Cpy[256];
        
         fgets(linha, sizeof(linha), fp);
         strcpy(linhaCpy, linha);
         long pos = ftell(fp);
         fgets(linha2, sizeof(linha2), fp);
         strcpy(linha2Cpy, linha2);
         long pos1 = ftell(fp);
         strtok(linhaCpy, " ");
         strtok(linha2Cpy, " ");
         
         if (atoi(linhaCpy) < atoi(linha2Cpy)); {
            char linhaTmp[256];
            strcpy(linhaTmp, linha);
            strcpy(linha, linha2);
            strcpy(linha2, linhaTmp);
            
         }
      } while (opt != 0);
    }
}

void separarPorSensores(FILE* fp, char* fileName, char types[]) {
    fp = fopen(fileName, "r+");
     if (fp == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
     } else {

     }
}

