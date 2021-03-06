////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Ephemeris.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Ephemeris__
#define __Library_Physics_Environment_Ephemeris__

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;

using library::physics::coord::Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief
///
/// @ref                        https://en.wikipedia.org/wiki/Fundamental_ephemeris

class Ephemeris
{

    public:

                                Ephemeris                                   ( ) ;

        virtual                 ~Ephemeris                                  ( ) = 0 ;

        virtual Ephemeris*      clone                                       ( ) const = 0 ;

        virtual bool            isDefined                                   ( ) const = 0 ;

        virtual Shared<const Frame> accessFrame                             ( ) const = 0 ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
