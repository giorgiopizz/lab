#include "complesso.h"
#include <cmath>
#include <iostream>
complesso::complesso(){
	re_p=0;
	im_p=0;
}
complesso::complesso(const double& re, const double& im){
	re_p=re;
	im_p=im;
}
complesso::complesso(const complesso& original){
	*(this)=original;
}
complesso::~complesso(){
    std::cout << "Eliminato" << std::endl;
}
complesso& complesso::operator = (const complesso& original){
	re_p=original.re_p;
	im_p=original.im_p;
	return *(this);
}
complesso& complesso::operator = (const double& original){
	re_p=original;
	return *(this);
}
complesso complesso::operator + (const complesso& original){
	complesso Sum(original);
	Sum.re_p+=re_p;
	Sum.im_p+=im_p;
	return Sum;
}
complesso complesso::operator - (const complesso& original){
	complesso Sub;
	Sub.re_p=re_p-original.re_p;
	Sub.im_p=im_p-original.im_p;
	return Sub;
}
complesso complesso::operator * (const complesso& original){
	//il prodotto di due complessi non è il prodotto tra la parte reale 
	//e la parte immaginaria ma un mix: (a+ib)*(c+id)=(ac-bd)+i(bc+ad)
	complesso Prod;
	Prod.re_p=(re_p*original.re_p-im_p*original.im_p);
	Prod.im_p=(im_p*original.re_p+re_p*original.im_p);
	return Prod;
}
complesso complesso::operator / (const complesso& original){
	//il rapporto tra complessi è (a+ib)/(c+id)=(a+ib)*(c-id)/(c^2+d^2)=
	//=(ac+bd)/mod+i(bc-ad)
	complesso Div;
	Div.re_p=(re_p*original.re_p+im_p*original.im_p)/original.Mod();
	Div.im_p=(im_p*original.re_p-re_p*original.im_p)/original.Mod();
	return Div;
}
complesso complesso::operator ^ (const int& potenza){
	complesso pot;
	pot.re_p=pow((*this).Mod(),potenza)*cos(potenza*(*this).Theta());
	pot.im_p=pow((*this).Mod(),potenza)*sin(potenza*(*this).Theta());
	return pot;
}
double complesso::Re() const{
	return re_p;
}
double complesso::Im() const{
	return im_p;
}
double complesso::Mod() const{
	return sqrt(pow(re_p,2)+pow(im_p,2));
}
double complesso::Theta() const{
	return atan(im_p/re_p);
}
double complesso::Print() const{
	std::cout << re_p << "+i" << im_p<<std::endl;
	return re_p+im_p;
}
	
