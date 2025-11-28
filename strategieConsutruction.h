#pragma once
#include <string>
#include <vector>
#include "Composante.h"
#include <algorithm>
#include <cmath>
#include "Point.h"
#include <unordered_set>

using namespace std;

class StrategieConstruction {
public:
    virtual ~StrategieConstruction() = default;
    virtual void construireNuages(shared_ptr<Composante> composante) const = 0;
};

class ConstructionCroissante : public StrategieConstruction {
public:
    void construireNuages(shared_ptr<Composante> composante) const override;
};

class ConstructionMinimale : public StrategieConstruction {
public:
    void construireNuages(shared_ptr<Composante> composante) const override;
};