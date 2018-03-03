#include "population.h"

Population::Population(int number_of_creatures, int number_of_genes_per_creature) :
  number_of_creatures_(number_of_creatures),
  number_of_genes_per_creature_(number_of_genes_per_creature){

  number_of_genes_ = number_of_creatures_ * number_of_genes_per_creature_;
  genes_ = new Gene[number_of_genes_];

  for (int i = 0; i < number_of_genes_; ++i) {
    genes_[i] = CreateGene();
  }

}

Population::~Population() {
  delete genes_;
}
