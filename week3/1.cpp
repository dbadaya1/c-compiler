#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include "../common.cpp"

using namespace std;

vector<string> keywords = {"false","true","continue","void","main","while","for","int","char","bool","return","string","vector","using","namespace","if"};
vector<string> specialSymbols = {"!","@","#","$",";","(",")","{","}",","};
vector<string> operators = {"=","+","-","/","*","==",">=","<=","!"};
vector<char> delimiters = {'\t',' ',')','(','{','}',';','\n',','};

vector<string> symbolTable;

bool inArray(vector<string> array,string s) {
	for(int i= 0;i< array.size();i++) {
		if(array[i] == s) {
			return true;
		}
	}
	return false;
}

bool indexOf(vector<string> array,string s) {
	for(int i= 0;i< array.size();i++) {
		if(array[i] == s) {
			return i;
		}
	}
	return -1;
}

bool inArray(vector<char> array,char s) {
	for(int i= 0;i< array.size();i++) {
		if(array[i] == s) {
			return true;
		}
	}
	return false;
}

bool isKeyword(string buffer) {
	return inArray(keywords,buffer);
}
bool isOperator(string buffer) {
	return inArray(operators,buffer);
}

bool isSpecialSymbol(string buffer) {
	return inArray(specialSymbols,buffer);
}

bool isDelimiter(char c) {
	return inArray(delimiters,c);
}

bool isAlphabet(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isDigit(char c) {
	return (c > '0' && c < '9');
}

bool isNumber(string buffer) {
	if(buffer.size() == 0) return false;
	for(int i = 0;i<buffer.size();i++) {
		if(!isDigit(buffer[i]))
			return false;
	}
	return true;
}
bool isStringLiteral(string buffer) {
	if(buffer.front() == '"' && buffer.back() == '"') {
		return true;
	}
	return false;
}

bool isIdentifier(string buffer) {
	if(!isAlphabet(buffer[0]))
		return false;
	for(int i = 1;i < buffer.size();i++) {
		if(!(isAlphabet(buffer[i]) || isDigit(buffer[i]) || buffer[i] == '_'))
			return false;
	}
	return true;
}

void processLexemes(vector<string> lexemes) {
	string buffer;
	for(int i = 0;i<lexemes.size();i++) {
		buffer = lexemes[i];
		if(isKeyword(buffer)) {
			cout<<"<"<<buffer<<">";
		}
		else if(isOperator(buffer)) {
			cout<<"<"<<buffer<<">";
		}
		else if(isSpecialSymbol(buffer)) {
			cout<<"<"<<buffer<<">";
		}
		else if(isIdentifier(buffer)) {
			int id;
			if((id = indexOf(symbolTable,buffer)) == -1) {
				symbolTable.push_back(buffer);
				id = symbolTable.size() - 1;
			}
			cout<<"<id"<<","<<id<<">";
		}
		else if(isStringLiteral(buffer)) {
			cout<<"<STRLITERAL,"<<buffer<<">";
		}
		else if(isNumber(buffer)) {
			cout<<"<num,"<<buffer<<">";
		}
		if(buffer == "\n")
			cout<<"\n";

	}

}

int main() {
	char filename[] = "1.cpp";
	char outputFileName[] = "1_output.txt";
	vector<string> lexemes;
	copyFile(filename,outputFileName);

	removeComments(outputFileName);
	removePreProcessorDirectives(outputFileName);

	FILE * cleanedFile = openFile(outputFileName,"r");
	string buffer;

	char c;
	while((c = fgetc(cleanedFile)) != EOF) {
		if(!isDelimiter(c)) {
			buffer.push_back(c);
			continue;
		}
		lexemes.push_back(buffer);
		buffer.erase();

		buffer.push_back(c);
		lexemes.push_back(buffer);
		buffer.erase();
	}

	processLexemes(lexemes);

	for(int i = 0;i<symbolTable.size();i++)
		cout<<i<<" "<<symbolTable[i]<<"\n";


		return 0;

}

