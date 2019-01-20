/**
 * @file
 * @author  Mamadou Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mamadou Babaei
 * Copyright (c) 2018 - 2019 Seditious Games Studio
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Softwrrare, and to permit persons to whom the Software is
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
 *
 * @section DESCRIPTION
 *
 * A smart thread-safe object pool implementation
 */


#pragma once

#include <memory>
#include <mutex>
#include <stack>
#include <utility>

#include <Misc/AssertionMacros.h>

template <typename TYPE, typename DEFAULT_DELETER = std::default_delete<TYPE>>
class GSharedObjectPool
{
private:
    struct ReturnToPoolDeleter
    {
    private:
        std::weak_ptr<GSharedObjectPool<TYPE, DEFAULT_DELETER>*> Pool;

    public:
        explicit ReturnToPoolDeleter(const std::weak_ptr<GSharedObjectPool<TYPE, DEFAULT_DELETER>*> InPool = { })
            : Pool(InPool)
        {

        }

        void operator()(TYPE* Pointer)
        {
            if (auto PoolPointer = Pool.lock())
            {
                std::unique_ptr<TYPE, DEFAULT_DELETER> UniquePointer{Pointer};
                (*PoolPointer.get())->Add(UniquePointer);
            }
            else
            {
                DEFAULT_DELETER{}(Pointer);
            }
        }
    };

public:
    using PointerType = std::unique_ptr<TYPE, ReturnToPoolDeleter>;

private:
    std::shared_ptr<GSharedObjectPool<TYPE, DEFAULT_DELETER>*> ThisSharedPointer;
    std::stack<std::unique_ptr<TYPE, DEFAULT_DELETER>> Pool;
    std::mutex Lock;

public:
    GSharedObjectPool()
        : ThisSharedPointer(std::make_shared<
                            GSharedObjectPool<TYPE, DEFAULT_DELETER>*>(this))
    {

    }

    virtual ~GSharedObjectPool() = default;

public:
    void Add(std::unique_ptr<TYPE, DEFAULT_DELETER>& UniquePointer)
    {
        std::lock_guard<std::mutex> LockGuard(Lock);
        (void)LockGuard;

        Pool.push(std::move(UniquePointer));
    }

    PointerType Acquire()
    {
        std::lock_guard<std::mutex> LockGuard(Lock);
        (void)LockGuard;

        checkf(!Pool.empty(),
               TEXT("FATAL: Cannot acquire object from an empty pool!"));

        PointerType TempPointer(Pool.top().release(),
                        ReturnToPoolDeleter {
                            std::weak_ptr<GSharedObjectPool
                            <TYPE, DEFAULT_DELETER>*>{ThisSharedPointer}});
        Pool.pop();

        return std::move(TempPointer);
    }

    bool Empty() const
    {
        return Pool.empty();
    }

    std::size_t Size() const
    {
        return Pool.size();
    }

    std::stack<std::unique_ptr<TYPE, DEFAULT_DELETER>>& GetPool()
    {
        return Pool;
    }
};
