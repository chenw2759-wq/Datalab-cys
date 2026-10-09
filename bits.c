/* 
 * CS:APP Data Lab 
 * 
 * 陈域圣 25800440031
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;   //1左移31位，后面位置补0；
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);   //为达到异或，取交集；第一个集合是一位不同时为0，第二个集合是一位不同时为1。
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask=x>>31;   //右移31位，得到符号位的掩码，负数为0xFFFFFFFF，非负数为0x00000000
  return mask&(~x+1);  //x取反加1得到负数的绝对值，mask与其相与，负数返回绝对值，非负数返回0
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int src_shift=src<<3;   
  int dst_shift=dst<<3;    //乘以8
  int src_byte=(x>>src_shift)&0xFF;  //右移src_shift位，取出src字节
  int mask=~(0xFF<<dst_shift);  //将dst字节位置设置掩码，用于清零
  return (x&mask)|(src_byte<<dst_shift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
int mask=~(((1 << 31) >> n) << 1);  //避免错误移位32（n=0）
  return (x>>n)& mask;  //第二次尝试时漏掉了右移操作！！！
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask_low = 0x0F|(0x0F << 8)|(0x0F << 16)|(0x0F << 24);
  int mask_high = ~mask_low;
  return ((x & mask_low) << 4) | (((x & mask_high) >> 4)&mask_low);  //问题：前面忘记了0x80000000是负数，算数右移高位补1，结果会出错，要清理1！
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
int x1=(~x&(x+1));  //取出最低位置的0位
int x2=(x1|x);  //通过或把最低的0变为1，其他不变；
int x3=(~x2&(x2+1));  //再来一遍
  return x3;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x^=x>>16;
  x^=x>>8;
  x^=x>>4;
  x^=x>>2;
  x^=x>>1;  //使用异或折叠（异或的本质是模2同余）
  return (x&1)^1;  //末尾就是模2余几，上一个版本整个输出了。
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  n=n&31;  //防止n大于31
  int logical_shifted=(x >> n) & ~(((1<<31)>>n) << 1);
  int left_shifted=x << ((32 + ~n + 1) & 31);
  return logical_shifted | left_shifted;  //第一个版本没考虑负数!!
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int half_minus_1=(1<<(n+~0))+~0;  //2^(n-1)
  int q=(x>>n)&1;  //求商
  int mask = (1 << n) + ~0;  //如果商是奇数，偏置为2^(n-1)-1，否则为0
  return (x +half_minus_1+q) & ~mask;  //加上偏置后右移n位再左移n位，清理。
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int avg=(x & y) + ((x ^ y)>>1);          // floor((x+y)/2)，不会溢出
  int odd=(x^y) & 1;                       // 1 表示 x+y 是奇数，中点落在 .5
  int sign_x = x >>31;
  int sign_y = y >>31;
  int diff_sign=sign_x^sign_y;
  int diff=x+~y+1;  //x-y,同号不溢出！
  int same_gt = ~(diff >> 31) & 1;      // 同号时 x > y
  int diff_gt = (~sign_x) & sign_y;     // 异号时 x >= 0 且 y < 0，即 x > y
  int x_gt_y =(diff_sign&diff_gt)|(~diff_sign&same_gt);       //原本判断反了  //第二次修改的代码在极端值下会溢出！！
  return avg +(odd & x_gt_y);  // 如果 x+y 是奇数且 x >= y，则向上取整
}
//第三次提交的问题在于极端值溢出！最小减最大就会爆掉。

// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    //原先减法溢出了。但我不知道如何做，所以这个代码AI辅助
  int dxa = x + ~a + 1;
  int of_a = (x ^ a) & (x ^ dxa);
  int x_ge_a = ~((dxa ^ of_a) >> 31);

  int dxb = x + ~b + 1;
  int of_b = (x ^ b) & (x ^ dxb);
  int x_ge_b = ~((dxb ^ of_b) >> 31);

  int dax = a + ~x + 1;
  int of_ax = (a ^ x) & (a ^ dax);
  int a_ge_x = ~((dax ^ of_ax) >> 31);

  int dbx = b + ~x + 1;
  int of_bx = (b ^ x) & (b ^ dbx);
  int b_ge_x = ~((dbx ^ of_bx) >> 31);

  return ((x_ge_a & b_ge_x) | (x_ge_b & a_ge_x)) & 1;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int sign = x >> 31;
  int abs_x = (x + sign) ^ sign;               // |x|
  int pos_thresh = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x99; // 0x19999999
  int diff = abs_x + ~pos_thresh + 1;          // |x| - 0x19999999
  int diff_sign = diff >> 31;
  int overflow = ~diff_sign & !!diff;          // 1 表示溢出
  int mask = ~overflow + 1;                    // 溢出时 mask = -1，否则 0
  int mul5 = (x << 2) + x;
  int sat_val = ~(sign ^ (1 << 31));           // INT_MAX 或 INT_MIN
  return (mask & sat_val) | (~mask & mul5);  //原本溢出判断只检查符号，但三正可为正！！故会漏判，只能用阈值！但我不会改，只能让AI帮我写代码。。。
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
   int s1 = x + y;
  int c1 = ((x & y) | ((x | y) & ~s1)) >> 31 & 1;
  int s2 = s1 + z;
  int c2 = ((s1 & z) | ((s1 | z) & ~s2)) >> 31 & 1;
  int carry = c1 + c2;

  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int sz = (z >> 31) & 1;
  int sign_sum = sx + sy + sz;
  int high = carry + ~sign_sum + 1;      // high = carry - sign_sum

  int sum_low = s2;
  int sign_low = sum_low >> 31;
  int low_neg = sign_low & 1;

  int high_sign = high >> 31;
  int high_nonzero = !!high;
  int high_gt_zero = high_nonzero & ~high_sign & 1;
  int high_eq_zero = !high;
  int overflow_pos = high_gt_zero | (high_eq_zero & low_neg);

  int high_plus_1 = high + 1;
  int high_plus_1_sign = high_plus_1 >> 31;
  int high_lt_minus_1 = high_plus_1_sign & 1;
  int high_eq_minus_1 = !(high + 1);
  int low_nonneg = ~sign_low & 1;
  int overflow_neg = high_lt_minus_1 | (high_eq_minus_1 & low_nonneg);

  int neg_result = overflow_neg << 31 >> 31;
  return overflow_pos | neg_result;

}   //原先中间溢出会相互抵消！所以现在用高位计数法，最后再判断符号位是否溢出。这个方法也是AI想的，我不会。。。

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign=uf&0x80000000;
  unsigned exp=(uf>>23)&0xFF;
  unsigned frac=uf&0x7FFFFF;
  unsigned m,t,E,half,tail;
  if(exp==0xFF){
    return uf;  //NaN直接返回参数，Inf乘3/2仍为Inf
  }
  if(exp==0){
    t = frac * 3;
    tail = t >> 1;
    if (t & 1) {
      tail += tail & 1;
    }
    if (tail & 0x800000) {
      return sign | (1 << 23) | (tail & 0x7FFFFF);
    }
    return sign | tail;
  }
  m = 0x800000 | frac;
  t = m * 3;
  if (t >= 0x2000000) {
    E = exp + 1;
    tail = t >> 2;
    if (t & 2) {
      unsigned rem = t & 3;
      if (rem > 2 || (rem == 2 && (tail & 1))) {
        tail++;
      }
    }
  } else {
    E = exp;
    tail = t >> 1;
    if (t & 1) {
      if (tail & 1) {
        tail++;
      }
    }
  }                       //原先问题：规格化数乘以1.5后当结果小于最小规格化数时指数被错误增大了！！
  if (tail & 0x1000000) {  
    tail >>= 1;
    E++;
  }
  if (E >= 0xFF) {
    return sign | 0x7F800000;
  }
  return sign | (E << 23) | (tail & 0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign=uf&0x80000000;
  unsigned exp=(uf>>23)&0xFF;
  unsigned frac=uf&0x7FFFFF;
  unsigned m,sh,v,rem,half,p;
  if(exp==0xFF){
    return uf;  //NaN和无穷返回原值
  }
  if(exp<126){
    return sign;  //绝对值<0.5舍入为0，负数返回-0
  }
  if(exp>=150){
    return uf;  //绝对值>=2^23，本身就是精确整数
  }
  m=frac|0x800000;  //值=m*2^(exp-150)
  sh=150-exp;
  v=m>>sh;  //整数部分
  rem=m&((1<<sh)-1);  //移出的小数部分
  half=1<<(sh-1);  //0.5
  if((rem>half)||((rem==half)&&(v&1))){
    v=v+1;  //向偶数舍入
  }
  if(!v){
    return sign;  //舍入到0，保留符号
  }
  p=23;
  while(!(v&(1<<p))){
    p--;  //找最高位位置
  }
  return sign|((p+127)<<23)|((v<<(23-p))&0x7FFFFF);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign=0;
  unsigned abs;
  unsigned frac,rem,half;
  int pos,sh,exp;
  if(!x){
    return 0;  //0对应+0
  }
  if(x<0){
    sign=0x80000000;
    abs=~x+1;  //取绝对值
  }else{
    abs=x;
  }
  pos=31;
  while(!(abs&(1<<pos))){
    pos--;  //找最高位位置
  }
  exp=pos+127;
  if(pos<=23){
    frac=(abs<<(23-pos))&0x7FFFFF;  //不超过24位
  }else{
    sh=pos-23;  //需丢弃的低位数
    frac=(abs>>sh)&0x7FFFFF;  //取高23位
    rem=abs&((1<<sh)-1);
    half=1<<(sh-1);
    if((rem>half)||((rem==half)&&(frac&1))){
      frac++;  //向偶数舍入
    }
    if(frac==0x800000){
      frac=0;  //舍入产生进位，阶码加一
      exp++;
    }
  }
  return sign|(exp<<23)|frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55;
  m1 = m1 | (m1 << 8);
  m1 = m1 | (m1 << 16);

  int m2 = 0x33;
  m2 = m2 | (m2 << 8);
  m2 = m2 | (m2 << 16);

  int m4 = 0x0F;
  m4 = m4 | (m4 << 8);
  m4 = m4 | (m4 << 16);

  int m8 = 0xFF;
  m8 = m8 | (m8 << 16);

  int m16 = 0xFF;
  m16 = m16 | (m16 << 8);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x & m8) + ((x >> 8) & m8);
  return (x & m16) + ((x >> 16) & m16);  //高低16位相加得总数
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  unsigned int y = x, m1, m2, m3, m4;

  /* 构造掩码，所有直接常量 ≤ 255 */
  m3 = 0x0F | (0x0F << 8);
  m3 = m3 | (m3 << 16);          /* 0x0F0F0F0F */
  m2 = m3 ^ (m3 << 2);           /* 0x33333333 */
  m1 = m2 ^ (m2 << 1);           /* 0x55555555 */
  m4 = 0xFF | (0xFF << 16);      /* 0x00FF00FF */

  /* 分段交换位 */
  y = ((y >> 1) & m1) | ((y & m1) << 1);
  y = ((y >> 2) & m2) | ((y & m2) << 2);
  y = ((y >> 4) & m3) | ((y & m3) << 4);
  y = ((y >> 8) & m4) | ((y & m4) << 8);
  y = (y >> 16) | (y << 16);

  return y;
}


