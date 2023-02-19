#include<stdio.h>
#include<assert.h>

int floatFloat2Int(unsigned uf) {
  int expmask = 0xff << 23;
  int exp = (uf & expmask) >> 23;

  printf("%02x\n",(uf & expmask));
  
  int s = uf >> 31;
  
  int fmask1 = 0xff;
  int fmask2 = fmask1 << 8;
  int fmask3 = fmask2 << 7;
  int fmask = fmask1 | fmask2 | fmask3;
  int frac = uf & fmask;

  int M;
  int E;
  int bias = 127;
  if(exp && (exp - 0xff)){
    M = 1 << 23 | frac;
    E = exp - 127;
  }
  else{
    M = frac;
    E = 1 - 127;
  }

    printf("exp: 0x%02x\tfrac: 0x%02x\tE: %d\tM: 0x%02x\n",exp,frac,E,M);

  int res;
  if(E > 23) res = M << E;
  else if(E == 23) res = M;
  else{
    printf("here\n");
    int e = 23 - E;
    if(e >= 24) return 0;
    res = M >> (23 - E);
    printf("0x%02x\n",(M >> (23 - E)));
  }
  if(s) return -res;
  return res;
}

void test_neg(){
    int x = 0x7fffffff;
    printf("%d\n",(!(!(x + x +2))));
    printf("%d\n",((x + x)));
    printf("%d\n",((x + x + 1)));
    printf("%d\n",((x + x + 2)));
    int y = (x + x + 2);
    assert(y == 0);
    int z = !(y);
    printf("%d\n",(!(x + x +2)));
    printf("%d\n",(!!!(x + x +2)));
    printf("%d\n",y);
    printf("0x%02x\n",x + x + 2);
    printf("%d\n",z);

    int w = 0;
    assert(!w == 1);
    w = 1;
    assert(!w == 0);
    // return 0;
}

unsigned floatPower2(int x) {
  printf("%d\n",x);

  int exp;
  int frac;
  int s = 0;
  int res = 0;

  if(x >= 128){
    exp = 0xff;
    frac = 0;
    s = 0;
    // res = (exp << 23) | (frac) | (s << 31);
  }
  else if(x < -127 - 23){
    frac = 0;
    exp = 0;
    // res = 0;
  }
  else if(x >= -127 - 23 && x <= -127){
    exp = 0;
    frac = 1 << (x - (-127 - 23));
  }
  else if(x > -127){
    frac = 0;
    exp = 127 + x;
  }

  res = (exp << 23) | (frac) | (s << 31);

  printf("0x%02x\t%d\n",res,x);
  return res;
}

int main(){
    // printf("%d\n",floatFloat2Int(0x7f000000));
    printf("0x%02x\n",floatPower2(0));
    return 0;
}