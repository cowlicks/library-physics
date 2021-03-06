////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/Static.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_Static__
#define __Library_Physics_Coordinate_Frame_Providers_Static__

#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame/Provider.hpp>
#include <Library/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::time::Instant ;
using library::physics::coord::frame::Provider ;
using library::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Static provider

class Static : public Provider
{

    public:

                                Static                                      (   const   Transform&                  aTransform                                  ) ;

        virtual                 ~Static                                     ( ) override ;

        virtual Static*         clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        virtual Transform       getTransformAt                              (   const   Instant&                    anInstant                                   ) const override ;

    private:

        Transform               transform_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
