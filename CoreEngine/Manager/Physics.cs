using Noesis;
using OpenTK;

namespace CoreEngine.Manager
{
    public class Physics : ManagerBase
    {
        public Physics()
        {
            
        }

        public bool Collision(Vector3 loc, Vector3 diff, out Vector3 colDist)
        {
            colDist = new Vector3();
            return false;
        }
    }
}