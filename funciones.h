struct Registrocotocollao{
    char zona[30];
    char fecha[20];
    int pm25;
    int pm10;
    int o3;
    int no2;
    int so2;
    int co;

};

// Funciones para manejo de archivos CSV
int leerCSV(const char* nombreArchivo, struct Registrocotocollao registros[], int maxRegistros);
void mostrarRegistro(struct Registrocotocollao registro);
void mostrarTodosRegistros(struct Registrocotocollao registros[], int numRegistros);
int escribirCSV(const char* nombreArchivo, struct Registrocotocollao registros[], int numRegistros);

// Función del menú
int menu();

// Función para leer cadenas
void leercadena(char *cadena, int num);

// Función para mostrar zonas urbanas
void mostrarZonasUrbanas();
void mostrarSoloZonas();

// Función para mostrar datos de contaminación
void mostrarDatosContaminacion();
void mostrarDatosZona(int numeroZona);

// Funciones para leer archivos CSV
int leerDatosZona(const char* nombreArchivo, struct Registrocotocollao registros[], int maxRegistros);
void mostrarDatosArchivo(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona);