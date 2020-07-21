using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using CoreEngine.Models;
using CoreEngine.OpenGLModels;
using OpenTK.Graphics.OpenGL4;
using GL = OpenTK.Graphics.OpenGL4.GL;
using InternalFormat = OpenTK.Graphics.OpenGL4.InternalFormat;
using PixelFormat = OpenTK.Graphics.OpenGL4.PixelFormat;
using SizedInternalFormat = OpenTK.Graphics.OpenGL4.SizedInternalFormat;
using TextureTarget = OpenTK.Graphics.OpenGL4.TextureTarget;
using TextureTarget3d = OpenTK.Graphics.OpenGL4.TextureTarget3d;

namespace CoreEngine.Manager
{
    public class BlockManager : ManagerBase
    {
        private Dictionary<int, BlockTexture> _blockTextures = new Dictionary<int, BlockTexture>();
        private List<BlockInfoModel> _blockInfoModels = new List<BlockInfoModel>();
        public Shader _shader { get; }

        private int TextureId;

        public BlockManager()
        {
            _shader = new Shader("Shaders/shader.vert", "Shaders/shader.frag");
            _shader.Use();
            var blockUrl = "Data/Json/block.json";
            var textureUrl = "Data/Json/textures.json";

            string blockJson = File.ReadAllText(blockUrl);
            string textureJson = File.ReadAllText(textureUrl);

            var blockInfoModels = JsonSerializer.Deserialize<List<BlockInfoModel>>(blockJson);
            var textureInfoModels = JsonSerializer.Deserialize<List<TextureInfoModel>>(textureJson);
            
            textureInfoModels.ForEach(a =>
            {
                _blockTextures.Add(a.Id,new BlockTexture("Data/Textures/textureMap2.png",a.X,a.Y));
            });
            
            blockInfoModels.ForEach(a =>
            {
                _blockInfoModels.Add(a);
            });
            BindBlockTextures();
        }

        public Dictionary<int, Texture> GetTextures(params int[] blocks)
        {
          // return _blockTextures.Where(a => _blockInfoModels
          //     .Any(b => blocks.Contains(b.Id) &&
          //               (b.Back==a.Key ||
          //                b.Front==a.Key ||
          //                b.Left==a.Key||
          //                b.Right==a.Key||
          //                b.Top==a.Key||
          //                b.Bottom==a.Key)))
          //     .ToDictionary(p=>p.Key,p=>p.Value);
          return null;
        }

        public BlockInfoModel GetBlock(int id)
        {
            return _blockInfoModels.FirstOrDefault(a => a.Id == id);
        }

        public void BindBlockTextures()
        {
            _shader.Use();
            GL.Uniform1(0,0);
            TextureId = GL.GenTexture();
            GL.ActiveTexture(0);
            GL.BindTexture(TextureTarget.Texture2DArray,TextureId);
            
            GL.TexStorage3D(TextureTarget3d.Texture2DArray,1,SizedInternalFormat.Rgba8,128,128,_blockTextures.Count);

            foreach (var keyValuePair in _blockTextures)
            {
                //var data = keyValuePair.Value.Data;
                //GL.TexSubImage3D(TextureTarget.Texture2DArray,
                //    0,
                //    0,0,i,
                //    data.Width,data.Height,keyValuePair.Key,
                //    PixelFormat.Bgra,
                //    PixelType.UnsignedByte,
                //    data.Scan0
                //    );
                keyValuePair.Value.BindToLayer(keyValuePair.Key);
            }
            
            GL.TexParameter(TextureTarget.Texture2DArray, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2DArray, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

            // Now, set the wrapping mode. S is for the X axis, and T is for the Y axis.
            // We set this to Repeat so that textures will repeat when wrapped. Not demonstrated here since the texture coordinates exactly match
            GL.TexParameter(TextureTarget.Texture2DArray, TextureParameterName.TextureWrapS, (int)TextureWrapMode.ClampToEdge);
            GL.TexParameter(TextureTarget.Texture2DArray, TextureParameterName.TextureWrapT, (int)TextureWrapMode.ClampToEdge);
            //GL.BindTextureUnit(keyValuePair.Key,keyValuePair.Value.Handle);
        }

        public void UnbindBlockTextures()
        {
            GL.DeleteProgram(_shader.Handle);
            foreach (var keyValuePair in _blockTextures)
            {
                //GL.DeleteTexture(keyValuePair.Value.Handle);
            }
        }
        
        
    }
}