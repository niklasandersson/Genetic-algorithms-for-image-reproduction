#include "gene.h"

Gene CreateGene() {
  Random* random = Random::Instance();

  Gene gene;
  glm::mat4 transform = glm::mat4(1.0f);
  transform = glm::rotate(transform, random->GetRandom() * 360.0f, glm::vec3(0,0,1));
  transform = glm::translate(transform, glm::vec3(2.0f * random->GetRandom() - 1.0f,
        2.0f * random->GetRandom() - 1.0f,
        2.0f * random->GetRandom() - 1.0f));
  transform = glm::scale(transform, glm::vec3(random->GetRandom(),random->GetRandom(),random->GetRandom()));
  gene.transform = transform;
  gene.opacity = random->GetRandom();
  gene.color = glm::vec3(random->GetRandom(),random->GetRandom(),random->GetRandom());

  return gene;
}
