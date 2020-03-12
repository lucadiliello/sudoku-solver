# sudoku-solver
Efficient sudoku solver in C++

## Usage

Build the project with `make`
```bash
make all
```

Execute with
```bash
./bin/sudoku_solver <sudoku-file>
```

Clean build files and binaries with
```bash
make clean
```

with `<sudoku-file>` being a CSV file like `sudoku.csv`:
```
X,X,5,3,X,X,X,X,X
8,X,X,X,5,X,X,2,X
X,7,X,X,1,X,5,X,X
4,X,X,X,X,5,3,X,X
X,1,X,X,7,X,X,X,6
X,X,3,2,X,X,X,8,X
X,6,X,5,X,X,X,X,9
X,X,4,X,X,X,X,3,X
X,X,X,X,X,9,7,X,X
```