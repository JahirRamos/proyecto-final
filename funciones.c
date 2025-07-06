#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

int menu(){
    int opc;
    printf("\n=== SISTEMA DE GESTION Y PREDICCION DE CONTAMINACION DE AIRE ===\n");
    printf("1. Visualizar zonas urbanas y datos de contaminacion\n");
    printf("2. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opc);
    return opc;
}

void leercadena(char *cadena, int num){
    fflush(stdin);
    fgets(cadena,num,stdin);
    int len = strlen(cadena) -1;
    cadena[len] = '\0';
}

void mostrarZonasUrbanas(){
    printf("\n=== CIUDAD DE QUITO - ZONAS URBANAS MONITOREADAS ===\n");
    printf("========================================\n");
    printf("No.\tZona Urbana\n");
    printf("========================================\n");
    printf("1\tCentro\n");
    printf("2\tBelisario\n");
    printf("3\tCotocollao\n");
    printf("4\tEl Camal\n");
    printf("5\tTumbaco\n");
    printf("========================================\n");
    printf("\nEstas zonas cuentan con estaciones de monitoreo de calidad del aire\n");
    printf("que miden los siguientes contaminantes:\n");
    printf("- PM2.5 (Particulas finas)\n");
    printf("- PM10 (Particulas gruesas)\n");
    printf("- O3 (Ozono)\n");
    printf("- NO2 (Dioxido de nitrogeno)\n");
    printf("- SO2 (Dioxido de azufre)\n");
    printf("- CO (Monoxido de carbono)\n");
    printf("\n");
}

void mostrarSoloZonas(){
    printf("\n=== CIUDAD DE QUITO - ZONAS URBANAS MONITOREADAS ===\n");
    printf("========================================\n");
    printf("No.\tZona Urbana\n");
    printf("========================================\n");
    printf("1\tCentro\n");
    printf("2\tBelisario\n");
    printf("3\tCotocollao\n");
    printf("4\tEl Camal\n");
    printf("5\tTumbaco\n");
    printf("========================================\n");
}

void mostrarDatosContaminacion(){
    int zona;
    
    printf("\n=== VISUALIZAR DATOS DE CONTAMINACION ===\n");
    mostrarSoloZonas();
    
    printf("Seleccione el numero de la zona urbana (1-5): ");
    scanf("%d", &zona);
    
    if(zona >= 1 && zona <= 5) {
        mostrarDatosZona(zona);
    } else {
        printf("Numero de zona no valido. Debe estar entre 1 y 5.\n");
    }
}

void mostrarDatosZona(int numeroZona){
    char nombreZona[30];
    char nombreArchivo[50];
    struct Registrocotocollao registros[100];
    int numRegistros;
    
    switch(numeroZona) {
        case 1: 
            strcpy(nombreZona, "Centro"); 
            strcpy(nombreArchivo, "Centro.csv");
            break;
        case 2: 
            strcpy(nombreZona, "Belisario"); 
            strcpy(nombreArchivo, "Belisario.csv");
            break;
        case 3: 
            strcpy(nombreZona, "Cotocollao"); 
            strcpy(nombreArchivo, "Cotocollao (2).csv");
            break;
        case 4: 
            strcpy(nombreZona, "El Camal"); 
            strcpy(nombreArchivo, "El_Camal.csv");
            break;
        case 5: 
            strcpy(nombreZona, "Tumbaco"); 
            strcpy(nombreArchivo, "Tumbaco.csv");
            break;
    }
    
    
    numRegistros = leerDatosZona(nombreArchivo, registros, 100);
    
    if (numRegistros > 0) {
        mostrarDatosArchivo(registros, numRegistros, nombreZona);
    } else {
        printf("\nNo se pudieron cargar los datos de %s.\n", nombreZona);
        printf("Asegurese de que el archivo %s existe en el directorio.\n", nombreArchivo);
    }
}

int leerDatosZona(const char* nombreArchivo, struct Registrocotocollao registros[], int maxRegistros) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        return 0;
    }
    
    char linea[200];
    int contador = 0;
    
   
    if (fgets(linea, sizeof(linea), archivo)) {
        
    }
    
    while (fgets(linea, sizeof(linea), archivo) && contador < maxRegistros) {
        
        char *columna = strtok(linea, ",");
        if (columna != NULL) {
            
            if (strcmp(nombreArchivo, "Centro.csv") == 0) {
                strcpy(registros[contador].zona, "Centro");
            } else if (strcmp(nombreArchivo, "Belisario.csv")) {
                strcpy(registros[contador].zona, "Belisario");
            } else if (strcmp(nombreArchivo, "Cotocollao.csv")) {
                strcpy(registros[contador].zona, "Cotocollao");
            } else if (strcmp(nombreArchivo, "El_Camal.csv")) {
                strcpy(registros[contador].zona, "El Camal");
            } else if (strcmp(nombreArchivo, "Tumbaco.csv")) {
                strcpy(registros[contador].zona, "Tumbaco");
            } else {
                strcpy(registros[contador].zona, "Desconocida");
            }
            
            strcpy(registros[contador].fecha, columna);
            
            
            columna = strtok(NULL, ",");
            if (columna != NULL && strlen(columna) > 0) {
                registros[contador].pm25 = atoi(columna);
            } else {
                registros[contador].pm25 = 0; 
            }
          
            columna = strtok(NULL, ",");
            if (columna != NULL && strlen(columna) > 0) {
                registros[contador].pm10 = atoi(columna);
            } else {
                registros[contador].pm10 = 0;
            }
            
           
            columna = strtok(NULL, ",");
            if (columna != NULL && strlen(columna) > 0) {
                registros[contador].o3 = atoi(columna);
            } else {
                registros[contador].o3 = 0;
            }
            
            
            columna = strtok(NULL, ",");
            if (columna != NULL && strlen(columna) > 0) {
                registros[contador].no2 = atoi(columna);
            } else {
                registros[contador].no2 = 0;
            }
            
            
            columna = strtok(NULL, ",");
            if (columna != NULL && strlen(columna) > 0) {
                registros[contador].so2 = atoi(columna);
            } else {
                registros[contador].so2 = 0;
            }
            
         
            columna = strtok(NULL, ",");
            if (columna != NULL && strlen(columna) > 0) {
                registros[contador].co = atoi(columna);
            } else {
                registros[contador].co = 0;
            }
            
            contador++;
        }
    }
    
    fclose(archivo);
    return contador;
}

void mostrarDatosArchivo(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona) {
    printf("\n=== DATOS DE CONTAMINACION - %s ===\n", nombreZona);
    printf("Total de registros: %d\n", numRegistros);
    printf("================================================================================\n");
    printf("Fecha\t\tPM2.5\tPM10\tO3\tNO2\tSO2\tCO\tEstado General\n");
    printf("================================================================================\n");
    
    for (int i = 0; i < numRegistros; i++) {
        
        char *estado;
        if (registros[i].pm25 > 25 || registros[i].pm10 > 50) {
            estado = "ALTO";
        } else if (registros[i].pm25 > 15 || registros[i].pm10 > 30) {
            estado = "MODERADO";
        } else {
            estado = "BUENO";
        }
        
        printf("%-12s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               registros[i].fecha, registros[i].pm25, registros[i].pm10,
               registros[i].o3, registros[i].no2, registros[i].so2,
               registros[i].co, estado);

    }
    
    
 
}