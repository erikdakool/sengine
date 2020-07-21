using System.Collections.Generic;
using OpenTK;

namespace CoreEngine.OpenGLModels
{
    public class ModelBuffer
    {
        public List<Vector3> Vertices { get; set; } = new List<Vector3>();
        public List<Vector4> Colors { get; set; } = new List<Vector4>();
        public List<Vector2> TextureCor { get; set; } = new List<Vector2>();
        public List<float> TextureId { get; set; } = new List<float>();
        public List<uint> Indices { get; set; } = new List<uint>();
    }
}