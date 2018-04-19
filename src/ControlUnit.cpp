#include <iostream>
#include "ControlUnit.hpp"

using namespace std;

void ControlUnit::run() {
    //return;
    //graph.print(true); return;
    //graph.printEdgeCounts(); return;
    //graph.printWithGraphTraversal(false); return;
    reductions.run();
    mis.print(graph.zeroDegreeNodes);
}

void ControlUnit::checkIndependentSet(const string &misInputFile) const {
    /* Build mis from input file */
    vector<uint32_t> mis;
    FILE *f;
    f = fopen(misInputFile.c_str(), "r");
    if (f == NULL) {
        cerr << "Error in opening MIS input file " << misInputFile << endl;
        exit(EXIT_FAILURE);
    }
    char buf[MAXLINE];
    if (fgets(buf, MAXLINE, f) == NULL) {
        cerr << "Error in parsing MIS input file " << misInputFile << endl;
        exit(EXIT_FAILURE);
    }
    while(fgets(buf, MAXLINE, f) != NULL) {
        uint32_t node = 0;
        for (uint32_t i = 0; buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n' ; i++) {
            node = node * 10 + (buf[i] - '0');
        }
        mis.push_back(node);
    }
    uint32_t node1, node2;
    bool independentSet = graph.isIndependentSet(mis, unordered_set<uint32_t>(), &node1, &node2);
    if (independentSet) {
        cout << "Valid independent set\n";
    } else {
        cout << "NOT an independent set!\nConflict between nodes " << node1 << " and " << node2 << endl;
    }
    fclose(f);
}
