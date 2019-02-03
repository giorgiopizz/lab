#ifndef DATA_H
#define DATA_H

#include <iostream>

class data
{
public:
  data ();
  data (int day, int month, int year);
  data (const data& other);
  data& operator= (const data& other);
  bool operator== (const data& other) const;
  bool operator<  (const data& other) const;

  void stampa  () const;
  void imposta (int day, int month, int year);

  bool valida     () const;
  bool bisestile  () const;
  int diff_giorni (const data other) const; 
  const char* giorno_settimana () const; 

  // Inline implementation
  bool operator!= (const data& other) const { return !this->operator==(other); }
  bool operator>  (const data& other) const { return other.operator<(*this);   }
  bool operator<= (const data& other) const { return !this->operator>(other);  }
  bool operator>= (const data& other) const { return !this->operator<(other);  }

private:
  int year_p, month_p, day_p;
};

#endif
