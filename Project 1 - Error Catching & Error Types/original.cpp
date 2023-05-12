// Code for Project 1
    // Report survey results
    
    #include <iostream>
    using namespace std;
    
    int main()
    {
        int numberSurveyed;
        int preferQuarter;
        int preferSemester;
    
        cout << "How many students were surveyed? ";
        cin >> numberSurveyed;
        cout << "How many of them prefer the quarter system? ";
        cin >> preferQuarter;
        cout << "How many of them prefer the semester system? ";
        cin >> preferSemester;
    
        double pctLikeQuarter = 100.0 * preferQuarter / numberSurveyed;
        double pctLikeSemester = 100.0 * preferSemester / numberSurveyed;

        cout.setf(ios::fixed);
        cout.precision(1);
    
        cout << endl;
        cout << pctLikeQuarter << "% prefer the quarter system." << endl;
        cout << pctLikeSemester << "% prefer the semester system." << endl;

        if (preferQuarter > preferSemester)
            cout << "More students prefer the quarter system to the semester system." << endl;
        else
            cout << "More students prefer the semester system to the quarter system." << endl;
    }
