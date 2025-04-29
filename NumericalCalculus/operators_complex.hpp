#ifndef OPERATORS_H
#define OPERATORS_H

#include <functional>
#include <complex>
#include <cmath>
#include <stdexcept>

#define DX 0.00001

#define MAX_ITER 10
#define TOLERANCE 0.001

typedef std::complex<double> Cmp;

typedef std::function<Cmp(Cmp)> CmpFn;
typedef std::function<CmpFn(CmpFn)> CmpOp;


////////////////////////////////////////////////////////////////////////////////
// Unary Operators /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Derivative of function
CmpOp D = [](CmpFn fn) -> CmpFn
{
	return [fn](Cmp x) -> Cmp
	{
		return (fn(x + DX) - fn(x - DX)) / (2 * DX);
	};
};

// Integral of function
CmpOp I = [](CmpFn fn) -> CmpFn
{
	return [fn](Cmp x) -> Cmp
	{
		Cmp sum(0.0, 0.0);
		Cmp x_i(0.0, 0.0);
		
		while (std::norm(x_i) < std::norm(x))
		{
			sum += (fn(x_i)+ fn(x_i + DX));
			x_i += DX;
		}
		
		return sum * (DX / 2);
	};
};

// Laplace transform of function
CmpOp L = [](CmpFn fn) -> CmpFn
{
	return [fn](Cmp x) -> Cmp
	{
		Cmp sum(0.0, 0.0);
		Cmp x_i(0.0, 0.0);
		
		while (std::norm(x_i) < MAX_ITER * MAX_ITER)
		{
			Cmp weight_1 = std::exp(-x_i * x);
			Cmp weight_2 = std::exp(-(x_i + DX) * x);
			
			sum += weight_1 * fn(x_i) + weight_2 * fn(x_i + DX);
			x_i += DX;
		}
		
		return sum * (DX / 2);
	};
};

// Inverse of function
CmpOp Inv = [](CmpFn fn) -> CmpFn
{
	return [fn](Cmp x) -> Cmp
	{
		CmpFn fn_prime = D(fn);
		
		Cmp y(1.0, 0.0);
		Cmp y_next;
		
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

////////////////////////////////////////////////////////////////////////////////
// Non-Unary Operators /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CmpFn Conv(CmpFn fn1, CmpFn fn2)
{
	return [fn1, fn2](Cmp x) -> Cmp
	{
		Cmp sum(0.0, 0.0);
		Cmp temp(0.0, 0.0);
		
		while (std::norm(temp) < std::norm(x)) 
		{
			sum += fn1(temp) * fn2(x - temp);
			temp += DX;
		}
		
		return sum * DX;
	};
}

Cmp Lim(CmpFn fn, Cmp x)
{
	Cmp left = fn(x - DX);
	Cmp right = fn(x + DX);
	
	return (left + right) / 2.0;
}

Cmp LimL(CmpFn fn, Cmp x)
{
	return fn(x - DX);
}

Cmp LimR(CmpFn fn, Cmp x)
{
	return fn(x + DX);
}


////////////////////////////////////////////////////////////////////////////////
// Multiplication Rules ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn * const
CmpFn operator*(CmpFn fn, Cmp a)
{
	return [fn, a](Cmp x) -> Cmp
	{
		return fn(x) * a;
	};
}

CmpFn operator*(Cmp a, CmpFn fn)
{
	return [a, fn](Cmp x) -> Cmp
	{
		return a * fn(x);
	};
}

// fn * fn
CmpFn operator*(CmpFn fn1, CmpFn fn2)
{
	return [fn1, fn2](Cmp x) -> Cmp
	{
		return fn1(x) * fn2(x);
	};
}

// op * const
CmpOp operator*(CmpOp op, Cmp a)
{
	return [op, a](CmpFn fn) -> CmpFn
	{
		return op(fn) * a;
	};
}

CmpOp operator*(Cmp a, CmpOp op)
{
	return [op, a](CmpFn fn) -> CmpFn
	{
		return a * op(fn);
	};
}

// op * fn
CmpFn operator*(CmpOp op, CmpFn fn)
{
	return op(fn);
}

// op * op
CmpOp operator*(CmpOp op1, CmpOp op2)
{
	return [op1, op2](CmpFn fn) -> CmpFn
	{
		return op1(op2(fn));
	};
}


////////////////////////////////////////////////////////////////////////////////
// Division Rules //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn / const
CmpFn operator/(CmpFn fn, Cmp a)
{
	return [fn, a](Cmp x) -> Cmp
	{
		return fn(x) / a;
	};
}

// fn / fn
CmpFn operator/(CmpFn fn1, CmpFn fn2)
{
	return [fn1, fn2](Cmp x) -> Cmp
	{
		return fn1(x) / fn2(x);
	};
}

// op / const
CmpOp operator/(CmpOp op, Cmp a)
{
	return [op, a](CmpFn fn) -> CmpFn
	{
		return op(fn) / a;
	};
}


////////////////////////////////////////////////////////////////////////////////
// Addition Rules //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn + const
CmpFn operator+(CmpFn fn, Cmp a)
{
	return [fn, a](Cmp x) -> Cmp
	{
		return fn(x) + a;
	};
}

CmpFn operator+(Cmp a, CmpFn fn)
{
	return [a, fn](Cmp x) -> Cmp
	{
		return a + fn(x);
	};
}

// fn + fn
CmpFn operator+(CmpFn fn1, CmpFn fn2)
{
	return [fn1, fn2](Cmp x) -> Cmp
	{
		return fn1(x) + fn2(x);
	};
	
}

// op + const
CmpOp operator+(CmpOp op, Cmp a)
{
	return [op, a](CmpFn fn) -> CmpFn
	{
		return op(fn) + a * fn;
	};
}

CmpOp operator+(Cmp a, CmpOp op)
{
	return [a, op](CmpFn fn) -> CmpFn
	{
		return a * fn + op(fn);
	};
}

// op + fn
CmpOp operator+(CmpOp op, CmpFn fn_in)
{
	return [op, fn_in](CmpFn fn_out) -> CmpFn
	{
		return op(fn_out) + fn_in * fn_out;
	};
}

CmpOp operator+(CmpFn fn_in, CmpOp op)
{
	return [fn_in, op](CmpFn fn_out) -> CmpFn
	{
		return  fn_in * fn_out + op(fn_out);
	};
}

// op + op
CmpOp operator+(CmpOp op1, CmpOp op2)
{
	return [op1, op2](CmpFn fn) -> CmpFn
	{
		return op1(fn) + op2(fn);
	};
}


////////////////////////////////////////////////////////////////////////////////
// Subtraction Rules ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// fn - const
CmpFn operator-(CmpFn fn, Cmp a)
{
	return [fn, a](Cmp x) -> Cmp
	{
		return fn(x) - a;
	};
}

CmpFn operator-(Cmp a, CmpFn fn)
{
	return [a, fn](Cmp x) -> Cmp
	{
		return a - fn(x);
	};
}

// fn - fn
CmpFn operator-(CmpFn fn1, CmpFn fn2)
{
	return [fn1, fn2](Cmp x) -> Cmp
	{
		return fn1(x) - fn2(x);
	};
}

// op - const
CmpOp operator-(CmpOp op, Cmp a)
{
	return [op, a](CmpFn fn) -> CmpFn
	{
		return op(fn) - a * fn;
	};
}

CmpOp operator-(Cmp a, CmpOp op)
{
	return [a, op](CmpFn fn) -> CmpFn
	{
		return a * fn - op(fn);
	};
}

// op - fn
CmpOp operator-(CmpOp op, CmpFn fn_in)
{
	return [op, fn_in](CmpFn fn_out) -> CmpFn
	{
		return op(fn_out) - fn_in * fn_out;
	};
}

CmpOp operator-(CmpFn fn_in, CmpOp op)
{
	return [fn_in, op](CmpFn fn_out) -> CmpFn
	{
		return  fn_in * fn_out - op(fn_out);
	};
}

// op - op
CmpOp operator-(CmpOp op1, CmpOp op2)
{
	return [op1, op2](CmpFn fn) -> CmpFn
	{
		return op1(fn) - op2(fn);
	};
}


#endif