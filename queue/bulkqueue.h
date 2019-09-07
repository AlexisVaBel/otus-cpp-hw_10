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
        std::lock_guard<T> guard( other.mutex_ );
        queue_ = other.queue_;
        m_finalized = other.m_finalized;
    }

    bool is_empty(){
        return queue_.empty();
    }

    // this queue can be stopped filling so, we need some default value and finalized marker
    void set_finalized(){
        std::unique_lock<std::mutex> mlock(mutex_);
        m_finalized = true;        
        mlock.unlock();
        cond_.notify_one();
    }

    bool is_finalized(){
        return m_finalized;
    }

    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty())
        {            
            if(m_finalized) return m_defaultValue;
            cond_.wait(mlock);

        }

        auto item = queue_.front();
        queue_.pop();
        return item;
    }

    void pop(T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty())
        {
            cond_.wait(mlock);
        }
        item = queue_.front();
        queue_.pop();
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_.notify_one();
    }

    void push(T&& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(std::move(item));
        mlock.unlock();
        cond_.notify_one();
    }

 private:
  T             m_defaultValue;
  std::queue<T> queue_;  
  std::mutex mutex_;
  std::condition_variable cond_;

  bool m_finalized;

};

#endif // BULKQUEUE_H
