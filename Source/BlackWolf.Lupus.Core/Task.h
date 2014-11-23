/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include "Utility.h"
#include <chrono>
#include <future>
#include <thread>
#include <functional>
#include <type_traits>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#if _MSC_VER <= 1800
namespace std {
    template<class... _ArgTypes>
    class packaged_task<void(_ArgTypes...)>
    {
        promise<void> _my_promise;
        function<void(_ArgTypes...)> _my_func;

    public:
        packaged_task() {
        }

        template<class _Fty2>
        explicit packaged_task(_Fty2&& _Fnarg)
            : _my_func(_Fnarg) {
        }

        packaged_task(packaged_task&& _Other)
            : _my_promise(move(_Other._my_promise)),
            _my_func(move(_Other._my_func)) {
        }

        packaged_task& operator=(packaged_task&& _Other) {
            _my_promise = move(_Other._my_promise);
            _my_func = move(_Other._my_func);
            return (*this);
        }

        packaged_task(const packaged_task&) = delete;
        packaged_task& operator=(const packaged_task&) = delete;

        ~packaged_task() {
        }

        void swap(packaged_task& _Other) {
            _my_promise.swap(_Other._my_promise);
            _my_func.swap(_Other._my_func);
        }

        explicit operator bool() const {
            return _my_func != false;
        }

        bool valid() const {
            return _my_func != false;
        }

        future<void> get_future() {
            return _my_promise.get_future();
        }

        void operator()(_ArgTypes... _Args) {
            _my_func(forward<_ArgTypes>(_Args)...);
            _my_promise.set_value();
        }

        void reset() {
            swap(packaged_task());
        }
    };
}
#endif

namespace Lupus {
    template <typename R>
    class Task : public NonCopyable
    {
    public:

        Task() = default;

        Task(Task&& task)
        {
            std::swap(mFuture, task.mFuture);
            std::swap(mThread, task.mThread);
            std::swap(mBlock, task.mBlock);
            std::swap(mIsRunning, task.mIsRunning);
        }

        template <typename Function, typename... Args>
        Task(Function&& f, Args&&... args)
        {
            std::packaged_task<R(Args...)> task(f);
            mFuture = task.get_future();
            mThread = std::thread(std::move(task), std::forward<Args>(args)...);
            mIsRunning = true;
        }

        ~Task()
        {
            if (mThread.joinable()) {
                if (mBlock) {
                    mThread.join();
                } else {
                    mThread.detach();
                }
            }
        }

        template <typename Function, typename... Args>
        void Start(Function&& f, Args&&... args) throw(RuntimeError)
        {
            if (mIsRunning) {
                throw RuntimeError("Task is already running");
            }

            std::packaged_task<R(Args...)> task(f);
            mFuture = task.get_future();
            mThread = std::thread(std::move(task), std::forward<Args>(args)...);
            mIsRunning = true;
        }

        R Get()
        {
            return mFuture.get();
            mIsRunning = false;
        }

        bool Valid() const
        {
            return mFuture.valid();
        }

        void Wait() const
        {
            mFuture.wait();
            mIsRunning = false;
        }

        template <typename Rep, typename Period>
        bool WaitFor(const std::chrono::duration<Rep, Period>& duration) const
        {
            mIsRunning = !mFuture.wait_for(duration);
            return mIsRunning;
        }

        template <typename Clock, typename Duration>
        bool WaitUntil(const std::chrono::time_point<Clock, Duration>& time) const
        {
            mIsRunning = !mFuture.wait_until(time);
            return mIsRunning;
        }

        bool IsBlocking() const
        {
            return mBlock;
        }

        void SetBlocking(bool b)
        {
            mBlock = b;
        }

        bool IsRunning() const
        {
            return mIsRunning;
        }

        Task& operator=(Task&& task)
        {
            std::swap(mFuture, task.mFuture);
            std::swap(mThread, task.mThread);
            std::swap(mBlock, task.mBlock);
            std::swap(mIsRunning, task.mIsRunning);
            Task<R> tmp(std::move(task));

            return *this;
        }

    private:

        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;

        std::future<R> mFuture;
        std::thread mThread;
        bool mBlock = false;
        mutable bool mIsRunning = false;
    };

    template <>
    class Task<void> : public NonCopyable
    {
    public:

        Task() = default;

        Task(Task&& task)
        {
            std::swap(mFuture, task.mFuture);
            std::swap(mThread, task.mThread);
            std::swap(mBlock, task.mBlock);
            std::swap(mIsRunning, task.mIsRunning);
        }

        template <typename Function, typename... Args>
        Task(Function&& f, Args&&... args)
        {
            std::packaged_task<void(Args...)> task(f);
            mFuture = task.get_future();
            mThread = std::thread(std::move(task), std::forward<Args>(args)...);
            mIsRunning = true;
        }

        ~Task()
        {
            if (mThread.joinable()) {
                if (mBlock) {
                    mThread.join();
                } else {
                    mThread.detach();
                }
            }
        }

        template <typename Function, typename... Args>
        void Start(Function&& f, Args&&... args) throw(RuntimeError)
        {
            if (mIsRunning) {
                throw RuntimeError("Task is already running");
            }

            std::packaged_task<void(Args...)> task(f);
            mFuture = task.get_future();
            mThread = std::thread(std::move(task), std::forward<Args>(args)...);
            mIsRunning = true;
        }

        void Get()
        {
            mFuture.get();
            mIsRunning = false;
        }

        bool Valid() const
        {
            return mFuture.valid();
        }

        void Wait() const
        {
            mFuture.wait();
            mIsRunning = false;
        }

        template <typename Rep, typename Period>
        bool WaitFor(const std::chrono::duration<Rep, Period>& duration) const
        {
            mIsRunning = !mFuture.wait_for(duration);
            return mIsRunning;
        }

        template <typename Clock, typename Duration>
        bool WaitUntil(const std::chrono::time_point<Clock, Duration>& time) const
        {
            mIsRunning = !mFuture.wait_until(time);
            return mIsRunning;
        }

        bool IsBlocking() const
        {
            return mBlock;
        }

        void SetBlocking(bool b)
        {
            mBlock = b;
        }

        bool IsRunning() const
        {
            return mIsRunning;
        }

        Task& operator=(Task&& task)
        {
            std::swap(mFuture, task.mFuture);
            std::swap(mThread, task.mThread);
            std::swap(mBlock, task.mBlock);
            std::swap(mIsRunning, task.mIsRunning);
            Task<void> tmp(std::move(task));

            return *this;
        }

    private:

        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;

        std::future<void> mFuture;
        std::thread mThread;
        bool mBlock = false;
        mutable bool mIsRunning = false;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
