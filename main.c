#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "libs/ordenar.h"
#include "libs/buscaBinaria.h"



time_t capturar_timestamp_valido() {
    int dia, mes, ano, hora, min, seg;
    struct tm t;

    while (1) {
        printf("Digite a data e hora (dd mm aaaa hh mm ss): ");
        if (scanf("%d %d %d %d %d %d", &dia, &mes, &ano, &hora, &min, &seg) != 6) {
            while (getchar() != '\n');
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        t.tm_year = ano - 1900;
        t.tm_mon = mes - 1;
        t.tm_mday = dia;
        t.tm_hour = hora;
        t.tm_min = min;
        t.tm_sec = seg;
        t.tm_isdst = -1;

        time_t timestamp = mktime(&t);
        if (timestamp == -1) {
            printf("Data inválida. Tente novamente.\n");
        } else {
            return timestamp;
        }
    }
}

char *gerar_nome(){
char *nomes[5]={"TEMP","PRESS","UMID","VIBR","FLUX"};
int idx=rand()%5;
return nomes[idx];
}

int gerar_num(){
    int num;
    num=rand()%1000;
    return num;
} 

time_t gerar_timestamp_aleatorio(int dia, int mes, int ano) {
    struct tm t;
    time_t timestamp_inicial, timestamp_final;
    
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    
    timestamp_inicial = mktime(&t);
    if (timestamp_inicial == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    t.tm_hour = 23;
    t.tm_min = 59;
    t.tm_sec = 59;
    
    timestamp_final = mktime(&t);
    if (timestamp_final == -1) {
        printf("Data inválida.\n");
        return -1;
    }

    time_t timestamp_aleatorio = timestamp_inicial + rand() % (timestamp_final - timestamp_inicial + 1);
    
    return timestamp_aleatorio;
}

int main(void){
    //variaveis de arquivo
    FILE *fp;
    struct tm *timenow;
    time_t clock;
    char *fname = "Registros.txt";

    //variaveis utilitarias
    char *sensorTypes[5] = {"TEMP", "PRES", "VIBR", "UMID", "FLUX"};
    int opt, sensorOpt = 0;;
    int i,j;
    srand(time(NULL) + i + j);
    setlocale(LC_ALL, "pt-BR");

        do {
            printf("Escolha uma opcao:\n");
            printf("1. Gerar novo arquivo arquivo\n");
            printf("2. Ordernar arquivos\n");
            printf("3. Separar\n");
            printf("4. Buscar sensor por tempo\n");
            printf("Opcao: ");
            scanf("%d", &opt);

            switch (opt) {
                case 1:
                    fp = fopen(fname, "w");
                    fputs("Timestamp Sensor Valor\r\n",fp);
                    clock=capturar_timestamp_valido();
                    timenow=localtime(&clock);
                    for ( j = 0; j < (sizeof(sensorTypes) / sizeof(sensorTypes[0])); j++) {
                        for (i = 0; i < 1200; i++) {
                            time_t randTimestamp = gerar_timestamp_aleatorio(timenow->tm_mday, timenow->tm_mon + 1, timenow->tm_year + 1900);
                            fprintf(fp, "%ld %s %d\n", randTimestamp, sensorTypes[j], gerar_num());
                        }
                    }
                    system("cls");
                    if (fp != NULL) {
                        printf("Arquivo Criado com sucesso\n\n");
                    }
                    fclose(fp);
                    break;
                case 2:
                    system("cls");
                    ordernar(fname);
                    break;
                case 3:
                    system("cls");
                    separarPorSensores(fname);
                    break;
                case 4:
                    fp = fopen(fname, "r");
                    if (fp == NULL) {
                        system("cls");
                        printf("Arquivo principal nao foi inicializado\n");
                        fclose(fp);
                        break;
                    }
                    fclose(fp);
                    printf("Escolha um sensor: \n");
                    for (int l = 0; l < sizeof(sensorTypes) / sizeof(sensorTypes[0]); l++) {
                        printf("%i- %s\n", l + 1, sensorTypes[l]);
                    }
                    
                    scanf("%d", &sensorOpt);
                    buscarRegistroExato(sensorTypes[sensorOpt - 1], capturar_timestamp_valido());
                    
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }
        } while (opt != 5);
        system("cls");
return 0;
}