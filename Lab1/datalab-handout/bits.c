/* 
 * CS:APP Data Lab 
 * 
 * <Ducon>
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	int result = ~((~x)|(~y));
	return result;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	int temp = x >> (n << 3);// shift the desired byte to the least significant position
	return (temp & 0xFF);// this operation will yield the least significant byte while set other bits to zero 
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
	int mask = ~(((1 << 31) >> n) << 1);
	return ((x >> n) & mask);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	int aux = 0x55|(0x55<<8);
	aux = (aux<<16)|aux; // now aux is 0x55555555
	int count = (x&aux)+((x>>1)&aux);
	aux = 0x33|(0x33<<8); 
	aux = (aux<<16)|aux; // now aux is 0x33333333
	count = (count&aux)+((count>>2)&aux);
	aux = 0x0F|(0x0F<<8);
	aux = (aux<<16)|aux; // now aux is 0x0F0F0F0F
	count = (count&aux)+((count>>4)&aux);
	aux = (0xFF<<16)|0xFF; // now aux is 0x00FF00FF
	count = (count&aux)+((count>>8)&aux);
	aux = (0xFF<<8)|0xFF; // now aux is 0x0000FFFF
	count = (count&aux)+((count>>16)&aux);
	return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	// because int uses two's complement representation
	int oppositeNumber = ~x+1;
	// except zero, for all other numbers, either their first bit is zero or their opposite number's first bit is zero
	int test = oppositeNumber | x; // now test's first bit must be 1 for numbers except 0
	test = ~test; // now test's first bit is 0 for non-zero numbers
	return (test>>31)&0x01;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31;
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
	int sign = ((x >> 31) & 1);
	int aux = x >> (n + (~0));
	return !(sign + aux);
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
	int bias = (1 << n) - 1;
	int sign = (x >> 31) & 1;
	sign = ~sign + 1;
	bias = bias & sign; // if x is positive, then bias will be set to zero
	// if x is negative, it has to add a bias first
	return (x + bias) >> n; 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return (~x + 1);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	int sign = (x >> 31) & 0x01;
	return !((!x) | sign);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int signY = (y >> 31) & 1;
	int signX = (x >> 31) & 1;
	int difference = y + (~x + 1);
	int sign = (difference >> 31) & 1;
	return (((!(sign)) ^ ((signY ^ sign) & ~(signX ^sign))) | (!(x ^ (~x +1)) ^ !x)); 
	// the first part is used to treat overflow, the second part is used to treat TMIN and zero
	// if signY is different than sign and signX is the same as sign, then it is overflow situation, where we should !sign
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int count = 0;
	count += (!(!(x >> 16))) << 4;
	// if we right shift x by 16, and we still get a non zero, then logx must be greater than 16 (10000)
	// else, if we get a zero, which means logx must be smaller than 16, then we add nothing
	count += (!(!(x >> (count + 8)))) << 3;
	// now comes the smartest part of this algorithm, if we get count = 0 at the previous step, this step we right shift x by 8 bits
	// else, if we get count = 16 at the previous step, now we right shift x by 24 bits, OMG, god like, really beautiful! -> like binary search
	count += (!(!(x >> (count + 4)))) << 2;
	// just like the first two steps
	count += (!(!(x >> (count + 2)))) << 1;
	count += !(!(x >> (count + 1)));
	return count;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	// 1 8 23
	// NaN: 8 for all 1, 23 for non-zero
	if (((0x7F800000 & uf) == 0x7F800000)&&((0x00FFFFFF & uf) != 0x00800000))
		return uf;
	if (((uf >> 31) & 0x01) == 1)
		return ((0x7FFFFFFF) & uf);
	else
		return ((0x80000000) | uf);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	unsigned int sign = x & 0x80000000;
	unsigned int body = x & 0x7FFFFFFF;
	body = body >> 8;
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
	unsigned int exponent = (0xFF & (uf >> 23)); // the exponent part
	unsigned int significant = 0x007FFFFF & uf; // the significant part
	unsigned int sign = 0x80000000 & uf;
	if (exponent == 0x7F800000) // special value
		return uf;
	if (exponent == 0) // denormalized form
		significant += 0x00800000;
	significant += significant;
	if (((significant >> 24) & 1) == 1) // M is equal or larger than 2
	{
		significant = significant >> 1;
		exponent += 1;
	}
	if (((significant >> 23) & 1) == 0)
	{
		int count = 1;
		significant = significant << 1;
		while (((significant >> 23) & 1) == 0)
		{
			significant = significant << 1;
			count += 1;
		}
		exponent -= count;
	}
	exponent = exponent << 23;
	unsigned int result = sign + significant + exponent;
	return result;
}

// gcc -O -o btest btest.c bits.c decl.c tests.c