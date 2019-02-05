//data.cc
#include "data.h"
#include <iostream>

data::data(){
        year_p=0;
        month_p=0;
        day_p=0;
}
data::data(int day, int month, int year){
        year_p=year;
        month_p=month;
        day_p=day;
}
data::data(const data& other){
        year_p=other.year_p;
        month_p=other.month_p;
        day_p=other.day_p;
}
data& data::operator=(const data& other){
        year_p=other.year_p;
        month_p=other.month_p;
        day_p=other.day_p;
        return *this;
}
bool data::operator==(const data& other) const{
        if(year_p==other.year_p && month_p==other.month_p && day_p==other.day_p)
                return true;

        else
                return false;
}
bool data::operator<(const data& other) const{
        if(year_p<other.year_p||(year_p==other.year_p&&month_p<other.month_p)||(year_p==other.year_p&&month_p==other.month_p&&day_p<other.day_p)){
                return true;
        }
        else{
                return false;
        }
        //sfrutto diff_giorni per vedere quale è maggiore
        //se la differenza tra this e other è negativa allora return true
}
/*
void stampa() à scrive a terminale la data nel formato GG/MM/AAAA
l                                void imposta(int day, int month, int year) à reimposta giorno, mese e anno della data secondo i parametri di input
l        bool valida() à restituisce TRUE/FALSE a seconda che la data inserita sia formalmente corretta oppure no (e.g. 34 febbraio 2018)
l        int diff_giorni(const data other) à calcola il numero di giorni che intercorrono tra la data inserita e un’altra data, passata come parametro di input
l        bool Bisestile() à restituisce TRUE/FALSE a seconda che l’anno della data inserita sia bisestile oppure no. Un anno è bisestile se è divisibile per 4 ma non per 100, oppure se è divisibile per 400: ad esempio il 2000 era bisestile ma il 1900 no
l        const char* giorno_settimana() à restituisce il giorno della settimana (si consiglia di sfruttare il metodo diff_giorni per calcolare il numero di giorni trascorsi rispetto ad una data di riferimento: ad esempio sappiamo che il 25/12/2017 sarà un lunedì)
*/
void data::stampa() const{
        std::cout<<"La data è: "<<day_p<<"/"<<month_p<<"/"<<year_p<<std::endl;
}
void data::imposta(int day, int month, int year){
        year_p=year;
        month_p=month;
        day_p=day;
}

bool data::valida() const{
        switch (month_p) {
                case 1:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
                case 2:
                        if(Bisestile()){
                                //massimo 29
                                if(day_p<=29)
                                        return true;
                                else
                                        return false;
                        }
                        else{
                                //massimo 28
                                if(day_p<=28)
                                        return true;
                                else
                                        return false;
                        }
                case 3:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
                case 4:
                        //massimo 30
                        if(day_p<=30)
                                return true;
                        else
                                return false;
                case 5:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
                case 6:
                        //massimo 30
                        if(day_p<=30)
                                return true;
                        else
                                return false;
                case 7:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
                case 8:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
                case 9:
                        //massimo 30
                        if(day_p<=30)
                                return true;
                        else
                                return false;
                case 10:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
                case 11:
                        //massimo 30
                        if(day_p<=30)
                                return true;
                        else
                                return false;
                case 12:
                        //massimo 31
                        if(day_p<=31)
                                return true;
                        else
                                return false;
        }
}
bool data::Bisestile() const{
        if(year_p%4==0&&year_p%100!=0){
                //anno non secolare bisestile
                return true;
        }
        else if(year_p%400==0){
                //anno secolare bisestile
                return true;
        }
        else{
                return false;
        }
}
int data::diff_giorni(const data other) const{
        //converto in giorni la data
        int this_tot=year_p*365+month_p*30+day_p;
        int other_tot=other.year_p*365+other.month_p*30+day_p;
}
const char* data::giorno_settimana() const{
        
}
