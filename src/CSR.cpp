//============================================================================
// Name        : CSR.cpp
// Author      : Avery Moates
// Version     : 0.0.1
// Description : Data Structures Project One.
//============================================================================

#include <iostream>
using namespace std;

class CSR {
protected:
	int n; //The number of rows of the original matrix
	int m; // The number of columns of the original matrix.
	int nonZeros; //The number of non-zeros in the original matrix.
	int currentValueIndex;
	int* values; //Value array assuming all are integers.
	int* rowPtr; //Array that contains number of non-zero elements in each row of the original matrix.
	int* colPos; //Array that contains the column number from the original matrix for the non-zero values

	//There may be other variables you may need.

public:
	CSR(); //Default or empty constructor
	CSR(CSR& matrixB); //Copy constructor
	CSR(int rows, int cols, int numNonZeros);
	int getNumRows();
	int getNumCols();
	int getNumNonZeros();
	int* getRowVec(int row);
	void addValue(int value); //Adds a new value in the values array
	void addColumn(int col); //Adds a column in the colPos array
	void addRow(int row); //Adds a row in the rowPtr array
	void display(); //Prints the contents of the three arrays. Each array must be on a different line and you have exactly a single space between each value printed.
	int* matrixVectorMultiply(int* inputVector); //Matrix-vector multiplication
	CSR* matrixMultiply(CSR& matrixB); //Matrix-matrix multiplication
	~CSR();

	//There may be other functions

};

//Some of the functions - Sridhar Radhakrishnan
CSR::CSR(){
	n = 0;
	m = 0;
	nonZeros = 0;
	currentValueIndex = -1;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}

CSR::CSR(CSR& matrixB){
	n = matrixB.getNumRows();
	m = matrixB.getNumCols();
	currentValueIndex = -1;
	nonZeros = matrixB.getNumNonZeros();
	values = new int[nonZeros];
	//setting all values in the array to negative values
	for(int i=0; i<nonZeros; ++i){
		values[i] = -1;
	}
	colPos = new int[nonZeros];
	//setting all values in the array to negative values
	for(int i=0; i<nonZeros; ++i){
		colPos[i] = -1;
	}
	rowPtr = new int[n];
	//setting all values in the array to negative values
	for(int i=0; i<n; ++i){
		rowPtr[i] = -1;
	}

}

CSR::CSR(int rows, int cols, int numNonZeros){
	n = rows;
	m = cols;
	currentValueIndex = -1;
	nonZeros = numNonZeros;
	values = new int[nonZeros];
	//setting all values in the array to negative values
	for(int i=0; i<nonZeros; ++i){
		values[i] = -1;
	}
	colPos = new int[nonZeros];
	//setting all values in the array to negative values
	for(int i=0; i<nonZeros; ++i){
		colPos[i] = -1;
	}
	rowPtr = new int[n];
	//setting all values in the array to negative values
	for(int i=0; i<n; ++i){
		rowPtr[i] = -1;
	}
}

int CSR::getNumRows(){
	return n;
}

int CSR::getNumCols(){
	return m;
}

int CSR::getNumNonZeros(){
	return nonZeros;
}

void CSR::addColumn(int col){
	int currentIndex = -1;
	for(int i=0; i<nonZeros; ++i){
		if(colPos[i]==-1 && currentIndex==-1){
			currentIndex = i;
		}
	}
	colPos[currentIndex] = col;
}

void CSR::addRow(int row){
	if(rowPtr[row] == -1){
		rowPtr[row] = currentValueIndex;
	}


}

void CSR::addValue(int value){
	int currentIndex = -1;
		for(int i=0; i<nonZeros; ++i){
			if(values[i]==-1 && currentIndex==-1){
				currentIndex = i;
			}
		}
		values[currentIndex] = value;
		currentValueIndex = currentIndex;

}

int* CSR::getRowVec(int row) {
	int *vector = new int[n];
	for (int i = 0; i < n; i++)
		vector[i] = 0;
	if (row < n - 1) {
		for (int i = rowPtr[row]; i < rowPtr[row + 1]; i++) {
			for (int j = 0; j < m; j++) {
				if (colPos[i] == j)vector[j] = values[i];
			}
		}
	} else {for (int i = rowPtr[row]; i < nonZeros; i++) {
		for (int j = 0; j < m; j++) {
			if (colPos[i] == j)vector[j] = values[i];
		}
	}
	}
	return vector;
}

void CSR::display(){
	//Displaying the colPos array
	cout << "This is the colPos array" << endl;
	for(int i=0; i<nonZeros; ++i){
		cout << colPos[i] << " ";
	}

	//Displaying the values array
	cout << endl << "This is the values array" << endl;
	for(int i=0; i<nonZeros; ++i){
		cout << values[i] << " ";
	}

	//Displaying the rowPtr array
	cout << endl << "This is the rowPtr array" << endl;
	for(int i=0; i<n; ++i){
		cout << rowPtr[i] << " ";
	}

	//Displaying the full array
	cout << endl << "This is the full array" << endl;
	for(int i=0; i<n; ++i){
		int* rowIndex = this->getRowVec(i);
		for(int j=0; j<m; ++j){
			cout << rowIndex[j] << " ";
		}
		cout << endl;
	}
}

int* CSR::matrixVectorMultiply(int* inputVector){
	int* outputVector = new int[n];

	for(int i=0; i<n; ++i){
		outputVector[i] = 0;
	}

	for(int i=0; i<n; ++i){
		for(int j=rowPtr[i]; j<rowPtr[i+1]; ++j){
			outputVector[i] = outputVector[i] + values[j] * inputVector[colPos[j]];
		}
	}

	return outputVector;
}

CSR* CSR::matrixMultiply(CSR& matrixB){
	return NULL;

}

CSR::~CSR(){
	if(values != NULL) delete [] values;
	if(rowPtr != NULL) delete [] rowPtr;
	if(colPos != NULL) delete [] colPos;

	cout << "CSR Object was Destroyed." << endl;

	n = 0;
	m = 0;
	nonZeros = 0;

}

int main(){

	CSR* A;
	CSR* B;
	//int* aVector;
	int numRows, numColumns, numNonZeros;
	int row, col, value;

	//read in the first matrix
	cin >> numRows >> numColumns;
	cin >> numNonZeros;

	A = new CSR(numRows, numColumns, numNonZeros);

	for(int i=0; i<numNonZeros; ++i){
		cin >> row >> col >> value;
		(*A).addValue(value);
		(*A).addRow(row);
		(*A).addColumn(col);
	}

	(*A).display();

	CSR* C = new CSR(*A); // Calling the copy constructor.
	(*C).display();

	//Read in the second matrix which is similar to the first into the CSR pointer object B and display
	cin >> numRows >> numColumns;
	cin >> numNonZeros;

	B = new CSR(numRows, numColumns, numNonZeros);

	for(int i=0; i<numNonZeros; ++i){
		cin >> row >> col >> value;
		(*B).addValue(value);
		(*B).addRow(row);
		(*B).addColumn(col);
	}
	(*B).display();

	//Read in the vector
	//cin >> numColumns;
	//aVector = new int[numColumns];
	//for(int i=0; i<numColumns; ++i){
	//	cin >> aVector[i];
	//}

	//Matrix-Vector Multiplication
	//int* resultVector = (*A).matrixVectorMultiply(aVector);
	//for(int i=0; i<(*A).getNumRows(); ++i){
	//	cout << resultVector[i] << " ";
	//	cout << endl;
	//}

	//Matrix-Matrix Multiplication
	//CSR* resultMatrix = (*C).matrixMultiply(*B);
	//(*resultMatrix).display();

	//Calling the destructors
	//delete [] aVector;
	//delete [] resultVector;
	delete A;
	delete B;
	//delete C;
	//delete resultMatrix;

	return 0;

}
