////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::Object                              (   const   String&                     aName,
                                                                                const   Instant&                    anInstant                                   )
                                :   name_(aName),
                                    instant_(anInstant),
                                    geometryUPtr_(nullptr)
{

}

                                Object::Object                              (   const   String&                     aName,
                                                                                const   Instant&                    anInstant,
                                                                                const   Object::Geometry&           aGeometry                                   )
                                :   name_(aName),
                                    instant_(anInstant),
                                    geometryUPtr_(aGeometry.clone())
{

}

                                Object::Object                              (   const   Object&                     anObject                                    )
                                :   name_(anObject.name_),
                                    instant_(anObject.instant_),
                                    geometryUPtr_((anObject.geometryUPtr_ != nullptr) ? anObject.geometryUPtr_->clone() : nullptr)
{

}


                                Object::~Object                             ( )
{

}

Object&                         Object::operator =                          (   const   Object&                     anObject                                    )
{

    if (this != &anObject)
    {

        name_ = anObject.name_ ;
        instant_ = anObject.instant_ ;

        geometryUPtr_.reset((anObject.geometryUPtr_ != nullptr) ? anObject.geometryUPtr_->clone() : nullptr) ;

    }

    return *this ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Object&                     anObject                                    )
{

    library::core::utils::Print::Header(anOutputStream, "Object") ;

    library::core::utils::Print::Line(anOutputStream) << "Name:" << (!anObject.name_.isEmpty() ? anObject.name_ : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Instant:" << (anObject.instant_.isDefined() ? anObject.instant_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Object::isDefined                           ( ) const
{
    return !name_.isEmpty() ;
}

const String&                   Object::accessName                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }
    
    return name_ ;

}

const Instant&                  Object::accessInstant                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }
    
    return instant_ ;

}

const Object::Geometry&         Object::accessGeometry                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    if (geometryUPtr_ == nullptr)
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }
    
    return *geometryUPtr_ ;

}

Frame                           Object::getFrame                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    if (auto frameSPtr = this->accessFrame().lock())
    {
        return *frameSPtr ;
    }
    else
    {
        throw library::core::error::RuntimeError("Cannot access frame.") ;
    }

    return Frame::Undefined() ;

}

void                            Object::setInstant                          (   const   Instant&                    anInstant                                   )
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    instant_ = anInstant ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////