#ifndef ORDENAR_H 
#define ORDENAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int timestamp;
   char sensor[50];
   int valor;
} Registro;

int contarLinhas(char* fileName, int ignore) {
   FILE *fp = fopen(fileName, "r");
   if (fp == NULL) {
      printf("Nao ha arquivo de registros");
       return -1;
   }
   int contador = 0;
   char linha[256]; 
   while (fgets(linha, sizeof(linha), fp) != NULL) {
       contador++; 
   }
   fclose(fp);
   return contador - ignore;
}

void ordernar(char *fileName) { //Funçaão de ordenar os registros

   Registro registros[contarLinhas(fileName, 2)]; //criando um vetor de registros do tamanho tamanho do arquivo ignorndo o cabeçalho

   FILE *fp = fopen(fileName, "r"); //Abrindo arquivo
   if (fp == NULL) {
      printf("Erro ao abrir o arquivo");
      return;
   }
   
   fseek(fp, 0, SEEK_SET); //Colocando o ponteiro na posição inicial do arquivo
   int i = 0;
   char linha[256];
   fgets(linha, sizeof(linha), fp); //pula 2 linhas
   fgets(linha, sizeof(linha), fp);
    while (fgets(linha, sizeof(linha), fp) != NULL) { //inicia um looping para ler as linhas
        if (strlen(linha) > 1) { //verifica se a linha tem conteudo
            sscanf(linha, "%d %49s %d", &registros[i].timestamp, registros[i].sensor, &registros[i].valor); //divide a linha no formato do struct registro
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

void separarPorSensores(char* fileName) {
   ordernar(fileName);
   FILE *fp, *tfp;
   Registro registros[contarLinhas(fileName, 2)];

   char linha[256], buffer[50];
   int i = 0;

   fp = fopen(fileName, "r"); //pegando as informações do arquivo principal
      if (fp == NULL) {
         printf("Erro ao abrir o arquivo");
         return;
      } else {
         fgets(linha, sizeof(linha), fp); //pulando o cabeçalho
         while (fgets(linha, sizeof(linha), fp) != NULL) {
         if (strlen(linha) > 1) { //verificando se a linha esta vazua
            sscanf(linha, "%d %49s %d", &registros[i].timestamp, registros[i].sensor, &registros[i].valor); //pegando conteudo da linha
            i++;
         }
         }
         fclose(fp); //fechando arquivo principal
      }

      for(i = 0; i < sizeof(registros) / sizeof(Registro); i++) { //mudar a forma de abertura
      snprintf(buffer, sizeof(buffer), "%s.txt", registros[i].sensor);
      tfp = fopen(buffer, "a");
         if (tfp == NULL) {
            tfp = fopen(buffer, "w");
            if (tfp == NULL) {
               perror("Erro ao abrir arquivo");
               return;
               }
        }
        printf("");
        fprintf(tfp, "%i %s %i\n", registros[i].timestamp, registros[i].sensor, registros[i].valor);
        fclose(tfp);
      }
   fclose(fp);
}

#endif 