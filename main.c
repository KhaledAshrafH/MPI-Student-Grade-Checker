#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    // file
    const int NumberOfStudent = 20;
    char line[50];
    int ID[NumberOfStudent];
    int grade[NumberOfStudent];
    FILE *file = fopen("students.txt", "r");

    int PassedTheExam;
    int parthial_sum, FinalPassed;

    int my_rank; /* rank of process */
    int p;       /* number of process */
    int source;  /* rank of sender */
    int dest;    /* rank of reciever */
    int tag = 0; /* tag for messages */
    int count = -1;
    int sum = 0;
    MPI_Status status; /* return status for */

    /* Start up MPI */
    MPI_Init(&argc, &argv);

    //////////////////////////////////////
    /* Find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    /* Find out number of process */
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    const int process = p - 1;

    int arr[process];
    double Students_per_process = (double) NumberOfStudent / (p - 1);

    if (my_rank == 0) /// master
    {
        if (process == 2) {
            for (int i = 0; i < process; i++) {
                arr[i] = Students_per_process + 0.5;
                sum += arr[i];
            }
        } else {
            for (int i = 0; i < p - 2; i++) {
                arr[i] = Students_per_process + 0.5;
                sum += arr[i];
            }

            arr[p - 2] = NumberOfStudent - sum;
        }

        ///////////////////////////////////////////
        if (file == NULL) {
            printf("error\n");
            return 0;
        }
        int k = 0;
        while (fgets(line, sizeof(line), file)) {
            int i = 0, j = 0;
            char temp1[10] = "";
            while (line[i] != ' ') {
                temp1[j++] += line[i++];
            }

            sscanf(temp1, "%d", &ID[k]);

            j = 0;
            i++;
            char temp2[3] = "";
            while (line[i] != '\0') {
                temp2[j++] += line[i++];
            }
            sscanf(temp2, "%d", &grade[k]);
            k++;
        }
        fclose(file);
        ////////////////////////////////////////////////////

        for (int i = 1; i < p; i++) // 1 2                  7   7   6
        {
            MPI_Send(&arr[i - 1], 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(&grade[(i - 1) * arr[i - 1]], arr[i - 1], MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(&ID[(i - 1) * arr[i - 1]], arr[i - 1], MPI_INT, i, tag, MPI_COMM_WORLD);
            printf("master send %d to process %d\n", arr[i - 1], i);
        }
        FinalPassed = 0;
        for (int i = 1; i < p; i++) {
            MPI_Recv(&parthial_sum, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
            FinalPassed += parthial_sum;
        }
        printf("Total Number Of Students Passed The Exam is %d out of %d\n", FinalPassed, NumberOfStudent);
    } else // other
    {

        MPI_Recv(&count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&grade, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&ID, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        PassedTheExam = 0;

        for (int i = 0; i < count; i++) {
            if (grade[i] >= 60) {
                printf("%d Passed The Exam\n", ID[i]);
                PassedTheExam++;
            } else {
                printf("%d Failed. Please Repeat The Exam\n", ID[i]);
            }
        }

        MPI_Send(&PassedTheExam, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    /* shutdown MPI */
    MPI_Finalize();
    return 0;
}