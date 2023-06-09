/** @file Waiting_Area.cc
    @brief Implementation of the class Waiting_Area
*/

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include "Waiting_Area.hh"
#endif

#include "Cluster.hh"
using namespace std;

//Typedefs to code faster, keep lines shorter and to make it more readable
typedef map<string, list<Process>> area;
typedef map<string, list<Process>>::iterator area_it;
typedef map<string, list<Process>>::const_iterator area_ct;

typedef list<Process> cat;
typedef list<Process>::iterator cat_it;
typedef list<Process>::const_iterator cat_ct;

typedef map<string, pair<int, int>> siu;
typedef map<string, pair<int, int>>::iterator siu_it;
typedef map<string, pair<int, int>>::const_iterator siu_ct;

void Waiting_Area::epc(int n, Cluster& clust) {
    area_it it = wa.begin();
    area_it itf = wa.end();
    int i = 0;

    while (i < n and it != itf) {
        cat_it it2 = it->second.begin();
        siu_it cat = sera.find(it->first);

        int tam, j;
        tam = it->second.size();
        j = 0;

        while (i < n and j < tam) {
            cat_it its = it2;
            Process a = *it2;
            ++its;
            
            if (clust.recive_processes(a)) {
                ++i;
                cat->second.first += 1;
                it->second.erase(it2);
            }
            else {
                it->second.erase(it2);
                it->second.insert(it->second.end(), a);
                cat->second.second += 1;
            }
            it2 = its;
            ++j;
        }

        ++it;
    }
}

bool Waiting_Area::search_process(area_ct it, int proc_id) const {
    cat_ct ite = it->second.end();

    for (cat_ct it2 = it->second.begin(); it2 != ite; ++it2) {
        if (it2->what_id() == proc_id) return true;
    }

    return false;
}

void Waiting_Area::read_waiting_area() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string prio;
        list<Process> a;
        pair<int, int> b(0, 0);

        cin >> prio;
        wa.insert(make_pair(prio, a));
        sera.insert(make_pair(prio, b));
    }   
}

void Waiting_Area::add_process(const string& prio, const Process& a) {
    area_it it = wa.find(prio);
    cat_it it2 = it->second.end();
    it->second.insert(it2, a);
}

bool Waiting_Area::ap(const string& x) {
    area_it it = wa.find(x);

    if (it != wa.end()) return false;

    cat a;
    wa.insert(make_pair(x, a));
    sera.insert(make_pair(x, make_pair(0, 0)));
    return true;
}

int Waiting_Area::bp(const string& x) {
    area::iterator it = wa.find(x);

    if (it == wa.end()) return 101;
    if (!(it->second.empty())) return 102;

    sera.erase(x);
    wa.erase(it);
    return 100;
}

int Waiting_Area::ape(const string& x, int identity, int memory, int time) {
    area::iterator it = wa.find(x);

    if (it == wa.end()) return 101;
    else if (search_process(it, identity)) return 102;

    add_process(x, Process(identity, memory, time, 0));
    return 100;
} 

bool Waiting_Area::ipri(const string& x) const {
    area_ct it = wa.find(x);

    if (it == wa.end()) return false;
    else {
        cat_ct ite = it->second.end();
    
        for(cat_ct it2 = it->second.begin(); it2 != ite; ++it2) {
            it2->wr2_process();
        }

        siu_ct ita = sera.find(x);
        cout << ita->second.first << " " << ita->second.second << endl;
    }

    return true;
}

void Waiting_Area::iae() const {
    area_ct it2 = wa.end();

    for (area_ct it = wa.begin(); it != it2; ++it) {
        string name = it->first;
        cout << name << endl;
        cat_ct itf2 = it->second.end();

        for (cat_ct itf = it->second.begin(); itf != itf2; ++itf) {
            itf->wr2_process();
        }

        siu_ct its = sera.find(name);
        cout << its->second.first << " " << its->second.second << endl;
    }
}

Waiting_Area::Waiting_Area() {}