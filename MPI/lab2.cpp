#include <iostream>
#include <mpi.h>

#define FILESIZE 40*4
#define int2 10

using namespace std;
int main(int argc, char** argv){

    
    MPI_Datatype blok, newtype; 

    int data[10];
    int pom = 10;

    MPI_File fh;
    int size, rank;
    int *buf, bufsize, iint;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);

    
    for(int i = 0; i < 10; i++){
        data[i] = rank*10 + i;
    }



    MPI_File_open(MPI_COMM_WORLD, "lab2.txt", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh);

    MPI_File_seek(fh, rank*int2*sizeof(int), MPI_SEEK_SET);
    MPI_File_write(fh, &data, int2, MPI_INT, &status);

    MPI_File_close(&fh);

    MPI_Barrier(MPI_COMM_WORLD);

    //citamo podatke iz fajla
    MPI_File_open(MPI_COMM_WORLD, "lab2.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

    bufsize = 10*sizeof(int);
    buf = (int*)malloc(bufsize);

    MPI_File_read_at(fh, rank*10*sizeof(int), buf, int2, MPI_INT, &status);

    printf("Rank %d/%d: ", rank, size);
    for (int i = 0; i < 10; i++) {
        printf("%d ", buf[i]);
    }
    printf("\n");
    MPI_File_close(&fh);

    MPI_Barrier(MPI_COMM_WORLD);

    //svaki proces upisuje po dva int i tako u krug
    MPI_File_open(MPI_COMM_WORLD, "lab2new.txt", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh);

    MPI_Type_contiguous(2, MPI_INT, &blok);
    MPI_Type_create_resized(blok, 0, 2*sizeof(int)*size, &newtype);

    MPI_Type_commit(&newtype);

    MPI_File_set_view(fh, 0, MPI_INT, newtype, "native", MPI_INFO_NULL);
    MPI_File_write(fh, buf, 10, MPI_INT, &status);
    MPI_File_close(&fh);


    MPI_Barrier(MPI_COMM_WORLD);
    //provera da li se lepo upisalo
    bufsize = 10*sizeof(int);
    buf = (int*)malloc(bufsize);

    MPI_File_open(MPI_COMM_WORLD, "lab2new.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

    MPI_File_read_at(fh, rank*10*sizeof(int), buf, int2, MPI_INT, &status);

    printf("Rank %d/%d: ", rank, size);
    for (int i = 0; i < 10; i++) {
        printf("%d ", buf[i]);
    }
    printf("\n");
    MPI_File_close(&fh);

    free(buf);
    MPI_Finalize();

    return 0;
}