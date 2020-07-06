#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

double euclidean_norm(int N, double *v)
{
    double sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}


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

    double t;
    cout << "Введите значение параметра" << endl;
    cin >> t;

    double epsilon = 0.01;

    double ratio = epsilon + 1; // ставим число заведомо больше эпсилон
    int count = 0;
    double* vector = new double[N];
    double* last_vector = new double[N];
    while (ratio >= epsilon) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                vector[i] += matrix[i][j] * x[i];
            }
            vector[i] -= b[i];
            last_vector[i] = x[i];
        }
        for (int i = 0; i < N; i++) {
            x[i] -= t * vector[i];
            last_vector[i] -= x[i];
        }
        ratio = euclidean_norm(N, last_vector);
        count++;
    }
    delete[] vector;
    vector = nullptr;
    delete[] last_vector;
    last_vector = nullptr;

    cout << "Ответ = " << endl;
    for (int i = 0; i < N; i++) {
        cout << x[i] << endl;
    }
    cout << "Количество итераций = " << count << endl;

    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] b;
    b = nullptr;
    delete[] x;
    x = nullptr;
    return 0;
}
