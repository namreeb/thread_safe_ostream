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

#pragma once

#include <boost/thread/tss.hpp>

#include <string>
#include <sstream>
#include <functional>
#include <mutex>

namespace nam
{
class Log;
}

namespace std
{
nam::Log& endl(nam::Log &log);
}

namespace nam
{
class Log
{
#ifdef UNICODE
    public:
        using string_type = std::wstring;

    private:
        using buffer_type = std::wstringstream;
#else
    public:
        using string_type = std::string;

    private:
        using buffer_type = std::stringstream;
#endif

        void Flush();

        boost::thread_specific_ptr<buffer_type> _buffer;
        std::function<void(const string_type &)> _callback;
        mutable std::mutex _mutex;

        friend Log& std::endl(Log &log);

    public:
        Log(const std::function<void (const string_type &)> &);

        Log& operator << (Log& (func)(Log&))
        {
            (*_buffer) << std::endl;    // FIXME: this ignores the actual value of func, but meh
            return func(*this);
        }

        template <typename T>
        Log & operator << (const T &val)
        {
            if (!_buffer.get())
                _buffer.reset(new buffer_type);

            (*_buffer) << val;
            return *this;
        }
};
}