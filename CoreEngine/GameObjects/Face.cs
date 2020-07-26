using System;
using System.Collections.Generic;

namespace CoreEngine.GameObjects
{
    public class Face
    {
        public float TextureId { get; set; }
        public Dir Dir { get; set; }
        
        public static Dictionary<Dir,List<uint>> Ind = new Dictionary<Dir, List<uint>>
        {
            {Dir.FRONT,new List<uint>{0,1,2,2,3,0}},
            {Dir.BACK,new List<uint>{4,7,6,6,5,4}},
            {Dir.LEFT,new List<uint>{4,0,3,3,7,4}},
            {Dir.RIGHT,new List<uint>{1,5,6,6,2,1}},
            {Dir.TOP,new List<uint>{3,2,6,6,7,3}},
            {Dir.BOTTOM,new List<uint>{1,0,4,4,5,1}}
        };
        
        public static Dictionary<Dir,List<float>> Tex = new Dictionary<Dir, List<float>>
        {
            {Dir.FRONT,new List<float>{0,1,1,1,1,0,1,0,0,0,0,1}},
            {Dir.BACK,new List<float>{0,1,0,0,1,0,1,0,1,1,0,1}},
            {Dir.LEFT,new List<float>{0,1,1,1,1,0,1,0,0,0,0,1}},
            {Dir.RIGHT,new List<float>{0,1,1,1,1,0,1,0,0,0,0,1}},
            {Dir.TOP,new List<float>{0,0,1,0,1,1,1,1,0,1,0,0}},
            {Dir.BOTTOM,new List<float>{0,0,1,0,1,1,1,1,0,1,0,0}}
        };
        
        public Face(Dir dir, float textureId)
        {
            //switch (dir) {
            //    case Dir.FRONT:
            //        Indices = new List<uint>{0,1,2,2,3,0};
            //        TexturePos = new List<float>{0,1,1,1,1,0,1,0,0,0,0,1};
            //        //Indices = new List<uint>{0,1,3,1,2,3};
            //        break;
            //    case Dir.BACK:
            //        Indices = new List<uint>{4,7,6,6,5,4};   
            //        TexturePos = new List<float>{0,1,0,0,1,0,1,0,1,1,0,1};
            //        break;
            //    case Dir.LEFT:
            //        Indices = new List<uint>{4,0,3,3,7,4};    
            //        TexturePos = new List<float>{0,1,1,1,1,0,1,0,0,0,0,1};
            //        break;
            //    case Dir.RIGHT:
            //        Indices = new List<uint>{1,5,6,6,2,1};    
            //        TexturePos = new List<float>{0,1,1,1,1,0,1,0,0,0,0,1};
            //        break;
            //    case Dir.TOP:
            //        Indices = new List<uint>{3,2,6,6,7,3};    
            //        TexturePos = new List<float>{0,0,1,0,1,1,1,1,0,1,0,0};
            //        break;
            //    case Dir.BOTTOM:
            //        Indices = new List<uint>{1,0,4,4,5,1};    
            //        TexturePos = new List<float>{0,0,1,0,1,1,1,1,0,1,0,0};
            //        break;
            //}
            TextureId = textureId;
            Dir = dir;
        }
    }
}