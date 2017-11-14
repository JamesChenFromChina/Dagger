
#ifndef __DTHREADPOOL_HPP__
#define __DTHREADPOOL_HPP__

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>

class DThreadPoolTask {
public:
    virtual void Run() = 0;
};

class DThreadPool {
private:
    std::list<std::shared_ptr<DThreadPoolTask> > _taskList;
    std::list<std::thread> _threadList;
    std::mutex _threadCvMtx;
    std::condition_variable _threadCv;
    bool _isQuiting;

    void run() {
        while(!_isQuiting) {
            std::shared_ptr<DThreadPoolTask> task(nullptr);
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
    DThreadPool(DThreadPool &) = delete;
    DThreadPool(DThreadPool &&pool)
        : _taskList(std::move(pool._taskList))
        ,_threadList(std::move(pool._threadList))
        ,_threadCvMtx(std::move(pool._threadCvMtx))
        ,_threadCv(std::move(pool._threadCv))
        ,_isQuiting(pool._isQuiting) {}

    DThreadPool(uint32_t threadCount) : _isQuiting(false) {
        for (uint32_t i = 0; i != threadCount; ++i) {
            _threadList.push_back(std::thread(&DThreadPool::run,::std::ref(*this)));
        }
    }

    virtual ~DThreadPool() { this->Close(); }

    void RunTask(std::shared_ptr<DThreadPoolTask> task) {
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
    }

    vod Wait() {
        this->join();
    }

};

#endif /* __DTHREADPOOL_H__ */
