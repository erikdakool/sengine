using System;
using System.Collections.Generic;
using OpenTK;

namespace CoreEngine.Models
{
    public class Vector3I : IEquatable<Vector3I>
    {
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }

        public Vector3I(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Vector3I(Vector3 v)
        {
            X = (int) v.X;
            Y = (int) v.Y;
            Z = (int) v.Z;
        }

        public static Vector3I operator -(Vector3I a, Vector3I b)
        {
            return new Vector3I(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }
        
        public static Vector3I operator /(Vector3I a, int b)
        {
            return new Vector3I(a.X /b, a.Y /b, a.Z /b);
        }
        
        public static Vector3I operator *(Vector3I a, int b)
        {
            return new Vector3I(a.X *b, a.Y *b, a.Z *b);
        }


        public Vector3I AddX(int d)
        {
            return new Vector3I(X+d,Y,Z);
        }

        public Vector3I AddY(int d)
        {
            return new Vector3I(X,Y+d,Z);

        }

        public Vector3I AddZ(int d)
        {
            return new Vector3I(X,Y,Z+d);
        }

        public Vector3 ToFloat()
        {
            return new Vector3(X,Y,Z);
        }

        public Vector3I Abs()
        {
            return new Vector3I(Math.Abs(X),Math.Abs(Y),Math.Abs(Z));
        }

        public override bool Equals(object? obj)
        {
            return Equals(obj as Vector3I);
        }

        public override int GetHashCode()
        {
            int hash = (int) 16777619;
            // Suitable nullity checks etc, of course :)
            hash = (hash * 16777619) ^ X.GetHashCode();
            hash = (hash * 16777619) ^ Y.GetHashCode();
            hash = (hash * 16777619) ^ Z.GetHashCode();
            return hash;          
        }

        public float Distance(Vector3I other)
        {
            return (float) Math.Sqrt(( X -  other.X) * (X -  other.X) + ( Y -  other.Y) * ( Y -  other.Y) + ( Z -other.Z) * ( Z -  other.Z));
        }

        public bool Equals(Vector3I other)
        {
            return (other.X == X && other.Y == Y && other.Z == Z);
        }

        public override string ToString()
        {
            return X + " " + Y + " " + Z;
        }
    }
}