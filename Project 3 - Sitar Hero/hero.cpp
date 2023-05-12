#include <iostream>
    #include <string>
    #include <cassert>
    using namespace std;

    bool isColor(char a) //function to check whether or not the character passed is a valid char representing a color
    {
        switch(a)
        {
            case 'g':
            case 'r':
            case 'y':
            case 'b':
            case 'o':
            case 'G':
            case 'R':
            case 'Y':
            case 'B':
            case 'O':
                return true;
                break;
            default:
                return false;
                break;
        }
    }
    bool hasProperSyntax(string tune) //checks if string is syntactically correct
    {
        for(int i = 0; i < tune.length(); i++) //iterates through tune
        {
            if(!(isColor(tune.at(i)) || isdigit(tune.at(i)) || tune.at(i) == '/' )) //checks if the character is not a color or is not a digit or is not a slash. If not then return false else continue on
            {
                return false;
            }
            else if (isColor(tune.at(i))) //if the character is a color
            {
                i++; //move onto the next character in the sequence
                if((i) == tune.length()) //if i is equal to the length of tune, it is out of bounds and thus is syntactically incorrect because a color has to be followed by something, so return false.
                {
                    return false;
                }
                else if(isdigit(tune.at(i))) //check if the character past the color is a digit
                {
                    i++; //move onto the next character
                    if(i == tune.length()) //if this character is out of range (indicated by i being equal to the length of the string) return false as the first digit has to be followed by either a slash or a second digit
                    {
                        return false;
                    }
                    else if (isdigit(tune.at(i))) //if there is a second digit past the first digit
                    {
                        if(i+1 == tune.length()) //check if the next character in the string would lead to the index being equal to the string length (this would mean that the index is out of range)
                        {
                            return false;
                        }
                        else if(tune.at(i+1) == '/') //check if the second digit is followed by a slash because digits are required to be followed by slashes to be syntactically correct
                        {
                            //if true then carry on
                        }
                        else //else it means that the second digit is followed by something other than a slash that is not out of range and should not be the case so it should return false
                        {
                            return false;
                        }
                    }
                    else if(tune.at(i) == '/') //catch for if the first digit is simply followed by a slash, if so carry on
                    {
            
                    }
                    else //if anything not covered is true, the string is not syntactically correct
                    {
                        return false;
                    }
                }
                else if (tune.at(i) == '/') //check if the digit is simply an empty beat with just a single slash and no color or digit associated with it
                {
                    
                }
                else //if none of the above cases are true then the program is not syntactically correct
                {
                    return false;
                }
            }
        }
        return true; //return true if all cases pass and are accounted for and the for loop runs through fully
    }

    int convertTune(string tune, string& instructions, int& badBeat) //returns 0 and sets instructions to a converted version of tune else returns a value of badBeat at where the issue occurs
    {
        if(!(hasProperSyntax(tune))) //if the string does not have proper syntax, automatically it does not work and return 1 without changing any variables
        {
            return 1;
        }
        int n; //placeholder used to count number of expected slashes after a color
        string s;
        string placeholder; //value of instructions is not changed until the very end thus placeholder is changed until it can be affirmed that tune is convertible
        string sustained; //sustained checks if the string is sustained
        int currentBeat = 0; //currentBeat increments per beat so that the correct badBeat can be returned
        for(int i = 0; i < tune.length(); i++) //iterate through tune
        {
            if(tune.at(i) == '/') //checks if the character is a standalone slash
            {
                currentBeat++;
                placeholder.append("x"); //adds "x" to placeholder to create new instructions as this empty beat is not attached to a color
            }
            else if(isColor(tune.at(i))) //checks if the current beat is a color
            {
                currentBeat++;
                if((tune.at(i+1) == '1' || tune.at(i+1) == '0') && (!isdigit(tune.at(i+2)))) //checks if the character after the color is 1 or 0, and if so, if there is not another number afterwards as 0 and 1 as standalone digits cannot be convertible
                {
                    badBeat = currentBeat; //the beat we are currently on is the error
                    return 3; //return 3 to represent this error
                }
                else if(tune.at(i+1) == '/') //if the character after the color is a slash, it means the color is only 1 beat long
                {
                    placeholder.append(1, tolower(tune.at(i))); //append a lowercase value of the color to placeholder which currently represents the new instructions
                    i++; //add 1 to i so that the current character will be accounted for in the next iteration of the loop
                }
                else if(isdigit(tune.at(i+1))) //checks if the value after the color is a  digit
                {
                    i++; //increment i to move onto the next value
                    if(isdigit(tune.at(i + 1))) //checks if the value after the first digit is a second digit
                    {
                        s = tune.substr(i, i+1); //if so set s to the substring of the 2 digits
                        n = stoi(s); //convert that string to an integer to utilize the value
                        i++; //increment i by 1 to move on to the next value
                        for(int j = 1; j <= n; j++) //new loop that will run n times to check if there are enough slashes for the correct number of n to ensure the tune is convertible
                        {
                            if(((i+j) == tune.length())) //check if i + j would be out of range and thus the slashes end prematurely
                            {
                                badBeat = currentBeat; //set the badbeat to the currentbeat
                                return 4; //return 4 representing error of strings ending prematurely
                            }
                            else if((!(tune.at(i + j) == '/'))) //check if i +j is a character besides a slash which would mean there are not enough slashes for the indicated value of n
                            {
                                badBeat = currentBeat;
                                return 2; //returns error indicating tune is not convertible logically because incorrect number of slashes while setting badBeat to this current beat
                            }
                            else
                            {
                                currentBeat++; //add to the beat count as there is a slash present
                            }
                        }
                        placeholder.append(n, toupper(tune.at(i-2))); //appends n amount of upper case letters representing the color to placeholder which currently represents the new instructions in order to represent the length of the sustained beat and which colors are used
                        i = i + n; //skip over the next n characters as they are accounted for
                        n = 0; //reset n in case there are other sustained beats needed to be accounted for
                    }
                    else //there is only one digit
                    {
                        s = tune.substr(i, i);
                        n = stoi(s); //n = value of that one digit
                        for(int j = 1; j <= n; j++) //iterate through function n times
                        {
                            if(((i+j) == tune.length())) //check if i + j would be out of range and thus the slashes end prematurely
                            {
                                badBeat = currentBeat;
                                return 4; //returns respective error with badBeat set to currentBeat
                            }
                            else if((!(tune.at(i + j) == '/')))
                            {
                                badBeat = currentBeat;
                                return 2; //returns error indicating tune is not convertible logically because incorrect number of slashes while setting badBeat to this current beat
                            }
                            else
                            {
                                currentBeat++;
                            }
                        }
                        placeholder.append(n, toupper(tune.at(i-1))); //appends n amount of upper case letters representing the color to placeholder which currently represents the new instructions in order to represent the length of the sustained beat and which colors are used
                        i = i + n; //skip over the next n characters as they are accounted for
                        n = 0; //reset n in case there are other sustained beats needed to be accounted for
                    }
                }
            }
        }
        instructions = placeholder;
        return 0; //if all tests pass then the string is convertible so instructions can be changed and set to the value of placeholder and return 0
    }
    int main()
    {
        assert(hasProperSyntax(""));
        assert(hasProperSyntax("G/"));
        assert(hasProperSyntax("r//Y/g3///o/"));
        assert(hasProperSyntax("y03///r10//////////"));
        assert(hasProperSyntax("///"));
        assert(hasProperSyntax("g/b//"));
        assert( ! hasProperSyntax("g/z//"));
        assert(hasProperSyntax("r/"));
        assert(!hasProperSyntax("r3"));
        assert( ! hasProperSyntax("r"));
        string instrs;
        int badb;
        badb = -999;  // so we can detect whether this gets changed
        assert(convertTune("r//g/", instrs, badb) == 0  &&  instrs == "rxg"  &&  badb == -999);
        instrs = "WOW";  // so we can detect whether this gets changed
        badb = -999;  // so we can detect whether this gets changed
        assert(convertTune("r", instrs, badb) == 1  &&  instrs == "WOW"  &&  badb == -999);
        assert(convertTune("r/y3//g/r/", instrs, badb) == 2  &&  instrs == "WOW"  &&  badb == 4);
        assert(convertTune("r/g03///R//B11///////////", instrs, badb) == 0 && instrs == "rGGGrxBBBBBBBBBBB");
        assert(convertTune("r/b/r13/", instrs, badb) == 4 && badb == 4);
        assert(convertTune("r/b/r3//", instrs, badb) == 4 && badb == 5);
        assert(convertTune("r1/", instrs, badb) == 3);
        cerr << "All tests succeeded" << endl;
    }
