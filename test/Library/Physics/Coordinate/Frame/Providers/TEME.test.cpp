////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/TEME.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Array.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame_Providers_TEME, GetTransformAt)
{

    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Transform ;
    using library::physics::coord::frame::provider::TEME ;

    {

        const Array<Pair<File, Angle>> referenceScenarios =
        {
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/TEME/Scenario_A/Scenario ITRF_TEME.csv")), Angle::Arcseconds(1.0) },
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/TEME/Scenario_B/Scenario ITRF_TEME.csv")), Angle::Arcseconds(20.0) }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const TEME temeFrameProvider ;

            // Reference data setup

            const File referenceDataFile = referenceScenario.first ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC) ;

                const Quaternion referenceOrientation_ITRF_TEME = Quaternion::XYZS(referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal(), referenceRow[4].accessReal()).normalize().conjugate() ;
                const Quaternion referenceOrientation_GCRF_TEME = Quaternion::XYZS(referenceRow[5].accessReal(), referenceRow[6].accessReal(), referenceRow[7].accessReal(), referenceRow[8].accessReal()).normalize() ;

                const Transform transform_TEME_ITRF = temeFrameProvider.getTransformAt(instant) ;

                const Quaternion dq_ITRF = (transform_TEME_ITRF.getOrientation() / referenceOrientation_ITRF_TEME).normalize().rectify() ;

                const Transform transform_TEME_GCRF = Frame::GCRF()->getTransformTo(Frame::TEME(), instant) ;

                const Quaternion dq_GCRF = (transform_TEME_GCRF.getOrientation() / referenceOrientation_GCRF_TEME).normalize().rectify() ;

                const Angle toleranceAngle = referenceScenario.second ;

                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_ITRF).getAngle().inDegrees()) ;
                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_GCRF).getAngle().inDegrees()) ;

                // std::cout << instant.toString()
                // << " : [TEME - ITRF]" << referenceOrientation_ITRF_TEME.toString(15) << " " << transform_TEME_ITRF.getOrientation().toString(15)
                // << " >> " << RotationVector::Quaternion(dq_ITRF).getAngle().inArcseconds().toString(3) << " [asec]"
                // << " : [TEME - GCRF]" << referenceOrientation_GCRF_TEME.toString(15) << " " << transform_TEME_GCRF.getOrientation().toString(15)
                // << " >> " << RotationVector::Quaternion(dq_GCRF).getAngle().inArcseconds().toString(3) << " [asec]" << std::endl ;

                // [TBI] Add angular velocity test

            }

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
