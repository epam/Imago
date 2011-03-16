/*
 * tpsinterpolate.h
 * license: http://www.boost.org/LICENSE_1_0.txt
 *  Created on: 18 Aug 2010
 *      Author: Peter Stroia-Williams
 */

#ifndef _tpsinterpolate_h_
#define _tpsinterpolate_h_

#include <vector>
#include <cmath>

#include <boost/array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace tps
{
   using namespace boost::numeric::ublas;
   using namespace boost;
   using namespace std;

   double radial_basis( double r )
   {
      if (r == 0.0)
         return 0.0;
      return pow(r, 2) * log(r);
   }

   template<typename T1, typename T2, int Dim>
   double radialbasis( const array<T1, Dim> & v1, const array<T2, Dim> & v2 )
   {
      boost::numeric::ublas::vector<double> v(Dim);
      for (unsigned int i(0); i < v.size(); ++i)
      {
         v(i) = v1[i] - v2[i];
      }
      return radial_basis(norm_2(v));
   }

   template<int PosDim, int ValDim, typename WorkingType = double>
   class ThinPlateSpline
   {
   public:
      matrix<WorkingType> Wa;
      std::vector<array<WorkingType, PosDim> > refPositions;

      ThinPlateSpline()
      {
      }

      ThinPlateSpline( std::vector<array<WorkingType, PosDim> > positions,
                       std::vector<array<WorkingType, ValDim> > values )
      {
         matrix<WorkingType> L;

         refPositions = positions;

         const int numPoints(refPositions.size());
         const int WaLength(numPoints + PosDim + 1);

         L = matrix<WorkingType> (WaLength, WaLength);

         // Calculate K and store in L
         for (int i(0); i < numPoints; i++)
         {
            L(i, i) = 0.0;
            // K is symmetrical so no point in calculating things twice
            int j(i + 1);
            for (; j < numPoints; ++j)
            {

               L(i, j) = L(j, i) =
                     radialbasis<WorkingType, WorkingType, PosDim> ( refPositions[i],
                                                                     refPositions[j] );
            }

            // construct P and store in K
            L(j, i) = L(i, j) = 1.0;
            ++j;
            for (int posElm(0); j < WaLength; ++posElm, ++j)
               L(j, i) = L(i, j) = positions[i][posElm];
         }

         // O
         for (int i(numPoints); i < WaLength; i++)
            for (int j(numPoints); j < WaLength; j++)
               L(i, j) = 0.0;

         // Solve L^-1 Y = W^T

         typedef permutation_matrix<std::size_t> pmatrix;

         matrix<WorkingType> A(L);
         pmatrix pm(A.size1());
         int res = lu_factorize(A, pm);
         if (res != 0)
            ;//TODO catch this error

         matrix<WorkingType> invL(identity_matrix<WorkingType> (A.size1()));
         lu_substitute(A, pm, invL);

         Wa = matrix<WorkingType> (WaLength, ValDim);

         matrix<WorkingType> Y(WaLength, ValDim);
         int i(0);
         for (; i < numPoints; i++)
            for (int j(0); j < ValDim; ++j)
               Y(i, j) = values[i][j];

         for (; i < WaLength; i++)
            for (int j(0); j < ValDim; ++j)
               Y(i, j) = 0.0;

         Wa = prod(invL, Y);

      }

      array<WorkingType, ValDim> interpolate( const array<WorkingType, PosDim> &position ) const
      {
         array<WorkingType, ValDim> result;
         // Init result
         for (int j(0); j < ValDim; ++j)
            result[j] = 0;

         unsigned int i(0);
         for (; i < Wa.size1() - (PosDim + 1); ++i)
         {
            for (int j(0); j < ValDim; ++j)
               result[j] += Wa(i, j) * radialbasis<WorkingType, WorkingType,
                     PosDim> (refPositions[i], position);
         }

         for (int j(0); j < ValDim; ++j)
            result[j] += Wa(i, j);
         ++i;

         for (int k(0); k < PosDim; ++k, ++i)
         {
            for (int j(0); j < ValDim; ++j)
               result[j] += Wa(i, j) * position[k];
         }
         return result;
      }

   };
}
#endif /* _tpsinterpolate_h_ */
