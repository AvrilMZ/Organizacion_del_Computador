/*
 * CS:APP Data Lab
 *
 * Avril Victoria Morfeo Zerbi - 112563
 * Dante Raddavero Sánchez - 112466
 * Nicolás Valencia - 112776
 */

#if 0
/*
 --------------------------------- RULES ---------------------------------

  - Only this file can be modified.
  - Do not include <stdio.h> because it causes issues with the compiler's DLC.

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

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

--------------------------------- FLOATING POINT RULES ---------------------------------

  - You are allowed to use looping and conditional control.
  - You are allowed to use both ints and unsigneds.
  - You can use arbitrary integer and unsigned constants.
  - You can use any arithmetic, logical, or comparison operations on int or unsigned data.

  You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.
 */
#endif

// --------------------------------- 1 ---------------------------------
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y)
{
	return ~(~x & ~y);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x)
{
	x = ~x;
	x = x ^ (x >> 16);
	x = x ^ (x >> 8);
	x = x ^ (x >> 4);
	x = x ^ (x >> 2);
	x = x ^ (x >> 1);
	return x & 1;
}

/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y)
{
	return (~x & ~y);
}

/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
	return ~(~(~x & y) & ~(x & ~y));
}

// --------------------------------- 2 ---------------------------------
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void)
{
	int m = 0x55; // 0x55 = 01010101, bits pares
	m = m << 8 | m;
	m = m << 16 | m;
	return m;
}

/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x)
{
	int m = 0xAA; // 0xAA = 10101010, bits impares
	m = m << 8 | m;
	m = m << 16 | m;
	return !!(x & m);
}

/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m)
{
	int shift_n = n << 3;
	int shift_m = m << 3;

	int byte_n = (x >> shift_n) & 0xFF;
	int byte_m = (x >> shift_m) & 0xFF;

	int mask_n = 0xFF << shift_n;
	int mask_m = 0xFF << shift_m;
	int mask = ~(mask_n | mask_m); // Máscara con 0s en los bytes a reemplazar

	int clean_x = x & mask; // Limpia los bytes n y m en x

	int new_byte_n = byte_m << shift_n;
	int new_byte_m = byte_n << shift_m;

	return clean_x | new_byte_n | new_byte_m;
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
int fitsBits(int x, int n)
{
	int shift = 32 + (~n + 1);
	int shift_x = (x << shift) >> shift; // Recorta a n bits y extiende el signo
	return !(x ^ shift_x);		     // x == shift_x
}

/*
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void)
{
	int m = 0xAA; // 0xAA = 10101010, bits impares
	m = m << 8 | m;
	m = m << 16 | m;
	return m;
}

/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x)
{
	int is_zero = !!x;
	int is_negative = x >> 31; // -1 si es negativo, 0 si no
	return is_zero | is_negative;
}

// --------------------------------- 3 ---------------------------------
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y)
{
	int x_sign = x >> 31;
	int y_sign = y >> 31;
	int result_sign = (x + y) >> 31;
	int overflow = ~(x_sign ^ y_sign) & (x_sign ^ result_sign);
	return !overflow;
}

/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit)
{
	int mask_high = (2 << highbit) + (~0); // '(~0)' = -1 en CA2
	int mask_low = (1 << lowbit) + (~0);
	return mask_high & ~mask_low;
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
	int mask = (!!x << 31) >> 31; // 0xFFFFFFFF si x distinto de 0, 0 si x igual a 0
	return (mask & y) | (~mask & z);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
	int m1 = 0x55 | (0x55 << 8); // 01010101
	int m2 = 0x33 | (0x33 << 8); // 00110011
	int m4 = 0x0F | (0x0F << 8); // 00001111

	m1 = m1 | (m1 << 16);
	m2 = m2 | (m2 << 16);
	m4 = m4 | (m4 << 16);

	x = (x & m1) + ((x >> 1) & m1);
	x = (x & m2) + ((x >> 2) & m2);
	x = (x & m4) + ((x >> 4) & m4);

	x = x + (x >> 8);
	x = x + (x >> 16);

	return x & 0x3F;
}

/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y)
{
	return ~(x & ~y) & ~(~x & y);
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)
{
	int shift = n << 3;
	int mask = 0xFF << shift;

	x = x & ~mask; // Limpia el byte n
	c = c << shift;

	return x | c;
}

// --------------------------------- 4 ---------------------------------
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y)
{
	int sum = x + y;
	int sign_x = x >> 31;
	int sign_y = y >> 31;
	int sum_sign = sum >> 31;
	int overflow = ~(sign_x ^ sign_y) & (sign_x ^ sum_sign);
	int pos_overflow = ~sign_x & overflow;
	int neg_overflow =  sign_x & overflow;
	int max_value = ~(1 << 31);
	int min_value = 1 << 31;
	return (~overflow & sum) | (max_value & pos_overflow) | (min_value & neg_overflow);
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x)
{
	int mul2 = x << 1;
	int sign_x = x >> 31;
	int mul2_sign = mul2 >> 31;
	int overflow = sign_x ^ mul2_sign;
	int pos_overflow = ~sign_x & overflow;
	int neg_overflow =  sign_x & overflow;
	int max_value = ~(1 << 31);
	int min_value = 1 << 31;
	return (mul2 & ~overflow) | (max_value & pos_overflow) | (min_value & neg_overflow);
}

/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x)
{
	return ((x | (~x + 1)) >> 31) & 1;
}

/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n)
{
	int mask = ~(((1 << 31) >> n) << 1);
	int move_right = (x >> n) & mask;
	int move_left = x << ((~n + 33) & 31);
	return move_left | move_right;
}

// --------------------------------- FLOAT ---------------------------------
/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf)
{
	unsigned mask = 0x7FFFFFFF;  // utilizo mascara para eliminar bit de signo
	unsigned abs_uf = uf & mask; // obtengo mi valor absoluto a nivel de bits

	if (abs_uf > 0x7F800000) // NaN ocurre cuando el exponente es 0xFF y la fraccion es distinta de 0 (para float)
		return uf;

	return abs_uf;
}

/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug)
{
	if (((uf & 0x7FFFFFFF) > 0x7F800000) || ((ug & 0x7FFFFFFF) > 0x7F800000))
		return 0; // verifico si alguno de los argumentos es NaN

	if (((uf & 0x7FFFFFFF) == 0) && ((ug & 0x7FFFFFFF) == 0))
		return 1; // debo considerar que +0 y -0 son iguales y para ambos al eliminar el signo se obtiene 0

	return (uf == ug) ? 1 : 0; // si los bits son exactamente iguales, los numeros son iguales
}

/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf)
{
	unsigned abs_uf = uf & 0x7FFFFFFF;

	if (abs_uf > 0x7F800000) // al eliminar el bit de signo si el valor es mayor que el +infinito, el original es NaN
		return uf;

	return uf ^ 0x80000000; // utilizo la mascara para invertir el bit de signo
}

/*
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug)
{
	int singF, singG;

	if (((uf & 0x7FFFFFFF) > 0x7F800000) || ((ug & 0x7FFFFFFF) > 0x7F800000))
		return 0;

	if (((uf & 0x7FFFFFFF) == 0) && ((ug & 0x7FFFFFFF) == 0))
		return 0;

	if (uf == ug)
		return 0;

	singF = uf >> 31;
	singG = ug >> 31; // extraigo el bit de signo

	if (singF != singG)   // si los signos son distintos, si f es neg y g pos, f < g, si fuera al revez f no es menor
		return singF; // devuelvo 1 si f es negativo o 0.

	if (singF == 0)
		return uf < ug; // si ambos son positivos la comparacion entera es valida. (mayor la representacion, mayor el flotante)
	else
		return uf > ug; // si ambos son negativos el orden es inverso
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
int floatFloat2Int(unsigned uf)
{
	int sign = uf >> 31;	     // extraigo bit de singo
	int exp = (uf >> 23) & 0xFF; // obtengo exponente (8 bits)
	int frac = uf & 0x7FFFFF;    // obtengo la fraccion (23 bits)
	int E = exp - 127;	     // exponente sin sesgo
	int M, result;

	if (exp == 0xFF) // caso especial NaN o infinito
		return 0x80000000u;

	if (E < 0) // exponente negativo se redondea a 0
		return 0;

	if (E > 31) // fuera de rango
		return 0x80000000u;

	if (E == 31)
	{ // para positivos no se puede representar y para negativos esta fuera de rango
		if (sign == 0 || frac != 0)
			return 0x80000000u;
	}

	M = frac | (1 << 23); // incorporo bit implicito 1

	if (E > 23)
		result = M << (E - 23);
	else
		result = M >> (23 - E);

	if (sign)
		result = -result;

	return result;
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
unsigned floatPower2(int x)
{
	int exp = x + 127;

	if (x < -149) // demasiado pequeño
		return 0;

	if (exp <= 0) // el exponente es menor o igual a 0
		return 1 << (x + 149);

	if (exp >= 255) // fuera del rango representable
		return 0xFF << 23;

	return exp << 23; // valor representable 2.0^x
}