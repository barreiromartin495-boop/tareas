#include <stdio.h>
#include <string.h>

#define MAX 5

void menu();
void agregar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int *total);
int buscar(char nombres[][50], int total, char nb[]);
void editar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int total);
void eliminar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int *total);
void mostrar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int total);
void calcular(float tiempos[], int recursos[], int cantidades[], int total, float hDisp, int rDisp);

int main(){
    char nombres[MAX][50];
    float tiempos[MAX];
    int recursos[MAX];
    int cantidades[MAX];
    int total = 0;
    int op;
    float horas;
    int rec;

    printf("=== FABRICA DE COMPONENTES ===\n");
    printf("ingrese las horas disponibles: ");
    scanf("%f", &horas);
    printf("ingrese los recursos disponibles: ");
    scanf("%d", &rec);

    do {
        menu();
        scanf("%d", &op);

        if(op == 1)
            agregar(nombres, tiempos, recursos, cantidades, &total);
        else if(op == 2)
            editar(nombres, tiempos, recursos, cantidades, total);
        else if(op == 3)
            eliminar(nombres, tiempos, recursos, cantidades, &total);
        else if(op == 4)
            mostrar(nombres, tiempos, recursos, cantidades, total);
        else if(op == 5)
            calcular(tiempos, recursos, cantidades, total, horas, rec);
        else if(op == 6)
            printf("saliendo...\n");
        else
            printf("opcion no valida\n");

    } while(op != 6);

    return 0;
}

void menu(){
    printf("\n1- agregar producto\n");
    printf("2- editar producto\n");
    printf("3- eliminar producto\n");
    printf("4- ver productos\n");
    printf("5- calcular\n");
    printf("6- salir\n");
    printf("opcion: ");
}

void agregar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int *total){
    char nb[50];
    float t;
    int r, c;

    if(*total >= MAX){
        printf("no se pueden agregar mas\n");
        return;
    }

    printf("nombre del producto: ");
    scanf(" %s", nb);

    if(buscar(nombres, *total, nb) >= 0){
        printf("ya existe ese producto\n");
        return;  /* FIX: sin (*total)-- porque *total nunca se incremento */
    }

    printf("tiempo de fabricacion: ");
    scanf("%f", &t);
    printf("recursos necesarios: ");
    scanf("%d", &r);
    printf("cantidad demandada: ");
    scanf("%d", &c);

    strcpy(nombres[*total], nb);
    tiempos[*total] = t;
    recursos[*total] = r;
    cantidades[*total] = c;
    (*total)++;

    printf("producto guardado\n");
}

int buscar(char nombres[][50], int total, char nb[]){
    int i;
    for(i = 0; i < total; i++){
        if(strcmp(nombres[i], nb) == 0)
            return i;
    }
    return -1;
}

void editar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int total){
    char nb[50];
    int pos, op2;

    if(total == 0){
        printf("no hay productos cargados\n");
        return;
    }

    printf("nombre del producto a editar: ");
    scanf(" %s", nb);

    pos = buscar(nombres, total, nb);
    if(pos == -1){
        printf("no existe\n");
        return;
    }

    printf("1-nombre 2-tiempo 3-recursos 4-cantidad\n");
    scanf("%d", &op2);

    if(op2 == 1){
        printf("nuevo nombre: ");
        scanf(" %s", nombres[pos]);
    } else if(op2 == 2){
        printf("nuevo tiempo: ");
        scanf("%f", &tiempos[pos]);
    } else if(op2 == 3){
        printf("nuevos recursos: ");
        scanf("%d", &recursos[pos]);
    } else if(op2 == 4){
        printf("nueva cantidad: ");
        scanf("%d", &cantidades[pos]);
    }

    printf("listo\n");
}

void eliminar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int *total){
    char nb[50];
    int pos, j;

    if(*total == 0){
        printf("lista vacia\n");
        return;
    }

    printf("nombre a eliminar: ");
    scanf(" %s", nb);

    pos = buscar(nombres, *total, nb);
    if(pos == -1){
        printf("no se encontro\n");
        return;
    }

    for(j = pos; j < *total - 1; j++){
        strcpy(nombres[j], nombres[j+1]);
        tiempos[j] = tiempos[j+1];
        recursos[j] = recursos[j+1];
        cantidades[j] = cantidades[j+1];
    }

    (*total)--;
    printf("eliminado\n");
}

void mostrar(char nombres[][50], float tiempos[], int recursos[], int cantidades[], int total){
    int i;

    if(total == 0){
        printf("no hay nada cargado\n");
        return;
    }

    for(i = 0; i < total; i++){
        printf("%d) %s | tiempo: %.2f | recursos: %d | cantidad: %d\n",
               i+1, nombres[i], tiempos[i], recursos[i], cantidades[i]);
    }
}

void calcular(float tiempos[], int recursos[], int cantidades[], int total, float hDisp, int rDisp){
    int i;
    float hTotal = 0;
    int rTotal = 0;

    if(total == 0){
        printf("no hay productos\n");
        return;
    }

    for(i = 0; i < total; i++){
        hTotal = hTotal + (tiempos[i] * cantidades[i]);
        rTotal = rTotal + (recursos[i] * cantidades[i]);
    }

    printf("horas requeridas: %.2f / disponibles: %.2f\n", hTotal, hDisp);
    printf("recursos requeridos: %d / disponibles: %d\n", rTotal, rDisp);

    if(hTotal <= hDisp && rTotal <= rDisp){
        printf("se puede producir todo\n");
    } else {
        printf("no alcanza\n");
        if(hTotal > hDisp)
            printf("faltan %.2f horas\n", hTotal - hDisp);
        if(rTotal > rDisp)
            printf("faltan %d recursos\n", rTotal - rDisp);
    }
}
