#include <thread>

#include <cstdio>

extern "C"
{
    void sleep_in_another_thread(int seconds)
    {
        std::thread th
        {
            [seconds]
            {
                std::printf("Thread started and will sleep for %d seconds\n", seconds);
                std::this_thread::sleep_for(std::chrono::seconds{seconds});
                std::printf("Thread woke up\n");
            }
        };
        th.detach(); // do not use std::thread::join() in main thread: it will freeze page
    }
}
