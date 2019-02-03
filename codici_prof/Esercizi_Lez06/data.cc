#include "data.h"

data::data()
{
  day_p   = 0;
  month_p = 0;
  year_p  = 0;
}

data::data(int dd, int mm, int yyyy)
{
  day_p   = dd;
  month_p = mm;
  year_p  = yyyy;
}

data::data(const data& data)
{
  day_p   = data.day_p;
  month_p = data.month_p;
  year_p  = data.year_p;
}

data& data::operator=(const data& other)
{
  day_p   = other.day_p;
  month_p = other.month_p;
  year_p  = other.year_p;
  return *this;
}

void data::stampa() const
{
  std::cout.fill('0');
  std::cout.width(2);
  std::cout << day_p;
  std::cout << " / ";

  std::cout.fill('0');
  std::cout.width(2);
  std::cout << month_p;
  std::cout << " / ";

  std::cout << year_p << std::endl;
}

void data::imposta(int dd, int mm, int yyyy)
{
  day_p   = dd;
  month_p = mm;
  year_p  = yyyy;
}

bool data::valida() const
{
  int month_length[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if ((year_p % 4 == 0 && year_p % 100 != 0) || year_p % 400 == 0)
    {
      month_length[1] = 29;
    }
  
  if (month_p <= 0 || month_p > 12) return false;
  if (day_p <= 0 || day_p > month_length[month_p-1]) return false;

  return true;
}

bool data::operator==(const data& other) const
{
  return year_p == other.year_p && month_p == other.month_p && day_p == other.day_p;
}

bool data::operator<(const data& other) const
{
  if (*this == other) return false;
  if (year_p > other.year_p) return false;
  if (year_p < other.year_p) return true;
  
  // Se arrivo qui, year_p == other.year_p
  if (month_p > other.month_p) return false;
  if (month_p < other.month_p) return true;
	
  // Se arrivo qui, anche il mese è lo stesso
  if (day_p > other.day_p) return false;
  else return true;
}

bool data::bisestile() const
{
  if ((year_p % 4 == 0 && year_p % 100 != 0) || (year_p % 400 == 0)) return true;
  else return false;
}

int data::diff_giorni(const data other) const
{
  int DayCounter = 0;
  
  data DataPre;
  data DataPost;
  
  // Per prima cosa verifico qual è la data antecedente tra le due
  if (other == (*this)) return 0;
  else if ((*this) < other)
    {
      DataPre  = (*this);
      DataPost = other;	
    }
  else
    {
      DataPre  = other;	
      DataPost = (*this);		
    }
	
  // Conto i giorni da DataPre fino al 31 dicembre di quell'anno
  if (DataPre.bisestile() == true)
    {	
      int month_length[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
      DayCounter += month_length [DataPre.month_p -1] - DataPre.day_p;
      for (int i = DataPre.month_p; i < 12; i++)
	DayCounter += month_length[i];
    }
  else
    {	
      int month_length[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
      DayCounter += month_length [DataPre.month_p -1] - DataPre.day_p;
      for (int i = DataPre.month_p; i < 12; i++)
	DayCounter += month_length[i];	
    }
	
  data DataTemp = DataPre;
	
  while (DataPost.year_p > DataTemp.year_p+1)
    {
      DataTemp.imposta(1, 1, DataTemp.year_p + 1);
      if (DataTemp.bisestile() == true) DayCounter += 366;
      else DayCounter += 365;
    }
	
  // Conto i giorni dal 1 gennaio fino a DataPost
  if (DataPost.bisestile() == true)
    {
      int month_length[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
      DayCounter += DataPost.day_p; 
      for (int i = 0; i < DataPost.month_p-1; i++)
	DayCounter += month_length[i];		
    }
  else
    {	
      int month_length[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
      DayCounter += DataPost.day_p; 
      for (int i = 0; i < DataPost.month_p-1; i++)
	DayCounter += month_length[i];
    }
	
  // Caso in cui DataPre e DataPost siano nello stesso anno
  if (DataPre.year_p == DataPost.year_p)
    {
      if (DataPre.bisestile() == true ) DayCounter -= 366;
      else DayCounter -= 365;
    }
  
  return DayCounter;
}

const char* data::giorno_settimana() const
{
  const char* giorni[] = { "lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica" };
  data Riferimento (25, 12, 2017); // è lunedì!
  
  int diff  = diff_giorni(Riferimento);
  int index = (diff % 7);
  
  if (Riferimento == (*this) || index == 0) return giorni[0];
  else if (Riferimento > (*this)) return giorni[7-index];
  else return giorni[index];
}
