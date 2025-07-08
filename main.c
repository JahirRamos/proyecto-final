#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main (int argc, char *argv[]) {
    int opcion;
    
    // Inicializar datos climaticos al inicio del programa
    inicializarDatosClimaticos();
    
    do {
        opcion = menu();
        
        switch(opcion) {
            case 1:
                mostrarDatosContaminacion();
                break;
                
            case 2:
                prediccionNivelesFuturos();
                break;
                
            case 3:
                analisisHistorico();
                break;
                
            case 4:
                exportarDatos();
                break;
                
            case 5:
                mostrarDatosClimaticos();
                break;
                
            case 6:
                printf("Saliendo del programa...\n");
                break;
                
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
        
        if (opcion != 6) {
            printf("\nPresione Enter para continuar");
            getchar(); 
            getchar(); 
        }
        
    } while (opcion != 6);
    
    return 0;
}