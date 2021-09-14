/*
Seccion A-1
Grupo 4:

Israel Arias Panez // 20110122-0
Christian Mendez Acosta //20220627-1

Fecha: 30 de abril de 2021

Notacion:
e: Entrada
s: Salida
o: Objetivo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct Paquete Paquete;
struct Paquete{
    int id;
    int precio;
    int volumen;
    float ponderacion;
};

/*
e: INT X INT
s: Float
o: retornar el resultado flotante de A/B

*/
float divisionFloat(int A,int B){
    float resultado,auxA,auxB;
    auxA = A;
    auxB = B;
    resultado = auxA / auxB;
    return resultado;
}

/*Creador paquete
e: INT X INT X INT
s: Paquete
o: Crear un paquete
*/
Paquete crearPaquete(int id,int precio,int volumen){
    Paquete nuevoPaquete;
    nuevoPaquete.id = id;
    nuevoPaquete.precio = precio;
    nuevoPaquete.volumen = volumen;
    nuevoPaquete.ponderacion = divisionFloat(precio,volumen);
    return nuevoPaquete;
}
/*
e: Paquete
s: INT
o: retornar el id de un paquete
*/
int getId(Paquete A){
    return A.id;
}
/*
e: Paquete
s: INT
o: retornar el precio de un paquete
*/
int getPrecio(Paquete A){
    return A.precio;
}
/*
e: Paquete
s: INT
o: retornar la cantidad de volumen de un paquete
*/
int getVolumen(Paquete A){
    return A.volumen;
}

/*
e: Paquete
s: Float
o: retornar la cantidad de ponderacion de un paquete
*/
float getPonderacion(Paquete A){
    return A.ponderacion;
}

Paquete* agregarPaqueteV2 (Paquete* arregloPrevio, int largoArreglo, Paquete nuevo){
    int i = 0;
    Paquete* arregloAux = (Paquete*)malloc(sizeof(Paquete)*largoArreglo+1);
    //Se agregan los elementos del arreglo anterior
    for(i; i < largoArreglo; i++){
        arregloAux[i] = arregloPrevio[i];
    }
    //Se agrega el nuevo elemento
    arregloAux[i] = nuevo;
    //Se retorna el nuevo arreglo
    return(arregloAux);

}


/*
e: Lista Paquetes ordenada, Largo inicial de la lista, Capacidad Container
s: Indice de corte de la solucion
o: Determinar la combinacion Optima de paquetes

[1,2,3,4,5] C = 5
1+0
1+2
3+3 <---->
6+4
10+5
*/
int metodoGoloso(Paquete* listaPaquetesInicial, int largoPaqueteInicial, int volumenMax){
    int i = 0;
    int indiceTope = 0;
    int valorAcumulado = 0;
    for (i; i < largoPaqueteInicial ; i++){
        valorAcumulado = valorAcumulado + getVolumen(listaPaquetesInicial[i]);
        if (valorAcumulado > volumenMax){
            return i-1;
        }
    }
    return largoPaqueteInicial-1;
} 
/*

[1,2,3,4]
li [1,2] i hasta med
ld [3,4] med+1 hasta fin

*/
void mezclar(Paquete* arreglo, int inicio,int medio, int fin){
    int izq = inicio;
    int der = medio+1;
    int largo = fin-inicio+1;
    int iaux = 0; //Indice auxiliar
    Paquete* listaAuxiliar = (Paquete *)malloc(sizeof(Paquete)*largo);    
    while(izq <= medio && der <= fin){
        if(getPonderacion(arreglo[izq]) > getPonderacion(arreglo[der])){
            listaAuxiliar[iaux] = arreglo[izq];
            iaux++;
            izq++;
        }
        else{
            listaAuxiliar[iaux] = arreglo[der];
            iaux++;
            der++;
        }

    }
    for(int i = izq;i <= medio;i++){
        listaAuxiliar[iaux] = arreglo[i];
        iaux++;
    }
    for(int j = der ;j <= fin; j++){
        listaAuxiliar[iaux] = arreglo[j];
        iaux++;
    }
    for (int i = 0; i < largo;i++){
      arreglo[i+inicio] =listaAuxiliar[i];
    }
    free(listaAuxiliar);
    
}
/*
O:ordenar de mayor a menor
*/
void mergeSort(Paquete* arreglo, int inicio, int fin){
    if(inicio < fin){
        int medio = (inicio + fin)/2;
        mergeSort(arreglo, inicio, medio);
        mergeSort(arreglo,medio+1,fin);
        mezclar (arreglo,inicio, medio,fin);
    }
}

/*
e: El nombre del archivo.
s: la lectura del archivo.
o: Abrir un archivo en modo lectura y leer su contenido.
*/
FILE * leerArchivo(char* nombreArchivo){
    //Se inicializa archivo como null
    FILE* archivo = NULL;
    archivo = fopen(nombreArchivo, "r"); //Lee el archivo
    if (archivo == NULL){ //Si el archivo no existe.
        return 0;
    } else {
        return(archivo);
    }
}

/*
e:
s:
o: Limpiar el buffer de entrada
*/
void limpiarBuffer(){
    while (getchar()!= '\n');
}
int compare (const void * a, const void * b)
{

  Paquete *orderA = (Paquete *)a;
  Paquete *orderB = (Paquete *)b;

  return ( orderB->ponderacion - orderA->ponderacion );
}
int compareFloat (const void * a, const void * b)
{
  Paquete* fa = (Paquete *) a;
  Paquete* fb = (Paquete *) b;
  return (fa->ponderacion < fb->ponderacion) - (fa->ponderacion > fb->ponderacion);
}

/*
e:Paquete
s:Vacio
o:Printea un paquete
*/
void mostrarPaquete(Paquete A){
    printf("Paquete Id:%d, Volumen:%d, Precio:%d Ponderado: %f\n",getId(A),getVolumen(A),getPrecio(A),getPonderacion(A));
}
/*
e: Lista de paquetes, largo arreglo
s: vacio
o: Mostrar los datos de una lista de paquetes
*/
void mostrarListaPaquetes(Paquete *arreglo, int largoArreglo){
    int i =0;
    for( i; i < largoArreglo; i++){
        mostrarPaquete(arreglo[i]);
    }
}

/*
e:Paquete
s:Vacio
o:Printea un paquete
*/
Paquete * agregarPaquete(Paquete* paquetesIniciales, Paquete nuevoPaquete, int *cantidadPaquetes){
    *cantidadPaquetes = *cantidadPaquetes + 1;
    paquetesIniciales = realloc(paquetesIniciales,sizeof(Paquete)*(*cantidadPaquetes));
    paquetesIniciales[(*cantidadPaquetes)-1] = nuevoPaquete;
    return(paquetesIniciales);
}

/*
e: Arreglo de enteros, numero, largo del arreglo
s: El arreglo ingresado con elemento agregado al final
o: Agrega un dato un id al final del arreglo
*/
int * agregarIdCombinacion(int * paquetesCombinacion, int nuevoId, int *largoArreglo){
    *largoArreglo = *largoArreglo + 1;
    paquetesCombinacion = realloc(paquetesCombinacion,sizeof(int)*(*largoArreglo));
    paquetesCombinacion[(*largoArreglo)-1] = nuevoId;
    return(paquetesCombinacion);
}

/*
e: archivo, cantidad paquetes, volumen maximo, puntero Paquetes, largo lista paquetes
s: vacio
o: Leer y validar los paquetes iniciales
*/
Paquete * generarPaquetesIniciales(FILE *archivo, int cantPaquetes, int volMax,Paquete* listaInicial,int *largoPaqueteInicial){
    int i = 0;
    int idAux = 0,volAux = 0,beneficioAux =0;
    for(i; i < cantPaquetes; i++){
        fscanf(archivo,"Paquete %d,%d,%d\n",&idAux,&volAux,&beneficioAux); //Lectura de una linea del archivo
        if(volAux <= volMax){
            Paquete aux = crearPaquete(idAux,beneficioAux,volAux); //Creacion de paquete segun estructura
            listaInicial = agregarPaquete(listaInicial,aux,largoPaqueteInicial);
            //mostrarPaquete(aux);
        }
    }
    return listaInicial;
}


/*
e: un arreglo, largo del arreglo
s: un nuevo arreglo identico al arreglo entrante
o: crear un nuevo arreglo que sea una copia del arreglo entrante
*/
int* copiarArreglo(int* arreglo,int largoArreglo){
    int * arregloAux = malloc(sizeof(int)*largoArreglo);
    int i=0;
    for(i;i<largoArreglo;i++){
        arregloAux[i] = arreglo[i];
    }
    return arregloAux;
}


void escribirArchivoFinal(Paquete* mejorCombinacion, int indice){
    FILE * salida; //Se define un archivo salida
    salida = fopen("salida.txt", "w"); //Se abre el archivo salida en modo de escritura y se le asigna el nombre salida.txt
    int i = 0;
    int beneficioTotal = 0;
    int volumenTotal = 0;
    for(i;i <= indice; i++){
        fprintf(salida,"Paquete %d\n",getId(mejorCombinacion[i]));
        beneficioTotal = beneficioTotal + getPrecio(mejorCombinacion[i]);
        volumenTotal = volumenTotal + getVolumen(mejorCombinacion[i]);
        //mostrarPaquete(mejorCombinacion[i]);
    }
    fprintf(salida,"Beneficio: %d\n", beneficioTotal);
    fprintf(salida,"Volumen: %dm3", volumenTotal);
    printf("Beneficio: %d\n", beneficioTotal);
    printf("Volumen: %dm3\n", volumenTotal);
    //Se cierra el archivo
    fclose(salida);
}

int main(){
    time_t inicio,fin;
    int cantidadPaquetes, volumenMaximo; //Datos del archivo
    //Se solicita el nombre del archivo
    int lecturaArchivo = 0;
    FILE* dataSet;
    char nombreArchivo[100];
    while(1){
        printf("Ingrese el nombre del archivo, con la extension incluida, por ejemplo dataset_5_20.csv:\n");
        scanf("dataset_%d_%d.csv",&cantidadPaquetes,&volumenMaximo);
        snprintf(nombreArchivo, sizeof nombreArchivo, "dataset_%d_%d.csv",cantidadPaquetes,volumenMaximo);
        dataSet = leerArchivo(nombreArchivo);  //Lectura
        //Se verifica en caso que no haya sido posible la lectura del archivo
        if(dataSet == 0){
            printf("Algo fallo, verifique el nombre del archivo e intentelo de nuevo\n");
            limpiarBuffer();
        } else {
            break;
        }
    }
    //printf("Cantidad de paquetes = %d \n", cantidadPaquetes);
    //Empieza a correr la medicion del tiempo de ejecucion luego de los inputs del usuario
    inicio = clock();
    int largoPaqueteInicial = 0;
    Paquete* paquetesIniciales = (Paquete*)malloc(sizeof(Paquete));
    paquetesIniciales=generarPaquetesIniciales(dataSet,cantidadPaquetes,volumenMaximo,paquetesIniciales,&largoPaqueteInicial);
    fclose(dataSet);
    //A continuación se verifica en caso que no se haya guardado ningun paquete valido
    if(largoPaqueteInicial == 0){
        printf("No hay paquetes validos");
        return 0;
    }
    //Se ordenan las combinaciones de mayor a menor de acuerdo a su ponderacion
    qsort(paquetesIniciales, largoPaqueteInicial, sizeof(Paquete), compareFloat);
    //Se usa el metodo golozo para conseguir el indice hasta el que se escribira la combinación optima
    int indice = metodoGoloso(paquetesIniciales, largoPaqueteInicial,volumenMaximo);
    //Se escribe el archivo final
    printf("El resultado es: \n");
    escribirArchivoFinal(paquetesIniciales,indice);
    fin = clock();
    double tiempoTotal = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n",tiempoTotal);
    //Se libera el arreglo de paquetes inicales
    free(paquetesIniciales);
    return 0;
}