//
// Created by Peter Zheng on 2018/08/29.
//

#ifndef GARBAGE_COLLECTION_CPP_IMPL_MEMORY_H
#define GARBAGE_COLLECTION_CPP_IMPL_MEMORY_H
#define MAXSIZE 1024*1024

#include "exception.h"
#include <cstring>
#include <utility>

namespace GCImpl {
    using memoryOperationResult = std::pair<bool, int>;

    class memory {
    private:
        char __memory[MAXSIZE + 1024];
        int curSize = 0, maxSize = MAXSIZE;
        int spareSize = maxSize;
    public:
        memory() = default;

        memory(const memory &rhs) {
            for (int i = 0; i < MAXSIZE; ++i) __memory[i] = rhs.__memory[i];
            curSize = rhs.curSize;
        }

        ~memory() = default;

        memory &operator=(const memory &rhs) {
            for (int i = 0; i < MAXSIZE; ++i) __memory[i] = rhs.__memory[i];
            curSize = rhs.curSize;
        }

        char operator[](const int &index) {
            if (index >= curSize) throw GCImpl::exception("Access out of bound.", "Access Denied");
            return __memory[index];
        }

        const char operator[](const int &index) const {
            if (index >= curSize) throw GCImpl::exception("Access out of bound.", "Access Denied");
            return __memory[index];
        }

        memoryOperationResult insert(const char *charSeq, const int &startAddress) {
            int length = strlen(charSeq);
            int sizeT = 0;
            for (int i = startAddress; i < maxSize && i - startAddress < length; ++i) {
                __memory[i] = charSeq[i - startAddress];
                sizeT++;
            }
            spareSize -= sizeT;
            return std::make_pair(true, std::min(length + startAddress, maxSize));
        }

        memoryOperationResult erase(const int &startAddr, const int &endAddr) {
            if (endAddr <= startAddr) throw GCImpl::exception("Upper Bound Smaller than Lower.", "Bound Check Error");
            //Check whether end Address is out of bound;
            if (endAddr >= maxSize) throw GCImpl::exception("Access out of bound.", "Access Denied");
            for (int i = startAddr; i < endAddr; ++i) __memory[i] = 0;
            spareSize += (endAddr - startAddr);
            return std::make_pair(true, std::max(endAddr, curSize));
        }

        memoryOperationResult insert(const char *charSeq) {
            int sizeT = 0;
            for (int i = curSize; i < maxSize && i - curSize < strlen(charSeq); ++i) {
                __memory[i] = charSeq[i - curSize];
                sizeT++;
            }
            if (sizeT != strlen(charSeq)) curSize = maxSize; else curSize += sizeT;
            return std::make_pair(true, curSize);
        }

        memoryOperationResult allocate(const int& sizeT){
            if(curSize + sizeT >= maxSize) return std::make_pair(false, -1);
            curSize += sizeT;
            return std::make_pair(true, curSize - sizeT);
        }
    };
}

#endif //GARBAGE_COLLECTION_CPP_IMPL_MEMORY_H
