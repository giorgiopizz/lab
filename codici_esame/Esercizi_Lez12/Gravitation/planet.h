#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <cmath>
#include <string>

#include "vett2d.h"

class planet
{
 public:
  // Ctor
  planet (const char* name, double mass, vett2d r, vett2d v);

  // Metodi
  double GetDistance     (planet* pl1); // Calcola la distanza ripetto a pl1
  vett2d GetAccDirection (planet* pl1); // Calcola il versore che identifica la direzione dell'accelerazione dovuta a pl1
  void   DoStep          (planet* pl1, planet* pl2, double dt); // Aggiorna i vettori posizione e velocità dopo un intervallo di tempo dt,
                         // calcolando l'accelerazione a cui è soggetto il corpo celeste per la forza di gravità esercitata da pl1 e pl2
  double GetX            (); // Restituisce la coordinata x della posizione del pianeta
  double GetY            (); // Restituisce la coordinata y della posizione del pianeta
  std::string GetName    ();
  
 private:
  double mass_p;
  vett2d r_p;
  vett2d v_p;
  std::string name_p;
};

#endif
