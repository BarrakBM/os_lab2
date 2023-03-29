//Barrak Mandani
//Due 3/27/2023

/*
    1.FCFS
    2.SRTF
    3.RR
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

int main(int argc, char* argv[]) {

    //check the argument
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " input_file algorithm" << endl;
        return 1;
    }
    //store the argument
    string input_file = argv[1];
    string algorithm = argv[2];

    //check the file
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "Error: could not open input file" << endl;
        return 1;
    }

    vector<process> processes;

    // store the values into vector
    string line;
    process p;
    while (getline(file, line)) {
        
        istringstream iss(line);
        if (!(iss >> p.pid >> p.arrival_time >> p.burst_time)) {
            cout << "Error: invalid input file format" << endl;
            return 1;
        }
        p.remaining_time = p.burst_time;
        processes.push_back(p);
    }

    file.close();


    /*

        1. FCFS

    */

    if (algorithm == "FCFS") {
        cout << endl;
        cout << " ************************************************************" << endl;
        cout << " ************ Scheduling algorithm : FCFS *******************" << endl;
        cout << " ************************************************************ "<< endl;
        cout << endl;

        // calculation
        int time;
        time = 0;
        int context = 0;
        //create a table
        cout << setw(10) << "Pid" << setw(15) << "arrival" << setw(15) << "finish" << setw(15) << "waiting time" << setw(15) << "turn around" << setw(15) << "NO.context" <<  endl;
        for (int i = 0; i < processes.size(); i++){

            //waiting time
            int waiting_time = time - processes[i].arrival_time;
            //update the time 
            time += processes[i].burst_time;
            //finish time 
            int finish_time = time;
            //turn around time
            int turn_around_time = finish_time - processes[i].arrival_time;

            cout << setw(10) << processes[i].pid << setw(15) << processes[i].arrival_time << setw(15) << finish_time << setw(15) << waiting_time << setw(15) << turn_around_time << setw(15) << context <<  endl;
            
        }



    }

    return 0;
}
