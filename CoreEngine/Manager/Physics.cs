using CoreEngine.Models;
using Noesis;
using OpenTK;

namespace CoreEngine.Manager
{
    public class Physics : ManagerBase
    {
        public Physics()
        {
            
        }

        public bool Collision(Vector3 loc, Vector3 diff)
        {
            var diff2 = new Vector3(-2,-2,-2);

            return !(TerrainManager.GetBlock(new Vector3I((loc + diff) / 2)) == null
                    && TerrainManager.GetBlock(new Vector3I((loc + diff + diff2) / 2)) == null
                );
        }
    }
}