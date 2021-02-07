//============================================================================
// Name        : project1.cpp
// Author      : Avery Moates
// Version     : 0.0.1
// Description : Data Structures Project One.
//============================================================================

#include <iostream>
using namespace std;

class CSR {
protected:
	int n; //The number of rows of the original matrix.
	int m; // The number of columns of the original matrix.
	int nonZeros; //The number of non-zeros in the original matrix.
	int currentValueIndex; //The current index that the value was placed into.
	int* values; //Value array assuming all are integers.
	int* rowPtr; //Array that contains number of non-zero elements in each row of the original matrix.
	int* colPos; //Array that contains the column number from the original matrix for the non-zero values.

public:
	CSR(); //Default or empty constructor.
	CSR(CSR& matrixB); //Copy constructor.
	CSR(int rows, int cols, int numNonZeros); //Constructs a CSR with the given dimensions and number of non-zeros.
	int getNumRows(); //Function to return the number of rows value.
	int getNumCols(); //Function to return the number of columns value.
	int getNumNonZeros(); //Function to return the number of non-zeros.
	int* getRowPtrArray(); //Function to get a copy of the rowPtr array.
	int* getColPosArray(); //Function to get a copy of the colPos array.
	int* getValuesArray(); //Function to get a copy of the values array.
	int* getRowVec(int row); //Function to return every value in the specified row including zeros.
	int* getColumnVector(int col); //Function to return every value in the specified column including zeros.
	void addValue(int value); //Adds a new value in the values array.
	void addColumn(int col); //Adds a column in the colPos array.
	void addRow(int row); //Adds a row in the rowPtr array.
	void display(); //Prints the contents of the three arrays. Each array must be on a different line and you have exactly a single space between each value printed.
	int* matrixVectorMultiply(int* inputVector); //Matrix-vector multiplication.
	CSR* matrixMultiply(CSR& matrixB); //Matrix-matrix multiplication.
	~CSR(); //Deconstructor functions.

private:
	int* copyArray(int* array, int size); //Helper function to make a copy of an array with a given array and size.
	int rowByColumnMultiply(int* row, int rowSize, int* column, int columnSize); //Helper function to handle the row by column multiplication for a matrix times another matrix. This function returns a int value.
};

//Some of the functions - Sridhar Radhakrishnan

//Default constructor.
CSR::CSR(){
	n = 0;
	m = 0;
	nonZeros = 0;
	currentValueIndex = -1;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}

//Copy constructor.
CSR::CSR(CSR& matrixB){
	n = matrixB.getNumRows();
	m = matrixB.getNumCols();
	nonZeros = matrixB.getNumNonZeros();
	rowPtr = matrixB.getRowPtrArray();
	colPos = matrixB.getColPosArray();
	values = matrixB.getValuesArray();

}

//Constructs a CSR with the given dimensions and number of non-zeros.
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

//Function to return the number of rows value.
int CSR::getNumRows(){
	return n;
}

//Function to return the number of columns value.
int CSR::getNumCols(){
	return m;
}

//Function to return the number of non-zeros.
int CSR::getNumNonZeros(){
	return nonZeros;
}

//Helper function to make a copy of an array with a given array and size.
int* CSR::copyArray(int* array, int size){
	int* copiedArray = new int[size];
	for(int i=0; i<size; ++i){
		copiedArray[i] = array[i];
	}
	return copiedArray;

}

//Function to get a copy of the rowPtr array.
int* CSR::getRowPtrArray(){
	int* copiedArray = this->copyArray(rowPtr, n);
	return copiedArray;
}

//Function to get a copy of the colPos array.
int* CSR::getColPosArray(){
	int* copiedArray = this->copyArray(colPos, nonZeros);
	return copiedArray;
}

//Function to get a copy of the values array.
int* CSR::getValuesArray(){
	int* copiedArray = this->copyArray(values, nonZeros);
	return copiedArray;
}

//Function to add the column that the value is located at with the given column into the colPos array.
void CSR::addColumn(int col){
	int currentIndex = -1;
	for(int i=0; i<nonZeros; ++i){
		if(colPos[i]==-1 && currentIndex==-1){
			currentIndex = i;
		}
	}
	colPos[currentIndex] = col;
}

//Function to add the row that the value is located at with the given row into the rowPtr array.
void CSR::addRow(int row){
	if(rowPtr[row] == -1){
		rowPtr[row] = currentValueIndex;
	}



}

//Function to add the given value into the values array.
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

//Function to return every value in the specified row including zeros.
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

	return vector;
}

//Function to return every value in the specified column including zeros.
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

//Function to display all the arrays and the full 2d array.
void CSR::display(){

	//Displaying the full array
	cout << endl;
	for(int i=0; i<n; ++i){
		int* rowIndex = this->getRowVec(i);
		for(int j=0; j<m; ++j){
			cout << rowIndex[j] << " ";
		}
		cout << endl;
	}
	cout << endl;

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
	cout << endl << endl;

}

//Function to multiply a matrix by a vector and returns an array of the result.
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

//Helper function to handle the row by column multiplication for a matrix times another matrix. This function returns a int value.
int CSR::rowByColumnMultiply(int* row, int rowSize, int* column, int columnSize){
	int sum = 0;
	for(int i=0; i<rowSize; ++i){
		sum += row[i] * column[i];
	}
	return sum;
}

//Function to multiply two matrices together and returns a CSR object..
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

//Deconstructor function.
CSR::~CSR(){
	if(values != NULL) delete [] values;
	if(rowPtr != NULL) delete [] rowPtr;
	if(colPos != NULL) delete [] colPos;

	cout << "CSR Object was Destroyed." << endl;

	n = 0;
	m = 0;
	nonZeros = 0;

}

//Main function.
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

	cout << "Matrix A: " << endl;
	(*A).display();

	// Calling the copy constructor.
	CSR* C = new CSR(*A);
	cout << "Matrix C: " << endl;
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
	cout << "Matrix B: " << endl;
	(*B).display();

	//Read in the vector
	cin >> numColumns;
	//cout << "This is the numColumns value: " << numColumns << endl;
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
	cout << "Matrix C time Matrix B:" << endl;
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
