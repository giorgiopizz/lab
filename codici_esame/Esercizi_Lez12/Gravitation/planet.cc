#include "planet.h"

#define CONST_G 6.67e-11

// Ctor
planet::planet(const char* name, double mass, vett2d r, vett2d v)
{
  name_p = name;
  mass_p = mass;
  r_p = r;
  v_p = v;
  
  std::cout << "Costruttore del corpo celeste: " << name_p << std::endl;
  std::cout << "\tMass: " << mass_p << std::endl;
  std::cout << "\tPosition: " << "(" << r_p.getx() << ", " << r_p.gety() << ")" << std::endl;
  std::cout << "\tVelocity: " << "(" << v_p.getx() << ", " << v_p.gety() << ")" << std::endl;
}

double planet::GetX()
{
  double x = r_p.getx();
  return x;
}

double planet::GetY()
{
  double y = r_p.gety();
  return y;
}

std::string planet::GetName()
{
  return name_p;
}


double planet::GetDistance(planet* pl1)
{
  vett2d distance = r_p - pl1->r_p;
  return distance.mod();
}

vett2d planet::GetAccDirection(planet* pl1)
{
  vett2d direction = pl1->r_p - r_p;
  direction.norm();
  return direction;
}

void planet::DoStep(planet* pl1, planet* pl2, double dt)
{
  double fatt_molt;
  vett2d versore;
	
  versore   = planet::GetAccDirection(pl1);	
  fatt_molt = CONST_G*(pl1->mass_p)/pow(planet::GetDistance(pl1),2);
	
  vett2d a1 = versore.scalar_prod(fatt_molt);
	
  versore   = planet::GetAccDirection(pl2);
  fatt_molt = CONST_G*(pl2->mass_p)/pow(planet::GetDistance(pl2),2);
  vett2d a2 = versore.scalar_prod(fatt_molt);
	
  vett2d a_tot = a1 + a2;
	
  // Variazione vettore velocità
  vett2d dv = a_tot.scalar_prod(dt);
  v_p = v_p + dv;
	
  // Variazione vettore posizione
  vett2d dr = v_p.scalar_prod(dt);
  r_p = r_p + dr;

  return;
}
