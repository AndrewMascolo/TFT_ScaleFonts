#include "TFT_ScaleFonts.h"

void TFT_ScaleFonts::TextBounds(int x, int y, int x2, int y2)
{
  Bound_X = x;
  Bound_Y = y;
  Bound_X2 = x2;
  Bound_Y2 = y2;
}

void TFT_ScaleFonts::printChar(byte c, int x, int y, int S)
{
  if (S < 1) S = 1;

  if (S == 1)
  {
    _Disp->printChar(c, x, y);
    return;
  }

  word temp;
  unsigned char ch;

  cbi(_Disp->P_CS, _Disp->B_CS);

  temp = ((c - _Disp->cfont.offset) * ((_Disp->cfont.x_size / 8) * _Disp->cfont.y_size)) + 4;

  for (int Y = 0; Y < ((_Disp->cfont.x_size / 8) * _Disp->cfont.y_size)*S; Y += (_Disp->cfont.x_size / 8) * S)
  {
    for (byte s = 0; s < S; s++)
    {
      _Disp->setXY(x, y + s + (Y / (_Disp->cfont.x_size / 8)), x + _Disp->cfont.x_size * S - 1, y + s + (Y / (_Disp->cfont.x_size / 8)));

      for (int xx = (_Disp->cfont.x_size / 8) - 1; xx >= 0; xx--)
      {
        if (_Disp->orient == LANDSCAPE)
        {
          ch = pgm_read_byte(&_Disp->cfont.font[temp + xx]);
          for (byte i = 0; i < (8 * S) ; i++)
          {
            if ((ch & (1 << (i / S))) != 0)
            {
              _Disp->setPixel((_Disp->fch << 8) | _Disp->fcl);
            }
            else
            {
              if (!_Disp->_transparent)
                _Disp->setPixel((_Disp->bch << 8) | _Disp->bcl);
            }
          }
        }
        else
        {
          ch = pgm_read_byte(&_Disp->cfont.font[temp + 1 - xx]);
          for (byte i = (8 * S) - 1; i > 0 ; i--)
          {
            if ((ch & (1 << (i / S))) != 0)
            {
              _Disp->setPixel((_Disp->fch << 8) | _Disp->fcl);
            }
            else
            {
              if (!_Disp->_transparent)
                _Disp->setPixel((_Disp->bch << 8) | _Disp->bcl);
            }
          }
        }
      }
    }
    temp += (_Disp->cfont.x_size / 8);
  }

  sbi(_Disp->P_CS, _Disp->B_CS);
  _Disp->clrXY();
}

#if 1
void TFT_ScaleFonts::rotateChar(byte c, int x, int y, int pos, int S, int deg)
{
  if (S < 1) S = 1;

  if ((S == 1) && (deg == 0))
  {
    _Disp->printChar(c, x, y);
    return;
  }
  else if (S == 1)
  {
    _Disp->rotateChar(c, x, y, pos, deg);
    return;
  }
  else if (deg == 0)
  {
    printChar(c, x, y, S);
    return;
  }

  byte i, j, ch;
  word temp;
  int newx, newy;
  double radian;
  radian = deg * 0.0175;

  cbi(_Disp->P_CS, _Disp->B_CS);

  temp = ((c - _Disp->cfont.offset) * ((_Disp->cfont.x_size / 8) * _Disp->cfont.y_size)) + 4;
  for (j = 0; j < _Disp->cfont.y_size * S; j += S)
  {
    for (int zz = 0; zz < (_Disp->cfont.x_size / 8)*S; zz += S)
    {
      ch = pgm_read_byte(&_Disp->cfont.font[temp + (zz / S)]);
      for (i = 0; i < (8 * S); i++)
      {
        for (int s = 0; s < S; s++)
        {
          newx = x + (((i + (zz * 8) + (pos * _Disp->cfont.x_size)) * cos(radian)) - ((j + s) * sin(radian)));
          newy = y + (((j + s) * cos(radian)) + ((i + (zz * 8) + (pos * _Disp->cfont.x_size)) * sin(radian)));

          _Disp->setXY(newx, newy, newx + 1, newy + 1);

          if ((ch & (1 << (7 - (i / S)))) != 0)
          {
            _Disp->setPixel((_Disp->fch << 8) | _Disp->fcl);
          }
          else
          {
            if (!_Disp->_transparent)
              _Disp->setPixel((_Disp->bch << 8) | _Disp->bcl);
          }
        }
      }
    }
    temp += (_Disp->cfont.x_size / 8);
  }
  sbi(_Disp->P_CS, _Disp->B_CS);
  _Disp->clrXY();
}

void TFT_ScaleFonts::print(char *st, int x, int y, int S, int deg)
{
  if (S < 1) S = 1;

  if (S == 1)
  {
    _Disp->print(st, x, y, deg);
    return;
  }

  int stl, i;

  stl = strlen(st);

  if (_Disp->orient == PORTRAIT)
  {
    if (x == RIGHT)
      x = ((Bound_X2 - Bound_X)/*_Disp->disp_x_size*/ + 1) - (stl * _Disp->cfont.x_size * S);
    if (x == CENTER)
      x = (((Bound_X2 - Bound_X) + 1) - (stl * _Disp->cfont.x_size * S)) / 2;
  }
  else
  {
    if (x == RIGHT)
      x = ((Bound_Y2 - Bound_Y) + 1) - (stl * _Disp->cfont.x_size * S);
    if (x == CENTER)
      x = (((Bound_Y2 - Bound_Y) + 1) - (stl * _Disp->cfont.x_size * S)) / 2;
  }

  for (i = 0; i < stl; i++)
    if (deg == 0)
      printChar(*st++, x + (i * (_Disp->cfont.x_size * S)), y, S);
    else
      rotateChar(*st++, x, y, i * S, S, deg);
}

void TFT_ScaleFonts::printNumI(long num, int x, int y, int length, byte S, char filler)
{
  if (S < 1) S = 1;

  if (S == 1)
  {
    _Disp->printNumI(num, x, y, length, filler);
    return;
  }

  char buf[25];
  char st[27];
  boolean neg = false;
  int c = 0, f = 0;

  if (num == 0)
  {
    if (length != 0)
    {
      for (c = 0; c < (length - 1); c++)
        st[c] = filler;
      st[c] = 48;
      st[c + 1] = 0;
    }
    else
    {
      st[0] = 48;
      st[1] = 0;
    }
  }
  else
  {
    if (num < 0)
    {
      neg = true;
      num = -num;
    }

    while (num > 0)
    {
      buf[c] = 48 + (num % 10);
      c++;
      num = (num - (num % 10)) / 10;
    }
    buf[c] = 0;

    if (neg)
    {
      st[0] = 45;
    }

    if (length > (c + neg))
    {
      for (int i = 0; i < (length - c - neg); i++)
      {
        st[i + neg] = filler;
        f++;
      }
    }

    for (int i = 0; i < c; i++)
    {
      st[i + neg + f] = buf[c - i - 1];
    }
    st[c + neg + f] = 0;

  }

  print(st, x, y, S);
}

void TFT_ScaleFonts::printNumF(double num, byte dec, int x, int y, char divider, int length, byte S, char filler)
{
  if (S < 1) S = 1;

  if (S == 1)
  {
    _Disp->printNumF(num, dec, x, y, divider, length, filler);
    return;
  }

  char st[27];
  boolean neg = false;

  if (dec < 1)
    dec = 1;
  else if (dec > 5)
    dec = 5;

  if (num < 0)
    neg = true;

  ftos(num, length, dec, st);

  if (divider != '.')
  {
    for (int i = 0; i < sizeof(st); i++)
      if (st[i] == '.')
        st[i] = divider;
  }

  if (filler != ' ')
  {
    if (neg)
    {
      st[0] = '-';
      for (int i = 1; i < sizeof(st); i++)
        if ((st[i] == ' ') || (st[i] == '-'))
          st[i] = filler;
    }
    else
    {
      for (int i = 0; i < sizeof(st); i++)
        if (st[i] == ' ')
          st[i] = filler;
    }
  }

  print(st, x, y, S);
}

char * TFT_ScaleFonts::ftos(float data, byte W, byte D, char * buf)
{
  byte shf = 0;
  if (data < 0)
  {
    data *= -1;
    shf = 1;
    buf[0] = '-';
  }
  long Wdata = data, tmp;
  float dec = data - long(data);

  // get the first whole number and convert it
  buf[0 + shf] = Wdata / Pow(10, W - 1) + '0';
  tmp = Wdata % Pow(10, W - 1);

  //now get the rest of the whole numbers
  for (byte i = 1; i < W; i++)
  {
    long factor = Pow(10, W - 1 - i);
    buf[i + shf] = (tmp / factor) + '0';
    tmp %= factor;
  }

  buf[W + shf] = '.'; // add the decimal point

  // now do the decimal numbers
  for (byte i = 0; i < D; i++)
  {
    dec *= 10;
    buf[W + i + 1 + shf] = (long(dec) % 10) + '0';
  }
  // don't forget the NULL terminator
  buf[W + D + 1 + shf] = NULL;
  return buf;
}

unsigned long TFT_ScaleFonts::Pow(long V, byte shift)
{
  unsigned long Val = 1;
  while (shift-- != 0)
    Val *= V;

  return Val;
}

#endif