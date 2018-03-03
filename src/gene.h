#ifndef GENE_H
#define GENE_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "random.h"

struct Gene {
  glm::mat4 transform;
  float opacity;
  glm::vec3 color;
};

Gene CreateGene();

#endif /* GENE_H */
