/** @file Cpu.hh
    @brief Especification of the class Cpu
*/

#ifndef CPU_HH
#define CPU_HH

#include "Process.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#endif

typedef map<int, pair<int, int>>::iterator& dit;

/**
    @class Cpu
    @brief It represents a cpu, a processor

    The processor has a memory with limited space and it can contain 
    processes, each one with a 'delta' time needed to be completed and 
    stored in chronological order
*/

class Cpu {
    private:
    int ffree, mema, max;               //ffree (value of the first free
                                        //direction of the memory)

                                        //mema (total memory of the cpu)

                                        //max (total ffree memory)
    bool leaf = false;
    map<int, Process> prl;              //key -> id, value -> processes

    map<int, set<int>> es;              //key -> empty space in front 
                                        //of a process
                                        //value -> set with directions of 
                                        //memory with that empty space

    map<int, pair<int,int>> diro;       //key -> direction of occupied memory
                                        //value -> map with
                                        //key2 -> process id
                                        //value2 -> size of the process

    /**
        @brief Checks for the next direction with free memory in front of a
        given process which "it" points to.

        \pre Direction and tam of the process pointed from it. Both
        initialized and it is a valid iterator.
        \post Ffree now has the lowest free direction of memory, in case that
        the cpu is full ffree stores mema + 1.
    */
    int check_ffree(const int direction, const int tam, dit it);

    /**
        @brief Takes value -> direction of memory and key -> size.
        Adds the direction to the set of that size of free memory.

        \pre Value and key initialized.
        \post The direction has been added, if the size of memory didn't
        exist, now exists.
    */
    void insert_set(int value, int key);

    /**
        @brief Takes key -> size and diff -> direction of free memory.
        Erases the direction and the size if this one turns to be empty.

        \pre Diff and key initialized.
        \post The direction has been removed, if size turns to be empty it's
        also deleted from the map of free memory.
    */
    void update_set_and_erase(int diff, int key);

    /**
        @brief Same functionality as add_process_cpu() but modified to
        epc().

        \pre All variables initialized, proc_id, mem and time correspond to
        the data of the process and back represents the size of free memory
        where ffree its stored on the map of free memory.
        \post The process has been added to the memory of the cpu.
    */
    void relocate(int proc_id, int mem, int time, int back);

    public:

    /**
        @brief Default creator.

        \pre <em>True</em>.
        \post A Cpu without the memory initialized.
    */
    Cpu();

    /**
        @brief Creator.

        \pre The Cpu is not initialized, n > 0.
        \post The Cpu is initialized with a memory of n space and an 
        identificator = cpu_id.
    */
    Cpu(int n);

    /**
        @brief Sets the variable leaf of the cpu to true, meaning that
        on the cluster it has no childs.

        \pre <em>True</em>.
        \post Leaf is set to true.
    */
    void is_leaf();

    /**
        @brief Checks if the cpu is a leaf of the cluster.

        \pre The variable leaf has to bee initialized, this means the cpu
        has to be initalized too.
        \post Returns the value of leaf.
    */
    bool yn_leaf() const;

    /**
        @brief Checks the errors and adds the process to the cpu if everything 
        goes right.

        \pre Identity, memory and time initialized.
        \post If the process already exists it returns 102, if it doesn't fit 
        it returns 103. If nothing of this happens, adds the process to the
        cou and returns 100.
    */
    int add_process_cpu(int identity, int memory, int time);

    /**
        @brief Checks the errors and removes the process to the cpu if 
        everything goes right.


        \pre Initialized proc_id.
        \post The process has been eliminated from the cpu and after
        checking if there is empty space before and after where the process
        was the new space it's stored also in back (used for relocate).
    */
    int remove_process_cpu(int proc_id, int& back);

    /**
        @brief Advances time to all the processes in delta unities.

        \pre Initialized and delta > 0.
        \post All the processes of our memory have been advanced in time.
    */
    void advance(int delta);

    /**
        @brief Returns the memory of the cpu, occupied and free memory.

        \pre <em>True</em>.
        \post Returns mema.
    */
    int what_mema() const;

    /**
        @brief Prints the cpu on the console.

        \pre <em>True</em>.
        \post The cpu has been printed.
    */
    void write_cpu() const;

    /**
        @brief Compacts the memory of the cpu, moving all the processes to
        the beginning of the memory respecting the order and without
        overlapping them.

        \pre <em>True</em>.
        \post The memory of the cpu has been compacted.
    */
    void compactar();

    /**
        @brief Tells if the cpu has any active process or not.

        \pre <em>True</em>.
        \post True if it's empty and false if it has at least one process.
    */
    bool active_processes() const;

    /**
        @brief Checks the errors and if everything goes right,
        returns the lowest space of free memory equal or greater
        than the variable mem.

        \pre Both variables initialized mem and identity.
        \post Returns -1 if it doesn't fit or if it already exists a process
        with that id. If not it returns the space where it would be added.
    */
    int get_memory(int mem, int identity) const;

    /**
        @brief Returns the value of the free space left on the cpu, NOT
        consecutive space, the whole free space.

        \pre <em>True</em>.
        \post Returns max.
    */
    int space_left() const;

    /**
        @brief Returns the first direction with free memory of the cpu.

        \pre <em>True</em>.
        \post Returns ffree.
    */
    int what_ffree() const;

    int how_many() const;
};

#endif