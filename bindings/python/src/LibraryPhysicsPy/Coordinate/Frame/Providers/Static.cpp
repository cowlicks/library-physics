////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Coordinate/Frame/Providers/Static.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/Static.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate_Frame_Providers_Static ( )
{

    using namespace boost::python ;

    using library::physics::coord::Transform ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    scope in_Static = class_<Static, bases<Provider>>("Static", init<const Transform&>())

        .def("isDefined", &Static::isDefined)

        .def("getTransformAt", &Static::getTransformAt)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
