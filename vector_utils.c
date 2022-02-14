#include "vector_utils.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

t_vector add(const t_vector* a, const t_vector* b)
{
    t_vector ret;
    ret.x = a->x + b->x;
    ret.y = a->y + b->y;
    ret.z = a->z + b->z;
    return  ret;
}

t_vector sub(const t_vector* a, const t_vector* b)
{
    t_vector ret;
    ret.x = a->x - b->x;
    ret.y = a->y - b->y;
    ret.z = a->z - b->z;
    return  ret;
}

t_vector mult(const t_vector* a, float b)
{
    t_vector ret;
    ret.x = a->x * b;
    ret.y = a->y * b;
    ret.z = a->z * b;
    return  ret;
}

float dot(const t_vector* a, const t_vector* b)
{
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

float squared_norm(const t_vector*v)
{
  return SQR(v->x) + SQR(v->y) + SQR(v->z);
}

float norm(const t_vector *v)
{
  return sqrt(squared_norm(v));
}

float normalize(t_vector* v)
{
  float vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}

void cross(t_vector* o, const t_vector*a, const t_vector*b)
{
  o->x = a->y * b->z - a->z * b->y;
  o->y = a->z * b->x - a->x * b->z;
  o->z = a->x * b->y - a->y * b->x;
}

const char* vector_str(const t_vector*v)
{
  static char buf[1024];
  memset(buf, 0, sizeof(buf));
  sprintf((void*)buf, "(%f, %f, %f)", v->x, v->y, v->z);
  return buf;
}
