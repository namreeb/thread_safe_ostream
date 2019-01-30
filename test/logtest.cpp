/*
 * MIT License
 *
 * Copyright (c) 2019 namreeb (legal@namreeb.org) https://github.com/namreeb/thread_safe_ostream
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Log.hpp"

#include <string>
#include <iostream>
#include <thread>
#include <vector>

#define THREADED

int main()
{
#ifdef THREADED
    nam::Log testLog([] (const std::string &str)
    {
        auto const id = std::this_thread::get_id();

        std::cout << "Thread " << id << ": " << str;
        std::cout.flush();
    });

    auto constexpr threadCount = 2;
    auto constexpr iterations = 5;
    auto constexpr repeats = 8;

    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    for (auto i = 0; i < threadCount; ++i)
        threads.emplace_back([&testLog] (int id, int iterations, int repeats)
        {
            for (auto i = 0; i < iterations; ++i)
            {
                for (auto r = 0; r < repeats; ++r)
                    testLog << id;

                testLog << std::endl;
            }
        }, i, iterations, repeats);

    for (auto &t : threads)
        t.join();

    std::cout << "\nIf the test worked, you should see " << (threadCount * iterations)
              << " lines with the thread id repeated " << repeats << " times.\n"
              << "There should be no interleaving." << std::endl;

#else
    nam::Log testLog([] (const std::string &str)
    {
        std::cout << "String: " << str;
    });

    testLog << "This is a test" << std::endl;
#endif

    return 0;
}