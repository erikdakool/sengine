using CoreEngine.Manager;

namespace CoreEngine.Components
{
    public abstract class Component : ManagerBase
    {
        public abstract void Init();
        public abstract void Update(float time);
    }
}