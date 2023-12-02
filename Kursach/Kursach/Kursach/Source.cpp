#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
//"C:\Users\83532\source\repos\MonkeBrainIsReal\AaDs\Kursach\Kursach\Kursach\test.txt"


struct Edge 
{
    Edge(char s, char d, int w) : source(s), destination(d), weight(w) {};
    char source;
    char destination;
    int weight;

   
   
};




int main() 
{
    ifstream inputFile("C:\\Users\\83532\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt");
    
    return 0;
}