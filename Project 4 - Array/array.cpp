using namespace std;
#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
int enumerate(const string a[], int n, string target) //counts how many times target appears in a[]
{
    if(n < 0) //check if n is negative and invalid
        return -1;
    int count = 0;
    for(int i = 0; i< n; i++)
        if(a[i] == target) //if this string is the same as target increment count by 1
            count++;
    return count; //return how many targets were found
}


int findMatch(const string a[], int n, string target)
{
    if(n < 0)//check if n is negative and invalid
        return -1;
    for(int i = 0; i< n; i++)
        if(a[i] == target)
            return i; //return the position of the match
    return -1;
}
bool findRun(const string a[], int n, string target, int& begin, int& end)
{
    int row = 0; //tracks row
    if(n < 0) //check if n is negative and invalid
        return false;
    for(int i = 0; i< n; i++)
    {
        if(a[i] == target && row == 0) //if the string matches target and there
        {
            begin = i; //set begin equal to position
            row++; //add 1 to row to understand there is a sequence
            if(i + 1 == n || a[i+1] != target) //if the next position is out of bounds or is in bounds but is not the target, end is the same position
            {
                end = i;
                return true;
            }
        }
        else if(i+1 == n && row != 0) //if there is a row of the same target values and the next position is out of bounds, end is this position
        {
            end = i;
            return true;
        }
        else if(a[i] == target && row!= 0 ) //if there is a row of the same target values and the current position is still equal to target
        {
            if(a[i+1] != target) //check if next position is not equal to the target and if so set the end position to the current
            {
                end = i;
                return true;
            }
        }
    }
    return false; //if it passes all the loops without returning, return false as there is no target
}
int findMin(const string a[], int n)
{
    if(n <= 0) //check if n is 0 or negative because should return -1 if array is empty as well
        return -1;
    int pos = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] <= a[pos]) //if the current string at position i is <= the other string at position pos, set pos to the current position
            pos = i;
    }
    return pos;
}
int moveToEnd(string a[], int n, int pos)
{
    if(n < 0 || pos > n-1 || pos < 0) //check if n is negative or position is greater than the last index or negative and thus invalid
        return -1;
    string temp = a[pos];
    for(int i = pos; i < n; i++) //iterate starting at the position of interest
        if(i+1 == n) //catch for array going out of bounds
            a[i] = temp;
        else //else move the string over one position to the left
            a[i] = a[i+1];
    return pos;
}
int moveToBeginning(string a[], int n, int pos)
{
    if(n < 0 || pos > n-1 || pos < 0) //check if n is negative or position is greater than the last index and thus invalid
        return -1;
    string temp = a[0]; //save value at first index
    string newtemp;
    a[0] = a[pos]; //set the first index value to the value at position pos
    for(int i = 1; i < pos + 1; i++)
    {
        newtemp = a[i];//use secondary temp variable to store value at i
        a[i] = temp; //set current value to value stored in temp
        temp = newtemp; //store newtemp value into temp
    }
    //return the position of the index that was sent to the beginning
    return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0) //check if either n1 or n2 are negative and thus invalid
        return -1;
    int smaller;
    if(n1 <= n2) //find the smaller array
        smaller = n1;
    else
        smaller = n2;
    for(int i = 0; i < smaller; i++) //iterate through only the smaller array size
        if(!(a1[i] == a2[i]))
            return i; //if the values don't line up return the position that doesn't line up
    return smaller; //if all values line up return size of smaller array
}
int removeDups(string a[], int n)
{
    int elements = 0;
    bool dup = false;
    int pos;
    if(n < 0) //check if n is negative and thus invalid
        return -1;
    for(int i = 1; i < n; i++) //iterate through array
    {
        if(dup) //check if there are dupliates found
        {
            if(i + 1 == n) //if the next index goes out of bounds return number elements
            {
                return elements;
            }
            else //if not check if the next value is the same
            {
                if(a[i] == a[i+1]) //if the next value is the same do nothing and carry on
                {
                    
                }
                else //if it is different, set the value at pos = to the new different value and set the dup variable to false indicating there are no duplicates and increment i to skip to the next variable when testing
                {
                    dup = false;
                    a[pos] = a[i+1];
                    i++;
                }
            }
        }
        else if(a[i-1] == a[i]) //if no duplicates had been found previously, check if the value at the position before is the same as the current
        {
            elements++; //if so increment elements
            if(i + 1 == n) //check if next index is out of bounds and if so return elements
            {
                return elements;
            }
            else //if not then check if the next value is not equal to the current
            {
                if(a[i] != a[i+1]) //if it is not the same then set the current value equal to the value at the next position and increment i
                {
                    a[i] = a[i+1];
                    i++;
                }
                else //if not then there are duplicates so set dup to true and the initial occurance of the duplicates (or "pos") to i
                {
                    dup = true;
                    pos = i;
                }
            }
        }
        else //if not then the variables are different and increment elements
        {
            elements++;
        }
    }
    return elements;
}
bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    bool appears;
    int start = 0;
    if(n1 < 0 || n2 < 0) //check if either n1 or n2 are negative and thus invalid
        return false;
    for(int i = 0; i < n2; i++)
    {
        appears = false; //set appears to false
        for(int j = start; j < n1; j++) //increment starting at "start" to ensure the strings are in subsequent order
        {
            if(a1[j] == a2[i])
            {
                appears = true; //show that the value was found
                start = j + 1; //set the new starting point for the next for loop to ensure the strings are in subsequent order
                break;
            }
        }
        if(!appears) //if the value was not found appear will still be false and thus the program should exit as the value in a2 was not found in a1
            return false;
    }
    //if all for loops are iterated through return true
    return true;
}
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    int pos1 = 0, pos2 = 0;
    if(n1 < 0 || n2 < 0 || max < 0 || (n1 + n2 > max)) //check if n1, n2, or max are negative or if n1 + n2 is greater than max and thus invalid
        return -1;
    for(int i = 0; i < n1; i++) //check if a1 is in nondescending order
    {
        if(i + 1 == n1)
        {
            
        }
        else if(a1[i] > a1[i+1])
        {
            return -1;
        }
    }
    for(int i = 0; i < n2; i++) //check if a2 is in nondescending order
    {
        if(i + 1 == n2)
        {
            
        }
        else if(a2[i] > a2[i+1])
        {
            return -1;
        }
    }
    for(int i = 0; i < n1+n2; i++) //iterate through a combination of both sizes of arrays
    {
        if(pos1 == n1 - 1 && pos2 == n2 - 1) //if the position in the first array is going to be out of bounds in the first array and the position of the second array is going to be out of bounds in the second array, then break
        {
            break;
        }
        else if(pos2 == n2) //if pos2 is out of bounds in array 2, add the string at pos1 in array 1 to the result function and increment pos1
        {
            result[i] = a1[pos1];
            pos1++;
        }
        else if(pos1 == n1) //if pos1 is out of bounds in array 1, add the string at pos2 in array 2 to the result function and increment pos2
        {
            result[i] = a2[pos2];
            pos2++;
        }
        else if(a1[pos1] > a2[pos2]) //if the value of a1 at pos1 > a2 at pos2 then set the value of result at position i to pos2 in a2 and increment pos2
        {
            result[i] = a2[pos2];
            pos2++;
        }
        else if(a2[pos2] > a1[pos1])//if the value of a2 at pos2 > a1 at pos1 then set the value of result at position i to pos1 in a1 and increment pos1
        {
            result[i] = a1[pos1];
            pos1++;
        }
        else if(pos1 > n1 - 1) //if pos1 is out of bounds of a1 then set the value of result at the current position to the value at pos2 of a2 and increment pos2
        {
            result[i] = a2[pos2];
            pos2++;
        }
        else if (pos2 > n2 - 1)//if pos2 is out of bounds of a2 then set the value of result at the current position to the value at pos1 of a1 and increment pos1
        {
            result[i] = a1[pos1];
            pos1++;
        }
        else if(a1[pos1] == a2[pos2]) //if the values at both positions are the same
        {
            if(pos1 > pos2) //check which position is larger and set the value to the smaller one and increment that one
            {
                result[i] = a2[pos2];
                pos2++;
            }
            else
            {
                result[i] = a1[pos1];
                pos1++;
            }
        }
    }
    return n1 + n2; //return the size of result which is the sum of both array sizes
}
int divide(string a[], int n, string divider)
{
    string z[10000]; //declare a placeholder array
    int pos = 0, mid;
    if(n < 0) //check if n is negative and thus invalid
        return -1;
    for(int i = 0; i < n; i++) //iterate through a and add each value less than divider to z while incrementing position
    {
        if(a[i] < divider)
        {
            z[pos] = a[i];
            pos++;
        }
    }
    mid = pos; //at this point position is equal to the first value that will be larger than or equal to "divider"
    for(int i = 0; i < n; i++) //iterate through a and add each value greater than divider to z while incrementing position
    {
        if(a[i] > divider)
        {
            z[pos] = a[i];
            pos++;
        }
    }
    if(mid == pos) //if mid is the same as position that means there are only values less than or equal to divider so return n after setting the value of the array a to the placeholder z
    {
        a = z;
        return n;
    }
    else //return the saved position at mid after setting the value of the array a to the placeholder z
    {
        a = z;
        return mid;
    }
}
int main()
    {
        string h[7] = { "neil", "sonia", "john", "amy", "", "elena", "john" };
        assert(enumerate(h, 7, "john") == 2);
        assert(enumerate(h, 7, "") == 1);
        assert(enumerate(h, 7, "brett") == 0);
        assert(enumerate(h, 0, "john") == 0);
        string d[9] = {
            "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy"
        };
        assert(enumerate(d, 9, "amy") == 4);     // returns 4
        assert(enumerate(d, 5, "ketanji") == 1); // returns 1
        assert(enumerate(d, 9, "brett") == 0);   // returns 0
        assert(findMatch(h, 7, "john") == 2);
        assert(findMatch(h, 2, "john") == -1);
        int bg;
        int en;
        assert(findRun(h, 7, "amy", bg, en) && bg == 3 && en == 3);

        string g[4] = { "neil", "sonia", "amy", "elena" };
        string v[9] = {
            "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy"
        };
        int b;
        int e;
        assert(findRun(v, 9, "amy", b, e) == true && b == 2 && e == 3);     //  returns true and
                                                  //    sets b to 2 and e to 3
        assert(findRun(v, 9, "neil", b, e) == true && b == 1 && e == 1);    //  returns true and
                                                  //    sets b to 1 and e to 1
       assert(findRun(v, 9, "samuel", b, e) == false);  //  returns false and
                                                  //    leaves b and e unchanged
        assert(findMin(g, 4) == 2);
        assert(findDifference(h, 4, g, 4) == 2);
        assert(subsequence(h, 7, g, 4));
        string big[10] = { "elena", "john", "amy", "ketanji", "neil", "amy" };
        string little1[10] = { "john", "ketanji", "neil" };
        assert(subsequence(big, 6, little1, 3)) ;  // returns true
        string little2[10] = { "amy", "john" };
        assert(!subsequence(big, 6, little2, 2));  // returns false
        string little3[10] = { "john", "amy", "amy" };
        assert(subsequence(big, 6, little3, 3));  // returns true
        string little4[10] = { "john", "john", "amy" };
        assert(!subsequence(big, 6, little4, 3));  // returns false
        assert(subsequence(big, 6, little4, 0));  // returns true

        assert(moveToEnd(g, 4, 1) == 1 && g[1] == "amy" && g[3] == "sonia");
        string ppl[5] = { "john", "sonia", "samuel", "elena", "neil" };
        assert(moveToBeginning(ppl, 5, 2) == 2 && ppl[3] == "elena");  // returns 2
        // people now contains:  "samuel"  "john"  "sonia"  "elena"  "neil"
        string f[4] = { "elena", "amy", "sonia", "john" };
        assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "sonia" && f[2] == "amy");
    
        string x[5] = { "elena", "elena", "elena", "sonia", "sonia" };
        assert(removeDups(x, 5) == 2 && x[1] == "sonia");
        string h2[9] = {
        "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy"
        };
        assert(removeDups(h2, 9) == 5 && h2[3] == "ketanji");  //  returns 5
           //  d[0] through d[4] now contain  "clarence" "neil" "amy" "ketanji" "amy"
           //  We no longer care what strings are in d[5] and beyond.
        string l[9] = {
            "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy"
        };
        assert(removeDups(l, 9) == 5);  //  returns 5
               //  d[0] through d[4] now contain  "clarence" "neil" "amy" "ketanji" "amy"
               //  We no longer care what strings are in d[5] and beyond.
    
        string c[4] = { "john", "john", "samuel", "sonia" };
        string y[4] = { "amy", "elena", "john", "ketanji" };
        string z[10];
        assert(makeMerger(c, 4, y, 4, z, 10) == 8 && z[5] == "ketanji");
        string x1[5] = { "amy", "elena", "elena", "ketanji", "samuel" };
        string y1[4] = { "clarence", "elena", "john", "sonia" };
        string z1[20];
        assert(makeMerger(x1, 5, y1, 4, z1, 20) == 9);  // returns 9
        // z has  amy clarence elena elena elena john ketanji samuel sonia
    
        string q[7] = { "neil", "sonia", "john", "amy", "", "elena", "john" };
        string sc[6] = { "john", "amy", "samuel", "elena", "sonia", "neil" };
        assert(divide(sc, 6, "ketanji") == 3);  //  returns 3
        // sc must now be
        //      "elena"  "john"  "amy"  "neil"  "sonia"  "samuel"
        // or   "john"  "amy"  "elena"  "samuel"  "neil"  "sonia"
        // or one of several other orderings.
        // All elements < "ketanji" (i.e., "john", "amy", and "elena")
        //   come before all others
        // All elements > "ketanji" (i.e., "sonia", "neil", and "samuel")
        //   come after all others
        string sc2[4] = { "john", "sonia", "amy", "neil" };
        assert(divide(sc2, 4, "neil") == 2) ;  //  returns 2
        // sc2 must now be either
        //      "john"  "amy"  "neil"  "sonia"
        // or   "amy"  "john"  "neil"  "sonia"
        // All elements < "neil" (i.e., "amy" and "john") come
            // before all others.
        // All elements > "neil" (i.e., "sonia") come after all others.
        assert(divide(q, 7, "john") == 3);

        cout << "All tests succeeded" << endl;
    }
