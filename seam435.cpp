/*****
 * John Fahringer
 * Project 4 Algorihtms
 * Seam Carving
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> /* abs */


using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::getline;

int* build_Energy_Array(int columns, int rows, char pgm_arr[]);
void carve_VerSeam(char* pgm_arr, int seams);
void carve_HorSeam(char* pgm_arr, int seams);
void rotateArray90(int& columns, int& rows, char* pgm_arr);
void rotateArray270(int& columns, int& rows, char* & pgm_arr);
void printRawArray(int columns, int rows, char arr[]);
void printArray(int columns, int rows, char arr[]);
void print_Energy_Array(int columns, int rows, int energy[]);
int char2PosInt(char c);

/***
Energy for a specifc pixel can be found using:
	e(i, j) = | v(i, j) - v(i - 1, j) | + | v(i, j) - v(i + 1, j) | + | v(i, j) - v(i, j - 1) | + | v(i, j) - v(i, j + 1) | ,
Where:
	v(i, j) = pixel value at(i, j)
*/
int* build_Energy_Array(int columns, int rows, char pgm_arr[])
{
	int* energy = new int[columns * rows];
	int energy_value(0);
	for (int p_row(0); p_row < rows; p_row++) {
		for (int p_column(0); p_column < columns; p_column++) {
			// Checking if v(i - 1, j) lies outside of the visual matrix space or not
			cout << p_column - 1 << endl;
			if (p_column - 1 >= 0)
				energy_value += abs(char2PosInt(pgm_arr[p_column + p_row * columns]) - char2PosInt(pgm_arr[p_column - 1 + p_row * columns]));
			// Check if v(i + 1, j) is outside of the visual matrix space or not
			cout << p_column + 1 << endl;
			if (p_column + 1 < columns)
				energy_value += abs(char2PosInt(pgm_arr[p_column + p_row * columns]) - char2PosInt(pgm_arr[p_column + 1 + p_row * columns]));
			// Check if v(i, j - 1) is outside of the visual matrix space or not
			cout << p_row - 1 << endl;
			if (p_row - 1 >= 0)
				energy_value += abs(char2PosInt(pgm_arr[p_column + p_row * columns]) - char2PosInt(pgm_arr[p_column + (p_row - 1) * columns]));
			// Check if v(i, j + 1) is outside of the visual matrix space or not
			cout << p_row + 1 << endl;
			if (p_row + 1 < rows)
				energy_value += abs(char2PosInt(pgm_arr[p_column + p_row * columns]) - char2PosInt(pgm_arr[p_column + (p_row + 1) * columns]));
			cout << "energy_value: " << (energy_value) << endl;
			cout << endl;

			energy[p_column + p_row * columns] = energy_value;
			energy_value = 0;
		}
	}
	cout << "Energy Array Produced: \n";
	print_Energy_Array(columns, rows, energy);
	return energy;
}

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
	/*
	cout << "pgm_arr 90_rotated to: " << endl;
	printRawArray(columns, rows, pgm_arr);
	*/
}

void rotateArray270(int& columns, int& rows, char* pgm_arr) {
	for (int i(0); i < 3; i++)
		rotateArray90(columns, rows, pgm_arr);
	/*
	cout << "pgm_arr 270_rotated to: " << endl;
	printRawArray(columns, rows, pgm_arr);
	cout << endl;
	*/
}

/* Debugging Function */
/* Prints the stored char value as an int. May print out 2's compliments of numbers */
void printRawArray(int columns, int rows, char arr[])
{
	cout << endl << "Reading from raw 2dim_char array: " << endl;
	cout << "Columns: " << columns << " and rows: " << rows << endl;
	for (int r(0); r < rows; r++) {
		for (int c(0); c < columns; c++)
			cout << int(arr[c + r * columns]) << " ";
		cout << endl;
	}
}

void printArray(int columns, int rows, char arr[])
{
	cout << "Columns: " << columns << " and rows: " << rows << endl;
	for (int r(0); r < rows; r++) {
		for (int c(0); c < columns; c++) {
			cout << char2PosInt(arr[columns * r + c]) << " "; // The current value is a 2's compliment.
		}
		cout << endl;
	}
}

/* Debug Function */
void print_Energy_Array(int columns, int rows, int energy[])
{
	cout << "Columns: " << columns << " and rows: " << rows << endl;
	for (int r(0); r < rows; r++) {
		for (int c(0); c < columns; c++) {
			cout << (energy[columns * r + c]) << " "; // The current value is a 2's compliment.
		}
		cout << endl;
	}
}

int char2PosInt(char c)
{
	if (int(c) < 0)
		return 256 + int(c); // The current value is a 2's compliment.
	else
		return int(c);
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
		/*////////////////////////////////////////////////////////////////////////////////////////////
		// We can see some of the int values, that are above 127, get stored into the char array as 2's compliments.
		// Take this into account when we have to use the non 2's compliment forms of these numbers.

		printRawArray(columns, rows, pgm_Arr);
		rotateArray90(columns, rows, pgm_Arr);
		cout << "RotatedArray" << endl;
		printRawArray(columns, rows, pgm_Arr);
		/////////////////////////////////////////////////////////////////////////////////////////////*/
		char testArray[24]; testArray[0] = (30);	testArray[1] = (120);	testArray[2] = (196); testArray[3] = (215);	testArray[4] = (198); testArray[5] = (180); testArray[6] = (45);	testArray[7] = (4);	testArray[8] = (172); testArray[9] = (5); testArray[10] = (250);	testArray[11] = (252); testArray[12] = (190); testArray[13] = (192);	testArray[14] = (53); testArray[15] = (35); testArray[16] = (123); testArray[17] = (124); testArray[18] = (5); testArray[19] = (100); testArray[20] = (132); testArray[21] = (110);	testArray[22] = (114); testArray[23] = (203);
		int roww = 8;
		int coll = 3;
		printArray(coll, roww, testArray);
		printRawArray(coll, roww, testArray);
		int* nrg_Arr = build_Energy_Array(coll, roww, testArray);
		// char* nrg_Arr = build_Energy_Array(columns, rows, pgm_Arr);

		// Testing outputfile...
		outputFile.open("testingoutput.pgm");
		outputFile << "P2\n# Created by IrfanView\n" << columns << " " << rows << "\n" << maxGreyVal << "\n";
		for (int r(0); r < rows; r++) {
			for (int c(0); c < columns; c++) {
				if (int(pgm_Arr[columns * r + c]) <= 0)
					outputFile << 256 + int(pgm_Arr[columns * r + c]); // The current value is a 2's compliment.
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
