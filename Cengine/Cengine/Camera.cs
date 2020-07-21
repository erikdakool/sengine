using System.Numerics;
using Silk.NET.OpenGL;

namespace Cengine
{
    public class Camera
    {
        private Vector3 CameraPosition = new Vector3(0.0f, 0.0f, 3.0f);
        private Vector3 CameraFront = new Vector3(0.0f, 0.0f, -1.0f);
        private Vector3 CameraUp = new Vector3(0.0f, 1.0f, 3.0f);
        private Vector3 CameraDirection = Vector3.Zero;

        public Matrix4x4 GetViewMatrix()
        {
            return Matrix4x4.CreateLookAt(CameraPosition, CameraPosition + CameraFront, CameraUp);
        }
    }
}