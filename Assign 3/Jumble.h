


// Since you are using the heap for the puzzle, your JumblePuzzle class must have a destructor, a copy constructor 
// and overload the assignment operator - the so-called "Big Three". You must make sure to prevent aliasing, 
// as tested for in the few supplied unit tests. You will probably find out that improper memory management often 
// causes your program to crash without any useful error messages! Of course you will have to figure out how to 
// delete a 2D array, considering you have "delete[]", but not "delete[][]".

// Examine the supplied code to see what other public member functions you need and how the normal constructor 
// should work. You may write as many private member functions as you wish to make for a well structured class. 
// Use the const modifier wherever possible to help ensure the proper operation of your code.

// Hint: When hiding the word in the array, you might wish to consider the following algorithm:

// Generate a random row and column position between 0 and size-1, where size is the size of the array.
// Choose a random direction from the string "nesw" or something like this.
// Lay down the first letter of the word in the starting position.
// Lay down the remaining letters in the direction obtained.
// If the word will not fit in the given direction, continue the process 
// by going back to the second step and trying again. 
// You have at least a 50% chance of getting a direction in which the word will fit, 
// so you should not need to go back too many times. Just leave the letters from the partial word in the puzzle -
//  just to make it more fun!





// jumble.h
#ifndef JUMBLE_H
#define JUMBLE_H

#include <string>
#include <exception>

using namespace std;

typedef char* charArrayPtr;

//Puzzle class defn
class JumblePuzzle {
private:
    //attributes
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

public:
    JumblePuzzle(const string& toHide, const string& difficulty);

    
    JumblePuzzle(const JumblePuzzle& other);
    JumblePuzzle& operator=(const JumblePuzzle& other);
    ~JumblePuzzle();

    
    int  getSize() const;         
    int  getRowPos() const;       
    int  getColPos() const;       
    char getDirection() const;    

    
    charArrayPtr* getJumble() const;
};

class BadJumbleException: public exception{
public:
    explicit BadJumbleException(const string& message) noexcept;
    const char* what() const noexcept override;
private:
    string msg_;
};

#endif // JUMBLE_H