#include "maxflow_mincut.h"
#include <iostream>
#include <chrono>

void writeOuptuFile(MaxflowResult &result, double duration, string file){
    fs::create_directories("assignment_03/outputs");
    string outFile = "assignment_03/outputs/" + fs::path(file).stem().string()+ "_" + "out.txt";
    ofstream out(outFile);

    out<<"Algorithm: Maxflow-Mincut"<<endl;
    out<<"Source: "<<result.source<<endl;
    out<<"Sink: "<<result.sink<<endl;
    out<<"Maximum flow: "<<result.maxflow<<endl;
    out<<"Minimum cut capacity: "<<result.min_cut_cap<<endl;
    out<<"Source side: ";
    for(auto &v : result.sourceNode){
        out<<v<<" ";
    }
    out<<endl;
    out<<"Sink side: ";
    for(auto &u: result.sinkNode){
        out<<u<<" ";
    }
    out<<endl;

    out<<"Cut edges: "<<endl;
    for(auto edge:result.cutEdges){
        out<<edge.u<<" "<<edge.v<<" "<<edge.w<<endl;
    }
    out<<"Execution time: "<<duration<<" ms"<<endl<<endl;
    cout<<"output file generated: "<<outFile<<endl;
    cout<<"Execution time: "<<duration<<" ms"<<endl;
}

void maxflow_mincut_driver(){
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_03/tests/maxflow_mincut");
            AdjList g = readGraph(file);
            CSR csr = buildCSR(g);
            auto start = chrono::high_resolution_clock::now();
            MaxflowResult result = maxflow_mincut(g.source, g.sink, csr);
            auto end = chrono::high_resolution_clock::now();
            double executeTime = chrono::duration<double,milli>(end-start).count();

            writeOuptuFile(result,executeTime,file);
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_03/tests/maxflow_mincut");
            for(auto &file : files){
                AdjList g = readGraph(file);
                CSR csr = buildCSR(g);
                auto start = chrono::high_resolution_clock::now();
                MaxflowResult result = maxflow_mincut(g.source, g.sink, csr);
                auto end = chrono::high_resolution_clock::now();
                double executeTime = chrono::duration<double,milli>(end-start).count();

                writeOuptuFile(result,executeTime,file);
            }
            break;
        }
        case 3:{
            string path;
            cout << "\nEnter file path : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, path);
            AdjList g = readGraph(path);
            CSR csr = buildCSR(g);
            auto start = chrono::high_resolution_clock::now();
            MaxflowResult result = maxflow_mincut(g.source, g.sink, csr);
            auto end = chrono::high_resolution_clock::now();
            double executeTime = chrono::duration<double,milli>(end-start).count();

            writeOuptuFile(result,executeTime,path);
            break;
        }
        case 0:
            cout << "Go Back" << endl;
            return;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}