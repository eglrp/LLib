#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <chrono>

/**
* @brief A Header only StopWatch which records time
*/

namespace LLib
{
    namespace utils
    {
        class StopWatch
        {
            public:
                StopWatch() { reset(); }

                /**
                * @brief Reset the StopWatch
                */ 
                void reset() { start = std::chrono::high_resolution_clock::now(); }

                /**
                * @brief Get the elapsed time in seconds.
                */
                inline double elapsed() const;

                /**
                * @brief Get the elapsed time in seconds.
                */
                inline double elapsedMs() const;

            private:

                std::chrono::high_resolution_clock::time_point start;

        };  // class StopWatch


        inline double StopWatch::elapsed() const
        {
            const auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        }

        inline double StopWatch::elapsedMs() const
        {
            const auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

    }   // namespace Tools

}   // namespace LLib

#endif  // STOPWATCH_H_