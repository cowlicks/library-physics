////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Coordinate/Frame/Providers/Dynamic.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/Dynamic.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate_Frame_Providers_Dynamic ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;

    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Dynamic ;

    scope in_Dynamic = class_<Dynamic, Shared<Dynamic>, bases<Provider>>("Dynamic", no_init)

        .def
        (
            "__init__",
            make_constructor
            (
                +[] (const boost::python::object& aGeneratorObject) -> Shared<Dynamic>
                {

                    const auto generatorProxy = [aGeneratorObject] (const Instant& anInstant) -> Transform
                    {
                        return boost::python::extract<Transform>(aGeneratorObject(anInstant)) ;
                    } ;

                    return std::make_shared<Dynamic>(generatorProxy) ;

                }
            )
        )

        .def("isDefined", &Dynamic::isDefined)

        .def("getTransformAt", &Dynamic::getTransformAt)

        .def("Undefined", &Dynamic::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
