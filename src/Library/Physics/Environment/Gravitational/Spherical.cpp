////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Gravitational/Spherical.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Gravitational/Spherical.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace environment
{
namespace gravitational
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::units::Length ;
using library::physics::units::Mass ;
using library::physics::units::Time ;
using library::physics::units::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Derived::Unit GravitationParameterSIUnit = Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Spherical::Spherical                        (   const   Derived&                    aGravitationalParameter                     )
                                :   Model(),
                                    gravitationalParameter_SI_(aGravitationalParameter.in(GravitationParameterSIUnit))
{

    if (!gravitationalParameter_SI_.isDefined())
    {
        throw library::core::error::runtime::Undefined("Gravitational parameter") ;
    }

}

Spherical*                      Spherical::clone                            ( ) const
{
    return new Spherical(*this) ;
}

Vector3d                        Spherical::getFieldValueAt                  (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{

    (void) anInstant ; // Temporal invariance

    const Real r = aPosition.norm() ;
    const Vector3d fieldDirection = aPosition.normalized() ;

    const Vector3d field = (- gravitationalParameter_SI_) / (r * r) * fieldDirection ;

    return field ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
