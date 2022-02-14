#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

typedef struct s_vector
{
  float x;
  float y;
  float z;
} t_vector;

t_vector add(const t_vector* a, const t_vector* b);
t_vector sub(const t_vector* a, const t_vector* b);
t_vector mult(const t_vector* a, float b);


float dot(const t_vector* a, const t_vector* b);
float squared_norm(const t_vector*v);

float norm(const t_vector *v);
float normalize(t_vector* v);

void cross(t_vector* o, const t_vector*a, const t_vector*b);

const char* vector_str(const t_vector*v);

#endif /* VECTOR_UTILS_H */
