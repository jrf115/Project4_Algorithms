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

char* build_Energy_Array(int columns, int rows, char pgm_arr[]);
void carve_VerSeam(char* pgm_arr, int seams);
void carve_HorSeam(char* pgm_arr, int seams);
void rotateArray90(int& columns, int& rows, char* pgm_arr);
void rotateArray270(int& columns, int& rows, char* & pgm_arr);
void printArray(int columns, int rows, char arr[]);

void rotateArray90(int& columns, int& rows, char* pgm_arr)
{
	int rotated_c(0), rotated_r(0);
	char* copy = new char[columns * rows];
	for (int i(0); i < columns * rows; i++)
		copy[i] = pgm_arr[i];

	for (int c(0); c < columns; c++) {
		for (int r(rows - 1); r >= 0; r--) {	
			pgm_arr[rotated_c + rotated_r * rows] = copy[c + r * columns];
			//cout << "copied " << c << " + " << r << " * " << columns << " == " << c + r * columns << " _____TO_____ " << rotated_c << " + " << rotated_r << " * " << rows << " == " << rotated_c + rotated_r * rows << endl;
			rotated_c++;
		}
		rotated_r++;
		rotated_c = 0;
	}
	
	// Delete old array and switch columns/rows
	delete copy;
	int temp(columns);
	columns = rows;
	rows = temp;
	cout << "pgm_arr 90_rotated to: " << endl;
	printArray(columns, rows, pgm_arr);
}

void rotateArray270(int& columns, int& rows, char* pgm_arr) {
	for (int i(0); i < 3; i++)
		rotateArray90(columns, rows, pgm_arr);
	cout << "pgm_arr 270_rotated to: " << endl;
	printArray(columns, rows, pgm_arr);
	cout << endl;
}

/* Debugging Function */
void printArray(int columns, int rows, char arr[])
{
	cout << endl << "Reading from 2dim_char array: " << endl;
	cout << "Columns: " << columns << " and rows: " << rows << endl;
	for (int r(0); r < rows; r++) {
		for (int c(0); c < columns; c++)
			cout << int(arr[c + r * columns]) << " ";
		cout << endl;
	}
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
		char pgm_Arr[columns * rows];
		int numRead;
		cout << "Reading from input to int var: " << endl;
		for (int r(0); r < rows; r++) {
			for (int c(0); c < columns; c++) {
				inputFile >> numRead;
				if (numRead > maxGreyVal) {
					cout << "Error: numRead(" << numRead << ") is greater than maxGreyVal(" << maxGreyVal << "). Found at row(" << r << ") and column(" << c << ")\n";
					return 0;
				}
				cout << numRead << " ";
				pgm_Arr[columns * r + c] = numRead;
			}
			cout << endl;
		}
		
		// We can see some of the int values, that are above 127, get stored as 2's compliments. 
		// Take this into account when we have to use the non 2's compliment forms of these numbers.
		printArray(columns, rows, pgm_Arr);
		rotateArray90(columns, rows, pgm_Arr);
		cout << "RotatedArray" << endl;
		printArray(columns, rows, pgm_Arr);
		rotateArray270(columns, rows, pgm_Arr);
		cout << "RotatedArray again" << endl;
		printArray(columns, rows, pgm_Arr);

		// Testing outputfile...
		outputFile.open("testingoutput.pgm");
		outputFile << "P2\n# Created by IrfanView\n" << columns << " " << rows << "\n" << maxGreyVal << "\n";
		for (int r(0); r < rows; r++) {
			for (int c(0); c < columns; c++) {
				if (int(pgm_Arr[columns * r + c]) <= 0)
					outputFile << 256 + int(pgm_Arr[columns * r + c]);
				else
					outputFile << int(pgm_Arr[columns * r + c]);
				if (c != columns - 1)
					outputFile << " ";
			}
			if (r != rows - 1)
				outputFile << "\n";
		}
	}
}