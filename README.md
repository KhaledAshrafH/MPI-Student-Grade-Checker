# MPI Student Grade Checker

It's a high-performance computing program that utilizes MPI (Message Passing Interface) to process a list of student grades in parallel and determine which students have passed the exam and which ones need to repeat it.

## Features

- Parallel processing of student grades using MPI.
- Efficient distribution of data to multiple processes for concurrent evaluation.
- Calculation of the total number of students who passed the exam.
- Identification of individual students who passed or failed the exam.
- Detailed console output with pass/fail messages for each student.
- Support for large datasets by dividing the workload among multiple processes.
- Flexibility to adjust the number of processes based on system configuration.

## Getting Started

### Prerequisites

- MPI implementation (e.g., Open MPI, MPICH)
- C compiler (e.g., GCC)

### Installation

1. Clone the repository:

```bash
git clone https://github.com/KhaledAshrafH/MPI-Student-Grade-Checker.git
```

2. Compile the source code using the MPI compiler wrapper:

```bash
mpicc main.c -o grade_checker
```

### Usage

1. Prepare the input file students.txt with the list of students' IDs and their corresponding grades. The file format should be as follows:

```bash
20190186 95
20190888 60
...
```

2. Run the MPI program:

```bash
mpirun -np <num_processes> ./grade_checker
```

Replace <num_processes> with the desired number of MPI processes to be used for parallel processing. It should be greater than 1.

3. View the console output to see the pass/fail messages for each student and the total number of students who passed the exam.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request.

## Authors

- [Khaled Ashraf Hanafy Mahmoud - 20190186](https://github.com/KhaledAshrafH).
- [Ahmed Sayed Hassan Youssef - 20190034](https://github.com/AhmedSayed117).
- [Samah Moustafa Hussien Mahmoud - 20190248](https://github.com/Samah-20190248).


## License

This project is licensed under the [MIT License](LICENSE.md).


