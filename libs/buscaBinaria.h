#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenar.h"

int buscar (char *fileName) {

    FILE *fp;
    char buffer[50], linha[256];
    Registro registros[contarLinhas(fileName)];
    int i;

    fgets(linha, sizeof(linha), fp);
    while (fgets(linha, sizeof(linha), fp) != NULL) {
    if (strlen(linha) > 1) {
       sscanf(linha, "%d %49s %d", &registros[i].timestamp, registros[i].sensor, &registros[i].valor);
       i++;
    }
    
    snprintf(buffer, sizeof(buffer), "%s.txt", registros[i].sensor);
    fp = fopen(buffer, "a");


}
