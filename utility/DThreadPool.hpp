
#ifndef __MYTHREADPOOL_HPP__
#define __MYTHREADPOOL_HPP__

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>

class ThreadPoolTask {
public:
    virtual void Run() = 0;
};

class ThreadPool {
private:
    std::list<ThreadPoolTask *> _taskList;
    std::list<std::thread> _threadList;
    std::mutex _threadCvMtx;
    std::condition_variable _threadCv;
    bool _isQuiting;

    void run() {
        while(!_isQuiting) {
            ThreadPoolTask *task(nullptr);
            {
                std::unique_lock<std::mutex> lck(_threadCvMtx);
                _threadCv.wait(lck,[&]() { return _taskList.size() > 0; });
                auto taskBegin = _taskList.begin();
                if (taskBegin != _taskList.end()) {
                    task = *taskBegin;
                    _taskList.erase(taskBegin);
                }
            }

            if (task) {
                task->Run();
            }
        }
    }

    void join() {
        for (auto &th : _threadList) th.join();
    }

public:
    ThreadPool(uint32_t threadCount) : _isQuiting(false) {
        for (uint32_t i = 0; i != threadCount; ++i) {
            _threadList.push_back(std::thread(&ThreadPool::run,::std::ref(*this)));
        }
    }

    void RunTask(ThreadPoolTask *task) {
        std::unique_lock<std::mutex> lck(_threadCvMtx);
        _taskList.push_back(task);
        _threadCv.notify_one();
    }

    void Close() {
        {
            std::unique_lock<std::mutex> lck(_threadCvMtx);
            _isQuiting = true;
            _threadCv.notify_all();
        }
        this->join();
    }
};

#endif /* __MYTHREADPOOL_H__ */