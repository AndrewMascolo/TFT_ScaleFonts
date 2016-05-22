#ifndef TFT_ScaleFonts_h
#define TFT_ScaleFonts_h

#include <UTFT.h>
#define PORTRAIT 0
#define LANDSCAPE 1

class TFT_ScaleFonts 
{
  public:
		TFT_ScaleFonts(UTFT * disp): _Disp(disp){ TextBounds(0,0,_Disp->disp_x_size,_Disp->disp_y_size); }
		void	TextBounds(int x, int y, int x2, int y2);
    	void	print(char *st, int x, int y, int S = 1, int deg=0);
		void	printNumI(long num, int x, int y, int length=0, byte S = 1, char filler=' ');
		void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, byte S = 1, char filler=' ');
    	void 	printChar(byte c, int x, int y, int S = 1);
		void 	rotateChar(byte c, int x, int y, int pos, int S = 1, int deg=0);
  private:
		char * ftos(float data, byte W, byte D, char * buf);
		unsigned long Pow(long V, byte shift);
		int Bound_X, Bound_Y, Bound_X2, Bound_Y2;
  protected:	
    UTFT * _Disp;
};


#endif