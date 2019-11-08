#include<stdio.h>
#include<string.h>
#include"mpi.h" //Librería necesaria para el uso de MPI en C.

int main(int argc,char *argv[])
{
   int name,p;
   MPI_Init(&argc,&argv);//Función que inicializa el uso de MPI.
   MPI_Comm_rank(MPI_COMM_WORLD,&name); // Define la etiqueta(nombre) de cada proceso
   MPI_Comm_size(MPI_COMM_WORLD,&p); //Numero total de procesos

   printf("Hola mundo, desde el proceso %d de %d \n",name,p);
   
   MPI_Finalize(); //Función estandar para finalizar el uso de MPI.
   return 0;
}
