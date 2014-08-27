#pragma once
#include "common.h"
#include <vector>
using namespace std;
namespace mono
{
	// a bunch of these will trigger warning C4756. it can be safely ignored.
#pragma warning(disable : 4756)
	const vector<Point> A{
		make_pair(0,0),
		make_pair(3,-10),
		make_pair(6,0),
		make_pair(4,-4),
		make_pair(2, -4)
	};
	const vector<Point> B{
		make_pair(0, 0),
		make_pair(0, -10),
		make_pair(3, -10),
		make_pair(6, -8),
		make_pair(6, -6),
		make_pair(5, -5),
		make_pair(0, -5),
		make_pair(5, -5),
		make_pair(6, -4),
		make_pair(6, -2),
		make_pair(4, 0),
		make_pair(0,0)
	};
	const vector<Point> C{
		make_pair(6, -10),
		make_pair(2, -9),
		make_pair(0, -5),
		make_pair(2, -1),
		make_pair(6, 0)
	};
	const vector<Point> D{
		make_pair(0,0),
		make_pair(0, -10),
		make_pair(3, -10),
		make_pair(6, -8), 
		make_pair(6, -4),
		make_pair(6, -2),
		make_pair(4, 0),
		make_pair(0, 0)
	};
	const vector<Point> E{
		make_pair(6, -10),
		make_pair(0, -10),
		make_pair(0,0), 
		make_pair(6, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -5),
		make_pair(4, -5)
	};
	const vector<Point> F{
		make_pair(6, -10),
		make_pair(0, -10),
		make_pair(0, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -5),
		make_pair(4, -5)
	};
	const vector<Point> G{
		make_pair(6, -10),
		make_pair(2, -9),
		make_pair(0, -5),
		make_pair(2, -1),
		make_pair(6, 0),
		make_pair(6, -5),
		make_pair(3, -5)
	};
	const vector<Point> H{
		make_pair(0, 0),
		make_pair(0, -10),
		make_pair(0, -5),
		make_pair(7, -5),
		make_pair(7, -10),
		make_pair(7, 0)
	};
	const vector<Point> I{
		make_pair(3, -10),
		make_pair(3, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(0,0),
		make_pair(6, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -10),
		make_pair(6, -10)
	};
	const vector<Point> J{
		make_pair(3, -10),
		make_pair(6, -10), 
		make_pair(6, -4),
		make_pair(6, -2),
		make_pair(4, 0),
		make_pair(2,0)
	};
	const vector<Point> K{
		make_pair(6, -10),
		make_pair(0, -5),
		make_pair(6, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(0,0),
		make_pair(0, -10)
	};
	const vector<Point> L{
		make_pair(0, -10),
		make_pair(0,0),
		make_pair(6, 0)
	};
	const vector<Point> M{
		make_pair(0,0),
		make_pair(0, -10),
		make_pair(3, -6),
		make_pair(6, -10),
		make_pair(6, 0)
	};
	const vector<Point> N{
		make_pair(0,0),
		make_pair(0,-10),
		make_pair(6, 0),
		make_pair(6, -10)
	};
	const vector<Point> O{
		make_pair(2, 0),
		make_pair(4, 0),
		make_pair(6, -2),
		make_pair(6, -8),
		make_pair(4, -10),
		make_pair(2, -10),
		make_pair(0, -8),
		make_pair(0, -2),
		make_pair(2, 0)
	};
	const vector<Point> P{
		make_pair(0, 0),
		make_pair(0, -10),
		make_pair(4, -10),
		make_pair(6, -8),
		make_pair(6, -7),
		make_pair(4, -5),
		make_pair(0, -5)
	};
	const vector<Point> Q{
		make_pair(2, 0),
		make_pair(4, 0),
		make_pair(6, -2),
		make_pair(6, -8),
		make_pair(4, -10),
		make_pair(2, -10),
		make_pair(0, -8),
		make_pair(0, -2),
		make_pair(2, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(6, 0),
		make_pair(3, -3)
	};
	const vector<Point> R{
		make_pair(0, 0),
		make_pair(0, -10),
		make_pair(4, -10),
		make_pair(6, -8),
		make_pair(6, -7),
		make_pair(4, -5),
		make_pair(0, -5),
		make_pair(6, 0)
	};
	const vector<Point> S{
		make_pair(6, -10),
		make_pair(2, -10),
		make_pair(0, -8),
		make_pair(0, -6),
		make_pair(1, -5),
		make_pair(5, -5),
		make_pair(6, -4),
		make_pair(6, -2),
		make_pair(4, 0),
		make_pair(0,0)
	};
	const vector<Point> T{
		make_pair(0, -10),
		make_pair(6, -10),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -10),
		make_pair(3, 0)
	};
	const vector<Point> U{
		make_pair(0, -10),
		make_pair(0, -0),
		make_pair(6, -0),
		make_pair(6, -10)
	};
	const vector<Point> V{
		make_pair(0, -10),
		make_pair(3, 0),
		make_pair(6, -10)
	};
	const vector<Point> W{
		make_pair(0,-10),
		make_pair(0, 0),
		make_pair(3, -4), 
		make_pair(3, -4),
		make_pair(6, 0),
		make_pair(6, -10)
	};
	const vector<Point> X{
		make_pair(0, -10),
		make_pair(6, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(6, -10),
		make_pair(0,0)
	};
	const vector<Point> Y{
		make_pair(0, -10),
		make_pair(3, -6),
		make_pair(6, -10),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -6),
		make_pair(3, 0)
	};
	const vector<Point> Z{
		make_pair(0, -10),
		make_pair(6, -10),
		make_pair(0, 0),
		make_pair(6, 0)
	};

	///////

	const vector<Point> a{
		make_pair(3, -7), 
		make_pair(5, -7),
		make_pair(5, 0), 
		make_pair(0,0),
		make_pair(0, -3),
		make_pair(5, -3),
		make_pair(INFINITY, INFINITY),
		make_pair(5, 0),
		make_pair(6, 0)
	};
	const vector<Point> b{
		make_pair(0, -10),
		make_pair(0,0),
		make_pair(4, 0),
		make_pair(4, -5),
		make_pair(0, -5)
	};
	const vector<Point> c{
		make_pair(4, -5),
		make_pair(1, -5),
		make_pair(0, -3),
		make_pair(0, -1),
		make_pair(1, 0),
		make_pair(4,0)
	};
	const vector<Point> d{
		make_pair(6, -10),
		make_pair(6, 0),
		make_pair(0, 0),
		make_pair(0, -5),
		make_pair(6, -5)
	};	
	const vector<Point> e{
		make_pair(0, -3),
		make_pair(6, -3),
		make_pair(6, -6),
		make_pair(0, -6),
		make_pair(0, 0),
		make_pair(6, 0)
	};
	const vector<Point> f{
		make_pair(3, 0),
		make_pair(3, -7),
		make_pair(4, -8),
		make_pair(6, -9),
		make_pair(6, -10),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -5),
		make_pair(6, -5)
	};
	const vector<Point> g{
		make_pair(5, -5),
		make_pair(5, 5),
		make_pair(1, 5),
		make_pair(INFINITY, INFINITY),
		make_pair(4, -5),
		make_pair(0, -5),
		make_pair(0, 0),
		make_pair(4, 0)
	};
	const vector<Point> h{
		make_pair(5, 0),
		make_pair(5, -3),
		make_pair(4, -4),
		make_pair(0, -4),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -10),
		make_pair(0,0)
	};
	const vector<Point> i{
		make_pair(3, 0),
		make_pair(3, -3),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -6),
		make_pair(3, -7)
	};
	const vector<Point> j{
		make_pair(3, -7),
		make_pair(3, -6),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -3),
		make_pair(3, 3),
		make_pair(2, 3)
	};
	const vector<Point> k{
		make_pair(0, -10),
		make_pair(0,0),
		make_pair(INFINITY, INFINITY),
		make_pair(4, -6),
		make_pair(0, -4),
		make_pair(4, 0)
	};
	const vector<Point> l{
		make_pair(0, -10),
		make_pair(3, -10),
		make_pair(3, 0),
		make_pair(0, 0),
		make_pair(6, 0)
	};
	const vector<Point> m{
		make_pair(0,0),
		make_pair(0,-5),
		make_pair(3,-5),
		make_pair(3,0),
		make_pair(3,-5),
		make_pair(6,-5),
		make_pair(6,0)
	};
	const vector<Point> n{
		make_pair(0, 0),
		make_pair(0, -5),
		make_pair(3, -5),
		make_pair(3, 0),
	};
	const vector<Point> o{
		make_pair(0, 0),
		make_pair(0, -5),
		make_pair(4, -5),
		make_pair(4, 0),
		make_pair(0, 0),
	};
	const vector<Point> p{
		make_pair(0, -5),
		make_pair(0,5),
		make_pair(INFINITY, INFINITY),
		make_pair(0,-5),
		make_pair(4,-5),
		make_pair(4,0),
		make_pair(0,0)
	};
	const vector<Point> q{
		make_pair(5, -5),
		make_pair(5, 5),
		make_pair(INFINITY, INFINITY),
		make_pair(4, -5),
		make_pair(0, -5),
		make_pair(0, 0),
		make_pair(4, 0)
		
	};
	const vector<Point> r{
		make_pair(0, -6),
		make_pair(0, 0),
		make_pair(0, -3),
		make_pair(0, -5),
		make_pair(5, -6)
	};
	const vector<Point> s{
		make_pair(5, -6),
		make_pair(0, -6),
		make_pair(0, -3),
		make_pair(5, -3),
		make_pair(5, 0),
		make_pair(0,0)
	};
	const vector<Point> t{
		make_pair(3, -8),
		make_pair(3, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(1, -6),
		make_pair(5, -6)
	};
	const vector<Point> u{
		make_pair(0, -5),
		make_pair(0,0),
		make_pair(4, 0),
		make_pair(4, -5)
	};
	const vector<Point> v{
		make_pair(0, -5),
		make_pair(3, 0),
		make_pair(6, -5)
	};
	const vector<Point> w{
		make_pair(0, -5),
		make_pair(1, 0),
		make_pair(3,-3),
		make_pair(5, 0),
		make_pair(6, -5)
	};
	const vector<Point> x{
		make_pair(6, -5),
		make_pair(0,0),
		make_pair(INFINITY, INFINITY),
		make_pair(0,-5),
		make_pair(6, 0)
	};
	const vector<Point> y{
		make_pair(0, -5),
		make_pair(3, 0),
		make_pair(6, -5),
		make_pair(1, 3)
	};
	const vector<Point> z{
		make_pair(0, -5), 
		make_pair(5, -5),
		make_pair(0,0),
		make_pair(5, 0)
	};
	
	///////

	const vector<Point> num0{
		make_pair(2, 0),
		make_pair(4, 0),
		make_pair(6, -2),
		make_pair(6, -8),
		make_pair(4, -10),
		make_pair(2, -10),
		make_pair(0, -8),
		make_pair(0, -2),
		make_pair(2, 0), 
		make_pair(INFINITY, INFINITY),
		make_pair(6, -8),
		make_pair(0, -2)
	};
	const vector<Point> num1{
		make_pair(1, -8),
		make_pair(3, -10),
		make_pair(3, 0)
	};
	const vector<Point> num2{
		make_pair(0, -10),
		make_pair(6, -10),
		make_pair(6, -5),
		make_pair(0, -5),
		make_pair(0,0),
		make_pair(6, 0)
	};
	const vector<Point> num3{
		make_pair(0, -10),
		make_pair(6, -10),
		make_pair(6, -5),
		make_pair(3, -5), 
		make_pair(6, -5),
		make_pair(6, 0),
		make_pair(0,0)
	};
	const vector<Point> num4{
		make_pair(5, 0),
		make_pair(5, -10),
		make_pair(0, -5),
		make_pair(6, -5)
	};
	const vector<Point> num5{
		make_pair(6, -10),
		make_pair(0, -10),
		make_pair(0, -5),
		make_pair(6, -5),
		make_pair(6, 0),
		make_pair(0,0)

	};
	const vector<Point> num6{
		make_pair(3, -10),
		make_pair(0, -10),
		make_pair(0,0),
		make_pair(5, 0),
		make_pair(5, -5),
		make_pair(0, -5)
	};
	const vector<Point> num7{
		make_pair(0, -10),
		make_pair(6, -10),
		make_pair(0,0)
	};
	const vector<Point> num8{
		make_pair(0, 0),
		make_pair(0, -10),
		make_pair(7, -10),
		make_pair(7, 0),
		make_pair(0, 0),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -5),
		make_pair(6, -5)
		
	};
	const vector<Point> num9{
		make_pair(6, 0),
		make_pair(6, -10),
		make_pair(1, -10),
		make_pair(1, -5), 
		make_pair(6, -5)
	};

	///////
	const vector<Point> space{
	};
	const vector<Point> excPoint{
		make_pair(3, -5),
		make_pair(3, -10),
		make_pair(4, -10),
		make_pair(4, -5),
		make_pair(INFINITY, INFINITY), //lift pen
		make_pair(4, -1),
		make_pair(4, 0),
		make_pair(3, 0),
		make_pair(3, -1)
	};
	const vector<Point> pipe{
		make_pair(2, -10),
		make_pair(2, 0),
		make_pair(3, 0),
		make_pair(3, -10)
	};
	const vector<Point> qMark{
		make_pair(3, -10),
		make_pair(5, -10),
		make_pair(6, -9),
		make_pair(6, -7),
		make_pair(5, -6),
		make_pair(3, -6),
		make_pair(3, -4),
		make_pair(INFINITY, INFINITY),
		make_pair(3, 0),
		make_pair(4, 0)
		
	};
	const vector<Point> comma{
		make_pair(2, 2),
		make_pair(3, -1), 
		make_pair(4, -1), 
		make_pair(3, 2),
	};
	const vector<Point> singleQuote{
		make_pair(3, -10),
		make_pair(3, -6)
	};
	const vector<Point> doubleQuote{
		make_pair(2, -10),
		make_pair(2, -6),
		make_pair(INFINITY, INFINITY),
		make_pair(4, -10),
		make_pair(4, -6)
	};
	const vector<Point> semicolon{
		make_pair(3, -8),
		make_pair(3, -7),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -3),
		make_pair(3, 0)
	};
	const vector<Point> colon{
		make_pair(3, -8),
		make_pair(3, -7),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -3),
		make_pair(3, -2)
	};
	const vector<Point> period{
		make_pair(3, 0),
		make_pair(4, 0)
	};
	const vector<Point> fSlash{
		make_pair(0, 0),
		make_pair(6, -10)
	};
	const vector<Point> bSlash{
		make_pair(0, -10),
		make_pair(6, 0)
	};
	const vector<Point> plus{
		make_pair(0, -5),
		make_pair(6, -5),
		make_pair(INFINITY, INFINITY),
		make_pair(3, -8),
		make_pair(3, -2)
	};
	const vector<Point> minus{
		make_pair(0, -5),
		make_pair(6, -5)
	};
	const vector<Point> underscore{
		make_pair(0, 0),
		make_pair(6, 0)
	};
	const vector<Point> equals{
		make_pair(0, -7),
		make_pair(6, -7),
		make_pair(INFINITY, INFINITY),
		make_pair(0, -3),
		make_pair(6, -3)
	};

	const vector<Point> placeholder{
		make_pair(0, 0),
		make_pair(0, -10),
		make_pair(7, -10),
		make_pair(7, 0),
		make_pair(0, 0)
	};
}