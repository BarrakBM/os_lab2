// Barrak Mandani
// Due 3/27/2023

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
#include <bits/stdc++.h>
#include <queue>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int finish_time;
    int waiting_time;
    int turn_around_time;
    int remaining_time;
    int context = 0;
};
// vector of type process(struct)
vector<process> processes;

void FCFS();
void SRTF();

int main(int argc, char *argv[])
{

    // check the argument
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " input_file algorithm"
             << " quantumsize" << endl;
        return 1;
    }
    // store the argument
    string input_file = argv[1];
    string algorithm = argv[2];
    // int quantum = stoi(argv[3]);
    // check the file
    ifstream file(input_file);
    if (!file.is_open())
    {
        cout << "Error: could not open input file" << endl;
        return 1;
    }

    // store the values into vector
    string line;
    // create p of type process
    process p;
    while (getline(file, line))
    {

        istringstream iss(line);
        if (!(iss >> p.pid >> p.arrival_time >> p.burst_time))
        {
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

    if (algorithm == "FCFS")
    {

        FCFS();
    }

    /*

        2. SRTF

    */

    if (algorithm == "SRTF")
    {
        SRTF();
    }

    return 0;
}

void FCFS()
{
    cout << endl;
    cout << " ************************************************************" << endl;
    cout << " ************ Scheduling algorithm : FCFS *******************" << endl;
    cout << " ************************************************************ " << endl;
    cout << endl;

    // calculation
    int time;
    time = 0;
    int context = 0;
    int turn_around_time;
    int waiting_time;
    // create a table
    cout << setw(10) << "Pid" << setw(15) << "arrival" << setw(15) << "CPU-burst" << setw(15) << "finish" << setw(15) << "waiting time" << setw(15) << "turn around" << setw(15) << "NO.context" << endl;
    for (int i = 0; i < processes.size(); i++)
    {

        // waiting time
        processes[i].waiting_time = time - processes[i].arrival_time;
        // update the time
        time += processes[i].burst_time;
        // finish time
        processes[i].finish_time = time;
        // turn around time
        processes[i].turn_around_time = processes[i].finish_time - processes[i].arrival_time;

        cout << setw(10) << processes[i].pid << setw(15) << processes[i].arrival_time << setw(15) << processes[i].burst_time << setw(15) << processes[i].finish_time << setw(15) << processes[i].waiting_time << setw(15) << processes[i].turn_around_time << setw(15) << context << endl;
    }

    float total_burst = 0;
    float total_wait = 0;
    float total_tt = 0;
    int total_context = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        total_burst += processes[i].burst_time;
        total_wait += processes[i].waiting_time;
        total_tt += processes[i].turn_around_time;
        total_context += processes[i].context;
    }

    float avg_burst = total_burst / processes.size();
    float avg_wait = total_wait / processes.size();
    float avg_tt = total_tt / processes.size();
    cout << "Average CPU burst time = " << avg_burst << " ms" << endl;
    cout << "Average waiting time = " << avg_wait << " ms" << endl;
    cout << "Average turn around time = " << avg_tt << " ms" << endl;
    cout << "Total No. of Context Switching Performed = " << total_context << endl;
    cout << endl;
}

void SRTF()
{
    for (int i = 0; i < processes.size(); i ++){
        processes[i].context = 0;
    }
    cout << endl;
    cout << " ************************************************************" << endl;
    cout << " ************ Scheduling algorithm : SRTF *******************" << endl;
    cout << " ************************************************************ " << endl;
    cout << endl;

    int time = 0;
    int done = 0;
    int current_process = -1;
    int context_switches = 0;

    // create a table
    cout << setw(10) << "Pid" << setw(15) << "arrival" << setw(15) << "CPU-burst" << setw(15) << "finish" << setw(15) << "waiting time" << setw(15) << "turn around" << setw(15) << "NO.context" << endl;

    // run the loop till all process are done
    while (done != processes.size())
    {
        int next_process = -1;
        int min_remaining_time = INT_MAX;

        // find the process with minimum remaining time
        for (int j = 0; j < processes.size(); j++)
        {
            if (processes[j].arrival_time <= time && processes[j].remaining_time < min_remaining_time && processes[j].remaining_time > 0)
            {
                next_process = j;
                min_remaining_time = processes[j].remaining_time;
            }
        }

        // if a new process has been selected
        if (next_process != -1 && next_process != current_process)
        {
            // context switch occurred
            context_switches++;
            if (current_process != -1)
            {
                processes[current_process].context++;
            }
            current_process = next_process;
        }

        // decrement the remaining time of the current process
        if (current_process != -1)
        {
            processes[current_process].remaining_time--;
            if (processes[current_process].remaining_time == 0)
            {
                // process gets completely executed
                done++;

                // finish time of finished process
                int finish_time = time + 1;
                processes[current_process].finish_time = finish_time;

                // calculate waiting and turnaround times
                processes[current_process].waiting_time = finish_time - processes[current_process].burst_time - processes[current_process].arrival_time;
                if (processes[current_process].waiting_time < 0)
                {
                    processes[current_process].waiting_time = 0;
                }
                processes[current_process].turn_around_time = processes[current_process].waiting_time + processes[current_process].burst_time;

                // select the next process
                current_process = -1;
            }
        }

        time++;
    }

    // print the table with process details
    for (int i = 0; i < processes.size(); i++)
    {
        cout << setw(10) << processes[i].pid << setw(15) << processes[i].arrival_time << setw(15) << processes[i].burst_time << setw(15) << processes[i].finish_time << setw(15) << processes[i].waiting_time << setw(15) << processes[i].turn_around_time << setw(15) << processes[i].context << endl;
    }

    // calculate and print the average waiting and turnaround times
    float total_burst = 0;
    float total_wait = 0;
    float total_tt = 0;
    int total_context;
    for (int i = 0; i < processes.size(); i++)
    {
        total_burst += processes[i].burst_time;
        total_wait += processes[i].waiting_time;
        total_tt += processes[i].turn_around_time;
        total_context += processes[i].context;
    }

    float avg_burst = total_burst / processes.size();
    float avg_wait = total_wait / processes.size();
    float avg_tt = total_tt / processes.size();
    cout << "Average CPU burst time = " << avg_burst << " ms" << endl;
    cout << "Average waiting time = " << avg_wait << " ms" << endl;
    cout << "Average turn around time = " << avg_tt << " ms" << endl;
    cout << "Total No. of Context Switching Performed = " << total_context  << endl;
    cout << endl;

}