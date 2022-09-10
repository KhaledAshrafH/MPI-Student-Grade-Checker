# Student-Success-Check
MPI program that takes the input of a group of students in their grades and check who has succeeded and who has not, and knows the ratio of success to failure (parallel processing).
<br>

# Master process (rank 0)
  - Read data from file
  - Divide the students list by the number of processes you have then send it to them.
  - Print the summation of the number of passed students received from each process.<br>
# For each process
  - Receive part of students data
  - Check if they passed or not and print message for each student
<Student ID> Passed The Exam
<Student ID> Failed. Please Repeat The Exam
- Calculate number of passed student then send it to master process (rank 0)
