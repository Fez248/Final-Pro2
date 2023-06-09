/** @file Process.cc
    @brief Implementation of the class Process
*/

#ifndef NO_DIAGRAM
#include <iostream>
#endif

#include "Process.hh"
using namespace std;

Process::Process(int identity, int memory, int delta, int direction) {
    ide = identity;
    memo = memory;
    time = delta;
    dir = direction;
}

bool Process::reducing(int t) {
    time = time - t;
    return time > 0;
}

int Process::what_id() const {
    return ide;
}

int Process::what_mem() const {
    return memo;
}

int Process::what_time() const {
    return time;
}

void Process::wr_process() const {
    cout << dir << " " << ide << " " << memo << " " << time << endl;
}

void Process::wr2_process() const {
    cout << ide << " " << memo << " " << time << endl;
}

int Process::what_dir() const {
    return dir;
}



