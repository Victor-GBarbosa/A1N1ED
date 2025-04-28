#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int timestamp;
   char sensor[50];
   int valor;
} Registro;

int contarLinhas(char* fileName) {
   FILE *fp = fopen(fileName, "r");
   int contador = 0;
   char linha[256]; 
   while (fgets(linha, sizeof(linha), fp) != NULL) {
       contador++; 
   }
   fclose(fp);
   return contador - 2;
}

void ordernar(char *fileName) { //Funçaão de ordenar os registros

   Registro registros[contarLinhas(fileName)];

   FILE *fp = fopen(fileName, "r+"); //Abrindo arquivo
   if (fp == NULL) {
      printf("Erro ao abrir o arquivo");
      return;
   }
   
   fseek(fp, 0, SEEK_SET);
    int i = 0;
    char linha[256];
    fgets(linha, sizeof(linha), fp);
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        if (strlen(linha) > 1) {
            sscanf(linha, "%d %49s %d", &registros[i].timestamp, registros[i].sensor, &registros[i].valor);
            i++;
        }
    }

    int contador, j = 0, k = 0;
    Registro tempReg;
    do {
      contador = 0;
      j = 0;
      do {
      if (registros[j].timestamp > registros[j + 1].timestamp) {
         contador++;
         tempReg = registros[j+1];
         registros[j+1] = registros[j];
         registros[j] = tempReg;
      }
      j++;
      } while (j < sizeof(registros) / sizeof(Registro) - 1);
    } while (contador != 0);

    fclose(fp);

   fp = fopen(fileName, "w");
   fputs("Timestamp Sensor Valor\r\n",fp);
   int index;
   for(index = 0; index < sizeof(registros) / sizeof(Registro); index++) {
      fprintf(fp, "%i %s %i\n", registros[index].timestamp, registros[index].sensor, registros[index].valor);
   } 
   
   fclose(fp);
}

void separarPorSensores(FILE* fp, char* fileName, char types[]) {
    fp = fopen(fileName, "r+");
     if (fp == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
     } else {

     }
}

