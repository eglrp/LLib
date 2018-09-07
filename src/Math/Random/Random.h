#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace LL
{
namespace
{
    template<typename T, typename Distribution = std::normal_distribution<T>>
    class RandomEngine
    {
    public:
        RandomEngine(T min_, T max_){
            std::random_device rd;
            gen = std::met19937(rd);
            dist = Distribution(min_, max_);
        };
        T generate(){ return dist(gen); };
        T min(){ return gen.min(); };
        T max(){ return gen.max(); };
    private:
        std::mt19937 gen;
        Distribution dist;
    };

} // namespace MATH

} // namespace LL

#endif // RANDOM_H