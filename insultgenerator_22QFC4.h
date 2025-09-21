#ifndef INSULTGENERATOR_22QFC4_H
#define INSULTGENERATOR_22QFC4_H

#include <string>
#include <vector>
#include <random>
using namespace std;

//Class that generates shakespearean insults
class InsultGenerator{
private:
	//random number generator engine
	mt19937 rng;
	//Stores all 3 columns of insults
    vector<vector<string>> insults;
	//Uniform integer distributions for random index selects of each word of each insult
	uniform_int_distribution<int> dist1, dist2, dist3;

public:
	//Insult Generator Constructor
	InsultGenerator();
	//Loads all phrases from 'InsultsSource.txt', throws exception if file cannot be read
    void initialize();
	//Generates a single random insult
    string talkToMe();
	//Generates 'numInsults' different insults
    vector<string> generate(int numInsults);
	//Genereates 'numInsults' different insults and stores them in 'file', throws an exception if fails to write to file 
    void generateAndSave(const string& file, int numInsults);
};

//Custom Exception class that is used to indicate when file R/W fails
class FileException : public exception{
public:
	//FileException Constructor
	FileException(const string& filename);

	//What() overwrite
	virtual const char* what() const noexcept override;

private:
	//Exception output message
	string message_;
};

//Custom Exception class that is used to indicate when the requested number of insults is invalid
class NumInsultsOutOfBounds : public exception{
public:
	//NumInsultsOutOfBounds Constructor
	NumInsultsOutOfBounds(const int numInsults);

	//What() overwrite
	virtual const char* what() const noexcept override;

private:
	//Exception output message
	string message_;
};
    

#endif // INSULTGENERATOR_22QFC4_H