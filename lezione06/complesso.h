#ifndef complesso_h
#define complesso_h

class complesso
{
public:
	complesso();
	complesso(const double& re, const double& im);
	complesso(const complesso& original);
	~complesso();
	
	complesso& operator = (const complesso& original);
	complesso& operator = (const double& original);
	complesso operator + (const complesso& original);
	complesso operator - (const complesso& original);
	complesso operator * (const complesso& original);
	complesso operator / (const complesso& original);
	complesso operator ^ (const int& potenza);
	
	double Re() const;
	double Im() const;
	double Mod() const;
	double Theta() const;
	double Print() const;
	
private:
	double re_p;
	double im_p;
};
#endif
