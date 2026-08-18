#include "gd_driver.h"

using namespace std;

void runOne(const string& file) {
    GDInput input = readGDInput(file);

    auto start = chrono::high_resolution_clock::now();

    GDResult result = runGradientDescent(input);

    auto end = chrono::high_resolution_clock::now();

    double executionTime =
        chrono::duration<double, milli>(end - start).count();

    string outputFileName = createOutputFiles3(file, "gd");

    ofstream outputFile(outputFileName);

    outputFile << fixed << setprecision(6);
    outputFile << "Algorithm: Gradient Descent\n";
    outputFile << "Degree: " << result.degree << "\n";
    outputFile << "Final x: " << result.finalX << "\n";
    outputFile << "Final f(x): " << result.finalFx << "\n";
    outputFile << "Iterations: " << result.iterations << "\n";
    outputFile << "Converged: "
               << (result.converged ? "true" : "false") << "\n";
    outputFile << "Execution time: " << executionTime << " ms\n";

    outputFile.close();

    cout << "\nOutput File Generated: " << outputFileName << endl;
    cout << "Final x: " << result.finalX << endl;
    cout << "Final f(x): " << result.finalFx << endl;
    cout << "Iterations: " << result.iterations << endl;
    cout << "Converged: "
         << (result.converged ? "true" : "false") << endl;
    cout << "Execution Time: " << executionTime << " ms" << endl;
}

void gdDriver() {
    int choice = Menu::showInputMenu();

    if (choice == 1) {
        string file = chooseFiles("./assignment_03/tests/gd");
        runOne(file);
    }
    else if (choice == 2) {
        vector<string> files = getTestsFiles("./assignment_03/tests/gd");

        for (string file : files) {
            runOne(file);
        }
    }
    else if (choice == 3) {
        string file;

        cout << "Enter file path: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, file);

        runOne(file);
    }
    else if (choice == 0) {
        cout << "Go Back" << endl;
    }
    else {
        cout << "Invalid choice" << endl;
    }
}