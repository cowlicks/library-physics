////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Coordinate/Spherical.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Coordinate/Spherical/AER.cpp>
#include <LibraryPhysicsPy/Coordinate/Spherical/LLA.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate_Spherical       ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Physics.Coordinate.Spherical")))) ;

    boost::python::scope().attr("Spherical") = module ;

    boost::python::scope scope = module ;

    LibraryPhysicsPy_Coordinate_Spherical_LLA() ;
    LibraryPhysicsPy_Coordinate_Spherical_AER() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
