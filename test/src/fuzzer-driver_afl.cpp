/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (fuzz test support)
|  |  |__   |  |  | | | |  version 3.7.3
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

This file implements a driver for American Fuzzy Lop (afl-fuzz). It relies on
an implementation of the `LLVMFuzzerTestOneInput` function which processes a
passed byte array.

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
*/

#include <vector>    // for vector
#include <cstdint>   // for uint8_t
#include <iostream>  // for cin
#include <cstring>   // for memcpy
#include <unistd.h>  // for read

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);

static const std::size_t MaxInputSize = 1048576;  // 1MiB
static uint8_t InputBuf[MaxInputSize];

int main()
{
#ifdef __AFL_HAVE_MANUAL_CONTROL
    /* AFL deferred fork */
    __AFL_INIT();

    /* AFL persistent loop */
    while (__AFL_LOOP(1000))
    {
#endif

        /* read data*/
        ssize_t bytesReaded = read(0, InputBuf, MaxInputSize);
        if (bytesReaded > 0)
        {
            /* allocate memory, exactly bytesReaded to catch overflows */
            uint8_t* tmpBuf = (uint8_t*)malloc(bytesReaded);
            memcpy(tmpBuf, InputBuf, bytesReaded);

#ifdef __AFL_HAVE_MANUAL_CONTROL
            /* run harness*/
            LLVMFuzzerTestOneInput(tmpBuf, bytesReaded);

            /* clear */
            free(tmpBuf);
        }
#endif
    }
    return 0;
}
