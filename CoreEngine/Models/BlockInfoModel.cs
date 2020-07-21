namespace CoreEngine.Models
{
    public class BlockInfoModel
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Left { get; set; }
        public int Right { get; set; }
        public int Bottom { get; set; }
        public int Top { get; set; }
        public int Front { get; set; }
        public int Back { get; set; }
    }
}