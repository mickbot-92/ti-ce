#include <cmath>
#include <errno.h>
#include <iostream>
#include <iomanip>

#define	sqrto2	0.707106781186548e0

float _logf_c(float arg)
{
#define	log2	0.693147180559945e0
#define	ln10	2.30258509299404
#define	p0	-0.240139179559211e2
#define	p1	0.309572928215377e2
#define	p2	-0.963769093368687e1
#define	p3	0.421087371217980e0
#define	q0	-0.120069589779605e2
#define	q1	0.194809660700890e2
#define	q2	-0.891110902798312e1
	float x,z, zsq, temp;
	int exp;

	if (arg <= 0.0) {
		errno = EDOM;
		return -HUGE_VALF;
	}
    x = frexpf(arg, & exp);
	if ( x < sqrto2 ){
		x *= 2;
		exp--;
	}

	z = (x-1)/(x+1);
	zsq = z*z;

	temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
	temp = temp/(((1.0*zsq + q2)*zsq + q1)*zsq + q0);
	temp = temp*z + exp*log2;
	return temp;
}

  float my_ln(float arg){
    float x,z, z2, temp;
    int exp;
    
    if (arg<=0.0) {
      errno = EDOM;
      return -HUGE_VALF;
    }
    x = frexpf(arg, & exp);
    if (x<sqrto2){
      x *= 2;
      exp--;
    }
    // now x is in [sqrt(2)/2,sqrt(2)]
    // ln(x)=ln((1+z)/(1-z)) where z=(x-1)/(x+1) is such that |z|<=3-2*sqrt(2)
    // = z*sum( (z^2)^k*2/(2k+1),k=0..inf)
    // for float precision, k=4 is enough, relative precision 2e-9/(1-|z|^2)
    z = (x-1)/(x+1);
    z2 = z*z;
    // seq(2./(2k+1),k,0,5)=[2.0,0.666666666667,0.4,0.285714285714,0.222222222222,0.181818181818]
    temp = (((0.222222222222*z2+0.285714285714)*z2+0.4)*z2+0.666666666667)*z2+2.0;
    temp = temp*z + exp*M_LN2;
    return temp;
  }

  float my_exp(float arg){
#define	log2e	1.44269504088896
#define	sqrt2	1.41421356237310
#define	maxf	100 // was 10000
      float fraction;
      float temp1, temp2, xsq;
      int ent;
      if (arg==0.0)
        return 1.0;
      if (arg<-maxf){
        return 0.0;
      }
      if (arg>maxf){
        errno = ERANGE;
        return HUGE_VALF;
      }
      // 1* 1 floor 2 -
      arg *= log2e;
      ent = floor( arg );
      fraction = arg - ent - 0.5;
      fraction *= M_LN2;
      xsq = fraction * fraction;
      // pade(exp(x),x,6,4) relative error<6e-9
      // (-x^3-12*x^2-60*x-120)/(x^3-12*x^2+60*x-120)
      temp1=(xsq+60.0)*fraction;
      temp2=12.0*(xsq+10.0);
      return ldexp( sqrt2 * (temp2+temp1) / (temp2-temp1), ent );
  }    

float pade_atan(float arg){
  // pade(atan(x),x,11,6)
  // (231*x^5+1190*x^3+1155*x)/(25*x^6+525*x^4+1575*x^2+1155)
  float argsq;
  float value;
  argsq = arg*arg;
  value = ((9.24*argsq+47.6)*argsq+46.2)/(((argsq+21)*argsq+63)*argsq+46.2);
  return(value*arg);
}

float my_atan(float arg) {
#define sq2p1	2.41421356237309
#define sq2m1	0.414213562373095
#define pio2	1.57079632679489
#define pio4	0.785398163397448
  if (arg<0)
    return -my_atan(-arg);
  if (arg<sq2m1)
    return pade_atan(arg);
  if (arg>sq2p1)
    return pio2 - pade_atan(1.0/arg);
  return pio4+pade_atan((arg-1.0)/(arg+1.0));
}




float my_tan(float arg)
{
#define invpi 	1.27323954473516   // 4/pi
  float temp, e, argsq;
  int i,sign;
  
  sign = 1;
  if (arg<0.){
    arg = -arg;
    sign = -1;
  }
  i = arg*invpi;
  arg -= i*pio4;
  i &= 3;
  if (i&1) // pi/4-arg=pi/2-(arg+pi/4) => tan(arg+pi/4)=1/tan(pi/4-arg)
    arg=pio4-arg;
  if (i/2)
    sign=-sign;
  // P:=pade(tan(x),x,10,6)
  // (x^5-105*x^3+945*x)/(15*x^4-420*x^2+945)
  argsq = arg*arg;
  temp = ((argsq-105)*argsq+945)*arg/((15*argsq-420)*argsq+945);
  if (i==1 || i==2) {
    if (temp==0.) {
      errno = ERANGE;
      if (sign>0)
        return HUGE_VALF;
      return -HUGE_VALF;
    }
    temp = 1./temp;
  }
  return sign==1?temp:-temp;
}

#define p0 	-0.130682026475483e+5
#define p1	0.105597090171495e+4
#define p2	-0.155068565348327e+2
#define p3	0.342255438724100e-1
#define p4	0.338663864267717e-4
#define q0	-0.166389523894712e+5
#define q1	0.476575136291648e+4
#define q2	-0.155503316403171e+3

float _tanf_c(float arg)
{
	float sign, temp, e, x, xsq;
	int flag, i;

	flag = 0;
	sign = 1.;
	if(arg < 0.){
		arg = -arg;
		sign = -1.;
	}
	arg = arg*invpi;   /*overflow?*/
        x = modff(arg, &e);
	i = e;
	switch(i%4) {
	case 1:
		x = 1. - x;
		flag = 1;
		break;

	case 2:
		sign = - sign;
		flag = 1;
		break;

	case 3:
		x = 1. - x;
		sign = - sign;
		break;

	case 0:
		break;
	}

	xsq = x*x;
	temp = ((((p4*xsq+p3)*xsq+p2)*xsq+p1)*xsq+p0)*x;
	temp = temp/(((1.0*xsq+q2)*xsq+q1)*xsq+q0);

	if(flag == 1) {
		if(temp == 0.) {
			errno = ERANGE;
			if (sign>0)
				return(HUGE_VALF);
			return(-HUGE_VALF);
		}
		temp = 1./temp;
	}
	return(sign*temp);
}

float my_log1p(float x){
  if (fabs(x)<=0.125){
    // pade(series(ln(1+x),x=0,6,polynom),x,5,3)
    // (-57*x**2-90*x)/(x**3-21*x**2-102*x-90)
    // relative error less than 1e-7
    return x*(57*x+90)/(((21-x)*x+102)*x+90);
  }
  // relative error about 2^-21 if abs(x) is just above 0.125
  return logf(1 + x);
}
int main(){
  double maxerr=0,xerr=-1,xmin=0.001,xmax=10,nstep=999,xstep=(xmax-xmin)/(nstep-1),x=xmin;
  for (int i=0;i<nstep;++i){
    std::cout << x << " ";
    double err=fabs(my_log1p(x)/std::log1p(float(x))-1);
    //double err=fabs(my_tan(x)/std::tan(float(x))-1);
    // double err=fabs(_tanf_c(x)/std::tan(float(x))-1);
    //double err=fabs(_logf_c(x)/std::log(float(x))-1);
    if (err>maxerr){
      maxerr=err;
      xerr=x;
    }
    x += xstep;
  }
  std::cout << std::setprecision(8) << "\nmaxerr=" << maxerr << " (2^-24=" << 6e-8 << ") xerr=" << xerr << " float=" << my_tan(xerr) << " double=" << std::tan(xerr) << "\n";
}
