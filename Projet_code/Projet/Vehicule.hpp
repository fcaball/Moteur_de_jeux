#ifndef OBJECTLOADED
#define OBJECTLOADED
#include "ObjectLoaded.hpp"
#endif
#include <common/objloader.hpp>
using namespace glm;

class Vehicule : public ObjectLoaded
{
private:
    /* data */
    vec3 vitesse;
    float vitesseMax ;
    float tpsMax ;
    int turn;
    bool stop;

public:
    Vehicule(float vitessemax=0, float timemax=0,vec3 speed = vec3(0, 0, 0));
    ~Vehicule();
    void setSpeed(vec3 speed);
    void addSpeed(vec3 speed);
    void mulSpeed(vec3 speed);
    vec3 getSpeed();
    void setTurn(int turn);
    int getTurn();
    void setStop(bool stop);
    bool getStop();
    void setVMax(float vMax);
    float getVMax();
    void setTMax(float t);
    float getTMax();
};

Vehicule::Vehicule(float vitessemax, float timemax,vec3 speed)
{
    this->vitesse = speed;
    this->turn = 0;
    this->stop = false;
    this->vitesseMax=vitessemax;
    this->tpsMax=timemax;
}



Vehicule::~Vehicule()
{
}

void Vehicule::setSpeed(vec3 speed)
{
    this->vitesse = speed;
}

void Vehicule::addSpeed(vec3 speed)
{
    this->vitesse += speed;
}

void Vehicule::mulSpeed(vec3 speed)
{
    this->vitesse *= speed;
}

vec3 Vehicule::getSpeed()
{
    return this->vitesse;
}

void Vehicule::setTurn(int turn)
{
    this->turn = turn;
}

int Vehicule::getTurn()
{
    return this->turn;
}


void Vehicule::setStop(bool stop)
{
    this->stop = stop;
}

bool Vehicule::getStop()
{
    return this->stop;
}

void Vehicule::setVMax(float vMax)
{
    vitesseMax = vMax ;
}
    
float Vehicule::getVMax()
{
    return vitesseMax ;
}
    
void Vehicule::setTMax(float t)
{
    tpsMax = t ;
}

float Vehicule::getTMax()
{
    return tpsMax ;
}