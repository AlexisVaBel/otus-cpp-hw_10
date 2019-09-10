#ifndef BULKQUEUE_H
#define BULKQUEUE_H

#include <iostream>

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;



// realisation from this article
//https://juanchopanzacpp.wordpress.com/2013/02/26/concurrent-queue-c11/

template <typename T>
struct BulkQueue {
    BulkQueue (T defval):m_bFinalized(false), m_defaultValue(defval){

    }
    BulkQueue( const BulkQueue& other)
    {
        std::lock_guard<T> guard( other.m_mutex );
        m_queue = other.m_queue;
        m_bFinalized = other.m_bFinalized;
    }

    bool is_empty(){
        return m_queue.empty();
    }

    // this queue can be stopped filling so, we need some default value and finalized marker
    void set_finalized(){
        std::unique_lock<std::mutex> mlock(m_mutex);
        m_bFinalized = true;
        m_cond.notify_all();
    }

    bool is_finalized(){
        std::unique_lock<std::mutex> mlock(m_mutex);
        return m_bFinalized;
    }

    T pop()
    {        
        std::unique_lock<std::mutex> mlock(m_mutex);
        if(!m_cond.wait_for(mlock, 100ms,[this]{return ( !m_queue.empty() );})){
            return std::vector<std::string>();;
        }
        auto last = m_queue.front();
        m_queue.pop();
        return last;
    }

    void pop(T& item)
    {
        std::unique_lock<std::mutex> mlock(m_mutex);
        if(!m_cond.wait_for(mlock, 100ms,[this]{return ( !m_queue.empty() );})){
            return;
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

  bool          m_bFinalized;

};

#endif // BULKQUEUE_H
