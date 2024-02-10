#include <iostream>
#include <cstdlib>
#include <string>

#include "mmatrix.h"
#include "LinearFilter.h"
#include "BackforwardLinearFilter.h"
#include "mexception.h"

using namespace std;

int main()
{
    double* data;
    string command;
    int i{}, k{}, n{};
    double v;

    do
    {
        cout << "Enter lenght of data string: ";
        cin >> n;
        data = new double[n];
        for (i = 0; i < n; ++i)
        {
            cin >> *(data + i);
        }

        cout << "Enter value of k parameter: ";
        cin >> k;

        try
        {
            LinearFilter filter(n, k, data);
            BackforwardLinearFilter back_filter(n, k, data);
            auto filterPackage = filter.getFilterData();
            auto backFilterPackage = back_filter.getFilterData();

            cout << "Result" << endl << "Forward linear filter:" << endl;
            cout << "x[i]=";
            for (i = 0; i < filterPackage.ElementsNumber; ++i)
            {
                cout << *(filterPackage.elements + i) << "*x[i-" << i + 1 << "] " << "+";
            }
            cout << "0\nBackforward linear filter:" << endl;
            cout << "x[i-" << k << "]=";
            for (i = 0; i < backFilterPackage.ElementsNumber; ++i)
            {
                cout << *(backFilterPackage.elements + i) << "*x[i-" << k - i - 1 << "] " << "+";
            }

            cout << 0 << endl << endl;
        }
        catch (const basic_mexception ex)
        {
            cout << "INTERNAL ERROR:" << endl << ex.description << endl << endl;
        }
        
        delete[] data;
        cout << "do you want to continue? y/n" << endl;
        cin >> command;
    } while (command != "n");
	

    return EXIT_SUCCESS;
}