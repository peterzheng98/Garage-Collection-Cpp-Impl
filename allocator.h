//
// Created by Peter Zheng on 2018/08/29.
//

#ifndef GARBAGE_COLLECTION_CPP_IMPL_ALLOCATOR_H
#define GARBAGE_COLLECTION_CPP_IMPL_ALLOCATOR_H

#include "memory.h"
#include <atomic>
#include <thread>

namespace GCImpl {
    class allocator {
    private:
        memory *core;
    public:
        allocator(memory *core) : core(core) {}

        allocator() { core = nullptr; }

        ~allocator() { core = nullptr; }

        void collect() {

        }

        int New(const int &sizeT) {
            int ref = core->allocate(sizeT).second;
            if (ref == -1) {
                collect();
                ref = core->allocate(sizeT).second;
                if (ref == -1) throw exception("Don\'t have enough memory.", "Memory Error");
            }
            return ref;
        }

    };
}

#endif //GARBAGE_COLLECTION_CPP_IMPL_ALLOCATOR_H
