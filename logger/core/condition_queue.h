#ifndef _LOGGER_CONDITION_QUEUE_H_
#define _LOGGER_CONDITION_QUEUE_H_

//C++ header
#include <cstddef>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename value_type>
class ConditionQueue
{
public:
    ConditionQueue() :
        m_queue_max_size(m_queue_default_size)
        {}

    // delete copy constructor
    ConditionQueue(const ConditionQueue&) = delete;
    // delete copy assignment
    ConditionQueue& operator=(const ConditionQueue&) = delete;
    // delete move constructor
    ConditionQueue(ConditionQueue&&) = delete;
    // delete move assignment
    ConditionQueue& operator=(ConditionQueue&&) = delete;

    ~ConditionQueue() = default;

    bool push(const value_type& element)
    {
        std::unique_lock<std::mutex> lock_obj(m_mutex);
        if (m_queue.size() > m_queue_max_size)
        {
            return false;
        }

        m_queue.push(element);
        m_cond.notify_one();

        return true;
    }

    value_type pop()
    {
        std::unique_lock<std::mutex> lock_obj(m_mutex);

        while (m_queue.empty())
        {
            m_cond.wait(lock_obj);
        }

        value_type element = m_queue.front();
        m_queue.pop();

        return element;
    }

    void set_max_size(size_t max_size)
    {
        m_queue_max_size = max_size;
    }

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;

    std::queue<value_type> m_queue;
    size_t m_queue_max_size;
    static const size_t m_queue_default_size = 10000;
};

#endif // _LOGGER_CONDITION_QUEUE_H_
