#ifndef _H_EVENT_MANAGER_H_
#define _H_EVENT_MANAGER_H_
#include "Event.hpp"
#include "BasicTypes.hpp"
#include <functional>
#include <thread>
#include <future>
#include <utility>
#include <chrono>
#include <atomic>

typedef int (*EventListenerFunctionC)(Event e);
#define EventListenerFunctionType int(Event e)
typedef std::function<EventListenerFunctionType> EventListenerFunction;
typedef std::vector<EventListenerFunction> EventListenerFunctions;
typedef std::unordered_map<EventType, EventListenerFunctions> EventListeners;
typedef std::vector<std::thread> threads;
// typedef std::pair<std::thread,std::promise<bool> > FutureThread;
typedef std::future<int> FutureThread;
typedef std::packaged_task<int(Event)> PackagedEventListenerFunction;
typedef std::pair<std::thread, PackagedEventListenerFunction > PackagedThread;
typedef std::atomic<bool> AtomicBool;
// typedef std::pair<std::thread, bool> Thread;


// class Thread {
//     std::thread *m_t = nullptr;
//     bool *m_b = nullptr;
//     static void run(EventListenerFunction func, Event e, bool *status) {
//         (func)(e);
//         *status = true;
//     }
//     public:
//     Thread(EventListenerFunction f, Event e) {
//         m_b = new bool(false);
//         m_t = new std::thread(run,f,e,m_b);
//     }
//     ~Thread() {
//         if (m_t != nullptr) m_t->join();
//         if (m_b != nullptr) delete m_b;
//         if (m_t != nullptr) delete m_t;
//         m_t = nullptr;
//         m_b = nullptr;
//     }
//     bool done() {
//         return *m_b;
//     }
//     void join() {
//         if (m_t != nullptr) m_t->join();
//     }
// };


typedef std::vector<FutureThread> FutureThreads;
typedef std::vector<PackagedThread> PackagedThreads;
// typedef std::vector<Thread> Threads;
typedef threads Threads;
typedef std::thread Thread;


#define toFunction(function) static_cast<EventListenerFunction>([&](Event ___e___){return function(___e___);})

class EventManager {
    EventListeners listeners;
    Threads m_threads;
    bool m_bubbles;

    public:
    EventManager(bool bubbles = true):m_bubbles(bubbles) {};
    ~EventManager() {
        std::cout << "waiting for threads" << std::endl;
        for (Thread &t : m_threads) {
            t.join();
        }
    }
    template<typename EventListenerFunctionTypename>
    void addEventListener(EventType eventType, EventListenerFunctionTypename func);
    void dispatchEvent(Event event);
    void dispatchEvent(EventType eventType);
};

template<>
void EventManager::addEventListener(EventType eventType, EventListenerFunctionC func) {
    listeners[eventType].push_back(func);
}

template<typename EventListenerFunctionTypename>
void EventManager::addEventListener(EventType eventType, EventListenerFunctionTypename func) {
    listeners[eventType].push_back(func);
}

void EventManager::dispatchEvent(Event event) {
    if (m_bubbles) {
        for (EventListenerFunction func : listeners[event.type()]) {
            m_threads.push_back(std::thread(func, event)); // running, but doesnt give thread status
            // FutureThreads ft = std::async(func, event);
            // PackagedEventListenerFunction pf(func);
            // std::thread t(std::move(pf),event);
            // m_threads.push_back(std::make_pair(t,pf));
            // m_threads.push_back(Thread(func,event)); // running exception
        }
        // for (Thread &t : m_threads) {
        //     std::cout << (t.done() ? "Done" : "Running") << std::endl;
        // }
    } else {
        for (EventListenerFunction func : listeners[event.type()]) {
            func(event);
        }
    }
}

void EventManager::dispatchEvent(EventType eventType) {
    dispatchEvent(Event(eventType,this));
}

#endif // _H_EVENT_MANAGER_H_