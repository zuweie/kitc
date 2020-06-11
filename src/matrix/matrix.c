/*
 * @Author: your name
 * @Date: 2020-06-09 16:11:26
 * @LastEditTime: 2020-06-11 17:07:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /kitc/src/matrix/matrix.c
 */ 
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

Matrix* Matrix_create(size_t row, size_t col) 
{
    Matrix* matrix = (Matrix*) malloc (sizeof(Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->data = (float*)malloc(row*col*sizeof(float));
    memset(matrix->data, 0, col*row*sizeof(float));
    return matrix;
}

Matrix* Matrix_create_by ( size_t row, size_t col, float *data) 
{
    Matrix* matrix = (Matrix*) malloc (sizeof(Matrix));
    matrix->row = row;
    matrix->col = col;
    matrix->data = (float*)malloc((col * row *sizeof(float)));
    memcpy(matrix->data, data, (row*col*sizeof(float)));
    return matrix;

}

int Matrix_destroy (Matrix* matrix) 
{
    free(matrix->data);
    free(matrix);
    return 0;
}

Matrix* Matrix_create_transpose (Matrix*  o_matrix) 
{
    Matrix* matrix = NULL;

    if (o_matrix->col == 1 || o_matrix->row == 1) {
        matrix = Matrix_create_by(o_matrix->col, o_matrix->row, o_matrix->data);
    }else {
        matrix = Matrix_create(o_matrix->col, o_matrix->row);
        float (*data)[o_matrix->row] = (float (*)[o_matrix->row]) malloc ((o_matrix->col)*(o_matrix->row)*sizeof(float));
        for (int j=0; j<o_matrix->col; ++j) {
            for (int i=0; i<o_matrix->row; ++i) {
                data[j][i] = Matrix_data(o_matrix)[i][j];
            }
        }
        matrix->data = data;
    }
    return matrix;
}