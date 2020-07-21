using CoreEngine.Manager;
using OpenTK;

namespace CoreEngine
{
    public class Managers
    {
        public BlockManager _blockManager { get; }
        public TerrainManager _terrainManager { get; }
        public Camera _Camera { get; }
        public Managers(Camera camera)
        {
            _Camera = camera;

            _blockManager= new BlockManager();
            SeedManager(_blockManager);
            
            _terrainManager= new TerrainManager();
            SeedManager(_terrainManager);

        }

        public void SeedManager(ManagerBase managerBase)
        {
            managerBase._blockManager = _blockManager;
            managerBase.TerrainManager = _terrainManager;
            managerBase._managers = this;
            managerBase._Camera = _Camera;
        }
    }
}