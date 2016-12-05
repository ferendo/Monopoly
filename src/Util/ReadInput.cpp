//
// Created by dylan on 17/11/2016.
//

#include "ReadInput.h"

int Util::readIntegerWithRange(int lowerRange, int upperRange) {
    string number;
    while(true) {
        try {
            getline(cin, number);
            // stoi will throw an exception if no numbers were given
            int givenNumber = stoi(number);
            if (givenNumber >= lowerRange && givenNumber <= upperRange) {
                return givenNumber;
            }
        }
        catch (invalid_argument error){}
        catch (out_of_range) {};
        cout << "Invalid input, try again." << endl;
    }
}

string Util::readString() {
    string input;
    while (true) {
        getline(cin, input);
        if (!input.empty()) {
            return input;
        }
        cout << "Invalid input, try again." << endl;
    }
}

double Util::readPositiveDoubleWithLimit(double limit) {
    string number;
    while(true) {
        try {
            getline(cin, number);
            // stod will throw an exception if no numbers were given
            double givenNumber = stod(number);
            if (givenNumber >= 0 && givenNumber <= limit) {
                return givenNumber;
            }
        }
        catch (invalid_argument error){}
        catch (out_of_range){};
        cout << "Invalid input, try again." << endl;
    }
}

void Util::pressEnterToContinue() {
    cout << "Press Enter to Continue";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}
