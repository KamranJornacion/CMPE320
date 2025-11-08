#ifndef JUMBLE_H
#define JUMBLE_H

using namespace std;

//class of puzzle
class JumblePuzzle{
private:


public:

    //Constructors

    JumblePuzzle(void arg1, void arg2);

    getJumble();

    getSize();

    getRowPos()

    getColPos()

    getDirection();
};

//Custom Exception class that
class BadJumbleException: public runtime_error{
public:
    //use runtime_error constructors
    using runtime_error::runtime_error;
};

#endif // JUMBLE_H