#ifndef BULKQUEUE_H
#define BULKQUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>

// realisation from this article
//https://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/

template <typename T>
struct BulkQueue {
    BulkQueue (T defval):m_finalized(false), m_defaultValue(defval){

    }
    BulkQueue( const BulkQueue& other)
    {
        std::lock_guard<T> guard( other.m_mutex );
        m_queue = other.m_queue;
        m_finalized = other.m_finalized;
    }

    bool is_empty(){
        return m_queue.empty();
    }

    // this queue can be stopped filling so, we need some default value and finalized marker
    void set_finalized(){
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_finalized = true;        
        mlock.unlock();        
        m_cond.notify_all();
    }

    bool is_finalized(){
        return m_finalized;
    }

    T pop()
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        while (m_queue.empty())
        {            
            if(m_finalized) return m_defaultValue;
            m_cond.wait(mlock);

        }

        auto item = m_queue.front();
        m_queue.pop();
        return item;
    }

    void pop(T& item)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        while (m_queue.empty())
        {
            m_cond.wait(mlock);
        }
        item = m_queue.front();
        m_queue.pop();
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_queue.push(item);
        mlock.unlock();
        m_cond.notify_one();
    }

    void push(T&& item)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_queue.push(std::move(item));
        mlock.unlock();
        m_cond.notify_one();
    }

 private:
  T             m_defaultValue;
  std::queue<T> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_cond;

  bool m_finalized;

};

#endif // BULKQUEUE_H
