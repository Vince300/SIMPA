extern unsigned char gfmul (unsigned char, unsigned char);
extern unsigned char gfadd (unsigned char, unsigned char);
extern unsigned char gfinv (unsigned char);
extern unsigned char gfexp (unsigned char, unsigned char);
#pragma external gfmul
#pragma external gfadd
#pragma external gfinv
#pragma external gfexp

unsigned char v2e[256] =
{
  255, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75,
  4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113,
  5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69,
  29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166,
  6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136,
  54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64,
  30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61,
  202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87,
  7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24,
  227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46,
  55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97,
  242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162,
  31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246,
  108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90,
  203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215,
79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175};

rsdecode (code, mesg, errcode)

     unsigned char code[255], mesg[249];
     int *errcode;
{

  unsigned char syn[7], deter, z[4], e0, e1, e2, n0, n1, n2, w0, w1, w2,
    x0, x[3];
  int i, sols;

  *errcode = 0;

  for (i = 0; i < 249; i++)
    mesg[i] = code[254 - i];

  syndrome (code, syn);

  if (syn[0] == 0)
    return;

  errnum (syn, &deter, errcode);

  if (*errcode == 4)
    return;

  switch (*errcode)
    {

    case 1:

      x0 = gfmul (syn[2], gfinv (syn[1]));
      w0 = gfmul (gfexp (syn[1], 2), gfinv (syn[2]));
      if (v2e[x0] > 5)
	mesg[254 - v2e[x0]] = gfadd (mesg[254 - v2e[x0]], w0);
      return;

    case 2:

      z[0] = gfmul (gfadd (gfmul (syn[1], syn[3]), gfexp (syn[2], 2)), gfinv (deter));
      z[1] = gfmul (gfadd (gfmul (syn[2], syn[3]), gfmul (syn[1], syn[4])), gfinv (deter));
      z[2] = 1;
      z[3] = 0;

      polysolve (z, x, &sols);
      if (sols != 2)
	{
	  *errcode = 4;
	  return;
	}

      w0 = gfmul (z[0], syn[1]);
      w1 = gfadd (gfmul (z[0], syn[2]), gfmul (z[1], syn[1]));
      n0 = 254 - v2e[gfinv (x[0])];
      n1 = 254 - v2e[gfinv (x[1])];
      e0 = gfmul (gfadd (w0, gfmul (w1, x[0])), gfinv (z[1]));
      e1 = gfmul (gfadd (w0, gfmul (w1, x[1])), gfinv (z[1]));

      if (n0 < 249)
	mesg[n0] = gfadd (mesg[n0], e0);
      if (n1 < 249)
	mesg[n1] = gfadd (mesg[n1], e1);
      return;

    case 3:

      z[3] = 1;
      z[2] = gfmul (syn[1], gfmul (syn[4], syn[6]));
      z[2] = gfadd (z[2], gfmul (syn[1], gfmul (syn[5], syn[5])));
      z[2] = gfadd (z[2], gfmul (syn[5], gfmul (syn[3], syn[3])));
      z[2] = gfadd (z[2], gfmul (syn[3], gfmul (syn[4], syn[4])));
      z[2] = gfadd (z[2], gfmul (syn[2], gfmul (syn[5], syn[4])));
      z[2] = gfadd (z[2], gfmul (syn[2], gfmul (syn[3], syn[6])));
      z[2] = gfmul (z[2], gfinv (deter));

      z[1] = gfmul (syn[1], gfmul (syn[3], syn[6]));
      z[1] = gfadd (z[1], gfmul (syn[1], gfmul (syn[5], syn[4])));
      z[1] = gfadd (z[1], gfmul (syn[4], gfmul (syn[3], syn[3])));
      z[1] = gfadd (z[1], gfmul (syn[2], gfmul (syn[4], syn[4])));
      z[1] = gfadd (z[1], gfmul (syn[2], gfmul (syn[3], syn[5])));
      z[1] = gfadd (z[1], gfmul (syn[2], gfmul (syn[2], syn[6])));
      z[1] = gfmul (z[1], gfinv (deter));

      z[0] = gfmul (syn[2], gfmul (syn[3], syn[4]));
      z[0] = gfadd (z[0], gfmul (syn[3], gfmul (syn[2], syn[4])));
      z[0] = gfadd (z[0], gfmul (syn[3], gfmul (syn[5], syn[1])));
      z[0] = gfadd (z[0], gfmul (syn[4], gfmul (syn[4], syn[1])));
      z[0] = gfadd (z[0], gfmul (syn[3], gfmul (syn[3], syn[3])));
      z[0] = gfadd (z[0], gfmul (syn[2], gfmul (syn[2], syn[5])));
      z[0] = gfmul (z[0], gfinv (deter));

      polysolve (z, x, &sols);
      if (sols != 3)
	{
	  *errcode = 4;
	  return;
	}

      w0 = gfmul (z[0], syn[1]);
      w1 = gfadd (gfmul (z[0], syn[2]), gfmul (z[1], syn[1]));
      w2 = gfadd (gfmul (z[0], syn[3]), gfadd (gfmul (z[1], syn[2]), gfmul (z[2], syn[1])));

      n0 = 254 - v2e[gfinv (x[0])];
      n1 = 254 - v2e[gfinv (x[1])];
      n2 = 254 - v2e[gfinv (x[2])];

      e0 = gfadd (w0, gfadd (gfmul (w1, x[0]), gfmul (w2, gfexp (x[0], 2))));
      e0 = gfmul (e0, gfinv (gfadd (z[1], gfexp (x[0], 2))));
      e1 = gfadd (w0, gfadd (gfmul (w1, x[1]), gfmul (w2, gfexp (x[1], 2))));
      e1 = gfmul (e1, gfinv (gfadd (z[1], gfexp (x[1], 2))));
      e2 = gfadd (w0, gfadd (gfmul (w1, x[2]), gfmul (w2, gfexp (x[2], 2))));
      e2 = gfmul (e2, gfinv (gfadd (z[1], gfexp (x[2], 2))));

      if (n0 < 249)
	mesg[n0] = gfadd (mesg[n0], e0);
      if (n1 < 249)
	mesg[n1] = gfadd (mesg[n1], e1);
      if (n2 < 249)
	mesg[n2] = gfadd (mesg[n2], e2);

      return;

    default:

      *errcode = 4;
      return;

    }

}

/*
volatile int code;
unsigned char arr1[255];
unsigned char arr2[249];
volatile unsigned char res;

void main()
{
   rscode ( arr1, arr2, &code );
   res = arr1[5];
   res = arr2[14];
}
*/
 
