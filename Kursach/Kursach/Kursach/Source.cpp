#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
//"C:\Users\83532\source\repos\MonkeBrainIsReal\AaDs\Kursach\Kursach\Kursach\test.txt"
//"C:\\Users\\Denis\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt"

void readGraph(const string& filePath, vector<string>& edges, vector<vector<int>>& matrix) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line);
    istringstream edgeStream(line);
    string edge;
    while (edgeStream >> edge) {
        edges.push_back(edge);
    }

    while (getline(file, line)) {
        istringstream matrixStream(line);
        vector<int> row;
        int value;
        while (matrixStream >> value) {
            row.push_back(value);
        }
        matrix.push_back(row);
    }

    file.close();
}



int main() {
    string filePath = "C:\\Users\\Denis\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt";
    vector<string> edges;
    vector<vector<int>> matrix;

    readGraph(filePath, edges, matrix);


    return 0;
}