#include "array.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"
#include "point.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main() {
    Array<shared_ptr<Figure<double>>> figures;
    
    cout << "=== Figure Program ===" << endl;
    cout << "Types: rhombus (r), pentagon (p), hexagon (h)" << endl;
    cout << "Commands: quit (q), delete (d), print (p), area (a)" << endl;
    cout << endl;
    
    char cmd;
    bool running = true;
    
    while (running) {
        cout << "Enter command: ";
        cin >> cmd;
        
        if (cmd == 'q') {
            running = false;
            cout << "Exiting..." << endl;
        }
        else if (cmd == 'p') {
            if (figures.size() == 0) {
                cout << "No figures in array" << endl;
            }
            else {
                for (size_t i = 0; i < figures.size(); ++i) {
                    cout << "Figure " << i << ":\n";
                    cout << "  " << *figures[i] << "\n";
                    
                    Point<double> center = figures[i]->geometricCenter();
                    cout << "  Geometric center: (" << center.x() << ", " << center.y() << ")\n";
                    
                    double area = figures[i]->area();
                    cout << "  Area: " << area << "\n\n";
                }
            }
        }
        else if (cmd == 'a') {
            double total = 0;
            for (size_t i = 0; i < figures.size(); ++i) {
                total += figures[i]->area();
            }
            cout << "Total area of all figures: " << total << endl;
        }
        else if (cmd == 'd') {
            if (figures.size() == 0) {
                cout << "Array is empty" << endl;
                continue;
            }
            
            size_t idx;
            cout << "Enter index to delete (0-" << figures.size()-1 << "): ";
            cin >> idx;
            
            if (idx < figures.size()) {
                figures.erase(idx);
                cout << "Figure " << idx << " deleted" << endl;
            }
            else {
                cout << "Invalid index!" << endl;
            }
        }
        else if (cmd == 'r' || cmd == 'p' || cmd == 'h') {
            shared_ptr<Figure<double>> newFig;
            
            if (cmd == 'r') {
                newFig = make_shared<Rhombus<double>>();
                cout << "Enter rhombus vertices (4 points x y): ";
            }
            else if (cmd == 'p') {
                newFig = make_shared<Pentagon<double>>();
                cout << "Enter pentagon vertices (5 points x y): ";
            }
            else if (cmd == 'h') {
                newFig = make_shared<Hexagon<double>>();
                cout << "Enter hexagon vertices (6 points x y): ";
            }
            
            try {
                cin >> *newFig;
                figures.push_back(move(newFig));
                cout << "Figure added! Total figures: " << figures.size() << endl;
            }
            catch (const exception& e) {
                cout << "Error reading figure: " << e.what() << endl;
                cin.clear();
                string temp;
                getline(cin, temp);
            }
        }
        else {
            cout << "Unknown command: " << cmd << endl;
            cout << "Available: r,p,h,p,a,d,q" << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}