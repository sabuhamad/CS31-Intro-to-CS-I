#include <iostream>
#include <string>
using namespace std;

int main() {
    int initialMeterReading;
    int finalMeterReading;
    string customerName;
    double bill;
    int month;
    cout << "Initial meter reading: ";
    cin >> initialMeterReading; //receives input for the initial meter reading
    cout << "Final meter reading: ";
    cin >> finalMeterReading; //receives input for the final meter reading
    cout << "Customer name: ";
    cin.ignore(10000, '\n'); //ignores input that may be a space
    getline(cin, customerName); //receives input for the customer Name as a string
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    cin >> month; //receives input for the month
    cout << "---" << endl;
    if(initialMeterReading < 0) //if the initial meter reading is inputted as negative
    {
        cout << "The initial meter reading must not be negative." << endl; //end program after telling the user that the initial meter reading should not be negative
    }
    else if(finalMeterReading < initialMeterReading) //if the initial meter reading is greater than or equal to that of the final meter reading (it should always be less)
    {
        cout << "The final meter reading must be at least as large as the initial reading." << endl; //end program after telling the user that the initial meter reading should be less than or equal to the final meter reading
    }
    else if(customerName.empty()) //checks if the customerName string input is empty
    {
        cout << "You must enter a customer name." << endl; //ends the program after telling the user that the customer name cannot be empty
    }
    else if(!(month >= 1 && month <= 12)) //checks if the month inputted is within the valid range 1-12
    {
        cout << "The month number must be in the range 1 through 12." << endl; //ends the program and lets the user know that the month range has to fall between 1 and 12 inclusive
    }
    else
    {
        int difference = finalMeterReading - initialMeterReading; //finds the increase over this month
        if(month >= 4 && month <= 10) //checks if within the high usage season
        {
            if(difference <= 23 ) //if less than or equal to 23, only calculate the first tier price for the entire difference
            {
                bill = difference * 5.41;
            }
            else //if not, only calculate the first tier price for the first 23 HCF and then  the second tier price for the high usage season for all HCF more than 23 and add the two
            {
                int overLimit = difference - 23;
                bill = (5.41 * 23) + (overLimit * 9.79);
            }
        }
        else //month is within the low usage season
        {
           if(difference <= 15) //if less than or equal to 15, only calculate the first tier price for the entire difference
           {
               bill = difference * 5.41;
           }
           else //if not, only calculate the first tier price for the first 15 HCF and then  the second tier price for the low usage season for all HCF more than 15 and add the two
           {
               int overLimit = difference - 15;
               bill = (5.41 * 15) + (overLimit * 7.77);
           }
        }
        //ensure output is formatted to 2 decimal places
        cout.setf(ios::fixed);
        cout.precision(2);
        //output the final calculation
        cout << "The bill for " << customerName << " is $" << bill << endl;
    }
    
}
