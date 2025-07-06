#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main (int argc, char *argv[]) {
    int opcion;
    
    do {
        opcion = menu();
        
        switch(opcion) {
            case 1:
                mostrarDatosContaminacion();
                break;
                
            case 2:
                printf("Saliendo del programa...\n");
                break;
                
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
        
        if (opcion != 2) {
            printf("\nPresione Enter para continuar");
            getchar(); 
            getchar(); 
        }
        
    } while (opcion != 2);
    
    return 0;
}