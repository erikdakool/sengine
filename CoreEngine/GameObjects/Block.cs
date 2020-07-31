using System;
using System.Collections.Generic;
using System.Linq;
using CoreEngine.Manager;
using CoreEngine.Models;
using CoreEngine.OpenGLModels;
using OpenTK;

namespace CoreEngine.GameObjects
{
    public class Block
    {
        private HashSet<Face> Faces = new HashSet<Face>();

        public List<float> Vertices { get; set; } 
        public List<uint> Indices { get; set; }

        private static readonly List<Vector3> SquareVertices =  new List<Vector3> {
            new Vector3(-1,-1,1),
            new Vector3(1,-1,1),
            new Vector3(1,1,1),
            new Vector3(-1,1,1),
            new Vector3(-1,-1,-1),
            new Vector3(1,-1,-1),
            new Vector3(1,1,-1),
            new Vector3(-1,1,-1),
        };
        
        private static readonly List<Vector4> SquareColors = new List<Vector4> {
            new Vector4(0,1,0,1),
            new Vector4(0,1,0,1),
            new Vector4(0,1,0,1),
            new Vector4(0,1,0,1),
            new Vector4(0,0,1,1),
            new Vector4(0,0,1,1),
            new Vector4(0,0,1,1),
            new Vector4(0,0,1,1)
        };

        
        private readonly BlockInfoModel BlockInfoModel;
        private Vector3 _chunkPos { get;}
        
        public Block(BlockInfoModel blockInfoModel, Vector3 chunkPos)
        {
            BlockInfoModel = blockInfoModel;
            _chunkPos = chunkPos;

            //AddFace(Dir.TOP);
            //AddFace(Dir.LEFT);
            //AddFace(Dir.RIGHT);
            //AddFace(Dir.BACK);
            //AddFace(Dir.BOTTOM);
            //AddFace(Dir.FRONT);
        }

        public void AddFace(Dir dir)
        {
            switch (dir)
            {
                case Dir.LEFT :
                    Faces.Add(new Face(Dir.LEFT, BlockInfoModel.Left));
                    break;
                case Dir.FRONT :
                    Faces.Add(new Face(Dir.FRONT, BlockInfoModel.Front));
                    break;
                case Dir.BACK :
                    Faces.Add(new Face(Dir.BACK, BlockInfoModel.Back));
                    break;
                case Dir.TOP :
                    Faces.Add(new Face(Dir.TOP, BlockInfoModel.Top));
                    break; 
                case Dir.BOTTOM :
                    Faces.Add(new Face(Dir.BOTTOM, BlockInfoModel.Bottom));
                    break;
                case Dir.RIGHT :
                    Faces.Add(new Face(Dir.RIGHT, BlockInfoModel.Right));
                    break;
            }
        }

        public void UpdateBufferData(int offset)
        {
            Vertices = new List<float>();
            Indices = new List<uint>();
            
            int indiceCounter = offset;
            foreach (var face in Faces)
            {
                int texCounter = 0;
                
                Dictionary<uint, uint> indDict = new Dictionary<uint, uint>();
                foreach (var a in Face.Ind[face.Dir])
                {
                    if (!indDict.ContainsKey(a))
                    {
                        indDict.Add(a,(uint) indiceCounter);
                        Vertices.Add(SquareVertices[(int)a].X +_chunkPos.X*2);
                        Vertices.Add(SquareVertices[(int)a].Y +_chunkPos.Y*2);
                        Vertices.Add(SquareVertices[(int)a].Z +_chunkPos.Z*2);
                        Vertices.Add(Face.Tex[face.Dir][texCounter]);
                        Vertices.Add(Face.Tex[face.Dir][texCounter+1]);
                        Vertices.Add(face.TextureId);
                        indiceCounter++;
                    }
                    Indices.Add(indDict[a]);

                    texCounter += 2;
                }
            }
        }

        public void ClearFaces()
        {
            Faces.Clear();
        }

        public override string ToString()
        {
            return _chunkPos.ToString();
        }
    }
}