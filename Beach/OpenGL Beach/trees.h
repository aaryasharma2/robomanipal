//----------------------------------------------------------------------------------------
/**
 * \file       spline.h
 * \author     Jordan Jiri, Miroslav Miksik & Jaroslav Sloup & Petr Felkel
 * \date       2021
 * \brief      Utility functions and stuff tasks concerning animation curves.
*/
//----------------------------------------------------------------------------------------
#ifndef __SPLINE_H
#define __SPLINE_H

#include "pgr.h" // glm

//**************************************************************************************************
/// Checks whether vector is zero-length or not.
bool isVectorNull(const glm::vec3& vect);

//**************************************************************************************************
/// Align (rotate and move) current coordinate system to given parameters.
/**
 This function works similarly to \ref gluLookAt, however it is used for object transform
 rather than for view transform. Therefore, this function does not compute the computed matrix inverse.
 The current coordinate system is moved in such a way that the origin is moved
 to the \a position. Object's local front (-Z) direction is rotated to the \a front and
 object's local up (+Y) direction is rotated so that angle between its local up direction and
 \a up vector is minimum.

 \param[in]  position           Position of the origin.
 \param[in]  front              Front direction.
 \param[in]  up                 Up vector.
 */
glm::mat4 alignObject(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up);


extern glm::vec3 curveData[];
extern const size_t  curveSize;


extern glm::vec3 curve2Data[];
extern const size_t  curve2Size;


//**************************************************************************************************
/// Evaluates a position on Catmull-Rom curve segment.
/**
  \param[in] P0       First control point of the curve segment.
  \param[in] P1       Second control point of the curve segment.
  \param[in] P2       Third control point of the curve segment.
  \param[in] P3       Fourth control point of the curve segment.
  \param[in] t        Curve segment parameter. Must be within range [0, 1].
  \return             Position on the curve for parameter \a t.
*/
glm::vec3 evaluateCatmullRollCurveSegment(
    const glm::vec3& P0,
    const glm::vec3& P1,
    const glm::vec3& P2,
    const glm::vec3& P3,
    const float t
);
//**************************************************************************************************
/// Evaluates a fist derivative of Catmull-Rom curve segment.
/**
  \param[in] P0       First control point of the curve segment.
  \param[in] P1       Second control point of the curve segment.
  \param[in] P2       Third control point of the curve segment.
  \param[in] P3       Founrth control point of the curve segment.
  \param[in] t        Curve segment parameter. Must be within range [0, 1].
  \return             First derivative of the curve for parameter \a t.
*/
glm::vec3 evaluateCatmullRollCurveSegment_1stDerivative(
    const glm::vec3& P0,
    const glm::vec3& P1,
    const glm::vec3& P2,
    const glm::vec3& P3,
    const float t
);
//**************************************************************************************************
/// Evaluates a position on a closed curve composed of Catmull-Rom segments.
/**
  \param[in] points   Array of curve control points.
  \param[in] count    Number of curve control points.
  \param[in] t        Parameter for which the position shall be evaluated.
  \return             Position on the curve for parameter \a t.
  \note               Although the range of the paramter is from [0, \a count] (outside the range
                      the curve is periodic) one must presume any value (even negative).
*/
glm::vec3 evaluateCatmullRollClosedCurve(
    const glm::vec3 points[],
    const size_t    count,
    const float     t
);
//**************************************************************************************************
/// Evaluates a first derivative of a closed curve composed of Catmull-Rom segments.
/**
  \param[in] points   Array of curve control points.
  \param[in] count    Number of curve control points.
  \param[in] t        Parameter for which the derivative shall be evaluated.
  \return             First derivative of the curve for parameter \a t.
  \note               Although the range of the paramter is from [0, \a count] (outside the range
                      the curve is periodic) one must presume any value (even negative).
*/
glm::vec3 evaluateCatmullRollClosedCurve_1stDerivative(
    const glm::vec3 points[],
    const size_t    count,
    const float     t
);

glm::vec3 evaluateCoonsCurveSegment(
    const glm::vec3& P0,
    const glm::vec3& P1,
    const glm::vec3& P2,
    const glm::vec3& P3,
    const float t
);

glm::vec3 evaluateCoonsCurveSegment_1stDerivative(
    const glm::vec3& P0,
    const glm::vec3& P1,
    const glm::vec3& P2,
    const glm::vec3& P3,
    const float t
);
glm::vec3  evaluateCoonsClosedCurve(
    const glm::vec3& P0,
    const glm::vec3& P1,
    const glm::vec3& P2,
    const glm::vec3& P3,
    const float t
);

glm::vec3 evaluateCoonsClosedCurve_1stDerivative(
    const glm::vec3& P0,
    const glm::vec3& P1,
    const glm::vec3& P2,
    const glm::vec3& P3,
    const float t
);

#endif // __SPLINE_H
