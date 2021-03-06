////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/Dynamic.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_Dynamic__
#define __Library_Physics_Coordinate_Frame_Providers_Dynamic__

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

/// @brief                      Dynamic provider

class Dynamic : public Provider
{

    public:

        typedef                 std::function<Transform (const Instant&)>       Generator ;

                                Dynamic                                     (   const   Dynamic::Generator&         aGenerator                                  ) ;

        virtual                 ~Dynamic                                    ( ) override ;

        virtual Dynamic*        clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        virtual Transform       getTransformAt                              (   const   Instant&                    anInstant                                   ) const override ;

        static Dynamic          Undefined                                   ( ) ;

    private:

        Dynamic::Generator      generator_ ;

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
