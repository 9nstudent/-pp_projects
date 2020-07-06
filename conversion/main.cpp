#include <iostream>
#include <Windows.h>

using namespace std;

void real2bin_hex(double a, bool flag) {
    unsigned long long* ull((unsigned long long*) & a);
    unsigned char nbits(flag ? 64 : 32);
    char* num16 = new char[nbits >> 2]();
    if (!flag)
        ull = (unsigned long long*)((unsigned int*)ull + 1);
    const char lut[] = "0123456789ABCDEF";
    for (int i(0); i < nbits >> 2; i++)
        num16[i] = lut[*ull >> ((nbits >> 2) - i - 1 << 2) & 15];
    for (int i(0); i < nbits; i++)
        cout << (*ull >> nbits - i - 1 & 1);
    cout << endl;
    for (int i(0); i < nbits >> 2; i++)
        cout << num16[i];
    cout << endl;
}

void hex2bin_real(char* mass16, bool flag) {
    unsigned long long ull(0);
    unsigned char nbits(flag ? 64 : 32);
    const char lut[] = "0123456789ABCDEF";
    for (int i(0); i < nbits >> 2; i++)
        for (int j = 0; j < 16; j++)
            if (lut[j] == toupper(mass16[i]))
                ull = (ull << 4) + j;
    for (int i(0); i < nbits; i++)
        cout << (ull >> nbits - i - 1 & 1);
    if (!flag)
        ull << 32;
    cout << endl << *(double*)&ull << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    bool flag;
    char param;
    system("cls");
    cout << "Число будет одинарной или двойной точности? 0/1" << endl;
    cin >> flag;
    if (flag != 0 && flag != 1) {
        cout << "Введены некорректные данные" << endl;
        system("pause");
        return 1;
    }

    cout << "Данные будут в формате числа с плавующей точкой или шестнадцетиричной строки? R/H" << endl;
    cin >> param;
    if (toupper(param) == 'R' || toupper(param) == 'H') {
        if (toupper(param) == 'R') {
            double k;
            cout << "Введите число" << endl;
            cin >> k;
            real2bin_hex(k, flag);
        }
        else {
            char* mass16 = new char[flag ? 16 : 8]();
            cout << "Введите число" << endl;
            cin >> mass16;
            hex2bin_real(mass16, flag);
        }
    }
    else {
        cout << "Введены некорректные данные" << endl;
        system("pause");
        return 1;
    }
    system("pause");
    return 0;
}
