#ifndef COMPLEX
#define COMPLEX
class complesso{

	public:
		complesso(double reale, double  ima);
		~complesso();
		double modulo();
	private:
		double real;
		double imm;
};


#endif
