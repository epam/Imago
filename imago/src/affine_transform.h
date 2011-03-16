#ifndef _affine_transform_h_
#define _affine_transform_h_

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "stl_fwd.h"

namespace imago
{
   namespace affine
   {
      using namespace boost::numeric::ublas;


      /* Matrix inversion routine.
       Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
      template<class T>
      bool InvertMatrix( const matrix<T> &input, matrix<T> &inverse )
      {
         typedef permutation_matrix<std::size_t> pmatrix;

         // create a working copy of the input
         matrix<T> A(input);

         // create a permutation matrix for the LU-factorization
         pmatrix pm(A.size1());

         // perform LU-factorization
         int res = lu_factorize(A, pm);
         if (res != 0)
            return false;

         // create identity matrix of "inverse"
         inverse.assign(identity_matrix<T> (A.size1()));

         // backsubstitute to get the inverse
         lu_substitute(A, pm, inverse);

         return true;
      }

      template<class T>
      bool PseudoInvertMatrix( const matrix<T> &input, matrix<T> &inverse )
      {
         matrix<T> A(input);
         matrix<T> AT = trans(A);

         matrix<T> ATA = prod(AT, A);
         matrix<T> ATAinv(ATA.size1(), ATA.size1());

         if (!InvertMatrix(ATA, ATAinv))
            return false;

         inverse = prod(ATAinv, AT);
         return true;
      }

      class AffineTransform
      {
      public:
         AffineTransform( const Points2i &from, const Points2i &to, const std::vector<int> &mapping ) : o(3)
         {
            matrix<double> P(from.size(), 3), Q(to.size(), 3);
            Points2i mappedTo(to.size());

            for (int i = 0; i < (int)to.size(); ++i)
            {
               mappedTo[i] = to[mapping[i]];

               o(0) += from[i].x - mappedTo[i].x;
               o(1) += from[i].y - mappedTo[i].y;
            }

            o(2) = 0;
            o /= to.size();

            for (int i = 0; i < (int)from.size(); ++i)
            {
               P(i, 0) = 1, P(i, 1) = from[i].x - o(0), P(i, 2) = from[i].y - o(1);
               Q(i, 0) = 1, Q(i, 1) = mappedTo[i].x - o(0), Q(i, 2) = mappedTo[i].y - o(1);
            }

            matrix<double> Qpinv(Q.size1(), Q.size2());

            if (!PseudoInvertMatrix(Q, Qpinv))
            {
               puts("***Affine modeling FAILED!!!***");
               return;
            }

            A = trans(prod(Qpinv, P));
            std::cout << "A:\n" << A;
         }
         Vec2i interpolate( const Vec2i &v )
         {
            vector<double> bv(3), res(3);
            bv(0) = v.x, bv(1) = v.y; bv(2) = 0;
            res = prod(A, bv) + o;
            return Vec2i(res(0), res(1));
         }
      private:
         matrix<double> A;
         vector<double> o;
      };

   }
}


#endif /* _affine_transform_h_ */
