using System;
using System.Collections.Generic;
using CoreEngine.Manager;
using CoreEngine.Models;
using CoreEngine.OpenGLModels;
using OpenTK;

namespace CoreEngine.GameObjects
{
    public class Block
    {
        private HashSet<Face> Faces = new HashSet<Face>();
        
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
        private Vector3 Pos { get;}
        
        public Block(BlockInfoModel blockInfoModel, Vector3 pos)
        {
            BlockInfoModel = blockInfoModel;
            Pos = pos;

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

        public ModelBuffer GetBufferObject()
        {
            
            var ret = new ModelBuffer();
            int e = 0;
            foreach (var face in Faces)
            {
                int texCounter = 0;
                //face.Indices.ForEach(a =>
                //{
                //    ret.Vertices.Add(SquareVertices[(int)a] + (Pos*2));
                //    ret.Colors.Add(SquareColors[(int)a]);

                //    
                //    
                //    var texcor = new Vector2();
                //    texcor.X = face.TexturePos[texCounter];
                //    texcor.Y = face.TexturePos[texCounter + 1];
                //    ret.TextureCor.Add(texcor);
                //    //ret.TextureCor.Add(SquareTextureCor[(int)a]);
                //    
                //    ret.TextureId.Add(face.TextureId);
                //    ret.Indices.Add((uint)e);
                //    e++;
                //    texCounter += 2;
                //});
                
                foreach (var a in Face.Ind[face.Dir])
                {
                    ret.Vertices.Add(SquareVertices[(int)a] + (Pos*2));
                    ret.Colors.Add(SquareColors[(int)a]);

                    
                    
                    var texcor = new Vector2();
                    texcor.X = Face.Tex[face.Dir][texCounter];
                    texcor.Y = Face.Tex[face.Dir][texCounter + 1];
                    ret.TextureCor.Add(texcor);
                    //ret.TextureCor.Add(SquareTextureCor[(int)a]);
                    
                    ret.TextureId.Add(face.TextureId);
                    ret.Indices.Add((uint)e);
                    e++;
                    texCounter += 2;
                }
            }
            return ret;
        }

        public void ClearFaces()
        {
            Faces.Clear();
        }

        public override string ToString()
        {
            return Pos.ToString();
        }
    }
}