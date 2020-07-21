using System.Drawing;
using System.Drawing.Imaging;
using OpenTK.Graphics.OpenGL4;

namespace CoreEngine.OpenGLModels
{
    public class BlockTexture
    {
        private static int gridCount = 10;
        private static int gridSize = 128;

        private string path;
        private int x;
        private int y;
        
        public BlockTexture(string path, int x, int y)
        {
            this.x = x;
            this.y = y;
            this.path = path;
        }

        public void BindToLayer(int i)
        {
            using (var image = new Bitmap(path))
            {
                var data = image.LockBits(
                    new Rectangle(gridSize*x, gridSize*y, image.Width/gridCount, image.Height/gridCount),
                    ImageLockMode.ReadOnly,
                    System.Drawing.Imaging.PixelFormat.Format32bppArgb);

                GL.TexSubImage3D(TextureTarget.Texture2DArray,
                    0,
                    0,0,i,
                    data.Width,data.Height,1,
                    OpenTK.Graphics.OpenGL4.PixelFormat.Bgra,
                    PixelType.UnsignedByte,
                    data.Scan0
                );
                i++;
            }
        }
    }
}