//----------------------------------------------------------------------------------------
/**
 * \file       spline.cpp
 * \author     Jordan Jiri, Miroslav Miksik & Jaroslav Sloup & Petr Felkel
 * \date       2021
 * \brief      Utility functions and stuff tasks concerning animation curves.
*/
//----------------------------------------------------------------------------------------

#include "spline.h"

//**************************************************************************************************
/// Checks whether vector is zero-length or not.
bool isVectorNull(const glm::vec3& vect) {

    return !vect.x && !vect.y && !vect.z;
}

//**************************************************************************************************
/// Align (rotate and move) current coordinate system to given parameters.
/**
 This function works similarly to \ref gluLookAt, however, it is used for object transform
 rather than for view transform. Therefore, this function does not compute the computed matrix inverse.
 The current coordinate system is moved in such a way that the origin is moved
 to the \a position. Object's local front (-Z) direction is rotated to the \a front and
 object's local up (+Y) direction is rotated so that angle between its local up direction and
 \a up vector is minimum.

 \param[in]  position           Position of the origin.
 \param[in]  front              Front direction.
 \param[in]  up                 Up vector.
 */
glm::mat4 alignObject(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) {

    glm::vec3 z = -glm::normalize(front);

    if (isVectorNull(z))
        z = glm::vec3(0.0, 0.0, 1.0);

    glm::vec3 x = glm::normalize(glm::cross(up, z));

    if (isVectorNull(x))
        x = glm::vec3(1.0, 0.0, 0.0);

    glm::vec3 y = glm::cross(z, x);
    //mat4 matrix = mat4(1.0f);
    glm::mat4 matrix = glm::mat4(
        x.x, x.y, x.z, 0.0,
        y.x, y.y, y.z, 0.0,
        z.x, z.y, z.z, 0.0,
        position.x, position.y, position.z, 1.0
    );

    return matrix;
}



/// Number of control points of the animation curve.
const size_t  curveSize = 12;
const size_t  curve2Size = 16;

/// Control points of the animation curve.
glm::vec3 curveData[] = {
  glm::vec3(0.00, 0.0,  0.0),
  glm::vec3(-0.99,  1.15, 0.0),
  glm::vec3(-1.98,  1.15, 0.0),
  glm::vec3(-3.00,  0.0, 0.0),
  glm::vec3(-1.98, -1.15, 0.0),
  glm::vec3(-0.99, -1.15, 0.0),
  glm::vec3(0.00,  0.0, 0.0),
  glm::vec3(0.99,  1.15, 0.0),
  glm::vec3(1.98,  1.15, 0.0),
  glm::vec3(3.00,  0.0, 0.0),
  glm::vec3(1.98, -1.15, 0.0),
  glm::vec3(0.99, -1.15, 0.0)
};

glm::vec3 curve2Data[] = {
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.3, 0.2, 0.3),
        glm::vec3(0.6, 0.4, 0.6),
        glm::vec3(0.9, 0.6, 0.7),
        glm::vec3(1.5, 0.9, 0.7),
        glm::vec3(1.8, 1.2, 0.7),
        glm::vec3(2.1, 0.9, 0.7),
        glm::vec3(1.3, 0.2, 0.2),
        glm::vec3(0.3, -1.0, -0.2),
        glm::vec3(0.3, -0.5, 0.3),
        glm::vec3(0.3, 0.1, 0.6),
        glm::vec3(0.9, 0.6, 0.7),
        glm::vec3(1.5, 0.9, 0.7),
        glm::vec3(1.8, 1.2, 0.7),
        glm::vec3(2.1, 0.9, 0.7),
        glm::vec3(2.4, 0.6, 0.7)
        
};

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
glm::vec3 evaluateCatmullRollCurveSegment(const glm::vec3& P0, const glm::vec3& P1, const glm::vec3& P2, const glm::vec3& P3, const float t){
    glm::vec3 result(0.0, 0.0, 0.0);

    // evaluate point on a curve segment (defined by the control points P0...P3)
    // for the given value of parameter t
    float t3 = pow(t, 3);
    float t2 = pow(t, 2);

    result = P0 * (-1 * t3 + 2 * t2 - 1 * t + 0)
           + P1 * ( 3 * t3 - 5 * t2 + 0 * t + 2)
           + P2 * (-3 * t3 + 4 * t2 + 1 * t + 0)
           + P3 * ( 1 * t3 - 1 * t2 + 0 * t + 0);

    result *= 0.5f;
    return result;
}

glm::vec3 evaluateCoonsCurveSegment(const glm::vec3& P0, const glm::vec3& P1, const glm::vec3& P2, const glm::vec3& P3, const float t) {
    glm::vec3 result(0.0, 0.0, 0.0);

    // evaluate point on a curve segment (defined by the control points P0...P3)
    // for the given value of parameter t
    float t3 = pow(t, 3);
    float t2 = pow(t, 2);

    result = P0 * pow((1 - t), 3);
           + P1 * (3 * t3 - 6 * t2 + 4)
           + P2 * (-3 * t3 + 3 * t2 + 3 * t + 1)
           + P3 * t3;

    result /= 6.0f;
    return result;
}

//**************************************************************************************************
/// Evaluates a first derivative of Catmull-Rom curve segment.
/**
  \param[in] P0       First control point of the curve segment.
  \param[in] P1       Second control point of the curve segment.
  \param[in] P2       Third control point of the curve segment.
  \param[in] P3       Fourth control point of the curve segment.
  \param[in] t        Curve segment parameter. Must be within range [0, 1].
  \return             First derivative of the curve for parameter \a t.
*/
glm::vec3 evaluateCatmullRollCurveSegment_1stDerivative(const glm::vec3& P0, const glm::vec3& P1, const glm::vec3& P2, const glm::vec3& P3, const float t){
    glm::vec3 result(1.0, 0.0, 0.0);

    // evaluate first derivative for a point on a curve segment (defined by the control points P0...P3)
    // for the given value of parameter t

    float t3 = 3 * pow(t, 2);
    float t2 = 2 * t;

    result = P0 * (-1 * t3 + 2 * t2 - 1)
           + P1 * ( 3 * t3 - 5 * t2 + 0)
           + P2 * (-3 * t3 + 4 * t2 + 1)
           + P3 * ( 1 * t3 - 1 * t2 + 0);

    result *= 0.5f;
    return result;
}

glm::vec3 evaluateCoonsCurveSegment_1stDerivative(const glm::vec3& P0, const glm::vec3& P1, const glm::vec3& P2, const glm::vec3& P3, const float t) {
    glm::vec3 result(0.0, 0.0, 0.0);

    // evaluate point on a curve segment (defined by the control points P0...P3)
    // for the given value of parameter t
    float t3 = 3 * pow(t, 2);
    float t2 = 2 * t;

    result = P0 * pow((1 - t), 3);
             +P1 * (3 * t3 - 6 * t2)
            + P2 * (-3 * t3 + 3 * t2 + 3 * t)
            + P3 * t3;

    result /= 6.0f;
    return result;
}

//**************************************************************************************************
/// Evaluates a position on a closed curve composed of Catmull-Rom segments.
/**
  \param[in] points   Array of curve control points.
  \param[in] count    Number of curve control points.
  \param[in] t        Parameter for which the position shall be evaluated.
  \return             Position on the curve for parameter \a t.
  \note               Although the range of the parameter is from [0, \a count] (outside the range
                      the curve is periodic), one must presume any value (even negative).
*/
glm::vec3 evaluateCatmullRollClosedCurve(const glm::vec3 points[], const size_t count, const float t){
    glm::vec3 result(0.0, 0.0, 0.0);

    // based on the value of parameter t first find corresponding segment and its control points => i
    // and then call evaluateCurveSegment function with proper parameters to get a point on a closed curve
    int index = (int)t;

    result = evaluateCatmullRollCurveSegment(
        points[(index - 1 + count) % count],
        points[(index) % count],
        points[(index + 1) % count],
        points[(index + 2) % count],
        t - index
    );

    return result;
}

glm::vec3 evaluateCoonsClosedCurve(const glm::vec3 points[], const size_t count, const float t) {
    glm::vec3 result(0.0, 0.0, 0.0);

    // based on the value of parameter t first find corresponding segment and its control points => i
    // and then call evaluateCurveSegment function with proper parameters to get a point on a closed curve
    int index = (int)t;

    result = evaluateCoonsCurveSegment(
        points[(index - 1 + count) % count],
        points[(index) % count],
        points[(index + 1) % count],
        points[(index + 2) % count],
        t - index
    );

    return result;
}

//**************************************************************************************************
/// Evaluates a first derivative of a closed curve composed of Catmull-Rom segments.
/**
  \param[in] points   Array of curve control points.
  \param[in] count    Number of curve control points.
  \param[in] t        Parameter for which the derivative shall be evaluated.
  \return             First derivative of the curve for parameter \a t.
  \note               Although the range of the parameter is from [0, \a count] (outside the range
                      the curve is periodic), one must presume any value (even negative).
*/
glm::vec3 evaluateCatmullRollClosedCurve_1stDerivative(
    const glm::vec3 points[],
    const size_t    count,
    const float     t
) {
    glm::vec3 result(1.0, 0.0, 0.0);

    // based on the value of parameter t first find corresponding curve segment and its control points => i
    // and then call evaluateCurveSegment_1stDerivative function with proper parameters
    // to get a derivative for the given point on a closed curve
    int index = (int)t;

    result = evaluateCatmullRollCurveSegment_1stDerivative(
        points[(index - 1 + count) % count],
        points[(index) % count],
        points[(index + 1) % count],
        points[(index + 2) % count],
        t - index
    );

    return result;
}

glm::vec3 evaluateCoonsClosedCurve_1stDerivative(
    const glm::vec3 points[],
    const size_t    count,
    const float     t
) {
    glm::vec3 result(1.0, 0.0, 0.0);

    // based on the value of parameter t first find corresponding curve segment and its control points => i
    // and then call evaluateCurveSegment_1stDerivative function with proper parameters
    // to get a derivative for the given point on a closed curve
    int index = (int)t;

    result = evaluateCoonsCurveSegment_1stDerivative(
        points[(index - 1 + count) % count],
        points[(index) % count],
        points[(index + 1) % count],
        points[(index + 2) % count],
        t - index
    );

    return result;
}
