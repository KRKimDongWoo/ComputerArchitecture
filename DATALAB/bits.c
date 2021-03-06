/* 
 * CS:APP Data Lab 
 * 
 * <김동우, 2017-1319>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  //Used De Morgan's law to implement nor; ~(x | y) = ~~(~x & ~y) = ~x & ~y
  return (~x) & (~y);
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  //Used De Morgan's law to implement or; x | y = ~(~x & ~y)
  return ~((~x) & (~y));
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //Used the definition of XOR; x ^ y = (x & ~y) | (~x & y)
  //Then, used De Morgan's law to use & instead of |. 
  return ~((~(x & ~y)) & (~(~x & y)));
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  //Create even bit mask (0x55555555)
  //Then, XOR mask and mask-covered original x, so that check if all even bits are 1.
  //Since XOR will return 0xFFFFFFFF if mask-covered original x is 0x55555555 and 0x00000000 otherwise,
  //Used ! to return 0 or 1.
  int mask = 0x00000055;
  mask = (mask << 8) + 0x00000055;
  mask = (mask << 8) + 0x00000055;
  mask = (mask << 8) + 0x00000055;
  x = x & mask;
  x = x ^ mask;
  return !x;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  //By adding 0x00000001, 1s at the last of value of ~x turns to 0,
  //and least significant 0 becomes 1 and other bits remain same.
  //Therefore, if we AND this with original one, we can get mask
  //only covers the LSB.
  int temp = ~x + 0x00000001;
  return temp & x;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //This code checks if first 32-(n-1) bits of x has same value.
  int mask = ~0x00000000;
  int sign = x >> 0x0000001F;
  mask = mask << (n + ~0x00000000);

  return !((x & mask) ^ (sign & mask));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  //Before right shift, it adds bias if x is an negative number.
  //Therefore, the result rounds to 0.
  int sign = x >> 0x0000001F;
  int mask = ~(~(0x00000000) << n);
  int adj = x + (sign & mask);
  return adj >> n;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  //It first checks if the all bits are 0000....0011XXXX, and check if XXXX is from 0000 to 0101.
  int mask = 0x00000030;
  int m1 = ~0x00000000 << 0x00000003;
  int m2 = ~0x00000009;
  x = mask ^ x;

  return !(m1 & x) | !(m2 & x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int max_mask = 0x00000001 << 0x000001F;
  int result = y + (~x) + 0x00000001;
  int x_sign = !(x & max_mask);
  int y_sign = !(y & max_mask);
  int d_sign = x_sign ^ y_sign;

  int a = d_sign & x_sign;
  int b = d_sign & (!x_sign);
  int c = !a & !(result & max_mask);

  return b | c; 
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int mask = ~(((0x00000001 << 0x0000001F) >> n) << 1);

  return mask & (x >> n);

}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  int sum = x + (x << 0x00000002);
  int sign = sum >> 0x0000001F;
  int mask = ~((~0x00000000) << 0x00000003);
  int adj = sum + (sign & mask);
  return adj >> 0x00000003;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int four_mask = 0x00000011;
  int end_mask = 0x00000007;
  int four_count = 0x00000000;
  int all_count = 0x00000000;
  four_mask = 0x00000011 + (four_mask << 0x00000008);
  four_mask = 0x00000011 + (four_mask << 0x00000008);
  four_mask = 0x00000011 + (four_mask << 0x00000008);


  four_count = x & four_mask;
  x = x >> 0x00000001;
  four_count = four_count + (x & four_mask);
  x = x >> 0x00000001;
  four_count = four_count + (x & four_mask);
  x = x >> 0x00000001;
  four_count = four_count + (x & four_mask);


  all_count = four_count & end_mask;
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);
  four_count = four_count >> 0x00000004;
  all_count = all_count + (four_count & end_mask);


  return all_count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int compare = x | ((~x) + 0x00000001);
  return ((~compare) >> 0x0000001F) & 0x00000001;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  x = x ^ (x >> 0x00000010);
  x = x ^ (x >> 0x00000008);
  x = x ^ (x >> 0x00000004);
  x = x ^ (x >> 0x00000002);
  x = x ^ (x >> 0x00000001);
  x = x & 0x00000001;
  return x;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int frac_mask;
  int exp_mask;
  int s_mask;
  int frac;
  int exp;
  int exp_bias;
  int shift;
  int round = 0x00000000;

  s_mask = 0x00000001 << 0x0000001F; //sign mask (0x80000000)
  frac_mask = ~(s_mask >> 0x00000008); //fraction mask (0x007FFFFF)
  exp_mask = ~(s_mask + frac_mask); //exponential mask (0x5F800000)

  exp = uf & exp_mask;
  frac = (uf & frac_mask) + (0x00000001 << 0x00000017); //calculate fraction * 2^x
  exp_bias = (exp >> 0x00000017) + (~0x0000007E); //calculate real exp
  shift = exp_bias + ~0x00000015; //calculate amount to shift the fraction
  
  if(exp_bias & s_mask)
	return 0x00000000; //case 1 : calculated exp is lower then 0; between -1.0 ~ 1.0, round to 0.
  if((exp_bias & ~0x0000001F))
	return s_mask; //case 2 : calculated exp is larger then 0x1F; NaN or overflow, return 0x80000000;
  
  if(shift & s_mask)
	frac = frac >> (~shift + 0x00000001); //left shift case (=2uf)
  else
	frac = frac << shift; //right shift case (=2uf)

  if(frac & 0x00000001)
	round = (frac & 0x00000010) >> 0x00000001; //set difference between round and true value
  
  frac = frac >> 0x00000001; //calculate uf
  frac = frac + round; //complete rounding
  
  if(s_mask & uf)
	return (~frac) + 0x00000001; //negative
  else
	return frac; //positive
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int sign = 0x00000001 << 0x0000001F;
  int frac_mask = ~(sign >> 0x00000008);
  int exp_mask = ~(sign + frac_mask);
  int exp = exp_mask & uf;
  int sum;
  
  if(!(exp_mask ^ exp))
	return uf;
  
  if(!exp)
	return (sign & uf) + (((~sign) & uf) << 0x00000001);

  sum = uf + (0x00000001 << 0x00000017);

  if(!((exp_mask & sum) ^ exp_mask))
	return sum & (~frac_mask);
  
  return sum;
}
