#ifndef POPULATION_H
#define POPULATION_H

#include "gene.h"

class Population {

  public:
    Population(int number_of_creatures, int number_of_genes_per_creature);
    ~Population();

    int GetNumberOfCreatures();
    int GetNumberOfGenesPerCreature();
    int GetNumberOfGenes();
    Gene* GetGenes();

  private:
    Gene* genes_;
    int number_of_creatures_;
    int number_of_genes_per_creature_;
    int number_of_genes_;
};

inline int Population::GetNumberOfCreatures() {
  return number_of_creatures_;
}

inline int Population::GetNumberOfGenesPerCreature() {
  return number_of_genes_per_creature_;
}

inline int Population::GetNumberOfGenes() {
  return number_of_genes_;
}

inline Gene* Population::GetGenes() {
  return genes_;
}
#endif /* POPULATION_H */
