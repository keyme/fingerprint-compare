/*
 * Provides methods needed to compare fingerprints.
 */

#ifndef COMPARE_H_
#define COMPARE_H_

#include <string>
#include <dpfj.h>
#include <dpfpdd.h>

// Target accuracy of fingerprint comparison
#define TARGET_FALSEMATCH_RATE (DPFJ_PROBABILITY_ONE / 100000)

// Compares the fingerprints in the two provided files
bool    VerifyUser( std::string db_file,
                    std::string print_file);

// Compares the fingerprints in the two provided buffers
bool    VerifyUser( unsigned char* dbPrint,
                    unsigned int dbPrintSize,
                    unsigned char* print,
                    unsigned int printSize);

// Loads a fingerprint from the specified file into the
//   supplied buffer
void    LoadPrint(  std::string file,
                    unsigned char** print,
                    unsigned int* printSize);

#endif /*COMPARE_H_*/
