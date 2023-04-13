# v0.9.4
## What's Changed
* Division between code for internal functionality vs. what is available to the user.
* CI/CD pipeline updates
   * `clang-format` for linting/formatting C++ source code, `autopep8` for Python.
   * Python PyPI packaging edits.
   * Tag bump related commits will include a `#MAJOR`, `#MINOR`, or `#PATCH` prefix to the commit message.
   * Updates to certain directories run certain jobs.
* Continuous Machine Learning & Linear Algebra module updates. 
   * Stubbed out implementations for activation, regularization, optimization & model trainer methods, statistical helpers, random sorts + utilities. 
   * `Matrix` related methods are usable. More updates to come.
   * ML module is not currently usable aside from `Linear Regression` model on very select data sets.


# v0.7.0
## New Changes in v0.7.0
1. Updates to Primary and Secondary Multi-Layer Perceptron networks
2. Updates to Python API
3. Added support for Operating Systems, Kernels, Architectures, etc.
	* Added tested support beyond x86 processors
	* ARMV6, ARMV7, ARMV8, RISCV64, S390X, PPC64LE
	* Raspberry Pi 3 & 4 support
4. Fortran, OCaml, Go and Julia demoted to experimental APIs, focus remains on Python and now R bindings

### Next :
_______________
1. Fix CMake bugs for `OSX` installation. Issues with Googletest hangup 
2. Update Machine Learning Module with more techniques
3. Inject source code updates into APIs
4. Create formal check/test process for Raspberry Pi hardware


# v0.6.0
## New Changes in v0.6.0
1. Continued changes to Linear Algebra Module + samples
2. Continued updates to Python API, injecting new C++ source functionalities into the `setup.py` file used in packaging process for PyPI
	* Install with `pip install openmtpk==0.6.1`
3. Updates to the `mtpk` namespace. Wrapped more classes in the namespace, does not affect Python API
4. Changes/updates to datatypes to allow for maximum precision while also avoiding potential overflow as well as for conciseness
	> **Note** Some int and char types will be updated later on to ensure nothing breaks
	* `int`----------->`int64_t`
	* `long long`-->`int64_t`
	* `unsigned`---->`uint64_t`
	* `double`------->`long double`
	* `float`--------->`long double`
5. Adding `make uninstall` option for the project's build process with CMake. See the install/uninstall directions [here](https://github.com/akielaries/openMTPK#installation).


# v0.5.3
## What's Changed 
1. Updates to Linear Algebra Module and samples
	* See this [example](https://github.com/akielaries/openMTPK/blob/main/samples/cpp/linalg_ops.cpp) to view operations on matrices
	* More updates to samples as development continues
2. PyPI updates
	* Adjusting SWIG process to accommodate for template based classes and methods
	* openmtpk `0.5.14` release [here](https://pypi.org/project/openmtpk/0.5.13/)
3. Updated to CMake installation of source C++ code

### Next :
_______________
1. Create first of many Neural Network Models and Machine Learning techniques for the [ml](https://akielaries.github.io/openMTPK/ml_8hpp.html) module
	* Update the overarching `ml.hpp` header to make use of implemented models and techniques
	> **Note** So far the [Linear Regression](https://akielaries.github.io/openMTPK/linreg_8hpp.html) technique works on select two-column data
2. Progress on CPP->R & OCaml language binding process


# v0.5.2
## What's Changed 
> **Note** Do not expect much until _**v1.0.0**_

### Major Updates to Python PyPI packaging process. 
* Builds wheels for OSX and Linux platforms (Windows will not be supported)
* See all [supported platforms](https://pypi.org/project/openmtpk/0.5.1/#files).
  * Manually tested on _**Kali(latest), Ubuntu(latest)**_ & _**macOS Ventura 13.1 (latest)**_. Works for most OSX and Linux distro versions.
* New versions must be specified in the `setup.py` file and will be published to https://pypi.org/project/openmtpk/ on pushes to `MAIN`.
* Install with `pip install openmtpk`
* Tools available: 
  * Arithmetic based operations
  * Primes
  * RC4
  * Ciphers

### C++ source is currently supported on Linux based platforms.
* Bugs with googletest on OSX.


# v0.4.0
## What's Changed
* Created Python pip package for Python API. Install with `pip install openmtpk`
  * Functionality is limited to Primes, RC4, Ciphers, and part of the Arithmetic module
  * Fixes to template classes/methods cpp->python conversion


# v0.3.2
CMake installation make Googletest as a dependency.
* openMTPK tests must pass in order to build and install the static library
* TEST -> BUILD -> INSTALL


# v0.3.1
Minor Release with updates to CMake installation process.
* Headers are now installed in nested fashion with a parent-level header representing each module. For example:
  * Files in a module directory such as the `ml/` directory (linreg.hpp, logreg.hpp, mlp_network.hpp, etc.) will make up that modules header file([ml.hpp](https://github.com/akielaries/openMTPK/blob/main/include/ml.hpp)).
* Will include googletest workflow into CMake installation
  * `Build library -> Test library -> Install library` 


# v0.3
Formal documentation created with Doxygen deployed to github pages, see [here](https://akielaries.github.io/openMTPK). 
* Documentation updates within headers
* Linear Regression model testing
* Additional work and plans for Machine/Deep Learning module
  * Multi-Layer Perceptron, Linear Algebra Matrix, Scalar, and Vector manipulations + testing
  * Formal API installation processes
  * Automate API installations with Actions  

As always refer to the project [README](https://github.com/akielaries/openMTPK#installation).


# v0.2
Formal installation of source C++ API with CMake. See installation steps in the project [README](https://github.com/akielaries/openMTPK#installation).
* Linux is supported. 
* OSX testing is in progress.
* Working Python API, user installation mandatory.
* Unstable Fortran, OCaml, and R bindings.

**Future**
* Fixes + testing + formal installation of language bindings.
* Neural Networks, Classifiers

https://openmtpk-docs.readthedocs.io/en/latest/index.html


# v0.1
### Initial "release" of _openMTPK_ 
Open-source (intended) mathematics package written in C++ with a working Python API allowing for the use of algorithms and equations seen in many mathematical topics.
See the [README](https://github.com/akielaries/openMTPK/blob/main/README.md) for more details


#### Modules
Module | Features | Status | 
------------|--------------|-----------|
Arithmetic          | Operations, GCD, etc. | **Working** | 
Calculus              | Derivative at value |**Limited** | 
Linear Algebra   |Matrix Operations | **Limited** | 
Machine/Deep Learning | Linear Regression | **Limited** |
Number Theory       | Primes, Cryptography/Encryption | **Working** | 

Issues:
* No formal installation method 
* Test coverage
* OCaml & R bindings are unstable. 
  * C++->OCaml class translation
