

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h> 
#define max_rows 100000
int array[max_rows];

void main(int argc, char **argv) 
   {
      long int sum, partial_sum,start_time,end_time;
      MPI_Status status;
	  int my_id, root_process, ierr, i, num_rows, num_procs, ista, iend
         an_id, num_rows_to_receive, avg_rows_per_process, 
         sender, num_rows_received, start_row, end_row, num_rows_to_send;

      /* Now replicte this process to create parallel processes.
       * From this point on, every process executes a seperate copy
       * of this program */

      ierr = MPI_Init(&argc, &argv);
      
      root_process = 0;
      
      /* find out MY process ID, and how many processes were started. */
      
      ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
      ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
      start_time = MPI_Wtime();
      printf("Start_Process %ld for processor %d\n",start_time,my_id);

      ista = my_id * 3 + 1
 	  iend = ista + 2

 	  for (i=ista;i<=iend,i++)
 	  	array(i)=i;
 	  end

 	  sum = 0;

 	  for(i=ista;i<=end;i++)
 	   sum = sum+array(i);
 	  end 

 	  MPI_Reduce(&array,&sum,3,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

 	  if(my_id == 0)
 	  printf("sum = %ld",sum);
 	  end

 	  end_time = MPI_Wtime();
      printf("End_time %ld for processor %d\n",end_time,my_id);
      printf("Total time by processor %d in seconds is %ld\n",my_id,(end_time-start_time));

      ierr = MPI_Finalize();
   }



 REAL a(9)
 REAL*8 END_TIME,START_TIME
 CALL MPI_INIT(ierr)
 CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
 CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)
 START_TIME=MPI_Wtime()
 print*,'start',myrank,START_TIME

 ista = myrank * 3 + 1
 iend = ista + 2

PRINT *,'myrank',myrank,'ista=',ista,'iend=',iend

 DO i=ista,iend
 a(i) = i

 ENDDO
 sum = 0.0
 DO i=ista,iend
 sum = sum + a(i)
 ENDDO

PRINT *,'myrank',myrank,'sum =',sum

 CALL MPI_REDUCE(sum, tmp, 1, MPI_REAL, MPI_SUM, 0,MPI_COMM_WORLD, ierr)
 sum = tmp
 IF (myrank==0) THEN
 PRINT *,'sum =',sum
 ENDIF
 END_TIME=MPI_Wtime()

 print*,'end',myrank,END_TIME
 print*,'run time(microsec)',myrank,(END_TIME-START_TIME)*1000000

 CALL MPI_FINALIZE(ierr)
 END

