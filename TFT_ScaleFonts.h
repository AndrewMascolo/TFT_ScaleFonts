#ifndef TFT_ScaleFonts_h
#define TFT_ScaleFonts_h

/*
The MIT License (MIT)
Copyright (c) 2016 Andrew Mascolo Jr
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
