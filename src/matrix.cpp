// $Source$
//------------------------------------------------------------------------------
// matrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file matrix.cpp
*   @brief Source of the matrix operations.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------


#include "..\include\matrix.hpp"


Matrix::Matrix() {	
	this->n_row = 0;
	this->n_column = 0;
	this->data = nullptr;
}


Matrix::Matrix(const int v_size) {
    if (v_size < 0) {
		cout << "Vector create: error in v_size\n";
        exit(EXIT_FAILURE);
	}    
	
	this->n_row = 1;
	this->n_column = v_size;
	this->data = (double **) malloc(n_row*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	this->data[0] = (double *) calloc(v_size,sizeof(double));
}


Matrix::Matrix(const int n_row, const int n_column) {
    if (n_row <= 0 || n_column <= 0) {
		cout << "Matrix create: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	this->n_row = n_row;
	this->n_column = n_column;
	this->data = (double **) malloc(n_row*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(n_column*sizeof(double));
	}
}


double& Matrix::operator () (const int n) {
	if (n <= 0 || n > this->n_row*this->n_column) {
		cout << "Vector get: error in row/column\n";
        exit(EXIT_FAILURE);
	}
	
	return this->data[(n - 1)/this->n_column][(n - 1)%this->n_column];
}


double& Matrix::operator () (const int row, const int column) {
	if (row <= 0 || row > this->n_row || column <= 0 || column > this->n_column) {
		cout << "Matrix get: error in row/column\n";
        exit(EXIT_FAILURE);
	}
	
	return this->data[row - 1][column - 1];
}

Matrix& Matrix::operator + (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sum: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator + (double n) {
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + n;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (double n) {
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - n;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator * (Matrix &m) {
	if (this->n_column != m.n_row) {
		cout << "Matrix mul: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, m.n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= m.n_column; j++) {
			double aux = 0.0;
			for(int k = 1; k <= this->n_column; k++) {
				aux = aux + (*this)(i,k) * m(k,j);
			}
			(*m_aux)(i,j) = aux;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator / (Matrix &m) {
	if (m.n_column != m.n_row) {
		cout << "Matrix div: error in n_row/n_column (non-square matrix)\n";
        exit(EXIT_FAILURE);
	}

	if (this->n_column != m.n_row) {
		cout << "Matrix div: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix m_aux = inv(m);
	
	return (*this)*m_aux;
}

Matrix& Matrix::operator = (Matrix &m) {
	
	Matrix *m_aux = new Matrix(m.n_row, m.n_column);
	
    for(int i = 1; i <= m.n_row; i++) {
        for(int j = 1; j <= m.n_column; j++) {
			(*m_aux)(i,j) = m(i,j);
		}
	}
	
	this->n_row = m_aux->n_row;
	this->n_column = m_aux->n_column;
	this->data = m_aux->data;
	
	return *this;
}

ostream& operator << (ostream &o, Matrix &m) {
	for (int i = 1; i <= m.n_row; i++) {
        for (int j = 1; j <= m.n_column; j++)
			printf("%5.20lf ", m(i,j));
        o << "\n";
    }
	
    return o;
}

Matrix& inv (Matrix &m) {
	if (m.n_column != m.n_row) {
		cout << "Matrix inv: error in n_row/n_column (non-square matrix)\n";
        exit(EXIT_FAILURE);
	}
	
	if (det(m)==0) {
		cout << "Matrix inv: error in n_row/n_column (non-invertible matrix)\n";
        exit(EXIT_FAILURE);
	}
	
	int r = m.n_row;
	int c = m.n_column;
	
	Matrix *m_aux = new Matrix(r, 2*c);
	for(int i = 1; i <= r; i++) {
		for(int j = 1; j <= c; j++) {
			(*m_aux)(i,j) = m(i,j);
		}
		
		for(int j = c+1; j <= 2*c; j++) {
			if (j==(i+c)) {
				(*m_aux)(i,j) = 1;
			} else {
				(*m_aux)(i,j) = 0;
			}
		}
	}	
	
	for(int i = 1; i <= r; i++) {
		double pivot = (*m_aux)(i,i);
		for(int j = 1; j <= 2*c; j++) {
			(*m_aux)(i,j) /= pivot;
		}
		
		for(int k = 1; k <= r; k++) {
            if (k != i) {
                double factor = (*m_aux)(k,i);
                for (int j = 1; j <= 2*c; j++) {
                    (*m_aux)(k,j) -= factor * (*m_aux)(i,j);
                }
            }
        }
	}
	
	Matrix *m_aux_inv = new Matrix(r, c);
	for(int i = 1; i <= r; i++) {		
		for(int j = 1; j <= c; j++) {
			(*m_aux_inv)(i,j) = (*m_aux)(i,j+c);
		}
	}
	
	return (*m_aux_inv);
}

double det (Matrix &m) {
	double aux_det = 0;
	Matrix *submatrix = new Matrix(m.n_row-1, m.n_column-1);
	if (m.n_row == 2){
		return ((m(1,1) * m(2,2)) - (m(2,1) * m(1,2)));
	} else {
		for (int x = 1; x <= m.n_row; x++) {
			int subi = 1;
			for (int i = 2; i <= m.n_row; i++) {
				int subj = 1;
				for (int j = 1; j <= m.n_row; j++) {
					if (j == x) {
						continue;
					}
					(*submatrix)(subi,subj) = m(i,j);
					subj++;
				}
				subi++;
			}
			aux_det = aux_det + (pow(-1, x+1) * m(1,x) * det(*submatrix));
		}
	}
	return aux_det;
}


Matrix& zeros(const int n_row, const int n_column) {
	Matrix *m_aux = new Matrix(n_row, n_column);
	
	for(int i = 1; i <= n_row; i++) {
		for(int j = 1; j <= n_column; j++) {
			(*m_aux)(i,j) = 0;
		}
	}
	
	return (*m_aux);
}


Matrix& eye(const int n) {
    Matrix *m_aux = new Matrix(n, n);
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == j) {
                (*m_aux)(i,j) = 1;
            } else {
                (*m_aux)(i,j) = 0;
            }
        }
    }
    
    return (*m_aux);
}


Matrix& transpose(Matrix &m) {
    Matrix *m_aux = new Matrix(m.n_column, m.n_row);
    
    for(int i = 1; i <= m.n_column; i++) {
        for(int j = 1; j <= m.n_row; j++) {
            (*m_aux)(i,j) = m(j,i);
        }
    }
    
    return (*m_aux);
}
