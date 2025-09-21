#include <iostream>
#include <mpi.h>

#define FILESIZE 40*4
#define int2 10
#define N 15

using namespace std;
int main(int argc, char** argv){

    
    MPI_Datatype blok, newtype; 

    int data[N];
    int pom = 10;

    MPI_File fh;
    int size, rank;
    int *buf, bufsize, iint;
    MPI_Status status;
    int offset;        
    int* b;

    MPI_Init(&argc, &argv);
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);

    
    for(int i = 0; i < N; i++){
        data[i] = rank*10 + i;
    }

    offset = (size - 1 - rank) * N * sizeof(int);
    MPI_File_open(MPI_COMM_WORLD, "jun2024.txt", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh);

    MPI_File_seek(fh, offset, MPI_SEEK_SET);
    MPI_File_write(fh, &data, N, MPI_INT, &status);

    MPI_File_close(&fh);


    bufsize = N*4;
    buf = (int*)malloc(bufsize);

    // 2.
    MPI_File_open(MPI_COMM_WORLD, "jun2024.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

    // MPI_File_seek(fh, rank*N*4, MPI_SEEK_SET);
    MPI_File_read_at(fh, rank*N*4, buf, N, MPI_INT, &status);

    // printf("Rank %d/%d: ", rank, size);
    // for (int i = 0; i < 10; i++) {
    //     printf("%d ", buf[i]);
    // }
    // printf("\n");

    MPI_File_close(&fh);

    MPI_Barrier(MPI_COMM_WORLD);

    // 3.
    MPI_File_open(MPI_COMM_WORLD, "jun2024novo.txt", MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &fh);

    // MPI_Type_contiguous(1, MPI_INT, &blok);
    // MPI_Type_create_resized(blok, 0, size*4, &newtype);
    // MPI_Type_commit(&newtype);

    // MPI_File_set_view(fh, rank*4, MPI_INT, newtype, "native", MPI_INFO_NULL);

    // MPI_File_write(fh, buf, N, MPI_INT, &status);
    //MPI_Datatype blok, newtype; 
    int written = 0;
    for (int k = 1; written < N; k++) {

        int count = (written + k <= N) ? k : (N - written);

        int ukupno = size * (k - 1) * k / 2;

        MPI_Offset offset = (ukupno + rank * count) * sizeof(int);

        MPI_File_write_at(fh, offset, &data[written], count, MPI_INT, &status);

        written += count;
    }

    MPI_File_close(&fh);
    //printf("program puca");


    MPI_Barrier(MPI_COMM_WORLD);
    // provera

    //printf("2program puca");

    b = (int*)malloc(N*4*size);
    MPI_File_open(MPI_COMM_WORLD, "jun2024novo.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

    MPI_File_read_at(fh, 0, b, N*size, MPI_INT, &status);

    if (rank == 0) {
    printf("Sadržaj fajla: ");
    for (int i = 0; i < N*size; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
}
    MPI_File_close(&fh);



    MPI_Finalize();

    return 0;
}