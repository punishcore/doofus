#pragma once

class Noise {
public:
  static float noise(float x, float z);

  static float fbm(float x, float z, int octaves, float persistence,
                   float scale);
};