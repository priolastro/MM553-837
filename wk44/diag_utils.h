//diag_utils.h
//utilities for matrix diagonalization

#ifndef __diag_utils_h__
#define __diag_utils_h__

#include <complex>
#include <vector>
#include <exception>

extern "C" 
	{
		void zpotrf_(char*, int*, std::complex<double>*, int*, int*);

		void dpotrf_(char*, int*, double*, int*, int*);




		void zgesvd_(char*, char*, int*, int*, std::complex<double>*, int*, double*, 
				std::complex<double>*, int*, std::complex<double>*, int*, std::complex<double>*, int*,
				double*, int*);

		void dgesvd_(char*, char*, int*, int*, double*, int*, double*, 
				double*, int*, double*, int*, double*, int*, int*);




		void zgesv_( int*, int*, std::complex<double>*, int*, int*, std::complex<double>*,
				int*, int* );

		void dgesv_( int*, int*, double*, int*, int*, double*,
				int*, int* );



		void zhpev_( char*, char*, int*, std::complex<double>*, double*, 
				std::complex<double>*, int*, std::complex<double>*, double*, int*);

		void dspev_( char*, char*, int*, double*, double*, 
				double*, int*, double*, int*);
		
		void dsygv_(int*, char*, char*, int*, double*, int*, double*, int*,
				double*, double*, int*, int*);
		
		void zhegv_(int*, char*, char*, int*, std::complex<double>*, int*, 
				std::complex<double>*, int*,
				double*, std::complex<double>*, int*, double*, int*);

	}


	//-------------------------------------------------------------------------
	
	//Diagonalize a hermitian matrix
	void diag_herm( 
			const std::vector<std::vector<std::complex<double> > >& mat_in, 
			std::vector<std::vector<std::complex<double> > >& evecs, 
			std::vector<std::complex<double> >& evals) {

		//convert MatrixComplex to an array of complex<double>
		int n1 = mat_in.size();
		int n2 = mat_in[0].size();

		if (n1!=n2) 
			throw(std::logic_error("Matrix input to diag_herm must be square!")); 

		//Check that the matrix is hermitian
		int n = n1;

		for (int i = 0 ; i < n ; i++)
			for (int j = 0 ; j < i ; ++j) {

				std::complex<double> temp1 = mat_in[i][j];
				std::complex<double> temp2 = conj(mat_in[j][i]);

				double tol = 0.0000001;

				std::complex<double> diff = temp1 - temp2;

				if (sqrt( real(conj(diff)*diff)) > tol)  
				{
					std::cerr << "temp1 = " << temp1 << std::endl;
					std::cerr << "temp2 = " << temp2 << std::endl;
					throw std::logic_error("in diag_herm: Matrix is not hermitian");
				}

			}

		std::complex<double>* a = new std::complex<double>[n*n];
		for (int j = 1; j <= n; ++j)
			for (int i = 1; i <= j; ++i) {

				int k = i + (j - 1) * j /2 - 1;
				std::complex<double> ctemp = mat_in[i-1][j-1]; 

				a[k] = ctemp;

			}

		int itype = 1;
		char jobz = 'V';
		char uplo = 'U';
		int lwork = 2*n;

		std::complex<double>* cwork = new std::complex<double> [lwork];

		int lrwork = 	3*n;

		double* rwork = new double[lrwork];
		int ldz = n;

		std::complex<double>* z = new std::complex<double> [n*n];

		double *w = new double[n];

		int info = 0;

		//Call the diag routine
		zhpev_(&jobz, &uplo, &n, a, w, z, &ldz, cwork, rwork, &info);
		if (info < 0) {
			std::cerr << "info = " << info <<std::endl;
			throw(std::logic_error( 
						"Bad arguments to diagonalization routine"));
		}
		if (info > 0) {
		std::cerr << "info = " << info <<std::endl;
			throw(std::logic_error(
						"diagonalization could not be completed")); 
		}

		evals.resize(n);
		evecs.resize(n);
		for (int v = 0 ; v < n ; ++v) {
			evals[v] = w[v];

			evecs[v].resize(n);

			for (int i = 0 ; i < n ; ++i) {
				int k = i + v*n;
				evecs[v][i] = z[k];
			}
		}


		delete[] a;
		delete[] w;
		delete[] z;
		delete[] cwork;
		delete[] rwork;

	}

	//--------------------------------------------------------------------------

	//Diagonalize a real symmetric matrix
	void diag_symm( const std::vector<std::vector<double> >& mat_in, 
			std::vector<std::vector<double> >& evecs, 
			std::vector<double>& evals) {

		//convert MatrixComplex to an array of complex<double>
		int n1 = mat_in.size();
		int n2 = mat_in[0].size();

		if (n1!=n2) 
			throw(std::logic_error("Matrix input to diag_herm must be square!")); 

		//Check that the matrix is symmetric
		int n = n1;

		for (int i = 0 ; i < n ; i++)
			for (int j = 0 ; j < i ; ++j) {

				double temp1 = mat_in[i][j];
				double temp2 = mat_in[j][i];

				double tol = 0.0000001;
				double diff = temp1 - temp2;

				if (sqrt(diff*diff) > tol) {
				std::cerr << "temp1 = " << temp1 << std::endl;
				std::cerr << "temp2 = " << temp2 << std::endl;
					throw std::logic_error("in diag_symm: Matrix is not symmetric");
				}

			}

		double* a = new double[n*n];
		for (int j = 1; j <= n; ++j)
			for (int i = 1; i <= j; ++i) {
				int k = i + (j - 1) * j /2 - 1;
				double temp = mat_in[i - 1][j - 1];
				a[k] = temp;
			}

		int itype = 1;
		char jobz = 'V';
		char uplo = 'U';

		int lwork = 	3*n;

		double* work = new double[lwork];
		int ldz = n;

		double* z = new double [n*n];

		double *w = new double[n];

		int info = 0;

		//Call the diag routine
		dspev_(&jobz, &uplo, &n, a, w, z, &ldz, work, &info);
		if (info < 0) {
			std::cerr<< info << std::endl;
			throw std::logic_error("Bad arguments to diagonalization routine");
		}
		if (info > 0) {
		std::cerr<< info << std::endl;
			throw std::logic_error("diagonalization could not be completed");
		}

		evals.resize(n);
		evecs.resize(n);
		for (int v = 0 ; v < n ; ++v) {
			evals[v] = w[v];
			evecs[v].resize(n);	
			for (int i = 0 ; i < n ; ++i) {
				int k = i + v*n;
				double temp = z[k];
				evecs[v][i]=temp;
			}
		}

		delete[] a;
		delete[] w;
		delete[] z;
		delete[] work;

	}

#endif
