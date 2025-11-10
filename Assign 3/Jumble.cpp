#include "Jumble.h"
#include <cstdlib>
#include <string>
using namespace std;


//Puzzle class defn

charArrayPtr* board_; 
int size_;            
int rowPos_;          
int colPos_;          
char dir_;            
string word_;    


static int  factorFromDifficulty(const string& difficulty);
static bool isAllAlpha(const string& str);
static char toLowerChar(char c);
static char randLower(); 

void allocateBoard(int n);
void freeBoard();

void fillRandomLetters();
void placeWordRandomly();

bool fits(int r, int c, char dir) const;
void placeAt(int r, int c, char dir);


void copyFrom(const JumblePuzzle& other);
static void deepCopy(charArrayPtr* destn, charArrayPtr* source, int n);


JumblePuzzle::JumblePuzzle(const string& toHide, const string& difficulty);


JumblePuzzle::JumblePuzzle(const JumblePuzzle& other);
JumblePuzzle::JumblePuzzle& operator=(const JumblePuzzle& other);
JumblePuzzle::~JumblePuzzle();


int  getSize() const;         
int  getRowPos() const;       
int  getColPos() const;       
char getDirection() const;    


charArrayPtr* getJumble() const;

//exception

explicit BadJumbleException(const string& message) noexcept;
const char* what() const noexcept override;
