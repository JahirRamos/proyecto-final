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

// Estructura para datos climaticos
struct DatosClimaticos{
    char zona[30];
    float temperatura;
    float presion;
    float humedad;
};

// Funciones para manejo de archivos TXT
int leerCSV(const char* nombreArchivo, struct Registrocotocollao registros[], int maxRegistros);
void mostrarRegistro(struct Registrocotocollao registro);
void mostrarTodosRegistros(struct Registrocotocollao registros[], int numRegistros);
int escribirCSV(const char* nombreArchivo, struct Registrocotocollao registros[], int numRegistros);

// Funcion del menu
int menu();

// Funcion para leer cadenas
void leercadena(char *cadena, int num);

// Funcion para mostrar zonas urbanas
void mostrarZonasUrbanas();
void mostrarSoloZonas();

// Funcion para mostrar datos de contaminacion
void mostrarDatosContaminacion();
void mostrarDatosZona(int numeroZona);

// Funciones para leer archivos TXT
int leerDatosZona(const char* nombreArchivo, struct Registrocotocollao registros[], int maxRegistros);
void mostrarDatosArchivo(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona);

// Funcion para mostrar limites aceptables de contaminantes
void mostrarLimitesAceptables();

// Funcion para evaluar estado de contaminante individual
char* evaluarContaminante(int valor, const char* tipo);

// Funcion para mostrar recomendaciones especificas por contaminante
void mostrarRecomendacionesEspecificas(struct Registrocotocollao registro);

// Funciones para prediccion de niveles futuros
void prediccionNivelesFuturos();
void mostrarMenuPrediccion();
void predecirZona(int numeroZona);
float calcularTendencia(int valores[], int numValores);
int predecirProximoValor(int valoresRecientes[], int numValores, float tendencia);
void mostrarPrediccion24h(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona);

// Funciones para analisis historico (30 dias)
void analisisHistorico();
void mostrarMenuAnalisis();
void analizarZonaHistorica(int numeroZona);
void calcularPromediosHistoricos(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona);
void compararConLimitesOMS(float promedios[], const char* nombreZona);

// Funciones para exportacion de datos
void exportarDatos();
void mostrarMenuExportacion();
void exportarZona(int numeroZona);
void generarReporte(struct Registrocotocollao registros[], int numRegistros, const char* nombreZona, const char* nombreArchivo);

// Funciones para manejo de datos climaticos
void inicializarDatosClimaticos();
void mostrarDatosClimaticos();
struct DatosClimaticos obtenerDatosClimaticos(const char* nombreZona);
float calcularFactorClimatico(struct DatosClimaticos clima);
int predecirConClima(int valoresRecientes[], int numValores, float tendencia, struct DatosClimaticos clima);