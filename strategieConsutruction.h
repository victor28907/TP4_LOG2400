#pragma once
#include <string>
#include <vector>
#include "Composante.h"

using namespace std;
/*
class StrategieConstruction {
public:
    virtual ~StrategieConstruction() = default;
    virtual void construireNuages(vector<string> (&textures)[3], vector<Point>& points) const = 0;
};

class ConstructionCroissante : public StrategieConstruction {
public:
    void construireNuages(vector<string> (&textures)[3], vector<Point>& points) const override;
};

class ConstructionMinimale : public StrategieConstruction {
public:
    void construireNuages(vector<string> (&textures)[3], vector<Point>& points) const override;
};*/

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