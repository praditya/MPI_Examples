
#include <stdio.h>
#include <mpi.h>

void main(int argc, char **argv) 
   {
      double partial_sum,start_time,end_time;
      int my_id, sum, g_sum, ierr, i, num_rows, num_procs, ista, iend, array[999999]={0};
      
      ierr = MPI_Init(&argc, &argv);
      ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
      ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
      start_time = MPI_Wtime();
      printf("Start_Process %lf for processor %d\n",start_time,my_id);

      ista = my_id * 333333 + 1;
 	  iend = ista + 333333;

 	  for (i=ista;i<=iend;i++)
 	  	array[i]=i;
 	  sum = 0;
 	  for(i=ista;i<=iend;i++)
 	   sum = sum + array[i];

 	  MPI_Reduce(&sum,&g_sum,3,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

 	  if(my_id == 0)
 	  printf("TOTAL sum = %d\n ",g_sum);
 	  end_time = MPI_Wtime();
      printf("End_time %lf for processor %d\n",end_time,my_id);
      printf("Total time by processor %d in microseconds is %lf\n",my_id,(end_time-start_time)*1000000);

      ierr = MPI_Finalize();
   }
 
