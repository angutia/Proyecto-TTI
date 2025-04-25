// $Header$
//------------------------------------------------------------------------------
// matrix
//------------------------------------------------------------------------------
// ProyectoTTI: Proyecto Taller Transversal I
//
// **Legal**
//
// Created: 2025/03/28
//
/** @file matrix.h
*   @brief This header contains the matrix operations.
*
*   @author Ander Gutiérrez Andrés.
*   @bug No known bugs.
*/
//------------------------------------------------------------------------------


#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class Matrix {
public:
    int n_row, n_column;
	double **data;

    // Parameterized constructor
	
	//------------------------------------------------------------------------------
	// Matrix(const int n_row, const int n_column)
	//------------------------------------------------------------------------------
	/**
	* @brief Creates a new matrix.
	*
	*/
	//------------------------------------------------------------------------------
    Matrix();
	
	//------------------------------------------------------------------------------
	// Matrix(const int n_row, const int n_column)
	//------------------------------------------------------------------------------
	/**
	* @brief Creates a new matrix.
	*
	* @param [in] n_row Number of rows of the matrix to be created.
	* @param [in] n_column Number of columns of the matrix to be created.
	*/
	//------------------------------------------------------------------------------
    Matrix(const int n_row, const int n_column);
	
	//------------------------------------------------------------------------------
	// Matrix(const int v_size)
	//------------------------------------------------------------------------------
	/**
	* @brief Creates a new vector.
	*
	* @param [in] v_size Size of the vector to be created.
	*/
	//------------------------------------------------------------------------------
	Matrix(const int v_size);
	
	// Member operators
	
	//------------------------------------------------------------------------------
	// operator () (const int row, const int column)
	//------------------------------------------------------------------------------
	/**
	* @brief Returns the element (row, column) of a matrix.
	*
	* @param [in] row Row of the matrix to extract the element from.
	* @param [in] column Column of the matrix to extract the element from.
	* @return The corresponding element of the matrix.
	*/
	//------------------------------------------------------------------------------
	double& operator () (const int row, const int column);
	
	//------------------------------------------------------------------------------
	// operator () (const int n)
	//------------------------------------------------------------------------------
	/**
	* @brief Returns the nth element of a vector.
	*
	* @param [in] n Number of element to extract from the vector.
	* @return The corresponding element of the vector.
	*/
	//------------------------------------------------------------------------------
	double& operator () (const int n);

    //------------------------------------------------------------------------------
    // operator + (Matrix &m)
    //------------------------------------------------------------------------------
    /**
     * @brief Adds a matrix to the current matrix.
     * 
     * @param m Matrix to be added.
     * @return The resulting matrix.
     */
	Matrix& operator + (Matrix &m);
	
	//------------------------------------------------------------------------------
    // operator + (double n)
    //------------------------------------------------------------------------------
    /**
     * @brief Adds a double to each element of the current matrix.
     * 
     * @param n Double to be added.
     * @return The resulting matrix.
     */
	Matrix& operator + (double n);

    //------------------------------------------------------------------------------
    // operator - (Matrix &m)
    //------------------------------------------------------------------------------
    /**
     * @brief Subtracts a matrix from the current matrix.
     * 
     * @param m Matrix to be subtracted.
     * @return The resulting matrix.
     */
	Matrix& operator - (Matrix &m);
	
	//------------------------------------------------------------------------------
    // operator - (double n)
    //------------------------------------------------------------------------------
    /**
     * @brief Subtracts a double from each element of the current matrix.
     * 
     * @param d Double to be subtracted.
     * @return The resulting matrix.
     */
	Matrix& operator - (double n);

    //------------------------------------------------------------------------------
    // operator * (Matrix &m)
    //------------------------------------------------------------------------------
    /**
     * @brief Multiplies the current matrix by another matrix.
     * 
     * @param m Matrix to be multiplied.
     * @return The resulting matrix.
     */
	Matrix& operator * (Matrix &m);
	
	//------------------------------------------------------------------------------
    // operator * (double n)
    //------------------------------------------------------------------------------
    /**
     * @brief Multiplies each element of the current matrix by a double.
     * 
     * @param n Double to be multiplied.
     * @return The resulting matrix.
     */
	Matrix& operator * (double n);

    //------------------------------------------------------------------------------
    // operator / (Matrix &m)
    //------------------------------------------------------------------------------
    /**
     * @brief Divides the current matrix by another matrix.
     * 
     * @param m Matrix to be divided.
     * @return The resulting matrix.
     */
	Matrix& operator / (Matrix &m);
	
	//------------------------------------------------------------------------------
    // operator = (Matrix &m)
    //------------------------------------------------------------------------------
    /**
     * @brief Copies another matrix in the current matrix.
     * 
     * @param m Matrix to be assigned.
     * @return The resulting matrix.
     */
	Matrix& operator = (Matrix &m);
	

	// Non-member operators

    //------------------------------------------------------------------------------
    // operator << (ostream &o, Matrix &m)
    //------------------------------------------------------------------------------
    /**
     * @brief Prints the matrix to the output stream.
     * 
     * @param o Output stream to print the matrix to.
     * @param m Matrix to be printed.
     */
	friend ostream& operator << (ostream &o, Matrix &m);
};

// Operator overloading
ostream& operator << (ostream &o, Matrix &m);

// Methods

//------------------------------------------------------------------------------
// zeros(const int n_row, const int n_column)
//------------------------------------------------------------------------------
/**
 * @brief Creates a matrix of zeros.
 * 
 * @param n_row Number of rows of the matrix to be created.
 * @param n_column Number of columns of the matrix to be created.
 * @return The created matrix.
 */
Matrix& zeros(const int n_row, const int n_column);

//------------------------------------------------------------------------------
// inv (Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Inverts a matrix.
 * 
 * @param m Matrix to be inverted.
 * @return The inverted matrix.
 */
Matrix& inv (Matrix &m);

//------------------------------------------------------------------------------
// det (Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calculates the determinant of a matrix.
 * 
 * @param m Matrix to calculate the determinant of.
 * @return The determinant of the matrix.
 */
double det (Matrix &m);

//------------------------------------------------------------------------------
// eye (const int n)
//------------------------------------------------------------------------------
/**
 * @brief Creates an identity matrix.
 * 
 * @param n Size of the identity matrix to be created.
 * @return The created identity matrix.
 */
Matrix& eye(const int n);

//------------------------------------------------------------------------------
// transpose(Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Transposes a matrix.
 * 
 * @param m Matrix to be transposed.
 * @return The transposed matrix.
 */
Matrix& transpose(Matrix &m);

#endif