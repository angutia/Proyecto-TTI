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
		cout << "Vector create: error in data\n";
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

Matrix& Matrix::operator * (double n) {
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) * n;
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

Matrix& Matrix::operator / (double n) {
    if (n == 0) {
        cout << "Matrix div: division by zero\n";
        exit(EXIT_FAILURE);
    }

    Matrix *m_aux = new Matrix(this->n_row, this->n_column);
    
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
            (*m_aux)(i,j) = (*this)(i,j) / n;
        }
    }
    
    return *m_aux;
}

Matrix& Matrix::operator = (Matrix &m) {

    this->n_row = m.n_row;
	this->n_column = m.n_column;
    this->data = (double **) malloc(this->n_row*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(this->n_column*sizeof(double));
	}

    for(int i = 1; i <= m.n_row; i++) {
        for(int j = 1; j <= m.n_column; j++) {
			this->data[i - 1][j - 1] = m(i,j);
		}
	}
	
	return *this;
}

Matrix& Matrix::extract_vector(const int start, const int end) {
    if (this->n_row > 1 || start < 1 || end > this->n_column || start > end) {
        cout << "Matrix extract_vector: error in start/end\n";
        exit(EXIT_FAILURE);
    }
    
    Matrix *m_aux = new Matrix(end - start + 1);
    
    for(int i = start; i <= end; i++) {
        (*m_aux)(i - start + 1) = (*this)(i);
    }
    
    return *m_aux;
}

Matrix& Matrix::extract_row(const int row) {
    if (row < 1 || row > this->n_row) {
        cout << "Matrix extract_row: error in row\n";
        exit(EXIT_FAILURE);
    }
    
    Matrix *m_aux = new Matrix(this->n_column);
    
    for(int i = 1; i <= this->n_column; i++) {
        (*m_aux)(i) = (*this)(row,i);
    }
    
    return *m_aux;
}

Matrix& Matrix::extract_column(const int column) {
    if (column < 1 || column > this->n_column) {
        cout << "Matrix extract_column: error in column\n";
        exit(EXIT_FAILURE);
    }
    
    Matrix *m_aux = new Matrix(this->n_row);
    
    for(int i = 1; i <= this->n_row; i++) {
        (*m_aux)(i) = (*this)(i,column);
    }
    
    return *m_aux;
}

void Matrix::assign_row(const int row, Matrix &m) {
    if (row < 1 || row > this->n_row || m.n_column != this->n_column || m.n_row != 1) {
        cout << "Matrix assign_row: error in row\n";
        exit(EXIT_FAILURE);
    }
    
    for(int i = 1; i <= this->n_column; i++) {
        (*this)(row,i) = m(i);
    }
}

void Matrix::assign_column(const int column, Matrix &m) {
    if (column < 1 || column > this->n_column || m.n_column != this->n_row || m.n_row != 1) {
        cout << "Matrix assign_column: error in column\n";
        exit(EXIT_FAILURE);
    }
    
    for(int i = 1; i <= this->n_row; i++) {
        (*this)(i,column) = m(i);
    }
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

Matrix& zeros(const int n) {
    Matrix *m_aux = new Matrix(n);
    
    for(int i = 1; i <= n; i++) {
        (*m_aux)(i) = 0;
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

double norm(Matrix &m) {
    if (m.n_row == 1 || m.n_column == 1) {
        double aux = 0.0;    
        for(int i = 1; i <= m.n_row; i++) {
            for(int j = 1; j <= m.n_column; j++) {
                aux += pow(m(i,j),2);
            }
        }        
        return sqrt(aux);
    }
    // Compute M^T * M
    Matrix mt = transpose(m);
    Matrix mtm = mt * m;
    
    // Use power iteration method to find largest eigenvalue
    Matrix v = zeros(m.n_column, 1);  // Initial vector
    v(1,1) = 1.0;  // Set first element to 1
    
    const int MAX_ITER = 100;
    const double TOLERANCE = 1e-10;
    double lambda_old = 0.0;
    
    for(int iter = 0; iter < MAX_ITER; iter++) {
        // w = M^T * M * v
        Matrix w = mtm * v;
        
        // Find largest element for normalization
        double norm_w = norm(w);
        
        // Normalize w
        Matrix v_new = w / norm_w;
        
        // Estimate eigenvalue
        double lambda = norm(w) / norm(v);
        
        // Check convergence
        if(fabs(lambda - lambda_old) < TOLERANCE) {
            return sqrt(lambda);  // Return square root as it's the singular value
        }
        
        lambda_old = lambda;
        v = v_new;
    }

    cout << "Matrix norm error: did not converge\n";
    exit(EXIT_FAILURE);
    return -1.0;  // Error: did not converge    
}

double dot(Matrix &v1, Matrix &v2) {
    if (v1.n_column != v2.n_column || v1.n_row != 1 || v2.n_row != 1) {
        cout << "Matrix dot: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
    }
    
    double aux = 0.0;
    
    for(int i = 1; i <= v1.n_column; i++) {
        aux += v1(i) * v2(i);
    }
    
    return aux;
}

Matrix& cross(Matrix &v1, Matrix &v2) {
    if (v1.n_column != 3 || v2.n_column != 3 || v1.n_row != 1 || v2.n_row != 1) {
        cout << "Matrix cross: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
    }
    
    Matrix *m_aux = new Matrix(3);
    
    (*m_aux)(1) = v1(2) * v2(3) - v1(3) * v2(2);
    (*m_aux)(2) = v1(3) * v2(1) - v1(1) * v2(3);
    (*m_aux)(3) = v1(1) * v2(2) - v1(2) * v2(1);
    
    return (*m_aux);
}

Matrix& union_vector(Matrix& v1, Matrix& v2) {
    if (v1.n_row != 1 || v2.n_row != 1) {
        cout << "Matrix union_vector: error in n_row\n";
        exit(EXIT_FAILURE);
    }
    
    int new_size = v1.n_column + v2.n_column;
    Matrix *m_aux = new Matrix(new_size);
    
    for(int i = 1; i <= v1.n_column; i++) {
        (*m_aux)(i) = v1(i);
    }
    
    for(int i = 1; i <= v2.n_column; i++) {
        (*m_aux)(i + v1.n_column) = v2(i);
    }
    
    return (*m_aux);
}