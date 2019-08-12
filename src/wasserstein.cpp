// [[Rcpp::depends(RcppArmadillo)]]

#include <csignal>
#include <iostream>
#include <math.h>
#include <RcppArmadillo.h>
#include <RcppArmadilloExtensions/sample.h>

#define END "\n";

using namespace arma;
using namespace std;
using namespace Rcpp;



/*=============================================

				VECTOR OPERATIONS

==============================================*/ 

//' vector_factor_addition
//'
//' @param x vector 
//' @param summand numerical
//' @return a vector containing the sum of each element in x and the summand
//'
template <typename T>
vector<T> operator+(vector<T> x, T summand)
{
	vector<T> result(x.begin(), x.end());

	for (T & element : result) {
		element = element + summand;
	}
	return result;
}

//' vector_vector_addition
//'
//' @param x vector 
//' @param y vector
//' @return a vector containing at each position i the sum of x[i] + y[i]
//'
template <typename T>
vector<T> operator+(vector<T> x, vector<T> y)
{
	if (x.size() != y.size()) {
		stop("add: Sizes of vectors x and y are incompatible.");
	} else {
		vector<T> result(x.begin(), x.end());
		for (int i=0; i<x.size(); i++) {
			result[i] = x[i] + y[i];
		}
		return result;
	}
}

//' vector_factor_multiplication
//'
//' @param x vector 
//' @param factor numerical
//' @return a vector containing the product of each element in x and the factor
//'
template <typename T>
vector<T> operator*(const vector<T> & x, const T & factor)
{ 
  vector<T> result(x.begin(), x.end());
  
  for (T & element : result) {
    element = element * factor;
  }

  return result;
}

//' vector_vector_multiplication
//'
//' @param x vector 
//' @param y vector
//' @return a vector containing at each position i the product  x[i] * y[i]
//'
template <typename T>
vector<T> operator*(const vector<T> & x, const vector<T> & y)
{ 
  vector<T> result(x.begin(), x.end());
  if (x.size() != y.size()) {
  	std::stringstream ss;
  	ss 	<< "multiply: Sizes of vectors x and y are incompatible. "
  		<< "Attempting multiplication by factor with y[0]";
  	warning(ss.str());

  	if (y.size() >=1) {
  		const double factor = y[0];
  		result = x * factor;
  	} else {
  		stop("Invalid vector y");
  	}
  } else {
    for (int i=0; i<x.size(); i++) {
      result[i] = x[i] * y[i];
    }
  }
  return result;
}

//' vector_vector_subtract
//'
//' @param x vector 
//' @param y vector
//' @return vector representing the subtraction x - y
//'
template <typename T>
vector<T> operator-(const vector<T> & x, const vector<T> & y)
{
  if (x.size() != y.size()) {
  	stop("subtract: Sizes of vectors x and y are incompatible.");
  } else {
  	vector<T> result(x.begin(), x.end());
    for (int i=0; i<x.size(); i++) {
      result[i] = x[i] - y[i];
    }
    return result;
  }
}

//' vector_factor_division
//'
//' @param x vector 
//' @param divisor numerical
//' @return a vector containing the result of each 
//'   element in x divided by divisor
//'
template <typename T>
vector<T> operator/(const vector<T> & x, const T & divisor)
{
  vector<T> result(x.begin(), x.end());
  for (T& element : result) {
    element = element / divisor;
  }
  return result;
}

//' vector_vector_division
//'
//' @param x vector 
//' @param y vector
//' @return a vector containing the product of each element
//'   in x and the factor
//'
template <typename T>
vector<T> operator/(const vector<T> & x, const vector<T> & y)
{ 
  vector<T> result(x.begin(), x.end());
  if (x.size() != y.size()) {
  	std::stringstream ss;
  	ss 	<< "divide: Sizes of vectors x and y are incompatible. "
  		<< "Attempting division of x by y[0] ...";
  	warning(ss.str());

  	if (y.size() >=1) {
  		const double divisor = y[0];
  		result = x / divisor;
  	} else {
  		stop("Invalid vector y");
  	}
  } else {
    for (int i=0; i<x.size(); i++) {
      result[i] = x[i] / y[i];
    }
  }
  return result;
}


//' vector_pow
//'
//' @param x vector 
//' @param exp numerical representing the exponent
//' @return a vector containing a copy of x with each 
//'   element raised to the power of exp
//'
template <typename T>
vector<T> pow(const vector<T> & x, const T & exp)
{
  vector<T> result(x.begin(), x.end());
  for (T& element : result) {
    element = pow(element, exp);
  }
  return result;
}

//' vector_sum
//'
//' @param x vector with numerical elements 
//' @return The sum of all elements in x
//'
template <typename T>
T sum(const vector<T> & x) 
{
  T result = 0;
  for(const T& element : x) {
    result += element;
  }
  return result;
}


//' vector_mean
//'
//' @param x vector with numericals
//' @return the average of all elements in x
//'
template <typename T>
double mean(const vector<T> & x)
{	

 		double sum = 0.0;
 		double result = 0.0;

 		for (const double& element : x)
 		{
 			sum += element;
 		}

 		result = sum / x.size();
 		return result;
}

//' vector_standard_deviation
//'
//' @param x vector with numericals
//' @return the standard deviation of all elements in x
//'
template <typename T>
double sd(const vector<T> & x)
{
	double mean_x = mean(x);
	double sum = 0.0;

	for (const T& number : x) {
		sum += pow((number - mean_x), 2);
	}

	double result = sqrt(sum / (x.size() - 1));
	return result;
}

//' vector_absolute
//'
//' @param x vector with numericals
//' @return vector with the absolute values of all elements in x
//'
template <typename T>
vector<T> abs(const vector<T> & x) 
{	

	vector<T> out(x.begin(), x.end());
	for (double& element : out)
	{	
		element = abs(element);
	}
	
	return out;

}


//' max
//'
//' @param x unsorted vector with numerals
//' @return the maximum value in x
template <typename T>
vector<T> max(const vector<T> & x)
{	
	if (x.size() < 1) {
		stop("max: vector x contains no elements.");
	}
	
	T max_val = x[0];
	for (const T & el : x) {
		if (el > max_val) {
			max_val = el;
		}
	}
	return max_val;
}


//' min
//'
//' @param x unsorted vector with numerals
//' @return the minimum value in x
template <typename T>
vector<T> min(const vector<T> & x)
{
	if (x.size() < 1) {
		stop("min: vector x contains no elements.");
	}
	
	T min_val = x[0];
	for (const T & el : x) {
		if (el < min_val) {
			min_val = el;
		}
	}
	return min_val;
}


/*=============================================

			ALGORITHMS ON VECTORS

==============================================*/ 


//' Repeat weighted
//'
//' Each element x[i] in the given input vector x is repeated according
//' to the weight vector at position i
//'
//' @param x vector with numeric elements
//' @param freq_table vector<int> representing the numer of repeats
//' @return the weight-repeated NumericVector of x
//'
vector<double> rep_weighted(vector<double> x,
						   vector<int> freq_table)
{
	// build a new vector x_weighted, that repeats every element at position i
	// in x according to the frequency given at position i in freq_table
	int length = sum(freq_table);
	vector<double> x_weighted(length);

	// iterate over all fields of the new weighted vector
	vector<double>::iterator it = x_weighted.begin();
	vector<double>::iterator it_end = x_weighted.end();

	if(it != it_end) {

    	// iterator over all elements in the original vector
    	for(int i=0; i<x.size(); i++) {

    		// iterator over the number of repeats assigned 
    		// to each element in the original vector
    		for (int n=0; n<freq_table[i]; n++) {
    			
    			// copy value from original vector
    			*it = x[i];

    			// increment the iterator
    			++it;
    		}
    	}
    }

    return x_weighted;

}


//' vector_concatenate
//'
//' `concat` returns a vector that represents the concatenation of two input
//' vectors. The elements of the second given vector are appended to a copy of
//' the first vector.
//'
//' @param x vector
//' @param y vector
//' @return concatenation of y after x
//'
vector<double> concat(vector<double> & x, vector<double> & y)
{	
	vector<double> out(x.size() + y.size());
	vector<double>::iterator x_it = x.begin();
	vector<double>::iterator x_it_end = x.end();
	vector<double>::iterator y_it = y.begin();
	vector<double>::iterator y_it_end = y.end();
	vector<double>::iterator out_it = out.begin();
	vector<double>::iterator out_it_end = out.end();

	for(; x_it != x_it_end; ++x_it, ++out_it){
		*out_it = *x_it;
	}
	for(; y_it != y_it_end; ++y_it, ++out_it){
		*out_it = *y_it;
	}

	return out;
}


//' vector_vector_correlation
//'
//' @param x vector with numericals
//' @param y vector with numericals
//' @param mean_x optional pre-calculated mean of x
//' @param mean_y optional pre-calculated mean of y
//' @return pearsons correlation of the vectors x and y
//'
template <typename T>
double cor(const vector<T> & x, const vector<T> & y, 
	double mean_x = std::numeric_limits<double>::infinity(), 
	double mean_y = std::numeric_limits<double>::infinity())
{	
	if (x.size() != y.size()){
		stop("cor: Vector x and y have incompatible size.");
	}

	// calculate empirical means if needed
	if (mean_x == numeric_limits<double>::infinity()) {
		mean_x = mean(x);
	}
	if (mean_y == numeric_limits<double>::infinity()) {
		mean_y = mean(y);
	}

	double 	r = 0.0, numerator = 0.0, denom_x = 0.0, denom_y = 0.0,
			delta_xval = 0.0, delta_yval = 0.0, denominator = 0.0;

	for (int i=0; i<x.size(); i++){
		delta_xval = x[i] - mean_x;
		delta_yval = y[i] - mean_y;

		numerator += delta_xval * delta_yval;

		denom_x += pow(delta_xval, 2);
		denom_y += pow(delta_yval, 2); 
	}

	denom_y = pow(denom_y, 1.0/2.0);
	denom_x = pow(denom_x, 1.0/2.0);
	denominator = denom_x * denom_y;

	r = numerator / denominator;

	return r;

}


//' vector_cumulative_sum
//' 
//' The cumulative sum x[i] is the sum of all previous elements in x:
//' x[i] = x[i-1] + x[i-2] + ... + x[0]
//'
//' @param x vector of numericals
//' @return a vector containing cumulative sums of the values in x
//'
template <typename T>
vector<T> cumSum(const std::vector<T> & x, const int last_index=0)
{
	
	int upper = ((last_index > 0) && (last_index <= x.size()) 
				? last_index
				: x.size());

	vector<T> out(upper);

	for (int i=0; i<upper; i++){
		if (i==0){
			out[i] = x[i];
		} else {
			out[i] = x[i] + out[i-1];
		}
	}

	return out;
}


template <typename T>
vector<T> quantile(const vector<T> & x, const vector<double> probs, const int type=1)
{	
	int 		n = x.size(),
				np = probs.size();

	vector<T>   x_sorted(x.begin(), x.end()),
				qs(probs.size());

	std::sort(x_sorted.begin(), x_sorted.end());
	
	T max_x = x_sorted[n-1];

	// ---------- TYPE 1 QUANTILES -----------
	vector<T> 	nppm(probs.size());
	nppm = probs * (double) n;

	// vector j is a floored copy of nppm representing provisional idices in x
	vector<T> j(probs.size());
	for (int i=0; i<np; i++) { j[i] = floor(nppm[i]); }

	// vector h is equal to 1, where (nppm > j); 
	// indicates where the provisional indices in j have to be adjusted
	vector<int> h(probs.size());
	for (int i=0; i<np; i++) { h[i] = (nppm[i] > j[i]) ? 1 : 0; }

	for (int i=0; i<np; i++) {

		if (h[i] == 0) {
			qs[i] = x_sorted[max(j[i] - 1, (double) 0.0)];
		} else {
			qs[i] = x_sorted[j[i]];
		}
	}

	return qs;
}


template <typename T>
vector<T> equidist_quantile(const vector<T> & x, const int K, const double d=0, const int type=1)
{
	vector<double> 	out(K),
					quantiles(K);

	for (int i=0; i<K; i++) { quantiles[i] = (i + 1 - d) / K; }

	out = quantile(x, quantiles, type);

	return out;
}


//' interval_table
//'
//' Given a vector datavec and a vector with interval breaks,
//' a histogram with the number of elements in datavec that fall into each
//' of the intervals is returned.
//'
//' @param datavec sorted vector with elements to be distributed over the
//'  intervals
//' @param interval_breaks vector with n interval_borders that are
//'  interpreted as interval breaks:\cr 
//' (-Inf, breaks[0]], (breaks[0], breaks[1]), ... , (breaks(n), Inf)
//' @param ini_value default frequency value
//'
//' @return frequency with which elements of datavec fall into each of the 
//'  intervals defined by interval_breaks
//'
vector<int> interval_table(	const vector<double> & datavec,
							const vector<double> & interval_breaks,
							const int init_value=0)
{
	// CPP BREAKPOINT
	//std::raise(SIGINT);
	int n = interval_breaks.size();

	// count the elements in cua that occur
	// in the intervals defined by cub
	vector<int> freq_table(n+1, init_value);

	if (n > 0) {

		double lower_bound(- numeric_limits<double>::infinity());
		double upper_bound = interval_breaks[0];
		int data_i = 0, interval_i=0;

		// iteration over the intervals (lower_bond, upper_bound]
		// defined by interval_breaks
		for (; interval_i<n+1; interval_i++){


			// iteration over the elements in cua, to count
			// how many elemtents fall into each of the intervals
			// defined by interval_breaks
			while (data_i < datavec.size()) {

				// if value at data_i in cua lies in interval
				// (lower_bound, upper_bound] 
				if ((datavec[data_i] > lower_bound) 
					&& (datavec[data_i] <= upper_bound)){ 

					// => increment the freq_table count for that interval
					// and don't check value at data_i in cua again
					++data_i;
					++freq_table[interval_i];

				} else {
					break;
				}
			}

			// update the interval:
			if (interval_i == n-1) {
				upper_bound = numeric_limits<double>::infinity();
				lower_bound = interval_breaks[interval_i];
			}
			else {
				upper_bound = interval_breaks[interval_i + 1];
				lower_bound = interval_breaks[interval_i];
			}
		}
	} else {
		freq_table = vector<int>({datavec.size()});
	}
	return freq_table;
}


//' permutations
//'
//' Returns permutations of a given NumericVector as columns in a NumericMatrix
//' object.
//' @param x NumericVector representing a vector that is to be permutated
//' @param num_permutations Integer representing the number of permutations
//' that are to be performed.
//' @return a matrix containing in every column one permutations of the
//' input vector
//'
//' @examples
//' x <- seq(1:10)
//' m <- permutations(x, 5)
//' dim(m)
//' #[1] 10  5
//'
//' @export
// [[Rcpp::export]]
NumericMatrix permutations(const NumericVector x, const int num_permutations) 
{

    // Matrix to store all permutations as columns
    int n_rows = x.size();
    int n_cols = num_permutations;
    NumericMatrix m(n_rows, n_cols);

	// create permutations
    for (int i=0; i<n_cols; i++){

    	m(_, i) = sample(x, n_rows, false);

    }

    return m;
}


/*=============================================

		WASSERSTEIN DISTANCE CALCULATION

==============================================*/

//' squared_wass_decomp
//'
//' Approximation of the squared Wasserstein distance \eqn{d_g}{W_g} between
//' two vectors decomposed into size, location and shape.
//' Calculation based on the mean squared difference between the equidistant
//' quantiles of the two input vectors a and b.
//' As an approximation of the distribution, 1000 quantiles are computed for
//' each vector.
//'
//' @param x Vector representing an empirical distribution under condition A
//' @param y Vector representing an empirical distribution under condition B
//' @return An named Rcpp::List with the wasserstein distance between x and y,
//' decomposed into terms for size, location, and shape
//' 
//' @references 
//' Schefzik and Goncalves 2019
//' Irpino and Verde (2015)
//'
//' @seealso [wasserstein_metric()], [squared_wass_approx()] for
//' different implementations of the wasserstein distance
//'
//' @examples
//' # input: one dimensional data in two conditions
//' x <- rnorm(100, 42, 2)
//' y <- c(rnorm(61, 20, 1), rnorm(41, 40,2))
//' # output: squared Wasserstein distance decomposed into terms for location,
//' # shape, size
//' d.wass.decomp <- squared_wass_decomp(x,y)
//' d.wass.decomp$location
//' d.wass.decomp$size
//' d.wass.decomp$shape
//' 
//' @export
//[[Rcpp::export]]
Rcpp::List squared_wass_decomp(	const NumericVector & x,
								const NumericVector & y)
{

	int NUM_QUANTILES = 1000;
	vector<double> 		a(x.begin(), x.end()), b(y.begin(), y.end()),
						quantiles_a = equidist_quantile(a, NUM_QUANTILES, (double) 0.5),
						quantiles_b = equidist_quantile(b, NUM_QUANTILES, (double) 0.5);

	double 	location, shape, size, d, 
			mean_a = mean(a), mean_b = mean(b),
			sd_a = sd(a), sd_b = sd(b), 
			quantile_cor_ab = cor(quantiles_a, quantiles_b);


	location 	= pow(mean_a - mean_b, 2);
	size 		= pow(sd_a - sd_b, 2);
	shape 		= 2 * sd_a * sd_b * (1 - quantile_cor_ab);
	d 			= location + size + shape;
	
	return Rcpp::List::create(
		Rcpp::Named("distance") = d,
		Rcpp::Named("location") = location,
		Rcpp::Named("size") = size,
		Rcpp::Named("shape") = shape
		);
}


//' squared_wass_approx
//'
//' Approximation of the squared wasserstein distance.
//' Calculation based on the mean squared difference between the equidistant
//' empirical quantiles of the two input vectors a and b.
//' As an approximation of the quantile function, 1000 quantiles are computed
//' for each vector.
//'
//' @param x Vector representing an empirical distribution under condition A
//' @param y Vector representing an empirical distribution under condition B
//' @return The approximated squared wasserstein distance between x and y
//'
//' @references Schefzik and Goncalves 2019
//'
//' @seealso [wasserstein_metric()], [squared_wass_decomp()] for
//' different implementations of the wasserstein distance
//'
//' @examples
//' # input: one dimensional data in two conditions
//' x <- rnorm(100, 42, 2)
//' y <- c(rnorm(61, 20, 1), rnorm(41, 40,2))
//' # output: The squared Wasserstein distance approximated as described in
//' # Schefzik and Goncalves 2019
//' d.wass.approx <- squared_wass_approx(x,y)
//'
//' @export
//[[Rcpp::export]]
double squared_wass_approx(	const NumericVector & x,
							const NumericVector & y)
{

	double				distance_approx;
	int 				NUM_QUANTILES = 1000;
	vector<double> 		a(x.begin(), x.end()), b(y.begin(), y.end()),
						quantiles_a = equidist_quantile(a, NUM_QUANTILES, (double) 0.5),
						quantiles_b = equidist_quantile(b, NUM_QUANTILES, (double) 0.5),
						squared_quantile_diff(NUM_QUANTILES);


	squared_quantile_diff = pow(quantiles_a - quantiles_b, (double) 2.0);
	distance_approx = mean(squared_quantile_diff);

	return distance_approx;
}


//' wasserstein_metric
//'
//' The order \code{p} Wasserstein metric (or distance) is defined as the 
//' \code{p}-th root of the total cost of turning one pile of mass x into a new
//' pile of mass y.
//' The cost a single trnasport \eqn{x_i} into \eqn{y_i} is the \code{p}-th
//' power of the euclidean distance between \eqn{x_i} and \eqn{y_i}.
//' 
//' The masses in \eqn{x} and \eqn{y} can also be represented as clusters
//' \eqn{P} and \eqn{Q} with weights \eqn{W_P} and \eqn{W_Q}.
//' The wasserstein distance then becomes the optimal flow F, which is the sum
//' of all optimal flows \eqn{f_{ij}} from \eqn{(p_i, w_{p,i})} to
//' \eqn{(q_i, w_{q,i})}.
//'
//' This implementation of the Wasserstein metric is a Rcpp reimplementation of
//' the wasserstein1d function by Dominic Schuhmacher from the package
//' transport.
//' 
//' @param x NumericVector representing an empirical distribution under
//' condition A
//' @param y NumericVector representing an empirical distribution under
//' condition B
//' @param p order of the wasserstein distance
//' @param wa_ NumericVector representing the weights of datapoints
//'  (interpreted as clusters) in x
//' @param wb_ NumericVector representing the weights of datapoints
//'  (interpreted as clusters) in y
//' @return The wasserstein (transport) distance between x and y
//'
//' @references Schefzik and Goncalves 2019
//'
//' @seealso [squared_wass_approx()], [squared_wass_decomp()] for
//' different approximations of the wasserstein distance
//'
//' @examples
//' # input: one dimensional data in two conditions
//' x <- rnorm(100, 42, 2)
//' y <- c(rnorm(61, 20, 1), rnorm(41, 40, 2))
//' # output: The exact Wasserstein distance between the two input
//' # vectors. Reimplementation of the wasserstein1d function found in
//' # the packge transport.
//' d.wass <- wasserstein_metric(x,y,2)
//'
//' @export
//[[Rcpp::export]]
double wasserstein_metric(const NumericVector x, 
						  const NumericVector y,
						  const double p=1,
						  const Nullable<NumericVector> wa_=R_NilValue, 
						  const Nullable<NumericVector> wb_=R_NilValue) 
{

	vector<double> a(x.begin(), x.end());
	vector<double> b(y.begin(), y.end());
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	// No weight vectors are given
	if (a.size() == b.size() && wa_.isNull() && wb_.isNull()) {

		// compute root mean squared absolute difference of a and b
		// in R: mean(abs(sort(b) - sort(a))^p)^(1/p)
		vector<double> sq_abs_diff = pow(
		  abs(b - a),
		  p);
		double mrsad = pow((double) mean(sq_abs_diff), (double) 1.0/p);
		return mrsad;

	}

	// At least one weight vector is given
	// If only one weight vector is undefined, set all its weights to 1
	double default_weight = 1.0;
	std::vector<double> wa(a.size(), default_weight);
	std::vector<double> wb(b.size(), default_weight);

	if (!wa_.isNull()) {
	  	NumericVector dumpwa = wa_.get();
		wa = vector<double>(dumpwa.begin(), dumpwa.end());
	}
	if (!wb_.isNull()) {
	  	NumericVector dumpwb = wb_.get();
		wb = vector<double>(dumpwb.begin(), dumpwb.end());
	}

	// normalize the weights to add up to 1
	vector<double> ua(wa.size());
	ua = wa / sum(wa);
	ua.pop_back();
	vector<double> ub(wb.size());
	ub = wb / sum(wb);
	ub.pop_back();
	//Rcout << "DEBUG OUTPUT:" <<END;
	////Rcout << "==============================================="<<END;
	//Rcout << "sorted a = "; for (double ea : a) { Rcout << ea << ", "; } Rcout << END;
	//Rcout << "sorted b = "; for (double eb : b) { Rcout << eb << ", "; } Rcout << END;
	
	// cumulative distribution without the last value
	// => last value will be considered as an open interval to Infinity
	vector<double> cua(ua.size());
	cua = cumSum(ua);
	vector<double> cub(ub.size());
	cub = cumSum(ub);
	vector<int> a_rep = interval_table(cub, cua, 1);
	vector<int> b_rep = interval_table(cua, cub, 1);
	//Rcout << "[!] ISSUE LIKELY HERE: " << END;
	//Rcout << "a_rep = "; for (int ea : a_rep) { Rcout << ea << ", "; } Rcout << END;
	//Rcout << "b_rep = "; for (int eb : b_rep) { Rcout << eb << ", "; } Rcout << END;

	//a_rep = a_rep + 1;
	//b_rep = b_rep + 1;

	//Rcout << "a_rep + 1 = "; for (int ea : a_rep) { Rcout << ea << ", "; } Rcout << END;
	//Rcout << "b_rep + 1 = "; for (int eb : b_rep) { Rcout << eb << ", "; } Rcout << END;

	int len_a_weighted = sum(a_rep);
	int len_b_weighted = sum(b_rep);
	//Rcout << "[sum(a_rep)] len_b_weighted = " << len_a_weighted << "; ";
	//Rcout << "[sum(b_rep)] len_a_weighted = " << len_b_weighted << END;

	vector<double> a_weighted(len_b_weighted);
	vector<double> b_weighted(len_a_weighted);
	a_weighted = rep_weighted(a, a_rep);
	b_weighted = rep_weighted(b, b_rep);

	//Rcout << "aa = "; for (double eaa : a_weighted) { Rcout << eaa << ", "; } Rcout << END;
	//Rcout << "bb = "; for (double ebb : b_weighted) { Rcout << ebb << ", "; } Rcout << END;

	vector<double> uu(cua.size() + cub.size());
	vector<double> uu0(cua.size() + cub.size()+1);
	vector<double> uu1(cua.size() + cub.size()+1);
	//Rcout << "AFTER INITIALIZATION: uu1.size() = " << uu1.size() << ", uu0.size() = " << uu0.size() <<END;
	vector<double> ONE{(double) 1.0};
	vector<double> ZERO{(double) 0.0};
	uu = concat(cua, cub);
	std::sort(uu.begin(), uu.end());
	uu0 = concat(ZERO, uu);
	uu1 = concat(uu, ONE);
	//Rcout << "uu0 = "; for (double euu0 : uu0) { Rcout << euu0 << ", "; } Rcout << END;
	//Rcout << "uu1 = "; for (double euu1 : uu1) { Rcout << euu1 << ", "; } Rcout << END;

	//Rcout << "AFTER CONCATENATIONS: uu1.size() = " << uu1.size() << ", uu0.size() = " << uu0.size() <<END;
	//Rcout << "b_weighted.size() = " << b_weighted.size() << ", a_weighted.size() = " << a_weighted.size() <<END;
	//Rcout << END;
	double wsum = 0.0;
	double areap = 0.0;

	wsum = sum((uu1 - uu0) * pow(abs(b_weighted - a_weighted), p));
	areap = pow(wsum, (double) (1/p));

	return areap;

}


int main()
{
	cout << "FOOO BAR TRALALA" <<END;
	/*
	vector<double> cua = {0.00934579, 0.0186916, 0.0280374, 0.0373832,
	 0.046729, 0.0560748, 0.0654206, 0.0747664, 0.0841121, 0.0934579,
	 0.102804, 0.11215, 0.121495, 0.130841, 0.140187, 0.149533,
	 0.158879, 0.168224, 0.17757, 0.186916, 0.196262, 0.205607,
	 0.214953, 0.224299, 0.233645, 0.242991, 0.252336, 0.261682,
	 0.271028, 0.280374, 0.28972, 0.299065, 0.308411, 0.317757,
	 0.327103, 0.336449, 0.345794, 0.35514, 0.364486, 0.373832,
	 0.383178, 0.392523, 0.401869, 0.411215, 0.420561, 0.429907,
	 0.439252, 0.448598, 0.457944, 0.46729, 0.476636, 0.485981,
	 0.495327, 0.504673, 0.514019, 0.523364, 0.53271, 0.542056, 0.551402,
	 0.560748, 0.570093, 0.579439, 0.588785, 0.598131, 0.607477, 0.616822,
	 0.626168, 0.635514, 0.64486, 0.654206, 0.663551, 0.672897, 0.682243,
	 0.691589, 0.700935, 0.71028, 0.719626, 0.728972, 0.738318, 0.747664,
	 0.757009, 0.766355, 0.775701, 0.785047, 0.794393, 0.803738, 0.813084,
	 0.82243, 0.831776, 0.841121, 0.850467, 0.859813, 0.869159, 0.878505, 
	 0.88785, 0.897196, 0.906542, 0.915888, 0.925234, 0.934579, 0.943925,
	 0.953271, 0.962617, 0.971963, 0.981308, 0.990654};

	vector<double> cub = {0.0035461, 0.0070922, 0.0106383, 0.0141844,
	 0.0177305, 0.0212766, 0.0248227, 0.0283688, 0.0319149, 0.035461,
	 0.0390071, 0.0425532, 0.0460993, 0.0496454, 0.0531915, 0.0567376,
	 0.0602837, 0.0638298, 0.0673759, 0.070922, 0.0744681, 0.0780142,
	 0.0815603, 0.0851064, 0.0886525, 0.0921986, 0.0957447, 0.0992908,
	 0.102837, 0.106383, 0.109929, 0.113475, 0.117021, 0.120567, 0.124113,
	 0.12766, 0.131206, 0.134752, 0.138298, 0.141844, 0.14539, 0.148936,
	 0.152482, 0.156028, 0.159574, 0.163121, 0.166667, 0.170213, 0.173759,
	 0.177305, 0.180851, 0.184397, 0.187943, 0.191489, 0.195035, 0.198582,
	 0.202128, 0.205674, 0.20922, 0.212766, 0.216312, 0.219858, 0.223404,
	 0.22695, 0.230496, 0.234043, 0.237589, 0.241135, 0.244681, 0.248227,
	 0.251773, 0.255319, 0.258865, 0.262411, 0.265957, 0.269504, 0.27305,
	 0.276596, 0.280142, 0.283688, 0.287234, 0.29078, 0.294326, 0.297872,
	 0.301418, 0.304965, 0.308511, 0.312057, 0.315603, 0.319149, 0.322695,
	 0.326241, 0.329787, 0.333333, 0.336879, 0.340426, 0.343972, 0.347518,
	 0.351064, 0.35461, 0.358156, 0.361702, 0.365248, 0.368794, 0.37234,
	 0.375887, 0.379433, 0.382979, 0.386525, 0.390071, 0.393617, 0.397163,
	 0.400709, 0.404255, 0.407801, 0.411348, 0.414894, 0.41844, 0.421986,
	 0.425532, 0.429078, 0.432624, 0.43617, 0.439716, 0.443262, 0.446809,
	 0.450355, 0.453901, 0.457447, 0.460993, 0.464539, 0.468085, 0.471631,
	 0.475177, 0.478723, 0.48227, 0.485816, 0.489362, 0.492908, 0.496454,
	 0.5, 0.503546, 0.507092, 0.510638, 0.514184, 0.51773, 0.521277, 0.524823,
	 0.528369, 0.531915, 0.535461, 0.539007, 0.542553, 0.546099, 0.549645,
	 0.553191, 0.556738, 0.560284, 0.56383, 0.567376, 0.570922, 0.574468,
	 0.578014, 0.58156, 0.585106, 0.588652, 0.592199, 0.595745, 0.599291,
	 0.602837, 0.606383, 0.609929, 0.613475, 0.617021, 0.620567, 0.624113,
	 0.62766, 0.631206, 0.634752, 0.638298, 0.641844, 0.64539, 0.648936,
	 0.652482, 0.656028, 0.659574, 0.663121, 0.666667, 0.670213, 0.673759,
	 0.677305, 0.680851, 0.684397, 0.687943, 0.691489, 0.695035, 0.698582,
	 0.702128, 0.705674, 0.70922, 0.712766, 0.716312, 0.719858, 0.723404,
	 0.72695, 0.730496, 0.734043, 0.737589, 0.741135, 0.744681, 0.748227,
	 0.751773, 0.755319, 0.758865, 0.762411, 0.765957, 0.769504, 0.77305,
	 0.776596, 0.780142, 0.783688, 0.787234, 0.79078, 0.794326, 0.797872,
	 0.801418, 0.804965, 0.808511, 0.812057, 0.815603, 0.819149, 0.822695,
	 0.826241, 0.829787, 0.833333, 0.836879, 0.840426, 0.843972, 0.847518,
	 0.851064, 0.85461, 0.858156, 0.861702, 0.865248, 0.868794, 0.87234, 
	 0.875887, 0.879433, 0.882979, 0.886525, 0.890071, 0.893617, 0.897163,
	 0.900709, 0.904255, 0.907801, 0.911348, 0.914894, 0.91844, 0.921986,
	 0.925532, 0.929078, 0.932624, 0.93617, 0.939716, 0.943262, 0.946809,
	 0.950355, 0.953901, 0.957447, 0.960993, 0.964539, 0.968085, 0.971631,
	 0.975177, 0.978723, 0.98227, 0.985816, 0.989362, 0.992908, 0.996454};
	
	vector<int> arep1;
	vector<int> brep1;
	vector<int> arep2;
	vector<int> brep2;

	for (int i=0; i < 1000; i++) {
		arep1 = interval_table(cub, cua, 1);
		brep1 = interval_table(cua, cub, 1);
		arep2 = interval_table(cub, cua, 1);
		brep2 = interval_table(cua, cub, 1);
		cout << "arep1 = " << arep1[arep1.size() -1] << " \n";
		cout << "brep1 = " << brep1[brep1.size() -1]<< "\n";
		cout << "arep2 = " << arep2[arep2.size() -1]<< "\n";
		cout << "brep2 = " << brep2[brep2.size() -1]<< "\n";
	} */
	
//	cout << "a_rep1 = "; for (int ea1 : arep1) { cout << ea1 << ", "; } cout << END;
//	cout << "b_rep1 = "; for (int eb1 : brep1) { cout << eb1 << ", "; } cout << END;
//	cout << "a_rep2 = "; for (int ea2 : arep2) { cout << ea2 << ", "; } cout << END;
//	cout << "b_rep2 = "; for (int eb2 : brep2) { cout << eb2 << ", "; } cout << END;

	return 0;
}


/*=============================================

			EXPORTS FOR TESTING IN R

==============================================*/ 

// [[Rcpp::export]]
NumericVector add_test_export(NumericVector & x_, NumericVector & y_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					y(y_.begin(), y_.end()),
					result(x.size());

	result = x + y;
	NumericVector output(result.begin(), result.end());
	return output;
}


// [[Rcpp::export]]
NumericVector add_test_export_sv(NumericVector & x_, double & summand_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					result(x.size());
	const double summand = summand_;

	result = x + summand;
	NumericVector output(result.begin(), result.end());
	return output;
}


// [[Rcpp::export]]
NumericVector multiply_test_export(NumericVector & x_, NumericVector & y_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					y(y_.begin(), y_.end()),
					result(x.size());

	result = x * y;
	NumericVector output(result.begin(), result.end());
	return output;
}


// [[Rcpp::export]]
NumericVector multiply_test_export_sv(NumericVector & x_, double & factor_)
{

	vector<double> 	x(x_.begin(), x_.end()),
					result(x.size());
	const double factor = factor_;

	result = x * factor;
	NumericVector output(result.begin(), result.end());
	return output;
}


// [[Rcpp::export]]
NumericVector pow_test_export(NumericVector & x_, const double & exp)
{
	vector<double>	x(x_.begin(), x_.end()),
					result(x.size());
	
	result = pow(x, exp);

	NumericVector 	output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
NumericVector abs_test_export(NumericVector & x_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					result(x.size());
	
	result = abs(x);

	NumericVector 	output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
double sum_test_export(NumericVector & x_)
{
	vector<double> 	x(x_.begin(), x_.end());

	double result = sum(x);

	return result;
}

// [[Rcpp::export]]
NumericVector subtract_test_export(NumericVector & x_, NumericVector & y_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					y(y_.begin(), y_.end()),
					result(x.size());

	result = x - y;
	
	NumericVector output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
NumericVector divide_test_export_sv(NumericVector & x_, double & y_)
{
	vector<double>	x(x_.begin(), x_.end()),
					result(x.size());
	const double 	y = y_;

	result = x / y;

	NumericVector output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
NumericVector divide_test_export_vectors(NumericVector & x_, NumericVector & y_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					y(y_.begin(), y_.end()),
					result(x.size());

	result = x / y;

	NumericVector output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
double mean_test_export(NumericVector & x_)
{
	vector<double> 	x(x_.begin(), x_.end());
	double 			result = mean(x);
	return result;
}

// [[Rcpp::export]]
double sd_test_export(NumericVector & x_)
{
	vector<double> 	x(x_.begin(), x_.end());
	double 			result = sd<double>(x);
	return result;	
}

// [[Rcpp::export]]
NumericVector cumSum_test_export(NumericVector & x_, int last_index=0)
{

	vector<double> 	x(x_.begin(), x_.end()),
					result;
	
	result = cumSum(x, last_index);
	
	NumericVector 	output(result.begin(), result.end());
	return output;	
}

// [[Rcpp::export]]
double cor_test_export(NumericVector x_, NumericVector y_)
{	

	vector<double> 	x(x_.size()),
					y(y_.size());
	
	for (int i=0; i<x.size(); i++) { x[i] = x_[i];}
	for (int j=0; j<y.size(); j++) { y[j] = y_[j];}

	double result = cor(x, y);
	
	return result;
}


// [[Rcpp::export]]
NumericVector rep_weighted_test_export(NumericVector & x_, NumericVector & weights_)
{
	vector<int>		weights(weights_.begin(), weights_.end());
	vector<double> 	x(x_.begin(), x_.end()),
					result(sum(weights));

	result = rep_weighted(x, weights);

	NumericVector output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
NumericVector concat_test_export(NumericVector & x_, NumericVector & y_)
{
	vector<double> 	x(x_.begin(), x_.end()),
					y(y_.begin(), y_.end()),
					result(x.size() + y.size());

	result = concat(x, y);

	NumericVector output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
IntegerVector interval_table_test_export(	NumericVector & data_,
											NumericVector & breaks_,
											const int & default_freq=0)
{
	vector<double> 	x(data_.begin(), data_.end()),
					y(breaks_.begin(), breaks_.end());
	vector<int>		result(x.size() + y.size());

	result = interval_table(x, y, default_freq);

	IntegerVector output(result.begin(), result.end());
	return output;
}

// [[Rcpp::export]]
NumericVector equidist_quantile_test_export(	NumericVector & x_,
												double K,
												double d=0,
												int type=1)
{
	vector<double>	x(x_.begin(), x_.end()),
					res(K);

	res = equidist_quantile(x, K, d, type);

	NumericVector output(res.begin(), res.end());
	return output;
}

// [[Rcpp::export]]
NumericVector quantile_test_export(	NumericVector & x_,
									NumericVector & q_,
									int type=1)
{
	vector<double>	x(x_.begin(), x_.end()),
					q(q_.begin(), q_.end()),
					res(q_.size());

	res = quantile(x, q, type);

	NumericVector output(res.begin(), res.end());
	return output;
}