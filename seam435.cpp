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

void seamVertical(char* picArray, int seams);
void rotateArray90(char* picArray);
void rotateArray270(char* picArray);

int main(int argc, char *argv[])
{
	/*
	{
		for (int i(0); i < 128; i++)
		{
			cout << char(i) << " ";
		}
		cout << endl;
		char** doublearray = new char*[25];
		for (int i(0); i < 25; i++)
		{
			doublearray[i] = new char[15];
			for (int k(0); k < 15; k++)
			{
				doublearray[i][k] = (k + 100 + i);
				cout << doublearray[i][k] << " ";
			}
			cout << endl;
		}
	}
	*/
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
		cout << "Collumns: " << columns << " and rows: " << rows << endl;
		inputFile >> maxGreyVal;

	}
}