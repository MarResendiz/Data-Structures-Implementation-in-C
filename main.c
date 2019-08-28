/*Por: Mariel C. Reséndiz.
Práctica #2
Fecha: 15 de Agosto del 2019.
Objetivo: Creación .
Compilador: GNU GCC.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();

#define MAXNOM 20
#define TAM sizeof(struct nodo_s)
#define NIL NULL

typedef struct datos{ //Estructura de la información del jugador
    short int num_j;
    char nom_j[MAXNOM];
}datos;

typedef struct nodo_s{
    struct datos info;
    struct nodo_s *sig;
}nodo_s;

nodo_s *i=NIL;

void agrega_en(int pos, short int dato_j, char dato_n[]);
void pos_f(short int dato_j, char dato_n[]);
void pos_i(short int dato_j, char dato_n[]);
void borra_dato(short int dato_j, char dato_n[]);
short int buscar_dato(short int dato_j, char dato_n[], short int *cont);

int main(){
    short int num=0, op=0, cont=0, pos=0, fun=0;
    char nombre[MAXNOM];
    while(op!=5){
      menu();
      fflush(stdin);
      scanf("%d",&op);
      if(!op){
        printf("\n\n\t Error: Opcion invalida.");
      }
    switch(op){
    case 1:system("cls");
    printf("\n\n\t\t (1) Insertar un jugador.");
    printf("\n\n\t Ingresa el nombre: \t");
    fflush(stdin);
    scanf("%s",&nombre);
    strupr(nombre);
    printf("\n\n\t Ingresa un numero de jugador: \t");
    fflush(stdin);
    scanf("%d",&num);
    if(cont==0){
       pos_i(num,nombre);
       cont++;
    }
    else if(cont!=0){
        pos_f(num,nombre);
        cont++;
    }
    break;

    case 2:system("cls");
    printf("\n\n\t\t (2) Borrar un jugador.");
    printf("\n\n\t Ingresa el nombre: \t");
    fflush(stdin);
    scanf("%s",&nombre);
    strupr(nombre);
    printf("\n\n\t Ingresa un numero de jugador: \t");
    fflush(stdin);
    scanf("%d",&num);
    borra_dato(num,nombre);
    if(cont!=0){
        cont--;
    }

    break;

    case 3:system("cls");
    printf("\n\n\t\t (3) Desplegar contenido de la lista.");
    desplegar_lista();

    break;

    case 4:system("cls");
    printf("\n\n\t\t (4) Buscar un jugador en la lista.");
    printf("\n\n\t Ingresa el nombre: \t");
    fflush(stdin);
    scanf("%s",&nombre);
    strupr(nombre);
    printf("\n\n\t Ingresa un numero de jugador: \t");
    fflush(stdin);
    scanf("%d",&num);
    fun=buscar_dato(num,nombre,&pos);
    if(fun==0){
        printf("\n\n\t\t Error: El jugador no existe.");
    }
    else if(fun==-1){
        printf("\n\n\t\t Error: La lista esta vacia.");
    }
    break;

    case 5:printf("\n\n\t\t Saliendo...\n\n");
    break;

    default:
    break;
    }


   }





    return 0;
}

void agrega_en(int pos, short int dato_j, char dato_n[]){
    int cont=0;
    nodo_s *prev=NIL, *act=i, *aux=NIL, *med=NIL;
    nodo_s *node=malloc(TAM*1);
    node->info.num_j=dato_j;
    strcpy(node->info.nom_j,dato_n);
    node->sig=NIL;

    //Si la lista esta vacía.
    if(i==NIL){
        i=node;
        return;
    }
    // Al terminar inserta el nodo 0 con la información.

    //Si no terminó la función, se mueve uno por uno hasta encontrar el final (un nodo vacío).

    while(act!=NIL && cont!=pos){
        cont++;
        prev=act;
        act=act->sig;
    }

    //Al terminar inserta el nuevo nodo con la información al inicio.

    if(cont==0){
        i=node;
        node->sig=act;
        return;
    }

    //Al terminar inserta el nuevo nodo con la información en el final.

    else if(act==NIL){
        prev->sig=node;
        return;
    }

    //Al terminar inserta el nuevo nodo con la información en el medio.

    else{
        prev->sig=node;
        node->sig=act;
        return;
    }

}

void pos_i(short int dato_j, char dato_n[]){
    agrega_en(0,dato_j,dato_n);
}

void pos_f(short int dato_j, char dato_n[]){
    agrega_en(-1,dato_j,dato_n);
}

void borra_dato(short int dato_j, char dato_n[]){
    nodo_s *ant=NIL, *act=i;
    while(act!=NIL && strcmp(dato_n,act->info.nom_j)!=0){
        ant=act;
        act=act->sig;
    }

    if(act==NIL){
        return;
    }

    else if(ant==NIL){
       if(act->sig==NIL){
        //Sólo hay un objeto en la lista.
        i=NIL;
       }
       else{
        //Hay más objetos aparte de este.
        i=act->sig;
       }
       free(act);
       return;
    }

    else if(act->sig==NIL){
        //Es el último dato.
        ant->sig=NIL;
        free(act);
        return;
    }

    else if(ant!=NIL && act->sig!=NIL){
        //Cuando es el dato de el medio.
        ant->sig=act->sig;
        free(act);
        return;
    }



}

short int buscar_dato(short int dato_j, char dato_n[], short int *cont){
    nodo_s *act=i;
    *cont=0;
    short int band=0;
    while(act!=NIL && band==0){
           if(strcmp(dato_n,act->info.nom_j)==0){
            band=1;
           }
           else{
            *cont=*cont+1;
            act=act->sig;
           }
         }
    if(band==1){
      printf("\n\n\t\t Jugador: %s Numero: %d Posicion: %d",act->info.nom_j,act->info.num_j,*cont);
   }

   else if(band==0){
        return 0;
    }

    else if(act==NIL){
        return -1;
    }

}


void desplegar_lista(){
    nodo_s *imprime=i;
    while(imprime!=NIL){
        printf("\n\n\t");
        printf(" Datos del jugador:\t Nombre: %s  Numero: %d",imprime->info.nom_j,imprime->info.num_j);
        imprime=imprime->sig;
    }
}

void menu(){
    printf("\n\n\t");
    system("pause");
    printf("\n\n\t\t Menu:\n\n");
    printf("\n\n\t (1) Insertar un jugador.\n\t (2) Borrar un jugador.\n\t (3) Desplegar el contenido de la lista.\n\t (4) Buscar un jugador.\n\t (5) Salir.");
    printf("\n\n\t Ingrese una opcion: \t");
}


