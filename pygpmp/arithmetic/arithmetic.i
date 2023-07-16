/* openGPMP Arithmetic Module */

%module arithmetic
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>
%include "std_string.i"

%{
    #include "../../include/arithmetic.hpp"
    using namespace gpmp;
%}

%include "../../include/arithmetic.hpp"

