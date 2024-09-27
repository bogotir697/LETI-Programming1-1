#include <iostream>
#include <array>
#include <cmath>
using namespace std;
using ull = unsigned long long;

bool contains(int item, int arr[]) {
    for (int i = 0; i <= sizeof(arr) / sizeof(arr[0]); i++) {
        if (item == arr[i]) {
            return 1;
        }
    }
    return 0;
}

void printBin(long long x) {
    unsigned long long mask = 1LL << (sizeof(long long) * 8 - 1);
    cout << endl;
    for (int i = 0; i <= (sizeof(long long) * 8 - 1); i++) {
        putchar(mask & x ? '1' : '0');
        mask >>= 1;
    }
    cout << endl;
}

array<ull, 2> moveBin(array<ull, 2> mask, int delta) {
    int lenLL = sizeof(ull) * 8;
    if (delta - lenLL >= 0) { mask = moveBin(mask, delta + 1 - lenLL); delta = lenLL - 1; }
    ull temp = mask[1];
    if (delta == 0) { temp = 0; }
    temp >>= lenLL - delta;
    mask[0] <<= delta;
    mask[0] += temp;
    mask[1] <<= delta;
    return mask;
}

array<ull, 2> createNonInvertMask(int maxIndex) {
    int index, prevIndex = 0;
    int lenLL = sizeof(ull) * 8;
    array<ull, 2> mask = {0, 0};
    cin >> index;
    while (index > prevIndex and index <= maxIndex) {
        int delta = index - prevIndex;
        mask = moveBin(mask, delta);
        mask[1] += 1;
        prevIndex = index;
        cin >> index;
    }
    int delta = lenLL + maxIndex - prevIndex;
    mask = moveBin(mask, delta);
    return mask;
}

int main()
{
    setlocale(0, "");
    cout << "int: " << sizeof(int) << " байт = " << sizeof(int)*8 << " бит \n"
        << "short int: " << sizeof(short int) << " байт = " << sizeof(short int)*8 << " бит \n"
        << "long int: " << sizeof(long int) << " байт = " << sizeof(long int)*8 << " бит \n"
        << "long long: " << sizeof(long long) << " байт = " << sizeof(long long)*8 << " бит \n"
        << "float: " << sizeof(float) << " байт = " << sizeof(float)*8 << " бит \n"
        << "double: " << sizeof(double) << " байт = " << sizeof(double)*8 << " бит \n"
        << "long double: " << sizeof(long double) << " байт = " << sizeof(long double)*8 << " бит \n"
        << "char: " << sizeof(char) << " байт = " << sizeof(char)*8 << " бит \n"
        << "bool: " << sizeof(bool) << " байт = " << sizeof(bool)*8 << " бит \n";

    int a;
    cout << "int: ";
    cin >> a;
    cout << endl;
    unsigned int mask = 1 << sizeof(int)*8 - 1;
    for (int i = 0; i <= (sizeof(int)*8 - 1); i++) {
        putchar(mask & a ? '1' : '0');
        mask >>= 1;
        if (i % 8 == 0) { putchar(' '); }
    }
    cout << endl;
    int inverted_a = 0;
    array<ull, 2> invMask;
    invMask = createNonInvertMask(sizeof(int) * 8);
    mask = 1 << sizeof(int) * 8 - 1;
    for (int i = 0; i < sizeof(int) * 8; i++) {
        inverted_a <<= 1;
        if (mask & invMask[i / (sizeof(ull) * 8)]) {
            putchar(mask & a ? '1' : '0');
            inverted_a += mask & a ? 1 : 0;
        }
        else { 
            putchar(mask & a ? '0' : '1');
            inverted_a += mask & a ? 0 : 1;
        }
        mask >>= 1;
        if (i % 8 == 0) { putchar(' '); }
    }
    cout << endl << inverted_a << endl;

    union {
        float x = 0;
        int y;
    };

    int arr[3] = { 0, 8, 9 };
    cout << "float: ";
    cin >> x;
    cout << endl;

    mask = 1 << sizeof(float) * 8 - 1;
    for (int i = 0; i <= (sizeof(float) * 8 - 1); i++) {
        putchar(mask & y ? '1' : '0');
        mask >>= 1;
        
        if (contains(i, arr)) { putchar(' '); }
    }
    cout << endl;
    union {
        float inverted_x;
        int inverted_y = 0;
    };
    invMask = createNonInvertMask(sizeof(float) * 8);
    mask = 1 << sizeof(int) * 8 - 1;
    for (int i = 0; i < sizeof(float) * 8; i++) {
        inverted_y <<= 1;
        if (mask & invMask[i / (sizeof(ull) * 8)]) {
            putchar(mask & y ? '1' : '0'); 
            inverted_y += mask & y ? 1 : 0;
        }
        else { 
            putchar(mask & y ? '0' : '1'); 
            inverted_y += mask & y ? 0 : 1;
        }
        mask >>= 1;
        if (contains(i, arr)) { putchar(' '); }
    }
    cout << endl << inverted_x << endl;

    array<ull, 2> maskDB = { 1LL << (sizeof(ull) * 8 - 1), 1LL << (sizeof(ull) * 8 - 1)};
    union {
        long double d = 0;
        ull darr[2];
    };
    
    /*cout << arr << endl;
    cout << arr[0] << " " << arr[1] << endl;*/

    cout << "long double: ";
    cin >> d;
    cout << endl;

    for (int i = 0; i <= (sizeof(long double) * 8 - 1); i++) {
        int k = i / (sizeof(ull) * 8);
        putchar(maskDB[k] & darr[k] ? '1' : '0');
        maskDB[k] >>= 1;

        if (contains(i, arr)) { putchar(' '); }
    }
    cout << endl;
    union {
        long double inverted_d;
        ull inverted_darr0[2] = {0, 0};
    };
    array<ull, 2> inverted_darr = {0, 0};
    maskDB = { 1ull << (sizeof(ull) * 8 - 1), 1ull << (sizeof(ull) * 8 - 1) };
    invMask = createNonInvertMask(sizeof(long double) * 8);
    int lastI = 0;
    for (int i = 0; i < sizeof(long double) * 8; i++) {
        int k = i / (sizeof(ull) * 8);
        inverted_darr = moveBin(inverted_darr, 1);
        if (maskDB[k] & invMask[k]) {
            putchar(maskDB[k] & darr[k] ? '1' : '0');
            inverted_darr[1] += maskDB[k] & darr[k] ? 1 : 0;
        }
        else {
            putchar(maskDB[k] & darr[k] ? '0' : '1');
            inverted_darr[1] += maskDB[k] & darr[k] ? 0 : 1;
        }
        maskDB[k] >>= 1;
        if (contains(i, arr)) { putchar(' '); }
        lastI = i;
    }
    inverted_darr = moveBin(inverted_darr, 2*sizeof(ull) * 8 - lastI - 1);
    inverted_darr0[0] = inverted_darr[0];
    inverted_darr0[1] = inverted_darr[1];
    cout << endl << inverted_d << endl;
    cout << endl << endl << endl;
}