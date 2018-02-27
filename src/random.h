#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <cmath>

class Random {

  public:
    static Random* Instance();

    float GetRandom();
  protected:
    Random();
    ~Random();
  private:
    static Random* instance_;

    std::mt19937* random_engine_;
    std::uniform_real_distribution<float>* distibution_;
};


#endif /* RANDOM_H */
