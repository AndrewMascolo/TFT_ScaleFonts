#ifndef TFT_ScaleFonts_h
#define TFT_ScaleFonts_h

#include <UTFT.h>

class TFT_ScaleFonts 
{
  public:
		TFT_ScaleFonts(UTFT * disp): _Disp(disp){}
    	void	print(char *st, int x, int y, int S = 1, int deg=0);
		void	printNumI(long num, int x, int y, int length=0, byte S = 1, char filler=' ');
		void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, byte S = 1, char filler=' ');
    	void 	printChar(byte c, int x, int y, int S = 1);
		void 	rotateChar(byte c, int x, int y, int pos, int S = 1, int deg=0);
  private:
		char * ftos(float data, byte W, byte D, char * buf);
		unsigned long Pow(long V, byte shift);
  protected:	
    UTFT * _Disp;
};


#endif