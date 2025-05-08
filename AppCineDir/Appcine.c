#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Aplicacion cine:
void ElegirAsiento(int Sala[10][15], int sala, int ID);
void MostrarAsientos(int esAdmin,int Sala[10][15],int sala);
int ElegirSala(void);


void ElegirAsiento(int Sala[10][15],int sala, int ID){
    int numasientos=0;
    char asiento[4];
    int fila=0;
    int columna=0;
    MostrarAsientos(0,Sala,sala);
    printf("Elige numero de asientos: \n");
    scanf("%i",&numasientos);
    //se repite petición de ingreso de asiento el número de asientos elegidos
    for(int i=0; i<numasientos;i++){
        do{
        printf("Ingresa el asiento elegido\n");
        scanf("%s",asiento);
        //Conversión de valor de fila a número
        fila=(int)asiento[0] - 'a';
        //Se usa la función atoi para convertir valor a partir de asiento[1]
        //Se le resta 1 por que inicia en cero la cuenta
        columna=atoi(&asiento[1])-1;
        //Si el asiento está ocupado, vuelve a pedir ingresar asiento
        if(Sala[fila][columna]>0){
            printf("Asiento ocupado, ingrese otro\n");
        }
        }while(Sala[fila][columna]>0);
        //Asigna a la sala, fila y columnas correspondientes el ID actual del usuario
        Sala[fila][columna]=ID;

    }
    //Limpia pantalla (usar system("cls"); para Windows)
    system("clear");
    printf("Lugares apartados, gracias por su compra\n");
}

void MostrarAsientos(int esAdmin,int Sala[10][15],int sala){
    //Imprimir información de sala
    printf("Asientos de la sala %i: Disponible (0) Ocupado (1)\n",sala);
    printf("                           P A N T A L L A\n\n   ");
    //Imprimir fila de números de columna
    for(int i=0; i<15;i++){
        printf("%02.0f   ",(float)(i+1));
    }
    printf("\n");
    for(int i=0; i<10;i++){
        //Imprimir filas de asientos
        printf("%c  ",'a'+i);
        for(int j=0;j<15;j++){
            if(Sala[i][j]>0){
                //Si tenemos acceso como admin, imprime ID guardado, sino, 
                //imprime si está ocupado el asiento
                if(esAdmin==1){
                    printf("%i  ",Sala[i][j]);
                }
                else{
                    printf("1    ");
                }
            }
            else{
                printf("0    ");
            }
        }
        printf("\n");
    }
}

int ElegirSala(void){
    int sala=0;
    //Imprime opciones de salas
    do{
        printf("Elige el número de sala:\n");
        printf("Sala 1: King Kong\n");
        printf("Sala 2: Godzilla\n");
        printf("Sala 3: King Kong vs Godzilla\n");
        printf("Sala 4: Nacho Libre\n");
        printf("Sala 5: Intensamente\n");
        scanf("%i",&sala);
    }while(sala<0 || sala>5);
    //Regresa el número de sala elegida
    return sala;
}

int main(){
    int ingreso=0;
    int Accesoadmin=0;
    int ID=0;
    char Password[10];
    int sala=0;
    int Sala1[10][15];
    int Sala2[10][15];
    int Sala3[10][15];
    int Sala4[10][15];
    int Sala5[10][15];
    char salirAdmin;
    char modres;
    char asiento[4];
    int fila=0;
    int columna=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<15;j++){
            Sala1[i][j]=0;
            Sala2[i][j]=0;
            Sala3[i][j]=0;
            Sala4[i][j]=0;
            Sala5[i][j]=0;
        }
    }
    //Limpia pantalla (usar system("cls"); para Windows)
    system("clear");
    while(1){
        do{
            printf("Entrar como cliente o admin? Cliente (1) Admin (2)\n");
            scanf("%i",&ingreso);
        }while(ingreso != 1 && ingreso!=2);
        //Limpia pantalla (usar system("cls"); para Windows)
        system("clear");
        switch(ingreso){
            case 1: //Cliente
                //Solicita ID, si no es valido, vuelve a pedirlo
                do{
                    printf("Ingrese ID de cliente: \n");
                    scanf("%i",&ID);
                    //Limpia pantalla (usar system("cls"); para Windows)
                    system("clear");
                    if(ID<0 || ID>1000){
                        printf("ID incorrecto\n");
                    }
                }while(ID<0 || ID>1000);
                //Muestra menú de salas
                sala=ElegirSala();
                //Dependiendo el número de sala, elige asiento
                //para la sala correspondiente
                switch(sala){
                   case 1: ElegirAsiento(Sala1,1,ID); break;
                   case 2: ElegirAsiento(Sala2,2,ID); break;
                   case 3: ElegirAsiento(Sala3,3,ID); break;
                   case 4: ElegirAsiento(Sala4,4,ID); break;
                   case 5: ElegirAsiento(Sala5,5,ID); break;
                }
            break;
            case 2: //Ingreso como Admin
                do{
                    printf("Ingrese contraseña de admin\n");
                    scanf("%s",Password);
                    //Limpia pantalla (usar system("cls"); para Windows)
                    system("clear");
                    //Verifica contraseña
                    if(strcmp(Password,"admin123")==0){
                        printf("Acceso como admin\n");
                        Accesoadmin=1;
                    }
                    else{
                        printf("Contraseña incorrecta\n");
                        Accesoadmin=0;
                    }
                }while(Accesoadmin==0);
                do{
                    sala=ElegirSala();
                    switch(sala){
                        case 1: MostrarAsientos(1,Sala1,1); break;
                        case 2: MostrarAsientos(1,Sala2,2); break;
                        case 3: MostrarAsientos(1,Sala3,3); break;
                        case 4: MostrarAsientos(1,Sala4,4); break;
                        case 5: MostrarAsientos(1,Sala5,5); break;
                    }
                    printf("Eliminar reservaciones? (y)/(n)\n");
                    scanf("%s",&modres);
                    if(modres=='y'){
                        printf("Ingrese número de asiento\n");
                        printf("Ingresa el asiento elegido\n");
                        scanf("%s",asiento);
                        fila=(int)asiento[0] - 'a';
                        columna=atoi(&asiento[1])-1;
                        switch(sala){
                        case 1: Sala1[fila][columna]=0; break;
                        case 2: Sala2[fila][columna]=0; break;
                        case 3: Sala3[fila][columna]=0; break;
                        case 4: Sala4[fila][columna]=0; break;
                        case 5: Sala5[fila][columna]=0; break;
                        }
                        printf("Asiento eliminado\n");
                    }
                    printf("Salir sesion Admin? (y)/(n)\n");
                    scanf("%s",&salirAdmin);
                    //Limpia pantalla (usar system("cls"); para Windows)
                    system("clear");
                }while(salirAdmin=='n');
            break;
        }
    }
    return 0;
}

