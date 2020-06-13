#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

	int size, rank;

	MPI_Init(&argc,&argv);
		
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status stat;

	//cout << "Sono il nodo "<<rank<<" dei "<<size<<" che hai utilizzato" << endl;

	int itag = 1, imesg;
	
	int set[5];

	if(rank == 0)
		for(int i =0; i<5; i++)
			set[i] = 2*i;

	if(rank ==1)
		for(int i =0; i<5; i++)
			set[i] = 2*i+1;

	for(int i=0;i<5;i++){
		imesg = set[i];
		if(rank == 1){
			MPI_Send(&imesg,1,MPI_INTEGER,0,itag,MPI_COMM_WORLD);
		}
		if(rank ==0){
			MPI_Recv(&imesg,1,MPI_INTEGER,1,itag,MPI_COMM_WORLD,&stat);
			set[i] = imesg;
		}
	}

	cout << "Sono il nodo "<<rank<<" dei "<<size<<" che hai utilizzato" << endl;
	cout << endl << endl << "Set "<<rank<<": ";
	for(int i=0;i<5;i++) {
		cout << set[i] << " ";
	}

	MPI_Finalize();
 

	return 0;
}
