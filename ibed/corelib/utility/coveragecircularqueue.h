#ifndef COVERAGECIRCULARQUEUE_H
#define COVERAGECIRCULARQUEUE_H

#include <QMutex>

template <typename T>

class CoverageCircularQueue
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
    int size(void) const
    {
        return m_size - 1;
    }

    T dequeue(void)
    {
        if(isEmpty())
            return T();

        QMutexLocker loker(m_mutex);
        int prevFront = m_front;
        m_front = (m_front + 1) % m_size;

        return m_queue[prevFront];
    }

    void enqueue(const T &t)
    {
        if(isFull())
            increaseFront();

        m_mutex->lock();
        m_queue[m_rear] = t;
        m_rear = (m_rear + 1) % m_size;
        m_mutex->unlock();
    }

    bool isFull(void) const
    {
        bool ret = false;
        m_mutex->lock();
        if(((m_rear + 1) % m_size) == m_front)
            ret = true;
        m_mutex->unlock();
        return ret;
    }

    bool isEmpty(void) const
    {
        bool ret;
        m_mutex->lock();
        ret = (m_front == m_rear);
        m_mutex->unlock();
        return ret;
    }

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
    void increaseFront(void)
    {
        m_mutex->lock();
        m_front = (m_front + 1) % m_size;
        m_mutex->unlock();
    }

private:
    static const int DEFAULT_SIZE = 128;
    int m_size;
    T *m_queue;
    int m_front;
    int m_rear;
    QMutex *m_mutex;
};

#endif // CIRCULARQUEUE_H
