#include <iostream>
#include <set>

using namespace std;

int main() {
    int num_queries;
    cin >> num_queries;

   
    set<int> elements;

    for (int i = 0; i < num_queries; ++i) {
        int operation, value;
        cin >> operation >> value;

        switch (operation) {
            case 1:
                elements.insert(value);
                break;
            case 2:
                elements.erase(value);
                break;
            case 3:
                if (elements.find(value) != elements.end()) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
                break;
            default:
                cerr << "Invalid operation: " << operation << endl;
        }
    }

    return 0;
}