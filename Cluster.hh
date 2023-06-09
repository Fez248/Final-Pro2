/** @file Cluster.hh
    @brief Especification of the class Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Cpu.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#endif

typedef map<string, Cpu> clus;
typedef const BinTree<string>& ord_ct;
typedef clus::iterator& cit;

/**
    @class Cluster
    @brief It represents a cluster

    The cluster is a binary tree where his components are processors, cpus.
    It needs to have at least one cpu.
*/

class Cluster {
    private:
    BinTree<string> cluster; //BinTree with the id of cpus to keep order
    map<string, Cpu> conj; //Map with the id and the cpus to access them

    /**
        @brief Reads a cluster and sets the leaf value of the processors.

        \pre The new cluster ready to be read on the console.
        \post Returns true if the node that it's reading it's empty.
    */
    bool read_bintree(BinTree<string>& cluster);

    /**
        @brief Prints the cluster.

        \pre <em>True</em>.
        \post The cluster has been printed.
    */
    void write_bintree(const BinTree<string>& cluster) const;

    /**
        @brief Modifies the cluster from a node p, if the node it's reading 
        it is not p it continues reading, when p is found it calls
        read_bintree() and the new cluster is inserted in its' position.

        \pre The new cluster ready to be read on the console, a initialized
        and guaranteed that p exists, it doesn't have processes and it's
        a leaf of the tree and p initialized.
        \post The new cluster a contains the old cluster and the new one in
        the position of p.
    */
    void reread(BinTree<string>& a, string p);

    void cut(BinTree<string>& a, const string& p, int& num_cpu, int& num_pro);

    /**
        @brief Finds the best cpu to insert the process with memory = mem
        and id = identity. It returns an iterator pointing to the best option,
        if it doesn't fit in any cpu it returns an iterator pointing to end().

        \pre mem, identity, ite and can initialized.
        \post ite points to the best cpu to add the process.
    */
    void find_best(const int mem, const int identity, cit ite, ord_ct can);

    void counting(BinTree<string>& a, int& num_cpu, int& num_pro);

    public:

    /**
        @brief Default creator.

        \pre <em>True</em>.
        \post An empty cluster.
    */
    Cluster();

    /**
        @brief Clears the map of cpus and reads a new BinTree

        \pre <em>True</em>.
        \post A new cluster. The older one it's erased.
    */
    void read();

    /**
        @brief Checks the errors that can happen when modifing the cluster, 
        erases x from the map and calls reread().

        \pre Initialized x.
        \post If the cpu doesn't exist, it returns 101, if it has any active 
        process it returns 102 and if it has auxiliary cpus it returns 103. 
        If not, it calls reread() and returns 100.
    */
    int mc(string x);

    /**
        @brief Takes the id of a cpu, and the values of a process, checks
        the errors, and if everything goes right it adds the process to the
        cpu.

        \pre All variables initialized.
        \post If the cpu doesn't exist, it returns 101, if not it calls
        add_process_cpu and returns the value this function returns,
        indicating if the process has been successful or not. If so,
        the process has been added.
    */
    int app(const string& x, int identity, int memmory, int time);

    /**
        @brief Takes a cpu id (x) and the identity of a process
        (identity). If the cpu exists and the process too, it removes
        it from the cpu.

        \pre A process and a cpu id initialized.
        \post If the cpu doesn't exist, it returns 101, if it does
        exist, it calls remove_process_cpu() which removes the process and
        returns the a number indicating if the operation has been completed.
    */
    int bpp(const string& x, int identity);

    /**
        @brief Makes time pass by.

        \pre A number t >= 0.
        \post The time has been advanced in t unities.
    */
    void at(int t);

    /**
        @brief Finds a cpu in the cluster and prints its processes.

        \pre Initialized x.
        \post If the cpu doesn't exist, it returns false, if not, 
        it prints his processes with their information and returns true.
    */
    bool ipro(const string& x) const;

    /**
        @brief Prints all the active processes from the cluster by 
        increasing id order.

        \pre <em>True</em>.
        \post All the processes have been printed.
    */
    void ipc() const;

    /**
        @brief Prints the cluster structure.

        \pre <em>True</em>.
        \post The cluster has been printed.
    */
    void iec() const;

    /**
        @brief Compacts the memory of a cpu.

        \pre A cpu id.
        \post If the cpu id doesn't exist, it returns false, if not, it 
        compacts its memory moving all the processes to the beginning of 
        the memory respecting the order and returns true.
    */
    bool cmp(string x);

    /**
        @brief Compacts all the cpus.

        \pre <em>True</em>.
        \post All the memory modules from all the cpus have been compacted.
    */
    void cmc();

    /**
        @brief Receives a process from the waiting area, finds the best cpu
        for it, if it's possible, it adds the process to the cluster.

        \pre <em>True</em>.
        \post If the process it's added it returns true, if not it
        returns false.
    */
    bool recive_processes(Process a);

    int podar_cluster(const string& id, int& num_cpu, int& num_pro);
};

#endif