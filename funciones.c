#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

int menu(){
    int opc;
    printf("\n=== SISTEMA DE GESTION Y PREDICCION DE CONTAMINACION DE AIRE ===\n");
    printf("1. Monitoreo actual de contaminacion (ultimos 3 dias)\n");
    printf("2. Prediccion de niveles futuros (24 horas con factores climaticos)\n");
    printf("3. Analisis historico (promedios de 30 dias)\n");
    printf("4. Exportar reportes y datos\n");
    printf("5. Ver datos climaticos actuales\n");
    printf("6. Salir\n");
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
    
    printf("\n=== MONITOREO ACTUAL DE CONTAMINACION (ULTIMOS 3 DIAS) ===\n");
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
            strcpy(nombreArchivo, "Centro.txt");
            break;
        case 2: 
            strcpy(nombreZona, "Belisario"); 
            strcpy(nombreArchivo, "Belisario.txt");
            break;
        case 3: 
            strcpy(nombreZona, "Cotocollao"); 
            strcpy(nombreArchivo, "Cotocollao (2).txt");
            break;
        case 4: 
            strcpy(nombreZona, "El Camal"); 
            strcpy(nombreArchivo, "El_Camal.txt");
            break;
        case 5: 
            strcpy(nombreZona, "Tumbaco"); 
            strcpy(nombreArchivo, "Tumbaco.txt");
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
            
            if (strcmp(nombreArchivo, "Centro.txt") == 0) {
                strcpy(registros[contador].zona, "Centro");
            } else if (strcmp(nombreArchivo, "Belisario.txt") == 0) {
                strcpy(registros[contador].zona, "Belisario");
            } else if (strcmp(nombreArchivo, "Cotocollao (2).txt") == 0) {
                strcpy(registros[contador].zona, "Cotocollao");
            } else if (strcmp(nombreArchivo, "El_Camal.txt") == 0) {
                strcpy(registros[contador].zona, "El Camal");
            } else if (strcmp(nombreArchivo, "Tumbaco.txt") == 0) {
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
    // Mostrar límites aceptables primero
    mostrarLimitesAceptables();
    
    // Limitar a los ultimos 3 dias para monitoreo actual
    int registrosAMostrar = (numRegistros > 3) ? 3 : numRegistros;
    
    printf("\n=== DATOS DE CONTAMINACION ACTUAL - %s ===\n", nombreZona);
    printf("Mostrando los ultimos %d dias de monitoreo\n", registrosAMostrar);
    printf("=====================================================================================================\n");
    printf("Fecha\t\tPM2.5\tPM10\tO3\tNO2\tSO2\tCO\tEstado General\n");
    printf("=====================================================================================================\n");
    
    int contadores[3] = {0, 0, 0}; // BUENO, MODERADO, ALTO
    
    for (int i = 0; i < registrosAMostrar; i++) {
        // Evaluar cada contaminante individualmente
        char *estadoPM25 = evaluarContaminante(registros[i].pm25, "PM2.5");
        char *estadoPM10 = evaluarContaminante(registros[i].pm10, "PM10");
        char *estadoO3 = evaluarContaminante(registros[i].o3, "O3");
        char *estadoNO2 = evaluarContaminante(registros[i].no2, "NO2");
        char *estadoSO2 = evaluarContaminante(registros[i].so2, "SO2");
        char *estadoCO = evaluarContaminante(registros[i].co, "CO");
        
        // Determinar estado general basado en el peor contaminante
        char *estadoGeneral = "BUENO";
        if (strcmp(estadoPM25, "ALTO") == 0 || strcmp(estadoPM10, "ALTO") == 0 || 
            strcmp(estadoO3, "ALTO") == 0 || strcmp(estadoNO2, "ALTO") == 0 || 
            strcmp(estadoSO2, "ALTO") == 0 || strcmp(estadoCO, "ALTO") == 0) {
            estadoGeneral = "ALTO";
            contadores[2]++;
        } else if (strcmp(estadoPM25, "MODERADO") == 0 || strcmp(estadoPM10, "MODERADO") == 0 || 
                   strcmp(estadoO3, "MODERADO") == 0 || strcmp(estadoNO2, "MODERADO") == 0 || 
                   strcmp(estadoSO2, "MODERADO") == 0 || strcmp(estadoCO, "MODERADO") == 0) {
            estadoGeneral = "MODERADO";
            contadores[1]++;
        } else {
            contadores[0]++;
        }
        
        printf("%-12s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               registros[i].fecha, registros[i].pm25, registros[i].pm10,
               registros[i].o3, registros[i].no2, registros[i].so2,
               registros[i].co, estadoGeneral);
    }
    
    // Mostrar resumen estadístico solo de los ultimos 3 dias
    printf("=====================================================================================================\n");
    printf("\n=== RESUMEN DE CALIDAD DEL AIRE ACTUAL - %s ===\n", nombreZona);
    printf("Dias con calidad BUENA: %d de %d\n", contadores[0], registrosAMostrar);
    printf("Dias con calidad MODERADA: %d de %d\n", contadores[1], registrosAMostrar);
    printf("Dias con calidad ALTA (Peligrosa): %d de %d\n", contadores[2], registrosAMostrar);
    
    // Evaluar tendencia de los ultimos 3 dias
    if (contadores[2] > 0) {
        printf("\n  ALERTA: Se detectaron %d dias con niveles ALTOS de contaminacion.\n", contadores[2]);
        printf("   Recomendacion: Evitar actividades al aire libre.\n");
    } else if (contadores[1] > 0) {
        printf("\n  PRECAUCION: %d dias con calidad MODERADA detectados.\n", contadores[1]);
        printf("   Recomendacion: Personas sensibles deben limitar actividades prolongadas al aire libre.\n");
    } else {
        printf("\n La calidad del aire en %s ha estado dentro de rangos aceptables.\n", nombreZona);
    }
    
    // Mostrar estado actual (dia mas reciente)
    if (registrosAMostrar > 0) {
        char *estadoActual = "BUENO";
        if (strcmp(evaluarContaminante(registros[0].pm25, "PM2.5"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[0].pm10, "PM10"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[0].o3, "O3"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[0].no2, "NO2"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[0].so2, "SO2"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[0].co, "CO"), "ALTO") == 0) {
            estadoActual = "ALTO";
        } else if (strcmp(evaluarContaminante(registros[0].pm25, "PM2.5"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[0].pm10, "PM10"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[0].o3, "O3"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[0].no2, "NO2"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[0].so2, "SO2"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[0].co, "CO"), "MODERADO") == 0) {
            estadoActual = "MODERADO";
        }
        
        printf("\n=== ESTADO ACTUAL (%s) ===\n", registros[0].fecha);
        printf("Calidad del aire: %s\n", estadoActual);
        
        // Mostrar recomendaciones especificas si hay contaminantes altos
        if (strcmp(estadoActual, "ALTO") == 0) {
            mostrarRecomendacionesEspecificas(registros[0]);
        }
    }
    
    printf("\n");
}

void mostrarLimitesAceptables() {
    printf("\n=== LIMITES ACEPTABLES DE CONTAMINANTES (OMS 2021) ===\n");
    printf("================================================================\n");
    printf("Contaminante\tBUENO\t\tMODERADO\tALTO\t\tUnidad\n");
    printf("================================================================\n");
    printf("PM2.5\t\t0-10\t\t11-15\t\t>15\t\tμg/m³\n");
    printf("PM10\t\t0-30\t\t31-45\t\t>45\t\tμg/m³\n");
    printf("O3\t\t0-60\t\t61-100\t\t>100\t\tμg/m³\n");
    printf("NO2\t\t0-15\t\t16-25\t\t>25\t\tμg/m³\n");
    printf("SO2\t\t0-25\t\t26-40\t\t>40\t\tμg/m³\n");
    printf("CO\t\t0-2\t\t3-4\t\t>4\t\tmg/m³\n");
    printf("================================================================\n\n");
}

char* evaluarContaminante(int valor, const char* tipo) {
    if (strcmp(tipo, "PM2.5") == 0) {
        if (valor <= 10) return "BUENO";
        else if (valor <= 15) return "MODERADO";
        else return "ALTO";
    }
    else if (strcmp(tipo, "PM10") == 0) {
        if (valor <= 30) return "BUENO";
        else if (valor <= 45) return "MODERADO";
        else return "ALTO";
    }
    else if (strcmp(tipo, "O3") == 0) {
        if (valor <= 60) return "BUENO";
        else if (valor <= 100) return "MODERADO";
        else return "ALTO";
    }
    else if (strcmp(tipo, "NO2") == 0) {
        if (valor <= 15) return "BUENO";
        else if (valor <= 25) return "MODERADO";
        else return "ALTO";
    }
    else if (strcmp(tipo, "SO2") == 0) {
        if (valor <= 25) return "BUENO";
        else if (valor <= 40) return "MODERADO";
        else return "ALTO";
    }
    else if (strcmp(tipo, "CO") == 0) {
        if (valor <= 2) return "BUENO";
        else if (valor <= 4) return "MODERADO";
        else return "ALTO";
    }
    return "DESCONOCIDO";
}

void prediccionNivelesFuturos() {
    printf("\n=== SISTEMA DE PREDICCION DE CONTAMINACION - PROXIMAS 24 HORAS ===\n");
    mostrarMenuPrediccion();
}

void mostrarMenuPrediccion() {
    int zona;
    
    printf("\n=== PREDICCION DE NIVELES FUTUROS ===\n");
    printf("Seleccione la zona para generar prediccion:\n");
    mostrarSoloZonas();
    
    printf("Seleccione el numero de la zona urbana (1-5): ");
    scanf("%d", &zona);
    
    if(zona >= 1 && zona <= 5) {
        predecirZona(zona);
    } else {
        printf("Numero de zona no valido. Debe estar entre 1 y 5.\n");
    }
}

void predecirZona(int numeroZona) {
    char nombreZona[30];
    char archivoActual[50];
    struct Registrocotocollao registros[100];
    int numRegistros;
    
    switch(numeroZona) {
        case 1: 
            strcpy(nombreZona, "Centro"); 
            strcpy(archivoActual, "Centro.txt");
            break;
        case 2: 
            strcpy(nombreZona, "Belisario"); 
            strcpy(archivoActual, "Belisario.txt");
            break;
        case 3: 
            strcpy(nombreZona, "Cotocollao"); 
            strcpy(archivoActual, "Cotocollao (2).txt");
            break;
        case 4: 
            strcpy(nombreZona, "El Camal"); 
            strcpy(archivoActual, "El_Camal.txt");
            break;
        case 5: 
            strcpy(nombreZona, "Tumbaco"); 
            strcpy(archivoActual, "Tumbaco.txt");
            break;
    }
    
    // Cargar datos de los ultimos 30 dias
    numRegistros = leerDatosZona(archivoActual, registros, 100);
    
    if (numRegistros > 0) {
        printf("\n=== ANALISIS COMPLETADO ===\n");
        printf("Datos de los ultimos 30 dias cargados: %d registros\n", numRegistros);
        
        mostrarPrediccion24h(registros, numRegistros, nombreZona);
    } else {
        printf("\nNo se pudieron cargar los datos para %s.\n", nombreZona);
        printf("Asegurese de que el archivo %s existe en el directorio.\n", archivoActual);
    }
}

float calcularTendencia(int valores[], int numValores) {
    if (numValores < 2) return 0.0;
    
    float suma = 0.0;
    int cambios = 0;
    
    // Calcular promedio de cambios entre dias consecutivos
    for (int i = 1; i < numValores; i++) {
        if (valores[i-1] > 0 && valores[i] > 0) { // Solo considerar valores validos
            suma += (float)(valores[i] - valores[i-1]);
            cambios++;
        }
    }
    
    return (cambios > 0) ? suma / cambios : 0.0;
}

int predecirProximoValor(int valoresRecientes[], int numValores, float tendencia) {
    if (numValores == 0) return 0;
    
    // Encontrar el ultimo valor valido
    int ultimoValor = 0;
    for (int i = numValores - 1; i >= 0; i--) {
        if (valoresRecientes[i] > 0) {
            ultimoValor = valoresRecientes[i];
            break;
        }
    }
    
    // Aplicar tendencia pero limitar cambios drasticos
    int prediccion = ultimoValor + (int)tendencia;
    
    // Asegurar que la prediccion sea realista (no negativa)
    if (prediccion < 0) prediccion = 0;
    
    // Limitar cambios drasticos (max 50% de variacion)
    int maxCambio = ultimoValor * 0.5;
    if (abs(prediccion - ultimoValor) > maxCambio) {
        if (prediccion > ultimoValor) {
            prediccion = ultimoValor + maxCambio;
        } else {
            prediccion = ultimoValor - maxCambio;
        }
    }
    
    return prediccion;
}

void mostrarPrediccion24h(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona) {
    printf("\n=== PREDICCION 24 HORAS - %s ===\n", nombreZona);
    printf("Basado en analisis de tendencias de los ultimos 30 dias (%d registros)\n", numRegistros);
    
    // Obtener datos climaticos para la zona
    struct DatosClimaticos clima = obtenerDatosClimaticos(nombreZona);
    printf("Condiciones climaticas: Temp %.1f°C, Presion %.0f hPa, Humedad %.0f%%\n", 
           clima.temperatura, clima.presion, clima.humedad);
    
    printf("===============================================================================\n");
    
    // Extraer valores de los ultimos 7 dias para cada contaminante
    int diasAnalisis = (numRegistros > 7) ? 7 : numRegistros;
    
    int pm25[7], pm10[7], o3[7], no2[7], so2[7], co[7];
    
    // Copiar ultimos valores
    for (int i = 0; i < diasAnalisis; i++) {
        pm25[i] = registros[i].pm25;
        pm10[i] = registros[i].pm10;
        o3[i] = registros[i].o3;
        no2[i] = registros[i].no2;
        so2[i] = registros[i].so2;
        co[i] = registros[i].co;
    }
    
    // Calcular tendencias
    float tendenciaPM25 = calcularTendencia(pm25, diasAnalisis);
    float tendenciaPM10 = calcularTendencia(pm10, diasAnalisis);
    float tendenciaO3 = calcularTendencia(o3, diasAnalisis);
    float tendenciaNO2 = calcularTendencia(no2, diasAnalisis);
    float tendenciaSO2 = calcularTendencia(so2, diasAnalisis);
    float tendenciaCO = calcularTendencia(co, diasAnalisis);
    
    // Generar predicciones con factor climatico
    int predPM25 = predecirConClima(pm25, diasAnalisis, tendenciaPM25, clima);
    int predPM10 = predecirConClima(pm10, diasAnalisis, tendenciaPM10, clima);
    int predO3 = predecirConClima(o3, diasAnalisis, tendenciaO3, clima);
    int predNO2 = predecirConClima(no2, diasAnalisis, tendenciaNO2, clima);
    int predSO2 = predecirConClima(so2, diasAnalisis, tendenciaSO2, clima);
    int predCO = predecirConClima(co, diasAnalisis, tendenciaCO, clima);
    
    // Mostrar factor climatico
    float factorClimatico = calcularFactorClimatico(clima);
    printf("Factor climatico aplicado: %.2f %s\n", factorClimatico,
           factorClimatico > 1.1 ? "(Condiciones desfavorables - mayor acumulacion)" :
           factorClimatico < 0.9 ? "(Condiciones favorables - mejor dispersion)" :
           "(Condiciones neutrales)");
    printf("===============================================================================\n");
    
    // Mostrar resultados
    printf("Contaminante\tValor Actual\tTendencia\tPrediccion 24h\tEstado Futuro\n");
    printf("===============================================================================\n");
    
    printf("PM2.5\t\t%d\t\t%.1f\t\t%d\t\t%s\n", 
           pm25[0], tendenciaPM25, predPM25, evaluarContaminante(predPM25, "PM2.5"));
    printf("PM10\t\t%d\t\t%.1f\t\t%d\t\t%s\n", 
           pm10[0], tendenciaPM10, predPM10, evaluarContaminante(predPM10, "PM10"));
    printf("O3\t\t%d\t\t%.1f\t\t%d\t\t%s\n", 
           o3[0], tendenciaO3, predO3, evaluarContaminante(predO3, "O3"));
    printf("NO2\t\t%d\t\t%.1f\t\t%d\t\t%s\n", 
           no2[0], tendenciaNO2, predNO2, evaluarContaminante(predNO2, "NO2"));
    printf("SO2\t\t%d\t\t%.1f\t\t%d\t\t%s\n", 
           so2[0], tendenciaSO2, predSO2, evaluarContaminante(predSO2, "SO2"));
    printf("CO\t\t%d\t\t%.1f\t\t%d\t\t%s\n", 
           co[0], tendenciaCO, predCO, evaluarContaminante(predCO, "CO"));
    
    printf("===============================================================================\n");
    
    // Evaluacion general de la prediccion
    char *estadoFuturo = "BUENO";
    if (strcmp(evaluarContaminante(predPM25, "PM2.5"), "ALTO") == 0 || 
        strcmp(evaluarContaminante(predPM10, "PM10"), "ALTO") == 0 || 
        strcmp(evaluarContaminante(predO3, "O3"), "ALTO") == 0 || 
        strcmp(evaluarContaminante(predNO2, "NO2"), "ALTO") == 0 || 
        strcmp(evaluarContaminante(predSO2, "SO2"), "ALTO") == 0 || 
        strcmp(evaluarContaminante(predCO, "CO"), "ALTO") == 0) {
        estadoFuturo = "ALTO";
    } else if (strcmp(evaluarContaminante(predPM25, "PM2.5"), "MODERADO") == 0 || 
               strcmp(evaluarContaminante(predPM10, "PM10"), "MODERADO") == 0 || 
               strcmp(evaluarContaminante(predO3, "O3"), "MODERADO") == 0 || 
               strcmp(evaluarContaminante(predNO2, "NO2"), "MODERADO") == 0 || 
               strcmp(evaluarContaminante(predSO2, "SO2"), "MODERADO") == 0 || 
               strcmp(evaluarContaminante(predCO, "CO"), "MODERADO") == 0) {
        estadoFuturo = "MODERADO";
    }
    
    printf("\n=== PREDICCION GENERAL PARA MANANA ===\n");
    printf("Estado del aire predicho: %s\n", estadoFuturo);
    
    if (strcmp(estadoFuturo, "ALTO") == 0) {
        printf("\n=== MEDIDAS DE EMERGENCIA RECOMENDADAS ===\n");
        
        // Crear registro temporal con predicciones para mostrar recomendaciones especificas
        struct Registrocotocollao prediccionRegistro;
        strcpy(prediccionRegistro.fecha, "PREDICCION");
        strcpy(prediccionRegistro.zona, nombreZona);
        prediccionRegistro.pm25 = predPM25;
        prediccionRegistro.pm10 = predPM10;
        prediccionRegistro.o3 = predO3;
        prediccionRegistro.no2 = predNO2;
        prediccionRegistro.so2 = predSO2;
        prediccionRegistro.co = predCO;
        
        mostrarRecomendacionesEspecificas(prediccionRegistro);
        
        printf("\nRECOMENDACIONES GENERALES ADICIONALES:\n");
        printf("- Evitar ejercicio al aire libre\n");
        printf("- Usar mascarilla si debe salir\n");
        printf("- Mantener ventanas cerradas\n");
        printf("- Personas con problemas respiratorios deben extremar precauciones\n");
    } else if (strcmp(estadoFuturo, "MODERADO") == 0) {
        printf("RECOMENDACIONES:\n");
        printf("- Limitar actividades prolongadas al aire libre\n");
        printf("- Personas sensibles deben reducir ejercicio intenso\n");
        printf("- Considerar usar mascarilla en areas de mucho trafico\n");
    } else {
        printf("RECOMENDACIONES:\n");
        printf("- Condiciones favorables para actividades al aire libre\n");
        printf("- Calidad del aire dentro de rangos saludables\n");
    }
    
    printf("\nNOTA: Esta prediccion se basa en tendencias de los ultimos 30 dias\n");
    printf("y puede variar debido a factores meteorologicos y eventos imprevistos.\n");
}

void analisisHistorico() {
    printf("\n=== ANALISIS HISTORICO DE CONTAMINACION (30 DIAS) ===\n");
    mostrarMenuAnalisis();
}

void mostrarMenuAnalisis() {
    int zona;
    
    printf("\n=== ANALISIS HISTORICO ===\n");
    printf("Seleccione la zona para analizar promedios de 30 dias:\n");
    mostrarSoloZonas();
    
    printf("Seleccione el numero de la zona urbana (1-5): ");
    scanf("%d", &zona);
    
    if(zona >= 1 && zona <= 5) {
        analizarZonaHistorica(zona);
    } else {
        printf("Numero de zona no valido. Debe estar entre 1 y 5.\n");
    }
}

void analizarZonaHistorica(int numeroZona) {
    char nombreZona[30];
    char archivoActual[50];
    struct Registrocotocollao registros[100];
    int numRegistros;
    
    switch(numeroZona) {
        case 1: 
            strcpy(nombreZona, "Centro"); 
            strcpy(archivoActual, "Centro.txt");
            break;
        case 2: 
            strcpy(nombreZona, "Belisario"); 
            strcpy(archivoActual, "Belisario.txt");
            break;
        case 3: 
            strcpy(nombreZona, "Cotocollao"); 
            strcpy(archivoActual, "Cotocollao (2).txt");
            break;
        case 4: 
            strcpy(nombreZona, "El Camal"); 
            strcpy(archivoActual, "El_Camal.txt");
            break;
        case 5: 
            strcpy(nombreZona, "Tumbaco"); 
            strcpy(archivoActual, "Tumbaco.txt");
            break;
    }
    
    // Cargar todos los datos disponibles
    numRegistros = leerDatosZona(archivoActual, registros, 100);
    
    if (numRegistros > 0) {
        printf("\n=== ANALISIS COMPLETADO ===\n");
        printf("Datos historicos cargados: %d registros (ultimos 30 dias)\n", numRegistros);
        
        calcularPromediosHistoricos(registros, numRegistros, nombreZona);
    } else {
        printf("\nNo se pudieron cargar los datos para %s.\n", nombreZona);
        printf("Asegurese de que el archivo %s existe en el directorio.\n", archivoActual);
    }
}

void calcularPromediosHistoricos(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona) {
    float sumasPM25 = 0, sumasPM10 = 0, sumasO3 = 0, sumasNO2 = 0, sumasSO2 = 0, sumasCO = 0;
    int contPM25 = 0, contPM10 = 0, contO3 = 0, contNO2 = 0, contSO2 = 0, contCO = 0;
    int diasBuenos = 0, diasModerados = 0, diasAltos = 0;
    
    // Calcular sumas y contadores para cada contaminante
    for (int i = 0; i < numRegistros; i++) {
        if (registros[i].pm25 > 0) {
            sumasPM25 += registros[i].pm25;
            contPM25++;
        }
        if (registros[i].pm10 > 0) {
            sumasPM10 += registros[i].pm10;
            contPM10++;
        }
        if (registros[i].o3 > 0) {
            sumasO3 += registros[i].o3;
            contO3++;
        }
        if (registros[i].no2 > 0) {
            sumasNO2 += registros[i].no2;
            contNO2++;
        }
        if (registros[i].so2 > 0) {
            sumasSO2 += registros[i].so2;
            contSO2++;
        }
        if (registros[i].co > 0) {
            sumasCO += registros[i].co;
            contCO++;
        }
        
        // Evaluar estado general del dia
        char *estadoGeneral = "BUENO";
        if (strcmp(evaluarContaminante(registros[i].pm25, "PM2.5"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[i].pm10, "PM10"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[i].o3, "O3"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[i].no2, "NO2"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[i].so2, "SO2"), "ALTO") == 0 || 
            strcmp(evaluarContaminante(registros[i].co, "CO"), "ALTO") == 0) {
            estadoGeneral = "ALTO";
            diasAltos++;
        } else if (strcmp(evaluarContaminante(registros[i].pm25, "PM2.5"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[i].pm10, "PM10"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[i].o3, "O3"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[i].no2, "NO2"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[i].so2, "SO2"), "MODERADO") == 0 || 
                   strcmp(evaluarContaminante(registros[i].co, "CO"), "MODERADO") == 0) {
            estadoGeneral = "MODERADO";
            diasModerados++;
        } else {
            diasBuenos++;
        }
    }
    
    // Calcular promedios
    float promedios[6];
    promedios[0] = (contPM25 > 0) ? sumasPM25 / contPM25 : 0;
    promedios[1] = (contPM10 > 0) ? sumasPM10 / contPM10 : 0;
    promedios[2] = (contO3 > 0) ? sumasO3 / contO3 : 0;
    promedios[3] = (contNO2 > 0) ? sumasNO2 / contNO2 : 0;
    promedios[4] = (contSO2 > 0) ? sumasSO2 / contSO2 : 0;
    promedios[5] = (contCO > 0) ? sumasCO / contCO : 0;
    
    // Mostrar resultados
    printf("\n=== PROMEDIOS HISTORICOS (30 DIAS) - %s ===\n", nombreZona);
    printf("================================================================================\n");
    printf("Contaminante\tPromedio\tDias con datos\tEstado Promedio\tLimite OMS\n");
    printf("================================================================================\n");
    
    if (contPM25 > 0) {
        printf("PM2.5\t\t%.1f\t\t%d\t\t%s\t\t15.0\n", 
               promedios[0], contPM25, evaluarContaminante((int)promedios[0], "PM2.5"));
    }
    if (contPM10 > 0) {
        printf("PM10\t\t%.1f\t\t%d\t\t%s\t\t45.0\n", 
               promedios[1], contPM10, evaluarContaminante((int)promedios[1], "PM10"));
    }
    if (contO3 > 0) {
        printf("O3\t\t%.1f\t\t%d\t\t%s\t\t100.0\n", 
               promedios[2], contO3, evaluarContaminante((int)promedios[2], "O3"));
    }
    if (contNO2 > 0) {
        printf("NO2\t\t%.1f\t\t%d\t\t%s\t\t25.0\n", 
               promedios[3], contNO2, evaluarContaminante((int)promedios[3], "NO2"));
    }
    if (contSO2 > 0) {
        printf("SO2\t\t%.1f\t\t%d\t\t%s\t\t40.0\n", 
               promedios[4], contSO2, evaluarContaminante((int)promedios[4], "SO2"));
    }
    if (contCO > 0) {
        printf("CO\t\t%.1f\t\t%d\t\t%s\t\t4.0\n", 
               promedios[5], contCO, evaluarContaminante((int)promedios[5], "CO"));
    }
    
    printf("================================================================================\n");
    
    // Resumen general
    printf("\n=== RESUMEN HISTORICO (30 DIAS) - %s ===\n", nombreZona);
    printf("Total de dias analizados: %d\n", numRegistros);
    printf("Dias con calidad BUENA: %d (%.1f%%)\n", diasBuenos, (float)diasBuenos/numRegistros*100);
    printf("Dias con calidad MODERADA: %d (%.1f%%)\n", diasModerados, (float)diasModerados/numRegistros*100);
    printf("Dias con calidad ALTA: %d (%.1f%%)\n", diasAltos, (float)diasAltos/numRegistros*100);
    
    // Comparar con limites OMS
    compararConLimitesOMS(promedios, nombreZona);
}

void compararConLimitesOMS(float promedios[], const char* nombreZona) {
    printf("\n=== COMPARACION CON LIMITES OMS ===\n");
    
    int problemasDetectados = 0;
    
    if (promedios[0] > 15) {  // PM2.5
        printf("ALERTA: PM2.5 promedio (%.1f) supera limite OMS (15.0)\n", promedios[0]);
        problemasDetectados++;
    }
    if (promedios[1] > 45) {  // PM10
        printf("ALERTA: PM10 promedio (%.1f) supera limite OMS (45.0)\n", promedios[1]);
        problemasDetectados++;
    }
    if (promedios[2] > 100) {  // O3
        printf("ALERTA: O3 promedio (%.1f) supera limite OMS (100.0)\n", promedios[2]);
        problemasDetectados++;
    }
    if (promedios[3] > 25) {  // NO2
        printf("ALERTA: NO2 promedio (%.1f) supera limite OMS (25.0)\n", promedios[3]);
        problemasDetectados++;
    }
    if (promedios[4] > 40) {  // SO2
        printf("ALERTA: SO2 promedio (%.1f) supera limite OMS (40.0)\n", promedios[4]);
        problemasDetectados++;
    }
    if (promedios[5] > 4) {  // CO
        printf("ALERTA: CO promedio (%.1f) supera limite OMS (4.0)\n", promedios[5]);
        problemasDetectados++;
    }
    
    if (problemasDetectados == 0) {
        printf("BUENAS NOTICIAS: Todos los promedios estan dentro de los limites OMS\n");
        printf("La calidad del aire en %s es generalmente aceptable.\n", nombreZona);
    } else {
        printf("\nSE DETECTARON %d PROBLEMAS DE CALIDAD DEL AIRE\n", problemasDetectados);
        printf("Se recomienda implementar medidas de mitigacion en %s.\n", nombreZona);
    }
}

void mostrarRecomendacionesEspecificas(struct Registrocotocollao registro) {
    printf("\n=== RECOMENDACIONES ESPECIFICAS ===\n");
    
    // Verificar PM2.5
    if (registro.pm25 > 15) {
        printf("\nPM2.5 ALTO (%d μg/m³) - Particulas finas:\n", registro.pm25);
        printf("- Reducir el uso de vehiculos particulares; promover transporte publico\n");
        printf("- Restringir el ingreso de vehiculos a ciertas zonas (pico y placa ambiental)\n");
        printf("- Aumentar zonas verdes y barreras vegetales\n");
        printf("- Suspender actividades fisicas al aire libre en escuelas\n");
        printf("- Controlar quemas agricolas o fuegos a cielo abierto\n");
    }
    
    // Verificar PM10
    if (registro.pm10 > 45) {
        printf("\nPM10 ALTO (%d μg/m³) - Particulas gruesas:\n", registro.pm10);
        printf("- Regar calles sin pavimentar o con polvo visible\n");
        printf("- Detener temporalmente obras de construccion o usar barreras anti-polvo\n");
        printf("- Restringir la circulacion de camiones pesados en zonas urbanas\n");
        printf("- Uso obligatorio de mascarillas en areas expuestas\n");
    }
    
    // Verificar O3
    if (registro.o3 > 100) {
        printf("\nO3 ALTO (%d μg/m³) - Ozono troposferico:\n", registro.o3);
        printf("- Evitar actividades fisicas intensas entre 11 a.m. y 5 p.m.\n");
        printf("- Incentivar el teletrabajo para reducir desplazamientos\n");
        printf("- Disminuir la actividad industrial y el uso de solventes volatiles\n");
        printf("- Emitir alertas a traves de medios y redes sociales\n");
    }
    
    // Verificar NO2
    if (registro.no2 > 25) {
        printf("\nNO2 ALTO (%d μg/m³) - Dioxido de nitrogeno:\n", registro.no2);
        printf("- Prohibir temporalmente la circulacion de vehiculos diesel\n");
        printf("- Fomentar el uso de bicicletas y transporte electrico\n");
        printf("- Controlar emisiones de buses y taxis urbanos\n");
        printf("- Reforzar la vigilancia ambiental en zonas escolares y hospitales\n");
    }
    
    // Verificar SO2
    if (registro.so2 > 40) {
        printf("\nSO2 ALTO (%d μg/m³) - Dioxido de azufre:\n", registro.so2);
        printf("- Suspender actividades industriales con altas emisiones de azufre\n");
        printf("- Supervisar quemas y emisiones de calderas industriales\n");
        printf("- Alertar a personas con asma o enfermedades pulmonares\n");
    }
    
    // Verificar CO
    if (registro.co > 4) {
        printf("\nCO ALTO (%d mg/m³) - Monoxido de carbono:\n", registro.co);
        printf("- Revision tecnica de vehiculos en mal estado\n");
        printf("- Cierre de estacionamientos subterraneos mal ventilados\n");
        printf("- Campanas de ventilacion en hogares e industrias con uso de combustibles\n");
    }
}

void exportarDatos(){
    printf("\n=== EXPORTACION DE DATOS Y REPORTES ===\n");
    mostrarMenuExportacion();
    int opcion;
    printf("Seleccione una opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);
    
    switch(opcion){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            exportarZona(opcion);
            break;
        case 6:
            printf("\nGenerando reporte completo de todas las zonas...\n");
            for(int i = 1; i <= 5; i++){
                exportarZona(i);
            }
            printf("\nReporte completo generado exitosamente!\n");
            break;
        case 7:
            printf("Volviendo al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
    }
}

void mostrarMenuExportacion(){
    printf("\n=== MENU DE EXPORTACION ===\n");
    printf("1. Exportar datos de Centro\n");
    printf("2. Exportar datos de Belisario\n");
    printf("3. Exportar datos de Cotocollao\n");
    printf("4. Exportar datos de El Camal\n");
    printf("5. Exportar datos de Tumbaco\n");
    printf("6. Generar reporte completo de todas las zonas\n");
    printf("7. Volver al menu principal\n");
}

void exportarZona(int numeroZona){
    const char* archivos[] = {"Centro.txt", "Belisario.txt", "Cotocollao (2).txt", "El_Camal.txt", "Tumbaco.txt"};
    const char* nombres[] = {"Centro", "Belisario", "Cotocollao", "El_Camal", "Tumbaco"};
    const char* archivosReporte[] = {"Centro_Reporte.txt", "Belisario_Reporte.txt", "Cotocollao_Reporte.txt", "El_Camal_Reporte.txt", "Tumbaco_Reporte.txt"};
    
    if(numeroZona < 1 || numeroZona > 5){
        printf("Numero de zona invalido.\n");
        return;
    }
    
    struct Registrocotocollao registros[100];
    int numRegistros = leerDatosZona(archivos[numeroZona-1], registros, 100);
    
    if(numRegistros > 0){
        printf("\nGenerando reporte para la zona: %s\n", nombres[numeroZona-1]);
        generarReporte(registros, numRegistros, nombres[numeroZona-1], archivosReporte[numeroZona-1]);
        printf("Reporte generado exitosamente: %s\n", archivosReporte[numeroZona-1]);
    } else {
        printf("No se pudieron leer los datos de la zona %s\n", nombres[numeroZona-1]);
    }
}

void generarReporte(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona, const char* nombreArchivo){
    FILE *archivo = fopen(nombreArchivo, "w");
    if(archivo == NULL){
        printf("Error: No se pudo crear el archivo de reporte %s\n", nombreArchivo);
        return;
    }
    
    // Escribir encabezado del reporte
    fprintf(archivo, "=== REPORTE DE CALIDAD DEL AIRE ===\n");
    fprintf(archivo, "Zona: %s\n", nombreZona);
    fprintf(archivo, "Fecha de generacion: 07/07/2025\n");
    fprintf(archivo, "Periodo analizado: Ultimos 30 dias\n");
    fprintf(archivo, "======================================\n\n");
    
    // Escribir limites OMS 2021
    fprintf(archivo, "LIMITES OMS 2021 (24 horas):\n");
    fprintf(archivo, "- PM2.5: 15 μg/m³\n");
    fprintf(archivo, "- PM10: 45 μg/m³\n");
    fprintf(archivo, "- O3: 100 μg/m³\n");
    fprintf(archivo, "- NO2: 25 μg/m³\n");
    fprintf(archivo, "- SO2: 40 μg/m³\n");
    fprintf(archivo, "- CO: 4 mg/m³\n\n");
    
    // Calcular y escribir promedios
    float sumaPM25 = 0, sumaPM10 = 0, sumaO3 = 0, sumaNO2 = 0, sumaSO2 = 0, sumaCO = 0;
    int contPM25 = 0, contPM10 = 0, contO3 = 0, contNO2 = 0, contSO2 = 0, contCO = 0;
    int diasBuenos = 0, diasModerados = 0, diasAltos = 0;
    
    for(int i = 0; i < numRegistros; i++){
        if(registros[i].pm25 > 0){
            sumaPM25 += registros[i].pm25;
            contPM25++;
        }
        if(registros[i].pm10 > 0){
            sumaPM10 += registros[i].pm10;
            contPM10++;
        }
        if(registros[i].o3 > 0){
            sumaO3 += registros[i].o3;
            contO3++;
        }
        if(registros[i].no2 > 0){
            sumaNO2 += registros[i].no2;
            contNO2++;
        }
        if(registros[i].so2 > 0){
            sumaSO2 += registros[i].so2;
            contSO2++;
        }
        if(registros[i].co > 0){
            sumaCO += registros[i].co;
            contCO++;
        }
        
        // Evaluar calidad del dia
        int excesosAltos = 0;
        int excesosLeves = 0;
        
        if(registros[i].pm25 > 15) excesosAltos++;
        else if(registros[i].pm25 > 10) excesosLeves++;
        
        if(registros[i].pm10 > 45) excesosAltos++;
        else if(registros[i].pm10 > 30) excesosLeves++;
        
        if(registros[i].o3 > 100) excesosAltos++;
        else if(registros[i].o3 > 80) excesosLeves++;
        
        if(registros[i].no2 > 25) excesosAltos++;
        else if(registros[i].no2 > 20) excesosLeves++;
        
        if(registros[i].so2 > 40) excesosAltos++;
        else if(registros[i].so2 > 30) excesosLeves++;
        
        if(registros[i].co > 4) excesosAltos++;
        else if(registros[i].co > 3) excesosLeves++;
        
        if(excesosAltos > 0){
            diasAltos++;
        } else if(excesosLeves > 0){
            diasModerados++;
        } else {
            diasBuenos++;
        }
    }
    
    // Escribir promedios
    fprintf(archivo, "PROMEDIOS DE 30 DIAS:\n");
    fprintf(archivo, "- PM2.5: %.1f μg/m³", contPM25 > 0 ? sumaPM25/contPM25 : 0);
    if(contPM25 > 0) fprintf(archivo, " %s", (sumaPM25/contPM25) > 15 ? "(EXCEDE LIMITE OMS)" : "(DENTRO DEL LIMITE)");
    fprintf(archivo, "\n");
    
    fprintf(archivo, "- PM10: %.1f μg/m³", contPM10 > 0 ? sumaPM10/contPM10 : 0);
    if(contPM10 > 0) fprintf(archivo, " %s", (sumaPM10/contPM10) > 45 ? "(EXCEDE LIMITE OMS)" : "(DENTRO DEL LIMITE)");
    fprintf(archivo, "\n");
    
    fprintf(archivo, "- O3: %.1f μg/m³", contO3 > 0 ? sumaO3/contO3 : 0);
    if(contO3 > 0) fprintf(archivo, " %s", (sumaO3/contO3) > 100 ? "(EXCEDE LIMITE OMS)" : "(DENTRO DEL LIMITE)");
    fprintf(archivo, "\n");
    
    fprintf(archivo, "- NO2: %.1f μg/m³", contNO2 > 0 ? sumaNO2/contNO2 : 0);
    if(contNO2 > 0) fprintf(archivo, " %s", (sumaNO2/contNO2) > 25 ? "(EXCEDE LIMITE OMS)" : "(DENTRO DEL LIMITE)");
    fprintf(archivo, "\n");
    
    fprintf(archivo, "- SO2: %.1f μg/m³", contSO2 > 0 ? sumaSO2/contSO2 : 0);
    if(contSO2 > 0) fprintf(archivo, " %s", (sumaSO2/contSO2) > 40 ? "(EXCEDE LIMITE OMS)" : "(DENTRO DEL LIMITE)");
    fprintf(archivo, "\n");
    
    fprintf(archivo, "- CO: %.1f mg/m³", contCO > 0 ? sumaCO/contCO : 0);
    if(contCO > 0) fprintf(archivo, " %s", (sumaCO/contCO) > 4 ? "(EXCEDE LIMITE OMS)" : "(DENTRO DEL LIMITE)");
    fprintf(archivo, "\n\n");
    
    // Escribir resumen de calidad del aire
    fprintf(archivo, "RESUMEN DE CALIDAD DEL AIRE (30 DIAS):\n");
    fprintf(archivo, "- Dias con calidad BUENA: %d\n", diasBuenos);
    fprintf(archivo, "- Dias con calidad MODERADA: %d\n", diasModerados);
    fprintf(archivo, "- Dias con calidad ALTA/PELIGROSA: %d\n", diasAltos);
    fprintf(archivo, "- Total de dias analizados: %d\n\n", numRegistros);
    
    // Escribir datos detallados (ultimos 10 dias)
    fprintf(archivo, "DATOS DETALLADOS (ULTIMOS 10 DIAS):\n");
    fprintf(archivo, "Fecha\t\tPM2.5\tPM10\tO3\tNO2\tSO2\tCO\n");
    fprintf(archivo, "------------------------------------------------------------\n");
    
    int limite = numRegistros > 10 ? 10 : numRegistros;
    for(int i = 0; i < limite; i++){
        fprintf(archivo, "%s\t", registros[i].fecha);
        fprintf(archivo, "%d\t", registros[i].pm25);
        fprintf(archivo, "%d\t", registros[i].pm10);
        fprintf(archivo, "%d\t", registros[i].o3);
        fprintf(archivo, "%d\t", registros[i].no2);
        fprintf(archivo, "%d\t", registros[i].so2);
        fprintf(archivo, "%d\n", registros[i].co);
    }
    
    // Escribir recomendaciones
    fprintf(archivo, "\nRECOMENDACIONES GENERALES:\n");
    
    if(diasAltos > 5){
        fprintf(archivo, "- ALERTA: La zona presenta frecuentes excesos de contaminantes\n");
        fprintf(archivo, "- Se recomienda implementar medidas urgentes de control\n");
        fprintf(archivo, "- Evitar actividades fisicas intensas al aire libre\n");
        fprintf(archivo, "- Usar mascarillas en dias de alta contaminacion\n");
    } else if(diasModerados > 10){
        fprintf(archivo, "- La zona presenta contaminacion moderada frecuente\n");
        fprintf(archivo, "- Se recomienda monitoreo continuo y medidas preventivas\n");
        fprintf(archivo, "- Limitar actividades al aire libre en horas pico\n");
    } else {
        fprintf(archivo, "- La zona presenta buena calidad del aire en general\n");
        fprintf(archivo, "- Continuar con el monitoreo regular\n");
        fprintf(archivo, "- Mantener las medidas de control existentes\n");
    }
    
    fprintf(archivo, "\n=== FIN DEL REPORTE ===\n");
    fclose(archivo);
}

// Array global para almacenar datos climaticos
struct DatosClimaticos datosClimaticos[5];

// Funciones para manejo de datos climaticos
void inicializarDatosClimaticos(){
    strcpy(datosClimaticos[0].zona, "Centro");
    datosClimaticos[0].temperatura = 13.0;
    datosClimaticos[0].presion = 1028.0;
    datosClimaticos[0].humedad = 87.0;
    
    strcpy(datosClimaticos[1].zona, "Belisario");
    datosClimaticos[1].temperatura = 13.0;
    datosClimaticos[1].presion = 1028.0;
    datosClimaticos[1].humedad = 87.0;
    
    strcpy(datosClimaticos[2].zona, "Cotocollao");
    datosClimaticos[2].temperatura = 13.0;
    datosClimaticos[2].presion = 1028.0;
    datosClimaticos[2].humedad = 87.0;
    
    strcpy(datosClimaticos[3].zona, "El_Camal");
    datosClimaticos[3].temperatura = 13.0;
    datosClimaticos[3].presion = 1028.0;
    datosClimaticos[3].humedad = 87.0;
    
    strcpy(datosClimaticos[4].zona, "Tumbaco");
    datosClimaticos[4].temperatura = 13.0;
    datosClimaticos[4].presion = 1028.0;
    datosClimaticos[4].humedad = 87.0;
}

void mostrarDatosClimaticos(){
    printf("\n=== DATOS CLIMATICOS ACTUALES ===\n");
    printf("Zona\t\tTemp(°C)\tPresion(hPa)\tHumedad(%%)\n");
    printf("================================================\n");
    for(int i = 0; i < 5; i++){
        printf("%-12s\t%.1f\t\t%.0f\t\t%.0f\n", 
               datosClimaticos[i].zona,
               datosClimaticos[i].temperatura,
               datosClimaticos[i].presion,
               datosClimaticos[i].humedad);
    }
    printf("================================================\n");
}

struct DatosClimaticos obtenerDatosClimaticos(const char* nombreZona){
    for(int i = 0; i < 5; i++){
        if(strcmp(datosClimaticos[i].zona, nombreZona) == 0){
            return datosClimaticos[i];
        }
    }
    // Retornar datos por defecto si no se encuentra la zona
    struct DatosClimaticos defecto = {"Desconocida", 13.0, 1028.0, 87.0};
    return defecto;
}

float calcularFactorClimatico(struct DatosClimaticos clima){
    // Factor basado en condiciones climaticas
    // Temperatura baja + humedad alta + presion alta = mas contaminacion (inversion termica)
    // Temperatura alta + humedad baja + presion baja = menos contaminacion (dispersion)
    
    float factorTemp = 1.0;
    float factorHumedad = 1.0;
    float factorPresion = 1.0;
    
    // Temperatura (°C) - temperaturas bajas favorecen acumulacion
    if(clima.temperatura < 10) factorTemp = 1.3;
    else if(clima.temperatura < 15) factorTemp = 1.1;
    else if(clima.temperatura > 25) factorTemp = 0.8;
    
    // Humedad (%) - humedad alta favorece acumulacion
    if(clima.humedad > 80) factorHumedad = 1.2;
    else if(clima.humedad > 60) factorHumedad = 1.0;
    else factorHumedad = 0.9;
    
    // Presion (hPa) - presion alta favorece acumulacion
    if(clima.presion > 1020) factorPresion = 1.1;
    else if(clima.presion < 1000) factorPresion = 0.9;
    
    return factorTemp * factorHumedad * factorPresion;
}

int predecirConClima(int valoresRecientes[], int numValores, float tendencia, struct DatosClimaticos clima){
    if(numValores == 0) return 0;
    
    // Prediccion base
    int valorBase = valoresRecientes[0]; // Ultimo valor
    int prediccionBase = valorBase + (int)(tendencia * 1.5);
    
    // Aplicar factor climatico
    float factorClimatico = calcularFactorClimatico(clima);
    int prediccionFinal = (int)(prediccionBase * factorClimatico);
    
    // Limites de seguridad
    if(prediccionFinal < 0) prediccionFinal = 0;
    if(prediccionFinal > valorBase * 3) prediccionFinal = valorBase * 3;
    
    return prediccionFinal;
}