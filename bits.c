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
    //Use ops: 4/8
    return ~(~x|~y); // ~(x&y) = ~x|~y
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
    //Use ops: 3/6
    return (x>>(n<<3))&0xFF;
    //通过右移将需要的字节放到最低位，并通过&运算截取最低位。
    //需要右移的位数应该是 字节数*8 (1字节＝8位)，即n<<3。
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    //Use ops: 6/20
    //如果直接进行算术右移temp＝x>>n，当符号位为1时，算术右移会填补1，而逻辑右移应该填补0。
    //所以需要构造0……01……1（前面有n个0），与temp进行&运算进行清0。
    //通过(1<<31)构造10……0，然后右移n-1位，得到1……10……0（前面有n个1）再取反即可。
    //但是注意到n有可能为0，所以先右移n位，再左移1位即可。
    return (x>>n)&(~(1<<31>>n<<1));
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    //Use ops: 26/40
    int num1,num2,count,result1,result2,result3,result4;
    num1 = (0x11<<8)+0x11; //0x00001111
    num2 = (num1<<16)+num1; //0x11111111
    count = num2 & x;
    count += num2 & (x>>1);
    count += num2 & (x>>2);
    count += num2 & (x>>3); //这样count的每4位均作为一个累加器进行计算
    count += (count>>16); //折叠合并每4位的结果
    result1 = count&0xf; //对4组4位进行合并，直接相加可能导致溢出
    result2 = (count>>4)&0xf;
    result3 = (count>>8)&0xf;
    result4 = (count>>12)&0xf;
    return result1 + result2 + result3 + result4;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    //Use ops: 6/12
    //只有!0的结果是1，其他均为0，故核心在于判断一个数是不是0
    //判断一个数是不是0，可以考虑运用题目negate
    //只有0的相反数和本身符号位均为0，所以只需要判断x与~x+1的符号位是否均为0。
    return ~((x|(~x+1))>>31)&1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    //Use ops: 1/4
    //最小的补码为1 000 0000 0000 …… 0000，真值是-2^31
    return 1<<31;
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
    //Use ops: 12/15
    //首先，n位补码可以表示的范围为[-2^(n-1),2^(n-1)-1]
    //也就是需要判断x是不是在[-2^(n-1),2^(n-1)-1]中
    //若x是正数，则x右移n-1位之后应该为0。
    //若x是负数，考察x的相反数-x，那么-x<=2^(n-1)，即-x-1右移n-1位之后应该为0。
    //x的相反数可以用~x+1来表示，所以-x-1=~x，也就是~x右移n-1位之后应该为0。
    int signal,positive,negative,temp;
    signal = x>>31; //取符号位，0为正数，1为负数。
    temp = n+(~0); //构造temp=n-1
    positive = !signal & !(x>>temp); //如果x是正数且在范围内，值为1
    negative = signal & !(~x>>temp); //如果x是负数且在范围内，值为1
    return positive|negative;
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
    //Use ops: 7/15
    //当x是正数时，x>>n就是所求的结果。
    //当x是负数时，x>>n会向下取整，这样就不对，所以先考虑x+(2^n-1)，再向下取整才是正确答案。
    int signal,temp;
    signal=x>>31;
    temp = (1<<n) + (~0); //构造00……0011……11。
    return ((signal&temp)+x)>>n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    //Use ops: 2/5
    //思考负数补码的运算规则，先将符号为取为1，再将剩余各位取反后加1，这等价于把负数的相反数每位都取反后加1。
    //同理，负数的补码按位取反后加1，就得到负数的相反数。
    //综上-x=~x+1
    return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    //Use ops: 4/8
    //大于0的数符号位为0，小于0的数符号位为1。唯一需要注意的是，0在这种情况下应该返回0，需要单独判断。
    int isZero = !x; //x为0返回1，否则返回0
    return !(isZero|(x>>31)); //若x为0或x为负，则isZero|(x>>31)为1，再取反即可。
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //Use ops: 14/24
    //x<=y等价于y-x>=0，即y-x的符号位为0时返回1。即!((y+(~x+1))>>31)
    //注意可能产生溢出的情况，当y>=0,x<0时，y-x可能溢出，所以应该直接返回1。同样y<0,x>=0，直接返回0。
    int normalResult,signalx,signaly;
    normalResult = !((y+(~x+1))>>31);
    signalx = x>>31;
    signaly = y>>31;
    //用signalx^signaly来判断是否异号，(signalx^signaly)&signalx表示了异号时的返回。
    //!(signalx^signaly)&normalResult表示了同号时的返回。
    return (((signalx^signaly)&signalx)|(!(signalx^signaly)&normalResult))&1; //保留最低位
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    //Use ops: 29/90
    int adder,isNotZero;
    //很容易想到brute force的方法如下：
    //使用累加器adder，每次将x右移一位，并判断右移后的结果是否为0。若不是0，则累加器加一。重复31次。
    //由于右移、累加、取反共需要三个操作，重复31次将会超出Max ops 90的限制，所以需要对算法进行优化。
    //采用二分法进行累加，第一次判断高16位是否为0，如果非0，则累加器直接加16，然后将x右移16位，如果为0，不做变动。
    //依次判断高16，高8，高4，高2和最后一位，这样操作符消耗量小了很多。
    isNotZero = !!(x>>16); //如果高16位为0，则isNotZero为0，否则为1。
    adder = isNotZero<<4; //如果高16位非零，累加器加16，否则不做改变。
    x = x>>(isNotZero<<4); //如果高16位非零，将x右移16位后继续累加。
    isNotZero = !!(x>>8); //同样判断高8位。
    adder = adder + (isNotZero<<3);
    x = x>>(isNotZero<<3);
    isNotZero = !!(x>>4); //同样判断高4位。
    adder = adder + (isNotZero<<2);
    x = x>>(isNotZero<<2);
    isNotZero = !!(x>>2); //同样判断高2位。
    adder = adder + (isNotZero<<1);
    x = x>>(isNotZero<<1);
    adder = adder + (x>>1); //判断最后2位的最高位是否为1即可
    return adder;
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
    //Use ops: 3/10
    //此题即判断阶码是否全1而尾数非0。
    //首先将符号位置为1（因为符号位不影响判断），那么只要大于11……1100……000(9和1，23个0)就是NaN了。
    if((uf|0x80000000) > 0xff800000) return uf; //NaN直接返回
    else return uf^0x80000000; //否则符号位取负
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
    //Use ops: 15/30
    unsigned signal,absx,E,temp,carry;
    if(!x) return 0; //如果为0需要单独处理，如果非0则必定最高位为1。
    //获取符号位，并保存|x|来计算阶码和尾数
    signal = 0;
    absx = x;
    E = 159; //阶码E
    if(x>>31){ //如果x<0，则|x|=-x
        signal = 0x80000000;
        absx = -absx;
    }
    //接下来为了得到尾数，需要将最高位的1去除。
    while(1){
        temp = absx;
        //每次将absx左移一位，直到absx的最高位为1。
        absx = absx<<1; //absx最大为0x7fffffff，移动2次将最高位1去除，阶码为157。假设移动了x次，那么阶码应该是127+(32-x)=159-x，所以之前将E置为159，每次--即可。
        --E;
        if(temp & 0x80000000) break; //如果temp最高位为1，跳出循环。此时absx最高位起23位即为进位前的尾数。
    }
    //接下来考虑截断的进位问题
    carry = 0;
    //absx一共保存了32位信息，只能取前23位作为尾数。剩下9位应该用于判断进位。
    //首先用absx&0x1ff截取最后九位，若最后九位>0x100，即(absx&0x1ff)>0x100则进位。
    //若最后九位=0x100，还需判断倒数第十位是否为1，也就是最后十位是否是0x300，即(absx&0x3ff)==0x300则进位。
    //其他情况不进位。
    if(((absx&0x1ff)>0x100)||((absx&0x3ff)==0x300)) carry = 1;
    return signal + (E<<23) + (absx>>9) + carry;
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
    //Use ops: 9/30
    unsigned signal,E,f;
    //进行分类讨论：
    //如果是NaN，正负无穷大，直接返回。
    signal = uf & 0x80000000; //取符号位
    E = uf & 0x7f800000; //取阶码(高位第二位起连续8位)
    f = uf & 0x7fffff; //取尾数(末23位)
    if(E == 0x7f800000) return uf; //NaN直接返回
    else{
        if(E){
            //如果阶码非0，则为规格化非零数，阶码加1即可。
            E = E + 0x800000;
            if(E == 0x7f800000) f=0; //有可能加1后溢出，则返回无穷大。
        }
        else{
            //如果阶码为0，有两种可能性，正负0或非规格化数。
            //此时直接左移尾数即可。若尾数首位为1，将会使得阶码加一，变成规格化数，仍然是正确的。
            f = f<<1;
        }
        return signal + E + f;
    }
}
