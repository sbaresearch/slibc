///////////////////////////////////////////////////////
/// This directory contains the public headers for the 
/// functions defined in ISO/IEC TR 24731-1 'Bounds-checking interfaces'.
///
/// This Technical Report provides alternative functions for the C library that
/// promote safer, more secure programming. The functions verify that output 
/// buffers are large enough for the intended result and return a failure 
/// indicator if they are not. Data is never written past the end of an array. 
/// All string results are null terminated.
///
/// All files with a trailing _ are not mentioned in the Standard.
/// Normally, you should not include them.
/// Instead, the library supports the following MACROs to 
/// make more functionality available:
///
/// Define SLIBC_WANT_TEMPLATES before using a slibc header
///  in order to have template overloads available (C++ only).     
/// Define SLIBC_WANT_MKTEMP before using an slibc header
///  in order to have the functions mkstemp_s available.
///
//////////////////////////////////////////////////////
