#include <iostream>
#include <cassert>
#include <cctype>
#include <cstring>

using namespace std;

const int MAX_WORD_LENGTH = 20;

int editStandards(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nStandards)
{
    if(nStandards <= 0)
    {
        return 0;
    }
    int notWorking = 0; //declare notWorking to count which values don't fall under the roof of match standard
    for (int i = 0; i < nStandards; i++) //iterate through the arrays by the amount of the max # of standards to count the number of incorrect standards
    {
        if (distance[i] <= 0) //check if the distance is zero or negative and thus does not match
        {
            notWorking++; // increment the amount of incorrect match standards
        }
        else if(distance[i] > 0) //if distance is positive
        {
            bool word1Wrong = false;
            if(word1[i][0] == '\0' || word2[i][0] == '\0') //if the first char in either word is null increment notWorking and don't continue
            {
                notWorking++;
            }
            else
            {
                for (int z = 0; z < strlen(word1[i]); z++) //iterate through word1
                {
                      if((!isalpha(word1[i][z]) && i != nStandards)) //if there is a char in word1 that is not a letter
                      {
                          notWorking++;
                          word1Wrong = true; //increment notWorking, indicate that word1 is not functioning and break out of the loop
                          break;
                      }
                }
                if(!word1Wrong) //if word1 is working then check if word2 is
                {
                    for (int z = 0; z < strlen(word2[i]); z++) //iterate through word2
                    {
                       if ((!isalpha(word2[i][z]) && i != nStandards)) //if there is a char in word2 that is not a letter
                        {
                            notWorking++; //increment notworking and break out of the loop
                            break;
                        }
                    }
                }
            }
        }
    }
    
        
        int n = 0;
        bool needToSwitch = true;
        while (needToSwitch) // itereate through the arrays while you still need to switch values to make sure the array is sorted
        {
            needToSwitch = false; //initialize needing to switch as false
            n++;
            
            for (int i = 0; i < nStandards - n; i++) //iterate through array
            {
                if (distance[i] < distance[i+1]) //switch values if current distance is less than the next distance
                {
                    int intTemp = distance[i];
                    char word1Temp[21];
                    char word2Temp[21];
                    strcpy(word1Temp, word1[i]);
                    strcpy(word2Temp, word2[i]);
                    strcpy(word1[i], word1[i+1]);
                    strcpy(word1[i+1], word1Temp);
                    strcpy(word2[i], word2[i+1]);
                    strcpy(word2[i+1], word2Temp);
                    distance[i] = distance[i+1];
                    distance[i+1] = intTemp;
                    needToSwitch = true;
                }
                if(word1[i][0] == '\0') //switch values if first character in word1 is null
                {
                    int intTemp = distance[i];
                    char word1Temp[21];
                    char word2Temp[21];
                    strcpy(word1Temp, word1[i]);
                    strcpy(word2Temp, word2[i]);
                    strcpy(word1[i], word1[i+1]);
                    strcpy(word1[i+1], word1Temp);
                    strcpy(word2[i], word2[i+1]);
                    strcpy(word2[i+1], word2Temp);
                    distance[i] = distance[i+1];
                    distance[i+1] = intTemp;
                    needToSwitch = true;
                }
                else if(word2[i][0] == '\0') //switch values if first character in word2 is null
                {
                    int intTemp = distance[i];
                    char word1Temp[21];
                    char word2Temp[21];
                    strcpy(word1Temp, word1[i]);
                    strcpy(word2Temp, word2[i]);
                    strcpy(word1[i], word1[i+1]);
                    strcpy(word1[i+1], word1Temp);
                    strcpy(word2[i], word2[i+1]);
                    strcpy(word2[i+1], word2Temp);
                    distance[i] = distance[i+1];
                    distance[i+1] = intTemp;
                    needToSwitch = true;
                }
                else {
                    for (int z = 0; z < strlen(word1[i]); z++) //iterate through the first c string in word1 array
                    {
                          if (!isalpha(word1[i][z])) //if there is a nonalpha character in the c string, switch that to the next position
                          {
                              int intTemp = distance[i];
                              char word1Temp[21];
                              char word2Temp[21];
                              strcpy(word1Temp, word1[i]);
                              strcpy(word2Temp, word2[i]);
                              strcpy(word1[i], word1[i+1]);
                              strcpy(word1[i+1], word1Temp);
                              strcpy(word2[i], word2[i+1]);
                              strcpy(word2[i+1], word2Temp);
                              distance[i] = distance[i+1];
                              distance[i+1] = intTemp;
                              needToSwitch = true;
                          }
                        
                          if(isupper(word1[i][z])) //if the alpha character is uppercase, make it lowercase
                          {
                              word1[i][z] = tolower(word1[i][z]);
                          }
                    }
                        
                    for (int z = 0; z < strlen(word2[i]); z++) //iterate through the first c string in word2
                    {
                        if (!isalpha(word2[i][z])) //if there is a nonalpha character in the c string, switch that to the next position
                        {
                            int intTemp = distance[i];
                            char word1Temp[21];
                            char word2Temp[21];
                            strcpy(word1Temp, word1[i]);
                            strcpy(word2Temp, word2[i]);
                            strcpy(word1[i], word1[i+1]);
                            strcpy(word1[i+1], word1Temp);
                            strcpy(word2[i], word2[i+1]);
                            strcpy(word2[i+1], word2Temp);
                            distance[i] = distance[i+1];
                            distance[i+1] = intTemp;
                            needToSwitch = true;
                        }
                        
                        if(isupper(word2[i][z])) //if the alpha character is uppercase, make it lowercase
                        {
                            word2[i][z] = tolower(word2[i][z]);
                        }
                    }
                }
            }
        }
    for(int i = 0; i < nStandards - notWorking; i++) //iterate through the number of currently working match standards
    {
       int biggestPosition = i; //initialize the biggest position to the first to compare with the other positions
        for(int z = i+1; z < nStandards - notWorking; z++) //iterate through every position past it looking for words that are the same
        {
            if (strcmp(word1[i], word1[z]) == 0 && strcmp(word2[i], word2[z]) == 0 && i != z ) //check if the values of the words are the same at current position and biggestPosition for both word1 and word2 and that the current position is not being compared to itself (to avoid linux errors)
            {
                if(distance[biggestPosition] >= distance[z]) //if the distance of biggestPosition is larger than that of the current position, increment notWorking so that the total match standards iterated through is lowered by 1 and send the values of distance word1 and word2 at current position to the end so they are counted as invalid standards
                {
                    notWorking++;
                    if((nStandards - notWorking) != z )
                    {
                        int intTemp = distance[z];
                        char word1Temp[21];
                        char word2Temp[21];
                        strcpy(word1Temp, word1[z]);
                        strcpy(word2Temp, word2[z]);
                        strcpy(word1[z], word1[nStandards - notWorking]);
                        strcpy(word1[nStandards - notWorking], word1Temp);
                        strcpy(word2[z], word2[nStandards - notWorking]);
                        strcpy(word2[nStandards - notWorking], word2Temp);
                        distance[z] = distance[nStandards - notWorking];
                        distance[nStandards - notWorking] = intTemp;
                        z--;
                    }
                }
                else //if the distance of biggestPosition is smaller than that of the current position, increment notWorking so that the total match standards iterated through is lowered by 1 and switch the values of distance word1 and word2 at currentPosition with that at biggestPosition
                {
                    notWorking++;
                    int intTemp = distance[biggestPosition];
                    char word1Temp[21];
                    char word2Temp[21];
                    strcpy(word1Temp, word1[biggestPosition]);
                    strcpy(word2Temp, word2[biggestPosition]);
                    strcpy(word1[biggestPosition], word1[z]);
                    strcpy(word1[z], word1Temp);
                    strcpy(word2[biggestPosition], word2[z]);
                    strcpy(word2[z], word2Temp);
                    if((nStandards - notWorking) != z ) //if the current position is not the end then send the values at the current position to the end so they are counted as invalid standards
                    {
                        intTemp = distance[z];
                        strcpy(word1Temp, word1[z]);
                        strcpy(word2Temp, word2[z]);
                        strcpy(word1[z], word1[nStandards - notWorking]);
                        strcpy(word1[nStandards - notWorking], word1Temp);
                        strcpy(word2[z], word2[nStandards - notWorking]);
                        strcpy(word2[nStandards - notWorking], word2Temp);
                        distance[z] = distance[nStandards - notWorking];
                        distance[nStandards - notWorking] = intTemp;
                        z--;
                    }
                    
                }
            }
        }
    }
    int difference = nStandards - notWorking; //find the working match cases which are represented by the difference of the total standards and the cases that don't work and return it
    return difference;
}
 
 int determineMatchLevel(const int distance[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], int nStandards, const char jeet[])
 {
     if(nStandards <= 0)
     {
         return 0;
     }
     char tempJeet[281] = {}; //create a new cstring to store the working values of jeet and a counter to store the current position of that new variable
     int sizeTemp = 0;
     int matchStandards = 0;
     for(int i = 0; i < strlen(jeet); i++) //iterate through the length of jeet
     {
         if((isalpha(jeet[i])) && isupper(jeet[i])) //if the value of jeet is alpha and uppercase input the lowercase value into the new cstring and increment the current position counter
         {
             tempJeet[sizeTemp] = tolower(jeet[i]);
             sizeTemp++;
         }
         else if(isalpha(jeet[i]) && islower(jeet[i])) //if the value of jeet is alpha and is lower input the value into the new cstring and increment the current position counter
         {
             tempJeet[sizeTemp] = jeet[i];
             sizeTemp++;
         }
         else if(jeet[i] == ' ') //if the value of jeet is a space
         {
             if(i == 0 || sizeTemp == 0) //check if it is at the beginning of the current position and do nothing if so
             {
        
             }
             else if(tempJeet[sizeTemp - 1] == ' ') //check if the character at the position before the current of the new cstring is a space and if so do nothing
             {
                 
             }
             else //else add a space at the current position and increment the position counter
             {
             tempJeet[sizeTemp] = ' ';
             sizeTemp++;
             }
         }
         else if (!(isalpha(jeet[i])) && !(jeet[i] == ' ')) //check if the current value of jeet is not alpha and is not a space and if so skip over it
         {
             
         }
     }
     int alpha = 0;
     for(int i = 0; i < sizeTemp; i++) //iterate through the new cstring to check if there is at least 1 alpha character if not return 0 for working match standards as it is empty
     {
         if(isalpha(tempJeet[i]))
         {
             alpha++;
         }
     }
     if (alpha == 0 || tempJeet[0] == '\0')
     {
         return matchStandards;
     }
     int n = 0;
     int numWords = 0;
     
     char allWords[281][281]; //create an array of cstrings and iterate through it to set all values to null
     for(int i = 0; i < 281; i++)
     {
         for(int z = 0; z < 281; z++)
         {
             allWords[i][z] = '\0';
         }
        
     }
     for(int i = 0; i < sizeTemp; i++) //iterate through the new cstring of only spaces and lowercase letters and assign the separate words to different positions in the array
     {
         for(int z = 0; z < sizeTemp; z++)
         {
             if(tempJeet[n] != ' ')
             {
                 allWords[i][z] = tempJeet[n];
                 n++;
             }
             else
             {
                 n++;
                 numWords++;
                 break;
             }
         }
         if(tempJeet[n] == '\0') //if the program reaches the null character in the cstring then break as the last word has been added
         {
             numWords++;
             break;
         }
     }
     bool w1found;
     int posFirst, posSecond;
     for(int i = 0; i < nStandards; i++) //iterate through nStandards to search for word1 and word2 in the array
     {
         posFirst = -1;
         posSecond = -1;
         w1found = false;
         for(int z = 0; z < numWords; z++) //iterate through the words in the array
         {
             if((!w1found) && strcmp(allWords[z], word1[i]) == 0) //if the first word has not been found yet in the array and the current word is the same as the first word, store the position in the array of the first word
             {
                 posFirst = z;
                 w1found = true;
             }
             else if(w1found && strcmp(allWords[z], word2[i]) == 0) //if the first word has been found and the current word is the same as the second word being searched for, store the position in the array of the second word and break
             {
                 posSecond = z;
                 break;
             }
         }
         if(posFirst != -1 && posSecond != -1) //if the positions were found, check if the distance between the positions is less than or equal to the distance given in the distance array and if so increment match standards
         {
             int foundDistance = posSecond - posFirst;
             if(foundDistance <= distance[i])
             {
                 matchStandards++;
             }
         }
     }
     return matchStandards; //return the value of matchStandards
 }
   

int main()
{
}

