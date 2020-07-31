using System.IO;

namespace CoreEngine.NoesisAddons
{
    public class CustomXamlProvider : Noesis.XamlProvider
    {
        public CustomXamlProvider()
        {
            
        }
        
        public override Stream LoadXaml(string filename)
        {
            return new FileStream(filename, FileMode.Open);
        }
    }
}