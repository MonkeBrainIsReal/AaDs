#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
//"C:\\Users\\83532\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt"
//"C:\\Users\\Denis\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt"



struct edge {
    char start;
    char destination;
    int weight;
    edge(char S, char D, int W) : start(S), destination(D), weight(W) {};
};

void SortEdges(vector<edge>& edges) {
    for (int i = 1; i < edges.size(); ++i) {
        edge key = edges[i];
        int j = i - 1;

        while (j >= 0) {
            // Сравнение наименований вершин в лексикографическом порядке
            if (key.start < edges[j].start || (key.start == edges[j].start && key.destination < edges[j].destination)) {
                edges[j + 1] = edges[j];
                --j;
            }
            else {
                break;
            }
        }

        edges[j + 1] = key;
    }
}



void depthFirstTraversal(vector<edge>& edges) {
    for (const edge& edge : edges) {
        cout << edge.start << " " << edge.destination << " : " << edge.weight << endl;
    }
}



void DeleteDupes(vector<edge>& edges) {
    vector<edge>Unique;
    for (size_t i = 0; i < edges.size(); ++i) {
        bool isDuplicate = false;

        // Проверяем, есть ли дубликат текущего элемента в Unique
        for (size_t j = 0; j < Unique.size(); ++j) {
            if (edges[i].start == Unique[j].start && edges[i].destination == Unique[j].destination) {
                isDuplicate = true;
                break;
            }
        }

        // Если текущий элемент не является дубликатом, добавляем его в Unique
        if (!isDuplicate) {
            Unique.push_back(edges[i]);
        }
    }

    edges = Unique;
}



int main() {
    ifstream inputFile("C:\\Users\\83532\\source\\repos\\MonkeBrainIsReal\\AaDs\\Kursach\\Kursach\\Kursach\\test.txt");
    if (!inputFile.is_open()) {
        cerr << "Unable to open the file." << endl;
        return 1;
    }
    vector<edge> edges;
    string verticesLine;
    getline(inputFile, verticesLine); // Считываем первую строку с вершинами

    char start;
    while (inputFile >> start) {
        char destination;
        for (int colIndex = 0; inputFile >> destination; ++colIndex) 
        {
            int weight;
            inputFile >> weight;
            if (weight > 0 && start < destination) 
            {
                edges.push_back(edge(start, destination, weight));
            }
        }
    }

    inputFile.close();

    SortEdges(edges);

    DeleteDupes(edges);

    depthFirstTraversal(edges);

    return 0;
}