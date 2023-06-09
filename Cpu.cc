/** @file Cpu.cc
    @brief Implementation of the class Cpu
*/

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <set>
#include "Cpu.hh"
#endif

#include "Process.hh"
using namespace std;

//Typedefs to code faster, keep lines shorter and to make it more readable
typedef map<int, Process> mem;
typedef map<int, Process>::iterator mem_it;
typedef map<int, Process>::const_iterator mem_ct;

typedef map<int, set<int>> dir;
typedef map<int, set<int>>::iterator dir_it;
typedef map<int, set<int>>::const_iterator dir_ct;

typedef map<int, pair<int,int>> naio;
typedef map<int, pair<int,int>>::iterator naio_it;
typedef map<int, pair<int,int>>::const_iterator naio_ct;

Cpu::Cpu(int n) {
    mema = max = n;
    ffree = 0;
    es.emplace(n, set<int>{0});
}

int Cpu::remove_process_cpu(int proc_id, int& back) {
    mem_ct it = prl.find(proc_id);
    if (it == prl.end()) return 102;

    //new_dir -> the new direction of free memory once checked if there is
    //empty space before and after the removed process
    //new_tam -> the new free space of that direction
    int a, b, new_tam, new_dir;
    a = new_tam = it->second.what_mem();
    b = new_dir = it->second.what_dir();
    max += a;

    //ffree -> if the direction is smaller than ffree we update it
    //ffree (the first direction of free memory of the cpu)
    if (b < ffree) ffree = b;
    naio_it itf = diro.find(b);

    //to check it, we take the direction and the size of the process before
    //we add the together and check if it's equal to the direction of the
    //process, if not, it means we have empty space
    if (itf != diro.begin()) {
        naio_it ita = itf;
        --ita;

        int c, d;
        c = ita->first;
        d = ita->second.second;

        if (c + d != b) {
            new_tam = new_tam + (b - c - d);
            new_dir = c + d;
            update_set_and_erase(c + d, b - c - d);
        }
    }
    else if (b != 0) {
        new_dir = 0;
        new_tam = new_tam + b;
        update_set_and_erase(0, b);
    }

    //the same but with the space in front of the process
    if (++itf != diro.end()) {
        int e;
        e = itf->first;

        if (a + b != e) {
            new_tam = new_tam + e - a - b;
            update_set_and_erase(a + b, e - a - b);
        }
    }
    else if (a + b != mema) {
        new_tam = new_tam + (mema - a - b);
        update_set_and_erase(a + b, mema - a - b);
    }

    insert_set(new_tam, new_dir);
    back = new_tam; //back it's only used when we are compacting the memory
    diro.erase(b);
    prl.erase(proc_id);

    return 100;
}

int Cpu::add_process_cpu(int identity, int memory, int time) {
    mem_ct it = prl.find(identity);
    if (it != prl.end()) return 102;

    dir_it it2 = es.lower_bound(memory);
    if (it2 == es.end()) return 103;

    max -= memory;
    int direction = *(--(it2->second.end()));
    int mem_ava = it2->first;
    it2->second.erase(direction);

    bool need_check = true; //used to know if we need to check ffree later

    if (mem_ava > memory) {
        if (direction == ffree) {
            need_check = false;
            ffree = memory + direction;
        }
        es[mem_ava - memory].insert(memory + direction);
    }

    //We add the process with its id to out map of <id, Process>
    //We also add the process to the map of used directions
    //<direction, <id, size>>
    prl.emplace(identity, Process (identity, memory, time, direction));
    diro.emplace(direction, make_pair(identity, memory));

    if (it2->second.empty()) es.erase(it2);

    if (need_check and direction == ffree) {
        naio_it itc = diro.upper_bound(direction);
        if (itc == diro.end()) {
            if (direction + memory == mema) ffree = mema + 1;
            else ffree = direction + memory;
        }
        else ffree = check_ffree(itc->first, itc->second.second, itc);
    }
    return 100;
}

void Cpu::relocate(int proc_id, int mem, int time, int back) {
    //this function that does the same as add_process_cpu() but here we know
    //from before where are we going to put the process, ffree and the size
    //we are going to use (back), even if we don't use all of the space
    max -= mem;
    int direction = ffree;
    dir_it it2 = es.find(back);
    it2->second.erase(ffree);

    bool need_check = true;

    if (back > mem) {
        if (direction == ffree) {
            need_check = false;
            ffree = mem + direction;
        }
        es[back - mem].insert(mem + direction);
    }

    prl.emplace(proc_id, Process (proc_id, mem, time, direction));
    diro.emplace(direction, make_pair(proc_id, mem));

    if (it2->second.empty()) es.erase(it2);

    if (need_check and direction == ffree) {
        naio_it itc = diro.upper_bound(direction);
        if (itc == diro.end()) {
            if (direction + mem == mema) ffree = mema + 1;
            else ffree = direction + mem;
        }
        else ffree = check_ffree(itc->first, itc->second.second, itc);
    }
}

void Cpu::compactar() {
    naio_it itf = diro.end();
    naio_it it = diro.upper_bound(ffree);
    
    while (it != itf) {
        int proc_id = it->second.first;
        int mem = it->second.second;
        int back = 0;
        mem_it it2 = prl.find(proc_id);
        int time = it2->second.what_time();

        ++it;
        remove_process_cpu(proc_id, back);
        relocate(proc_id, mem, time, back);
    }
}

void Cpu::advance(int delta) {
    mem_it it2 = prl.end();
    mem_it it = prl.begin();
    int back = 0;

    while (it != it2) {
        if (!(it->second.reducing(delta))) {
            mem_it aux = it;
            ++aux;
            remove_process_cpu(it->second.what_id(), back);
            it = aux;
        }
        else ++it;
    } 
}

int Cpu::check_ffree(const int direction, const int tam, naio_it& it) {
    int aux = direction + tam;
    ++it;
    if (it == diro.end()) {
        if (aux == mema) return mema + 1;
        else return aux;
    }
    else {
        int newd = it->first;
        int newt = it->second.second;

        if (aux != newd) return aux;
        else return check_ffree(newd, newt, it);
    }
}

void Cpu::insert_set(int value, int key) {
    dir_it ite = es.find(value);

    if (ite != es.end()) ite->second.insert(key);
    else {
        set<int> z;
        z.insert(key);
        es.insert(make_pair(value, z));
    }
}

void Cpu::write_cpu() const {
    naio_ct itf = diro.end();

    for (naio_ct it = diro.begin(); it != itf; ++it) {
        int a = it->second.first;
        mem_ct ita = prl.find(a);
        ita->second.wr_process();
    }
}

int Cpu::get_memory(int mem, int identity) const {
    dir_ct it2 = es.lower_bound(mem);
    mem_ct it = prl.find(identity);

    if (it != prl.end()) return -1;
    if (it2 == es.end()) return -1;
    return it2->first;
}

void Cpu:: update_set_and_erase(int diff, int key) {
    dir_it ite = es.find(key);
    ite->second.erase(diff);

    if (ite->second.empty()) es.erase(ite);
}

bool Cpu::active_processes() const {
    return diro.empty();
}

int Cpu::space_left() const {
    return max;
}

int Cpu::what_ffree() const {
    return ffree;
}

void Cpu::is_leaf() {
    leaf = true;
}

bool Cpu::yn_leaf() const {
    return leaf;
}

int Cpu::what_mema() const {
    return mema;
}

int Cpu::how_many() const {
    return prl.size();
}