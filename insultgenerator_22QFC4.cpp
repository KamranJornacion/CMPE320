#include <fstream>
#include <sstream>
#include <random>
#include <set>

#include "insultgenerator_22QFC4.h"
using namespace std;


//InsultGenerator Methods/Constructs----------------------
InsultGenerator::InsultGenerator()
		: rng(random_device{}()) {}

void InsultGenerator::initialize(){
	//Open File
	ifstream InsultsFile("InsultsSource.txt");

	if(!InsultsFile.is_open()){
		throw FileException("InsultsSource.txt");
	}

	//Setup insults attribute
	insults.clear();
	insults.resize(3);

	//Read insults and store in insults attribute
	string currLine;
	while(getline(InsultsFile, currLine)){
		istringstream iss(currLine);
		string word;

		for(int col =0;col<3;col++){
			if(getline(iss,word,'\t')){
				insults[col].push_back(word);
			}
		}
		
	}

	InsultsFile.close();

	//Initialize each random integer distributions
	dist1 = uniform_int_distribution<int> (0, insults[0].size()-1);
	dist2 = uniform_int_distribution<int> (0, insults[1].size()-1);
	dist3 = uniform_int_distribution<int> (0, insults[2].size()-1);
};

string InsultGenerator::talkToMe(){
	//Generate each random word
	string w1 = insults[0][dist1(rng)];
	string w2 = insults[1][dist2(rng)];
	string w3 = insults[2][dist3(rng)];

	//Prepare and return insult
	string insult = "Thou " + w1 + " " + w2 +" "+ w3 + "!";
	return insult;

};

vector<string> InsultGenerator::generate(int numInsults){
	//Verify Input Size
	if(numInsults <1 || numInsults>10000){
		throw NumInsultsOutOfBounds(numInsults);
	}
	//Ensure Alphabetic Order
	set<string> insultSet;
	
	//Generate each insult and return as a vector
	while((int)insultSet.size()<numInsults){
		insultSet.insert(talkToMe());
	}
	vector<string> insultList(insultSet.begin(), insultSet.end());
	return insultList;

};


void InsultGenerator::generateAndSave(const string& file, int numInsults){
	//Generate insults
	vector<string> insultsToSave = generate(numInsults);
	//Prepare storage file
	ofstream outFile(file);
	if(!outFile.is_open()){
		throw FileException(file);
	}
	//Write to File
	for( const auto& insult: insultsToSave){
		outFile << insult<< endl;
	}
	//Close File
	outFile.close();
};

//FileException Methods/Construct-----------------------
FileException::FileException(const string& filename)
	: message_("File not found: " + filename){}

	//What() overwrite
const char* FileException::what() const noexcept {
	return message_.c_str();
}

//NumInsultsOutOfBounds Methods/Construct------------------
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const int numInsults)
	: message_("NumInsults of " + to_string(numInsults) + " is invalid"){}
const char* NumInsultsOutOfBounds::what() const noexcept{
	return message_.c_str();
}
