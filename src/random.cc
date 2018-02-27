#include "random.h"

Random* Random::instance_ = 0;

Random* Random::Instance() {
  if (instance_ == 0) {
    instance_ = new Random();
  }

  return instance_;
}

float Random::GetRandom() {
  return distibution_->operator()(*random_engine_);
}

Random::Random() {
  std::random_device r;
  std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
  random_engine_ = new std::mt19937(seed2);
  distibution_ = new std::uniform_real_distribution<float>(0.0f, 1.0f);
}

Random::~Random() {
  delete random_engine_;
  delete distibution_;
}
