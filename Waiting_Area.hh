/** @file Waiting_Area.hh
    @brief Especification of the class Waiting_Area
*/

#ifndef WAITING_AREA_HH
#define WAITING_AREA_HH

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <map>
#endif

typedef map<string, list<Process>> area;
typedef list<Process> category;

/**
    @class Waiting_Area
    @brief It represents a waiting area

    Here we store the processes waiting to be sended to the cluster sorted 
    by their priority.
*/

class Waiting_Area {
    private:
    map<string, list<Process>> wa; //priorities with a list of processes
    map<string, pair<int, int>> sera; //sended processes and rejected

    /**
        @brief Search for a process with a specific priority in the 
        waiting area.

        \pre Both proc_prio and proc_id initialized, proc_id > 0.
        \post Returns true if the process exists and false if not.
    */
    bool search_process(area::const_iterator it, int proc_id) const;

    /**
        @brief Adds a process to the waiting area.

        \pre Both prio and a initialized.
        \post Adds the process to the waiting area.
    */
    void add_process(const string& prio, const Process& a);

    public:
    /**
        @brief Default creator.

        \pre <em>True</em>.
        \post An empty waiting area.
    */
    Waiting_Area();

    /**
        @brief Used to initialize the Waiting Area.

        \pre A number n indicating the number of priorities and all their 
        information on the console.
        \post Waiting Area initialized.
    */
    void read_waiting_area();

    /**
        @brief Reads a priority identification and if everything it's correct 
        it adds the priority to the waiting area.

        \pre A priority identification.
        \post If the identification already exists it returns false, if not, 
        it adds the priority to the waiting area without pending processes 
        and returns true.
    */
    bool ap(const string& x);

    /**
        @brief Reads a priority identification and if everything it's correct 
        it removes this priority from the waiting area.

        \pre A priority identification.
        \post If the identification doesn't exist returns 101, if it has 
        pending processes it returns 102, if not, it removes this priority 
        from the waiting area and returns 100.
    */
    int bp(const string& x);

    /**
        @brief Reads the values of a proccess and a priority id and if 
        everything goes right, adds the proccess to the waiting area 
        with that priority id.

        \pre A process and a priority identification ready to be read.
        \post If the id priority doesn't exist returns 101, if a process with
        that id and priority already exists it returns 102, if not it adds 
        the process and returns 100.
    */
    int ape(const string& x, int identity, int memory, int time); 

    /**
        @brief Reads a positive number, n and tries to send n waiting        
        processes to the cluster by priority and by the time they have been
        waiting. They are send to the best spot, if a process can not be send
        to the cluster it comes back as a new process to the waiting area.

        \pre A number n ready to be read in the console.
        \post If the process it's sended it increments the number of sended 
        processes of the priority by one, if not it increments the number of 
        rejected ones.
    */
    void epc(int n, Cluster& clust);

    /**
        @brief Reads a priority id and prints all the pending processes, the 
        number of processes sended to the cluster and rejections.

        \pre A priority id ready to be read at the console.
        \post If the priority id doesn't exist it returns false, if not, 
        returns true.
    */
    bool ipri(const string& x) const;

    /**
        @brief Prints all the priorities with their processes, number of 
        processes sended and rejections.

        \pre <em>True</em>
        \post All the processes have been printed on the console and for 
        each priority the number of processes send and rejections.
    */
    void iae () const;
};

#endif