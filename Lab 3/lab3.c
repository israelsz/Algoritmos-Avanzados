/*
Seccion A-1
Grupo 4:

Israel Arias Panez // 20110122-0
Christian Mendez Acosta //20220627-1

Fecha: 23 de julio de 2021

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
e: indice, lista de paquetes, largo de la lista 
s: paquete
o: encontrar el paquete al cual pertenece el indice
*/
Paquete encontrarPaquete(int i, Paquete* listaPaquetes, int largo){
    int j;
    for(j=0; j <= largo; j++){
        if(getId(listaPaquetes[j]) == i){
            return listaPaquetes[j];
        }
    }
    return listaPaquetes[0];

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
    Paquete aux = crearPaquete(0,0,0); //Creacion de paquete segun estructura
    listaInicial = agregarPaquete(listaInicial,aux,largoPaqueteInicial);
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
e: beneficio actual, peso actual, volumen maximo, indice, lista de paquetes, largo de la lista
s: posible beneficio
o: Determinar el posible beneficio al agregar paquetes restantes al conjunto
*/
int posibleBeneficio(int beneficioActual, int pesoActual, int volumenMaximo, int i, Paquete* paquetesIniciales, int cantidadPaquetes){
    int volumenRestante = volumenMaximo - pesoActual;   
    int posibleBeneficio = beneficioActual;
    while(i <= cantidadPaquetes && volumenRestante >= getVolumen(paquetesIniciales[i])){
        volumenRestante = volumenRestante - getVolumen(paquetesIniciales[i]);
        posibleBeneficio = posibleBeneficio + getPrecio(paquetesIniciales[i]);
        i = i+1;
    }

    if(i <= cantidadPaquetes){
        posibleBeneficio = beneficioActual + (volumenRestante * getPrecio(paquetesIniciales[i]));
    }
    return posibleBeneficio;
}

/*
e: Indice i, beneficio actual, peso actual, 2 arreglos "mochila" inicializados con ceros, lista de paquetes leida de dataset, cantidad de paquetes, volumen maximo y el mejor beneficio
s: Arreglo que contiene los paquetes que generan la mejor combinación encontrada
o: Encontrar la mejor combinación de paquetes que entregue el mayor beneficio usando el metodo de backtracking con poda
*/

int * backtrack(int i, int beneficioActual, int pesoActual, int* mochila, int* mejorMochila, Paquete * paquetesIniciales, int cantidadPaquetes, int volumenMaximo, int mejorBeneficio){
    if(i > cantidadPaquetes){
        mejorBeneficio = beneficioActual;
        for(int j = 1; j <= cantidadPaquetes; j++){
            mejorMochila[j] = mochila[j];
        }
        return mejorMochila;
    }
    if(pesoActual + getVolumen(paquetesIniciales[i]) <= volumenMaximo){
        mochila[getId(paquetesIniciales[i])] = 1;
        pesoActual = pesoActual + getVolumen(paquetesIniciales[i]);
        beneficioActual = beneficioActual + getPrecio(paquetesIniciales[i]);
        //Llamada recursiva
        return backtrack(i+1,beneficioActual,pesoActual,mochila,mejorMochila,paquetesIniciales,cantidadPaquetes,volumenMaximo,mejorBeneficio);
        pesoActual = pesoActual - getVolumen(paquetesIniciales[i]);
        beneficioActual = beneficioActual - getPrecio(paquetesIniciales[i]);
        mochila[getId(paquetesIniciales[i])] = 0;
    }
    //Se verifica si se expande el arbol a la derecha
    if(posibleBeneficio(beneficioActual,pesoActual,volumenMaximo,i,paquetesIniciales,cantidadPaquetes) > mejorBeneficio){
        mochila[getId(paquetesIniciales[i])] = 0;
        return backtrack(i+1,beneficioActual,pesoActual,mochila,mejorMochila,paquetesIniciales,cantidadPaquetes,volumenMaximo,mejorBeneficio);
        
    }
}
/*
e: La cantidad de paquetes leidos del dataset
s: Un arreglo de enteros
o: Inicializar un arreglo lleno de ceros
*/
int * inicializarArreglo(int cantidadPaquetes){
    int * arreglo = malloc(sizeof(int)*cantidadPaquetes+1);
    for(int i=0; i <= cantidadPaquetes; i++){
        arreglo[i] = 0;
    }
    return arreglo;
}



void escribirArchivoFinal(Paquete* mejorCombinacion, int *mejorMochila, int cantidadPaquetes){
    FILE * salida; //Se define un archivo salida
    salida = fopen("salida.txt", "w"); //Se abre el archivo salida en modo de escritura y se le asigna el nombre salida.txt
    int i = 0;
    int beneficioTotal = 0;
    int volumenTotal = 0;
    Paquete paqueteAux;
    for(i;i <= cantidadPaquetes; i++){
        if(mejorMochila[i] == 1){
            paqueteAux = encontrarPaquete(i,mejorCombinacion,cantidadPaquetes);
            fprintf(salida,"Paquete %d\n",getId(paqueteAux));
            beneficioTotal = beneficioTotal + getPrecio(paqueteAux);
            volumenTotal = volumenTotal + getVolumen(paqueteAux);
            //mostrarPaquete(mejorCombinacion[i]);
        }
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
    //Se inicializa un indice i y dos arreglos que seran usados en el backtracking
    int i = 1;
    int * mochila = inicializarArreglo(cantidadPaquetes);
    int * mejorMochila = inicializarArreglo(cantidadPaquetes);
    //Se usa el metodo de backtracking para conseguir la combinación optima
    mejorMochila = backtrack(i,0,0,mochila,mejorMochila,paquetesIniciales,cantidadPaquetes,volumenMaximo,0);
    //Se escribe el archivo final
    escribirArchivoFinal(paquetesIniciales,mejorMochila,cantidadPaquetes);
    fin = clock();
    double tiempoTotal = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Archivo de salida generado ! \n");
    printf("Tiempo de ejecucion: %f\n",tiempoTotal);
    //Se libera el arreglo de paquetes inicales
    free(paquetesIniciales);
    return 0;
}