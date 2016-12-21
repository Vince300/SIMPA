/*
    ecc Version 1.2  by Paul Flaherty (paulf@stanford.edu)
    Copyright (C) 1993 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


/* ecc.h
	Generator Polynomial Coefficients

	This header file contains an array which defines the generator
	polynomial for the Reed - Solomon Code (255,249,7).  The polynomial
	was hand generated, using a set of calculator programs.
*/

extern unsigned char gfmul (unsigned char, unsigned char);
extern unsigned char gfadd (unsigned char, unsigned char);
extern unsigned char gfinv (unsigned char);
extern unsigned char gfexp (unsigned char, unsigned char);

static unsigned char g[6] =
{
  117, 49, 58, 158, 4, 126};
