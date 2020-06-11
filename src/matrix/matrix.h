/*
 * @Author: your name
 * @Date: 2020-06-09 16:11:38
 * @LastEditTime: 2020-06-11 16:23:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /kitc/src/matrix/matrix.h
 */ 

#ifndef _MATRIX_H_
#define _MATRIX_H_
typedef struct _matrix 
{
    
    size_t row;
    size_t col;
    float* data;
    
} Matrix;

#define Matrix_data(matrix) ((float(*)[(matrix)->col])((matrix)->data))
#define Matrix_get(matrix,x,y) Matrix_data(matrix)[x][y]
#define Matrix_set(matrix,x,y,v) Matrix_data(matrix)[x][y]=v

Matrix* Matrix_create(size_t, size_t);
Matrix* Matrix_create_by(size_t, size_t, float* data);
Matrix* Matrix_create_transpose (Matrix*);
int Matrix_destroy(Matrix*);



#endif