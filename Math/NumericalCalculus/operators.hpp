#ifndef OPERATORS_H
#define OPERATORS_H

#include <functional>
#include <cmath>
#include <stdexcept>

#define DX 0.00001
#define MAX_ITER 15
#define TOLERANCE 0.001

typedef std::function<double(double)> RealFn;
typedef std::function<RealFn(RealFn)> RealOp;


////////////////////////////////////////////////////////////////////////////////
// Primitive Operators /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
RealOp D = [](RealFn fn) -> RealFn
{
	return [fn](double x) -> double
	{
		return (fn(x + DX) - fn(x - DX)) / (2 * DX);
	};
};

RealOp I = [](RealFn fn) -> RealFn
{
	return [fn](double x) -> double
	{
		double sum = 0.0;
		double temp = 0.0;
		
		while (temp < x)
		{
			sum += (fn(temp)+ fn(temp + DX));
			temp += DX;
		}
		
		return sum * (DX / 2);
	};
};

RealOp Inv = [](RealFn fn) -> RealFn
{
	return [fn](double x) -> double
	{
		RealFn fn_prime = D(fn);
		
		double y = 1;
		double y_next;
		
		for (int i = 0; i < MAX_ITER; i++)
		{
			y_next = y - (fn(y) - x) / fn_prime(y);
			
			if (std::abs(y_next - y) < TOLERANCE)
				return y_next;
			
			y = y_next;
		}
		
		throw std::runtime_error("Newton's method for inverse did not converge");
	};
};

double Lim(RealFn fn, double x)
{
	double left = fn(x - DX);
	double right = fn(x + DX);
	
	return (left + right) / 2.0;
}

double LimL(RealFn fn, double x)
{
	return fn(x - DX);
}

double LimR(RealFn fn, double x)
{
	return fn(x + DX);
}

RealFn Conv(RealFn fn1, RealFn fn2)
{
	return [fn1, fn2](double x) -> double
	{
		double sum = 0.0;
		double temp = 0.0;
		
		while (temp < x) 
		{
			sum += fn1(temp) * fn2(x - temp);
			temp += DX;
		}
		
		return sum * DX;
	};
}



////////////////////////////////////////////////////////////////////////////////
// Multiplication Rules ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn * const
RealFn operator*(RealFn fn, double a)
{
	return [fn, a](double x) -> double
	{
		return fn(x) * a;
	};
}

RealFn operator*(double a, RealFn fn)
{
	return [a, fn](double x) -> double
	{
		return a * fn(x);
	};
}

// fn * fn
RealFn operator*(RealFn fn1, RealFn fn2)
{
	return [fn1, fn2](double x) -> double
	{
		return fn1(x) * fn2(x);
	};
}

// op * const
RealOp operator*(RealOp op, double a)
{
	return [op, a](RealFn fn) -> RealFn
	{
		return op(fn) * a;
	};
}

RealOp operator*(double a, RealOp op)
{
	return [op, a](RealFn fn) -> RealFn
	{
		return a * op(fn);
	};
}

// op * fn
RealFn operator*(RealOp op, RealFn fn)
{
	return op(fn);
}

// op * op
RealOp operator*(RealOp op1, RealOp op2)
{
	return [op1, op2](RealFn fn) -> RealFn
	{
		return op1(op2(fn));
	};
}


////////////////////////////////////////////////////////////////////////////////
// Division Rules //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn / const
RealFn operator/(RealFn fn, double a)
{
	return [fn, a](double x) -> double
	{
		return fn(x) / a;
	};
}

// fn / fn
RealFn operator/(RealFn fn1, RealFn fn2)
{
	return [fn1, fn2](double x) -> double
	{
		return fn1(x) / fn2(x);
	};
}

// op / const
RealOp operator/(RealOp op, double a)
{
	return [op, a](RealFn fn) -> RealFn
	{
		return op(fn) / a;
	};
}


////////////////////////////////////////////////////////////////////////////////
// Addition Rules //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn + const
RealFn operator+(RealFn fn, double a)
{
	return [fn, a](double x) -> double
	{
		return fn(x) + a;
	};
}

RealFn operator+(double a, RealFn fn)
{
	return [a, fn](double x) -> double
	{
		return a + fn(x);
	};
}

// fn + fn
RealFn operator+(RealFn fn1, RealFn fn2)
{
	return [fn1, fn2](double x) -> double
	{
		return fn1(x) + fn2(x);
	};
	
}

// op + const
RealOp operator+(RealOp op, double a)
{
	return [op, a](RealFn fn) -> RealFn
	{
		return op(fn) + a * fn;
	};
}

RealOp operator+(double a, RealOp op)
{
	return [a, op](RealFn fn) -> RealFn
	{
		return a * fn + op(fn);
	};
}

// op + fn
RealOp operator+(RealOp op, RealFn fn_in)
{
	return [op, fn_in](RealFn fn_out) -> RealFn
	{
		return op(fn_out) + fn_in * fn_out;
	};
}

RealOp operator+(RealFn fn_in, RealOp op)
{
	return [fn_in, op](RealFn fn_out) -> RealFn
	{
		return  fn_in * fn_out + op(fn_out);
	};
}

// op + op
RealOp operator+(RealOp op1, RealOp op2)
{
	return [op1, op2](RealFn fn) -> RealFn
	{
		return op1(fn) + op2(fn);
	};
}


////////////////////////////////////////////////////////////////////////////////
// Subtraction Rules ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn - const
RealFn operator-(RealFn fn, double a)
{
	return [fn, a](double x) -> double
	{
		return fn(x) - a;
	};
}

RealFn operator-(double a, RealFn fn)
{
	return [a, fn](double x) -> double
	{
		return a - fn(x);
	};
}

// fn - fn
RealFn operator-(RealFn fn1, RealFn fn2)
{
	return [fn1, fn2](double x) -> double
	{
		return fn1(x) - fn2(x);
	};
}

// op - const
RealOp operator-(RealOp op, double a)
{
	return [op, a](RealFn fn) -> RealFn
	{
		return op(fn) - a * fn;
	};
}

RealOp operator-(double a, RealOp op)
{
	return [a, op](RealFn fn) -> RealFn
	{
		return a * fn - op(fn);
	};
}

// op - fn
RealOp operator-(RealOp op, RealFn fn_in)
{
	return [op, fn_in](RealFn fn_out) -> RealFn
	{
		return op(fn_out) - fn_in * fn_out;
	};
}

RealOp operator-(RealFn fn_in, RealOp op)
{
	return [fn_in, op](RealFn fn_out) -> RealFn
	{
		return  fn_in * fn_out - op(fn_out);
	};
}

// op - op
RealOp operator-(RealOp op1, RealOp op2)
{
	return [op1, op2](RealFn fn) -> RealFn
	{
		return op1(fn) - op2(fn);
	};
}


#endif