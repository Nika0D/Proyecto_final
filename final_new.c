#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ingrediente
{
    char nombre[50];
    float precio;
};
struct ingrediente_receta
{
    int cantidad;
    struct ingrediente ingrediente;
};
struct receta
{
    float precio;
    char nombre[50];
    int cantidad_ingredientes;
    struct ingrediente_receta ingredientes[50];
    float costo;
};
void leerArchivo(char *fileName, char *matriz[100][100])
{
    FILE *archivo;
    char caracter;
    char data[1000];
    int contador_data = 0;
    int fila = 0;
    int columna = 0;
    archivo = fopen(fileName, "r");

    while (!feof(archivo))
    {
        caracter = fgetc(archivo);
        data[contador_data++] = caracter;
    }

    fclose(archivo);
    data[contador_data] = '\000';

    matriz[0][0] = &data[0];
    for (int i = 1; i < contador_data; i++)
    {
        char c = data[i];

        if (c == '\377')
        {
            matriz[fila][columna] = '\000';
            break;
        }
        else if (c == ',')
        {
            data[i] = '\000';
            matriz[fila][++columna] = &data[i + 1];
        }
        else if (c == '\n')
        {
            data[i] = '\000';
            columna = 0;
            fila++;
            matriz[fila][columna] = &data[i + 1];
        }
    }
}
int main(int argc, char const *argv[])
{
    int caracteres = 100;
    char str[caracteres];
    char *matriz[100][100];
    char *matriz_receta[100][100];
    struct ingrediente ingredientes[50];
    struct receta recetas_array[50];
    int cantidad_recetas = 0;

    FILE *puntero;
    FILE *recetas;
    int num, cantidad, num_ingrediente, salir = 1;
    float precioi;
    char ingrediente[50];
    char result[50];
    char nombre_reseta[50];
    float precio_pori, precio = 0;
    float *arreglo2[30];
    do
    {
        printf("presione 0 para añadir nuevos ingrdientes\n");
        printf("presione 1 para añadir una reseta\n");
        printf("presione 2 para contavilisar platos\n");
        scanf("%d", &num);
        switch (num)
        {
        case 0:
            puntero = fopen("ingredientes.txt", "a");
            do
            {
                printf("nombre del ingrediente\n");
                scanf("%s", &ingrediente);
                printf("Preciodel ingrediente\n");
                scanf("%f", &precioi);
                sprintf(result, "%s,%.2f\n", ingrediente, precioi);
                printf("%s", result);
                fputs(result, puntero);
                printf("Salir=1, seguir =0\n");
                scanf("%d", &salir);
            } while (salir == 0);
            fclose(puntero);
            break;
        case 1:
            printf("nombre de la reseta\n");
            scanf("%s", &nombre_reseta);
            recetas_array[cantidad_recetas].cantidad_ingredientes = 0;
            recetas_array[cantidad_recetas].costo = 0;
            strcpy(recetas_array[cantidad_recetas].nombre, nombre_reseta);
            leerArchivo("ingredientes.txt", matriz);
            for (int j = 0; j < salir; j++)
            {
                if (matriz[j][0] != NULL)
                {
                    printf("%d %s\n", j + 1, matriz[j][0]);
                    strcpy(ingredientes[j].nombre, matriz[j][0]);
                    sscanf(matriz[j][1], "%f", &ingredientes[j].precio);
                    salir++;
                }
            }
            salir = 1;
            do
            {
                printf("Elige el ingrediente; -1 para terminar\n");
                scanf("%d", &num_ingrediente);
                if (num_ingrediente < 1)
                {
                    break;
                }

                printf("Elige la cantidad \n");
                scanf("%d", &cantidad);

                num_ingrediente--;

                if (ingredientes[num_ingrediente].precio == 0)
                {
                    printf("Ingrediente no existe\n");
                }
                else
                {
                    precio_pori = ingredientes[num_ingrediente].precio * cantidad;
                    recetas_array[cantidad_recetas].ingredientes[recetas_array[cantidad_recetas].cantidad_ingredientes].cantidad = cantidad;
                    recetas_array[cantidad_recetas].ingredientes[recetas_array[cantidad_recetas].cantidad_ingredientes++].ingrediente = ingredientes[num_ingrediente];
                    recetas_array[cantidad_recetas].costo += precio_pori;
                    printf("%d %.2f\n", num_ingrediente + 1, precio_pori);
                }

            } while (num_ingrediente >= 0);
            do
            {
                printf("La reseta cuesta: %f cuanto desea cobrar: \n", recetas_array[cantidad_recetas].costo);
                scanf("%f", &precioi);
                recetas_array[cantidad_recetas].precio = precioi;
                printf("la ganancia es de: %f\n", (precioi * 0.78) - recetas_array[cantidad_recetas].costo);
                printf("Desea guardar el precio 1=si 0=no\n");
                scanf("%d", &salir);
            } while (salir == 0);

            recetas = fopen("recetas.txt", "a");
            char cadena_ingredientes[100];
            for (int i = 0; i < recetas_array[cantidad_recetas].cantidad_ingredientes; i++)
            {
                char pareja[100];
                sprintf(pareja, ",%s,%d", recetas_array[cantidad_recetas].ingredientes[i].ingrediente.nombre, recetas_array[cantidad_recetas].ingredientes[i].cantidad);
                strcat(&cadena_ingredientes, &pareja);
            }

            char tosave[100];
            sprintf(tosave, "%s,%.2f%s\n", recetas_array[cantidad_recetas].nombre, recetas_array[cantidad_recetas].precio, cadena_ingredientes);
            printf("%s\n", tosave);
            fputs(tosave, recetas);
            fclose(recetas);
            cantidad_recetas++;
            break;
        case 2:
            int num_new;
            char arreglo_caja[100];
            float calculo;
            salir = 0;
            int cont = 0;
            float preciot = 0;
            do
            {
                printf("Numero de la receta\n");
                scanf("%d", &num_new);
                printf("Cantidad \n");
                scanf("%d", &cantidad);
                leerArchivo("recetas.txt", matriz);
                sscanf(matriz[num_new - 1][1], "%f", &calculo);
                calculo = calculo * cantidad;
                sscanf(matriz[num_new - 1][0], "%s", nombre_reseta);
                sprintf(arreglo_caja, "%s,%.2f\n", nombre_reseta, calculo);
                printf("%s", arreglo_caja);
                preciot = preciot + calculo;
                cont++;
                printf("Terminar =1, continuar pedido=0\n");
                scanf("%d", &salir);
            } while (salir == 0);
            printf("%f\n", preciot);
            break;
        default:
            break;
        }
    } while (salir == 1);
    return 0;
}