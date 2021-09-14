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
};
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

typedef struct combinacionPaquetes combinacionPaquetes;
struct combinacionPaquetes{
    int * arregloPaquetes; //Almacena los id's de los cuales se compone la combinacion
    int beneficioTotal; //Beneficio total de la combinacaion de paquetes
    int volumenTotal; //volumen Total que ocupa la combinacion de paquetes
    int ultimaPos; //Optimizacion, guarda la posicion(del arreglo inicial) del ultimo paquete que entro a la combinacion
    int largoArreglo;
};

/*
e: Paquete, ultimaPos
s: combacionPaquetes
o: crear combinacion para los paquetes iniciales
*/
combinacionPaquetes crearCombinacionInicial(Paquete nuevoPaquete,int ultimaPos){
    combinacionPaquetes nuevaCombinacion;
    nuevaCombinacion.largoArreglo = 1;
    int * arreglo = (int*)malloc(sizeof(int)*nuevaCombinacion.largoArreglo);
    arreglo[nuevaCombinacion.largoArreglo-1] = nuevoPaquete.id;
    nuevaCombinacion.volumenTotal = getVolumen(nuevoPaquete);
    nuevaCombinacion.beneficioTotal = getPrecio(nuevoPaquete);
    nuevaCombinacion.ultimaPos = ultimaPos;
    nuevaCombinacion.arregloPaquetes = arreglo;
    return nuevaCombinacion;
}
/*
e: combinacionPaquetes
s: int
o: retornar beneficio total
*/
int getBeneficioTotal(combinacionPaquetes A){
    return A.beneficioTotal;
}
/*
e: combinacionPaquetes
s: int
o: retornar volumen total 
*/
int getVolumenTotal(combinacionPaquetes A){
    return A.volumenTotal;
}
/*
e: combinacionPaquetes
s: int 
o: retornar la ultima posicion del arreglo
*/
int getUltimaPos(combinacionPaquetes A){
    return A.ultimaPos;
}
/*
e: combinacionPaquetes
s: int 
o: retornar largo del arreglo de combinaciones 
*/
int getLargoArreglo(combinacionPaquetes A){
    return A.largoArreglo;
}
/*
e: combinacionPaquetes
s: int*
o: retornar arreglo de combinaciones
*/
int* getArreglo(combinacionPaquetes A){
    return A.arregloPaquetes;
}
/*
e: Arreglo de enteros, largo del arreglo
s: el arreglo ingresado con un elemento más
o: Agregar un entero a un arreglo de enteros
*/
int * agregarIdArreglo(int * arregloPrevio, int largoArreglo, int id){
    int i = 0;
    int * arregloAux = (int*)malloc(sizeof(int)*largoArreglo+1);
    //Se agregan los elementos del arreglo anterior
    for(i; i < largoArreglo; i++){
        arregloAux[i] = arregloPrevio[i];
    }
    //Se agrega el nuevo elemento
    arregloAux[i] = id;
    //Se retorna el nuevo arreglo
    return(arregloAux);
}

/*
e: Un paquete, ultima posicion del arreglo inicial agregada, combinacion previa
s: Una nueva combinacion proveniente de una combinacion existente
o: Crear una nueva combinacion
*/
combinacionPaquetes crearCombinacion(Paquete nuevoPaquete,int ultimaPos,combinacionPaquetes combinacionAntigua){
    combinacionPaquetes nuevaCombinacion;
    nuevaCombinacion.arregloPaquetes = agregarIdArreglo(getArreglo(combinacionAntigua),getLargoArreglo(combinacionAntigua),getId(nuevoPaquete));
    nuevaCombinacion.largoArreglo = getLargoArreglo(combinacionAntigua) + 1;
    nuevaCombinacion.beneficioTotal = getBeneficioTotal(combinacionAntigua) + getPrecio(nuevoPaquete);
    nuevaCombinacion.volumenTotal = getVolumenTotal(combinacionAntigua) + getVolumen(nuevoPaquete);
    nuevaCombinacion.ultimaPos = ultimaPos;
    return nuevaCombinacion;
}

//Entrada: El nombre del archivo.
//Salida: la lectura del archivo.
//Objetivo: Abrir un archivo en modo lectura y leer su contenido.
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
e:Paquete
s:Vacio
o:Printea un paquete
*/
void mostrarPaquete(Paquete A){
    printf("Paquete Id:%d, Volumen:%d, Precio:%d\n",getId(A),getVolumen(A),getPrecio(A));
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
e: combinacionPaquetes
s: vacio 
o: muestra datos de la combinacion
*/
void mostrarCombinacion(combinacionPaquetes A){
    int i=0;
    int *aux = getArreglo(A);
    int largoLista = getLargoArreglo(A);
    printf("Combinacion Beneficio:%d, volumen:%d, UPos:%d, Largo: %d\n", getBeneficioTotal(A), getVolumenTotal(A),getUltimaPos(A),largoLista);
    printf("Combinaciones: ");  
    for(i; i < largoLista;i++){
        printf("%d ,", aux[i]);
    }
    
    printf("\n");
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
        }
    }
    return listaInicial;
}

/*
e: Lista de combinaciones, Combinacion a agregar, largo de la lista de combinaciones
s: La lista de combinaciones con el nuevo elemento agregado
o: Agregar una combinacion a la lista que contiene las combinaciones
*/
combinacionPaquetes* agregarCombinacion(combinacionPaquetes* lista, combinacionPaquetes elemento, int *largo){
    lista = realloc(lista,sizeof(combinacionPaquetes)*(*largo+1));
    lista[*largo] = elemento;
    *largo = *largo + 1;
    return lista;
}
/*
e: lista de combinaciones, largo del arreglo
s: vacio
o: libera la memoria de los arreglos ocupados para representar las combinaciones
*/
void liberarMemoria(combinacionPaquetes* lista, int largoLista){
    int *aux;
    int i=0;
    for(i; i < largoLista;i++){
        aux = getArreglo(lista[i]);
        free(aux);
    }
    free(lista);
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

combinacionPaquetes encontrarMejorCombinacion(Paquete* listaPaquetesInicial, int largoPaqueteInicial, int volumenMax){
    int largoListaCombinaciones = 0;
    //Se agrega una combinacion auxiliar, que tendra beneficio -1 a fin de poder buscar la mejor combinacion
    Paquete paqueteNulo = crearPaquete(-1,-1,-1);
    combinacionPaquetes mejorCombinacion = crearCombinacionInicial(paqueteNulo,-1);
    //Convertir los paquetes iniciales a combinaciones de un solo paquete
    combinacionPaquetes *listaCombinaciones = (combinacionPaquetes*)malloc(sizeof(combinacionPaquetes));
    int i = 0;
    for(i; i<largoPaqueteInicial; i++){
        combinacionPaquetes aux = crearCombinacionInicial(listaPaquetesInicial[i],i);
        listaCombinaciones = agregarCombinacion(listaCombinaciones,aux,&largoListaCombinaciones);
        //Se almacenara la combinacion que va generando el mayor beneficio hasta el momento
        if(getBeneficioTotal(mejorCombinacion) < getBeneficioTotal(aux)){
            mejorCombinacion = aux;
        }
    }
    //Generar combinaciones -> guardar posicion de la mejor combinacion    
    i = 0;
    int j=0;
    combinacionPaquetes auxB;
    Paquete paqueteAux;
    //Se crean todas las combinaciones
    for(i; i < largoListaCombinaciones;i++){
        auxB=listaCombinaciones[i];
        for(j=getUltimaPos(auxB)+1 ; j < largoPaqueteInicial; j++){        
            paqueteAux = listaPaquetesInicial[j];
            if(getVolumenTotal(auxB)+getVolumen(paqueteAux) <= volumenMax){
                combinacionPaquetes nuevaCombinacion = crearCombinacion(paqueteAux,j,auxB);
                listaCombinaciones = agregarCombinacion(listaCombinaciones,nuevaCombinacion,&largoListaCombinaciones);
                //Se almacenara la combinacion que va generando el mayor beneficio hasta el momento
                if(getBeneficioTotal(mejorCombinacion) < getBeneficioTotal(nuevaCombinacion)){
                    mejorCombinacion = nuevaCombinacion;
                    printf("Mejor combinacion actualizada\n");
                    mostrarCombinacion(mejorCombinacion);
                }
            }
        }
    }
    int *idMejores = copiarArreglo(getArreglo(mejorCombinacion),getLargoArreglo(mejorCombinacion));
    liberarMemoria(listaCombinaciones,largoListaCombinaciones);// se libera el espacio ocupado en los arreglos para las combinaciones
    mejorCombinacion.arregloPaquetes = idMejores; //Se recupera el arreglo con la mejor combinacion
    return(mejorCombinacion);
}

void escribirArchivoFinal(combinacionPaquetes mejorCombinacion){
    FILE * salida; //Se define un archivo salida
    salida = fopen("salida.txt", "w"); //Se abre el archivo salida en modo de escritura y se le asigna el nombre salida.txt
    int i = 0;
    int *aux = getArreglo(mejorCombinacion);
    for(i;i < getLargoArreglo(mejorCombinacion); i++){
        fprintf(salida,"Paquete %d\n",aux[i]);
    }
    fprintf(salida,"Beneficio: %d\n",getBeneficioTotal(mejorCombinacion));
    fprintf(salida,"Volumen: %dm3",getVolumenTotal(mejorCombinacion));
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
    printf("Ingrese el nombre del archivo, con la extension incluida, por ejemplo dataset_5_20.csv:\n");
    scanf("dataset_%d_%d.csv",&cantidadPaquetes,&volumenMaximo);
    snprintf(nombreArchivo, sizeof nombreArchivo, "dataset_%d_%d.csv",cantidadPaquetes,volumenMaximo);
    dataSet = leerArchivo(nombreArchivo);  //Lectura
    //Se verifica en caso que no haya sido posible la lectura del archivo
    if(dataSet == 0){
        printf("Algo fallo, verifique el nombre del archivo por favor\n");
        return 0;
    }
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
    //Se generan todas las combinaciones y se retorna la que tenga el mejor beneficio
    combinacionPaquetes mejorCombinacion = encontrarMejorCombinacion(paquetesIniciales,largoPaqueteInicial,volumenMaximo);
    printf("\n Mejor combinacion final \n");
    mostrarCombinacion(mejorCombinacion);
    escribirArchivoFinal(mejorCombinacion);
    fin = clock();
    double tiempoTotal = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n",tiempoTotal);
    //Se libera el arreglo de paquetes inicales
    free(paquetesIniciales);
    return 0;
}
