#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;



int main()
{
    string path;
    cout << "Specify the path to the file to write\n";
    getline(cin, path);
    ifstream fin(path, ios::binary);
    if (!fin) {
        cout << "File not found\n";
        return 1;
    }
    int N;
    fin >> N;
    double** matrix;
    matrix = new double* [N];
    for (int i = 0; i < N; i++)
        matrix[i] = new double[N];
    double* b = new double[N];
    double* x = new double[N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> matrix[i][j];
        }
        fin >> b[i];
        x[i] = 0;
    }

    int q; //нахождение не нулевого элемента
    int p;
    for (int j = 0; j < N; j++) {
        int k = 0;
        for (int i = 0; i < N; i++) {
            if (matrix[i][j] != 0) {
                p = i;
                q = j;
                k = 1;
                break;
            }
        }
        if (k == 1) {
            break;
        }
    }
    if (p != 0) {
        double temp;
        for (int j = 0; j < N; j++)
        {
            temp = matrix[1][j];
            matrix[1][j] = matrix[p][j];
            matrix[p][j] = temp;
        }

        temp = b[1];
        b[1] = b[p];
        b[p] = temp;
    }


    if (q != 0) {
        for (int i = 0; i < N; i++)
        {
            double temp = matrix[i][q];
            matrix[i][q] = matrix[i][0];
            matrix[i][0] = temp;
        }
    }


    for (int j = 0; j < N - 1; j++) { // прямой ход в методе Гаусса
        for (int i = j + 1; i < N; i++) {
            double r = -matrix[i][j] / matrix[j][j];
            for (int k = j; k < N; k++) {
                matrix[i][k] += r * matrix[j][k];
            }
            b[i] += r * b[j];
        }
    }

    double det = matrix[0][0]; // нахождение детерминанта
    for (int i = 1; i < N; i++) {
        det *= matrix[i][i];
    }
    cout << "Детерминант равен " << det << endl;
    if (det == 0) {
        for (int i = 0; i < N; i++) {
            int sum = 0;
            for (int j = 0; j < N; j++) {
                if (matrix[i][j] == 0) {
                    sum++;
                }
                if ((sum == N - 1) && (b[i] != 0)) {
                    cout << "Cистема не совместна" << endl;
                    return 0;
                }
            }
        }
        cout << "Система имеет бесконечное количество решений" << endl;
        return 0;
    }

    for (int i = N - 1; i >= 0; i--) { // обратный ход в методе Гаусса
        double r = 0;
        for (int j = i + 1; j < N; j++)
        {
            r += matrix[i][j] * x[j];
        }
        x[i] = (b[i] - r) / matrix[i][i];
    }

    cout << "Ответ = " << endl;
    for (int i = 0; i < N; i++) {
        cout << x[i] << endl;
    }
    
    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] b;
    b = nullptr;
    delete[] x;
    x = nullptr;
    return 0;
}