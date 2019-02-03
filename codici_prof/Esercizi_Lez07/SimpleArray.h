#ifndef SIMPLEARR_H
#define SIMPLEARR_H  

template <class T> 
class SimpleArray
{ 
public:
  // Default
  SimpleArray()    
  {
    elementsNum_p = 0;
    elements_p = NULL;
  }

  // Costruttore
  SimpleArray(const int& elementsNum)
  {
    elementsNum_p = elementsNum;
    if (elementsNum_p != 0)
      elements_p = new T[elementsNum];
    else elements_p = NULL;
  }

  // Copy Ctor
  SimpleArray(const SimpleArray& original)
  {
    elementsNum_p = original.elementsNum_p;
    if (elementsNum_p != 0)
      {
	elements_p = new T[elementsNum_p];
	for (int i = 0; i < elementsNum_p; i++)
	  elements_p[i] = original.elements_p[i];
      }
    else elements_p = NULL;
  }

  // Distruttore
  ~SimpleArray()
  {
    delete[] elements_p;
  }
  
  // Metodo che restituisce un elemento dell'array
  T& element(const int& i)
  {
    if (i < elementsNum_p) return elements_p[i];
    else                   return elements_p[elementsNum_p - 1];
  }

  // Overloading operator[]
  T& operator[](const int& i)
  {
    if (i < elementsNum_p) return elements_p[i];
    else                   return elements_p[elementsNum_p - 1];
  }

  // Metodo size
  int size() 
  {
    return elementsNum_p;
  }

  // Metodo push
  void push(const T& elem) 
  {
    elementsNum_p++; // Incrementa il numero degli elementi
    // Alloca lo spazio di memoria per ospitare un array con un l'elemento in più
    T* newAddress = new T[elementsNum_p]; 
		
    for (int i = 0; i < (elementsNum_p-1); i++) // Copia tutti gli elementi dell'array nel nuovo spazio di memoria
      newAddress[i] = elements_p[i]; 
			
    newAddress[elementsNum_p-1] = elem; // Aggiunge in coda l'elemento passato in input

    delete [] elements_p; // Libera la memoria del vecchio array
		
    // Aggiorna l'indirizzo di elements_p in modo che punti all'indirizzo del nuovo array
    elements_p = newAddress;

    return;
  }

  // Metodo pop
  T pop(int i) 
  {
    if (i < elementsNum_p)
      {
	T elem = elements_p[i]; // Elemento da estrarre e passare in uscita
	elementsNum_p--;
	T* newAddress = new T[elementsNum_p];
			
	for (int j = 0; j < i; j++)
	  newAddress[j] = elements_p[j];
				
	for (int j = (i+1); j < (elementsNum_p+1); j++)
	  newAddress[j-1] = elements_p[j];
	delete [] elements_p;
	elements_p = newAddress;
	return elem;
      }
    else
      {
	std::cout << "Errore: non è possibile estrarre l'elemento numero " << i << " dell'array" << std::endl;
	std::cout << "N elementi array = " << elementsNum_p << std::endl;
	return elements_p[0]; // Deve comunque restituire un elemento di tipo T, sceglie ad esempio il primo
      }
  }

private: 
  int elementsNum_p;
  T* elements_p; 
};

#endif
