#include "Noise.h"

#include <cmath>

static float lerp(float a, float b, float t) { return a + t * (b - a); }

static float random2(int x, int z) {
  int n = x + z * 57;

  n = (n << 13) ^ n;

  return 1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) /
                    1073741824.0f;
}

static float smoothNoise(float x, float z) {
  int ix = (int)std::floor(x);
  int iz = (int)std::floor(z);

  float fx = x - ix;
  float fz = z - iz;

  float v1 = random2(ix, iz);
  float v2 = random2(ix + 1, iz);
  float v3 = random2(ix, iz + 1);
  float v4 = random2(ix + 1, iz + 1);

  float i1 = lerp(v1, v2, fx);
  float i2 = lerp(v3, v4, fx);

  return lerp(i1, i2, fz);
}

float Noise::noise(float x, float z) { return smoothNoise(x, z); }

float Noise::fbm(float x, float z, int octaves, float persistence,
                 float scale) {
  float total = 0.0f;

  float frequency = scale;

  float amplitude = 1.0f;

  float maxValue = 0.0f;

  for (int i = 0; i < octaves; i++) {
    total += noise(x * frequency, z * frequency) * amplitude;

    maxValue += amplitude;

    amplitude *= persistence;

    frequency *= 2.0f;
  }

  return total / maxValue;
}