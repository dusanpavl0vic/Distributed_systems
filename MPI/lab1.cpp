#include <iostream>
#include <mpi.h>

#define FILESIZE 21*4

using namespace std;
int main(int argc, char** argv){
    int data[21] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    FILE *f = fopen("lab1file.txt", "wb"); // binary mode
    fwrite(data, sizeof(int), 12, f);
    fclose(f);

    int rank, size;
    MPI_Status status;
    MPI_File fh;
    int *buf, bufsize, nint;
    MPI_Datatype blokInt, tip1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    bufsize = FILESIZE/size; // ukupna 16bajta po procesu (po 4 int broja)
    buf = (int*)malloc(bufsize);
    nint = bufsize/sizeof(int); // koliko int vrednosti cita iz fajla sad 4

    MPI_Type_contiguous( 2 , MPI_INT , &blokInt);
    MPI_Type_create_resized(blokInt, 0, bufsize + 4*2, &tip1);

    MPI_Type_commit(&tip1);
    MPI_Type_commit(&blokInt);


    MPI_File_open(MPI_COMM_WORLD, "lab1file.txt", MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, rank*sizeof(int)*2, MPI_INT, tip1, "native", MPI_INFO_NULL);

    // MPI_File_seek(fh, rank*bufsize, MPI_SEEK_SET);
    MPI_File_read(fh, buf, 4, MPI_INT, &status);

    MPI_File_close(&fh);

    printf("Rank %d/%d: ", rank, size);
    for (int i = 0; i < nint; i++) {
        printf("%d ", buf[i]);
    }
    printf("\n");


    


    MPI_Finalize();

    return 0;
}