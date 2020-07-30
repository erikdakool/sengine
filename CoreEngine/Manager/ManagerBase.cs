namespace CoreEngine.Manager
{
    public class ManagerBase
    {
        public BlockManager _blockManager { get; set; }
        public TerrainManager TerrainManager { get; set; }
        public Managers _managers { get; set; }
        public Camera _Camera { get; set; }
        
        public Physics Physics { get; set; }
    }
}