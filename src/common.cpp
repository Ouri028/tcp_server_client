
#include <cstdlib>
#include "../include/file_descriptor.h"
#include "../include/common.h"

#define SELECT_FAILED -1
#define SELECT_TIMEOUT 0

namespace socket_waiter {
    /**
     * monitor file descriptor and wait for I/O operation
     */
    Result waitFor(const FileDescriptor &fileDescriptor, size_t timeoutSeconds) {
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        fd_set fds;

        FD_ZERO(&fds);
        FD_SET(fileDescriptor.get(), &fds);
        const int selectRet = select(fileDescriptor.get() + 1, &fds, nullptr, nullptr, &tv);

        if (selectRet == SELECT_FAILED) {
            return Result::FAILURE;
        } else if (selectRet == SELECT_TIMEOUT) {
            return Result::TIMEOUT;
        }
        return Result::SUCCESS;
    }
}

