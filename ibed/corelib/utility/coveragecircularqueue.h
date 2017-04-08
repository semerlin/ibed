/*****************************************************************************
**
**  Copyright (C) 2016-2017 HuangYang
**
**  This file is part of IBED
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as
**  published by the Free Software Foundation.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
**
**  @file     CoverageCircularQueue.cpp
**  @brief    circle queue template
**  @details  none
**  @author   huang yang
**  @email    elious.huang@gmail.com
**  @version  v1.0.0.0
**  @license  GNU General Public License (GPL)
**
*****************************************************************************/

#ifndef COVERAGECIRCULARQUEUE_H
#define COVERAGECIRCULARQUEUE_H

#include "utility_global.h"
#include <QMutex>
#include "boost/shared_ptr.hpp"

template <typename T>

class UTILITYSHARED_EXPORT CoverageCircularQueue
{
public:
    CoverageCircularQueue(const int size = DEFAULT_SIZE) :
        m_size(size + 1),
        m_front(0),
        m_rear(0),
        m_mutex(new QMutex)
    {
        if(m_size <= 1)
            m_size = 2;
        m_queue = new T[m_size];
    }

    ~CoverageCircularQueue()
    {
        delete []m_queue;
    }

public:
    /**
     * @brief return circle queue size
     * @return circle queue size
     */
    int size(void) const
    {
        return m_size - 1;
    }

    /**
     * @brief dequeue value form the queue
     * @return value
     */
    T dequeue(void)
    {
        if(isEmpty())
            return T();

        QMutexLocker loker(m_mutex);
        int prevFront = m_front;
        m_front = (m_front + 1) % m_size;

        return m_queue[prevFront];
    }

    /**
     * @brief enqueue value to the queue
     * @param t - value
     */
    void enqueue(const T &t)
    {
        m_mutex->lock();
        if(((m_rear + 1) % m_size) == m_front)
            m_front = (m_front + 1) % m_size;

        m_queue[m_rear] = t;
        m_rear = (m_rear + 1) % m_size;
        m_mutex->unlock();
    }

    /**
     * @brief check if queue is full
     * @return full flag
     */
    bool isFull(void) const
    {
        QMutexLocker locker(m_mutex);
        return (((m_rear + 1) % m_size) == m_front);
    }

    /**
     * @brief check if queue is empty
     * @return empty flag
     */
    bool isEmpty(void) const
    {
        QMutexLocker locker(m_mutex);
        return (m_front == m_rear);
    }

    /**
     * @brief get value at potision
     * @param index - value index
     * @return value
     */
    const T& at(int index) const
    {
        QMutexLocker locker(m_mutex);
        if((index < 0) || (index >= m_size))
            return T();

        return m_queue[index];
    }

    T& at(int index)
    {
        return const_cast<T&>(static_cast<const CoverageCircularQueue&>(*this).at(index));
    }

    const T& operator[](int index) const
    {
        QMutexLocker locker(m_mutex);
        if((index < 0) || (index >= m_size))
            return T();

        return m_queue[index];
    }

    T& operator[](int index)
    {
        return const_cast<T&>(static_cast<const CoverageCircularQueue&>(*this)[index]);
    }

private:
    static const int DEFAULT_SIZE = 128;
    int m_size;
    T *m_queue;
    int m_front;
    int m_rear;
    boost::shared_ptr<QMutex> m_mutex;
};

#endif // CIRCULARQUEUE_H
