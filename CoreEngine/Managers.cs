using CoreEngine.Manager;
using OpenTK;

namespace CoreEngine
{
    public class Managers
    {
        public BlockManager _blockManager { get; }
        public TerrainManager _terrainManager { get; }
        public Camera _Camera { get; }
        public Physics _physics { get; }
        public Managers(Camera camera)
        {
            _Camera = camera;

            _blockManager= new BlockManager();
            _terrainManager= new TerrainManager();
            _physics = new Physics();

            SeedManager(_physics);
            SeedManager(_terrainManager);
            SeedManager(_blockManager);
        }

        public void SeedManager(ManagerBase managerBase)
        {
            managerBase._blockManager = _blockManager;
            managerBase.TerrainManager = _terrainManager;
            managerBase._managers = this;
            managerBase._Camera = _Camera;
            managerBase.Physics = _physics;
        }
    }
}