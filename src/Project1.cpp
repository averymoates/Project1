//============================================================================
// Name        : Project1.cpp
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
	int* copyArray(int* array, int size);
	int* getRowPtrArray();
	int* getColPosArray();
	int* getValuesArray();
	int* getRowVec(int row);
	int* getColumnVector(int col);
	void addValue(int value); //Adds a new value in the values array
	void addColumn(int col); //Adds a column in the colPos array
	void addRow(int row); //Adds a row in the rowPtr array
	void display(); //Prints the contents of the three arrays. Each array must be on a different line and you have exactly a single space between each value printed.
	int* matrixVectorMultiply(int* inputVector); //Matrix-vector multiplication
	int rowByColumnMultiply(int* row, int rowSize, int* column, int columnSize);
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
	nonZeros = matrixB.getNumNonZeros();
	rowPtr = matrixB.getRowPtrArray();
	colPos = matrixB.getColPosArray();
	values = matrixB.getValuesArray();

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

int* CSR::copyArray(int* array, int size){
	int* copiedArray = new int[size];
	for(int i=0; i<size; ++i){
		copiedArray[i] = array[i];
	}
	return copiedArray;

}

int* CSR::getRowPtrArray(){
	int* copiedArray = this->copyArray(rowPtr, n);
	return copiedArray;
}

int* CSR::getColPosArray(){
	int* copiedArray = this->copyArray(colPos, nonZeros);
	return copiedArray;
}

int* CSR::getValuesArray(){
	int* copiedArray = this->copyArray(values, nonZeros);
	return copiedArray;
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
	for (int i = 0; i < n; i++){
		vector[i] = 0;
	}

	int start = 0;
	int end = -1;

	if((row-1)==-1){
		start = 0;
		end = rowPtr[row+1];
	}
	else if((row+1)>=n){
		start = rowPtr[row];
		end = nonZeros;
	}
	else{
		start = rowPtr[row];
		end = rowPtr[row+1];
	}

	if(end!=-1){
		for(int i=start; i<end; ++i){
			vector[colPos[i]]=values[i];
		}
	}

//	if (row < n - 1) {
//		for (int i = rowPtr[row]; i < rowPtr[row + 1]; i++) {
//			for (int j = 0; j < m; j++) {
//				if (colPos[i] == j)vector[j] = values[i];
//			}
//		}
//	} else {
//		for (int i = rowPtr[row]; i < nonZeros; i++) {
//			for (int j = 0; j < m; j++) {
//				if (colPos[i] == j)vector[j] = values[i];
//			}
//		}
//	}
	return vector;
}

int* CSR::getColumnVector(int col){
	int* colVector = new int[n];
	int r;
	for(int i=0; i<n; ++i){
		colVector[i] = 0;
	}

	bool found;
	int k,j;

	k=0;
	for(int i=0; i<n-1; ++i){
		r = rowPtr[i+1] - rowPtr[i];
		k = rowPtr[i];
		found = false;
		j = 0;
		while((j<r) && !found){
			if(colPos[k] == col){
				found = true;
				colVector[i] = values[k];
			}
			++k;
			++j;
		}
	}
	int p = rowPtr[n-1];
	found = false;
	while((p < (nonZeros))&&(!found)){
		if(colPos[p] ==col){
			colVector[n-1] = values[p];
			found = true;
		}
		else{
			++p;
		}
	}
	return colVector;
}

void CSR::display(){
	//Displaying the colPos array
	cout << "This is the colPos array :";
	for(int i=0; i<nonZeros; ++i){
		cout << colPos[i] << " ";
	}

	//Displaying the values array
	cout << endl << "This is the values array :";
	for(int i=0; i<nonZeros; ++i){
		cout << values[i] << " ";
	}

	//Displaying the rowPtr array
	cout << endl << "This is the rowPtr array :";
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

	int sum = 0;
	int start, end;
	for(int i=0; i<n; ++i){
		sum = 0;
		start = rowPtr[i];
		if((i+1) ==n){
			end = nonZeros;
		}
		else{
			end = rowPtr[i + 1];
		}

		for(int j=start; j<end; ++j){
			sum = sum + (values[j] * inputVector[colPos[j]]);
		}
		outputVector[i] = sum;
	}

	return outputVector;
}

int CSR::rowByColumnMultiply(int* row, int rowSize, int* column, int columnSize){
	int sum = 0;
	for(int i=0; i<rowSize; ++i){
		sum += row[i] * column[i];
	}
	return sum;
}

CSR* CSR::matrixMultiply(CSR& matrixB){
	int* row;
	int* column;
	int size = this->getNumRows();
	int nonZeroCount = 0;
	int sum = 0;

	for(int i=0; i<size; ++i){
		row = this->getRowVec(i);
		for(int j=0; j<size; ++j){
			column = matrixB.getColumnVector(j);
			sum = rowByColumnMultiply(row, size, column, size);
			if(sum > 0){
				++nonZeroCount;
			}
		}

	}

	CSR* fin = new CSR(this->getNumRows(), matrixB.getNumCols(), nonZeroCount);

	for(int i=0; i<size; ++i){
		row = this->getRowVec(i);
		for(int j=0; j<size; ++j){
			column = matrixB.getColumnVector(j);
			sum = rowByColumnMultiply(row, size, column, size);
			if(sum > 0){
				(*fin).addValue(sum);
				(*fin).addRow(i);
				(*fin).addColumn(j);
			}
		}

	}

	return fin;

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
	int* aVector;
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
	cin >> numColumns;
	cout << "This is the numColumns value: " << numColumns << endl;
	aVector = new int[numColumns];
	cout << "This is the aVector array: ";
	for(int i=0; i<numColumns; ++i){
		cin >> aVector[i];
		cout << aVector[i] << " ";
	}
	cout << endl;

	//Matrix-Vector Multiplication
	int* resultVector = (*A).matrixVectorMultiply(aVector);
	for(int i=0; i<(*A).getNumRows(); ++i){
		cout << resultVector[i] << " ";
		cout << endl;
	}

	//Matrix-Matrix Multiplication
	CSR* resultMatrix = (*C).matrixMultiply(*B);
	(*resultMatrix).display();

	//Calling the destructors
	delete [] aVector;
	delete [] resultVector;
	delete A;
	delete B;
	delete C;
	delete resultMatrix;

	return 0;

}
