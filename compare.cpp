#include <iostream>
#include <fstream>
#include <unistd.h>
#include "compare.h"

using namespace std;

bool    VerifyUser( std::string db_file,
										std::string print_file) {
	unsigned char *dbFmd = NULL, *printFmd = NULL;
	unsigned int dbFmdSize = 0, printFmdSize = 0;

	LoadPrint(db_file, &dbFmd, &dbFmdSize);
	LoadPrint(print_file, &printFmd, &printFmdSize);

	return VerifyUser(dbFmd, dbFmdSize, printFmd, printFmdSize);
}

bool    VerifyUser( unsigned char* dbPrint,
										unsigned int dbPrintSize,
										unsigned char* print,
										unsigned int printSize) {

	// Only compare if both fingerprints have data
	if(dbPrintSize > 0 && printSize > 0) {
		unsigned int falsematch_rate;
		int result = dpfj_compare(DPFJ_FMD_ANSI_378_2004, dbPrint, dbPrintSize, 0,
				DPFJ_FMD_ANSI_378_2004, print, printSize, 0, &falsematch_rate);

		cout << "FINGERPRINT: result=" << result << ", falsematch_rate=" << falsematch_rate
				 << ", target=" << TARGET_FALSEMATCH_RATE << endl;

		// If the comparison was successful and the prints matched
		if(result == DPFJ_SUCCESS && falsematch_rate < TARGET_FALSEMATCH_RATE) {
			return true;
		}
	}

	return false;
}

void    LoadPrint(  std::string file,
										unsigned char** print,
										unsigned int* printSize) {

	// Open the file in binary mode
	ifstream input(file.c_str(), ios::in | ios::binary | ios::ate);

	// Only try if the file exists
	if(input.is_open()) {
		// Figure out the file size and allocate memory
		//   for the data
		*printSize = (unsigned int) input.tellg();
		*print = new unsigned char[*printSize];

		// Read the file data from the beginning
		input.seekg(0, ios::beg);
		input.read((char*) (*print), *printSize);
		input.close();
	}
}
