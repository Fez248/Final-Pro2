/** @file Process.hh
    @brief Especification of the class Process
*/

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;
#ifndef PROCESS_HH
#define PROCESS_HH

/** 
    @class Process
    @brief It represents a process

    Each process has his proc_id, the memory it needs, his priority and the 
    time needed to be executed
*/

class Process {
    private:
    int dir, ide, memo, time; //information of the process

    public:

    /**
        @brief Default creator.

        \pre <em>True</em>.
        \post A process.
    */
    Process();

    /**
        @brief Secondary creator.

        \pre <em>Identity, memory, delta and direction initialized</em>.
        \post A process with this information.
    */
    Process(int identity, int memmory, int delta, int direction);

    /**
        @brief Returns the id of the process.

        \pre <em>True</em>.
        \post Returns proc_id.
    */
    int what_id() const;

    /**
        @brief Returns the memory needed for the process.

        \pre <em>True</em>.
        \post Returns mem.
    */
    int what_mem() const;

    /**
        @brief Returns the time left of the process.

        \pre <em>True</em>.
        \post Returns delta.
    */
    int what_time() const;

    /**
        @brief Returns the memory direction where the process it's stored.

        \pre Initialized cpu direction.
        \post Returns the direction.
    */
    int what_dir() const;

    /**
        @brief Prints the process on the console.

        \pre <em>True</em>.
        \post The process is printed.
    */
    void wr_process() const;

    /**
        @brief Second way of printing the process on the console.

        \pre <em>True</em>.
        \post The process is printed.
    */
    void wr2_process() const;

    /**
        @brief Reduces the time left of the process.

        \pre Initialized and t > 0.
        \post Reduces time in t unities, if delta == 0 it returns false, if 
        not returns true.
    */
    bool reducing(int t);
};

#endif