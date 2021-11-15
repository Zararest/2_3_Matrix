#include "./headers/Matrix.hpp"

template <typename T>
Matrix<T>::Matrix(int new_vert_size, int new_hor_size, std::ifstream& input_stream){

    int num_of_elements = new_vert_size * new_hor_size;
    vert_size = new_vert_size;
    hor_size = new_hor_size;
    data = new T[num_of_elements];

    for (int i = 0; i < num_of_elements; i++){

        if (!input_stream.eof()){

            input_stream >> data[i];
        } else{

            data[i] = 0;
            error = wrong_input;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(int new_vert_size, int new_hor_size, const T* new_data){

    int num_of_elements = new_vert_size * new_hor_size;
    vert_size = new_vert_size;
    hor_size = new_hor_size;
    data = new T[num_of_elements];

    memcpy(data, new_data, num_of_elements * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& old_matr){

    int num_of_elements = old_matr.vert_size * old_matr.hor_size;
    vert_size = old_matr.vert_size;
    hor_size = old_matr.hor_size;
    error = old_matr.error;

    delete[] data;
    data = new T[num_of_elements, old_matr.data];
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& tmp_matr){

    vert_size = tmp_matr.vert_size;
    hor_size = tmp_matr.hor_size;
    error = tmp_matr.error;

    std::swap(data, tmp_matr.data);
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& old_matr){

    if (this == &old_matr){ return *this; }

    int num_of_elements = old_matr.vert_size * old_matr.hor_size;
    vert_size = old_matr.vert_size;
    hor_size = old_matr.hor_size;
    error = old_matr.error;

    delete[] data;
    data = new T[num_of_elements, old_matr.data];

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(Matrix<T>&&  tmp_matr){

    if (this == &tmp_matr){ return *this; }

    vert_size = tmp_matr.vert_size;
    hor_size = tmp_matr.hor_size;
    error = tmp_matr.error;

    std::swap(data, tmp_matr.data);

    return *this;
}

template <typename T>
Matrix<T>::~Matrix(){

    delete[] data;
}

int not_del_elem(int* deleted_columns, int deleted_rows_count){

    bool elem_has_found = false;

    for (int i = 0; i <= deleted_rows_count; i++){

        for (int j = 0; j < deleted_rows_count; j++){

            if (deleted_columns[j] == i){

                elem_has_found = true;
            }
        }

        if (!elem_has_found){ return i;}

        elem_has_found = false;
    }

    return -1;
}

bool check_deleted(int elem, int* array, int arr_size){

    for (int i = 0; i < arr_size; i++){

        if (array[i] == elem){ return true; }
    }

    return false;
}

template <typename T>
T Matrix<T>::minor(const Matrix& cur_matr, int deleted_rows_count, int* deleted_columns){

    //поскольку мы вычеркиваем и строку и столбец, то на каждом шаге количество удаленных строк и столбцов одинаковое
    assert(cur_matr.vert_size == cur_matr.hor_size);
    int cur_matr_size = cur_matr.vert_size;
    int next_deleted_col = 0, minor_size = cur_matr_size - deleted_rows_count, cur_size = 0;
    T minor_determ = 0, next_minor = 0;

    if (deleted_rows_count + 1 != cur_matr_size){

        for (int next_deleted_col = 0; next_deleted_col < cur_matr_size; next_deleted_col++){

            assert(next_deleted_col < cur_matr_size);
            if (!check_deleted(next_deleted_col, deleted_columns, deleted_rows_count)){

                if (cur_size % 2 == 0){

                    next_minor = minor(cur_matr, deleted_rows_count + 1, deleted_columns);
                    minor_determ += cur_matr[deleted_rows_count][next_deleted_col] * next_minor;
                } else{

                    next_minor = minor(cur_matr, deleted_rows_count + 1, deleted_columns);
                    minor_determ += (-1) * cur_matr[deleted_rows_count][next_deleted_col] * next_minor;
                }
                cur_size++;
            }
        }

        return minor_determ;
    } else{

        int last_row = deleted_rows_count;
        int cur_single_minor = not_del_elem(deleted_columns, deleted_rows_count);
        assert(cur_single_minor != -1);
        return cur_matr[last_row][cur_single_minor];
    }
}

template <typename T>
T Matrix<T>::determinant() const{

    if (vert_size != hor_size){

        error = wrong_matr_size;
        return 0;
    }

    T determ = 0;
    int* deleted_columns = new int[hor_size];

    for (int i = 0; i < hor_size; i++){

        deleted_columns[0] = i;

        if ((i % 2) == 0){

            determ += data[i] * minor(*this, 1, deleted_columns);
        } else{

            determ += (-1) * data[i] * minor(*this, 1, deleted_columns);
        }
    }

    delete[] deleted_columns;
    return determ;
}
