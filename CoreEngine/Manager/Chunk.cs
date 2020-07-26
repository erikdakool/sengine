using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using CoreEngine.GameObjects;
using CoreEngine.Models;
using CoreEngine.OpenGLModels;
using OpenTK;
using OpenTK.Graphics.OpenGL4;

namespace CoreEngine.Manager
{
    public class Chunk : ManagerBase
    {
        private Dictionary<Vector3I,Block> Blocks = new Dictionary<Vector3I, Block>();
        
        private int _vertexArrayId = 0;
        private int _vertexBufferId = 0;
        private int _indiceBufferId = 0;

        public static int Width { get; set; } = 16;
        public static int Height { get; set; } = 16;
        public static int Length { get; set; } = 16;
        private Vector3I _loc;
        
        
        public List<float> Vertices { get; set; } = new List<float>();
        public List<uint> Indices { get; set; } = new List<uint>();
        
        public Chunk(Vector3I loc)
        {
            _loc = loc;
        }

        ~Chunk()
        {
            Console.WriteLine("Delete");
            //DeleteBuffers();    
        }

        public void AddBlock(int x, int y, int z, int id)
        {
            var loc = new Vector3I(x,y,z);
            //Console.WriteLine(loc.ToFloat()+_loc.ToFloat()*Width);
            Blocks.Add(loc,new Block(_blockManager.GetBlock(id),loc.ToFloat()+_loc.ToFloat()*Width));
            //Console.WriteLine(loc.ToFloat());
        }

        public void UpdateSides()
        {
            foreach (var pair in Blocks)
            {
                pair.Value.ClearFaces();
                //if (pair.Key.X == 0)
                //{
                //    var chunk = TerrainManager.GetChunk(_loc.AddX(-1));
                //    if (chunk != null && !chunk.BlockExists(pair.Key.AddX(-1)))
                //    {
                //        pair.Value.AddFace(Dir.LEFT);
                //    }
                //}else if (!BlockExists(pair.Key.AddX(-1)))
                //{
                //    pair.Value.AddFace(Dir.LEFT);
                //}
                if (VisibleSide(pair.Key,Dir.LEFT))
                {
                    pair.Value.AddFace(Dir.LEFT);
                }

                if (VisibleSide(pair.Key, Dir.RIGHT))
                {
                    pair.Value.AddFace(Dir.RIGHT);
                }

                if (VisibleSide(pair.Key, Dir.FRONT))
                {
                    pair.Value.AddFace(Dir.FRONT);
                }

                if (VisibleSide(pair.Key, Dir.BACK))
                {
                    pair.Value.AddFace(Dir.BACK);
                }

                if (VisibleSide(pair.Key, Dir.TOP))
                {
                    pair.Value.AddFace(Dir.TOP);
                }

                if (VisibleSide(pair.Key, Dir.BOTTOM))
                {
                    pair.Value.AddFace(Dir.BOTTOM);
                }
            }
            
            int offset = 0;
            foreach (var keyValuePair in Blocks)
            {
                keyValuePair.Value.UpdateBufferData(offset);
                //for (int i = 0; i < buffer.Indices.Count; i++)
                //{
                //    Vertices.Add(buffer.Vertices[i].X);
                //    Vertices.Add(buffer.Vertices[i].Y);
                //    Vertices.Add(buffer.Vertices[i].Z);
                //    
                //    //Vertices.Add(buffer.Colors[i].X);
                //    //Vertices.Add(buffer.Colors[i].Y);
                //    //Vertices.Add(buffer.Colors[i].Z);
                //    
                //    Vertices.Add(buffer.TextureCor[i].X);
                //    Vertices.Add(buffer.TextureCor[i].Y);
                //    Vertices.Add(buffer.TextureId[i]);
                //    
                //    Indices.Add((uint)(buffer.Indices[i]+offset));
                //}
                Vertices.AddRange(keyValuePair.Value.Vertices);
                keyValuePair.Value.Indices.ForEach(a =>
                {
                    Indices.Add((uint)(a));
                });
                offset = Vertices.Count/6;
            }
        }

        public void UpdateBuffer()
        {
            
            _blockManager._shader.Use();
            
            var sampler = GL.GetUniformLocation(_blockManager._shader.Handle, "u_Textures");

            //int[] samplers = Enumerable.Range(0, 8).ToArray();
            //GL.Uniform1i(sampler,8,samplers);
            //GL.Uniform1(sampler,1);
            
            _vertexArrayId = GL.GenVertexArray();
            GL.BindVertexArray(_vertexArrayId);
            
            
            _vertexBufferId = GL.GenBuffer();
            GL.BindBuffer(BufferTarget.ArrayBuffer,_vertexBufferId);
            GL.BufferData(BufferTarget.ArrayBuffer, Vertices.Count * sizeof(float), Vertices.ToArray(), BufferUsageHint.StaticDraw);

            _indiceBufferId = GL.GenBuffer();
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, _indiceBufferId);
            GL.BufferData(BufferTarget.ElementArrayBuffer, Indices.Count * sizeof(uint), Indices.ToArray(), BufferUsageHint.StaticDraw);
            
            GL.EnableVertexAttribArray(0);
            GL.VertexAttribPointer(0,3,VertexAttribPointerType.Float,false,6*sizeof(float),0);
            
            //GL.EnableVertexAttribArray(1);
            //GL.VertexAttribPointer(1,3,VertexAttribPointerType.Float,false,9*sizeof(float),3*sizeof(float));
            
            GL.EnableVertexAttribArray(2);
            GL.VertexAttribPointer(2,2,VertexAttribPointerType.Float,false,6*sizeof(float),3*sizeof(float));
            
            GL.EnableVertexAttribArray(3);
            GL.VertexAttribPointer(3,1,VertexAttribPointerType.Float,false,6*sizeof(float),5*sizeof(float));
            //return bufferModel;
        }

        public int Render()
        {
            _blockManager._shader.Use();
            //_blockManager.BindBlockTextures();

            //_shader.SetMatrix4("model", model);
            _blockManager._shader.SetMatrix4("view", _Camera.GetViewMatrix());
            _blockManager._shader.SetMatrix4("projection", _Camera.GetProjectionMatrix());

            GL.BindVertexArray(_vertexArrayId);
            GL.DrawElements(PrimitiveType.Triangles,Indices.Count,DrawElementsType.UnsignedInt,0);
            return Indices.Count;
        }

        public void DeleteBuffers()
        {
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            GL.BindVertexArray(0);
            GL.UseProgram(0);

            GL.DeleteBuffer(_vertexBufferId);
            GL.DeleteVertexArray(_vertexArrayId);
        }

        private bool BlockExists(Vector3I loc)
        {
            return Blocks.ContainsKey(loc);
        }

        public Block GetBlock(int x, int y, int z)
        {
            return GetBlock(new Vector3I(x, y, z));
        }

        public Block GetBlock(Vector3I loc)
        {
            Block ret;
            Blocks.TryGetValue(loc, out ret);
            return ret;
        } 
        
        private bool VisibleSide(Vector3I loc, Dir dir)
        {
            switch (dir)
            {
                case Dir.LEFT:
                    if (loc.X == 0)
                    {
                        var t = TerrainManager.GetChunk(_loc.AddX(-1));
                        if (t == null)
                            return false;
                        return !t.BlockExists(loc.AddX(Width - 1));
                    }
                    return !BlockExists(loc.AddX(-1));
                case Dir.RIGHT:
                    if (loc.X == Width - 1)
                    {
                        var t = TerrainManager.GetChunk(_loc.AddX(1));
                        if (t == null)
                            return false;
                        return !t.BlockExists(loc.AddX(-(Width-1)));
                    }
                    return !BlockExists(loc.AddX(1));
                case Dir.FRONT:
                    if (loc.Z == Length - 1)
                    {
                        var t = TerrainManager.GetChunk(_loc.AddZ(1));
                        if (t == null)
                            return false;
                        return !t.BlockExists(loc.AddZ(-(Length - 1)));
                    }
                    return !BlockExists(loc.AddZ(1));
                case Dir.BACK:
                    if (loc.Z == 0)
                    {
                        var t = TerrainManager.GetChunk(_loc.AddZ(-1));
                        if (t == null)
                            return false;
                        return !t.BlockExists(loc.AddZ(Length-1));
                    }
                    return !BlockExists(loc.AddZ(-1));
                case Dir.TOP:
                    if (loc.Y == Height-1)
                        return false;
                    return !BlockExists(loc.AddY(1));
                case Dir.BOTTOM:
                    if (loc.Y == 0)
                        return false;
                    return !BlockExists(loc.AddY(-1));
            }

            return false;
        }
    }
}