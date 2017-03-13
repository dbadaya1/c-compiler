#include "include/compiler.h"
#include "include/preprocessor.h"
#include "include/lex.h"
#include <iostream>

using namespace std;


void compiler_initialize(char *inputFileName) {
    //string tempFile = tmpnam(nullptr);
  //  removeComments(inputFileName, tempFile.c_str());

    processIncludes(inputFileName,TEMPFILE);

    lex_initialize(TEMPFILE);
}

void compiler_finalize() {
    lex_finalize();
}

