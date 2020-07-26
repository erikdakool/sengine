using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using CoreEngine.GameObjects;
using CoreEngine.Models;
using CoreEngine.staticMethods;
using OpenTK;
using CoreEngine.staticMethods;
using OpenTK.Graphics.OpenGL4;

namespace CoreEngine.Manager
{
    public class TerrainManager : ManagerBase
    {
        private ConcurrentDictionary<Vector3I, Chunk> _chunks = new ConcurrentDictionary<Vector3I, Chunk>();
        private ConcurrentDictionary<Vector3I, bool> _ready = new ConcurrentDictionary<Vector3I, bool>();
        private ConcurrentDictionary<Vector3I, Chunk> _drawing = new ConcurrentDictionary<Vector3I, Chunk>();
        private Vector3I _current;

        private static int Range = 30;
        public TerrainManager()
        {
            _current = new Vector3I(0,0,0);
        }

        public void UpdateChunks(int x, int z)
        {
            var range = Range + 1;

            var removeable = _chunks.Select(a => a.Key).Where(a =>
                !PointMath.inRange(x - Range, x + Range, a.X) || !PointMath.inRange(z - Range, z + Range, a.Z));
            foreach (var vec in removeable)
            {
                _drawing.TryRemove(vec, out _);
                _ready.TryRemove(vec, out _);
            }

            for (int i = x-range; i <= x+range; i++)
            {
                for (int j = z-range; j <= z+range; j++)
                {
                    var v = new Vector3I(i,0,j);
                    if (!_chunks.ContainsKey(v))
                    {
                        GenerateChunk(v);
                    }
                }
            }
            
            for (int i = x-Range; i <= x+Range; i++)
            {
                for (int j = z-Range; j <= z+Range; j++)
                {
                    var v = new Vector3I(i,0,j);
                    if (!_drawing.ContainsKey(v) && !_ready.ContainsKey(v))
                    {
                        _ready.TryAdd(v,true);
                    }
                }
            }
        }
        
        public void Update()
        {
            int x = (int)_Camera.Position.X/ (Chunk.Width*2);
            int z = (int)_Camera.Position.Z/ (Chunk.Length*2);
            
            if (_current.X != x || _current.Z != z)
            {    
                var t =new Task(() =>
                {
                    UpdateChunks(x,z);
                });
                t.Start();
                _current = new Vector3I(x,0,z);
            }
            
            
            //Console.WriteLine(Current.X + " " +x);
            //if (xDiff==1)
            //{
            //    //Console.WriteLine("GENERATING");
            //    for (int i = z-Range; i < z+Range; i++)
            //    {
            //        var loc = new Vector3I(x+Range-1,0,i);
            //        //var t = new Task(() =>
            //        //{
            //            //_pending.TryAdd(loc, true);
            //            //_pending.TryAdd(loc.AddX(-Range * 2), false);
            //            GenerateChunk(loc);
            //            _chunks.TryRemove(loc.AddX(-Range  * 2),out _);
            //            //System.Threading.Thread.Sleep(100);
            //        //});
            //        //t.Start();
            //    }
            //    Current = Current.AddX(1);
            //}else if (xDiff == -1)
            //{
            //    for (int i = z-Range; i < z+Range; i++)
            //    {
            //        var loc = new Vector3I(x-Range+1,0,i);
            //       //var t = new Task(() =>
            //       //{
            //            GenerateChunk(loc);
            //            _chunks.TryRemove(loc.AddX(Range * 2),out _);
            //            //System.Threading.Thread.Sleep(100);
            //       // });
            //       // t.Start();
            //    }
            //    Current = Current.AddX(-1);
            //}
            //
            //
            ////Console.WriteLine(Current.X + " " +x);
            //if (zDiff==1)
            //{
            //    //Console.WriteLine("GENERATING");
            //    for (int i = x-Range; i < x+Range; i++)
            //    {
            //        var loc = new Vector3I(i,0,z+Range-1);
            //        //var t = new Task(() =>
            //        //{
            //            GenerateChunk(loc);
            //            _chunks.TryRemove(loc.AddZ(-Range * 2),out _);
            //            //System.Threading.Thread.Sleep(100);
            //        //});
            //        //t.Start();
            //    }
            //    Current = Current.AddZ(1);
            //}else if (zDiff == -1)
            //{
            //    for (int i = x-Range; i < x+Range; i++)
            //    {
            //        var loc = new Vector3I(i,0,z-Range+1);
            //        //var t = new Task(() =>
            //        //{
            //            GenerateChunk(loc);
            //            _chunks.TryRemove(loc.AddZ(Range * 2),out _);
            //            //System.Threading.Thread.Sleep(100);
            //        //});
            //        //t.Start();
            //    }
            //    Current = Current.AddZ(-1);
            //}
        }

        public void GenerateTerrain()
        {
            var range = Range + 1;
            for (int i = -range; i <= range; i++)
            {
                for (int j = -range; j <= range; j++)
                {
                    var v = new Vector3I(i,0,j);
                    var t = new Task(() =>
                    { 
                        GenerateChunk(v);
                    });
                    t.Start();
                }
                //await GenerateChunk(new Vector3I(i,0,j));
            }
            
            for (int i = -Range; i <= Range; i++)
            {
                for (int j = -Range; j <= Range; j++)
                {
                    var v = new Vector3I(i,0,j);
                    _ready.TryAdd(v, true);
                }
            }        
        }

        private int TopBlockLoc(int x, int z)
        {
            FastNoise myNoise = new FastNoise();
            myNoise.SetNoiseType(FastNoise.NoiseType.SimplexFractal);
            int y = -(int)(myNoise.GetNoise(x,z)*50);
            if (y < 0)
            {
                y = 0;
            }
            return y;
        }
        
        public void GenerateChunk(Vector3I loc)
        {
            var chunk = new Chunk(loc);
            for (int i = 0; i < Chunk.Width; i++)
            {
                for (int j = 0; j < Chunk.Length; j++)
                {
                    _managers.SeedManager(chunk);
                    int y = TopBlockLoc(i + loc.X * Chunk.Width, j + loc.Z * Chunk.Length);
                    int chunkTop = y;
                    if (chunkTop > 15)
                    {
                        chunkTop = 15;
                    }

                    if (y > 24)
                    {
                        for (int e = y; e >= 0; e--)
                        {
                            if (e == y)
                            {
                                chunk.AddBlock(i,e,j,6);
                            }
                            else
                            {
                                chunk.AddBlock(i,e,j,3);
                            }
                        }
                    }
                    else if (y > 20)
                    {
                        for (int e = y; e >= 0; e--)
                        {
                            chunk.AddBlock(i, e, j, 3);
                        }
                    }
                    else if (y > 2)
                    {
                        for (int e = y; e >= 0; e--)
                        {
                            if (e == y)
                            {
                                chunk.AddBlock(i,e,j,1);
                            }else if (y-e <= 5)
                            {
                                chunk.AddBlock(i,e,j,2);
                            }else if (y-e >= 5)
                            {
                                chunk.AddBlock(i,e,j,3);
                            }
                        }
                    }
                    else if(y >=1)
                    {
                        for (int e = chunkTop; e >= 0; e--)
                        {
                            chunk.AddBlock(i,e,j,4);
                        }
                    }
                    else
                    {
                        chunk.AddBlock(i,y,j,5);
                    }
                    

                }
            }
            
            _chunks.TryAdd(loc,chunk );
        }
        
        public void InitDraw()
        {
            var readies =_ready.Where(a => a.Value).Select(a => a.Key).OrderBy(a=>a.Distance(_current)).Take(2);
            //var ready = readies.FirstOrDefault();
            //if (ready != null)
            //{
            //    Chunk chunk;
            //    if (!_chunks.TryGetValue(ready, out chunk))
            //    {
            //        return;
            //    }
            //    chunk.UpdateSides();
            //    chunk.UpdateBuffer();
            //    _ready.TryRemove(ready, out _);
            //    _drawing.TryAdd(ready, chunk);
            //}
            
            foreach (var vector3I in readies)
            {

                Chunk chunk;
                if (!_chunks.TryGetValue(vector3I, out chunk))
                {
                    return;
                }
                chunk.UpdateSides();

                chunk.UpdateBuffer();
                _ready.TryRemove(vector3I, out _);
                _drawing.TryAdd(vector3I, chunk);
 

            }
        }

        public void Draw()
        {
            int e = 0;
            //var chunks = _chunks.ToDictionary(entry=>entry.Key,entry=>entry.Value);
            lock (_drawing)
            {
                var rot = _Camera.Yaw;
                
                var coneVec = new Vector2((float)Math.Cos(MathHelper.DegreesToRadians(rot)),(float)Math.Sin(MathHelper.DegreesToRadians(rot)));
                var playerLoc = _Camera.Position.Xz;
                
                foreach (var keyValuePair in _drawing)
                {
                    var locv = keyValuePair.Key.ToFloat().Xz * Chunk.Width*2;
                    if (PointMath.inRange(playerLoc.X - 2*Chunk.Width*2, playerLoc.X + 2*Chunk.Width*2, locv.X) &&
                        PointMath.inRange(playerLoc.Y - 2*Chunk.Width*2, playerLoc.Y + 2*Chunk.Width*2, locv.Y))
                    {
                        e += keyValuePair.Value.Render();
                    }
                    else if (PointMath.InsideFoc(locv, playerLoc, coneVec))
                    {
                        e+= keyValuePair.Value.Render();
                    }
                }
            }
            //Console.WriteLine(_chunks.Count + " " + e);
        }

        public void UnBind()
        {
            foreach (var keyValuePair in _drawing)
            {
                keyValuePair.Value.DeleteBuffers();
            }

            _blockManager.UnbindBlockTextures();
        }

        public Chunk GetChunk(int x, int y, int z)
        {
            return GetChunk(new Vector3I(x, y, z));
        }

        public Chunk GetChunk(Vector3I loc)
        {
            Chunk ret;
            _chunks.TryGetValue(loc, out ret);
            return ret;
        }

        public Block GetBlock(Vector3I loc)
        {
            var chunkLoc = loc / (Chunk.Width *2);
            var chunk = GetChunk(chunkLoc);
            if (chunk != null)
            {
                return chunk.GetBlock(loc - chunkLoc);
            }
            return null;
        }
    }
}