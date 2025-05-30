#ifndef BUSCABINARIA_H
#define BUSCABINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenar.h"
#include <time.h>

char* converterTimestampParaData(time_t timestamp) {
    static char buffer[20];
    struct tm *tm_info = localtime(&timestamp);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);
    return buffer;
}

void buscarRegistro(char *sensor, time_t timeStamp) {
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s.txt", sensor);
    
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read all lines and populate the registro array
    Registro registros[contarLinhas(fileName, 0)]; 
    int count = 0;
    int i = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), fp) != NULL) { //inicia um looping para ler as linhas
        if (strlen(linha) > 1) { //verifica se a linha tem conteudo
            sscanf(linha, "%ld %49s %d", &registros[i].timestamp, registros[i].sensor, &registros[i].valor); //divide a linha no formato do struct registro
            i++;
        }
    }
    fclose(fp);

    //busca binaria
    int inicio = 0, fim = i - 1, meio;
    Registro aprox = {0, "", 0}; //registro aproximado

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;

        if (registros[meio].timestamp == timeStamp) { //Caso o ts seja encontrado
            printf("Registro encontrado: data: %s, Sensor: %s, Valor: %d\n", //retorno do registro encontrado
                   converterTimestampParaData(registros[meio].timestamp), registros[meio].sensor, registros[meio].valor);
                   return;
        }

        if (registros[meio].timestamp < timeStamp) {
            aprox = registros[meio]; //atualiza o mais próximo
            inicio = meio + 1;
        } else {
            if (aprox.timestamp == 0 || registros[meio].timestamp < aprox.timestamp) {
                aprox = registros[meio]; //atualiza o mais próximo 
            }
            fim = meio - 1;
        }
    }

    //se não encontrado, retorna o mais próximo para baixo
    if (aprox.timestamp != 0) {
        printf("Registro mais próximo encontrado: Data: %s, Sensor: %s Valor: %d \n",
            converterTimestampParaData(aprox.timestamp), aprox.sensor, aprox.valor);
        return;
    }

    //Caso não haja nenhum timestamp menor, retorna um registro vazio --
    
    printf("Registro não encontrado para o timestamp: %ld\n", timeStamp);
    
}

void buscarRegistroExato(char *sensor, time_t timeStamp) {
    char fileName[50];
    snprintf(fileName, sizeof(fileName), "%s.txt", sensor);
    
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Read all lines and populate the registro array
    Registro registros[contarLinhas(fileName, 0)];
    int count = 0;
    int i = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), fp) != NULL) {
        if (strlen(linha) > 1) {
            sscanf(linha, "%ld %49s %d", &registros[i].timestamp, registros[i].sensor, &registros[i].valor);
            i++;
        }
    }
    fclose(fp);

    // Binary search for exact match
    int inicio = 0, fim = i - 1, meio;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;

        if (registros[meio].timestamp == timeStamp) {
            printf("Registro encontrado: Data: %s, Sensor: %s, Valor: %d\n",
                   converterTimestampParaData(registros[meio].timestamp), registros[meio].sensor, registros[meio].valor);
            return;
        }

        if (registros[meio].timestamp < timeStamp) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Registro não encontrado para o timestamp: %ld\n", timeStamp);
}
#endif