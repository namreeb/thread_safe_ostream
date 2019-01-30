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
#include <sstream>
#include <functional>
#include <mutex>

namespace std
{
nam::Log& endl(nam::Log &log)
{
    log.Flush();
    return log;
}
}

namespace nam
{
void Log::Flush()
{
    std::lock_guard<std::mutex> guard(_mutex);

    _callback((*_buffer).str());
    _buffer.reset(new nam::Log::buffer_type);
}

Log::Log(std::function<void(const string_type &)> callback) : _callback(callback) {}
}
