#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <stdexcept>  

using namespace std;

template <typename T>
string to_string(T value) {
    ostringstream os;
    os << value;
    return os.str();
}

// Class to handle conversions between number systems
class Converter {
public:
    // Binary to Decimal
    static double binaryToDecimal(const string& binary) {
        return stringToDecimal(binary, 2);
    }

    // Decimal to Binary
    static string decimalToBinary(double dec) {
        return decimalToBase(dec, 2);
    }

    // Octal to Decimal
    static double octalToDecimal(const string& octal) {
        return stringToDecimal(octal, 8);
    }

    // Decimal to Octal
    static string decimalToOctal(double dec) {
        return decimalToBase(dec, 8);
    }

    // Hexadecimal to Decimal
    static double hexadecimalToDecimal(const string& hex) {
        return stringToDecimal(hex, 16);
    }

    // Decimal to Hexadecimal
    static string decimalToHexadecimal(double dec) {
        return decimalToBase(dec, 16);
    }

private:
    // Common logic to convert a string to decimal for any base
    static double stringToDecimal(const string& num, int base) {
        double decimal = 0.0;
        int pointPos = num.find('.');

        // Handle integer part
        int i = (pointPos == string::npos) ? num.length() - 1 : pointPos - 1;
        int multiplier = 1;
        for (; i >= 0; i--) {
            decimal += charToDigit(num[i]) * multiplier;
            multiplier *= base;
        }

        // Handle fractional part
        if (pointPos != string::npos) {
            double fracMultiplier = 1.0 / base;
            for (i = pointPos + 1; i < num.length(); i++) {
                decimal += charToDigit(num[i]) * fracMultiplier;
                fracMultiplier /= base;
            }
        }

        return decimal;
    }

    // Convert decimal to any base and return as string
    static string decimalToBase(double dec, int base) {
        int intPart = static_cast<int>(dec);
        double fracPart = dec - intPart;
        string result = "";

        if (intPart == 0) {
            result = "0";
        } else {
            result = printIntegerPart(intPart, base);
        }

        if (fracPart > 0) {
            result += ".";
            result += printFractionalPart(fracPart, base);
        }

        return result;
    }

    // Helper to convert character to digit
    static int charToDigit(char ch) {
        if (ch >= '0' && ch <= '9') return ch - '0';
        if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
        if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
        return 0;
    }

    // Helper to print the integer part in a given base as string
    static string printIntegerPart(int intPart, int base) {
        string result;
        while (intPart > 0) {
            int remainder = intPart % base;
            result = (remainder < 10 ? to_string(remainder) : string(1, 'A' + (remainder - 10))) + result;
            intPart /= base;
        }
        return result;
    }

    // Helper to print the fractional part in a given base as string
    static string printFractionalPart(double fracPart, int base) {
        string result;
        int precision = 10;
        while (fracPart > 0 && precision--) {
            fracPart *= base;
            int fracInt = static_cast<int>(fracPart);
            result += (fracInt < 10 ? to_string(fracInt) : string(1, 'A' + (fracInt - 10)));
            fracPart -= fracInt;
        }
        return result;
    }
};

// Class to handle bitwise operations
class BitwiseOperations {
private:
    string x;
    string y;

    // Convert binary string to decimal
    int total(const string& binary) const {
        int decimalValue = 0;
        for (size_t i = 0; i < binary.length(); i++) {
            int bit = binary[binary.length() - 1 - i] - '0'; // Reverse bit position for LSB first
            decimalValue += bit * pow(2, i);                 // Calculate decimal value
        }
        return decimalValue;
    }

    // Perform bitwise operations
    void performOperations() const {
        string resultAND, resultOR, resultXOR, resultNOTx, resultNOTy;
        for (size_t i = 0; i < x.length(); i++) {
            int bitA = x[i] - '0';
            int bitB = y[i] - '0';
            resultAND += (bitA & bitB) ? '1' : '0';
            resultOR += (bitA | bitB) ? '1' : '0';
            resultXOR += (bitA ^ bitB) ? '1' : '0';
            resultNOTx += (bitA == 0) ? '1' : '0';
            resultNOTy += (bitB == 0) ? '1' : '0';
        }


int spc = 8;
        // Output the results in a table format
        cout << "\n\n"<<left << setw(spc) << "X"
             << "| " << setw(spc) << "Y"
             << "| " << setw(spc) << "AND"
             << "| " << setw(spc) << "OR"
             << "| " << setw(spc) << "XOR"
             << "| " << setw(spc) << "~X"
             << "| " << setw(spc) << "~Y"
             << endl;

        cout << ""<<setfill('-') << setw(70) << "" << setfill(' ') << endl;

        for (size_t i = 0; i < x.length(); i++) {
            char xBit = x[i];
            char yBit = y[i];
            cout << ""<< left << setw(spc) << xBit
                 << "| " << setw(spc) << yBit
                 << "| " << setw(spc) << resultAND[i]
                 << "| " << setw(spc) << resultOR[i]
                 << "| " << setw(spc) << resultXOR[i]
                 << "| " << setw(spc) << resultNOTx[i]
                 << "| " << setw(spc) << resultNOTy[i]
                 << endl;
        }

        cout <<""<< setfill('-') << setw(70) << "" << setfill(' ') << endl;
        cout  << ""<< left << setw(spc) << total(x)
             << "| " << setw(spc) << total(y)
             << "| " << setw(spc) << total(resultAND)
             << "| " << setw(spc) << total(resultOR)
             << "| " << setw(spc) << total(resultXOR)
             << "| " << setw(spc) << total(resultNOTx)
             << "| " << setw(spc) << total(resultNOTy)
             << endl;
    }

public:
    // Constructor to initialize binary strings
    BitwiseOperations(const string& x, const string& y) : x(x), y(y) {
        if (x.length() != y.length()) {
            throw invalid_argument("Binary strings must be of the same length.");
        }
    }

    // Execute the bitwise operations
    void execute() const {
        performOperations();
    }
};


class Calculator {
private:
    string num1, num2;
    char op;
    int base;
    double result;

    double convertToDecimal(const string& num, int base) {
        switch (base) {
            case 1:
                return Converter::binaryToDecimal(num);
            case 2:
 
                        return atof(num.c_str());
            case 3:
                       return Converter::octalToDecimal(num);
            case 4:
                return Converter::hexadecimalToDecimal(num);
            default:
                throw invalid_argument("Invalid base");
        }
    }

    string convertFromDecimal(double num, int base) {
        switch (base) {
            case 1:
                return Converter::decimalToBinary(num);
            case 2:
              
                      return to_string(num);
            case 3:
            return Converter::decimalToOctal(num);
            case 4:
                return Converter::decimalToHexadecimal(num);
            default:
                throw invalid_argument("Invalid base");
        }
    }

    void performCalculation() {
        double num1dec = convertToDecimal(num1, base);
        double num2dec = convertToDecimal(num2, base);

        switch (op) {
            case '+': result = num1dec + num2dec; break;
            case '-': result = num1dec - num2dec; break;
            case '*': result = num1dec * num2dec; break;
            case '/':
                if (num2dec == 0) throw runtime_error("Division by zero.");
                result = num1dec / num2dec;
                break;
            default:
                throw invalid_argument("Invalid operation.");
        }
    }

public:
    Calculator(const string& num1, const string& num2, char op, int base)
        : num1(num1), num2(num2), op(op), base(base), result(0) {}

    void execute() {
        try {
            performCalculation();
            cout << "Result: " << convertFromDecimal(result, base) << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};


int main() {
	
	
	
    int menu;
cout << "    _   _ _   _ __  __ ____  _____ ____       ______   ______ _____ _____ __  __ \n"
        "   | \\ | | | | |  \\/  | __ )| ____|  _ \\     / ___\\ \\ / / ___|_   _| ____|  \\/  |\n"
        "   |  \\| | | | | |\\/| |  _ \\|  _| | |_) |    \\___ \\\\ V /\\___ \\ | | |  _| | |\\/| |\n"
        "   | |\\  | |_| | |  | | |_) | |___|  _ <      ___) || |  ___) || | | |___| |  | |\n"
        "   |_| \\_|\\___/|_|  |_|____/|_____|_| \\_\\    |____/ |_|_|____/_|_| |_____|_|  |_|\n\n";
          
    cout << "\n\n1. Bitwise Operators\n2. Conversion\n3. Calculator\n\nEnter Choice: ";
    cin >> menu;

    if (menu == 1) {
    	
        string x, y;

        cout << "\n\nEnter Binary X: ";
        cin >> x;

        cout << "\n\nEnter Binary Y: ";
        cin >> y;

        try {
            BitwiseOperations operations(x, y);
            operations.execute();
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            return 1; // Exit the program with an error code
        }

    } else if (menu == 2) {
        int from, to;
        double dec_inp;
        string binary_inp, octal_inp, hex_inp;

        cout << "\nConvert From: \n1. Binary\n2. Decimal\n3. Octal\n4. Hexadecimal\n\nEnter Choice: ";
        cin >> from;
        cout << "\n----->\nConvert To\n1. Binary\n2. Decimal\n3. Octal\n4. Hexadecimal\n\nEnter Choice: ";
        cin >> to;

        switch (from) {
            case 1: cout << "Enter Binary: "; cin >> binary_inp; break;
            case 2: cout << "Enter Decimal: "; cin >> dec_inp; break;
            case 3: cout << "Enter Octal: "; cin >> octal_inp; break;
            case 4: cout << "Enter Hexadecimal: "; cin >> hex_inp; break;
        }

        switch (to) {
            case 1:
                if (from == 2) cout << Converter::decimalToBinary(dec_inp) << endl;
                else if (from == 3) cout << Converter::decimalToBinary(Converter::octalToDecimal(octal_inp)) << endl;
                else if (from == 4) cout << Converter::decimalToBinary(Converter::hexadecimalToDecimal(hex_inp)) << endl;
                break;

            case 2:
                if (from == 1) cout << Converter::binaryToDecimal(binary_inp) << endl;
                else if (from == 3) cout << Converter::octalToDecimal(octal_inp) << endl;
                else if (from == 4) cout << Converter::hexadecimalToDecimal(hex_inp) << endl;
                break;

            case 3:
                if (from == 1) cout << Converter::decimalToOctal(Converter::binaryToDecimal(binary_inp)) << endl;
                else if (from == 2) cout << Converter::decimalToOctal(dec_inp) << endl;
                else if (from == 4) cout << Converter::decimalToOctal(Converter::hexadecimalToDecimal(hex_inp)) << endl;
                break;

            case 4:
                if (from == 1) cout << Converter::decimalToHexadecimal(Converter::binaryToDecimal(binary_inp)) << endl;
                else if (from == 2) cout << Converter::decimalToHexadecimal(dec_inp) << endl;
                else if (from == 3) cout << Converter::decimalToHexadecimal(Converter::octalToDecimal(octal_inp)) << endl;
                break;
        }

        } else  if (menu == 3) {
        string num1, num2;
        char op;
        int base;

        cout << "1. Binary [2]\n2. Decimal [10]\n3. Octal [8]\n4. Hexadecimal [16]\n";
        cin >> base;

        cout << "Enter num 1: ";
        cin >> num1;

        cout << "Enter arithmetic operation (+, -, *, /): ";
        cin >> op;

        cout << "Enter num 2: ";
        cin >> num2;

        Calculator calc(num1, num2, op, base);
        calc.execute();
    }
    return 0;

}

