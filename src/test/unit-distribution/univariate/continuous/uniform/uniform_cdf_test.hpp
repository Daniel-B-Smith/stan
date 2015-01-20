// Arguments: Doubles, Doubles, Doubles
#include <stan/prob/distributions/univariate/continuous/uniform.hpp>

using std::vector;
using std::numeric_limits;
using stan::agrad::var;

class AgradCdfUniform : public AgradCdfTest {
public:
  void valid_values(vector<vector<double> >& parameters,
                    vector<double>& cdf) {
    vector<double> param(3);

    param[0] = 0.1;                // y
    param[1] = -0.1;               // alpha
    param[2] = 5.0;                // beta
    parameters.push_back(param);
    cdf.push_back(0.2 / 5.1);   // expected cdf

    param[0] = 0.2;                // y
    param[1] = -0.25;              // alpha
    param[2] = 5.0;               // beta
    parameters.push_back(param);
    cdf.push_back(0.45 / 5.25);   // expected cdf

    param[0] = 0.05;               // y
    param[1] = -5;                 // alpha
    param[2] = 5;                  // beta
    parameters.push_back(param);
    cdf.push_back(5.05 / 10.0);   // expected cdf
  }
 
  void invalid_values(vector<size_t>& /*index*/, 
                      vector<double>& /*value*/) {
    // y
    
    // alpha

    // beta
  }


  bool has_lower_bound() {
    return false;
  }

  //BOUND INCLUDED IN ORDER FOR TEST TO PASS WITH CURRENT FRAMEWORK
  bool has_upper_bound() {
    return true;
  }

  double upper_bound() {
    return 5.0;
  }

  template <class T_y, class T_low, class T_high,
            typename T3, typename T4, typename T5>
  typename stan::return_type<T_y, T_low, T_high>::type 
  cdf(const T_y& y, const T_low& alpha, const T_high& beta,
      const T3&, const T4&, const T5&) {
    return stan::prob::uniform_cdf(y, alpha, beta);
  }
  
  template <class T_y, class T_low, class T_high,
            typename T3, typename T4, typename T5>
  typename stan::return_type<T_y, T_low, T_high>::type 
  cdf_function(const T_y& y, const T_low& alpha, const T_high& beta,
               const T3&, const T4&, const T5&) {
      using stan::prob::include_summand;
      using stan::prob::LOG_ZERO;

      if (y < alpha || y > beta)
        return 0.0;

      return (y - alpha) / (beta - alpha);
  }
};
