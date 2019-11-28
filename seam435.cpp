/*****
 * John Fahringer
 * Project 4 Algorihtms
 * Seam Carving 
 */

#include <iostream>
#include <string>
#include <fstream>


using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::getline;

char** build_Energy_Array(int rows, int columns, char** pgm_arr);
void seamVertical(char** picArray, int seams);
void rotateArray90(char** picArray);
void rotateArray270(char** picArray);
void printArray(int rows, int columns, char** arr);


void printArray(int rows, int columns, char** arr)
{
	cout << endl << "Reading from 2dim_char array: " << endl;
	for (int r(0); r < rows; r++) {
		for (int c(0); c < columns; c++)
			cout << int(arr[r][c]) << " ";
		cout << endl;
	}
	cout << endl;
}


int main(int argc, char *argv[])
{
	if (argc < 4)
		cout << "Error: Running program format must be: \"./seam435 imageFile.pgm #verticalSeams #horizontalSeams\"" << endl;

	else {
		string filename(argv[1]), strLiteral;
		int verticalSeams(int(argv[2])), horizontalSeams(int(argv[3]));
		int columns(0), rows(0), maxGreyVal(0);
		ifstream inputFile;
		ofstream outputFile;

		inputFile.open(filename);
		getline(inputFile, strLiteral);
		if (strLiteral != "P2") {
			cout << "Error: Wrong Format! Non 'P2' literal read" << endl;
			return 0;
		}
		getline(inputFile, strLiteral); /// # Created by IrfanView
		inputFile >> columns;
		inputFile >> rows;
		cout << "Columns: " << columns << " and rows: " << rows << endl;
		inputFile >> maxGreyVal;

		/* Initialize and build pgm_array */
		/* Chars are less expensive than ints for storing numbers 0-255 */
		/* Pay attention to how chars may store some numbers, though. */
		char** pgm_Arr = new char*[rows];
		int numRead;
		for (int i(0); i < rows; i++) 
			pgm_Arr[i] = new char[columns];
		cout << "Reading from input to int var: " << endl;
		for (int r(0); r < rows; r++) {
			for (int c(0); c < columns; c++){
				inputFile >> numRead;
				if (numRead > maxGreyVal) {
					cout << "Error: numRead(" << numRead << ") is greater than maxGreyVal(" << maxGreyVal << "). Found at row(" << r << ") and column(" << c << ")\n";
					return 0;
				}
				cout << numRead << " ";
				pgm_Arr[r][c] = numRead;
			}
			cout << endl;
		}
		
		// We can see some of the int values, that are above 127, get stored as 2's compliments. 
		// Take this into account when we have to use the non 2's compliment forms of these numbers.
		printArray(rows, columns, pgm_Arr);
	}
}