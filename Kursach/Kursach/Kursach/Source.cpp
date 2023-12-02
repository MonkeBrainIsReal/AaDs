#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
//"C:\Users\83532\source\repos\MonkeBrainIsReal\AaDs\Kursach\Kursach\Kursach\test.txt"
//"C:\Users\Denis\source\repos\MonkeBrainIsReal\AaDs\Kursach\Kursach\Kursach\test.txt"


struct Edge {
    string vertex1;
    string vertex2;
    int weight;

    Edge(const string& v1, const string& v2, int w) : vertex1(v1), vertex2(v2), weight(w) {}
};

/
int main() {
    // Открываем файл
    ifstream inputFile("C:\\Users\\Denis\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt");
    if (!inputFile.is_open()) {
        cerr << "Unable to open the file." << endl;
        return 1;
    }

    

    return 0;
}