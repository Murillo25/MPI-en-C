#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mpi.h"
#include<math.h>
#include <time.h>

#define Master 0

void reservaMem(int **array,int n);
void generaRandoms(int *array, int n);

int main(int argc,char *argv[])
{
   int N = 20;
   int name,p;
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&name);
   MPI_Comm_size(MPI_COMM_WORLD,&p);
   printf("Proceso: %d \n",name);
   int nDatos = (N/(p-1));
   int nDatosU = N/(p-1)+ N%(p-1);
   int suma = 0;
   int sumap;
   int i;
   int *A;
   MPI_Status Status;
   if(name==Master)
   {
	reservaMem(&A,N);
	srand(time(NULL));
	generaRandoms(A,N);
	for(i=1;i<=(p-1);i++){
		if(i == (p-1)){
			MPI_Send(A+((i-1)*nDatos),nDatosU,MPI_INT,i,0,MPI_COMM_WORLD);
		}
		MPI_Send(A+((i-1)*nDatos),nDatos,MPI_INT,i,0,MPI_COMM_WORLD);
	}
	for(i=1;i<=(p-1);i++){
		MPI_Recv(&sumap,1,MPI_INT,i,0,MPI_COMM_WORLD,&Status);
		suma += sumap;
	}
	printf("La suma es: %d",suma);
	MPI_Finalize();
   }else{
	if(name == (p-1))
		nDatos = nDatosU;
	int* aux;
	reservaMem(&aux,nDatos);
	MPI_Recv(aux,nDatos,MPI_INT,Master,0,MPI_COMM_WORLD,&Status);
	
	for(i=0;i<nDatos;i++){
		suma += aux[i];
	}
	MPI_Send(&suma,1,MPI_INT,Master,0,MPI_COMM_WORLD);
	MPI_Finalize();
   }
   return 0;
}

void reservaMem(int **array,int n){
	*array = (int*)malloc (n*sizeof(int));
}

void generaRandoms(int *array, int n){
	int j;
	printf("Numeros generados: \n");
	for(j=0; j<n ;j++){
		array[j] = (rand()%150+1);
		printf("%d: %d \n",j+1,array[j]);
	} 
}
