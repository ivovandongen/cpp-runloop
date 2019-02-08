# C++ Runloops

Some different alternatives to maintain a list of work items in a runloop using async io (pipes here)

- [Basic runloop](src/basic_runloop) Uses a mutex to handle concurrent access to the list of work items.
Disadvantage is that in some situations this could lead to a deadlock as demonstrated in 
[main.cpp](src/basic_runloop/main.cpp)
- [Basic runloop based on a flat-combining queue](src/basic_runloop_fc_cds) implementation from 
[libcds](https://github.com/khizmax/libcds) (interesting read 
[here](https://www.cs.bgu.ac.il/~hendlerd/papers/flat-combining.pdf)). This is dependent on Boost, 
which might or might not fit your project.
- [Basic runloop based a spin-lock](src/basic_runloop_spin_lock). Using busy wait and a atomic to 
acquire a lock. The work queue is swapped to a temporary queue before processing the work items.
Needs shared pointers to assure life-time of the work items. 