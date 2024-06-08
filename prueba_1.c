#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTROS 50
#define MAX_CHAR 50

typedef struct {
    char marca[MAX_CHAR];
    char submarca[MAX_CHAR];
    int modelo;
    char placas[MAX_CHAR];
    char color[MAX_CHAR];
    char num_serie[MAX_CHAR];
    char fecha_in[MAX_CHAR];
    char fecha_out[MAX_CHAR];
}Carro;

Carro auto_registro[MAX_REGISTROS];
int num_registros = 0;

int menu();
//char* crear_archivo();
void agregar_carro();
void arch_bin(const char* filename);
void cargar();
void save_info();
void mostrar_registro();
void eliminar_dato();
void modificar_dato();
void clear();

int main(){

    int op;
    char bin_filename[] = "carros.bin";//no es necesario que el usuario sepa cual es.
    //char csv_filename[MAX_CHAR];//para que el usuario le ponga nombre :)

    do{
        clear();
        op=menu();
        getchar();

        switch(op)
        {
            case 1: //Crear archivo nuevo
                arch_bin(bin_filename);
                break;
            case 2://Agregar registro del carro
                agregar_carro();//esta funcion ya esta al 100.
                cargar(bin_filename);
                break;
            case 3://Mostrar registros del carro
                mostrar_registro(bin_filename);
                break;
            case 4://Modificar registro el carro
                break;
            case 5://Eliminar registro del carro
                break;
            case 6: //salir
                printf("Saliendo del programa. %cHasta luego!\n", 173);
                break;
            default://agrega un numero que no esta en las opciones
                printf("\nOpci%cn invalida", 163);
        }
    }while(op!=6);

    getchar();
    return 0;
}

int menu(){
    int opcion;

    printf("Menu:\n");
    printf("\n1. Crear Archivo Nuevo");
    printf("\n2. Agregar registro del carro");
    printf("\n3. Mostrar registros del carro");
    printf("\n4. Modificar registro el carro");
    printf("\n5. Eliminar registro del carro");
    printf("\n6. Salir");
    printf("\nIngrese opcion:");
    scanf("%d" , &opcion);
    
    return opcion;
}

/*char* crear_archivo(){
    clear();

    static char filename[MAX_CHAR];

    printf("\nIngres el nombre del archivo: ");
    fgets(filename,MAX_CHAR,stdin);
    
    strcat(filename, ".csv");

    FILE *archivo = fopen(filename, "w");
    if (archivo != NULL){
        fprintf(archivo, "Marca, SubMarca, Modelo, Placa, Color, N%cmero de serie, Fecha de Entrada, Fecha de Salida\n", 163);
    }
    fclose(archivo);

    return filename;
}*/

void agregar_carro(){
    clear();
    if(num_registros >= MAX_REGISTROS){
        printf("\nMaximo de registros");
        return;
    }
    printf("<------------Ingrese informaci%cn del Veh%cculo------------>\n", 162, 161);
   
    printf("Marca: ");
    fgets(auto_registro[num_registros].marca, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].marca, "\n");

    printf("SubMarca: ");
    fgets(auto_registro[num_registros].submarca, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].submarca, "\n");

    printf("Modelo: ");
    char modelo_str[MAX_CHAR];
    fgets(modelo_str, MAX_CHAR, stdin);
    sscanf(modelo_str, "%d", &auto_registro[num_registros].modelo);//Para que se guarde en entero :)

    printf("Placas: ");
    fgets(auto_registro[num_registros].placas, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].placas, "\n");

    printf("Color: ");
    fgets(auto_registro[num_registros].color, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].color, "\n");

    printf("N%cmero de serie: ", 163);
    fgets(auto_registro[num_registros].num_serie, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].num_serie, "\n");

    printf("Fecha de Entrada: (DD/MM/AAAA)");
    fgets(auto_registro[num_registros].fecha_in, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].fecha_in, "\n");

    printf("Fecha de Salida: (DD/MM/AAAA)");
    fgets(auto_registro[num_registros].fecha_out, MAX_CHAR, stdin);
    strtok(auto_registro[num_registros].fecha_out, "\n");
    
    num_registros ++;
}

void arch_bin(const char* filename){
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL){
        perror("Error al abrir el archivo binario...\n");
        exit(1);
    }

    fclose(fp);
}

void cargar(const char* filename){

    FILE* fp = fopen(filename, "ab");
    if(fp == NULL){
        perror("Error al abrir el archivo binario...\n");
        exit(1);
    }
    
    fwrite(&auto_registro[num_registros - 1], sizeof(Carro), 1, fp);
    fclose(fp);

    printf("\nDatos guardados en el archivo binario %s.\n", filename);
    getchar();
}

void save_info(const char* filename){
    FILE *archivo = fopen(filename, "wb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    fprintf(archivo, "%s, %s, %d, %s, %s, %s, %s, %s", auto_registro[MAX_REGISTROS].marca, auto_registro[MAX_REGISTROS].submarca,
    auto_registro[MAX_REGISTROS].modelo, auto_registro[MAX_REGISTROS].placas, auto_registro[MAX_REGISTROS].color,
    auto_registro[MAX_REGISTROS].num_serie, auto_registro[MAX_REGISTROS].fecha_in, auto_registro[MAX_REGISTROS].fecha_out);
    printf("\nVeh%cculo agregado exitosamente", 161);
    
    fclose(archivo);
}

void mostrar_registro(const char* filename) {
    clear();
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error al abrir el archivo binario");
        exit(1);
    } else {
        printf("Apertura de archivo exitosa.\n");
    }
    
    printf("<---------------Información ingresada--------------->\n");

    Carro carro;
    while (fread(&carro, sizeof(Carro), 1, fp) == 1) {
        printf("Marca: %s\n", carro.marca);
        printf("SubMarca: %s\n", carro.submarca);
        printf("Modelo: %d\n", carro.modelo);
        printf("Placas: %s\n", carro.placas);
        printf("Color: %s\n", carro.color);
        printf("Número de serie: %s\n", carro.num_serie);
        printf("Fecha de Entrada: %s\n", carro.fecha_in);
        printf("Fecha de Salida: %s\n", carro.fecha_out);
        printf("\n");
    }

    fclose(fp);
    getchar();
}

void clear(){
    printf("\033[2J"); // Codigo ANSI para limpiar la pantalla
    printf("\033[1;1H"); // Mover el cursor al inicio de la pantalla
}