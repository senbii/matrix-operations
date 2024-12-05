#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> inputMatrix(int &rows, int &cols) {
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));
    cout << "Enter the elements row by row:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

void displayMatrix(const vector<vector<int>> &matrix) {
    for (const auto &row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> addMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int rows = A.size(), cols = A[0].size();
    vector<vector<int>> result(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

vector<vector<int>> subtractMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int rows = A.size(), cols = A[0].size();
    vector<vector<int>> result(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int rows = A.size(), cols = B[0].size(), common = A[0].size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < common; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

vector<vector<int>> transposeMatrix(const vector<vector<int>> &matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> result(cols, vector<int>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

vector<vector<int>> readMatrixFromFile(const string &filename, int &rows, int &cols) {
    ifstream inFile(filename, ios::in);
    vector<vector<int>> matrix;

    if (inFile.is_open()) {
        inFile >> rows >> cols;
        matrix.resize(rows, vector<int>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                inFile >> matrix[i][j];
            }
        }

        inFile.close();
        cout << "Matrix successfully read from " << filename << endl;
    } else {
        cout << "Error: Could not open file " << filename << endl;
    }

    return matrix;
}

void saveMatrixToFile(const vector<vector<int>> &matrix, const string &filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto &row : matrix) {
            for (int element : row) {
                outFile << element << " ";
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Matrix saved to " << filename << endl;
    } else {
        cout << "Error: Could not open file " << filename << endl;
    }
}

void menu() {
    int choice;
    vector<vector<int>> A, B, result;
    int rowsA, colsA, rowsB, colsB;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Matrix Addition\n";
        cout << "2. Matrix Subtraction\n";
        cout << "3. Matrix Multiplication\n";
        cout << "4. Matrix Transposition\n";
        cout << "5. Input Matrix from File\n";
        cout << "6. Save Result to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Input Matrix A:\n";
                A = inputMatrix(rowsA, colsA);
                cout << "Input Matrix B:\n";
                B = inputMatrix(rowsB, colsB);
                if (rowsA == rowsB && colsA == colsB) {
                    result = addMatrices(A, B);
                    cout << "Result:\n";
                    displayMatrix(result);
                } else {
                    cout << "Error: Matrices must have the same dimensions for addition.\n";
                }
                break;

            case 2:
                cout << "Input Matrix A:\n";
                A = inputMatrix(rowsA, colsA);
                cout << "Input Matrix B:\n";
                B = inputMatrix(rowsB, colsB);
                if (rowsA == rowsB && colsA == colsB) {
                    result = subtractMatrices(A, B);
                    cout << "Result:\n";
                    displayMatrix(result);
                } else {
                    cout << "Error: Matrices must have the same dimensions for subtraction.\n";
                }
                break;

            case 3:
                cout << "Input Matrix A:\n";
                A = inputMatrix(rowsA, colsA);
                cout << "Input Matrix B:\n";
                B = inputMatrix(rowsB, colsB);
                if (colsA == rowsB) {
                    result = multiplyMatrices(A, B);
                    cout << "Result:\n";
                    displayMatrix(result);
                } else {
                    cout << "Error: Number of columns in Matrix A must equal number of rows in Matrix B for multiplication.\n";
                }
                break;

            case 4:
                cout << "Input Matrix:\n";
                A = inputMatrix(rowsA, colsA);
                result = transposeMatrix(A);
                cout << "Transpose:\n";
                displayMatrix(result);
                break;

            case 5:
                cout << "Enter filename to input matrix A: \n";
                {
                    string filename;
                    cin >> filename;
                    A = readMatrixFromFile(filename, rowsA, colsA);

                    cout << "Enter filename to input matrix B: \n";
                    cin >> filename;
                    B = readMatrixFromFile(filename, rowsB, colsB);
                }
                break;

            case 6:
                cout << "Enter filename to save the result: \n";
                {
                    string filename;
                    cin >> filename;
                    saveMatrixToFile(result, filename);
                }
                break;

            case 7:
                cout << "Exiting program. Goodbye!\n";
                return;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
