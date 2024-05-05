#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Функция для преобразования дробного числа в бинарный вид
string toBinary(double num, int precision) {
    string result = "";
    int integerPart = (int)num;
    double fractionalPart = num - integerPart;

    // Преобразование целой части в бинарный вид
    while (integerPart > 0) {
        result = to_string(integerPart % 2) + result;
        integerPart /= 2;
    }

    // Преобразование дробной части в бинарный вид
    result += '.';
    int count = 0;
    while (fractionalPart > 0 && count < precision) {
        fractionalPart *= 2;
        int digit = (int)fractionalPart;
        result += to_string(digit);
        fractionalPart -= digit;
        count++;
    }

    return result;
}

int shiftDecimal(string& numStr) {
    size_t decimalPos = numStr.find('.');// Находим позицию десятичной точки в строке
    int exponent;
    if (numStr[0] == '0') {
        // Найти позицию первого символа отличного от '0' начиная от точки
        size_t pos = numStr.find_first_not_of('0', decimalPos+1);
        exponent = pos-1;
        numStr.erase(0, pos); // Удаляем символ из текущей позиции
    } else {
        exponent = int(decimalPos) - 1;// Получаем степень числа
        numStr.erase(decimalPos, 1); // Удаляем символ из текущей позиции
    }
    numStr.insert(1, 1, '.'); // Вставляем символ на новую позици
    return exponent;
}

string getMantissa(string numStr, int zerosToAdd) {
    size_t pos = numStr.find('.');
    numStr = numStr.substr(pos + 1); // отбрасывание 1.
    numStr = numStr + string(zerosToAdd - numStr.length(), '0');// Добавляем необходимое количество нулей в конец строки
    return numStr;
}

string getExponent(int exponent, int bias, int zerosToAdd){
    double stored_exponent = exponent + bias;
    string numStr = toBinary(stored_exponent, 23);
    size_t pos = numStr.find('.');
    numStr.erase(pos, 1); // Удаляем символ из текущей позиции
    numStr = string(zerosToAdd - numStr.length(), '0') + numStr;// Добавляем необходимое количество нулей в начало строки
    return numStr;
}

string to_ieee754(double num) {
    char sign = (num >= 0) ? '0' : '1'; // Отделение знака от числа
    double absValue = fabs(num); // Получение абсолютного значения числа
    string numStr = toBinary(absValue, 23);
    int exponent = shiftDecimal(numStr);
    string mantissa = getMantissa(numStr, 23);
    string Exponent = getExponent(exponent, 127, 8);
    return sign+Exponent+mantissa;
}

//==============================================================

// Функция для перевода целой части бинарного числа в десятичное
int binaryToDecimal(string binary) {
    int decimal = 0;
    int power = 1; // Начальная степень для умножения

    // Проход по бинарным разрядам справа налево
    for (int i = binary.size() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            decimal += power;
        }
        power *= 2; // Увеличение степени на каждом шаге
    }
    return decimal;
}

// Функция для перевода дробной части бинарного числа в десятичное
double binaryFractionToDecimal(string binary_fraction) {
    double decimal = 0.0;
    double divisor = 2.0;
    for (int i = 0; i < binary_fraction.size(); ++i) {
        if (binary_fraction[i] == '1') {decimal += 1.0 / divisor;}
        divisor *= 2.0;
    }
    return decimal;
}


double from_ieee754(string numStr) {
    char sign = numStr [0];
    numStr.erase(0, 1); //удаление бита знака
    size_t split_index = 8; // Индекс, по которому нужно разделить строку

    // Разделение строки на две части
    string exponent = numStr.substr(0, split_index);
    string mantissa = numStr.substr(split_index);

    int Exponent;
    Exponent = binaryToDecimal(exponent) - 127;
    mantissa = "1." + mantissa.substr(0, mantissa.find_last_not_of('0') + 1);

    //смещение точки дробной части
    mantissa.erase(1, 1); // Удаляем символ из текущей позиции
    if ( Exponent > 0){
        if (mantissa.length()-1 > Exponent) {mantissa.insert(Exponent+1, 1, '.');}// Вставляем символ на новую позици
    }else{
        mantissa = string(abs(Exponent), '0') + mantissa;// Добавляем необходимое количество нулей в начало строк
        mantissa.insert(1, 1, '.'); // Вставляем десфтичную точку
    }

    double ans;
    size_t integerPartEnd = mantissa.find('.');// Индекс, где заканчивается целая часть
    if (integerPartEnd != string::npos) { // Проверяем, что символ найден
        string integerPartBinary = mantissa.substr(0, integerPartEnd);// Получаем целую часть
        string fractionalPartBinary = mantissa.substr(integerPartEnd + 1);// Получаем дробную часть
        ans = binaryToDecimal(integerPartBinary) + binaryFractionToDecimal(fractionalPartBinary);
    } else { //Символ не найден в строке
        ans = binaryToDecimal(mantissa);
    }

    if (sign == '1'){ans = -ans;} //добавление знака

    return ans;
}
