// Copyright (c) 2004  Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>
//                 Andreas Meyer <ameyer@mpi-sb.mpg.de>

#ifndef CGAL_BOX_INTERSECTION_D_BOX_D_H
#define CGAL_BOX_INTERSECTION_D_BOX_D_H

#include <CGAL/basic.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Box_intersection_d/box_limits.h>
#include <algorithm>

CGAL_BEGIN_NAMESPACE

namespace Box_intersection_d {

// Pseudo template class to skip the need for a C file for the static counter
template <class Dummy>
struct Unique_numbers {
    typedef std::size_t Id_type;
    Unique_numbers() : i(n++) {}
    std::size_t id() const { return i; }
private:
    static std::size_t n;
    std::size_t i;
};
template <class Dummy>
std::size_t Unique_numbers<Dummy>::n = 0;


// Policies for id-number of boxes
struct ID_NONE {};
struct ID_EXPLICIT {};
struct ID_FROM_BOX_ADDRESS {};
struct ID_FROM_HANDLE {};

// Generic template signature of boxes, specialized for policies
template<class NT_, int N, class IdPolicy = ID_EXPLICIT> 
class Box_d;

// ID_NONE is used as base class and cannot be used directly in the algorithms
template<class NT_, int N>
class Box_d< NT_, N, ID_NONE> {
protected:
    NT_ lo[N];
    NT_ hi[N];
public:
    typedef NT_         NT;
    typedef std::size_t Id_type;

    Box_d() {}
    Box_d(bool complete) { init(complete); }
    Box_d(NT l[N], NT h[N]) {
        std::copy( l, l + N, lo );
        std::copy( h, h + N, hi );
    }
    void init (bool complete = false) {
        NT inf = box_limits<NT>::inf();
        NT sup = box_limits<NT>::sup();
        if(!complete)
            std::swap(inf,sup);
        std::fill( lo, lo+N, inf );
        std::fill( hi, hi+N, sup );
    }
    void extend(NT p[N]) {
        for( int dim = 0; dim < N; ++dim ) {
            lo[dim] = std::min( lo[dim], p[dim] );
            hi[dim] = std::max( hi[dim], p[dim] );
        }
    }
    static const int dimension() { return N; }
    NT min_coord(int dim) const { return lo[dim]; }
    NT max_coord(int dim) const { return hi[dim]; }
};

// Specialization for Bbox_2, i.e. double and dim 2.
template<>
class Box_d< double, 2, ID_NONE> {
protected:
    Bbox_2 bbx;
public:
    typedef double      NT;
    typedef std::size_t Id_type;

    Box_d() {}
    Box_d(bool complete) { init(complete); }
    Box_d(NT l[2], NT h[2]) : bbx(l[0], l[1], h[0], h[1]) {}
    Box_d( const Bbox_2& b) : bbx( b) {}
    const Bbox_2& bbox() const { return bbx; }
    void init () {
        NT inf = box_limits<NT>::inf();
        NT sup = box_limits<NT>::sup();
        bbx = Bbox_2( sup, sup, inf, inf);
    }
    void init (bool complete) {
        NT inf = box_limits<NT>::inf();
        NT sup = box_limits<NT>::sup();
        if ( complete)
            bbx = Bbox_2( inf, inf, sup, sup);
        else
            bbx = Bbox_2( sup, sup, inf, inf);
    }
    void extend(NT p[2]) {
        bbx = Bbox_2(
            std::min( bbx.xmin(), p[0]),
            std::min( bbx.ymin(), p[1]),
            std::max( bbx.xmax(), p[0]),
            std::max( bbx.ymax(), p[1]));
    }
    static const int dimension() { return 2; }
    NT min_coord(int dim) const { return (dim==0) ? bbx.xmin() : bbx.ymin();}
    NT max_coord(int dim) const { return (dim==0) ? bbx.xmax() : bbx.ymax();}
};

// Specialization for Bbox_3, i.e. double and dim 3.
template<>
class Box_d< double, 3, ID_NONE> {
protected:
    Bbox_3 bbx;
public:
    typedef double      NT;
    typedef std::size_t Id_type;

    Box_d() {}
    Box_d(bool complete) { init(complete); }
    Box_d(NT l[3], NT h[3]) : bbx(l[0], l[1], l[2], h[0], h[1], h[2]) {}
    Box_d( const Bbox_3& b) : bbx( b) {}
    const Bbox_3& bbox() const { return bbx; }
    void init () {
        NT inf = box_limits<NT>::inf();
        NT sup = box_limits<NT>::sup();
        bbx = Bbox_3( sup, sup, sup, inf, inf, inf);
    }
    void init (bool complete) {
        NT inf = box_limits<NT>::inf();
        NT sup = box_limits<NT>::sup();
        if ( complete)
            bbx = Bbox_3( inf, inf, inf, sup, sup, sup);
        else
            bbx = Bbox_3( sup, sup, sup, inf, inf, inf);
    }
    void extend(NT p[3]) {
        bbx = Bbox_3(
            std::min( bbx.xmin(), p[0]),
            std::min( bbx.ymin(), p[1]),
            std::min( bbx.zmin(), p[2]),
            std::max( bbx.xmax(), p[0]),
            std::max( bbx.ymax(), p[1]),
            std::max( bbx.zmax(), p[2]));
    }
    static const int dimension() { return 3; }
    NT min_coord(int dim) const { 
        return (dim==0) ? bbx.xmin() : ((dim==1) ? bbx.ymin() : bbx.zmin());
    }
    NT max_coord(int dim) const {
        return (dim==0) ? bbx.xmax() : ((dim==1) ? bbx.ymax() : bbx.zmax());
    }
};

// ID_EXPLICIT
template<class NT_, int N>
class Box_d< NT_, N, ID_EXPLICIT> : public Box_d< NT_, N, ID_NONE>,
                                    public Unique_numbers<int> {
public:
    typedef Box_d< NT_, N, ID_NONE> Base;
    typedef NT_                     NT;
    typedef typename Unique_numbers<int>::Id_type Id_type;
    Box_d() {}
    Box_d(bool complete) : Base(complete) {}
    Box_d(NT l[N], NT h[N]) : Base( l, h) {}
    Box_d( const Bbox_2& b) : Base( b) {}
    Box_d( const Bbox_3& b) : Base( b) {}
};

// ID_FROM_BOX_ADDRESS
template<class NT_, int N>
class Box_d< NT_, N, ID_FROM_BOX_ADDRESS> : public Box_d< NT_, N, ID_NONE> {
public:
    typedef Box_d< NT_, N, ID_NONE> Base;
    typedef NT_                     NT;
    typedef std::size_t             Id_type;

    Box_d() {}
    Box_d(bool complete) : Base(complete) {}
    Box_d(NT l[N], NT h[N]) : Base( l, h) {}
    Box_d( const Bbox_2& b) : Base( b) {}
    Box_d( const Bbox_3& b) : Base( b) {}
    Id_type  id() const { return reinterpret_cast<Id_type>(this); }
};


} // end namespace Box_intersection_d


CGAL_END_NAMESPACE

#endif
