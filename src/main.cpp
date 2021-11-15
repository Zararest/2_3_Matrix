#include "./headers/Matrix.hpp"

#define MATRIX_SIZE 10

int main(){
    
    std::ifstream inp_stream("../bin/input.txt");
    std::ofstream out_stream("../bin/output.txt");
    Matrix<int> new_matr(MATRIX_SIZE, MATRIX_SIZE, inp_stream);
    
    std::cout << new_matr.determinant() << std::endl;
    new_matr.dump(out_stream);
}