   #include <stdio.h>
   #include <mpi.h>
   #include <stdlib.h>   
   #define max_rows 1000000
   #define send_data_tag 2001
   #define return_data_tag 2002

   int array[max_rows];
   int array2[max_rows];
   
   void main(int argc, char **argv) 
   {
      double start_time,end_time;
      long int sum, partial_sum;
      MPI_Status status;
      int my_id, root_process, ierr, i, num_rows, num_procs,
         an_id, num_rows_to_receive, avg_rows_per_process, 
         sender, num_rows_received, start_row, end_row, num_rows_to_send;
      root_process = 0;

      ierr = MPI_Init(&argc, &argv);      
      ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
      ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
      start_time = MPI_Wtime();
      printf("Start_Process %lf for processor %d\n",start_time,my_id);	
      if(my_id == root_process) {

         num_rows = 999999;
         avg_rows_per_process = num_rows / num_procs;

         for(i = 0; i < num_rows; i++) {
            array[i] = i + 1;
         }

         for(an_id = 1; an_id < num_procs; an_id++) {
            start_row = an_id*avg_rows_per_process + 1;
            end_row   = (an_id + 1)*avg_rows_per_process;

            if((num_rows - end_row) < avg_rows_per_process)
               end_row = num_rows - 1;
            num_rows_to_send = end_row - start_row + 1;

            ierr = MPI_Send( &num_rows_to_send, 1 , MPI_INT,
                  an_id, send_data_tag, MPI_COMM_WORLD);

            ierr = MPI_Send( &array[start_row], num_rows_to_send, MPI_INT,
                  an_id, send_data_tag, MPI_COMM_WORLD);
         }
        
         sum = 0;
         for(i = 0; i < avg_rows_per_process + 1; i++) {
            sum += array[i];   
         } 

         printf("sum %ld calculated by root process\n", sum);

         for(an_id = 1; an_id < num_procs; an_id++) {
            ierr = MPI_Recv( &partial_sum, 1, MPI_LONG, MPI_ANY_SOURCE,
                  return_data_tag, MPI_COMM_WORLD, &status);
            sender = status.MPI_SOURCE;
            printf("Partial sum %ld returned from process %i\n", partial_sum, sender);
            sum += partial_sum;
         }

         printf("The grand total is: %ld\n", sum);
      }

      else {
         ierr = MPI_Recv( &num_rows_to_receive, 1, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);
          
         ierr = MPI_Recv( &array2, num_rows_to_receive, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);

         num_rows_received = num_rows_to_receive;

         partial_sum = 0;
         for(i = 0; i < num_rows_received; i++) {
            partial_sum += array2[i];
         }
         ierr = MPI_Send( &partial_sum, 1, MPI_LONG, root_process, 
               return_data_tag, MPI_COMM_WORLD);
      }
      end_time = MPI_Wtime();
      printf("End_time %lf for processor %d\n",end_time,my_id);
      printf("Total time by processor %d in microseconds is %lf\n",my_id,(end_time-start_time)*1000000);
      ierr = MPI_Finalize();
   }
