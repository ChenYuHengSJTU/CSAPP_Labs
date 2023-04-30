/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int m = (~x) & y;
  int n = (~y) & x;
  return ~((~m) &  (~n));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // easy
  return (1 << 31);
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // static int n=1;
  // int mask1 = 0xff;
  // int mask2 = mask1 << 8;
  // int mask3 = mask2 << 8;
  // int mask4 = mask3 << 7;
  // int mask = (mask1 | mask2 | mask3 | mask4);
  // return !((~x) & mask);
  // int y = x + x;
  // y = y + 2;
  // x = 0x7fffffff;
  int y = x + x + 2;
  // printf("0x%02x\t%d\t%d\n",x,y,(!y));
  // printf("%d\n",!!(x+1));
  // printf("%d\n",y);
  // printf("%d\n",((!y) & (!!(x + 1))));

  // int z = (!y);
  return ((!y) & (!!(x + 1)));
  // if (n) {
  //   int y = x + x + 2;
  //   --n;
  //   return ((!y) & (!!(x + 1)));
  // }
  // else {
  //   int y = x + x + 2;
  //   return ((!y));
  // }
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // even-numbered bits can also be 1
  int mask1 = 0xaa;
  int mask2 = mask1 << 8;
  int mask3 = mask2 << 8;
  int mask4 = mask3 << 8;
  int mask = (mask1 | mask2 | mask3 | mask4);
  // x & mask clears the impact of even-numbered 1s
  // to judge whether it equals to 0xaaaaaaaa
  return !((x & mask) + (~mask) + 1);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // easy
  return (~x) + 1;
}
//3
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
  // my first method run out of all the 15 available ops

  // int mask1 = 0xff;
  // int mask2 = mask1 << 8;
  // int mask3 = mask2 << 8;
  // int mask4 = mask3 << 8;
  // int mask = (0xc0 | mask2 | mask3 | mask4);

  // int c = (x & mask); 

  // int xx = x & 0x3f;

  // int c1 = !(((xx + (~0x30) +1) >> 31) & (0x1)); // == 0
  // int c2 = !((((~xx) + 1 + 0x39) >> 31) & (0x1)); // == 0

  // return (!c) & (c1 & c2);


  // first step is to fetch the low four bits
  int mask = 0xf;
  int low = mask & x;
  // then judge the upper 28 bits;use ^ to judge whether it equals to 0x30
  int xx = x + (~low) +1;
  int c = xx ^ 0x30;

  // two cases of the low four bits
  // 0xxx or 1000 or 1001
  int mid = low & 0x6;
  int high = low >> 3;

  return (!c) & ((!high) | (!mid));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // use ! to judge , to change odinary nums to 0 or 1
  // after we get 0 or 1
  // for 0 : we can use !x to change it to 1 , then ~x + 1 to get -1 , with
  // all bits of 1
  // for 1 : we can use !!x to change it back to 1, then ~x+1 to get -1
  return ((~(!(!x)) + 1) & y) | ((~(!x) + 1) & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // use ^ to judge equalance
  // to avoid overflow , use the most significant bit to deal with different cases
  int xs = x >> 31;
  int ys = y >> 31;
  return (!(x ^ y)) | (xs & (!ys)) | ((!(xs ^ ys)) & (x + (~y) +1) >> 31);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // we divide all x into three groups: 0,positive,negative
  // for negative and positive,one and only one of the significant bit of x and -x will be 1
  // but for 0,they are all 0
  // so we add 1 ,keep the trait for positive and negative numbers,but change the case of 0
  // last,for non-zero : xs == 0 && negxs == 1 || xs == 1 && negxs == 0
  // for zero : xs == 1 || negxs == 1 
  int xs = (((x >> 31) & 0x1) + 1) & 0x1 ;
  int negxs = (((((~x) + 1) >> 31) & 0x1) + 1) & 0x1 ;
  return xs & negxs;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int isZero = !x;
  int mask = ((!!x) << 31) >> 31;

  int flag = x >> 31;

  x = ((~flag) & x) | (flag & (~x));

  int bit_16, bit_8, bit_4, bit_2, bit_1, bit_0;

  bit_16 = (!((!!(x >> 16)) ^ 0x1)) << 4;
  x >>= bit_16;

  bit_8 = (!((!!(x >> 8)) ^ 0x1)) << 3;
  x >>= bit_8;

  bit_4 = (!((!!(x >> 4)) ^ 0x1)) << 2;
  x >>= bit_4;

  bit_2 = (!((!!(x >> 2)) ^ 0x1)) << 1;
  x >>= bit_2;

  bit_1 = (!((!!(x >> 1)) ^ 0x1));
  x >>= bit_1;

  bit_0 = x;

  int res = bit_16 + bit_8 + bit_4 + bit_2 + bit_1 + bit_0 + 1;

  return (isZero | (mask & res));
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int expmask = 0xff << 23;
  int s = uf >> 31;
  int fmask1 = 0xff;
  int fmask2 = fmask1 << 8;
  int fmask3 = fmask2 << 7;
  int fmask = fmask1 | fmask2 | fmask3;
  int frac = uf & fmask;
  int exp = (uf & expmask) >> 23;
  if(exp && (exp - 0xff))
    exp = exp + 1;
  if(!exp)
    frac = frac << 1;
  uf = (s << 31) | (exp << 23) | (frac);
  return uf;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
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
int floatFloat2Int(unsigned uf) {
  int expmask = 0xff << 23;
  int exp = (uf & expmask) >> 23;
  
  int s = uf >> 31;
  
  int fmask1 = 0xff;
  int fmask2 = fmask1 << 8;
  int fmask3 = fmask2 << 7;
  int fmask = fmask1 | fmask2 | fmask3;
  int frac = uf & fmask;

  int M;
  int E;
  int bias = 127;

  if(exp == 0xff){
    return 0x80000000u;
  }

  if(exp && (exp - 0xff)){
    M = 1 << 23 | frac;
    E = exp - bias;
  }
  else{
    M = frac;
    E = 1 - bias;
  }

  int res;
  if(E > 23){
    res = M << E;
    // do not forget this anything out of range
    if(E >= 8) return 0x80000000u;
  }
  else if(E == 23) res = M;
  else{
    int e = 23 - E;
    if(e >= 24) return 0;
    res = M >> (23 - E);
  }
  if(s) return -res;
  return res;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
#include<stdio.h>
unsigned floatPower2(int x) {
  int exp;
  int frac;
  int s = 0;
  int res = 0;

  if(x >= 128){
    exp = 0xff;
    frac = 0;
    s = 0;
  }
  else if(x < -126 - 23){
    frac = 0;
    exp = 0;
  }
  else if(x >= -126 - 23 && x <= -127){
    exp = 0;
    frac = 1 << (x - (-126 - 23));
  }
  else {
    frac = 0;
    exp = 127 + x;
  }

  res = (exp << 23) | (frac) | (s << 31);

  return res;
}
