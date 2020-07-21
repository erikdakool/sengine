using System;
using OpenTK;

namespace CoreEngine.staticMethods
{
    public class PointMath
    {
        public static bool InsideFoc(Vector2 objectLoc, Vector2 playerLoc, Vector2 coneVector)
        {
            var pointVec = (objectLoc - playerLoc).Normalized();
            float dotProduct = Vector2.Dot(coneVector.Normalized(), pointVec);
            double angle = Math.Cos(MathHelper.DegreesToRadians(90));
            return dotProduct > angle;
        }

        public static bool inRange(float low, float high, float x)
        {
            return (x - high) * (x - low) <= 0;
        }
    }
}