#ifndef __STAN__MATH__ERROR_HANDLING__DOM_ERR_VEC_HPP__
#define __STAN__MATH__ERROR_HANDLING__DOM_ERR_VEC_HPP__

#include <sstream>
#include <stan/meta/traits.hpp>
#include <stan/math/error_handling/raise_domain_error.hpp>

namespace stan {
  namespace math {

    template <typename T_y, 
              typename T_result,
              typename T_msg2,
              class Policy>
    inline bool dom_err_vec(size_t i,
                            const char* function,
                            const T_y& y,
                            const char* name,
                            const char* error_msg,
                            T_msg2 error_msg2,
                            T_result* result,
                            const Policy&) {
      using stan::math::policies::raise_domain_error;
      std::ostringstream msg_o;
      msg_o << name << "[" << i << "] " << error_msg << error_msg2;
      T_result tmp 
        = raise_domain_error<T_result,
        typename T_y::value_type>(function,
                                  msg_o.str().c_str(),
                                  stan::get(y,i),
                                  Policy());
      if (result != 0)
        *result = tmp;
      return false;
    }

    
  }
}
#endif