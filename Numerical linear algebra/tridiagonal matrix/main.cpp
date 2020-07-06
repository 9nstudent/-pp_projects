#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

double mod(double a) {
    if (a < 0) {
        a = -a;
    }
    return a;
}

int main() {
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

    int sum1 = 0; // проверка на то, подходит ли нам матрица
    int sum2 = 0;
    for (int i = 1; i < N - 1; i++) {
        double sum = mod(matrix[i][i - 1]) + mod(matrix[i][i + 1]);
        double modul = mod(matrix[i][i]);
        if (modul > sum) {
            sum1++;
            sum2++;
        }
        else {
            if (modul == sum) {
                sum2++;
            }
        }
    }

    if ((matrix[0][0] < matrix[0][1]) || (matrix[N - 1][N - 2] > matrix[N - 1][N - 1]) || (sum1 == 0) || (sum2 == 0)) {
        cout << "Матрица не подходит для использования данного метода" << endl;
        return 0;
    }

    double det = matrix[0][0]; 
    double** detA;
    detA = new double* [N];
    for (int i = 0; i < N; i++)
        detA[i] = new double[N];
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            detA[i][j] = matrix[i][j];
        }
        if (i == 1) {
            double temp = detA[1][0] / matrix[0][0];
            //detA[1][0] = 0;
            detA[1][1] -= temp * matrix[0][1];
        }
        double temp = detA[i][i - 1] / detA[i - 1][i - 1];
        //detA[i][i-1] = 0;
        detA[i][i] -= temp * detA[i - 1][i];
        det *= detA[i][i];
    }
    for (int i = 0; i < N; i++)
        delete[] detA[i];
    delete[] detA;
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

    double y = matrix[0][0]; // прямой ход
    double* matA = new double[N];
    matA[0] = -matrix[0][1] / y;
    double* matB = new double[N];
    matB[0] = b[0] / y;
    for (int i = 1; i < N - 1; i++) {
        y = matrix[i][i] + matrix[i][i - 1] * matA[i - 1];
        matA[i] = -matrix[i][i + 1] / y;
        matB[i] = (b[i] - matrix[i][i - 1] * matB[i - 1]) / y;
    }

    x[N - 1] = (b[N - 1] - matrix[N - 1][N - 2] * matB[N - 2]) / (matrix[N - 1][N - 1] + matrix[N - 1][N - 2] * matA[N - 2]); // обратный ход
    for (int i = N - 2; i >= 0; i--) {
        x[i] = matA[i] * x[i + 1] + matB[i];
    }
    delete[] matA;
    matA = nullptr;
    delete[] matB;
    matB = nullptr;

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
