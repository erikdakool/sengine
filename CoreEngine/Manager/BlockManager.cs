using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using CoreEngine.Models;
using CoreEngine.OpenGLModels;
using OpenTK.Graphics.OpenGL4;

namespace CoreEngine.Manager
{
    public class BlockManager : ManagerBase
    {
        private Dictionary<int, Texture> _blockTextures = new Dictionary<int, Texture>();
        private List<BlockInfoModel> _blockInfoModels = new List<BlockInfoModel>();
        public Shader _shader { get; }
        
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
                _blockTextures.Add(a.Id,new Texture("Data/Textures/textureMap2.png",a.X,a.Y));
            });
            
            blockInfoModels.ForEach(a =>
            {
                _blockInfoModels.Add(a);
            });
        }

        public Dictionary<int, Texture> GetTextures(params int[] blocks)
        {
            return _blockTextures.Where(a => _blockInfoModels
                .Any(b => blocks.Contains(b.Id) &&
                          (b.Back==a.Key ||
                           b.Front==a.Key ||
                           b.Left==a.Key||
                           b.Right==a.Key||
                           b.Top==a.Key||
                           b.Bottom==a.Key)))
                .ToDictionary(p=>p.Key,p=>p.Value);
        }

        public BlockInfoModel GetBlock(int id)
        {
            return _blockInfoModels.FirstOrDefault(a => a.Id == id);
        }

        public void BindBlockTextures()
        {
            foreach (var keyValuePair in _blockTextures)
            {
                GL.BindTextureUnit(keyValuePair.Key,keyValuePair.Value.Handle);
            }
        }

        public void UnbindBlockTextures()
        {
            GL.DeleteProgram(_shader.Handle);
            foreach (var keyValuePair in _blockTextures)
            {
                GL.DeleteTexture(keyValuePair.Value.Handle);
            }
        }
        
        
    }
}