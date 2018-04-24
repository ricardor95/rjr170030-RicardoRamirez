/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Ricardo Ramirez
 * Email:  rjr170030@utdallas.edu
 * Course: CS3377
 */

#include <iostream>
#include "cdk.h"

#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <sstream>      // std::stringstream

 
#define maxRecordStringLength 25
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 17
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

class BinaryFileHeader
{
public:
  unsigned int magicNumber;
  unsigned int versionNumber;
  unsigned long long numRecord;
};

class BinaryFileRecord
{
public:
  unsigned char strLength;
  char stringBuffer[maxRecordStringLength];
};


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /* Read from file */
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecords = new BinaryFileRecord();

  stringstream value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11;

  ifstream binInfile;
  binInfile.open("cs3377.bin", ios::in | ios::binary);  

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  /*
   * Dipslay a message 
   */

  value1 << "Magic: 0x" << hex << uppercase << myHeader->magicNumber;
  value2 << "Version: " << dec << myHeader->versionNumber; 
  value3 << "NumRecords: " << myHeader->numRecord;

  binInfile.read((char *) myRecords, sizeof(BinaryFileRecord));
  value4 << "strlen: " << (int) myRecords->strLength;
  for( unsigned int i = 0 ; i < strlen(myRecords->stringBuffer) ; i ++ )
  {
  	value5 <<  myRecords->stringBuffer[i]; 
  }

  binInfile.read((char *) myRecords, sizeof(BinaryFileRecord));
  value6 << "strlen: " << (int) myRecords->strLength;
  for( unsigned int i = 0 ; i < strlen(myRecords->stringBuffer) ; i ++ )
  {
  	value7 <<  myRecords->stringBuffer[i]; 
  }
  binInfile.read((char *) myRecords, sizeof(BinaryFileRecord));
  value8 << "strlen: " << (int) myRecords->strLength;
  for( unsigned int i = 0 ; i < strlen(myRecords->stringBuffer) ; i ++ )
  {
  	value9 <<  myRecords->stringBuffer[i]; 
  }
  binInfile.read((char *) myRecords, sizeof(BinaryFileRecord));
  value10 << "strlen: " << (int) myRecords->strLength;
  for( unsigned int i = 0 ; i < strlen(myRecords->stringBuffer) ; i ++ )
  {
  	value11 <<  myRecords->stringBuffer[i]; 
  }
 
  setCDKMatrixCell(myMatrix, 1, 1, value1.str().c_str());
  setCDKMatrixCell(myMatrix, 1, 2, value2.str().c_str());
  setCDKMatrixCell(myMatrix, 1, 3, value3.str().c_str());
  setCDKMatrixCell(myMatrix, 2, 1, value4.str().c_str());
  setCDKMatrixCell(myMatrix, 2, 2, value5.str().c_str());
  setCDKMatrixCell(myMatrix, 3, 1, value6.str().c_str());
  setCDKMatrixCell(myMatrix, 3, 2, value7.str().c_str());
  setCDKMatrixCell(myMatrix, 4, 1, value8.str().c_str());
  setCDKMatrixCell(myMatrix, 4, 2, value9.str().c_str());
  setCDKMatrixCell(myMatrix, 5, 1, value10.str().c_str());
  setCDKMatrixCell(myMatrix, 5, 2, value11.str().c_str());

  drawCDKMatrix(myMatrix, true);    /* required  */

  binInfile.close();

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
